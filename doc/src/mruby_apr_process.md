# Class APR::Process

## `::new()`
Creates a new Process object.
To execute the process, configure this object (as needed) and run `APR::Process#exec`

Notes:

- Sets default cmdtype == `:APR_SHELLCMD_ENV `

## `::wait(pid)`
Blocks until the process finishes <br/>
Returns the exit code

## `#cmdtype_set(cmdtype)`
- Args
  + cmdtype: One of
    - `:APR_SHELLCMD`
    - `:APR_PROGRAM`
    - `:APR_PROGRAM_ENV`
    - `:APR_PROGRAM_PATH`
    - `:APR_SHELLCMD_ENV`

## `#io_set(in, out, err)`
- Args
  + `in`, `out`, and `err`: Each are one of
    - `:APR_NO_PIPE`: The child inherits the parent's corresponding stdio stream
    - `:APR_FULL_BLOCK`: Connect a pipe to the child process
- Notes
  + After the process is started, an IO object for any pipes
    set to `:APR_FULL_BLOCK` can be retrieved by the `Process#in`,
    `Process#out`, or `Process#err` accessors

## `#in`
- Grab the IO object for the standard err of the process
- Will return nil unless in was set to `:APR_FULL_BLOCK`
  in a prior call to `#io_set`

## `#out`
- Grab the IO object for the standard out of the process
- Will return nil unless out was set to `:APR_FULL_BLOCK`
  in a prior call to `#io_set`

## `#err`
- Grab the IO object for the standard err of the process
- Will return nil unless err was set to `:APR_FULL_BLOCK`
  in a prior call to `#io_set`

## `#exec(argv)`
- Args
  + argv: An array of strings. `argv[0]` should be the process name.
- Returns
  + `self`

## `#pid()`
Returns the pid of the process

## `#wait()`
Blocks until the process finishes <br/>
Returns `self`

