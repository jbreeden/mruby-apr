mruby-apr
=========

Bindings to the Apache APR library, providing a portable runtime library for mruby.

`mruby-apr` implements the following components from MRI's standard library

- IO
  + `::popen`, `::pipe`, plus methods like `read`, `write`, `gets`, and `puts`.
  + Instance methods works with files & sockets.
- File, FileTest, File::Stat
  + CRUD operations & `flock`
- Dir
  + `entries`, `chdir`, `mkdir`, `exists?`, `delete`, etc.
- BasicSocket, UDPSocket, TCPSocket, TCPServer
  + Inherit `read`, `write`, etc. from IO.
  + `recv` & `send` family of functions not yet implemented.
- ENV
  + `[]`, `[]=`, & `delete`
- Kernel
  + `` ` ``, `system`, `spawn`, `load`
- Process
  + `spawn`, `wait`
- Process::Status
- Forwardable
- Observer
- OpenStruct
- Shellwords

Building
--------

`mruby-apr` will try to link statically against libapr. You will have to install the libapr binaries, or build
the library yourself.

### On Mac and Linux

`mruby-apr` will expect to find libapr in the default `make install` target directory (/usr/local/apr).
If found, it will use the `apr-1-config` tool to set compiler and linker search paths. The process would look something
like this:

- Download libapr version 1.5.2 from [Apache's website](https://apr.apache.org/download.cgi)
- `configure`, `make`, && `sudo make install`
- Download/clone `mruby`
- Download/clone `mruby-apr`, and add `conf.gem 'PATH/TO/mruby-apr'` to your MRuby build_config.rb file.
  + Alternatively, you can skip downloading `mruby-apr` manually and use `conf.gem :github => 'jbreeden/mruby-apr'`,
    the MRuby build system will take care of cloning `mruby-apr` for you at build time.
- Run `rake` in the root director of MRuby.

### On windows

The environment variable `APR_HOME` should be set to the directory where libapr was built. There are various
ways to build libapr on Windows. The approach used to test `mruby-apr` on Windows is as follows:

- Download libapr version 1.5.2 from [Apache's website](https://apr.apache.org/download.cgi)
- Using `cmake`, generate the visual studio project files.
- Open the solution, create a 64-bit build target, and build libapr.
- Download/clone `mruby`
- In MRuby's build_config.rb file, set `ENV['APR_HOME'] = "PATH/TO/LIBAPR/BUILD/DIR"`
  + Make sure this appears before the `conf.gem ...` declaration for `mruby-apr`
- Download/clone `mruby-apr`, and add `conf.gem 'PATH/TO/mruby-apr'` to your MRuby build_config.rb file.
  + Alternatively, you can skip downloading `mruby-apr` manually and use `conf.gem :github => 'jbreeden/mruby-apr'`,
    the MRuby build system will take care of cloning `mruby-apr` for you at build time.
- Run `rake` in the root director of MRuby.

This assumes you're using the visual studio toolchain for compiling MRuby on Windows. It is possible to use nmake for the
build instead of Visual Studio project files, or even to use gcc via MinGW. Whatever your choice, just make sure to
update `mruby-apr`'s mrbgem.rake file to use the correct search paths and compiler options for your build.

Overview
--------

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

Platform Support
----------------

`mruby-apr` is intended for mruby builds targeting the platforms supported by libapr. This includes Windows, Mac, Linux, and other fairly common operating systems. So, while some limited embedded targets may be out of the question, this mrbgem could be useful when embedding mruby as a scripting language in a desktop or mobile app. It does work on the Raspberry Pi, which pairs well with mruby given its small footprint.

Spec
----

[The spec](/spec.md) is generated from the tests and covers most of the API. It should serve as a decent (if not verbose) reference.

APR Function Bindings
---------------------

For a complete list of APR functions for which bindings have been created, see [apr_functions.txt](/apr_functions.txt)

Development Guidelines
----------------------

### Testing
+ APR API Wrappers
  * Nothing special, just writing unit tests
+ Ruby API Implementations
  * Each test file should run from the command line in the specs/ directory
  * The test file should run on MRI & MRuby (`ruby ./ruby_file.rb` & `mruby ./ruby_file.rb`)
    + This is not the case for all existing files ATM, but they should be updated as they are touched
    + Just need to check for the existence of "MRUBY_VERSION" constant & add requires if on MRI
  * Running from the rake tasks runs MRuby tests only
    + MRuby will need to be on your path
    + Any new tests should be run on MRI as well to verify the behavior being tested is correct.

### Using APR Pools for Resource Management
+ An APR pool created by MRuby is "owned" by MRuby.
  * That is, the pool will be destroyed when the reference to it is GC'ed by MRuby.
+ APR registers cleanup functions for the system resources it provides.
  * So, for example, apr_file_t objects are closed when the APR pool they belong to is destroyed.
+ The above has several implications.
  * Any MRuby object (such as a File) that contains resources allocated by a pool MUST
    retain a reference to that pool.
  * Once all objects in a pool are GC'ed, there will no longer be a reference to the pool.
    Therefore, the pool will be destroyed, which will clean up all allocated resources.

_Note: When building with mruby-apr, you may need to add `-fexceptions` to your `conf.cc.flags` and `conf.cxx.flags` in your mruby build_config.rb file. If you see errors like "Terminate called after throwing instance of 'int'," this is likely the issue._
