/*
 * apr_sockaddr_t
 * Defined in file apr_network_io.h @ line 207
 */

#include "mruby_APR.h"

#if BIND_Sockaddr_TYPE

/* MRUBY_BINDING: header */
/* sha: user_defined */

/* MRUBY_BINDING_END */

/* MRUBY_BINDING: Sockaddr::initialize */
/* sha: cbeb84a851e4d1cb2f93cc00c6d89f2c9fc1c5e0a5e929f35f25a122c7db55e6 */
#if BIND_Sockaddr_INITIALIZE
mrb_value
mrb_APR_Sockaddr_initialize(mrb_state* mrb, mrb_value self) {
  mrb_raise(mrb, E_NOMETHOD_ERROR, "No initializer defined");
/* 
  apr_sockaddr_t* native_object = (apr_sockaddr_t*)calloc(1, sizeof(apr_sockaddr_t));
  mruby_gift_apr_sockaddr_t_data_ptr(self, native_object);
  return self;
*/
}
#endif
/* MRUBY_BINDING_END */

/*
 * Fields
 */

/* MRUBY_BINDING: Sockaddr::pool_reader */
/* sha: 577a821eb6dfb127874d42b34d25bc01a67c5b687bb8b9c143911d5d144f9126 */
#if BIND_Sockaddr_pool_FIELD_READER
mrb_value
mrb_APR_Sockaddr_get_pool(mrb_state* mrb, mrb_value self) {
  apr_sockaddr_t * native_self = mruby_unbox_apr_sockaddr_t(self);

  apr_pool_t * native_pool = native_self->pool;

  mrb_value pool = (native_pool == NULL ? mrb_nil_value() : mruby_box_apr_pool_t(mrb, native_pool));

  return pool;
}
#endif
/* MRUBY_BINDING_END */

/* MRUBY_BINDING: Sockaddr::pool_writer */
/* sha: 2aa84b83dfedcfc332a6b2dd6768e2304adebf6af39c539643e30210554401d9 */
#if BIND_Sockaddr_pool_FIELD_WRITER
mrb_value
mrb_APR_Sockaddr_set_pool(mrb_state* mrb, mrb_value self) {
  apr_sockaddr_t * native_self = mruby_unbox_apr_sockaddr_t(self);
  mrb_value pool;

  mrb_get_args(mrb, "o", &pool);

  /* type checking */
  if (!mrb_obj_is_kind_of(mrb, pool, Pool_class(mrb))) {
    mrb_raise(mrb, E_TYPE_ERROR, "Pool expected");
    return mrb_nil_value();
  }

  apr_pool_t * native_pool = (mrb_nil_p(pool) ? NULL : mruby_unbox_apr_pool_t(pool));

  native_self->pool = native_pool;
  
  mrb_value value_as_mrb_value;
  mrb_get_args(mrb, "o", &value_as_mrb_value);
  return value_as_mrb_value;
}
#endif
/* MRUBY_BINDING_END */

/* MRUBY_BINDING: Sockaddr::hostname_reader */
/* sha: 3e6e6ba56f14b76822adb459066c71d9a4c04a94d98e2444b03a4f74fd4b9b30 */
#if BIND_Sockaddr_hostname_FIELD_READER
mrb_value
mrb_APR_Sockaddr_get_hostname(mrb_state* mrb, mrb_value self) {
  apr_sockaddr_t * native_self = mruby_unbox_apr_sockaddr_t(self);

  char * native_hostname = native_self->hostname;

  mrb_value hostname = TODO_mruby_box_char_PTR(mrb, native_hostname);

  return hostname;
}
#endif
/* MRUBY_BINDING_END */

