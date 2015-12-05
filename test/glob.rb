class GlobCursor
  class Link
    attr_accessor :next, :node
    def initialize(node)
      @node = node
    end
  end

  def initialize
    @first = nil
    @next_first = nil
    @next_last = nil
  end

  # Called from nodes
  # -----------------

  def add_cursor(node)
    if @next_last
      @next_last.next = Link.new(node)
      @next_last = @next_last.next
    else
      @next_first = Link.new(node)
      @next_last = @next_first
    end
  end
  alias keep_alive add_cursor

  # Called from driver
  # ------------------

  def immediate_match(pattern)
    rotate_cursors
    each_node do |node|
      node.immediate_match(pattern)
    end
  end

  def deep_match(lookahead)
    rotate_cursors
    each_node do |node|
      node.deep_match(lookahead)
    end
  end

  def finish
    rotate_cursors
    result = []
    each_node do |node|
      result.push(node.path)
    end
    result
  end

  # Private
  # -------

  def rotate_cursors
    @first = @next_first
    @next_first = nil
    @next_last = nil
  end

  def each_node
    if @first
      l = @first
      while l
        yield l.node
        l = l.next
      end
    end
  end
end

class GlobNode
  attr_accessor :name, :path

  def initialize(name, cursor, parent=nil)
    @cursor = cursor
    # Caching this has a _huge_ impact on speed... though memory is an issue
    @path ||= if parent && parent.path
      "#{parent.path}/#{name}"
    else
      name
    end
  end

  def immediate_match(pattern)
    return unless File.directory?(path)

    Dir.entries(path).each { |e|
      if match_file(pattern, e)
        @cursor.add_cursor GlobNode.new(e, @cursor, self)
      end
    }
  end

  def deep_match(pattern, no_timer=nil)
    # Deep match is only called if there is a following immediate_match,
    # So this entry will definitely be removed if it's not a directory.

    return unless File.directory?(path)
    entries = Dir.entries(path)

    entries.each do |e|
      child = GlobNode.new(e, @cursor, self)
      if match_file(pattern, e)
        @cursor.add_cursor child
      end
      child.deep_match(pattern, true) unless e[0] == '.'
    end
  end

  def match_file(pattern, file)
    if file[0] == '.'
      return false unless pattern[0] == '.'
    end
    APR::APR_SUCCESS == APR.apr_fnmatch(pattern, file, 0)
  end

end

def glob(pattern)
  tokens = pattern.split('/')
  return [] if tokens.length == 0
  tokens.inject([tokens[0]]) { |acc, cur| acc.push(cur) unless acc.last == '**' && cur == '**'; acc}
  cursor = GlobCursor.new
  root_node = GlobNode.new('.', cursor)
  cursor.add_cursor(root_node)

  @just_epsiloned = false
  (0...tokens.length).each do |i|
    if @just_epsiloned
      @just_epsiloned = false
      next
    end
    if (i == (tokens.length - 1)) || (tokens[i] != '**')
      cursor.immediate_match(tokens[i])
    else
      cursor.deep_match(tokens[i + 1])
      @just_epsiloned = true
    end
  end
  cursor.finish
end

puts glob('**/*').length
