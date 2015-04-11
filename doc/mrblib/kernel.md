# Module Kernel

## ``#`(command)``
Runs a process, waits for it to finish, and returns the exit code.
- Args
  + `command`. One of:
     - commandline : command line string which is passed to the standard shell
     - cmdname, arg1, ... : command name and one or more arguments (no shell)

## `#popen(command, &block)`
Runs the specified command as a subprocess. 
The subprocess' standard input will be connected to the returned IO object.
- Args
  + `command`. One of:
     - commandline : command line string which is passed to the standard shell
     - [cmdname, arg1, ...] : command name and one or more arguments (no shell)
  + `block`. Optional. If supplied, the IO object will be passed into the block as the only param.
    If supplied, the return of `popen` will be the return of the block instead of the IO object.

## `#sleep(seconds)`
Sleeps for `seconds`
- Args
  + `seconds`: Number of seconds to sleep (can be a fraction)

## `#spawn(*command)`
Starts a new process and returns the PID.
Does not wait for the process to end.
- Args
  + `command`. One of:
     - commandline : command line string which is passed to the standard shell
     - cmdname, arg1, ... : command name and one or more arguments (no shell)

## `#system(*command)`
Runs a process, waits for it to finish, and returns the exit code.
- Args
  + `command`. One of:
     - commandline : command line string which is passed to the standard shell
     - cmdname, arg1, ... : command name and one or more arguments (no shell)

