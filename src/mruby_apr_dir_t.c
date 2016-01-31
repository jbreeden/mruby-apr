/*
 * apr_dir_t
 * Defined in file apr_file_info.h @ line 121
 */

#include "mruby_APR.h"

#if BIND_AprDirT_TYPE

/* MRUBY_BINDING: header */
/* sha: user_defined */

/* MRUBY_BINDING_END */

/* MRUBY_BINDING: AprDirT::initialize */
/* sha: 87fd724605866d34101ed73b88bb90bfb8b3e41bd40ab45209edaf27d4914df5 */
#if BIND_AprDirT_INITIALIZE
mrb_value
mrb_APR_AprDirT_initialize(mrb_state* mrb, mrb_value self) {
  mrb_raise(mrb, E_NOMETHOD_ERROR, "No initializer defined");
/* 
  apr_dir_t* native_object = (apr_dir_t*)calloc(1, sizeof(apr_dir_t));
  mruby_gift_apr_dir_t_data_ptr(self, native_object);
  return self;
*/
}
#endif
/* MRUBY_BINDING_END */


void mrb_APR_AprDirT_init(mrb_state* mrb) {
  static int initialized = 0;
  if (initialized) return;
  else initialized = 1;

/* MRUBY_BINDING: pre_class_definition */
/* sha: user_defined */

/* MRUBY_BINDING_END */

/* MRUBY_BINDING: AprDirT::class_definition */
/* sha: b15c58905996754a73c36e577ee77fbe85dc0607a7b27b03ba936e765749b30d */
  struct RClass* AprDirT_class = mrb_define_class_under(mrb, APR_module(mrb), "AprDirT", mrb->object_class);
  MRB_SET_INSTANCE_TT(AprDirT_class, MRB_TT_DATA);
/* MRUBY_BINDING_END */

/* MRUBY_BINDING: AprDirT::pre_class_method_definitions */
/* sha: user_defined */

/* MRUBY_BINDING_END */

/* MRUBY_BINDING: AprDirT::class_method_definitions */
/* sha: 408a414fd456f6d0e8fb900b91a9a916af99016a075ebaaf911fbbb9f2ba1ec7 */
#if BIND_AprDirT_INITIALIZE
  mrb_define_method(mrb, AprDirT_class, "initialize", mrb_APR_AprDirT_initialize, MRB_ARGS_NONE());
#endif
/* MRUBY_BINDING_END */



/* MRUBY_BINDING: AprDirT::post_class_definition */
/* sha: user_defined */

/* MRUBY_BINDING_END */
}

/* MRUBY_BINDING: footer */
/* sha: user_defined */

/* MRUBY_BINDING_END */
#endif
