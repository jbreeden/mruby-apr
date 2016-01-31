/*
 * apr_global_mutex_t
 * Defined in file apr_global_mutex.h @ line 46
 */

#include "mruby_APR.h"

#if BIND_AprGlobalMutexT_TYPE

/* MRUBY_BINDING: header */
/* sha: user_defined */

/* MRUBY_BINDING_END */

/* MRUBY_BINDING: AprGlobalMutexT::initialize */
/* sha: f00c84be387afac86b2dc633846a33c8122e9fbbbaf5096a7ca8b183b74a6b57 */
#if BIND_AprGlobalMutexT_INITIALIZE
mrb_value
mrb_APR_AprGlobalMutexT_initialize(mrb_state* mrb, mrb_value self) {
  mrb_raise(mrb, E_NOMETHOD_ERROR, "No initializer defined");
/* 
  apr_global_mutex_t* native_object = (apr_global_mutex_t*)calloc(1, sizeof(apr_global_mutex_t));
  mruby_gift_apr_global_mutex_t_data_ptr(self, native_object);
  return self;
*/
}
#endif
/* MRUBY_BINDING_END */


void mrb_APR_AprGlobalMutexT_init(mrb_state* mrb) {
  static int initialized = 0;
  if (initialized) return;
  else initialized = 1;

/* MRUBY_BINDING: pre_class_definition */
/* sha: user_defined */

/* MRUBY_BINDING_END */

/* MRUBY_BINDING: AprGlobalMutexT::class_definition */
/* sha: c8211e202812127a157e6add73e9ae0fdcaa53e3c59375ee5cf9158c03f2a889 */
  struct RClass* AprGlobalMutexT_class = mrb_define_class_under(mrb, APR_module(mrb), "AprGlobalMutexT", mrb->object_class);
  MRB_SET_INSTANCE_TT(AprGlobalMutexT_class, MRB_TT_DATA);
/* MRUBY_BINDING_END */

/* MRUBY_BINDING: AprGlobalMutexT::pre_class_method_definitions */
/* sha: user_defined */

/* MRUBY_BINDING_END */

/* MRUBY_BINDING: AprGlobalMutexT::class_method_definitions */
/* sha: 36b95cb055bec6a88dad926a68cd3833601c242abe7505bf737c123018420ffd */
#if BIND_AprGlobalMutexT_INITIALIZE
  mrb_define_method(mrb, AprGlobalMutexT_class, "initialize", mrb_APR_AprGlobalMutexT_initialize, MRB_ARGS_NONE());
#endif
/* MRUBY_BINDING_END */



/* MRUBY_BINDING: AprGlobalMutexT::post_class_definition */
/* sha: user_defined */

/* MRUBY_BINDING_END */
}

/* MRUBY_BINDING: footer */
/* sha: user_defined */

/* MRUBY_BINDING_END */
#endif
