$TOPLEVEL_OBJ = self

module Kernel
  # Mostly for compatability with existing CRuby code.
  # This version of `pp` simply calls `puts obj.inspect`
  # for each object in `objs`
  def pp(*objs)
    objs.each { |o| puts o.inspect }
  end
  
  # Mostly for compatability with existing CRuby code.
  # This version of `pretty_inspect` simply calls `self.inspect`
  def pretty_inspect
    self.inspect
  end
  
  def spawn(*command)
    Process.spawn(*command)
  end

  def system(cmd)
    pid = spawn(cmd)
    Process.wait(pid)
    $?.exitstatus == 0
  end

  def `(command)
    r, w = IO.pipe
    pid = spawn(command, {out: w})
    w.close
    result = r.read
    r.close
    Process.wait(pid)
    result
  end

  def load(path)
    unless path.kind_of?(String)
      path = path.to_str
    end

    if File.exist?(path)
      eval(File.read(path), nil, path, 0)
    else
      $LOAD_PATH.each do |dir|
        full_path = File.absolute_path("#{dir}#{File::SEPARATOR}#{path}")
        if File.exist?(full_path)
          eval(File.read(full_path), nil, full_path, 0)
          return true
        end
      end
      raise LoadError.new "Cannot load such file -- #{path}"
    end
    true
  end
  
  ALREADY_LOADED = 1
  LOADED = 2
  DNE = 3
  
  def try_require(full_path)
    # trace = false
    # trace = true if full_path.end_with?('classes.rb')
    # puts "try_require: full_path" if trace
    
    if $LOADED_FEATURES.include?(full_path)
      return ALREADY_LOADED
    end
    
    if File.exist?(full_path)
      $LOADED_FEATURES.push(full_path)
      begin
        eval(File.read(full_path), nil, full_path, 0)
      rescue SystemCallError => ex
        $LOADED_FEATURES.pop
        raise ex # Losing the backtrace... mruby limitation
      end
      return LOADED
    else
      return DNE
    end      
  end
  
  def require(path)
    unless path.kind_of?(String)
      path = path.to_str
    end
    
    if $BUILTIN_FEATURES.include?(path)
      return false
    end
    
    empty = ''
    [empty].concat($LOAD_PATH).each do |dir|
      full_path = ''
      unless dir == empty
        full_path << dir
        full_path << File::SEPARATOR
      end
      full_path << path
      full_path << '.rb' unless path.end_with?('.rb')

      # puts "require '#{full_path}'" if trace
      result = try_require(full_path)
      case result
      when ALREADY_LOADED
        return false
      when LOADED
        return true
      else
        next
      end
    end
    
    raise LoadError.new "Cannot load such file -- #{path}"
  end

end

class LoadError < ScriptError
  def initialize(msg = nil)
    super
  end
end
