/*
 * apr_hdtr_t
 * Defined in file apr_network_io.h @ line 195
 */

#include "mruby_APR.h"

#if BIND_Hdtr_TYPE

/* MRUBY_BINDING: header */
/* sha: user_defined */

/* MRUBY_BINDING_END */

/* MRUBY_BINDING: Hdtr::initialize */
/* sha: fda54cdab95c817f7406158c9f3ebb0db6342bd7d826dfa238d996a5272243f1 */
#if BIND_Hdtr_INITIALIZE
mrb_value
mrb_APR_Hdtr_initialize(mrb_state* mrb, mrb_value self) {
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

/* MRUBY_BINDING: Hdtr::headers_reader */
/* sha: 1ad63e64c709116a174f3aae498f58b52072573158d0559b69b8c56a94a7eddd */
#if BIND_Hdtr_headers_FIELD_READER
mrb_value
mrb_APR_Hdtr_get_headers(mrb_state* mrb, mrb_value self) {
  apr_hdtr_t * native_self = mruby_unbox_apr_hdtr_t(self);

  struct iovec * native_headers = native_self->headers;

  mrb_value headers = TODO_mruby_box_iovec_PTR(mrb, native_headers);

  return headers;
}
#endif
/* MRUBY_BINDING_END */

/* MRUBY_BINDING: Hdtr::headers_writer */
/* sha: fefc7fa4e5227e5b0e899d7b0b0eee4a238902ca1d8c28a002fa4a57826b35a9 */
#if BIND_Hdtr_headers_FIELD_WRITER
mrb_value
mrb_APR_Hdtr_set_headers(mrb_state* mrb, mrb_value self) {
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

/* MRUBY_BINDING: Hdtr::numheaders_reader */
/* sha: 5406e82ab1dd81e916238ede9743cb189008d55be003827c189c8da2549da758 */
#if BIND_Hdtr_numheaders_FIELD_READER
mrb_value
mrb_APR_Hdtr_get_numheaders(mrb_state* mrb, mrb_value self) {
  apr_hdtr_t * native_self = mruby_unbox_apr_hdtr_t(self);

  int native_numheaders = native_self->numheaders;

  mrb_value numheaders = mrb_fixnum_value(native_numheaders);

  return numheaders;
}
#endif
/* MRUBY_BINDING_END */

/* MRUBY_BINDING: Hdtr::numheaders_writer */
/* sha: 966ba36160f6d3a9c8d5b4d4b5a8677647574501989bf53c218f3f7cf4dd3218 */
#if BIND_Hdtr_numheaders_FIELD_WRITER
mrb_value
mrb_APR_Hdtr_set_numheaders(mrb_state* mrb, mrb_value self) {
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

/* MRUBY_BINDING: Hdtr::trailers_reader */
/* sha: 309d06cf4e4b50e2c56b7ca49980b1884aacfb6f191dab646414cb9014e55c95 */
#if BIND_Hdtr_trailers_FIELD_READER
mrb_value
mrb_APR_Hdtr_get_trailers(mrb_state* mrb, mrb_value self) {
  apr_hdtr_t * native_self = mruby_unbox_apr_hdtr_t(self);

  struct iovec * native_trailers = native_self->trailers;

  mrb_value trailers = TODO_mruby_box_iovec_PTR(mrb, native_trailers);

  return trailers;
}
#endif
/* MRUBY_BINDING_END */

/* MRUBY_BINDING: Hdtr::trailers_writer */
/* sha: 64ea9e7e8bc916589fbbb91d19d491a5c324cfa7759c8ea212a5e8a71919ad51 */
#if BIND_Hdtr_trailers_FIELD_WRITER
mrb_value
mrb_APR_Hdtr_set_trailers(mrb_state* mrb, mrb_value self) {
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

/* MRUBY_BINDING: Hdtr::numtrailers_reader */
/* sha: 777d8c011354dcce191373dfd717ef0b89a31e80ca50c06bdd5a68ddd505b97d */
#if BIND_Hdtr_numtrailers_FIELD_READER
mrb_value
mrb_APR_Hdtr_get_numtrailers(mrb_state* mrb, mrb_value self) {
  apr_hdtr_t * native_self = mruby_unbox_apr_hdtr_t(self);

  int native_numtrailers = native_self->numtrailers;

  mrb_value numtrailers = mrb_fixnum_value(native_numtrailers);

  return numtrailers;
}
#endif
/* MRUBY_BINDING_END */

/* MRUBY_BINDING: Hdtr::numtrailers_writer */
/* sha: 80c8c82426e9f58a8a4bc037ac150fb3d2ce3bd206e794c3ecb092161f1629fc */
#if BIND_Hdtr_numtrailers_FIELD_WRITER
mrb_value
mrb_APR_Hdtr_set_numtrailers(mrb_state* mrb, mrb_value self) {
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


void mrb_APR_Hdtr_init(mrb_state* mrb) {
  static int initialized = 0;
  if (initialized) return;
  else initialized = 1;

/* MRUBY_BINDING: pre_class_definition */
/* sha: user_defined */

/* MRUBY_BINDING_END */

/* MRUBY_BINDING: Hdtr::class_definition */
/* sha: 769e8e5048375c12e70259f83b43827931f490843b9149e943a8b7d4d1ac8af1 */
  struct RClass* Hdtr_class = mrb_define_class_under(mrb, APR_module(mrb), "Hdtr", mrb->object_class);
  MRB_SET_INSTANCE_TT(Hdtr_class, MRB_TT_DATA);
/* MRUBY_BINDING_END */

/* MRUBY_BINDING: Hdtr::pre_class_method_definitions */
/* sha: user_defined */

/* MRUBY_BINDING_END */

/* MRUBY_BINDING: Hdtr::class_method_definitions */
/* sha: b9f54e20633de8b5c73d2d4b155fb66a90fa47c071ff272a3e7a77d31a09bcb2 */
#if BIND_Hdtr_INITIALIZE
  mrb_define_method(mrb, Hdtr_class, "initialize", mrb_APR_Hdtr_initialize, MRB_ARGS_NONE());
#endif
/* MRUBY_BINDING_END */

/* MRUBY_BINDING: Hdtr::pre_attr_definitions */
/* sha: user_defined */

/* MRUBY_BINDING_END */

/* MRUBY_BINDING: Hdtr::attr_definitions */
/* sha: f3871177ce56653d12592d198c837a131292c22b8fb8a97e2c77b28420715711 */
  /*
   * Fields
   */
#if BIND_Hdtr_headers_FIELD_READER
  mrb_define_method(mrb, Hdtr_class, "headers", mrb_APR_Hdtr_get_headers, MRB_ARGS_ARG(0, 0));
#endif
#if BIND_Hdtr_headers_FIELD_WRITER
  mrb_define_method(mrb, Hdtr_class, "headers=", mrb_APR_Hdtr_set_headers, MRB_ARGS_ARG(1, 0));
#endif
#if BIND_Hdtr_numheaders_FIELD_READER
  mrb_define_method(mrb, Hdtr_class, "numheaders", mrb_APR_Hdtr_get_numheaders, MRB_ARGS_ARG(0, 0));
#endif
#if BIND_Hdtr_numheaders_FIELD_WRITER
  mrb_define_method(mrb, Hdtr_class, "numheaders=", mrb_APR_Hdtr_set_numheaders, MRB_ARGS_ARG(1, 0));
#endif
#if BIND_Hdtr_trailers_FIELD_READER
  mrb_define_method(mrb, Hdtr_class, "trailers", mrb_APR_Hdtr_get_trailers, MRB_ARGS_ARG(0, 0));
#endif
#if BIND_Hdtr_trailers_FIELD_WRITER
  mrb_define_method(mrb, Hdtr_class, "trailers=", mrb_APR_Hdtr_set_trailers, MRB_ARGS_ARG(1, 0));
#endif
#if BIND_Hdtr_numtrailers_FIELD_READER
  mrb_define_method(mrb, Hdtr_class, "numtrailers", mrb_APR_Hdtr_get_numtrailers, MRB_ARGS_ARG(0, 0));
#endif
#if BIND_Hdtr_numtrailers_FIELD_WRITER
  mrb_define_method(mrb, Hdtr_class, "numtrailers=", mrb_APR_Hdtr_set_numtrailers, MRB_ARGS_ARG(1, 0));
#endif
/* MRUBY_BINDING_END */


/* MRUBY_BINDING: Hdtr::post_class_definition */
/* sha: user_defined */

/* MRUBY_BINDING_END */
}

/* MRUBY_BINDING: footer */
/* sha: user_defined */

/* MRUBY_BINDING_END */
#endif
