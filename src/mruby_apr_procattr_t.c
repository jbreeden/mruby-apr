/*
 * apr_procattr_t
 * Defined in file apr_thread_proc.h @ line 183
 */

#include "mruby_APR.h"

#if BIND_AprProcattrT_TYPE

/* MRUBY_BINDING: header */
/* sha: user_defined */

/* MRUBY_BINDING_END */

/* MRUBY_BINDING: AprProcattrT::initialize */
/* sha: 96d1acd00a2676ed0efbdc38dba712e51789108c3b67b83e98f7606af8d51e82 */
#if BIND_AprProcattrT_INITIALIZE
mrb_value
mrb_APR_AprProcattrT_initialize(mrb_state* mrb, mrb_value self) {
  mrb_raise(mrb, E_NOMETHOD_ERROR, "No initializer defined");
/* 
  apr_procattr_t* native_object = (apr_procattr_t*)calloc(1, sizeof(apr_procattr_t));
  mruby_gift_apr_procattr_t_data_ptr(self, native_object);
  return self;
*/
}
#endif
/* MRUBY_BINDING_END */


void mrb_APR_AprProcattrT_init(mrb_state* mrb) {
  static int initialized = 0;
  if (initialized) return;
  else initialized = 1;

/* MRUBY_BINDING: pre_class_definition */
/* sha: user_defined */

/* MRUBY_BINDING_END */

/* MRUBY_BINDING: AprProcattrT::class_definition */
/* sha: c7b030cf5fd4272dd68b7aa05ff416cdcb0dc0661ddf4f2f8d617ec52389d11a */
  struct RClass* AprProcattrT_class = mrb_define_class_under(mrb, APR_module(mrb), "AprProcattrT", mrb->object_class);
  MRB_SET_INSTANCE_TT(AprProcattrT_class, MRB_TT_DATA);
/* MRUBY_BINDING_END */

/* MRUBY_BINDING: AprProcattrT::pre_class_method_definitions */
/* sha: user_defined */

/* MRUBY_BINDING_END */

/* MRUBY_BINDING: AprProcattrT::class_method_definitions */
/* sha: 2a4ee637c7095ac32b7cf4c8bde9d61b6ae175cdf93521f37e0a46a19a551839 */
#if BIND_AprProcattrT_INITIALIZE
  mrb_define_method(mrb, AprProcattrT_class, "initialize", mrb_APR_AprProcattrT_initialize, MRB_ARGS_NONE());
#endif
/* MRUBY_BINDING_END */



/* MRUBY_BINDING: AprProcattrT::post_class_definition */
/* sha: user_defined */

/* MRUBY_BINDING_END */
}

/* MRUBY_BINDING: footer */
/* sha: user_defined */

/* MRUBY_BINDING_END */
#endif
