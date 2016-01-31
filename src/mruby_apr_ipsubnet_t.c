/*
 * apr_ipsubnet_t
 * Defined in file apr_network_io.h @ line 199
 */

#include "mruby_APR.h"

#if BIND_Ipsubnet_TYPE

/* MRUBY_BINDING: header */
/* sha: user_defined */

/* MRUBY_BINDING_END */

/* MRUBY_BINDING: Ipsubnet::initialize */
/* sha: bd5c30444357cfb44faa078fcd8447e65073975928bc1390f58ec5f281e1f6d8 */
#if BIND_Ipsubnet_INITIALIZE
mrb_value
mrb_APR_Ipsubnet_initialize(mrb_state* mrb, mrb_value self) {
  mrb_raise(mrb, E_NOMETHOD_ERROR, "No initializer defined");
/* 
  apr_ipsubnet_t* native_object = (apr_ipsubnet_t*)calloc(1, sizeof(apr_ipsubnet_t));
  mruby_gift_apr_ipsubnet_t_data_ptr(self, native_object);
  return self;
*/
}
#endif
/* MRUBY_BINDING_END */


void mrb_APR_Ipsubnet_init(mrb_state* mrb) {
  static int initialized = 0;
  if (initialized) return;
  else initialized = 1;

/* MRUBY_BINDING: pre_class_definition */
/* sha: user_defined */

/* MRUBY_BINDING_END */

/* MRUBY_BINDING: Ipsubnet::class_definition */
/* sha: 4e353fcd1b406b70ff682e8cee199feb256a46b49b19ee448af68574451b081d */
  struct RClass* Ipsubnet_class = mrb_define_class_under(mrb, APR_module(mrb), "Ipsubnet", mrb->object_class);
  MRB_SET_INSTANCE_TT(Ipsubnet_class, MRB_TT_DATA);
/* MRUBY_BINDING_END */

/* MRUBY_BINDING: Ipsubnet::pre_class_method_definitions */
/* sha: user_defined */

/* MRUBY_BINDING_END */

/* MRUBY_BINDING: Ipsubnet::class_method_definitions */
/* sha: 38a193ee422f8cdf7947ca85cb684ae2095e174061759ae45816113ec17d90e7 */
#if BIND_Ipsubnet_INITIALIZE
  mrb_define_method(mrb, Ipsubnet_class, "initialize", mrb_APR_Ipsubnet_initialize, MRB_ARGS_NONE());
#endif
/* MRUBY_BINDING_END */



/* MRUBY_BINDING: Ipsubnet::post_class_definition */
/* sha: user_defined */

/* MRUBY_BINDING_END */
}

/* MRUBY_BINDING: footer */
/* sha: user_defined */

/* MRUBY_BINDING_END */
#endif
