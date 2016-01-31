/*
 * apr_pool_t
 * Defined in file apr_pools.h @ line 60
 */

#include "mruby_APR.h"

#if BIND_AprPoolT_TYPE

/* MRUBY_BINDING: header */
/* sha: user_defined */

/* MRUBY_BINDING_END */

/* MRUBY_BINDING: AprPoolT::initialize */
/* sha: 8f45c03ab061ceb13f483c675dee69bf4c8e61137d2be28ce44ce2c195e52ed7 */
#if BIND_AprPoolT_INITIALIZE
mrb_value
mrb_APR_AprPoolT_initialize(mrb_state* mrb, mrb_value self) {
  mrb_raise(mrb, E_NOMETHOD_ERROR, "No initializer defined");
/* 
  apr_pool_t* native_object = (apr_pool_t*)calloc(1, sizeof(apr_pool_t));
  mruby_gift_apr_pool_t_data_ptr(self, native_object);
  return self;
*/
}
#endif
/* MRUBY_BINDING_END */


void mrb_APR_AprPoolT_init(mrb_state* mrb) {
  static int initialized = 0;
  if (initialized) return;
  else initialized = 1;

/* MRUBY_BINDING: pre_class_definition */
/* sha: user_defined */

/* MRUBY_BINDING_END */

/* MRUBY_BINDING: AprPoolT::class_definition */
/* sha: 00ea51acf0fb3076166fa56f93f685aaca7ad5183d1d8a44e0fdfad7c639b749 */
  struct RClass* AprPoolT_class = mrb_define_class_under(mrb, APR_module(mrb), "AprPoolT", mrb->object_class);
  MRB_SET_INSTANCE_TT(AprPoolT_class, MRB_TT_DATA);
/* MRUBY_BINDING_END */

/* MRUBY_BINDING: AprPoolT::pre_class_method_definitions */
/* sha: user_defined */

/* MRUBY_BINDING_END */

/* MRUBY_BINDING: AprPoolT::class_method_definitions */
/* sha: 945e70f3fe6d594e9f4917f9ed7c7c36a5394e58990cacf84eecfadaeb7159a7 */
#if BIND_AprPoolT_INITIALIZE
  mrb_define_method(mrb, AprPoolT_class, "initialize", mrb_APR_AprPoolT_initialize, MRB_ARGS_NONE());
#endif
/* MRUBY_BINDING_END */



/* MRUBY_BINDING: AprPoolT::post_class_definition */
/* sha: user_defined */

/* MRUBY_BINDING_END */
}

/* MRUBY_BINDING: footer */
/* sha: user_defined */

/* MRUBY_BINDING_END */
#endif
