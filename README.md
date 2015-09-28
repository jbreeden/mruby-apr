mruby-apr
=========

Bindings to the Apache APR library, providing a portable runtime library for mruby.

Thus far, `mruby-apr` provides access to

- Files (APR & Ruby APIs)
  + Create, delete, read, write, status, lock
- Directories (APR & Ruby APIs)
  + Create, delete, read, write, glob
- Processes (APR & Ruby APIs)
  + Spawning & waiting
- Pipes (APR & Ruby APIs)
  + Create, read, write, share with child processes
- Sockets (APR APIs & Ruby APIs)
  + Client & server
- Time functions (APR APIs)

Additionally, some of the CRuby standard library has been included (with some light patching).

- Forwardable
- Observer
- OpenStruct
- Shellwords

Description
-----------

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

`mruby-apr` is intended for mruby builds targeting the platforms supported by libapr. This includes Windows, Mac, Linux, and other fairly common operating systems. So, while some limited embedded targets may be out of the question, this mrbgem could be
useful when embedding mruby as a scripting language in a desktop or mobile app.

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
