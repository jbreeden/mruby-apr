/*
 * apr_threadattr_t
 * Defined in file apr_thread_proc.h @ line 180
 */

#include "mruby_APR.h"

#if BIND_Threadattr_TYPE

/* MRUBY_BINDING: header */
/* sha: user_defined */

/* MRUBY_BINDING_END */

/* MRUBY_BINDING: Threadattr::initialize */
/* sha: f852ef8b9a7f5566517f3f1014bb1adbdcb9cf0837cc37a232ebb7de1bce27a7 */
#if BIND_Threadattr_INITIALIZE
mrb_value
mrb_APR_Threadattr_initialize(mrb_state* mrb, mrb_value self) {
  mrb_raise(mrb, E_NOMETHOD_ERROR, "No initializer defined");
/* 
  apr_threadattr_t* native_object = (apr_threadattr_t*)calloc(1, sizeof(apr_threadattr_t));
  mruby_gift_apr_threadattr_t_data_ptr(self, native_object);
  return self;
*/
}
#endif
/* MRUBY_BINDING_END */


void mrb_APR_Threadattr_init(mrb_state* mrb) {
  static int initialized = 0;
  if (initialized) return;
  else initialized = 1;

/* MRUBY_BINDING: pre_class_definition */
/* sha: user_defined */

/* MRUBY_BINDING_END */

/* MRUBY_BINDING: Threadattr::class_definition */
/* sha: a1a8eb328af4819a0881fe198ce299b4471a05e0f2ac6cb7843d6c6a5cad03f1 */
  struct RClass* Threadattr_class = mrb_define_class_under(mrb, APR_module(mrb), "Threadattr", mrb->object_class);
  MRB_SET_INSTANCE_TT(Threadattr_class, MRB_TT_DATA);
/* MRUBY_BINDING_END */

/* MRUBY_BINDING: Threadattr::pre_class_method_definitions */
/* sha: user_defined */

/* MRUBY_BINDING_END */

/* MRUBY_BINDING: Threadattr::class_method_definitions */
/* sha: e12802d75f2843858a1e908e2b1c448e35d36045cab15e1acac66c2740a7a3f8 */
#if BIND_Threadattr_INITIALIZE
  mrb_define_method(mrb, Threadattr_class, "initialize", mrb_APR_Threadattr_initialize, MRB_ARGS_NONE());
#endif
/* MRUBY_BINDING_END */



/* MRUBY_BINDING: Threadattr::post_class_definition */
/* sha: user_defined */

/* MRUBY_BINDING_END */
}

/* MRUBY_BINDING: footer */
/* sha: user_defined */

/* MRUBY_BINDING_END */
#endif
