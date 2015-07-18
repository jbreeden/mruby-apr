
APR API: Directories
--------------------

  - APR::apr_dir_open(path: String, pool: AprPoolType): [errno: Fixnum, dir: AprDirT]
    + Gets file information for each entry in the directory

  - APR::apr_dir_read(finfo: AprFinfoT, wanted: Fixnum, dir: AprDirT): errno: Fixnum
    + Gets file information for each entry in the directory

  - APR::apr_dir_make(path: String, permissions: Fixnum, pool: AprPoolType): errno: Fixnum
    + Creates a directory

  - APR::apr_dir_make_recursive(path: String, permissions: Fixnum, pool: AprPoolType): errno: Fixnum
    + Creates a directory and any required parent directories

  - APR::apr_dir_remove(path: String, pool: AprPoolType): errno: Fixnum
    + Deletes a directory

  SUCCESS [0/5 tests failed]

APR API: File IO
----------------

  - APR::apr_file_open(name: String, mode: Fixnum, permissions: Fixnum, pool: AprPoolT): [errno: Fixnum, file: AprFileT]
    + Can open a file for writing
    + Can open a file for reading

  - APR::apr_file_puts(buf: String, file: AprFileT)
    + Can write to an open, writable, file

  - APR::apr_file_gets(at_most_n_bytes: Fixnum, file: AprFileT): [errno: Fixnum, str: String]
    + Reads length (1st param) characters and returns the string
    + Reads as many characters as possible when length is beyond EOF

  - APR::apr_file_write(file: AprFileT, buffer: String, num_bytes: Fixnum): [errno: Fixnum, bytes_written: Fixnum]
    + Can write strings with nulls to a file

  - APR::apr_file_read(file: AprFileT, Fixnum: num_bytes): [errno: Fixnum, str: String]
    + Can read strings with nulls from a file
    + Returns EOF on first attempt to read past EOF

  - APR::apr_file_close(file: AprFileT): errno: Fixnum
    + Closes an AprFileT

  - APR::apr_file_seek(thefile: AprFileT, where: Fixnum, offset: Fixnum): [errno: Fixnum, resulting_offset: Fixnum]
    + Can seek back from the end of the file

  - APR::apr_file_copy(from_path: String, to_path: String, perms: int, pool: AprPoolType): errno: Fixnum
    + Copies files by name

  - APR::apr_file_rename(from_path: String, to_path: String, pool: AprPoolType): errno: Fixnum
    + Renames a file

  - APR::apr_file_remove(from_path: String, to_path: String, perms: int, pool: AprPoolType): errno: Fixnum
    + Removes a file

  - APR::apr_file_lock(file: AprFileT, lock_type: Fixnum): errno: Fixnum
    + Locks a file (either flock or iocntl based, depending on platform)

  - APR::apr_file_unlock(file: AprFileT): errno: Fixnum
    + Unlocks a file (either flock or iocntl based, depending on platform)

  - APR::apr_file_attrs_set(fname: String, attrs: Fixnum, attr_mask: Fixnum, pool: AprPoolT): errno: Fixnum
    + Sets attributes on a file

  - APR::apr_file_info_get(wanted: Fixnum, file: AprFileT)
    + Gets the finfo (fstat - like structure) for an open file

  - APR::apr_stat(file_name: String, wanted: Fixnum, pool: AprPoolT)
    + Gets the finfo (fstat - like structure) for an open file

  SUCCESS [0/18 tests failed]

APR API: Processes
------------------

  - APR::apr_proc_create(command: String, argv: Array<String>, env: Array<String>, proc_attr: AprProcattrT, pool: AprPoolT): [errno: Fixnum, proc: AprProcT]
    + Can run a shell command and redirect output to a file
    + Can run a shell command and pipe output to parent via APR.apr_file_pipe_create

  - APR::apr_procattr_io_set(procattr: AprProcattrT, in: Fixnum, out: Fixnum, err: Fixnum): errno: Fixnum
    + Can automatically create pipes between the parent and child processes (for std in, out, & err)

  SUCCESS [0/3 tests failed]

APR API: Sockets
----------------

  - APR::apr_sockaddr_info_get
    + Creates a socket

  SUCCESS [0/1 tests failed]

APR API: Time
-------------

  - APR::apr_time_now(pool: AprPoolT): time: AprTimeT
    + Gets the current time

  SUCCESS [0/1 tests failed]

