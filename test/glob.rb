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

  def immediate_match(pattern)
    rotate_heads
    each_match do |node|
      node.immediate_match(pattern)
    end
  end

  def deep_match(pattern)
    rotate_heads
    each_match do |node|
      node.deep_match(pattern)
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

  def immediate_match(pattern)
    return unless File.directory?(explicit_path)

    Dir.entries(explicit_path).each { |e|
      if match_file(pattern, e)
        @cursor.enqueue_possible_match @cursor.get_node(e, @cursor, self)
      end
    }
  end

  def deep_match(pattern, no_timer=nil)
    # Deep match is only called if there is a following immediate_match,
    # So this entry will definitely be removed if it's not a directory.

    return unless File.directory?(explicit_path)
    entries = Dir.entries(explicit_path)

    entries.each do |e|
      child = @cursor.get_node(e, @cursor, self)
      if match_file(pattern, e)
        @cursor.enqueue_possible_match child
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
  cursor.enqueue_possible_match(root_node)

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

puts glob('*/*/*').length
