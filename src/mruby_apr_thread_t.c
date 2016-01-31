/*
 * apr_thread_t
 * Defined in file apr_thread_proc.h @ line 177
 */

#include "mruby_APR.h"

#if BIND_AprThreadT_TYPE

/* MRUBY_BINDING: header */
/* sha: user_defined */

/* MRUBY_BINDING_END */

/* MRUBY_BINDING: AprThreadT::initialize */
/* sha: 31f3d1db83929d0ced3c7b8d2955bfdb5324672d9a33cdd918a48445efd136ba */
#if BIND_AprThreadT_INITIALIZE
mrb_value
mrb_APR_AprThreadT_initialize(mrb_state* mrb, mrb_value self) {
  mrb_raise(mrb, E_NOMETHOD_ERROR, "No initializer defined");
/* 
  apr_thread_t* native_object = (apr_thread_t*)calloc(1, sizeof(apr_thread_t));
  mruby_gift_apr_thread_t_data_ptr(self, native_object);
  return self;
*/
}
#endif
/* MRUBY_BINDING_END */


void mrb_APR_AprThreadT_init(mrb_state* mrb) {
  static int initialized = 0;
  if (initialized) return;
  else initialized = 1;

/* MRUBY_BINDING: pre_class_definition */
/* sha: user_defined */

/* MRUBY_BINDING_END */

/* MRUBY_BINDING: AprThreadT::class_definition */
/* sha: 8552706d0761b6b93694d703899def3287511ea59f9774391934e0ea042274df */
  struct RClass* AprThreadT_class = mrb_define_class_under(mrb, APR_module(mrb), "AprThreadT", mrb->object_class);
  MRB_SET_INSTANCE_TT(AprThreadT_class, MRB_TT_DATA);
/* MRUBY_BINDING_END */

/* MRUBY_BINDING: AprThreadT::pre_class_method_definitions */
/* sha: user_defined */

/* MRUBY_BINDING_END */

/* MRUBY_BINDING: AprThreadT::class_method_definitions */
/* sha: a0f01ce7439ba983e48a0326aa97fab058f95ee47fb18e5dadf3678526a0a082 */
#if BIND_AprThreadT_INITIALIZE
  mrb_define_method(mrb, AprThreadT_class, "initialize", mrb_APR_AprThreadT_initialize, MRB_ARGS_NONE());
#endif
/* MRUBY_BINDING_END */



/* MRUBY_BINDING: AprThreadT::post_class_definition */
/* sha: user_defined */

/* MRUBY_BINDING_END */
}

/* MRUBY_BINDING: footer */
/* sha: user_defined */

/* MRUBY_BINDING_END */
#endif
