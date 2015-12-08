/*
 * This file is a starting place for porting Ruby API code to C.
 * While the preferred language for CRuby Standard Library implementations
 * is Ruby, some things just need to be fast and efficient. Calling APR
 * through the ruby bindings involves allocating extra objects, and spending
 * extra time copying/moving arguments and results. So, sometimes, we'll
 * fall back to C.
 *
 * An example where this is the case is file globbing. Result sets can
 * easily hit hundreds of thousands if the user simply globs for "**\/*".
 * Saving a few extra objects per file test/directory traverse is significant.
 *
 * Note: This code is not generated. Do not let this file grow to the size
 *       of mruby_APR.c. That was generated with mruby-binings, so it's size
 *       is excusable.
 */


#include "mruby_APR.h"
#if defined(_WIN32)
  #include <process.h> /* _getpid */
  #define getpid _getpid
#else
  #include <unistd.h> /* getpid */
#endif

#ifdef __cplusplus
extern "C" {
#endif

#define RAISE_APR_ERRNO(err) mrb_funcall(mrb, mrb_obj_value(APR_module(mrb)), "raise_apr_errno", 1, mrb_fixnum_value(err));

/*
 * Stack Pool Implementation
 */

static apr_pool_t* stack_pool = NULL;
static int stack_pool_enter_count = 0;

mrb_value
mruby_APR_stack_pool(mrb_state* mrb, mrb_value self) {
  return mruby_box_apr_pool_t(mrb, stack_pool);
}

void
stack_pool_enter() {
  stack_pool_enter_count += stack_pool_enter_count + 1;
}

mrb_value
mruby_APR_stack_pool_enter(mrb_state* mrb, mrb_value self) {
  stack_pool_enter();
  return mrb_nil_value();
}

void
stack_pool_leave() {
  mrb_int enter_count = stack_pool_enter_count - 1;
  if (enter_count == 0) {
    apr_pool_clear(stack_pool);
  }
  stack_pool_enter_count = enter_count;
}

mrb_value
mruby_APR_stack_pool_leave(mrb_state* mrb, mrb_value self) {
  stack_pool_leave();
  return mrb_nil_value();
}

/*
 * END: Stack Pool Implementation
 */

mrb_value
mruby_Dir_entries(mrb_state* mrb, mrb_value self) {
  char* path;
  stack_pool_enter();
  mrb_get_args(mrb, "z", &path);
  mrb_value results = mrb_ary_new(mrb);

  apr_dir_t* dir;
  apr_status_t err = apr_dir_open(&dir, path, stack_pool);
  if (err != APR_SUCCESS) {
    stack_pool_leave(mrb);
    RAISE_APR_ERRNO(err);
    return mrb_nil_value();
  }

  apr_finfo_t finfo;
  int status = apr_dir_read(&finfo, APR_FINFO_NAME, dir);
  while (status == 0 || status == APR_INCOMPLETE) {
    mrb_ary_push(mrb, results, mrb_str_new_cstr(mrb, finfo.name));
    status = apr_dir_read(&finfo, APR_FINFO_NAME, dir);
  }
  stack_pool_leave(mrb);
  return results;
}

mrb_value
mruby_FilteTest_is_type(mrb_state* mrb, mrb_value self) {
  char* path;
  mrb_int type;
  mrb_value result = mrb_nil_value();

  stack_pool_enter();
  mrb_get_args(mrb, "zi", &path, &type);

  apr_finfo_t finfo;
  apr_status_t err = apr_stat(&finfo, path, APR_FINFO_TYPE, stack_pool);
  result = (err == APR_SUCCESS && finfo.filetype == type)
    ? mrb_true_value()
    : mrb_false_value();
  stack_pool_leave();
  return result;
}

mrb_value
mruby_Process_pid(mrb_state* mrb, mrb_value self) {
  return mrb_fixnum_value(getpid());
}

void
mruby_APR_init_native_ext(mrb_state* mrb) {
  apr_pool_create(&stack_pool, NULL);

  mrb_define_class_method(mrb, APR_module(mrb), "stack_pool", mruby_APR_stack_pool, MRB_ARGS_ARG(0, 0));
  mrb_define_class_method(mrb, APR_module(mrb), "stack_pool_enter", mruby_APR_stack_pool_enter, MRB_ARGS_ARG(0, 0));
  mrb_define_class_method(mrb, APR_module(mrb), "stack_pool_leave", mruby_APR_stack_pool_leave, MRB_ARGS_ARG(0, 0));

  struct RClass* Dir_class = mrb_define_class(mrb, "Dir", mrb->object_class);
  mrb_define_class_method(mrb, Dir_class, "entries", mruby_Dir_entries, MRB_ARGS_ARG(1, 0));

  struct RClass* FileTest_module = mrb_define_module(mrb, "FileTest");
  mrb_define_class_method(mrb, FileTest_module, "is_type?", mruby_FilteTest_is_type, MRB_ARGS_ARG(2, 0));

  struct RClass* Process_module = mrb_define_module(mrb, "Process");
  mrb_define_class_method(mrb, Process_module, "pid", mruby_Process_pid, MRB_ARGS_ARG(0, 0));
}

#ifdef __cplusplus
}
#endif
