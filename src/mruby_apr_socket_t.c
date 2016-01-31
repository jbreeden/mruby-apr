/*
 * apr_socket_t
 * Defined in file apr_network_io.h @ line 191
 */

#include "mruby_APR.h"

#if BIND_Socket_TYPE

/* MRUBY_BINDING: header */
/* sha: user_defined */

/* MRUBY_BINDING_END */

/* MRUBY_BINDING: Socket::initialize */
/* sha: 3f2356ce4f35e709b57222af064b4bb8777eb4ff4242684d9251ae1ae6fb2256 */
#if BIND_Socket_INITIALIZE
mrb_value
mrb_APR_Socket_initialize(mrb_state* mrb, mrb_value self) {
  mrb_raise(mrb, E_NOMETHOD_ERROR, "No initializer defined");
/* 
  apr_socket_t* native_object = (apr_socket_t*)calloc(1, sizeof(apr_socket_t));
  mruby_gift_apr_socket_t_data_ptr(self, native_object);
  return self;
*/
}
#endif
/* MRUBY_BINDING_END */


void mrb_APR_Socket_init(mrb_state* mrb) {
  static int initialized = 0;
  if (initialized) return;
  else initialized = 1;

/* MRUBY_BINDING: pre_class_definition */
/* sha: user_defined */

/* MRUBY_BINDING_END */

/* MRUBY_BINDING: Socket::class_definition */
/* sha: e20a33894c1f1d6c986b1cf41b73485df726f94faba4c31b301367241f68ea14 */
  struct RClass* Socket_class = mrb_define_class_under(mrb, APR_module(mrb), "Socket", mrb->object_class);
  MRB_SET_INSTANCE_TT(Socket_class, MRB_TT_DATA);
/* MRUBY_BINDING_END */

/* MRUBY_BINDING: Socket::pre_class_method_definitions */
/* sha: user_defined */

/* MRUBY_BINDING_END */

/* MRUBY_BINDING: Socket::class_method_definitions */
/* sha: 17dc079606987449ed036a7604e89d7807d71d02e8711d018a006bcba1bc9533 */
#if BIND_Socket_INITIALIZE
  mrb_define_method(mrb, Socket_class, "initialize", mrb_APR_Socket_initialize, MRB_ARGS_NONE());
#endif
/* MRUBY_BINDING_END */



/* MRUBY_BINDING: Socket::post_class_definition */
/* sha: user_defined */

/* MRUBY_BINDING_END */
}

/* MRUBY_BINDING: footer */
/* sha: user_defined */

/* MRUBY_BINDING_END */
#endif
