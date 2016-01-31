/*
 * apr_thread_once_t
 * Defined in file apr_thread_proc.h @ line 186
 */

#include "mruby_APR.h"

#if BIND_AprThreadOnceT_TYPE

/* MRUBY_BINDING: header */
/* sha: user_defined */

/* MRUBY_BINDING_END */

/* MRUBY_BINDING: AprThreadOnceT::initialize */
/* sha: bb3cf90b549c19e1afc361656d2caadb8f2b25b58145fe8a5fc05dc40e9815d0 */
#if BIND_AprThreadOnceT_INITIALIZE
mrb_value
mrb_APR_AprThreadOnceT_initialize(mrb_state* mrb, mrb_value self) {
  mrb_raise(mrb, E_NOMETHOD_ERROR, "No initializer defined");
/* 
  apr_thread_once_t* native_object = (apr_thread_once_t*)calloc(1, sizeof(apr_thread_once_t));
  mruby_gift_apr_thread_once_t_data_ptr(self, native_object);
  return self;
*/
}
#endif
/* MRUBY_BINDING_END */


void mrb_APR_AprThreadOnceT_init(mrb_state* mrb) {
  static int initialized = 0;
  if (initialized) return;
  else initialized = 1;

/* MRUBY_BINDING: pre_class_definition */
/* sha: user_defined */

/* MRUBY_BINDING_END */

/* MRUBY_BINDING: AprThreadOnceT::class_definition */
/* sha: ea7ad8a349edd759f972f6c6fc49a08f21659e85fc71f7dc8fe2360bf4281ba6 */
  struct RClass* AprThreadOnceT_class = mrb_define_class_under(mrb, APR_module(mrb), "AprThreadOnceT", mrb->object_class);
  MRB_SET_INSTANCE_TT(AprThreadOnceT_class, MRB_TT_DATA);
/* MRUBY_BINDING_END */

/* MRUBY_BINDING: AprThreadOnceT::pre_class_method_definitions */
/* sha: user_defined */

/* MRUBY_BINDING_END */

/* MRUBY_BINDING: AprThreadOnceT::class_method_definitions */
/* sha: ff4ef7c7eee56a9f616c34b77cddc4b8a4998cd66f6dfbe0e5206cfa1a5ae37d */
#if BIND_AprThreadOnceT_INITIALIZE
  mrb_define_method(mrb, AprThreadOnceT_class, "initialize", mrb_APR_AprThreadOnceT_initialize, MRB_ARGS_NONE());
#endif
/* MRUBY_BINDING_END */



/* MRUBY_BINDING: AprThreadOnceT::post_class_definition */
/* sha: user_defined */

/* MRUBY_BINDING_END */
}

/* MRUBY_BINDING: footer */
/* sha: user_defined */

/* MRUBY_BINDING_END */
#endif
