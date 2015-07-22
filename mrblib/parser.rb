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
      reduce
    end
    block[]
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

  def reduce
    begin
      reduced = false
      @reductions.each do |reduction|
        to_reduce = nil

        if reduction[RED_LA_IDX].nil?
          to_reduce = pop(reduction[RED_EXPECTED_IDX])
        else
          if reduction[RED_LA_IDX][:is]
            to_reduce = pop_positive_la(reduction[RED_EXPECTED_IDX], reduction[RED_LA_IDX][:is])
          elsif reduction[RED_LA_IDX][:not]
            to_reduce = pop_negative_la(reduction[RED_EXPECTED_IDX], reduction[RED_LA_IDX][:not])
          else
            raise "Invalid lookahead. Must be {is: kind(s)} or {not: kind(s)}"
          end
        end

        if to_reduce
          puts "Reducing: #{to_reduce}"
          new_node = node(kind: reduction[RED_KIND_IDX])
          reduction[RED_BLOCK_IDX][new_node, to_reduce]
          push new_node
          puts "Reduced to: #{new_node}"
          reduced ||= true
        end
      end
    end while reduced
  end

  def lex(&block)
    # TODO: Default implementation
  end

  def push(new_node)
    if new_node.class == OpenStruct
      @stack.push(new_node)
    else
      @stack.push(node(new_node))
    end
  end

  def pop_positive_la(kinds, lookaheads)
    kinds = Array(kinds)
    lookaheads = Array(lookaheads)
    pop(kinds) do |la|
      lookaheads.find { |la_kind| la_kind == la.kind }
    end
  end

  def pop_negative_la(kinds, lookaheads)
    kinds = Array(kinds)
    lookaheads = Array(lookaheads)
    pop(kinds) do |la|
      lookaheads.find { |la_kind| la_kind == la.kind }.nil?
    end
  end

  def pop(args, &lookahead)
    args = Array(args)
    matched = true
    if lookahead
      return nil if @stack.length < (args.length + 1)
      checkset = @stack[(-(args.length + 1))..(@stack.length)]
    else
      return nil if @stack.length < (args.length)
      checkset = @stack[(-args.length)..(@stack.length)]
    end
    (0..(args.length - 1)).each do |i|
      matched &&= (Array(args[i]).find { |kind| kind == checkset[i].kind } != nil)
    end

    if matched && lookahead
      matched = lookahead[checkset.last]
    end

    if matched
      result = []
      (args.length).times do
        result.unshift @stack.pop
      end
      result
    else
      nil
    end
  end

  def node(opts)
    Node.new(opts)
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
