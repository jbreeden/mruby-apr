#include <string>
#include <memory>
#include "mruby_apr.h"
#include "mruby.h"
#include "mruby/variable.h"
#include "mruby/string.h"
#include "mruby/data.h"
#include "apr.h"
#include "apr_env.h"
#include "apr_errno.h"
#include "apr_pools.h"
#include "apr_file_io.h"
#include "apr_thread_proc.h"
#include "apr_network_io.h"
#include "stdlib.h"

#if defined(_WIN32) || defined(_WIN64)
   // Need OpenProcess function.
   // This is in WinBase.h before Window 8, then Processthreadsapi.h there after.
   #include "WinBase.h"
   #include "Processthreadsapi.h"
#endif

using namespace std;

static apr_pool_t* pool;

static
void
mrb_raise_apr_errno(mrb_state* mrb, int apr_errno, char* message) {
   auto errno_module = mrb_module_get(mrb, "Errno");
   auto sys_call_error_class = mrb_class_get_under(mrb, errno_module, "SystemCallError");
   mrb_value error_args[2];
   mrb_value rb_message = mrb_str_new_cstr(mrb, message);
   mrb_value rb_errno;
   SET_INT_VALUE(rb_errno, APR_TO_OS_ERROR(apr_errno));

   int argc;
   if (message != NULL) {
      argc = 2;
      error_args[0] = rb_message;
      error_args[1] = rb_errno;
   }
   else {
      argc = 1;
      error_args[0] = rb_errno;
   }

   mrb_value rb_exception = mrb_obj_new(mrb, sys_call_error_class, argc, error_args);
   mrb_exc_raise(mrb, rb_exception);
}

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

struct AprProc {
   apr_proc_t proc;
   apr_procattr_t* proc_attr;
   apr_pool_t* pool;

   AprProc() {
      apr_pool_create(&pool, NULL);
      apr_procattr_create(&proc_attr, pool);
   }
};

static
void free_mpr_proc(mrb_state* mrb, void* ptr) {
   AprProc* mpr_proc = (AprProc*)ptr;
   apr_pool_destroy(mpr_proc->pool);
   free(mpr_proc);
}

static
mrb_data_type apr_proc_data_type = {
   "MprProc", free_mpr_proc
};

