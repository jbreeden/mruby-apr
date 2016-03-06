class Pathname
  ROOT = '/'
  DOT = '.'
  DOT_DOT = '..'
  
  def initialize(path_str)
    path_str = File::Private.to_path_str(path_str)
    @path = path_str.dup
  end
  
  def self.join(*parts)
    rooted = false
    if parts[0] == ROOT
      rooted = true
    end
    parts = parts.map { |p| 
      p.to_s
    }.select { |p|
      p != File::SEPARATOR && !p.empty?
    }
    str = parts.join(File::SEPARATOR)
    if rooted
      str = "#{ROOT}#{str}"
    end
    str
  end
  
  def +(other)
    Pathname.new(self.to_s + File::SEPARATOR + other.to_s)
  end
  
  # Non-standard
  def <<(other)
    @path.concat(File::SEPARATOR).concat(other.to_s)
    self
  end
  
  def absolute?
    @path.start_with?(ROOT)
  end
  
  def dup
    Pathname.new(@path.dup)
  end
  
  # Non-standard
  def cleanpath!
    parts = each_filename.to_a
    
    if absolute?
      parts.unshift ROOT
    end

    result = []
    parts.each do |part|
      case part
      when DOT
        next
      when DOT_DOT
        case result.last
        when ROOT
          # No parent directory of the root
          next
        when DOT_DOT
          # If the last part was deemed a useful parent ref,
          # then we need this one too.
          result.push(DOT_DOT)
        when nil
          # This is the first part of the path, it must be useful.
          result.push(DOT_DOT)
        else
          # There is a path segment we can just pop to reduce the ..
          result.pop
        end
      else
        result.push(part)
      end
    end

    replace(result.empty? ? DOT : self.class.join(*result))
    
    self
  end

  # Cleans the path by removing consecutive slashes, and useless dots.
  def cleanpath
    dup.cleanpath!
  end
  
  def hash
    @path.hash
  end
  
  def parent
    if root?
      self
    else
      Pathname.new(each_filename.to_a[0..-1].join(File::SEPARATOR))
    end
  end
  
  # Non-standard
  def replace(new_path)
    @path = new_path.to_s.dup
    self
  end
  
  def relative?
    @path.start_with?(ROOT)
  end
  
  def root?
    return false if @path.length == 0
    @path.each_char do |c|
      return false unless c == ROOT
    end
    true
  end
  
  def sub(pattern, replacement)
    Pathname.new(self.to_s.sub(pattern, replacement))
  end
  
  def each_filename
    return self.enum_for(:each_filename) unless block_given?
    
    @path.split(File::SEPARATOR).
      select { |p| p && !p.empty? }.
      each { |f| yield f }
  end
  
  def to_s
    @path.dup
  end
  alias to_str to_s
end
