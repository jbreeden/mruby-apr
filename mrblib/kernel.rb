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
end
