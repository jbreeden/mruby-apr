MRuby-APR
=========

---

BasicSocket
-----------

Ancestors: `IO`

Instance Methods:
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

---

Dir
---

Class Methods:
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


---

File
----

Ancestors: `IO`

Class Methods:
  - `::atime`
  - `::ctime`
  - `::delete`
  - `::extname`
  - `::open`
  - `::read`

Instance Methods:
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

---

File::Stat
----------

Instance Methods:
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

---

FileTest
--------

Class Methods:
  - `::is_type?`

Instance Methods:
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

---

Forwardable
-----------

Class Methods:
  - `::debug`
  - `::debug=`

Instance Methods:
  - `#def_delegator`
  - `#def_delegators`
  - `#def_instance_delegator`
  - `#def_instance_delegators`
  - `#delegate`
  - `#instance_delegate`

---

IO
--

Class Methods:
  - `::pipe`
  - `::popen`

Instance Methods:
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

---

IPSocket
--------

Ancestors: `BasicSocket`, `IO`

Instance Methods:
  - `#recvfrom`

---

Kernel
------

Instance Methods:
  - \` (Backtick)
  - `#load`
  - `#spawn`
  - `#system`

---

Observable
----------

Instance Methods:
  - `#add_observer`
  - `#changed`
  - `#changed?`
  - `#count_observers`
  - `#delete_observer`
  - `#delete_observers`
  - `#notify_observers`

---

OpenStruct
----------

Instance Methods:
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

---

Shellwords
----------

Class Methods:
  - `::escape`
  - `::join`
  - `::shellescape`
  - `::shelljoin`
  - `::shellsplit`
  - `::shellwords`
  - `::split`

Instance Methods:
  - `#shellescape`
  - `#shelljoin`
  - `#shellsplit`
  - `#shellwords`

---

IO::Pipe
--------

Ancestors: `File`, `IO`

Instance Methods:
  - `#initialize`

---

Process
-------

Class Methods:
  - `::pid`
  - `::spawn`
  - `::wait`


---

Socket
------


---

Process::Status
---------------

Instance Methods:
  - `#coredump?`
  - `#exited?`
  - `#exitstatus`
  - `#initialize`
  - `#pid`
  - `#signaled?`
  - `#success?`

---

TCPServer
---------

Ancestors: `TCPSocket`, `IPSocket`, `BasicSocket`, `IO`

Instance Methods:
  - `#accept`
  - `#initialize`
  - `#listen`

---

TCPSocket
---------

Ancestors: `IPSocket`, `BasicSocket`, `IO`

Instance Methods:
  - `#initialize`

---

UDPSocket
---------

Ancestors: `IPSocket`, `BasicSocket`, `IO`

Instance Methods:
  - `#bind`
  - `#connect`
  - `#initialize`
  - `#read`