Ruby API: File
--------------

  - File::open(filename, mode="r" [, &block])
    + Returns an open File object, if filename exists
    + Raises a SystemCallError if filename does not exist
    + If given a block, it is passed the File, and the File is automatically closed when the block terminates

  - File::absolute_path
    + [PENDING] Is implemented

  - File::atime
    + [PENDING] Is implemented

  - File::basename
    + [PENDING] Is implemented

  - File::copy_stream
    + [PENDING] Is implemented

  - File::ctime
    + [PENDING] Is implemented

  - File::delete(path[, path]...)
    + Deletes the file named by the path argument
    + Accepts multiple path parameters and deletes them all
    + Raises a system call error if the file does not exist

  - File::directory?
    + [PENDING] Is implemented

  - File::dirname
    + [PENDING] Is implemented

  - File::exist? | exists?
    + Returns true if the file exists
    + Returns true if the file exists, even if it's a directory
    + Returns false if the file does not exist

  - File::exists?
    + [PENDING] Is implemented

  - File::expand_path
    + [PENDING] Is implemented

  - File::extname
    + [PENDING] Is implemented

  - File::file?
    + [PENDING] Is implemented

  - File::fnmatch
    + [PENDING] Is implemented

  - File::fnmatch?
    + [PENDING] Is implemented

  - File::link
    + [PENDING] Is implemented

  - File::lstat
    + [PENDING] Is implemented

  - File::mtime
    + [PENDING] Is implemented

  - File#print(obj, ...)
    + Writes the given objects to the File
    + If the output field separator ($,) is nil, nothing is inserted between each object.
    + If the output field separator ($,) is not nil, it will be inserted between each object.
    + If the output record separator ($) is not nil, it will be appended to the output.
    + Objects that aren’t strings will be converted by calling their to_s method

  - File#<<(obj)
    + Writes obj to ios. obj will be converted to a string using to_s.

  - File#puts(obj, ...)
    + Writes the given objects to the File, appending the output record separator ($\) between each item
    + Raises an IOError if the file is not open for writing
    + Appends to the file if opened with mode="a"
    + Does not append a record separator after any args that already end with a record separator sequence
    + If called with any array arguments, flattens the arrays and writes each element on a new line
    + If called without arguments, outputs a single record separator

  - File#gets | gets(sep=$/) | gets(limit) | gets(sep, limit)
    + Reads until sep when called as `gets(sep=$/)` (the separator is included in the result)
    + Returns "" if limit is 0
    + Reads at most `limit` bytes when called as `gets(limit)`
    + Reads at most `limit` bytes when called as `gets(sep, limit)`
    + Raises an IOError if the stream isn't open for reading
    + Returns nil if called at end of file

  - File#read
    + Reads length bytes from the file
    + If length is omitted or is nil, it reads until EOF
    + If length is provided, nil means it met EOF at beginning
    + If length is provided, 1 to length-1 bytes string means it met EOF after reading the result
    + If length is provided, the length bytes string means it doesn’t meet EOF
    + If length is zero, it returns ""
    + At end of file, it returns "" if length omitted or nil
    + Raises an IOError if the file isn't open for reading

  - File#write
    + Writes the given string to the file
    + If the argument is not a string, it will be converted to a string using to_s
    + Returns the number of bytes written
    + Raises an IOError if the file isn't open for writing

  - File#each(&block)
    + Executes the given block for each line in the file, passing in the line
    + Returns an Enumerator if no block is given

  - File#each_line(&block)
    + Is an alias for each

  - File#each_byte(&block)
    + Executes the given block for each character in the file
    + Returns an Enumerator if no block is given

  - File#eof | eof?
    + Returns true if EOF has been hit, or else false
    + Returns true for an empty file, even if no reads have been performed yet

  - File#getbyte
    + Returns the next character, or nil if at EOF

  - File#getc
    + Returns the next character, or nil if at EOF

  - File#ungetbyte
    + Pushes back bytes onto a file buffer 

  - File#ungetc
    + Pushes back bytes onto a file buffer 

  - File#seek(amount, whence=IO::SEEK_SET)
    + Seeks `amount` bytes from the beginning of the file when given `whenc=IO::SEEK_SET` (the default)
    + Seeks `amount` bytes from the end of the file when given `whenc=IO::SEEK_END`
    + Seeks `amount` bytes from the current position of the file when given `whenc=IO::SEEK_CUR`

  SUCCESS [0/69 tests failed]

Ruby API: File
--------------

  - Stat#atime
    + Gives the access time of the file as a Time

  - Stat#ctime
    + Gives the creation time of the file as a Time

  - Stat#mtime
    + Gives the creation time of the file as a Time

  - Stat#size
    + Gives the size of the file in bytes

  - Stat#directory?
    + Returns true if the file is a directory
    + Returns false for non-directory files

  - Stat#file?
    + Returns true if the file is a regular file
    + Returns false for non-regular files

  SUCCESS [0/8 tests failed]

Ruby API: IO
------------

  - IO.pipe
    + Creates a pair of File objects to be used as the read & write ends of the pipe

  - IO.popen([env,] cmd, mode="r" [, opt])
    + Runs the specified command as a subprocess, returning an IO like object with a pid member
    + Connects the returned IO-like object to child's stdin for mode "r"
    + Connects the returned IO-like object to child's stdout for mode "w"
    + Connects the returned IO-like object to child's stdin & stdout for mode "r+"
    + Sends EOF when the output pipe is closed
    + [PENDING] Yeilds the IO like object instead of returning it if a block is provided
    + [PENDING] Handles \r\n & \n line endings in text mode

  - IO.pipe
    + [PENDING] Both pipes are closed & freed after each is garbage collected

  SUCCESS [0/9 tests failed]

Ruby API: Kernel
----------------

  - Kernel::` (backquote)
    + Runs a command and returns it's standard output
    + Sets $? based on the exit status of the child process

  SUCCESS [0/2 tests failed]

Ruby API: Process
-----------------

  - Process::spawn
    + Spawns a shell command if given a string
    + Interprets shell command arguments correctly
    + Spawns a program from the path, with no shell, if given argv as multiple args
    + Supports redirecting in, out, & err streams to/from a Pipe's created by IO.pipe
    + Supports redirecting to ordinary file objects

  - Process::wait
    + Sets $? based on the exit status of the indicated process
    + [PENDING] If called twice on the same PID, does the right thing... which is...?

  SUCCESS [0/7 tests failed]
