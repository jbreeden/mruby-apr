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
    p = APR::Process.new

    if command.length == 0
      raise ArgumentError.new("No command specified")
    elsif command.length == 1 && command[0].class == String
      argv = command[0].shellsplit
      p.cmdtype_set :APR_SHELLCMD_ENV
    elsif command.length == 1
      argv = command[0].to_s.shellsplit
      p.cmdtype_set :APR_SHELLCMD_ENV
    else
      argv = command.map{ |arg| arg.to_s}
      p.cmdtype_set :APR_PROGRAM_PATH
    end

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