#define SYM_CHECK(sym, name) \
   (cmdtype == mrb_intern_cstr(mrb, #name))

#define GET_APR_PROC_DATA(MRB_VAL) \
   ((AprProc*)DATA_PTR(mrb_iv_get(mrb, MRB_VAL, mrb_intern_cstr(mrb, "data"))))

#define GUARD_DOUBLE_EXEC(MSG) \
   if (mrb_test(mrb_iv_get(mrb, self, mrb_intern_cstr(mrb, "execed")))) { \
      mrb_raise(mrb, mrb->eStandardError_class, MSG); \
      return mrb_nil_value(); \
   }

#define GUARD_NO_EXEC(MSG) \
   if (!mrb_test(mrb_iv_get(mrb, self, mrb_intern_cstr(mrb, "execed")))) { \
      mrb_raise(mrb, mrb->eStandardError_class, MSG); \
      return mrb_nil_value(); \
   }

#define GUARD_APR_ERRNO(ERR, MSG) \
   if (ERR != APR_SUCCESS) { \
      mrb_raise_apr_errno(mrb, ERR, MSG); \
      return mrb_nil_value(); \
   }

extern "C" {
   
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
      GUARD_DOUBLE_EXEC("Cannot change process after calling exec");

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

      return mrb_symbol_value(cmdtype);
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
      GUARD_DOUBLE_EXEC("Cannot exec a process twice");

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
      GUARD_NO_EXEC("Cannot get PID of a process that has not been started")
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

   //<
   // # module APR::TCP
   // ## `::get_open_port`
   // Return an open TCP port number
   //>
   mrb_value
   mrb_apr_tcp_get_open_port(mrb_state* mrb, mrb_value self) {
      // Bind a socket to port 0 (lets the OS choose)
      apr_socket_t *socket;
      apr_socket_create(&socket, APR_INET, SOCK_STREAM, APR_PROTO_TCP, pool);
      apr_sockaddr_t *addr;
      apr_sockaddr_info_get(&addr, NULL, APR_INET, 0, 0, pool);
      apr_socket_bind(socket, addr);

      // Get the selected port for the socket
      apr_socket_addr_get(&addr, apr_interface_e::APR_LOCAL, socket);
      mrb_value port;
      SET_INT_VALUE(port, addr->port);

      apr_socket_close(socket);
      return port;
   }

   //<
   // # object ENV
   // ## `#[](name)`
   // Returns the value of the environemnt variable named `name`
   //>
   mrb_value
   mrb_apr_env_get(mrb_state* mrb, mrb_value self) {
      mrb_value key;
      mrb_get_args(mrb, "S", &key);

      char* key_cstr = mrb_str_to_cstr(mrb, key);

      char* value;
      apr_status_t status = apr_env_get(&value, key_cstr, pool);
      
      mrb_value result;
      if (status == APR_SUCCESS) {
         result = mrb_str_new_cstr(mrb, value);
      }
      else {
         result = mrb_nil_value();
      }

      apr_pool_clear(pool);
      return result;
   }

   //<
   // ## `#[]=(name, value)`
   // Sets the value of the environemnt variable named `name` to `value`
   //>
   mrb_value
   mrb_apr_env_set(mrb_state* mrb, mrb_value self) {
      mrb_value key;
      mrb_value value;
      mrb_get_args(mrb, "SS", &key, &value);

      char* key_cstr = mrb_str_to_cstr(mrb, key);
      char* value_cstr = mrb_str_to_cstr(mrb, value);
      apr_status_t status = apr_env_set(key_cstr, value_cstr, pool);
      apr_pool_clear(pool);

      if (status == APR_SUCCESS) {
         return value;
      }
      else {
         return mrb_nil_value();
      }
   }

   //<
   // ## `#delete(name)`
   // Deletes the environemnt variable named `name`
   //>
   mrb_value
   mrb_apr_env_delete(mrb_state* mrb, mrb_value self) {
      mrb_value key;
      mrb_get_args(mrb, "S", &key);

      char* key_cstr = mrb_str_to_cstr(mrb, key);

      char* value;
      apr_status_t get_status = apr_env_get(&value, key_cstr, pool);

      if (get_status != APR_SUCCESS) {
         return mrb_nil_value();
      }

      mrb_value result = mrb_str_new_cstr(mrb, value);

      apr_status_t status = apr_env_delete(key_cstr, pool);
      apr_pool_clear(pool);

      return result;
   }

   void define_apr_cmdtype_symbols(mrb_state* mrb) {
      mrb_intern_cstr(mrb, "APR_SHELLCMD");
      mrb_intern_cstr(mrb, "APR_PROGRAM");
      mrb_intern_cstr(mrb, "APR_PROGRAM_ENV");
      mrb_intern_cstr(mrb, "APR_PROGRAM_PATH");
      mrb_intern_cstr(mrb, "APR_SHELLCMD_ENV");
   }

   void mrb_mruby_apr_gem_init(mrb_state* mrb) {
      apr_initialize();
      apr_pool_create(&pool, NULL);

      define_apr_cmdtype_symbols(mrb);

      auto proces_module = mrb_define_module(mrb, "Process");
      auto apr_module = mrb_define_module(mrb, "APR");
      auto apr_process_class = mrb_define_class_under(mrb, apr_module, "Process", mrb->object_class);
      auto apr_tcp_module = mrb_define_module_under(mrb, apr_module, "TCP");

      // APR::Process methods
      mrb_define_method(mrb, apr_process_class, "initialize", mrb_apr_proc_init, MRB_ARGS_NONE());
      mrb_define_method(mrb, apr_process_class, "cmdtype_set", mrb_apr_proc_cmdtype_set, MRB_ARGS_REQ(1));
      mrb_define_method(mrb, apr_process_class, "exec", mrb_apr_proc_exec, MRB_ARGS_REQ(1));
      mrb_define_method(mrb, apr_process_class, "wait", mrb_apr_proc_wait, MRB_ARGS_NONE());
      mrb_define_class_method(mrb, apr_process_class, "wait", mrb_apr_proc_wait_pid, MRB_ARGS_REQ(1));
      mrb_define_method(mrb, apr_process_class, "pid", mrb_apr_proc_pid, MRB_ARGS_NONE());

      // APR::TCP Methods
      mrb_define_module_function(mrb, apr_tcp_module, "get_open_tcp_port", mrb_apr_tcp_get_open_port, MRB_ARGS_NONE());

      // ENV Object
      auto env = mrb_instance_new(mrb, mrb_obj_value(mrb->object_class));
      mrb_define_singleton_method(mrb, mrb_obj_ptr(env), "[]", mrb_apr_env_get, MRB_ARGS_REQ(1));
      mrb_define_singleton_method(mrb, mrb_obj_ptr(env), "[]=", mrb_apr_env_set, MRB_ARGS_REQ(2));
      mrb_define_singleton_method(mrb, mrb_obj_ptr(env), "delete", mrb_apr_env_delete, MRB_ARGS_REQ(1));
      mrb_define_global_const(mrb, "ENV", env);
   }

   void mrb_mruby_apr_gem_final(mrb_state* mrb) {}

}