/* MRUBY_BINDING: Sockaddr::hostname_writer */
/* sha: a1b2fcc158412088f8d8d6ad9918b7a78292ae9c000715ef94de6c5c6095de7c */
#if BIND_Sockaddr_hostname_FIELD_WRITER
mrb_value
mrb_APR_Sockaddr_set_hostname(mrb_state* mrb, mrb_value self) {
  apr_sockaddr_t * native_self = mruby_unbox_apr_sockaddr_t(self);
  mrb_value hostname;

  mrb_get_args(mrb, "o", &hostname);

  /* type checking */
  TODO_type_check_char_PTR(hostname);

  char * native_hostname = TODO_mruby_unbox_char_PTR(hostname);

  native_self->hostname = native_hostname;
  
  mrb_value value_as_mrb_value;
  mrb_get_args(mrb, "o", &value_as_mrb_value);
  return value_as_mrb_value;
}
#endif
/* MRUBY_BINDING_END */

/* MRUBY_BINDING: Sockaddr::servname_reader */
/* sha: becf99741427d48d64b06c1d446da1d2e9a08297782aac9ddc2671991a42b7d8 */
#if BIND_Sockaddr_servname_FIELD_READER
mrb_value
mrb_APR_Sockaddr_get_servname(mrb_state* mrb, mrb_value self) {
  apr_sockaddr_t * native_self = mruby_unbox_apr_sockaddr_t(self);

  char * native_servname = native_self->servname;

  mrb_value servname = TODO_mruby_box_char_PTR(mrb, native_servname);

  return servname;
}
#endif
/* MRUBY_BINDING_END */

/* MRUBY_BINDING: Sockaddr::servname_writer */
/* sha: a90f7c4f0d0663a274088b76da34c901817ddec4aeca97eeb83fdaccd2745b19 */
#if BIND_Sockaddr_servname_FIELD_WRITER
mrb_value
mrb_APR_Sockaddr_set_servname(mrb_state* mrb, mrb_value self) {
  apr_sockaddr_t * native_self = mruby_unbox_apr_sockaddr_t(self);
  mrb_value servname;

  mrb_get_args(mrb, "o", &servname);

  /* type checking */
  TODO_type_check_char_PTR(servname);

  char * native_servname = TODO_mruby_unbox_char_PTR(servname);

  native_self->servname = native_servname;
  
  mrb_value value_as_mrb_value;
  mrb_get_args(mrb, "o", &value_as_mrb_value);
  return value_as_mrb_value;
}
#endif
/* MRUBY_BINDING_END */

/* MRUBY_BINDING: Sockaddr::port_reader */
/* sha: 7062fb53d73e63bfe3dfd3abf55847a3133c0016b61f352e5ef8493d2d112f90 */
#if BIND_Sockaddr_port_FIELD_READER
mrb_value
mrb_APR_Sockaddr_get_port(mrb_state* mrb, mrb_value self) {
  apr_sockaddr_t * native_self = mruby_unbox_apr_sockaddr_t(self);

  apr_port_t native_port = native_self->port;

  mrb_value port = mrb_fixnum_value(native_port);

  return port;
}
#endif
/* MRUBY_BINDING_END */

/* MRUBY_BINDING: Sockaddr::port_writer */
/* sha: 9db3530bfdaf23a132255dfc1eac9417eaf00bb29dbb39c45546487cf835a194 */
#if BIND_Sockaddr_port_FIELD_WRITER
mrb_value
mrb_APR_Sockaddr_set_port(mrb_state* mrb, mrb_value self) {
  apr_sockaddr_t * native_self = mruby_unbox_apr_sockaddr_t(self);
  mrb_int native_port;

  mrb_get_args(mrb, "i", &native_port);

  native_self->port = native_port;
  
  mrb_value value_as_mrb_value;
  mrb_get_args(mrb, "o", &value_as_mrb_value);
  return value_as_mrb_value;
}
#endif
/* MRUBY_BINDING_END */

