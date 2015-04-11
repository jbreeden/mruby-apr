#<
# # Module Kernel
#>
module Kernel
  #<
  # ## ``#`(command)``
  # Runs a process, waits for it to finish, and returns the exit code.
  # - Args
  #   + `command`. One of:
  #      - commandline : command line string which is passed to the standard shell
  #      - cmdname, arg1, ... : command name and one or more arguments (no shell)
  #>
  def self.`(command)
    p = APR::Process.new
    p.cmdtype_set :APR_SHELLCMD_ENV
    p.io_set :APR_NO_PIPE, :APR_FULL_BLOCK, :APR_NO_PIPE
    p.exec command.shellsplit
    result = ""
    while line = p.out.gets
      result += line
    end
    result
  end
  
  #<
  # ## `#popen(command, &block)`
  # Runs the specified command as a subprocess. 
  # The subprocess' standard input will be connected to the returned IO object.
  # - Args
  #   + `command`. One of:
  #      - commandline : command line string which is passed to the standard shell
  #      - [cmdname, arg1, ...] : command name and one or more arguments (no shell)
  #   + `block`. Optional. If supplied, the IO object will be passed into the block as the only param.
  #     If supplied, the return of `popen` will be the return of the block instead of the IO object.
  #>
  def popen(command, &block)
    p, argv = APR::Process.with_ruby_semantics(*command)
    p.io_set :APR_FULL_BLOCK, :APR_NO_PIPE, :APR_NO_PIPE
    p.exec(argv)
    
    if block_given?
      value = block[p.in]
      p.in.close
      value
    else
      p.in
    end
  end
  
  #<
  # ## `#sleep(seconds)`
  # Sleeps for `seconds`
  # - Args
  #   + `seconds`: Number of seconds to sleep (can be a fraction)
  #>
  def sleep(seconds)
    APR::System.sleep((seconds * 1000).to_i, :milliseconds)
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
end
