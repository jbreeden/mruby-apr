class Parser
  Glob = Parser.new do
    @meta_characters = [
      :open_group,
      :close_group,
      :comma,
      :backslash
    ]
    @meta_character_values = [
      '{',
      '}',
      ',',
      '\\'
    ]
    @meta_character_map = {}
    @meta_characters.zip(@meta_character_values).each do |k, v|
      @meta_character_map[k] = v
    end
    @path_sep = '/'
    @special_chars = [@path_sep].concat @meta_character_values

    def lex(&block)
      # TODO: Ever heard of Regular Expressions?
      i = 0
      block[node(kind: :start)]
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
      block[node(kind: :end)]
    end

    # GLOB = PARTLIST '$'
    # ROOTED_SEGMENT_LIST = #TODO
    # SEGMENT_LIST = # TODO
    #
    # SEGMENT = start EXPR !!end
    #   | start EXPR !!slash
    #   | slash EXPR !!end
    #
    # EXPR = STRING
    #   | GROUP
    #   | EXPR EXPR
    #
    # GROUP = OPEN_GROUP close_group | open_group close_group
    #
    # OPEN_GROUP = open_group (comma|STRING)
    #   | OPEN_GROUP comma comma
    #   | OPEN_GROUP comma !!close_group
    #
    # STRING = string | backslash [string[:meta_characters:]]

    # Simple string reduction
    reduction(:STRING, [:string]) do |reduced, nodes|
      reduced.value = nodes[0].value
    end

    # String escaping
    reduction(:STRING, [:backslash, [:STRING, :string].concat(@meta_characters)]) do |reduced, nodes|
      if nodes[1].kind == :string || nodes[1].kind == :STRING
        reduced.value = nodes[1].value
      else
        reduced.value = @meta_character_map[nodes[1].kind]
      end
    end

    # OPEN_GROUP Creation
    reduction(:OPEN_GROUP, [:open_group, [:comma, :STRING]]) do |reduced, nodes|
      if nodes[1].kind == :comma
        # A group like '{,...}' starts with the empty string as a matcher
        reduced.strings = ['']
      else
        reduced.strings = [nodes[1].value]
      end
    end

    # OPEN_GROUP Continuation
    reduction(:OPEN_GROUP, [:OPEN_GROUP, :comma, :STRING]) do |reduced, nodes|
      reduced.strings = nodes[0].strings
      reduced.strings.push(nodes[2].value)
    end

    # OPEN_GROUP empty-string continuation
    reduction(:OPEN_GROUP, [:OPEN_GROUP, :comma, :comma]) do |reduced, nodes|
      reduced.strings = nodes[0].strings
      reduced.strings.push('')
    end

    # OPEN_GROUP empty-string terminated
    reduction(:OPEN_GROUP, [:OPEN_GROUP, :comma], is: :close_group) do |reduced, nodes|
      reduced.strings = nodes[0].strings
      reduced.strings.push('')
    end

    # OPEN_CROUP closure
    reduction(:GROUP, [:OPEN_GROUP, :close_group]) do |reduced, nodes|
      reduced.strings = nodes[0].strings
    end

    # Empty Group
    reduction(:GROUP, [:open_group, :close_group]) do |reduced, nodes|
      reduced.strings = ['']
    end

    # EXPR creation
    reduction(:EXPR, [[:STRING, :GROUP]]) do |reduced, nodes|
      reduced.children = [nodes[0]]
    end

    # EXPR concatentation
    reduction(:EXPR, [:EXPR, :EXPR]) do |reduced, nodes|
      reduced.children = nodes[0].children.concat(nodes[1].children)
    end

    # SEGMENT = start EXPR !!
    #   | ^ EXPR !!slash
    #   | slash EXPR !!slash
    #   | slash EXPR !!end
    reduction(:SEGMNET, [:])
  end
end
