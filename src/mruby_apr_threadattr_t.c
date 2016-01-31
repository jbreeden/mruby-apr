/*
 * apr_threadattr_t
 * Defined in file apr_thread_proc.h @ line 180
 */

#include "mruby_APR.h"

#if BIND_AprThreadattrT_TYPE

/* MRUBY_BINDING: header */
/* sha: user_defined */

/* MRUBY_BINDING_END */

/* MRUBY_BINDING: AprThreadattrT::initialize */
/* sha: c664054df86294fa251582eddb2395bddbe9e40e7f137a6139406ff5704d039c */
#if BIND_AprThreadattrT_INITIALIZE
mrb_value
mrb_APR_AprThreadattrT_initialize(mrb_state* mrb, mrb_value self) {
  mrb_raise(mrb, E_NOMETHOD_ERROR, "No initializer defined");
/* 
  apr_threadattr_t* native_object = (apr_threadattr_t*)calloc(1, sizeof(apr_threadattr_t));
  mruby_gift_apr_threadattr_t_data_ptr(self, native_object);
  return self;
*/
}
#endif
/* MRUBY_BINDING_END */


void mrb_APR_AprThreadattrT_init(mrb_state* mrb) {
  static int initialized = 0;
  if (initialized) return;
  else initialized = 1;

/* MRUBY_BINDING: pre_class_definition */
/* sha: user_defined */

/* MRUBY_BINDING_END */

/* MRUBY_BINDING: AprThreadattrT::class_definition */
/* sha: ff5cbb5f0a98849b7b6a03e1f34903a86926ac6916f82c3ca3b88ed815ad7001 */
  struct RClass* AprThreadattrT_class = mrb_define_class_under(mrb, APR_module(mrb), "AprThreadattrT", mrb->object_class);
  MRB_SET_INSTANCE_TT(AprThreadattrT_class, MRB_TT_DATA);
/* MRUBY_BINDING_END */

/* MRUBY_BINDING: AprThreadattrT::pre_class_method_definitions */
/* sha: user_defined */

/* MRUBY_BINDING_END */

/* MRUBY_BINDING: AprThreadattrT::class_method_definitions */
/* sha: ff66900d59ec12711e9628752262d0b3811319516834246d265aeda82a5fa273 */
#if BIND_AprThreadattrT_INITIALIZE
  mrb_define_method(mrb, AprThreadattrT_class, "initialize", mrb_APR_AprThreadattrT_initialize, MRB_ARGS_NONE());
#endif
/* MRUBY_BINDING_END */



/* MRUBY_BINDING: AprThreadattrT::post_class_definition */
/* sha: user_defined */

/* MRUBY_BINDING_END */
}

/* MRUBY_BINDING: footer */
/* sha: user_defined */

/* MRUBY_BINDING_END */
#endif
