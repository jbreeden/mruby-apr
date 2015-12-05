#include "mruby_APR.h"

#ifdef __cplusplus
extern "C" {
#endif

#define RAISE_APR_ERRNO(err)\
if (err != APR_SUCCESS) { \
  mrb_funcall(mrb, mrb_obj_value(APR_module(mrb)), "raise_apr_errno", 1, (mrb_int)err); \
  printf("Should have raised\n");\
  return mrb_nil_value(); \
}

// mrb_value
// mruby_Dir_entries(mrb_state* mrb, mrb_value self) {
//   char* path;
//   apr_pool_t* pool;
//   RAISE_APR_ERRNO(apr_pool_create(&pool, NULL));
//   mrb_get_args(mrb, "z", &path);
//   mrb_value results = mrb_ary_new(mrb);
//
//   apr_dir_t* dir;
//   RAISE_APR_ERRNO(apr_dir_open(&dir, path, pool));
//
//   apr_finfo_t finfo;
//   int status = apr_dir_read(&finfo, APR_FINFO_NAME, dir);
//   while (status == 0 || status == APR_INCOMPLETE) {
//     mrb_ary_push(mrb, results, mrb_str_new_cstr(mrb, finfo.name));
//     status = apr_dir_read(&finfo, APR_FINFO_NAME, dir);
//   }
//   apr_pool_destroy(pool);
//   return results;
// }

void
mruby_APR_init_native_ext(mrb_state* mrb) {
  // struct RClass* Dir_class = mrb_define_class(mrb, "Dir", mrb->object_class);
  // mrb_define_class_method(mrb, Dir_class, "entries", mruby_Dir_entries, MRB_ARGS_ARG(1, 0));
}

#ifdef __cplusplus
}
#endif
