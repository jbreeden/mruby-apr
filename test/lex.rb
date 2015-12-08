class FileMatch
  def initialize
    @alternatives = ['']
  end

  def alternatives
    if @err
      []
    else
      @alternatives
    end
  end

  def start_alt
    @root = @alternatives.map { |a| a.dup }
    @alternatives = []
  end

  def end_alt
    @root = nil
  end

  def add_alt(str)
    @alternatives.concat @root.map { |r| r.dup.concat(str) }
  end

  def concat(str)
    @alternatives.each { |a| a.concat str }
  end

  def self.from(str)
    match = FileMatch.new
    result = match.parse(str)
    match
  end

  private

  def parse(str)
    text = ''

    brace_level = 0

    lex(str) do |token|
      # Normalize out-of-choice commas to strings
      if token.kind_of?(String) || (brace_level == 0 && token == :',')
        text.concat token.to_s
        next
      end

      if token == :'{'
        self.concat(text)
        text = ''
        self.start_alt if brace_level == 0
        brace_level += 1
      elsif token == :'}'
        self.add_alt(text)
        text = ''
        brace_level -= 1
        self.end_alt if brace_level == 0
        if brace_level < 0
          @err = true
          return
        end
      elsif token == :','
        self.add_alt(text)
        text = ''
      elsif token == :'$'
        self.concat(text)
        text = ''
      end
    end

    if brace_level > 0
      @err = true
    end
  end

  def lex(str)
    match = nil

    while str && !str.empty?
      if match = str[/^\\\\/]
        yield match
      elsif match = str[/^\\./]
        yield match[1]
      elsif match = str[/^\{/]
        yield :'{'
      elsif match = str[/^\}/]
        yield :'}'
      elsif match = str[/^,/]
        yield :','
      else match = str[0]
        yield match
      end
      str = str[(match.length)...(str.length)]
    end
    yield :'$'
  end

end

puts FileMatch.from(ARGV[0]).alternatives
