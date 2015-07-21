require 'ostruct' unless Object.const_defined?(:MRUBY_VERSION)

class Parser
  def parse(str)
    @stack = []
    @input = str
    @context = nil
    @meta_characters =  {
      :open_group => '{',
      :close_group => '}',
      :comma => ',',
      :backslash => '\\'
    }
    @path_sep = '/'
    @special_chars = [@path_sep].concat @meta_characters.values

    lex do |token|
      puts token
    end
    lex do |token|
      push(token)
      reduce
    end
    pp @stack
  end

  private

  def node(opts)
    OpenStruct.new(opts)
  end

  def reduce
    # GLOB = PARTLIST '$'
    # PARTLIST = PARTLIST PART | PART PART
    # PART = ^ EXPRLIST !!'$' | ^ EXPRLIST !!'/' | '/' EXPRLIST !!'/' | / EXPRTLIST !!'$'
    # EXPRLIST = EXPRLIST EXPR | EXPR EXPR
    #
    # EXPR = if context != :group
    #   STRING | GROUP
    # end
    #
    # GROUP = STRINGLIST close_group | open_group close_group
    #
    # STRINGLIST = open_group !!(STRING|comma|close_group)
    # {} {,} {asdf,} {,adf} {asdf,asdf}
    #
    # STRING = string | escape | STRING string

    reduced = true
    while reduced
      puts @stack.map { |n| n.kind }.join ', '
      if @context != :group
        # STRING
        if reduced = pop(:string)
          push(kind: :STRING, value: reduced[0].value)
        elsif reduced = pop(:backslash, @meta_characters.keys)
          push(kind: :STRING, value: @meta_characters[reduced[1].kind])
        elsif reduced = pop_negative_la([:backslash], @meta_characters.keys)
          push(kind: :STRING, value: reduced)
        else
          reduced = false
        end
      else
        reduced = false
      end
    end
  end

  def lex(&block)
    i = 0
    block[node(kind: :START)]
    while i < @input.length
      case @input[i]
      when '{'
        block[node(kind: :open_group)]
        i += 1
      when '}'
        block[node(kind: :close_group)]
        i += 1
      when ','
        block[node(kind: :comma)]
        i += 1
      when '\\'
        block[node(kind: :backslash)]
        i += 1
      when '/'
        block[node(kind: :slash)]
        i += 1
      else
        str = @input[i]
        i += 1
        while !@special_chars.index(@input[i]) && i < @input.length
          str += @input[i]
          i += 1
        end
        block[node(kind: :string, value: str)]
      end
    end
    block[node(kind: :END)]
  end

  def push(node)
    if node.class == OpenStruct
      @stack.unshift(node)
    else
      @stack.unshift(OpenStruct.new(node))
    end
  end

  def pop_positive_la(kinds, lookahead)
    return nil if @stack.length < (kinds.length + 1)
    if (result = pop(*kinds)) &&  (Array(lookahead).find { |kind| kind == @stack[i].kind } != nil)
      result
    else
      @stack = result.concat(@stack) unless result.nil?
      nil
    end
  end

  def pop_negative_la(kinds, lookahead)
    return nil if @stack.length < (kinds.length + 1)
    result = nil
    if (result = pop(*kinds)) &&  (Array(lookahead).find { |kind| kind == @stack[i].kind } == nil)
      result
    else
      @stack = result.concat(@stack) unless result.nil?
      nil
    end
  end

  def pop(*args)
    return nil if @stack.length < args.length
    matched = false
    (0..(args.length - 1)).each do |i|
      matched ||= (Array(args[i]).find { |kind| kind == @stack[i].kind } != nil)
    end
    if matched
      result = []
      (args.length).times do
        result.push @stack.shift
      end
      result
    else
      nil
    end
  end

end
