# mruby glob.rb  "/./a/{}b/c{}/d{e}f/{g,h,}/{,i,j}/{k/l}/[m/n]//o///p"

class GlobCursor
  def initialize
    @first = nil
    @next_first = nil
    @next_last = nil
    @node_pool = nil
  end

  # Maintain a pool of old nodes to reuse, rather than allocating new ones
  # ----------------------------------------------------------------------

  def get_node(name, cursor, parent=nil)
    if @node_pool
      result = @node_pool
      @node_pool = @node_pool.next
      result.initialize(name, cursor, parent)
      result
    else
      GlobNode.new(name, cursor, parent)
    end
  end

  def return_node(node)
    node.next = @node_pool
    @node_pool = node
  end

  # Called from nodes
  # -----------------

  # A node must never add itself back to the cursor!
  # During iteration, each node is visited,
  # and it's "next" pointer is reused to simulate two queues:
  # The current nodes being traversed, and the next nodes to be traversed.
  #
  # (During glob, you're always looking at an existing set of directories,
  #  and building a list of their decendants that match the next part of the
  #  glob - in a loop.)
  #
  # If you add yourself back to the cursor, you go become the tail of the "next"
  # queue. if another node is added, it replaces your "next" pointer, and the
  # "current" queue is confused with the tail of the next queue.
  #
  # TODO: ASCIIFLOW
  def enqueue_possible_match(node)
    ## Debug
    # raise "Tried to add a node that already had a 'next' node" if node.next
    # raise "Enqueing node_pool #{node}" if node == @node_pool
    if @next_last # Already some node on the "next" queue
      @next_last.next = node
      @next_last = node
    else
      @next_first = node
      @next_last = @next_first
    end
  end

  def rotate_heads
    @first = @next_first
    @next_first = nil
    @next_last = nil
  end

  def each_match
    if @first
      node = @first
      while node
        yield node
        node_next = node.next
        return_node(node) # Modifies the "next" pointer
        node = node_next
      end
    end
  end

  # Public
  # ------

  def immediate_match(segment)
    rotate_heads
    each_match do |node|
      node.immediate_match(segment)
    end
  end

  def deep_match(segment)
    rotate_heads
    each_match do |node|
      node.deep_match(segment)
    end
  end

  def finish
    rotate_heads
    result = []
    each_match do |node|
      result.push(node.path)
    end
    result
  end
end

class GlobNode
  attr_accessor :path, :next

  def initialize(name, cursor, parent=nil)
    @next = nil
    @cursor = cursor
    @path = if parent && parent.path
      ## Debug
      # raise "Cannot add a node with nil name to a parent" if name = nil
      if parent.path == '/'
        "/#{name}"
      else
        "#{parent.path}/#{name}"
      end
    else
      name
    end
  end

  def explicit_path
    # if name is nil, this signifies the implicit '.', which should
    # not be included in the results string.
    @path || '.'
  end

  def immediate_match(segment)
    return unless File.directory?(explicit_path)

    entries = Dir.entries(explicit_path) rescue [] # Ignore permission errors

    entries.each { |e|
      t_start = Time.now
      segment.each do |pattern|
        if match_file(pattern, e)
          @cursor.enqueue_possible_match @cursor.get_node(e, @cursor, self)
          break
        end
      end
      $t_match += Time.now - t_start
    }
  end

  def deep_match(segment)
    # Deep match is only called if there is a following immediate_match,
    # So this entry will definitely be removed if it's not a directory.

    return unless File.directory?(explicit_path)
    entries = Dir.entries(explicit_path) rescue [] # Ignore permission errors

    entries.each do |e|
      child = @cursor.get_node(e, @cursor, self)
      t_start = Time.now
      segment.each do |pattern|
        if match_file(pattern, e)
          @cursor.enqueue_possible_match child
          break
        end
      end
      $t_match += Time.now - t_start
      child.deep_match(segment) unless e[0] == '.'
    end
  end

  def match_file(pattern, file)
    if file[0] == '.'
      return false unless pattern[0] == '.'
    end
    return true if pattern == '.' && file == '.'
    return true if pattern == '..' && file == '..'
    return true if pattern == '*'
    APR::APR_SUCCESS == APR.apr_fnmatch(pattern, file, 0)
  end
end

