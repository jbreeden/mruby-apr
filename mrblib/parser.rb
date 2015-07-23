require 'ostruct' unless Object.const_defined?(:MRUBY_VERSION)

class Parser
  class Node < OpenStruct; end

  def initialize(&block)
    @stack = []
    @input = nil
    @reductions = []
    self.instance_eval(&block) unless block.nil?
  end

  def debug(str)
    parse(str) do
      print_stack
    end
  end

  def parse(str, &block)
    @input = str
    lex do |token|
      # puts "Lexed: #{token}"
      push(token)
      apply_reductions
    end
    block[] if block
    @stack = []
    @input = nil
  end

  RED_KIND_IDX = 0
  RED_EXPECTED_IDX = 1
  RED_LA_IDX = 2
  RED_BLOCK_IDX = 3
  def reduction(kind, expected, lookahead_opt = nil, &block)
    @reductions.push([kind, expected, lookahead_opt, block])
  end

  private

  def lex(&block)
    # TODO: Default implementation
  end

  def apply_reductions
    begin
      reduced = false
      @reductions.each do |reduction|
        reduced ||= try_reduce(reduction)
      end
    end while reduced
  end

  def try_reduce(reduction)
    kinds_expected = reduction[RED_EXPECTED_IDX]
    lookahead_needed = !(reduction[RED_LA_IDX].nil?)

    match = pop(kinds_expected, lookahead: lookahead_needed)
    return false unless match

    puts "Reducing: #{match.map { |m| m.kind }.join(', ')} #{'(lookahead)' if lookahead_needed}"

    to_reduce = lookahead_needed ? match[0...-1] : match
    lookahead = lookahead_needed ? match.last : nil

    if lookahead_needed && reduction[RED_LA_IDX][:is]
      unless lookahead.kind == reduction[RED_LA_IDX][:is]
        push(match)
        return false
      end
    elsif lookahead_needed && reduction[RED_LA_IDX][:not]
      unless lookahead.kind != reduction[RED_LA_IDX][:not]
        push(match)
        return false
      end
    elsif lookahead_needed
      raise "Invalid lookahead. Must be {is: kind(s)} or {not: kind(s)} (was #{reduction[RED_LA_IDX]})"
    end

    new_node = Node.new(kind: reduction[RED_KIND_IDX])
    reduction[RED_BLOCK_IDX][new_node, to_reduce]
    puts "Reduced: #{new_node.kind}"
    push(new_node)
    if lookahead
      puts "Pushing back lookahead #{lookahead.kind}"
      push(lookahead)
    end
    true
  end

  def push(new_nodes)
    new_nodes = Array(new_nodes)
    new_nodes.each do |new_node|
      if new_node.class == Node
        @stack.push(new_node)
      else
        @stack.push(Node.new(new_node))
      end
    end
  end

  def pop(kinds_expected, opt = { lookahead: false })
    lookahead = opt[:lookahead] || opt == true
    kinds_expected = Array(kinds_expected)
    matched = true

    # Check that enough nodes are on the stack to perform the match
    if lookahead
      return nil if @stack.length < (kinds_expected.length + 1)
      checkset = @stack[(-(kinds_expected.length + 1))..(@stack.length)]
    else
      return nil if @stack.length < (kinds_expected.length)
      checkset = @stack[(-kinds_expected.length)..(@stack.length)]
    end

    # Perform the match (only on kinds_expected length, ignore the lookahead)
    (0..(kinds_expected.length - 1)).each do |i|
      # If a members of kinds_expected is an array, it denotes `or`, so match if any is found
      matched &&= (Array(kinds_expected[i]).find { |kind| kind == checkset[i].kind } != nil)
    end

    if matched
      if lookahead
        @stack = @stack[0...(-(kinds_expected.length + 1))]
      else
        @stack = @stack[0...(-kinds_expected.length)]
      end
      checkset
    else
      nil
    end
  end

  def print_stack
    indent = 0
    @stack.each do |node|
      print_node(node, indent)
    end
  end

  def print_node(node, indent)
    properties = node.to_h.keys.reject { |k| k == :children || node[k].class == Node }.reduce('') do |acc, cur|
      (acc == '' ? '' : acc + ', ') + "#{cur.to_s} = #{node[cur].to_s}"
    end
    puts ((' ' * indent) + properties)
    node.to_h.keys.select { |k| k == :children || node[k].class == Node }.each do |k|
      if k == :children && node[k].respond_to?(:each)
        node[k].each do |child|
          print_node(child, indent + 2)
        end
      else
        print_node(node[k], indent + 2)
      end
    end
  end
end
