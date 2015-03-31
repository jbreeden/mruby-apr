#include "mruby_apr.h"
#include "mruby.h"
#include "apr.h"
#include "apr_general.h"
#include "apr_errno.h"

using namespace std;

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

void mrb_mruby_apr_gem_init(mrb_state* mrb) {
   apr_initialize();

   auto apr_module = mrb_define_module(mrb, "APR");
      
   mrb_mruby_apr_file_init(mrb, apr_module);
   mrb_mruby_apr_env_init(mrb, apr_module);
   mrb_mruby_apr_process_init(mrb, apr_module);
   mrb_mruby_apr_system_init(mrb, apr_module);
   mrb_mruby_apr_tcp_init(mrb, apr_module);
}

void mrb_mruby_apr_gem_final(mrb_state* mrb) {}
