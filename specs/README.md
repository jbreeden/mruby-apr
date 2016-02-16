
APR API: Directories
--------------------

- APR.dir_open(path: String, pool: Pool): [errno: Fixnum, dir: Dir]
  + Gets file information for each entry in the directory

- APR.dir_read(finfo: Finfo, wanted: Fixnum, dir: Dir): errno: Fixnum
  + Gets file information for each entry in the directory

- APR.dir_make(path: String, permissions: Fixnum, pool: Pool): errno: Fixnum
  + Creates a directory

- APR.dir_make_recursive(path: String, permissions: Fixnum, pool: Poolype): errno: Fixnum
  + Creates a directory and any required parent directories

- APR.dir_remove(path: String, pool: Poolype): errno: Fixnum
  + Deletes a directory


SUCCESS [0 failed, 0 skipped, 5 total]

APR API: File IO
----------------

- APR.file_open(name: String, mode: Fixnum, permissions: Fixnum, pool: Pool): [errno: Fixnum, file: File]
  + Can open a file for writing
  + Can open a file for reading

- APR.file_puts(buf: String, file: File)
  + Can write to an open, writable, file

- APR.file_gets(at_most_n_bytes: Fixnum, file: File): [errno: Fixnum, str: String]
  + Reads length (1st param) characters and returns the string
  + Reads as many characters as possible when length is beyond EOF

- APR.file_write(file: File, buffer: String, num_bytes: Fixnum): [errno: Fixnum, bytes_written: Fixnum]
  + Can write strings with nulls to a file

- APR.file_read(file: File, Fixnum: num_bytes): [errno: Fixnum, str: String]
  + Can read strings with nulls from a file
  + Returns EOF on first attempt to read past EOF

- APR.file_close(file: File): errno: Fixnum
  + Closes an File

- APR.file_seek(thefile: File, where: Fixnum, offset: Fixnum): [errno: Fixnum, resulting_offset: Fixnum]
  + Can seek back from the end of the file

- APR.file_copy(from_path: String, to_path: String, perms: int, pool: Poolype): errno: Fixnum
  + Copies files by name

- APR.file_rename(from_path: String, to_path: String, pool: Poolype): errno: Fixnum
  + Renames a file

- APR.file_remove(from_path: String, to_path: String, perms: int, pool: Poolype): errno: Fixnum
  + Removes a file

- APR.file_lock(file: File, lock_type: Fixnum): errno: Fixnum
  + Locks a file (either flock or iocntl based, depending on platform)

- APR.file_unlock(file: File): errno: Fixnum
  + Unlocks a file (either flock or iocntl based, depending on platform)

- APR.file_attrs_set(fname: String, attrs: Fixnum, attr_mask: Fixnum, pool: Pool): errno: Fixnum
  + Sets attributes on a file

- APR.file_info_get(wanted: Fixnum, file: File)
  + Gets the finfo (fstat - like structure) for an open file

- APR.stat(file_name: String, wanted: Fixnum, pool: Pool)
  + Gets the finfo (fstat - like structure) for a file by name


SUCCESS [0 failed, 0 skipped, 18 total]

APR API: Processes
------------------

- APR.proc_create(command: String, argv: Array<String>, env: Array<String>, proc_attr: Procattr, pool: Pool): [errno: Fixnum, proc: Proc]
  + Can run a shell command and redirect output to a file
  + Can run a shell command and pipe output to parent via APR.file_pipe_create

- APR.procattr_io_set(procattr: Procattr, in: Fixnum, out: Fixnum, err: Fixnum): errno: Fixnum
  + Can automatically create pipes between the parent and child processes (for std in, out, & err)


SUCCESS [0 failed, 0 skipped, 3 total]

APR API: Sockets
----------------

- APR.socket_connect(socket: Socket, addr: Sockaddr)
  + Connects a client socket to a server

- APR.socket_atreadeof(socket: Socket)
  + Returns [APR::APR_SUCCESS, true] when the read buffer is empty and the socket has been closed by the peer

- APR.socket_send(socket, message, length)
  + Returns a APR::APR_EOF when the connection is closed

- APR.socket_bind(socket, addr)
  + Binds a server socket to an address


SUCCESS [0 failed, 0 skipped, 4 total]

APR API: Time
-------------

- APR.time_now(pool: Pool): time: Time
  + Gets the current time


SUCCESS [0 failed, 0 skipped, 1 total]

Ruby API: Dir
-------------

- Dir
  + [SKIPPED] Is implemented, but needs tests


SUCCESS [0 failed, 1 skipped, 1 total]

Ruby API: File
--------------

