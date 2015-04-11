#include <memory>
#include "mruby.h"
#include "mruby/data.h"
#include "mruby/string.h"
#include "mruby/variable.h"
#include "mruby_apr.h"
#include "apr.h"
#include "apr_poll.h"
#include "apr_portable.h"
#include "apr_thread_proc.h"

#if defined(_WIN32) || defined(_WIN64)
   // Need OpenProcess function.
   // This is in WinBase.h before Window 8, then Processthreadsapi.h there after.
   #include "WinBase.h"
   #include "Processthreadsapi.h"

   // Need this to convert HANDLES to file descriptors
   #include "io.h"
#endif

using namespace std;

struct AprProc {
   apr_proc_t proc;
   apr_procattr_t* proc_attr;
   apr_pool_t* pool;

   AprProc() {
      apr_pool_create(&pool, NULL);
      apr_procattr_create(&proc_attr, pool);
      proc.in = NULL;
      proc.out = NULL;
      proc.err = NULL;
   }
};

static
void free_apr_proc(mrb_state* mrb, void* ptr) {
   AprProc* mpr_proc = (AprProc*)ptr;
   apr_pool_destroy(mpr_proc->pool);
   free(mpr_proc);
}

static
mrb_data_type apr_proc_data_type = {
   "APRProc", free_apr_proc
};

static
unique_ptr<char*[]>
to_apr_proc_argv(mrb_state* mrb, mrb_int argc, mrb_value* argv) {
   auto c_argv = unique_ptr<char*[]>(new char*[argc + 1]);
   for (int i = 0; i < argc; ++i) {
      char* arg;
      if (mrb_obj_class(mrb, argv[i]) != mrb->string_class) {
         arg = mrb_str_to_cstr(mrb, mrb_funcall(mrb, argv[i], "to_s", 0));
      }
      else {
         arg = mrb_str_to_cstr(mrb, argv[i]);
      }
      c_argv[i] = arg;
   }
   c_argv[argc] = NULL;
   return c_argv;
}

//<
// # Class APR::Process
//>

//<
// ## `::new()`
// Creates a new Process object.
// To execute the process, configure this object (as needed) and run `APR::Process#exec`
//
// Notes:
//>
mrb_value
mrb_apr_proc_init(mrb_state* mrb, mrb_value self) {
   auto data = new AprProc;

   //<
   // - Sets default cmdtype == `:APR_SHELLCMD_ENV `
   //>
   apr_procattr_cmdtype_set(data->proc_attr, APR_SHELLCMD_ENV);

   // Proc has not been executed yet
   mrb_iv_set(mrb, self, mrb_intern_cstr(mrb, "execed"), mrb_false_value());

   auto wrapped = mrb_data_object_alloc(mrb, mrb->object_class, data, &apr_proc_data_type);
   mrb_iv_set(mrb, self, mrb_intern_cstr(mrb, "data"), mrb_obj_value(wrapped));
   return self;
}

//<
// ## `::wait(pid)`
// Blocks until the process finishes <br/>
// Returns the exit code
//>
mrb_value
mrb_apr_proc_wait_pid(mrb_state* mrb, mrb_value self) {
   mrb_int pid;
   mrb_get_args(mrb, "i", &pid);

   apr_proc_t proc;
   // TODO: untested, but on unix you should only need the file descriptor
   proc.pid = pid;
#if defined(_WIN32) || defined(_WIN64)
   proc.hproc = OpenProcess(SYNCHRONIZE, false, pid);
#endif

   int exit_status = 0;
   apr_exit_why_e why;
   apr_proc_wait(&proc, &exit_status, &why, apr_wait_how_e::APR_WAIT);

   mrb_value rb_exit_status;
   SET_INT_VALUE(rb_exit_status, exit_status);
   return rb_exit_status;
}

//<
// ## `#cmdtype_set(cmdtype)`
// - Args
//   + cmdtype: One of
//     - `:APR_SHELLCMD`
//     - `:APR_PROGRAM`
//     - `:APR_PROGRAM_ENV`
//     - `:APR_PROGRAM_PATH`
//     - `:APR_SHELLCMD_ENV`
//>
mrb_value
mrb_apr_proc_cmdtype_set(mrb_state* mrb, mrb_value self) {
   GUARD_ALREADY_EXECED("Cannot change process cmdtyp after it has been started");

   mrb_sym cmdtype;
   mrb_get_args(mrb, "n", &cmdtype);

   AprProc* data = GET_APR_PROC_DATA(self);

   if (SYM_CHECK(cmdtype, APR_SHELLCMD)) {
      apr_procattr_cmdtype_set(data->proc_attr, APR_SHELLCMD);
   }
   else if (SYM_CHECK(cmdtype, APR_PROGRAM)) {
      apr_procattr_cmdtype_set(data->proc_attr, APR_PROGRAM);
   }
   else if (SYM_CHECK(cmdtype, APR_PROGRAM_ENV)) {
      apr_procattr_cmdtype_set(data->proc_attr, APR_PROGRAM_ENV);
   }
   else if (SYM_CHECK(cmdtype, APR_PROGRAM_PATH)) {
      apr_procattr_cmdtype_set(data->proc_attr, APR_PROGRAM_PATH);
   }
   else if (SYM_CHECK(cmdtype, APR_SHELLCMD_ENV)) {
      apr_procattr_cmdtype_set(data->proc_attr, APR_SHELLCMD_ENV);
   }
   else {
      mrb_raise(mrb, mrb->eStandardError_class, "Invalid cmdtype");
      return mrb_nil_value();
   }

   return mrb_symbol_value(cmdtype);
}

