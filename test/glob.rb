class GlobCursor
  def initialize
    @first = nil
    @next_first = nil
    @next_last = nil
  end

  # Called from nodes
  # -----------------

  # A node must never add itself back to the cursor!
  # During iteration, each node is visited,
  # and it's "next" pointer is reused to simulate two queues:
  # The current nodes being traversed, and the next nodes to be traversed.
  # (During glob, you're always looking at an existing set of directories,
  #  and building a list of their decendants that match the next part of the
  #  glob - in a loop. )
  # If you add yourself back to the cursor, you go become the tail of the next
  # queue. if another node is added, it replaces your "next" pointer, and the
  # "current" queue is confused with the tail of the next queue.
  # TODO: ASCIIFLOW
  def add_cursor(node)
    raise "Tried to add a node that already had a 'next' node" if node.next
    if @next_last # Already some node on the "next" queue
      @next_last.next = node
      @next_last = node
    else
      @next_first = node
      @next_last = @next_first
    end
  end
  alias keep_alive add_cursor

  def rotate_cursors
    @first = @next_first
    @next_first = nil
    @next_last = nil
  end

  def each_node
    if @first
      l = @first
      while l
        yield l
        l = l.next
      end
    end
  end

  # Public
  # ------

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
end

class GlobNode
  attr_accessor :name, :path, :next

  def initialize(name, cursor, parent=nil)
    @cursor = cursor
    # Caching this has a _huge_ impact on speed... though memory is an issue
    @path ||= if parent && parent.path
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

  def immediate_match(pattern)
    return unless File.directory?(explicit_path)

    Dir.entries(explicit_path).each { |e|
      if match_file(pattern, e)
        @cursor.add_cursor GlobNode.new(e, @cursor, self)
      end
    }
  end

  def deep_match(pattern, no_timer=nil)
    # Deep match is only called if there is a following immediate_match,
    # So this entry will definitely be removed if it's not a directory.

    return unless File.directory?(explicit_path)
    entries = Dir.entries(explicit_path)

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
  root_node = GlobNode.new(nil, cursor)
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