- File::open(filename, mode="r" [, &block])
  + Returns an open File object, if filename exists
  + Raises a SystemCallError if filename does not exist
  + If given a block, it is passed the File, and the File is automatically closed when the block terminates

- File::absolute_path
  + [SKIPPED] Is implemented

- File::atime
  + Returns the access time of the file

- File::basename
  + [SKIPPED] Is implemented

- File::copy_stream
  + [SKIPPED] Is implemented

- File::ctime
  + Returns the creation time of the file

- File::delete(path[, path]...)
  + Deletes the file named by the path argument
  + Accepts multiple path parameters and deletes them all
  + Raises a system call error if the file does not exist

- File::directory?
  + Returns true if the given path is a directory

- File::dirname
  + [SKIPPED] Is implemented

- File::exist? | exists?
  + Returns true if the file exists
  + Returns true if the file exists, even if it's a directory
  + Returns false if the file does not exist

- File::expand_path
  + [SKIPPED] Is implemented

- File::extname
  + Returns the extension name of the given path, including the dot

- File::file?
  + Returns true if the given path is a normal file

- File::fnmatch
  + [SKIPPED] Is implemented

- File::fnmatch?
  + [SKIPPED] Is implemented

- File::link
  + [SKIPPED] Is implemented

- File::lstat
  + [SKIPPED] Is implemented

- File::mtime
  + [SKIPPED] Is implemented

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


SUCCESS [0 failed, 10 skipped, 68 total]

Ruby API: File::Stat
--------------------

- Stat#atime
  + Gives the access time of the file as a Time

- Stat#ctime
  + Gives the creation time of the file as a Time

- Stat#mtime
  + Gives the last modified time of the file as a Time

- Stat#size
  + Gives the size of the file in bytes

- Stat#directory?
  + Returns true if the file is a directory
  + Returns false for non-directory files

- Stat#file?
  + Returns true if the file is a regular file
  + Returns false for non-regular files


SUCCESS [0 failed, 0 skipped, 8 total]

Ruby API: Forwardable
---------------------

- Forwardable#delegate
  + Creates delegate methods on classes
  + Creates delegate methods on instances
  + Passes arguments along
  + Passes blocks along


SUCCESS [0 failed, 0 skipped, 4 total]

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
  + Yeilds the IO like object instead of returning it if a block is provided
  + Closes the IO object after yielding to a block
  + [SKIPPED] Handles \r\n & \n line endings in text mode

- IO.pipe
  + [SKIPPED] Both pipes are closed & freed after each is garbage collected


SUCCESS [0 failed, 2 skipped, 10 total]

Ruby API: Kernel
----------------

- Kernel::` (backquote)
  + Runs a command and returns it's standard output
  + Sets $? based on the exit status of the child process


SUCCESS [0 failed, 0 skipped, 2 total]

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
  + [SKIPPED] If called twice on the same PID, does the right thing... which is...?


SUCCESS [0 failed, 1 skipped, 7 total]

Ruby API: TCPSocket, & TCPServer
--------------------------------

- TCPSocket::new(remote_host, remote_port, local_host=nil, local_port=nil)
  + Creates a connected TCP socket when given remote host & port

- TCPSocket#write(str)
  + [SKIPPED] Writes the given str to the socket

- TCPSocket#read(len=nil)
  + [SKIPPED] Reads from the socket until EOF (when the socket is closed)
  + Reads at most len bytes if len is provided
  + Returns the empty string after EOF has been encountered, if length is not provided
  + Returns nil after EOF has been encountered, if length is provided

- TCPSocket#recv(maxlen)
  + Reads at most maxlen bytes

- TCPSocket#close_read
  + Closes a socket for reading

- TCPSocket#close_write
  + Closes a socket for writing

- TCPSocket#close
  + Closes a socket for reading & writing

- TCPSocket#eof?
  + Returns true if the socket has been closed by the peer

- TCPSocket#gets
  + Read from the socket one line at a time

- TCPServer::new([hostname], port)
  + Creates a new TCPServer on the given port


SUCCESS [0 failed, 2 skipped, 13 total]

Ruby API: UDPSocket
-------------------

- UDPSocket::read(length=nil)
  + Reads at most length bytes from a bound UDPSocket
  + Reads consecutive packets as a stream

- UDPSocket::recv(maxlen)
  + Reads at most maxlen bytes from a bound UDPSocket

- UDPSocket::recvfrom(maxlen)
  + Reads from a bound UDPSocket, returning the sender's address

- UDPSocket::write(str)
  + Writes the given string to a connected UDPSocket


SUCCESS [0 failed, 0 skipped, 5 total]
