mruby-apr
=========

[![Join the chat at https://gitter.im/jbreeden/mruby-apr](https://badges.gitter.im/Join%20Chat.svg)](https://gitter.im/jbreeden/mruby-apr?utm_source=badge&utm_medium=badge&utm_campaign=pr-badge&utm_content=badge)

A cross-platform MRuby port of the core system libraries from CRuby:

- IO (read, write, pipe, popen)
- File, FileTest, File::Stat
- Dir
- BasicSocket, UDPSocket, TCPSocket, TCPServer
- ENV
- Kernel ( \`backticks\`, system, spawn, & load)
- Process (spawn & wait)
- Process::Status (including the global $?)
- Forwardable
- Observer
- OpenStruct
- Pathname
- Shellwords

Specs
-----

[See the ruby/spec results](https://googledrive.com/host/0B0NNQZ6fVYyiZHlPNTk1dDA5YVE)

- [mruby-spec](https://github.com/jbreeden/mruby-spec) is used to run [ruby/spec](https://github.com/ruby/spec)
  against [mruby](https://github.com/mruby/mruby).
  + This is a recent addition. Currently working to get more of the tests passing.
- The original `mruby-apr` specs are [here](./specs).

Building
--------

### Mac and Linux

**1. Setup the dependencies**
- Download libapr version 1.5.2 from [Apache's website](https://apr.apache.org/download.cgi)
- Download `mruby-apr` [here](https://github.com/jbreeden/mruby-apr).
- Add the following lines to your MRuby build_config.rb file.
```Ruby
spec.cc.flags << '-DMRB_INT64'
conf.gem 'path/to/mruby-apr'
```
**2. Make & Rake**
```
cd /path/to/apr
configure && make && sudo make install
cd /path/to/mruby
rake
```

### Windows

**1. Setup the dependencies**
- Download libapr version 1.5.2 from [Apache's website](https://apr.apache.org/download.cgi)
- Download `mruby-apr` [here](https://github.com/jbreeden/mruby-apr).
- Add the following lines to your MRuby build_config.rb file.
```Ruby
spec.cc.flags << '-DMRB_INT64'
ENV['APR_HOME'] = "/path/to/your/libapr/build/dir"
conf.gem '/path/to/mruby-apr'
```
*Notice that on windows, you must set APR_HOME to tell this gem where to find headers & lib files*

**2. CMake & Rake**

APR comes with `cmake` scripts. You can use `cmake` to generate different kinds of project files for building APR.
To name a few, Visual Studio, MinGW, and NMake are supported. Just use the same compiler you're using for MRuby.

Once APR is built

```
cd /path/to/mruby
rake
```

Platform Support
----------------

Primary development and testing done on Windows, Mac, Ubuntu, and Raspbian. However, it should work anywhere you can compile [Apache APR](https://apr.apache.org).

Implementation Details
----------------------

Apache APR provides a cross platform runtime library for C, allowing portable access to system resources
(eg processes, files, sockets, etc.). `mruby-apr` provides bindings to this library to bring these capabilities
to mruby, without having to code the cross-platform logic over again.

These bindings are provided at 2 distinct levels:

1. Direct bindings to libapr are provided in the `APR` module.
  + These bindings provide a nearly identical api to libapr from mruby as is available in C.
  + The main point of difference is that out-parameters in the C API correspond to multiple return values in the mruby API.
2. The direct bindings are used to implement portions of the CRuby standard library, purely in mruby.
  + This provides a familiar and idiomatic API to system resources for ruby programmers.
  + As with the Rubinius implementation, this should make it easier for Ruby programmers to hack on the stdlib.
