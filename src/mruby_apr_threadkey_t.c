/*
 * apr_threadkey_t
 * Defined in file apr_thread_proc.h @ line 189
 */

#include "mruby_APR.h"

#if BIND_Threadkey_TYPE

/* MRUBY_BINDING: header */
/* sha: user_defined */

/* MRUBY_BINDING_END */

/* MRUBY_BINDING: Threadkey::initialize */
/* sha: 928a124f348d17a298ae63aa55fcafb957a6b559b71b0a8c035bbf18ecdc5bd7 */
#if BIND_Threadkey_INITIALIZE
mrb_value
mrb_APR_Threadkey_initialize(mrb_state* mrb, mrb_value self) {
  mrb_raise(mrb, E_NOMETHOD_ERROR, "No initializer defined");
/* 
  apr_threadkey_t* native_object = (apr_threadkey_t*)calloc(1, sizeof(apr_threadkey_t));
  mruby_gift_apr_threadkey_t_data_ptr(self, native_object);
  return self;
*/
}
#endif
/* MRUBY_BINDING_END */


void mrb_APR_Threadkey_init(mrb_state* mrb) {
  static int initialized = 0;
  if (initialized) return;
  else initialized = 1;

/* MRUBY_BINDING: pre_class_definition */
/* sha: user_defined */

/* MRUBY_BINDING_END */

/* MRUBY_BINDING: Threadkey::class_definition */
/* sha: e8f2bb5b7961e1c21644014229bc34723587f0733c281d479217b0bd74d05568 */
  struct RClass* Threadkey_class = mrb_define_class_under(mrb, APR_module(mrb), "Threadkey", mrb->object_class);
  MRB_SET_INSTANCE_TT(Threadkey_class, MRB_TT_DATA);
/* MRUBY_BINDING_END */

/* MRUBY_BINDING: Threadkey::pre_class_method_definitions */
/* sha: user_defined */

/* MRUBY_BINDING_END */

/* MRUBY_BINDING: Threadkey::class_method_definitions */
/* sha: c4f591693005182f404b1f8dbdf4d7bc7e77fd23c21b98c2815667a53a124a24 */
#if BIND_Threadkey_INITIALIZE
  mrb_define_method(mrb, Threadkey_class, "initialize", mrb_APR_Threadkey_initialize, MRB_ARGS_NONE());
#endif
/* MRUBY_BINDING_END */



/* MRUBY_BINDING: Threadkey::post_class_definition */
/* sha: user_defined */

/* MRUBY_BINDING_END */
}

/* MRUBY_BINDING: footer */
/* sha: user_defined */

/* MRUBY_BINDING_END */
#endif