/* MRUBY_BINDING: Sockaddr::family_reader */
/* sha: 72cee73231a2fbdbb8f0f85982935bc63b5594f0bb9ea625e5b56d6993b8bcd1 */
#if BIND_Sockaddr_family_FIELD_READER
mrb_value
mrb_APR_Sockaddr_get_family(mrb_state* mrb, mrb_value self) {
  apr_sockaddr_t * native_self = mruby_unbox_apr_sockaddr_t(self);

  apr_int32_t native_family = native_self->family;

  mrb_value family = mrb_fixnum_value(native_family);

  return family;
}
#endif
/* MRUBY_BINDING_END */

/* MRUBY_BINDING: Sockaddr::family_writer */
/* sha: 6aca0a9f2862df3c3c902f05f082365a6dbcb3f26f8f2f55c11de9e09c1fefaa */
#if BIND_Sockaddr_family_FIELD_WRITER
mrb_value
mrb_APR_Sockaddr_set_family(mrb_state* mrb, mrb_value self) {
  apr_sockaddr_t * native_self = mruby_unbox_apr_sockaddr_t(self);
  mrb_int native_family;

  mrb_get_args(mrb, "i", &native_family);

  native_self->family = native_family;
  
  mrb_value value_as_mrb_value;
  mrb_get_args(mrb, "o", &value_as_mrb_value);
  return value_as_mrb_value;
}
#endif
/* MRUBY_BINDING_END */

/* MRUBY_BINDING: Sockaddr::salen_reader */
/* sha: e72c668b3cb899312040b6db6af0d717d29b80d8dd5a27c604c8f48936d85159 */
#if BIND_Sockaddr_salen_FIELD_READER
mrb_value
mrb_APR_Sockaddr_get_salen(mrb_state* mrb, mrb_value self) {
  apr_sockaddr_t * native_self = mruby_unbox_apr_sockaddr_t(self);

  apr_socklen_t native_salen = native_self->salen;

  mrb_value salen = TODO_mruby_box_apr_socklen_t(mrb, native_salen);

  return salen;
}
#endif
/* MRUBY_BINDING_END */

/* MRUBY_BINDING: Sockaddr::salen_writer */
/* sha: 1a7ac1148cd8f95eb98884304095ee13fdf172a6b763c4d70c77d7026ddccf15 */
#if BIND_Sockaddr_salen_FIELD_WRITER
mrb_value
mrb_APR_Sockaddr_set_salen(mrb_state* mrb, mrb_value self) {
  apr_sockaddr_t * native_self = mruby_unbox_apr_sockaddr_t(self);
  mrb_value salen;

  mrb_get_args(mrb, "o", &salen);

  /* type checking */
  TODO_type_check_apr_socklen_t(salen);

  apr_socklen_t native_salen = TODO_mruby_unbox_apr_socklen_t(salen);

  native_self->salen = native_salen;
  
  mrb_value value_as_mrb_value;
  mrb_get_args(mrb, "o", &value_as_mrb_value);
  return value_as_mrb_value;
}
#endif
/* MRUBY_BINDING_END */

/* MRUBY_BINDING: Sockaddr::ipaddr_len_reader */
/* sha: cfa224943e501fa97cddb2b981a497f88ac5da3dc95a58b10a0ada89a9ae5c44 */
#if BIND_Sockaddr_ipaddr_len_FIELD_READER
mrb_value
mrb_APR_Sockaddr_get_ipaddr_len(mrb_state* mrb, mrb_value self) {
  apr_sockaddr_t * native_self = mruby_unbox_apr_sockaddr_t(self);

  int native_ipaddr_len = native_self->ipaddr_len;

  mrb_value ipaddr_len = mrb_fixnum_value(native_ipaddr_len);

  return ipaddr_len;
}
#endif
/* MRUBY_BINDING_END */

