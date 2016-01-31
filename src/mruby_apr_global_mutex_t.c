/*
 * apr_global_mutex_t
 * Defined in file apr_global_mutex.h @ line 46
 */

#include "mruby_APR.h"

#if BIND_GlobalMutex_TYPE

/* MRUBY_BINDING: header */
/* sha: user_defined */

/* MRUBY_BINDING_END */

/* MRUBY_BINDING: GlobalMutex::initialize */
/* sha: 0c460c6e17cae2ee552a536ea5349a51e70b3104734125f4b7c78caa084b28ca */
#if BIND_GlobalMutex_INITIALIZE
mrb_value
mrb_APR_GlobalMutex_initialize(mrb_state* mrb, mrb_value self) {
  mrb_raise(mrb, E_NOMETHOD_ERROR, "No initializer defined");
/* 
  apr_global_mutex_t* native_object = (apr_global_mutex_t*)calloc(1, sizeof(apr_global_mutex_t));
  mruby_gift_apr_global_mutex_t_data_ptr(self, native_object);
  return self;
*/
}
#endif
/* MRUBY_BINDING_END */


void mrb_APR_GlobalMutex_init(mrb_state* mrb) {
  static int initialized = 0;
  if (initialized) return;
  else initialized = 1;

/* MRUBY_BINDING: pre_class_definition */
/* sha: user_defined */

/* MRUBY_BINDING_END */

/* MRUBY_BINDING: GlobalMutex::class_definition */
/* sha: 5b51c28a094b11c57462017e43966700fae02510dfbccc90fc2d9166d17dcd0f */
  struct RClass* GlobalMutex_class = mrb_define_class_under(mrb, APR_module(mrb), "GlobalMutex", mrb->object_class);
  MRB_SET_INSTANCE_TT(GlobalMutex_class, MRB_TT_DATA);
/* MRUBY_BINDING_END */

/* MRUBY_BINDING: GlobalMutex::pre_class_method_definitions */
/* sha: user_defined */

/* MRUBY_BINDING_END */

/* MRUBY_BINDING: GlobalMutex::class_method_definitions */
/* sha: f2da77931083ab470cf0d4841a37642e4bae414b5c1253488bcddc976a38f983 */
#if BIND_GlobalMutex_INITIALIZE
  mrb_define_method(mrb, GlobalMutex_class, "initialize", mrb_APR_GlobalMutex_initialize, MRB_ARGS_NONE());
#endif
/* MRUBY_BINDING_END */



/* MRUBY_BINDING: GlobalMutex::post_class_definition */
/* sha: user_defined */

/* MRUBY_BINDING_END */
}

/* MRUBY_BINDING: footer */
/* sha: user_defined */

/* MRUBY_BINDING_END */
#endif
