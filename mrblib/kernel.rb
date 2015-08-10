#<
# # Module Kernel
#>
module Kernel
  def spawn(*command)
    Process.spawn(*command)
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
      eval(File.read(path))
    else
      raise LoadError.new "File not found -- #{path}"
    end

    true
  end
end

class LoadError < ScriptError
  def initialize
    super
  end
end
