module Kernel
  # Mostly for compatability with existing CRuby code.
  # This version of `pp` simply calls `puts obj.inspect`
  # for each object in `objs`
  def pp(*objs)
    objs.each { |o| puts o.inspect }
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
    raise TypeError unless path.class == String

    if File.exist?(path)
      eval(File.read(path), nil, path, 0)
    else
      $LOAD_PATH.each do |dir|
        if File.exist?("#{dir}/#{path}")
          eval(File.read("#{dir}/#{path}"), nil, "#{dir}/#{path}", 0)
          return true
        end
      end
      raise LoadError.new "File not found -- #{path}"
    end
    true
  end
  
  
end

class LoadError < ScriptError
  def initialize(msg = nil)
    super
  end
end
