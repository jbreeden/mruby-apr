# mruby glob.rb  "/./a/{}b/c{}/d{e}f/{g,h,}/{,i,j}/{k/l}/[m/n]//o///p"

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
        if @children[@children.length - 2] != :'**'
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

  def rooted?
    @rooted
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

    # # Special case:
    # # leading ** doens't need to be surrounded by /'s to be significant
    # if str[0..1] == '**'
    #   yield :'**'
    #   str = str[2..str.length]
    # end

    while str && !str.empty? && str != ?/ && str != ?\\
      step = 1
      if str.start_with?(?\\)
        token = str[1]
        step = 2
      elsif "{},".include?(str[0])
        token = str[0].to_sym
        step = 1
      elsif str[0..2] == '**/'
        # ** is only significant if it stands alone
        token = [:'**', :/]
        step = str[/^(\*\*\/)+/].length
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

class Globber
  def initialize
    @match_num = 0
  end

  def glob(pattern, &block)
    ast = GlobAST.new(pattern) rescue nil
    return nil unless ast
    segments = ast.segments
    glob_recurse(ast.rooted? ? '/' : '', ast.segments, &block)
  end

  def explicit(dir)
    dir.empty? ? '.' : dir
  end

  def join(dir, file)
    if dir[dir.length - 1] == ?/
      "#{dir}#{file}"
    elsif dir.empty?
      file
    else
      "#{dir}/#{file}"
    end
  end

  def glob_recurse(dir, segments, &block)
    if segments.length == 1
      segments[0].each do |pattern|
        Dir.entries(explicit(dir)).each do |e|
          full = join(dir, e)
          if match_file(pattern, e)
            block[full, @match_num]
            @match_num += 1
          end
        end
      end
    elsif segments[0] == [:'**']
      Dir.entries(explicit(dir)).each do |e|
        full = join(dir, e)
        if e[0] != '.' && File.directory?(full)
          glob_recurse(full, segments, &block)
        end
      end
      glob_recurse(dir, segments[1..segments.length], &block)
    else
      segments[0].each do |pattern|
        Dir.entries(explicit(dir)).each do |e|
          full = join(dir, e)
          if File.directory?(full) && match_file(pattern, e)
            glob_recurse(full, segments[1..segments.length], &block)
          end
        end
      end
    end
  end

  def match_file(pattern, file)
    return false if file[0] == '.' unless pattern[0] == '.'
    return true if pattern == '.' && file == '.'
    return true if pattern == '..' && file == '..'
    return true if pattern == '*'
    APR::APR_SUCCESS == APR.apr_fnmatch(pattern, file, 0)
  end
end

def glob(pattern)
  results = []
  globber = Globber.new
  globber.glob(pattern) do |match, match_num|
    results.push(match)
  end
  results
end

# GlobAST.new(ARGV[0]).each_segment { |segment| puts segment.map { |pattern| "/#{pattern}/(#{pattern.class})"}}
puts glob(ARGV[0]).length
