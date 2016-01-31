/*
 * apr_socket_t
 * Defined in file apr_network_io.h @ line 191
 */

#include "mruby_APR.h"

#if BIND_AprSocketT_TYPE

/* MRUBY_BINDING: header */
/* sha: user_defined */

/* MRUBY_BINDING_END */

/* MRUBY_BINDING: AprSocketT::initialize */
/* sha: 1da316050192500eb8e31a0c02596a029876cc2e923a5a331f8b604074ebc8e0 */
#if BIND_AprSocketT_INITIALIZE
mrb_value
mrb_APR_AprSocketT_initialize(mrb_state* mrb, mrb_value self) {
  mrb_raise(mrb, E_NOMETHOD_ERROR, "No initializer defined");
/* 
  apr_socket_t* native_object = (apr_socket_t*)calloc(1, sizeof(apr_socket_t));
  mruby_gift_apr_socket_t_data_ptr(self, native_object);
  return self;
*/
}
#endif
/* MRUBY_BINDING_END */


void mrb_APR_AprSocketT_init(mrb_state* mrb) {
  static int initialized = 0;
  if (initialized) return;
  else initialized = 1;

/* MRUBY_BINDING: pre_class_definition */
/* sha: user_defined */

/* MRUBY_BINDING_END */

/* MRUBY_BINDING: AprSocketT::class_definition */
/* sha: 52f45ef9f3e92d7b8bfc3edbc91bd0a40c077064fa3809bffd35c809965db2a0 */
  struct RClass* AprSocketT_class = mrb_define_class_under(mrb, APR_module(mrb), "AprSocketT", mrb->object_class);
  MRB_SET_INSTANCE_TT(AprSocketT_class, MRB_TT_DATA);
/* MRUBY_BINDING_END */

/* MRUBY_BINDING: AprSocketT::pre_class_method_definitions */
/* sha: user_defined */

/* MRUBY_BINDING_END */

/* MRUBY_BINDING: AprSocketT::class_method_definitions */
/* sha: ff0d357f7af73be7c8b25b99341309b946743b8a30583d2ac65ca31a67b98456 */
#if BIND_AprSocketT_INITIALIZE
  mrb_define_method(mrb, AprSocketT_class, "initialize", mrb_APR_AprSocketT_initialize, MRB_ARGS_NONE());
#endif
/* MRUBY_BINDING_END */



/* MRUBY_BINDING: AprSocketT::post_class_definition */
/* sha: user_defined */

/* MRUBY_BINDING_END */
}

/* MRUBY_BINDING: footer */
/* sha: user_defined */

/* MRUBY_BINDING_END */
#endif
