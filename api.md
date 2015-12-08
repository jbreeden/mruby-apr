MRuby-APR
=========

BasicSocket
-----------

  - `#assert_can_read`
  - `#assert_can_write`
  - `#close`
  - `#close_read`
  - `#close_write`
  - `#eof?`
  - `#initialize`
  - `#read`
  - `#recv`
  - `#send`
  - `#shutdown`
  - `#write`

Dir
---

  - `::[]`
  - `::chdir`
  - `::delete`
  - `::entries`
  - `::exist?`
  - `::exists?`
  - `::foreach`
  - `::getcwd`
  - `::glob`
  - `::mkdir`
  - `::mktmpdir`
  - `::pwd`
  - `::rmdir`
  - `::tmpdir`
  - `::unlink`

File
----

  - `::atime`
  - `::ctime`
  - `::delete`
  - `::extname`
  - `::open`
  - `::read`
  - `#assert_can_read`
  - `#assert_can_write`
  - `#close`
  - `#closed?`
  - `#eof`
  - `#eof?`
  - `#flock`
  - `#flush`
  - `#getbyte`
  - `#getc`
  - `#initialize`
  - `#native_file`
  - `#read`
  - `#seek`
  - `#ungetbyte`
  - `#ungetc`
  - `#write`

File::Stat
----------

  - `#<=>`
  - `#atime`
  - `#blockdev?`
  - `#chardev?`
  - `#ctime`
  - `#directory?`
  - `#file?`
  - `#ftype`
  - `#initialize`
  - `#mtime`
  - `#name`
  - `#nlink`
  - `#pipe?`
  - `#size`
  - `#size?`
  - `#socket?`
  - `#symlink?`
  - `#zero?`

FileTest
--------

  - `::is_type?`
  - `#blockdev?`
  - `#chardev?`
  - `#directory?`
  - `#exist?`
  - `#exists?`
  - `#file?`
  - `#pipe?`
  - `#size`
  - `#size?`
  - `#socket?`
  - `#symlink?`
  - `#zero?`

Forwardable
-----------

  - `::debug`
  - `::debug=`
  - `#def_delegator`
  - `#def_delegators`
  - `#def_instance_delegator`
  - `#def_instance_delegators`
  - `#delegate`
  - `#instance_delegate`

IO
--

  - `::pipe`
  - `::popen`
  - `#<<`
  - `#each`
  - `#each_byte`
  - `#each_char`
  - `#each_line`
  - `#eof`
  - `#getbyte`
  - `#getc`
  - `#gets`
  - `#print`
  - `#puts`
  - `#seek`

IPSocket
--------

  - `#recvfrom`

Kernel
------

  - `#``
  - `#load`
  - `#spawn`
  - `#system`

Observable
----------

  - `#add_observer`
  - `#changed`
  - `#changed?`
  - `#count_observers`
  - `#delete_observer`
  - `#delete_observers`
  - `#notify_observers`

OpenStruct
----------

  - `#==`
  - `#[]`
  - `#[]=`
  - `#delete_field`
  - `#each_pair`
  - `#eql?`
  - `#hash`
  - `#initialize`
  - `#initialize_copy`
  - `#inspect`
  - `#marshal_dump`
  - `#marshal_load`
  - `#method_missing`
  - `#modifiable`
  - `#new_ostruct_member`
  - `#table`
  - `#to_h`
  - `#to_s`

Shellwords
----------

  - `::escape`
  - `::join`
  - `::shellescape`
  - `::shelljoin`
  - `::shellsplit`
  - `::shellwords`
  - `::split`
  - `#shellescape`
  - `#shelljoin`
  - `#shellsplit`
  - `#shellwords`

IO::Pipe
--------

  - `#initialize`

Process
-------

  - `::pid`
  - `::spawn`
  - `::wait`

Socket
------


Process::Status
---------------

  - `#coredump?`
  - `#exited?`
  - `#exitstatus`
  - `#initialize`
  - `#pid`
  - `#signaled?`
  - `#success?`

TCPServer
---------

  - `#accept`
  - `#initialize`
  - `#listen`

TCPSocket
---------

  - `#initialize`

UDPSocket
---------

  - `#bind`
  - `#connect`
  - `#initialize`
  - `#read`