/* MRUBY_BINDING: Sockaddr::ipaddr_len_writer */
/* sha: bb834d30f14c26ae53e24894401ab49b3ddea9f3f71ce1a407c3bd5963a9ca61 */
#if BIND_Sockaddr_ipaddr_len_FIELD_WRITER
mrb_value
mrb_APR_Sockaddr_set_ipaddr_len(mrb_state* mrb, mrb_value self) {
  apr_sockaddr_t * native_self = mruby_unbox_apr_sockaddr_t(self);
  mrb_int native_ipaddr_len;

  mrb_get_args(mrb, "i", &native_ipaddr_len);

  native_self->ipaddr_len = native_ipaddr_len;
  
  mrb_value value_as_mrb_value;
  mrb_get_args(mrb, "o", &value_as_mrb_value);
  return value_as_mrb_value;
}
#endif
/* MRUBY_BINDING_END */

/* MRUBY_BINDING: Sockaddr::addr_str_len_reader */
/* sha: 12f8581fbf2ad0b0d567782998cfb22d39249aa69f35479c5dc7ec3477e7243e */
#if BIND_Sockaddr_addr_str_len_FIELD_READER
mrb_value
mrb_APR_Sockaddr_get_addr_str_len(mrb_state* mrb, mrb_value self) {
  apr_sockaddr_t * native_self = mruby_unbox_apr_sockaddr_t(self);

  int native_addr_str_len = native_self->addr_str_len;

  mrb_value addr_str_len = mrb_fixnum_value(native_addr_str_len);

  return addr_str_len;
}
#endif
/* MRUBY_BINDING_END */

/* MRUBY_BINDING: Sockaddr::addr_str_len_writer */
/* sha: 5a0d99e0f8142501d6031d73a3c1c1694d7afe80d6cf956749e52f04ea7b5e5f */
#if BIND_Sockaddr_addr_str_len_FIELD_WRITER
mrb_value
mrb_APR_Sockaddr_set_addr_str_len(mrb_state* mrb, mrb_value self) {
  apr_sockaddr_t * native_self = mruby_unbox_apr_sockaddr_t(self);
  mrb_int native_addr_str_len;

  mrb_get_args(mrb, "i", &native_addr_str_len);

  native_self->addr_str_len = native_addr_str_len;
  
  mrb_value value_as_mrb_value;
  mrb_get_args(mrb, "o", &value_as_mrb_value);
  return value_as_mrb_value;
}
#endif
/* MRUBY_BINDING_END */

/* MRUBY_BINDING: Sockaddr::ipaddr_ptr_reader */
/* sha: b888eaf1978d9b4e27cb0a756a465ae1d7c028aabae7ffe15e2437a8e444fcb7 */
#if BIND_Sockaddr_ipaddr_ptr_FIELD_READER
mrb_value
mrb_APR_Sockaddr_get_ipaddr_ptr(mrb_state* mrb, mrb_value self) {
  apr_sockaddr_t * native_self = mruby_unbox_apr_sockaddr_t(self);

  void * native_ipaddr_ptr = native_self->ipaddr_ptr;

  mrb_value ipaddr_ptr = TODO_mruby_box_void_PTR(mrb, native_ipaddr_ptr);

  return ipaddr_ptr;
}
#endif
/* MRUBY_BINDING_END */

/* MRUBY_BINDING: Sockaddr::ipaddr_ptr_writer */
/* sha: bca7e1031087066db75880430d211d57c046009621f7874a1cf57090c131564a */
#if BIND_Sockaddr_ipaddr_ptr_FIELD_WRITER
mrb_value
mrb_APR_Sockaddr_set_ipaddr_ptr(mrb_state* mrb, mrb_value self) {
  apr_sockaddr_t * native_self = mruby_unbox_apr_sockaddr_t(self);
  mrb_value ipaddr_ptr;

  mrb_get_args(mrb, "o", &ipaddr_ptr);

  /* type checking */
  TODO_type_check_void_PTR(ipaddr_ptr);

  void * native_ipaddr_ptr = TODO_mruby_unbox_void_PTR(ipaddr_ptr);

  native_self->ipaddr_ptr = native_ipaddr_ptr;
  
  mrb_value value_as_mrb_value;
  mrb_get_args(mrb, "o", &value_as_mrb_value);
  return value_as_mrb_value;
}
#endif
/* MRUBY_BINDING_END */

