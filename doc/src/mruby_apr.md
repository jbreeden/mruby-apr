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

# module APR::TCP
## `::get_open_port`
Return an open TCP port number

# object ENV
## `#[](name)`
Returns the value of the environemnt variable named `name`

## `#[]=(name, value)`
Sets the value of the environemnt variable named `name` to `value`

## `#delete(name)`
Deletes the environemnt variable named `name`

