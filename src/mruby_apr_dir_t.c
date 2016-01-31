/*
 * apr_dir_t
 * Defined in file apr_file_info.h @ line 121
 */

#include "mruby_APR.h"

#if BIND_Dir_TYPE

/* MRUBY_BINDING: header */
/* sha: user_defined */

/* MRUBY_BINDING_END */

/* MRUBY_BINDING: Dir::initialize */
/* sha: 59df0c9500b378b8231133135551efbccfb6326b700b95aefec564d7c90cd8e1 */
#if BIND_Dir_INITIALIZE
mrb_value
mrb_APR_Dir_initialize(mrb_state* mrb, mrb_value self) {
  mrb_raise(mrb, E_NOMETHOD_ERROR, "No initializer defined");
/* 
  apr_dir_t* native_object = (apr_dir_t*)calloc(1, sizeof(apr_dir_t));
  mruby_gift_apr_dir_t_data_ptr(self, native_object);
  return self;
*/
}
#endif
/* MRUBY_BINDING_END */


void mrb_APR_Dir_init(mrb_state* mrb) {
  static int initialized = 0;
  if (initialized) return;
  else initialized = 1;

/* MRUBY_BINDING: pre_class_definition */
/* sha: user_defined */

/* MRUBY_BINDING_END */

/* MRUBY_BINDING: Dir::class_definition */
/* sha: 2ce0af74e22b9cbf59cec741314680d7278d632acceb66e94d0a6fd9d9081b7a */
  struct RClass* Dir_class = mrb_define_class_under(mrb, APR_module(mrb), "Dir", mrb->object_class);
  MRB_SET_INSTANCE_TT(Dir_class, MRB_TT_DATA);
/* MRUBY_BINDING_END */

/* MRUBY_BINDING: Dir::pre_class_method_definitions */
/* sha: user_defined */

/* MRUBY_BINDING_END */

/* MRUBY_BINDING: Dir::class_method_definitions */
/* sha: 0a23c41cfaa5de27a056220d5e833aa3f60fc8f348ae929caa46a728bcbe4ea9 */
#if BIND_Dir_INITIALIZE
  mrb_define_method(mrb, Dir_class, "initialize", mrb_APR_Dir_initialize, MRB_ARGS_NONE());
#endif
/* MRUBY_BINDING_END */



/* MRUBY_BINDING: Dir::post_class_definition */
/* sha: user_defined */

/* MRUBY_BINDING_END */
}

/* MRUBY_BINDING: footer */
/* sha: user_defined */

/* MRUBY_BINDING_END */
#endif
