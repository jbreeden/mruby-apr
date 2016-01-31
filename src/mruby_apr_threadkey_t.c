/*
 * apr_threadkey_t
 * Defined in file apr_thread_proc.h @ line 189
 */

#include "mruby_APR.h"

#if BIND_AprThreadkeyT_TYPE

/* MRUBY_BINDING: header */
/* sha: user_defined */

/* MRUBY_BINDING_END */

/* MRUBY_BINDING: AprThreadkeyT::initialize */
/* sha: 5cd3b3e86592d75b17ea88ef4c2ab85bc31a044aa2e7b07237a90e65930e143e */
#if BIND_AprThreadkeyT_INITIALIZE
mrb_value
mrb_APR_AprThreadkeyT_initialize(mrb_state* mrb, mrb_value self) {
  mrb_raise(mrb, E_NOMETHOD_ERROR, "No initializer defined");
/* 
  apr_threadkey_t* native_object = (apr_threadkey_t*)calloc(1, sizeof(apr_threadkey_t));
  mruby_gift_apr_threadkey_t_data_ptr(self, native_object);
  return self;
*/
}
#endif
/* MRUBY_BINDING_END */


void mrb_APR_AprThreadkeyT_init(mrb_state* mrb) {
  static int initialized = 0;
  if (initialized) return;
  else initialized = 1;

/* MRUBY_BINDING: pre_class_definition */
/* sha: user_defined */

/* MRUBY_BINDING_END */

/* MRUBY_BINDING: AprThreadkeyT::class_definition */
/* sha: 0ff9a73dcc50bf1dd83fa8189c1e9f225922d30c78e40e45002ec9095e8dcde2 */
  struct RClass* AprThreadkeyT_class = mrb_define_class_under(mrb, APR_module(mrb), "AprThreadkeyT", mrb->object_class);
  MRB_SET_INSTANCE_TT(AprThreadkeyT_class, MRB_TT_DATA);
/* MRUBY_BINDING_END */

/* MRUBY_BINDING: AprThreadkeyT::pre_class_method_definitions */
/* sha: user_defined */

/* MRUBY_BINDING_END */

/* MRUBY_BINDING: AprThreadkeyT::class_method_definitions */
/* sha: 3e653bb0a0c0fe20450d717ce5912eeb08f54605dbba362fb06682a801857ebd */
#if BIND_AprThreadkeyT_INITIALIZE
  mrb_define_method(mrb, AprThreadkeyT_class, "initialize", mrb_APR_AprThreadkeyT_initialize, MRB_ARGS_NONE());
#endif
/* MRUBY_BINDING_END */



/* MRUBY_BINDING: AprThreadkeyT::post_class_definition */
/* sha: user_defined */

/* MRUBY_BINDING_END */
}

/* MRUBY_BINDING: footer */
/* sha: user_defined */

/* MRUBY_BINDING_END */
#endif