//<
// ## `#io_set(in, out, err)`
// - Args
//   + `in`, `out`, and `err`: Each are one of
//     - `:APR_NO_PIPE`: The child inherits the parent's corresponding stdio stream
//     - `:APR_FULL_BLOCK`: Connect a pipe to the child process
// - Notes
//   + After the process is started, an IO object for any pipes
//     set to `:APR_FULL_BLOCK` can be retrieved by the `Process#in`,
//     `Process#out`, or `Process#err` accessors
//>
mrb_value
mrb_apr_proc_io_set(mrb_state* mrb, mrb_value self) {
   GUARD_ALREADY_EXECED("Cannot configure IO of a process after it has been started");

   mrb_sym in;
   mrb_sym out;
   mrb_sym err;

   mrb_get_args(mrb, "nnn", &in, &out, &err);

   apr_int32_t c_in;
   apr_int32_t c_out;
   apr_int32_t c_err;

   SYM_TO_IO_FLAG(in, c_in);
   SYM_TO_IO_FLAG(out, c_out);
   SYM_TO_IO_FLAG(err, c_err);

   if (c_in == APR_FULL_BLOCK) {
      mrb_iv_set(mrb, self, mrb_intern_cstr(mrb, "in_open"), mrb_true_value());
   }
   if (c_out == APR_FULL_BLOCK) {
      mrb_iv_set(mrb, self, mrb_intern_cstr(mrb, "out_open"), mrb_true_value());
   }
   if (c_err == APR_FULL_BLOCK) {
      mrb_iv_set(mrb, self, mrb_intern_cstr(mrb, "err_open"), mrb_true_value());
   }

   AprProc* data = GET_APR_PROC_DATA(self);
   apr_procattr_io_set(data->proc_attr, c_in, c_out, c_err);
   return self;
}

mrb_value
mrb_apr_proc_get_stream(mrb_state* mrb, mrb_value self, apr_file_t* file, char* iv_name, char* mode) {
   GUARD_NO_EXEC("Cannot get the out file until a process has started");

   auto out_sym = mrb_intern_cstr(mrb, iv_name);
   auto out = mrb_iv_get(mrb, self, out_sym);
   if (mrb_test(out)) {
      return out;
   }

   if (NULL == file) {
      return mrb_nil_value();
   }

   RClass* io_class = mrb_class_get(mrb, "IO");

   apr_os_file_t os_file;
   apr_os_file_get(&os_file, file);

#if defined(_WIN32) || defined (_WIN64)
   int fd;
   int mode_int;

   if (0 == strcmp("r", mode)) {
      mode_int = _O_RDONLY;
   }
   else {
      mode_int = _O_WRONLY;
   }

   fd = _open_osfhandle((long)os_file, mode_int);
   if (fd == -1) {
      return mrb_nil_value();
   }
#else
   // Just a guess so far, haven't tested on linux
   int fd = os_file;
#endif

   mrb_value argv[2];
   SET_INT_VALUE(argv[0], fd);
   argv[1] = mrb_str_new_cstr(mrb, mode);
   out = mrb_obj_new(mrb, io_class, 2, argv);
   mrb_iv_set(mrb, self, out_sym, out);
   return out;
}

//<
// ## `#in`
// - Grab the IO object for the standard err of the process
// - Will return nil unless in was set to `:APR_FULL_BLOCK`
//   in a prior call to `#io_set`
//>
mrb_value
mrb_apr_proc_in(mrb_state* mrb, mrb_value self) {
   if (!mrb_test(mrb_iv_get(mrb, self, mrb_intern_cstr(mrb, "in_open")))) {
      return mrb_nil_value();
   }
   AprProc* data = GET_APR_PROC_DATA(self);
   return mrb_apr_proc_get_stream(mrb, self, data->proc.in, "in", "w");
}

