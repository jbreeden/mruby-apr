mruby-apr
=========

A cross-platform MRuby port of the core system libraries from CRuby.

Notably, mruby-apr includes

- IO (read, write, pipe, popen)
- File, FileTest, File::Stat
- Dir
- BasicSocket, UDPSocket, TCPSocket, TCPServer
- ENV[], ENV[]=, & ENV.delete
- Kernel ( \`backticks\`, system, spawn, & load)
- Process (spawn & wait)
- Process::Status (including the global $?)
- Forwardable
- Observer
- OpenStruct
- Shellwords

Check [the spec](/spec.md) to see the list of methods supported. (You'll need to scroll down to the sections marked "Ruby API".)

Building
--------

### On Mac and Linux

- Download libapr version 1.5.2 from [Apache's website](https://apr.apache.org/download.cgi)
- `/path/to/apr$ configure && make && sudo make install`
- Download `mruby-apr`
- Add `conf.gem 'path/to/mruby-apr'` to your MRuby `build_config.rb` file.
- `/path/to/mruby$ rake`

### On windows

- Download libapr version 1.5.2 from [Apache's website](https://apr.apache.org/download.cgi)
- Using `cmake`, generate the visual studio project files.
- Open the solution, create a 64-bit build target, and build libapr.
- Download/clone `mruby`
- Download `mruby-apr`
- Add the following lines to your MRuby build_config.rb file.
  + `ENV['APR_HOME'] = "/path/to/your/libapr/build/dir"`
  + `conf.gem '/path/to/mruby-apr'`
- `/path/to/mruby$ rake`

This assumes you're using the visual studio toolchain for compiling MRuby on Windows. It is possible to use nmake for the
build instead of Visual Studio project files, or even to use gcc via MinGW. Whatever your choice, just make sure to
update `mruby-apr`'s mrbgem.rake file to use the correct search paths and compiler options for your build.

Platform Support
----------------

Primary development and testing done on Windows, Mac, Linux, and Raspbian. However, it should work anywhere you can compile [Apache APR](https://apr.apache.org).

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
