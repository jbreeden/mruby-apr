#<
# # Module Kernel
#>
module Kernel
  def spawn(*command)
    Process.spawn(*command)
  end

  def `(command)
    r, w = IO.pipe
    spawn(command, {out: w})
    w.close
    result = r.read
    r.close
    result
  end
end