//<
// ## `#out`
// - Grab the IO object for the standard out of the process
// - Will return nil unless out was set to `:APR_FULL_BLOCK`
//   in a prior call to `#io_set`
//>
mrb_value
mrb_apr_proc_out(mrb_state* mrb, mrb_value self) {
   if (!mrb_test(mrb_iv_get(mrb, self, mrb_intern_cstr(mrb, "out_open")))) {
      return mrb_nil_value();
   }
   AprProc* data = GET_APR_PROC_DATA(self);
   return mrb_apr_proc_get_stream(mrb, self, data->proc.out, "out", "r");
}

//<
// ## `#err`
// - Grab the IO object for the standard err of the process
// - Will return nil unless err was set to `:APR_FULL_BLOCK`
//   in a prior call to `#io_set`
//>
mrb_value
mrb_apr_proc_err(mrb_state* mrb, mrb_value self) {
   if (!mrb_test(mrb_iv_get(mrb, self, mrb_intern_cstr(mrb, "err_open")))) {
      return mrb_nil_value();
   }
   AprProc* data = GET_APR_PROC_DATA(self);
   return mrb_apr_proc_get_stream(mrb, self, data->proc.err, "err", "r");
}

//<
// ## `#exec(argv)`
// - Args
//   + argv: An array of strings. `argv[0]` should be the process name.
// - Returns
//   + `self`
//>
mrb_value
mrb_apr_proc_exec(mrb_state* mrb, mrb_value self) {
   GUARD_ALREADY_EXECED("Cannot exec a process twice");

   mrb_value *argv;
   mrb_int argc;

   mrb_get_args(mrb, "a", &argv, &argc);
   auto c_argv = to_apr_proc_argv(mrb, argc, argv);

   mrb_iv_set(mrb, self, mrb_intern_cstr(mrb, "execed"), mrb_true_value());

   AprProc* data = GET_APR_PROC_DATA(self);

   apr_status_t launch_status =
      apr_proc_create(&data->proc, c_argv[0], c_argv.get(), NULL, data->proc_attr, data->pool);

   GUARD_APR_ERRNO(launch_status, c_argv[0]);

   return self;
}

//<
// ## `#pid()`
// Returns the pid of the process
//>
mrb_value
mrb_apr_proc_pid(mrb_state* mrb, mrb_value self) {
   GUARD_NO_EXEC("Cannot get PID of a process that has not been started");
   AprProc* data = GET_APR_PROC_DATA(self);
   mrb_value pid;
   SET_INT_VALUE(pid, data->proc.pid);
   return pid;
}

//<
// ## `#wait()`
// Blocks until the process finishes <br/>
// Returns `self`
//>
mrb_value
mrb_apr_proc_wait(mrb_state* mrb, mrb_value self) {
   GUARD_NO_EXEC("Cannot wait on a process that has not been started")

      AprProc* data = GET_APR_PROC_DATA(self);

   int exit_status = 0;
   apr_exit_why_e why;
   apr_proc_wait(&data->proc, &exit_status, &why, apr_wait_how_e::APR_WAIT);

   mrb_value rb_exit_status;
   SET_INT_VALUE(rb_exit_status, exit_status);
   return rb_exit_status;
}

void mrb_mruby_apr_process_init(mrb_state* mrb, RClass* apr_module) {
   auto apr_process_class = mrb_define_class_under(mrb, apr_module, "Process", mrb->object_class);
   mrb_define_method(mrb, apr_process_class, "initialize", mrb_apr_proc_init, MRB_ARGS_NONE());
   mrb_define_method(mrb, apr_process_class, "cmdtype_set", mrb_apr_proc_cmdtype_set, MRB_ARGS_REQ(1));
   mrb_define_method(mrb, apr_process_class, "exec", mrb_apr_proc_exec, MRB_ARGS_REQ(1));
   mrb_define_method(mrb, apr_process_class, "wait", mrb_apr_proc_wait, MRB_ARGS_NONE());
   mrb_define_class_method(mrb, apr_process_class, "wait", mrb_apr_proc_wait_pid, MRB_ARGS_REQ(1));
   mrb_define_method(mrb, apr_process_class, "pid", mrb_apr_proc_pid, MRB_ARGS_NONE());
   mrb_define_method(mrb, apr_process_class, "io_set", mrb_apr_proc_io_set, MRB_ARGS_REQ(3));
   mrb_define_method(mrb, apr_process_class, "in", mrb_apr_proc_in, MRB_ARGS_NONE());
   mrb_define_method(mrb, apr_process_class, "out", mrb_apr_proc_out, MRB_ARGS_NONE());
   mrb_define_method(mrb, apr_process_class, "err", mrb_apr_proc_err, MRB_ARGS_NONE());
}
