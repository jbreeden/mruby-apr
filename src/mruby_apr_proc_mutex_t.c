/*
 * apr_proc_mutex_t
 * Defined in file apr_proc_mutex.h @ line 54
 */

#include "mruby_APR.h"

#if BIND_AprProcMutexT_TYPE

/* MRUBY_BINDING: header */
/* sha: user_defined */

/* MRUBY_BINDING_END */

/* MRUBY_BINDING: AprProcMutexT::initialize */
/* sha: 65ad40f40ef87090abfb8aba6dc8ee240286e6991464ee2c0e0a233a897478d2 */
#if BIND_AprProcMutexT_INITIALIZE
mrb_value
mrb_APR_AprProcMutexT_initialize(mrb_state* mrb, mrb_value self) {
  mrb_raise(mrb, E_NOMETHOD_ERROR, "No initializer defined");
/* 
  apr_proc_mutex_t* native_object = (apr_proc_mutex_t*)calloc(1, sizeof(apr_proc_mutex_t));
  mruby_gift_apr_proc_mutex_t_data_ptr(self, native_object);
  return self;
*/
}
#endif
/* MRUBY_BINDING_END */


void mrb_APR_AprProcMutexT_init(mrb_state* mrb) {
  static int initialized = 0;
  if (initialized) return;
  else initialized = 1;

/* MRUBY_BINDING: pre_class_definition */
/* sha: user_defined */

/* MRUBY_BINDING_END */

/* MRUBY_BINDING: AprProcMutexT::class_definition */
/* sha: c7690f3b809ce2c2414cbcc657a38cf2ad9e1d6a1d50daedac6ad621556e93e9 */
  struct RClass* AprProcMutexT_class = mrb_define_class_under(mrb, APR_module(mrb), "AprProcMutexT", mrb->object_class);
  MRB_SET_INSTANCE_TT(AprProcMutexT_class, MRB_TT_DATA);
/* MRUBY_BINDING_END */

/* MRUBY_BINDING: AprProcMutexT::pre_class_method_definitions */
/* sha: user_defined */

/* MRUBY_BINDING_END */

/* MRUBY_BINDING: AprProcMutexT::class_method_definitions */
/* sha: a735374e0f5a60d11956a5a091b70b5eb111cc559dadcc49a7d6a353a2be47a8 */
#if BIND_AprProcMutexT_INITIALIZE
  mrb_define_method(mrb, AprProcMutexT_class, "initialize", mrb_APR_AprProcMutexT_initialize, MRB_ARGS_NONE());
#endif
/* MRUBY_BINDING_END */



/* MRUBY_BINDING: AprProcMutexT::post_class_definition */
/* sha: user_defined */

/* MRUBY_BINDING_END */
}

/* MRUBY_BINDING: footer */
/* sha: user_defined */

/* MRUBY_BINDING_END */
#endif