class GlobAST
  class ParserError < StandardError
  end

  class Node
    attr_accessor :parent, :children

    def initialize(parent)
      @parent = parent
      @children = []
    end
  end

  class Root < Node
    def initialize
      super(nil)
    end

    def accept(token)
      case token
      when :'{'
        child = Alternation.new(self)
        @children.push(child)
        child
      when :'}'
        raise ParserError.new("Unmatched closing brace")
      when :'/'
        @children.push(token)
        self
      when :'**'
        if @children[@children.length - 2] != '**'
          @children.push(token)
        end
        self
      when :'$'
        # Do nothing
        self
      else
        # Everything else is a string at the root level
        if @children.last.kind_of?(String)
          @children.last.concat(token.to_s)
        else
          @children.push(token.to_s)
        end
        self
      end
    end

    def to_a
      parts = [['']]
      @children.each do |child|
        case child
        when :'/'
          parts.push([''])
        when :'**'
          parts.last[0] = :'**'
        when String
          parts.last.each do |str|
            str.concat(child)
          end
        when Alternation
          replacement = []
          last_part = parts.pop
          last_part.each do |str|
            child.to_a.each do |alt|
              replacement.push "#{str}#{alt}"
            end
          end
          parts.push(replacement)
        end
      end
      parts
    end

  end

  class Alternation < Node
    def initialize(*args)
      super
      @children.push('')
    end

    def accept(token)
      case token
      when :'{'
        child = Alternation.new(self)
        children.push(child)
        child
      when :'}'
        parent
      when :','
        @children.push(:',')
        @children.push('')
        self
      when :'$'
        raise ParserError.new("Unmatched open brace")
      else
        # Everything else is considered a string in alternation,
        # so append it onto the most recent alternative
        @children.push(token.to_s)
        self
      end
    end

    def to_a
      alts = [['']]
      @children.each do |child|
        case child
        when String
          alts.last.each { |alt| alt.concat(child) }
        when :','
          alts.push([''])
        when Alternation
          replacement = []
          last_alt = alts.pop
          last_alt.each do |alt|
            child.to_a.each do |child_alt|
              replacement.push "#{alt}#{child_alt}"
            end
          end
          alts.push(replacement)
        end
      end
      alts.flatten
    end
  end

  def initialize(str)
    @root = Root.new
    @rooted = str[0] == ?/
    @table = nil
    parse(str)
  end

  def each_segment(&block)
    @table.each_with_index do |segment, i|
      if @rooted && i == 0
        next # Skip the leading [''] segment
      else
        block[segment, @table[i + 1]]
      end
    end
  end

  def segments
    result = []
    each_segment do |seg|
      result.push(seg)
    end
    result
  end

  private

  def parse(str)
    current_node = @root
    lex(str) do |token|
      current_node = current_node.accept(token)
    end
    @table = @root.to_a
  end

  def lex(str)
    match = nil
    token = nil

    # Special case:
    # leading ** doens't need to be surrounded by /'s to be significant
    if str[0..1] == '**'
      yield :'**'
      str = str[2..str.length]
    end

    while str && !str.empty? && str != ?/ && str != ?\\
      step = 1
      if str.start_with?(?\\)
        token = str[1]
        step = 2
      elsif "{},".include?(str[0])
        token = str[0].to_sym
        step = 1
      elsif str[0..3] == '/**/'
        # ** is only significant if it stands
        token = [:/, :'**', :/]
        step = str[/^\/(\*\*\/)+/].length
      elsif str[0] == ?/
        # Collapse consecutive /'s
        token = :/
        step = str[/^\/*/].length
      elsif str[0] == ?[
        # passthrough the character sets
        token = str[/^(\\.|[^\\])+\]/]
        step = token.length
      else
        i = 1
        i += 1 until "{},/\\".include?(str[i]) || str[i].nil?
        token = str[0...i]
        step = token.length
      end

      str = str[(step)...(str.length)]
      [token].flatten.each { |t| yield t }
    end
    yield :'$'
  end
end

def glob(pattern)
  ast = GlobAST.new(pattern) rescue nil
  return [] unless ast

  cursor = GlobCursor.new
  root_node = GlobNode.new(nil, cursor)
  cursor.enqueue_possible_match(root_node)

  skip = 0
  ast.each_segment do |segment, lookahead|
    unless skip == 0
      skip -= 1
      next
    end
    if segment == [:'**']
      cursor.deep_match(lookahead)
      skip = 1
    else
      cursor.immediate_match(segment)
    end
  end
  cursor.finish
end

# GlobAST.new(ARGV[0]).each_segment { |segment| puts segment.map { |pattern| "/#{pattern}/(#{pattern.class})"}}
$t_match = 0
puts glob(ARGV[0]).length
puts $t_match
