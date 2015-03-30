# Module Kernel

## `#system(*command)`
Runs a process, waits for it to finish, and returns the exit code.
- Args
  + `command`. One of:
     - commandline : command line string which is passed to the standard shell
     - cmdname, arg1, ... : command name and one or more arguments (no shell)

## `#spawn(*command)`
Starts a new process and returns the PID.
Does not wait for the process to end.
- Args
  + `command`. One of:
     - commandline : command line string which is passed to the standard shell
     - cmdname, arg1, ... : command name and one or more arguments (no shell)

## `#sleep(seconds)`
Sleeps for `seconds`
- Args
  + `seconds`: Number of seconds to sleep (can be a fraction)

