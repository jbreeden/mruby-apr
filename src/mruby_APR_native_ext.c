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

#ifdef __cplusplus
extern "C" {
#endif

#define RAISE_APR_ERRNO(err) mrb_funcall(mrb, mrb_obj_value(APR_module(mrb)), "raise_apr_errno", 1, mrb_fixnum_value(err));
#define APR_STACK_POOL() mruby_unbox_apr_pool_t(mrb_iv_get(mrb, mrb_obj_value(APR_module(mrb)), mrb_intern_lit(mrb, "@stack_pool")))
#define APR_STACK_POOL_ENTER_COUNT() mrb_fixnum(mrb_iv_get(mrb, mrb_obj_value(APR_module(mrb)), mrb_intern_lit(mrb, "@stack_pool_enter_count")))
#define APR_STACK_POOL_ENTER_COUNT_SET(i) mrb_iv_set(mrb, mrb_obj_value(APR_module(mrb)), mrb_intern_lit(mrb, "@stack_pool_enter_count"), mrb_fixnum_value(i))

apr_pool_t *
mruby_apr_stack_pool_enter(mrb_state* mrb) {
  APR_STACK_POOL_ENTER_COUNT_SET(APR_STACK_POOL_ENTER_COUNT() + 1);
  return APR_STACK_POOL();
}

void
mruby_apr_stack_pool_leave(mrb_state* mrb) {
  mrb_int enter_count = APR_STACK_POOL_ENTER_COUNT() - 1;
  if (enter_count == 0) {
    apr_pool_clear(APR_STACK_POOL());
  }
  APR_STACK_POOL_ENTER_COUNT_SET(enter_count);
}

mrb_value
mruby_Dir_entries(mrb_state* mrb, mrb_value self) {
  char* path;
  apr_pool_t* pool = mruby_apr_stack_pool_enter(mrb);
  mrb_get_args(mrb, "z", &path);
  mrb_value results = mrb_ary_new(mrb);

  apr_dir_t* dir;
  apr_status_t err = apr_dir_open(&dir, path, pool);
  if (err != APR_SUCCESS) {
    mruby_apr_stack_pool_leave(mrb);
    RAISE_APR_ERRNO(err);
    return mrb_nil_value();
  }

  apr_finfo_t finfo;
  int status = apr_dir_read(&finfo, APR_FINFO_NAME, dir);
  while (status == 0 || status == APR_INCOMPLETE) {
    mrb_ary_push(mrb, results, mrb_str_new_cstr(mrb, finfo.name));
    status = apr_dir_read(&finfo, APR_FINFO_NAME, dir);
  }
  mruby_apr_stack_pool_leave(mrb);
  return results;
}

mrb_value
mruby_FilteTest_is_type(mrb_state* mrb, mrb_value self) {
  char* path;
  mrb_int type;
  mrb_value result = mrb_nil_value();

  apr_pool_t* pool = mruby_apr_stack_pool_enter(mrb);
  mrb_get_args(mrb, "zi", &path, &type);

  apr_finfo_t finfo;
  apr_status_t err = apr_stat(&finfo, path, APR_FINFO_TYPE, pool);
  if (err == APR_SUCCESS) {
    result = finfo.filetype == type
      ? mrb_true_value()
      : mrb_false_value();
  } else {
    RAISE_APR_ERRNO(err);
  }
  mruby_apr_stack_pool_leave(mrb);
  return result;
}

void
mruby_APR_init_native_ext(mrb_state* mrb) {
  struct RClass* Dir_class = mrb_define_class(mrb, "Dir", mrb->object_class);
  mrb_define_class_method(mrb, Dir_class, "entries", mruby_Dir_entries, MRB_ARGS_ARG(1, 0));

  struct RClass* FileTest_module = mrb_define_module(mrb, "FileTest");
  mrb_define_class_method(mrb, FileTest_module, "is_type?", mruby_FilteTest_is_type, MRB_ARGS_ARG(2, 0));
}

#ifdef __cplusplus
}
#endif