/* MRUBY_BINDING: Sockaddr::next_reader */
/* sha: 6ed70f8a568c6cf9c1e4422873df54ee543342df0a9c255c2e39588048bbfc3d */
#if BIND_Sockaddr_next_FIELD_READER
mrb_value
mrb_APR_Sockaddr_get_next(mrb_state* mrb, mrb_value self) {
  apr_sockaddr_t * native_self = mruby_unbox_apr_sockaddr_t(self);

  apr_sockaddr_t * native_next = native_self->next;

  mrb_value next = (native_next == NULL ? mrb_nil_value() : mruby_box_apr_sockaddr_t(mrb, native_next));

  return next;
}
#endif
/* MRUBY_BINDING_END */

/* MRUBY_BINDING: Sockaddr::next_writer */
/* sha: e02fa5db1e2e1b549108f9e4659befb6ff7387bc50b095a9a6ff9da5360548e1 */
#if BIND_Sockaddr_next_FIELD_WRITER
mrb_value
mrb_APR_Sockaddr_set_next(mrb_state* mrb, mrb_value self) {
  apr_sockaddr_t * native_self = mruby_unbox_apr_sockaddr_t(self);
  mrb_value next;

  mrb_get_args(mrb, "o", &next);

  /* type checking */
  if (!mrb_obj_is_kind_of(mrb, next, Sockaddr_class(mrb))) {
    mrb_raise(mrb, E_TYPE_ERROR, "Sockaddr expected");
    return mrb_nil_value();
  }

  apr_sockaddr_t * native_next = (mrb_nil_p(next) ? NULL : mruby_unbox_apr_sockaddr_t(next));

  native_self->next = native_next;
  
  mrb_value value_as_mrb_value;
  mrb_get_args(mrb, "o", &value_as_mrb_value);
  return value_as_mrb_value;
}
#endif
/* MRUBY_BINDING_END */

/* MRUBY_BINDING: Sockaddr::sa_reader */
/* sha: 7092ed2f0cd84a754beace4f6e5defaaa0fcde231b146ebb8ce5ae64a9f9eaa7 */
#if BIND_Sockaddr_sa_FIELD_READER
mrb_value
mrb_APR_Sockaddr_get_sa(mrb_state* mrb, mrb_value self) {
  apr_sockaddr_t * native_self = mruby_unbox_apr_sockaddr_t(self);

  union (anonymous union at /usr/include/apr-1/apr_network_io.h:236:5) native_sa = native_self->sa;

  mrb_value sa = TODO_mruby_box_union_LPAREN_anonymous_union_at_/usr/include/apr-1/apr_network_io.h:236:5_RPAREN(mrb, native_sa);

  return sa;
}
#endif
/* MRUBY_BINDING_END */

/* MRUBY_BINDING: Sockaddr::sa_writer */
/* sha: 3721d2f76718d5c8781354629414bf033a3786a9dccd6b28d9486f232a0deefb */
#if BIND_Sockaddr_sa_FIELD_WRITER
mrb_value
mrb_APR_Sockaddr_set_sa(mrb_state* mrb, mrb_value self) {
  apr_sockaddr_t * native_self = mruby_unbox_apr_sockaddr_t(self);
  mrb_value sa;

  mrb_get_args(mrb, "o", &sa);

  /* type checking */
  TODO_type_check_union_LPAREN_anonymous_union_at_/usr/include/apr-1/apr_network_io.h:236:5_RPAREN(sa);

  union (anonymous union at /usr/include/apr-1/apr_network_io.h:236:5) native_sa = TODO_mruby_unbox_union_LPAREN_anonymous_union_at_/usr/include/apr-1/apr_network_io.h:236:5_RPAREN(sa);

  native_self->sa = native_sa;
  
  mrb_value value_as_mrb_value;
  mrb_get_args(mrb, "o", &value_as_mrb_value);
  return value_as_mrb_value;
}
#endif
/* MRUBY_BINDING_END */


