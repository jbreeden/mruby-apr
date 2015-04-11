#<
# # Module Process
#>
module Process
  #<
  # ## `::spawn(*command)`
  # Starts a new process and returns the PID.
  # Does not wait for the process to end.
  # - Args
  #   + `command`. One of:
  #      - commandline : command line string which is passed to the standard shell
  #      - cmdname, arg1, ... : command name and one or more arguments (no shell)
  #>
  def self.spawn(*command)
    p, argv = APR::Process.with_ruby_semantics(*command)
    p.exec(argv).pid
  end

  #<
  # ## `::wait(pid)`
  # Waits for the process with the given PID to exit. <br/>
  # Returns the exit code (no Process::Status implemented yet)
  #>
  def self.wait(pid)
    APR::Process.wait(pid)
  end
end
