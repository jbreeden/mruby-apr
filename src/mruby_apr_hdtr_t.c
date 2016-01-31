/*
 * apr_hdtr_t
 * Defined in file apr_network_io.h @ line 195
 */

#include "mruby_APR.h"

#if BIND_AprHdtrT_TYPE

/* MRUBY_BINDING: header */
/* sha: user_defined */

/* MRUBY_BINDING_END */

/* MRUBY_BINDING: AprHdtrT::initialize */
/* sha: 8e08591a577f1a754bd817eff2345cc9396f3832c10907801f1a175f45927dad */
#if BIND_AprHdtrT_INITIALIZE
mrb_value
mrb_APR_AprHdtrT_initialize(mrb_state* mrb, mrb_value self) {
  mrb_raise(mrb, E_NOMETHOD_ERROR, "No initializer defined");
/* 
  apr_hdtr_t* native_object = (apr_hdtr_t*)calloc(1, sizeof(apr_hdtr_t));
  mruby_gift_apr_hdtr_t_data_ptr(self, native_object);
  return self;
*/
}
#endif
/* MRUBY_BINDING_END */

/*
 * Fields
 */

/* MRUBY_BINDING: AprHdtrT::headers_reader */
/* sha: 678a4a5984ed0c93a9bb54ff836db83f9c6b032b0842eabc71717976908a167b */
#if BIND_AprHdtrT_headers_FIELD_READER
mrb_value
mrb_APR_AprHdtrT_get_headers(mrb_state* mrb, mrb_value self) {
  apr_hdtr_t * native_self = mruby_unbox_apr_hdtr_t(self);

  struct iovec * native_headers = native_self->headers;

  mrb_value headers = TODO_mruby_box_iovec_PTR(mrb, native_headers);

  return headers;
}
#endif
/* MRUBY_BINDING_END */

/* MRUBY_BINDING: AprHdtrT::headers_writer */
/* sha: 9106018d89af3d5667c7dfd446161929ace01fe1476cff839486028906b23b67 */
#if BIND_AprHdtrT_headers_FIELD_WRITER
mrb_value
mrb_APR_AprHdtrT_set_headers(mrb_state* mrb, mrb_value self) {
  apr_hdtr_t * native_self = mruby_unbox_apr_hdtr_t(self);
  mrb_value headers;

  mrb_get_args(mrb, "o", &headers);

  /* type checking */
  TODO_type_check_iovec_PTR(headers);

  struct iovec * native_headers = TODO_mruby_unbox_iovec_PTR(headers);

  native_self->headers = native_headers;
  
  mrb_value value_as_mrb_value;
  mrb_get_args(mrb, "o", &value_as_mrb_value);
  return value_as_mrb_value;
}
#endif
/* MRUBY_BINDING_END */

/* MRUBY_BINDING: AprHdtrT::numheaders_reader */
/* sha: a80b144d516b509800bfc935d8c1da15f65fc3d7385a3ebf52a24b70cab65dfb */
#if BIND_AprHdtrT_numheaders_FIELD_READER
mrb_value
mrb_APR_AprHdtrT_get_numheaders(mrb_state* mrb, mrb_value self) {
  apr_hdtr_t * native_self = mruby_unbox_apr_hdtr_t(self);

  int native_numheaders = native_self->numheaders;

  mrb_value numheaders = mrb_fixnum_value(native_numheaders);

  return numheaders;
}
#endif
/* MRUBY_BINDING_END */

/* MRUBY_BINDING: AprHdtrT::numheaders_writer */
/* sha: 950d87f8fdd074383871cee43d5af0421ffa5a349782ce2b1030c524e2809b02 */
#if BIND_AprHdtrT_numheaders_FIELD_WRITER
mrb_value
mrb_APR_AprHdtrT_set_numheaders(mrb_state* mrb, mrb_value self) {
  apr_hdtr_t * native_self = mruby_unbox_apr_hdtr_t(self);
  mrb_int native_numheaders;

  mrb_get_args(mrb, "i", &native_numheaders);

  native_self->numheaders = native_numheaders;
  
  mrb_value value_as_mrb_value;
  mrb_get_args(mrb, "o", &value_as_mrb_value);
  return value_as_mrb_value;
}
#endif
/* MRUBY_BINDING_END */

/* MRUBY_BINDING: AprHdtrT::trailers_reader */
/* sha: a3ba1ba3c7cb62241c9b1178b185ba9ca50de1f89af79b8090594c423cb05296 */
#if BIND_AprHdtrT_trailers_FIELD_READER
mrb_value
mrb_APR_AprHdtrT_get_trailers(mrb_state* mrb, mrb_value self) {
  apr_hdtr_t * native_self = mruby_unbox_apr_hdtr_t(self);

  struct iovec * native_trailers = native_self->trailers;

  mrb_value trailers = TODO_mruby_box_iovec_PTR(mrb, native_trailers);

  return trailers;
}
#endif
/* MRUBY_BINDING_END */

/* MRUBY_BINDING: AprHdtrT::trailers_writer */
/* sha: d22e35fa5cc373eb9653e2f2394db271116ad7eb107153f43637d82ca18193f5 */
#if BIND_AprHdtrT_trailers_FIELD_WRITER
mrb_value
mrb_APR_AprHdtrT_set_trailers(mrb_state* mrb, mrb_value self) {
  apr_hdtr_t * native_self = mruby_unbox_apr_hdtr_t(self);
  mrb_value trailers;

  mrb_get_args(mrb, "o", &trailers);

  /* type checking */
  TODO_type_check_iovec_PTR(trailers);

  struct iovec * native_trailers = TODO_mruby_unbox_iovec_PTR(trailers);

  native_self->trailers = native_trailers;
  
  mrb_value value_as_mrb_value;
  mrb_get_args(mrb, "o", &value_as_mrb_value);
  return value_as_mrb_value;
}
#endif
/* MRUBY_BINDING_END */