void mrb_APR_Sockaddr_init(mrb_state* mrb) {
  static int initialized = 0;
  if (initialized) return;
  else initialized = 1;

/* MRUBY_BINDING: pre_class_definition */
/* sha: user_defined */

/* MRUBY_BINDING_END */

/* MRUBY_BINDING: Sockaddr::class_definition */
/* sha: c19c8ce2a34389f865038be1d9ac1c11c51fadd5e551192afff81b154cbb71c6 */
  struct RClass* Sockaddr_class = mrb_define_class_under(mrb, APR_module(mrb), "Sockaddr", mrb->object_class);
  MRB_SET_INSTANCE_TT(Sockaddr_class, MRB_TT_DATA);
/* MRUBY_BINDING_END */

/* MRUBY_BINDING: Sockaddr::pre_class_method_definitions */
/* sha: user_defined */

/* MRUBY_BINDING_END */

/* MRUBY_BINDING: Sockaddr::class_method_definitions */
/* sha: 42bf15baf47a040a2ce1da41b7db545209353f509ab6d89f69222b30b0ef6f58 */
#if BIND_Sockaddr_INITIALIZE
  mrb_define_method(mrb, Sockaddr_class, "initialize", mrb_APR_Sockaddr_initialize, MRB_ARGS_NONE());
#endif
/* MRUBY_BINDING_END */

/* MRUBY_BINDING: Sockaddr::pre_attr_definitions */
/* sha: user_defined */

/* MRUBY_BINDING_END */

/* MRUBY_BINDING: Sockaddr::attr_definitions */
/* sha: 88a0b2c5c94fd0ed6e57e879f09db3f88c9f4415dded5397259241f0be6a3fee */
  /*
   * Fields
   */
#if BIND_Sockaddr_pool_FIELD_READER
  mrb_define_method(mrb, Sockaddr_class, "pool", mrb_APR_Sockaddr_get_pool, MRB_ARGS_ARG(0, 0));
#endif
#if BIND_Sockaddr_pool_FIELD_WRITER
  mrb_define_method(mrb, Sockaddr_class, "pool=", mrb_APR_Sockaddr_set_pool, MRB_ARGS_ARG(1, 0));
#endif
#if BIND_Sockaddr_hostname_FIELD_READER
  mrb_define_method(mrb, Sockaddr_class, "hostname", mrb_APR_Sockaddr_get_hostname, MRB_ARGS_ARG(0, 0));
#endif
#if BIND_Sockaddr_hostname_FIELD_WRITER
  mrb_define_method(mrb, Sockaddr_class, "hostname=", mrb_APR_Sockaddr_set_hostname, MRB_ARGS_ARG(1, 0));
#endif
#if BIND_Sockaddr_servname_FIELD_READER
  mrb_define_method(mrb, Sockaddr_class, "servname", mrb_APR_Sockaddr_get_servname, MRB_ARGS_ARG(0, 0));
#endif
#if BIND_Sockaddr_servname_FIELD_WRITER
  mrb_define_method(mrb, Sockaddr_class, "servname=", mrb_APR_Sockaddr_set_servname, MRB_ARGS_ARG(1, 0));
#endif
#if BIND_Sockaddr_port_FIELD_READER
  mrb_define_method(mrb, Sockaddr_class, "port", mrb_APR_Sockaddr_get_port, MRB_ARGS_ARG(0, 0));
#endif
#if BIND_Sockaddr_port_FIELD_WRITER
  mrb_define_method(mrb, Sockaddr_class, "port=", mrb_APR_Sockaddr_set_port, MRB_ARGS_ARG(1, 0));
#endif
#if BIND_Sockaddr_family_FIELD_READER
  mrb_define_method(mrb, Sockaddr_class, "family", mrb_APR_Sockaddr_get_family, MRB_ARGS_ARG(0, 0));
#endif
#if BIND_Sockaddr_family_FIELD_WRITER
  mrb_define_method(mrb, Sockaddr_class, "family=", mrb_APR_Sockaddr_set_family, MRB_ARGS_ARG(1, 0));
#endif
#if BIND_Sockaddr_salen_FIELD_READER
  mrb_define_method(mrb, Sockaddr_class, "salen", mrb_APR_Sockaddr_get_salen, MRB_ARGS_ARG(0, 0));
#endif
#if BIND_Sockaddr_salen_FIELD_WRITER
  mrb_define_method(mrb, Sockaddr_class, "salen=", mrb_APR_Sockaddr_set_salen, MRB_ARGS_ARG(1, 0));
#endif
#if BIND_Sockaddr_ipaddr_len_FIELD_READER
  mrb_define_method(mrb, Sockaddr_class, "ipaddr_len", mrb_APR_Sockaddr_get_ipaddr_len, MRB_ARGS_ARG(0, 0));
#endif
#if BIND_Sockaddr_ipaddr_len_FIELD_WRITER
  mrb_define_method(mrb, Sockaddr_class, "ipaddr_len=", mrb_APR_Sockaddr_set_ipaddr_len, MRB_ARGS_ARG(1, 0));
#endif
#if BIND_Sockaddr_addr_str_len_FIELD_READER
  mrb_define_method(mrb, Sockaddr_class, "addr_str_len", mrb_APR_Sockaddr_get_addr_str_len, MRB_ARGS_ARG(0, 0));
#endif
#if BIND_Sockaddr_addr_str_len_FIELD_WRITER
  mrb_define_method(mrb, Sockaddr_class, "addr_str_len=", mrb_APR_Sockaddr_set_addr_str_len, MRB_ARGS_ARG(1, 0));
#endif
#if BIND_Sockaddr_ipaddr_ptr_FIELD_READER
  mrb_define_method(mrb, Sockaddr_class, "ipaddr_ptr", mrb_APR_Sockaddr_get_ipaddr_ptr, MRB_ARGS_ARG(0, 0));
#endif
#if BIND_Sockaddr_ipaddr_ptr_FIELD_WRITER
  mrb_define_method(mrb, Sockaddr_class, "ipaddr_ptr=", mrb_APR_Sockaddr_set_ipaddr_ptr, MRB_ARGS_ARG(1, 0));
#endif
#if BIND_Sockaddr_next_FIELD_READER
  mrb_define_method(mrb, Sockaddr_class, "next", mrb_APR_Sockaddr_get_next, MRB_ARGS_ARG(0, 0));
#endif
#if BIND_Sockaddr_next_FIELD_WRITER
  mrb_define_method(mrb, Sockaddr_class, "next=", mrb_APR_Sockaddr_set_next, MRB_ARGS_ARG(1, 0));
#endif
#if BIND_Sockaddr_sa_FIELD_READER
  mrb_define_method(mrb, Sockaddr_class, "sa", mrb_APR_Sockaddr_get_sa, MRB_ARGS_ARG(0, 0));
#endif
#if BIND_Sockaddr_sa_FIELD_WRITER
  mrb_define_method(mrb, Sockaddr_class, "sa=", mrb_APR_Sockaddr_set_sa, MRB_ARGS_ARG(1, 0));
#endif
/* MRUBY_BINDING_END */


/* MRUBY_BINDING: Sockaddr::post_class_definition */
/* sha: user_defined */

/* MRUBY_BINDING_END */
}

/* MRUBY_BINDING: footer */
/* sha: user_defined */

/* MRUBY_BINDING_END */
#endif
