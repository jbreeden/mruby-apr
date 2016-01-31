/*
 * apr_ipsubnet_t
 * Defined in file apr_network_io.h @ line 199
 */

#include "mruby_APR.h"

#if BIND_AprIpsubnetT_TYPE

/* MRUBY_BINDING: header */
/* sha: user_defined */

/* MRUBY_BINDING_END */

/* MRUBY_BINDING: AprIpsubnetT::initialize */
/* sha: c6a5b70304137dbc24b8e2b2ba4baa9bf6878326bf882cc8cc3badca70104137 */
#if BIND_AprIpsubnetT_INITIALIZE
mrb_value
mrb_APR_AprIpsubnetT_initialize(mrb_state* mrb, mrb_value self) {
  mrb_raise(mrb, E_NOMETHOD_ERROR, "No initializer defined");
/* 
  apr_ipsubnet_t* native_object = (apr_ipsubnet_t*)calloc(1, sizeof(apr_ipsubnet_t));
  mruby_gift_apr_ipsubnet_t_data_ptr(self, native_object);
  return self;
*/
}
#endif
/* MRUBY_BINDING_END */


void mrb_APR_AprIpsubnetT_init(mrb_state* mrb) {
  static int initialized = 0;
  if (initialized) return;
  else initialized = 1;

/* MRUBY_BINDING: pre_class_definition */
/* sha: user_defined */

/* MRUBY_BINDING_END */

/* MRUBY_BINDING: AprIpsubnetT::class_definition */
/* sha: c45aaf7fdb44d9f5dc6f0cf9963b222dbdd4a66a926b2fb23450e072d6f5bf18 */
  struct RClass* AprIpsubnetT_class = mrb_define_class_under(mrb, APR_module(mrb), "AprIpsubnetT", mrb->object_class);
  MRB_SET_INSTANCE_TT(AprIpsubnetT_class, MRB_TT_DATA);
/* MRUBY_BINDING_END */

/* MRUBY_BINDING: AprIpsubnetT::pre_class_method_definitions */
/* sha: user_defined */

/* MRUBY_BINDING_END */

/* MRUBY_BINDING: AprIpsubnetT::class_method_definitions */
/* sha: a216a2ea0e94d6547dd48ca0de25a652af172906d409f0a8195bf876576ccfee */
#if BIND_AprIpsubnetT_INITIALIZE
  mrb_define_method(mrb, AprIpsubnetT_class, "initialize", mrb_APR_AprIpsubnetT_initialize, MRB_ARGS_NONE());
#endif
/* MRUBY_BINDING_END */



/* MRUBY_BINDING: AprIpsubnetT::post_class_definition */
/* sha: user_defined */

/* MRUBY_BINDING_END */
}

/* MRUBY_BINDING: footer */
/* sha: user_defined */

/* MRUBY_BINDING_END */
#endif