/* MRUBY_BINDING: AprHdtrT::numtrailers_reader */
/* sha: 72aeb0ff6dc8efb19a06905e1d1130c3216790e632591f62bf72e6904ec8337f */
#if BIND_AprHdtrT_numtrailers_FIELD_READER
mrb_value
mrb_APR_AprHdtrT_get_numtrailers(mrb_state* mrb, mrb_value self) {
  apr_hdtr_t * native_self = mruby_unbox_apr_hdtr_t(self);

  int native_numtrailers = native_self->numtrailers;

  mrb_value numtrailers = mrb_fixnum_value(native_numtrailers);

  return numtrailers;
}
#endif
/* MRUBY_BINDING_END */

/* MRUBY_BINDING: AprHdtrT::numtrailers_writer */
/* sha: 5908f5ebc2b5ba12c8f0420230de0d49ab2ee1313ff41f77fc9162fc9bc25479 */
#if BIND_AprHdtrT_numtrailers_FIELD_WRITER
mrb_value
mrb_APR_AprHdtrT_set_numtrailers(mrb_state* mrb, mrb_value self) {
  apr_hdtr_t * native_self = mruby_unbox_apr_hdtr_t(self);
  mrb_int native_numtrailers;

  mrb_get_args(mrb, "i", &native_numtrailers);

  native_self->numtrailers = native_numtrailers;
  
  mrb_value value_as_mrb_value;
  mrb_get_args(mrb, "o", &value_as_mrb_value);
  return value_as_mrb_value;
}
#endif
/* MRUBY_BINDING_END */


void mrb_APR_AprHdtrT_init(mrb_state* mrb) {
  static int initialized = 0;
  if (initialized) return;
  else initialized = 1;

/* MRUBY_BINDING: pre_class_definition */
/* sha: user_defined */

/* MRUBY_BINDING_END */

/* MRUBY_BINDING: AprHdtrT::class_definition */
/* sha: 2ed14d039e4e4960d4750966e9939d49b3959db798f54e6bc5f03e20c5ac66c9 */
  struct RClass* AprHdtrT_class = mrb_define_class_under(mrb, APR_module(mrb), "AprHdtrT", mrb->object_class);
  MRB_SET_INSTANCE_TT(AprHdtrT_class, MRB_TT_DATA);
/* MRUBY_BINDING_END */

/* MRUBY_BINDING: AprHdtrT::pre_class_method_definitions */
/* sha: user_defined */

/* MRUBY_BINDING_END */

/* MRUBY_BINDING: AprHdtrT::class_method_definitions */
/* sha: d909f2b81207707c2204118485aa85c4cbb78db0a22fb4aa92326f5184d8a6d8 */
#if BIND_AprHdtrT_INITIALIZE
  mrb_define_method(mrb, AprHdtrT_class, "initialize", mrb_APR_AprHdtrT_initialize, MRB_ARGS_NONE());
#endif
/* MRUBY_BINDING_END */

/* MRUBY_BINDING: AprHdtrT::pre_attr_definitions */
/* sha: user_defined */

/* MRUBY_BINDING_END */

/* MRUBY_BINDING: AprHdtrT::attr_definitions */
/* sha: 5f170abe3a69905945a3292f4c86b936e96ce92903026eaf4686b851cd0bb81e */
  /*
   * Fields
   */
#if BIND_AprHdtrT_headers_FIELD_READER
  mrb_define_method(mrb, AprHdtrT_class, "headers", mrb_APR_AprHdtrT_get_headers, MRB_ARGS_ARG(0, 0));
#endif
#if BIND_AprHdtrT_headers_FIELD_WRITER
  mrb_define_method(mrb, AprHdtrT_class, "headers=", mrb_APR_AprHdtrT_set_headers, MRB_ARGS_ARG(1, 0));
#endif
#if BIND_AprHdtrT_numheaders_FIELD_READER
  mrb_define_method(mrb, AprHdtrT_class, "numheaders", mrb_APR_AprHdtrT_get_numheaders, MRB_ARGS_ARG(0, 0));
#endif
#if BIND_AprHdtrT_numheaders_FIELD_WRITER
  mrb_define_method(mrb, AprHdtrT_class, "numheaders=", mrb_APR_AprHdtrT_set_numheaders, MRB_ARGS_ARG(1, 0));
#endif
#if BIND_AprHdtrT_trailers_FIELD_READER
  mrb_define_method(mrb, AprHdtrT_class, "trailers", mrb_APR_AprHdtrT_get_trailers, MRB_ARGS_ARG(0, 0));
#endif
#if BIND_AprHdtrT_trailers_FIELD_WRITER
  mrb_define_method(mrb, AprHdtrT_class, "trailers=", mrb_APR_AprHdtrT_set_trailers, MRB_ARGS_ARG(1, 0));
#endif
#if BIND_AprHdtrT_numtrailers_FIELD_READER
  mrb_define_method(mrb, AprHdtrT_class, "numtrailers", mrb_APR_AprHdtrT_get_numtrailers, MRB_ARGS_ARG(0, 0));
#endif
#if BIND_AprHdtrT_numtrailers_FIELD_WRITER
  mrb_define_method(mrb, AprHdtrT_class, "numtrailers=", mrb_APR_AprHdtrT_set_numtrailers, MRB_ARGS_ARG(1, 0));
#endif
/* MRUBY_BINDING_END */


/* MRUBY_BINDING: AprHdtrT::post_class_definition */
/* sha: user_defined */

/* MRUBY_BINDING_END */
}

/* MRUBY_BINDING: footer */
/* sha: user_defined */

/* MRUBY_BINDING_END */
#endif
