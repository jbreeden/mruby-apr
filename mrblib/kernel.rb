#<
# # Module Kernel
#>
module Kernel
  def self.`(command)
    # TODO
  end

  #<
  # ## `#system(*command)`
  # Runs a process, waits for it to finish, and returns the exit code.
  # - Args
  #   + `command`. One of:
  #      - commandline : command line string which is passed to the standard shell
  #      - cmdname, arg1, ... : command name and one or more arguments (no shell)
  #>
  def system(command)
    Process.wait Process.spawn(*command)
  end

  #<
  # ## `#spawn(*command)`
  # Starts a new process and returns the PID.
  # Does not wait for the process to end.
  # - Args
  #   + `command`. One of:
  #      - commandline : command line string which is passed to the standard shell
  #      - cmdname, arg1, ... : command name and one or more arguments (no shell)
  #>
  def spawn(*command)
    Process.spawn(*command)
  end
end
