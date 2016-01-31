/*
 * apr_sockaddr_t
 * Defined in file apr_network_io.h @ line 207
 */

#include "mruby_APR.h"

#if BIND_AprSockaddrT_TYPE

/* MRUBY_BINDING: header */
/* sha: user_defined */

/* MRUBY_BINDING_END */

/* MRUBY_BINDING: AprSockaddrT::initialize */
/* sha: 7c3b9841bf80b12656745d4067942f238038d16788991175eb6623cb4cf43d6d */
#if BIND_AprSockaddrT_INITIALIZE
mrb_value
mrb_APR_AprSockaddrT_initialize(mrb_state* mrb, mrb_value self) {
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

/* MRUBY_BINDING: AprSockaddrT::pool_reader */
/* sha: 5a7a14169b88745d7cc92465b27d4fb1e3541c8416fe4382936be7182bb1cf0c */
#if BIND_AprSockaddrT_pool_FIELD_READER
mrb_value
mrb_APR_AprSockaddrT_get_pool(mrb_state* mrb, mrb_value self) {
  apr_sockaddr_t * native_self = mruby_unbox_apr_sockaddr_t(self);

  apr_pool_t * native_pool = native_self->pool;

  mrb_value pool = (native_pool == NULL ? mrb_nil_value() : mruby_box_apr_pool_t(mrb, native_pool));

  return pool;
}
#endif
/* MRUBY_BINDING_END */

/* MRUBY_BINDING: AprSockaddrT::pool_writer */
/* sha: a91c4a67cb8314b4e10d35962bd6396daf618e110a2bdcd8402cfa253b3b2332 */
#if BIND_AprSockaddrT_pool_FIELD_WRITER
mrb_value
mrb_APR_AprSockaddrT_set_pool(mrb_state* mrb, mrb_value self) {
  apr_sockaddr_t * native_self = mruby_unbox_apr_sockaddr_t(self);
  mrb_value pool;

  mrb_get_args(mrb, "o", &pool);

  /* type checking */
  if (!mrb_obj_is_kind_of(mrb, pool, AprPoolT_class(mrb))) {
    mrb_raise(mrb, E_TYPE_ERROR, "AprPoolT expected");
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

/* MRUBY_BINDING: AprSockaddrT::hostname_reader */
/* sha: ca9a221fdaa2766d46ddc98d251911f7e480063bb4d17bf5590ab9b29bc83765 */
#if BIND_AprSockaddrT_hostname_FIELD_READER
mrb_value
mrb_APR_AprSockaddrT_get_hostname(mrb_state* mrb, mrb_value self) {
  apr_sockaddr_t * native_self = mruby_unbox_apr_sockaddr_t(self);

  char * native_hostname = native_self->hostname;

  mrb_value hostname = TODO_mruby_box_char_PTR(mrb, native_hostname);

  return hostname;
}
#endif
/* MRUBY_BINDING_END */

/* MRUBY_BINDING: AprSockaddrT::hostname_writer */
/* sha: a5223017a0488afc3230340c2f278ccc60d6a81ed5c4fa090010b0133aa865a4 */
#if BIND_AprSockaddrT_hostname_FIELD_WRITER
mrb_value
mrb_APR_AprSockaddrT_set_hostname(mrb_state* mrb, mrb_value self) {
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

/* MRUBY_BINDING: AprSockaddrT::servname_reader */
/* sha: b40b67a8ce8ef53e3f8b6da7986ca1a6239622ce477990bebe18ba7aad9db72e */
#if BIND_AprSockaddrT_servname_FIELD_READER
mrb_value
mrb_APR_AprSockaddrT_get_servname(mrb_state* mrb, mrb_value self) {
  apr_sockaddr_t * native_self = mruby_unbox_apr_sockaddr_t(self);

  char * native_servname = native_self->servname;

  mrb_value servname = TODO_mruby_box_char_PTR(mrb, native_servname);

  return servname;
}
#endif
/* MRUBY_BINDING_END */

/* MRUBY_BINDING: AprSockaddrT::servname_writer */
/* sha: 6495e040235001bde93f2181a844524c8b8485d82b164c5532418fcdc68e07c6 */
#if BIND_AprSockaddrT_servname_FIELD_WRITER
mrb_value
mrb_APR_AprSockaddrT_set_servname(mrb_state* mrb, mrb_value self) {
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

/* MRUBY_BINDING: AprSockaddrT::port_reader */
/* sha: 6fac2983d75b571752ca44897636dd5f44c59dcb194ee80050b8554737595937 */
#if BIND_AprSockaddrT_port_FIELD_READER
mrb_value
mrb_APR_AprSockaddrT_get_port(mrb_state* mrb, mrb_value self) {
  apr_sockaddr_t * native_self = mruby_unbox_apr_sockaddr_t(self);

  apr_port_t native_port = native_self->port;

  mrb_value port = mrb_fixnum_value(native_port);

  return port;
}
#endif
/* MRUBY_BINDING_END */

/* MRUBY_BINDING: AprSockaddrT::port_writer */
/* sha: dacdcc8f6fb0a57ba5618ccf602797cd43cc3af097afbd06ffbb69e6cf3b7c27 */
#if BIND_AprSockaddrT_port_FIELD_WRITER
mrb_value
mrb_APR_AprSockaddrT_set_port(mrb_state* mrb, mrb_value self) {
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

/* MRUBY_BINDING: AprSockaddrT::family_reader */
/* sha: 524b703efdedf4fd16fc2dd2f6948d40c7f23bc064905d463e08b7a7c39acc3a */
#if BIND_AprSockaddrT_family_FIELD_READER
mrb_value
mrb_APR_AprSockaddrT_get_family(mrb_state* mrb, mrb_value self) {
  apr_sockaddr_t * native_self = mruby_unbox_apr_sockaddr_t(self);

  apr_int32_t native_family = native_self->family;

  mrb_value family = mrb_fixnum_value(native_family);

  return family;
}
#endif
/* MRUBY_BINDING_END */

/* MRUBY_BINDING: AprSockaddrT::family_writer */
/* sha: afa7fe526bc9d4bc8833e3b71af7491e380031607d0398370df90d2b4d357e4a */
#if BIND_AprSockaddrT_family_FIELD_WRITER
mrb_value
mrb_APR_AprSockaddrT_set_family(mrb_state* mrb, mrb_value self) {
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

/* MRUBY_BINDING: AprSockaddrT::salen_reader */
/* sha: 2c73f7f7f0f60fb37e3d9a3adc098b1222f31c42c1e23dbe99a56385d4553dfa */
#if BIND_AprSockaddrT_salen_FIELD_READER
mrb_value
mrb_APR_AprSockaddrT_get_salen(mrb_state* mrb, mrb_value self) {
  apr_sockaddr_t * native_self = mruby_unbox_apr_sockaddr_t(self);

  apr_socklen_t native_salen = native_self->salen;

  mrb_value salen = TODO_mruby_box_apr_socklen_t(mrb, native_salen);

  return salen;
}
#endif
/* MRUBY_BINDING_END */

/* MRUBY_BINDING: AprSockaddrT::salen_writer */
/* sha: bc0cfa94026ee85adc8d708bbab3615ad44f56b84798780746c590898cb1bf75 */
#if BIND_AprSockaddrT_salen_FIELD_WRITER
mrb_value
mrb_APR_AprSockaddrT_set_salen(mrb_state* mrb, mrb_value self) {
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

/* MRUBY_BINDING: AprSockaddrT::ipaddr_len_reader */
/* sha: 18796056034d2df830829fc899572934e159ef1005af745b5b636d76aac71af1 */
#if BIND_AprSockaddrT_ipaddr_len_FIELD_READER
mrb_value
mrb_APR_AprSockaddrT_get_ipaddr_len(mrb_state* mrb, mrb_value self) {
  apr_sockaddr_t * native_self = mruby_unbox_apr_sockaddr_t(self);

  int native_ipaddr_len = native_self->ipaddr_len;

  mrb_value ipaddr_len = mrb_fixnum_value(native_ipaddr_len);

  return ipaddr_len;
}
#endif
/* MRUBY_BINDING_END */

/* MRUBY_BINDING: AprSockaddrT::ipaddr_len_writer */
/* sha: b4d7d80bcd3252827f7be8660dbf30a5f544ef5a67dc5ea83e17d3d1b194c92d */
#if BIND_AprSockaddrT_ipaddr_len_FIELD_WRITER
mrb_value
mrb_APR_AprSockaddrT_set_ipaddr_len(mrb_state* mrb, mrb_value self) {
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

/* MRUBY_BINDING: AprSockaddrT::addr_str_len_reader */
/* sha: ed7b251c81bc69fe2b90e795b5392277fc6f598327552fff0d8a6ef184ea17ee */
#if BIND_AprSockaddrT_addr_str_len_FIELD_READER
mrb_value
mrb_APR_AprSockaddrT_get_addr_str_len(mrb_state* mrb, mrb_value self) {
  apr_sockaddr_t * native_self = mruby_unbox_apr_sockaddr_t(self);

  int native_addr_str_len = native_self->addr_str_len;

  mrb_value addr_str_len = mrb_fixnum_value(native_addr_str_len);

  return addr_str_len;
}
#endif
/* MRUBY_BINDING_END */

/* MRUBY_BINDING: AprSockaddrT::addr_str_len_writer */
/* sha: 096c4b30a0a10a5448a6cb1dbb40c696cae4142c80141667d25f47606ff3a433 */
#if BIND_AprSockaddrT_addr_str_len_FIELD_WRITER
mrb_value
mrb_APR_AprSockaddrT_set_addr_str_len(mrb_state* mrb, mrb_value self) {
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

/* MRUBY_BINDING: AprSockaddrT::ipaddr_ptr_reader */
/* sha: da9c9b1d88407e52de6af68eb116e950f810deb6d588368db83cbe7de96b39aa */
#if BIND_AprSockaddrT_ipaddr_ptr_FIELD_READER
mrb_value
mrb_APR_AprSockaddrT_get_ipaddr_ptr(mrb_state* mrb, mrb_value self) {
  apr_sockaddr_t * native_self = mruby_unbox_apr_sockaddr_t(self);

  void * native_ipaddr_ptr = native_self->ipaddr_ptr;

  mrb_value ipaddr_ptr = TODO_mruby_box_void_PTR(mrb, native_ipaddr_ptr);

  return ipaddr_ptr;
}
#endif
/* MRUBY_BINDING_END */

/* MRUBY_BINDING: AprSockaddrT::ipaddr_ptr_writer */
/* sha: 7412aadd25fa138340daf844fcee3a5839355452ca938e0f7dcc6973793f7715 */
#if BIND_AprSockaddrT_ipaddr_ptr_FIELD_WRITER
mrb_value
mrb_APR_AprSockaddrT_set_ipaddr_ptr(mrb_state* mrb, mrb_value self) {
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

/* MRUBY_BINDING: AprSockaddrT::next_reader */
/* sha: c88055a44168f6f7c73013e8edd7d01eb05e916a63ea6829c9a5b8e47763654f */
#if BIND_AprSockaddrT_next_FIELD_READER
mrb_value
mrb_APR_AprSockaddrT_get_next(mrb_state* mrb, mrb_value self) {
  apr_sockaddr_t * native_self = mruby_unbox_apr_sockaddr_t(self);

  apr_sockaddr_t * native_next = native_self->next;

  mrb_value next = (native_next == NULL ? mrb_nil_value() : mruby_box_apr_sockaddr_t(mrb, native_next));

  return next;
}
#endif
/* MRUBY_BINDING_END */

/* MRUBY_BINDING: AprSockaddrT::next_writer */
/* sha: dc9dadc92beef8ed2577c9138976e107c18c78bdd70b07d8678a4534fc92ab72 */
#if BIND_AprSockaddrT_next_FIELD_WRITER
mrb_value
mrb_APR_AprSockaddrT_set_next(mrb_state* mrb, mrb_value self) {
  apr_sockaddr_t * native_self = mruby_unbox_apr_sockaddr_t(self);
  mrb_value next;

  mrb_get_args(mrb, "o", &next);

  /* type checking */
  if (!mrb_obj_is_kind_of(mrb, next, AprSockaddrT_class(mrb))) {
    mrb_raise(mrb, E_TYPE_ERROR, "AprSockaddrT expected");
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

/* MRUBY_BINDING: AprSockaddrT::sa_reader */
/* sha: 7d57d6d6e94a6e735750b36501ee4eb468219b9974050b1502944df262b511d1 */
#if BIND_AprSockaddrT_sa_FIELD_READER
mrb_value
mrb_APR_AprSockaddrT_get_sa(mrb_state* mrb, mrb_value self) {
  apr_sockaddr_t * native_self = mruby_unbox_apr_sockaddr_t(self);

  union (anonymous union at /usr/include/apr-1/apr_network_io.h:236:5) native_sa = native_self->sa;

  mrb_value sa = TODO_mruby_box_union_LPAREN_anonymous_union_at_/usr/include/apr-1/apr_network_io.h:236:5_RPAREN(mrb, native_sa);

  return sa;
}
#endif
/* MRUBY_BINDING_END */

/* MRUBY_BINDING: AprSockaddrT::sa_writer */
/* sha: 78405149596d4ad08da5650ba7c92d60c8dae9ba67dfb8d9d352d9fd512c8753 */
#if BIND_AprSockaddrT_sa_FIELD_WRITER
mrb_value
mrb_APR_AprSockaddrT_set_sa(mrb_state* mrb, mrb_value self) {
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


void mrb_APR_AprSockaddrT_init(mrb_state* mrb) {
  static int initialized = 0;
  if (initialized) return;
  else initialized = 1;

/* MRUBY_BINDING: pre_class_definition */
/* sha: user_defined */

/* MRUBY_BINDING_END */

/* MRUBY_BINDING: AprSockaddrT::class_definition */
/* sha: c1238c8169f45185f0a3c26881e80e93d2f7ade3447bd2490416d88d0bc790a4 */
  struct RClass* AprSockaddrT_class = mrb_define_class_under(mrb, APR_module(mrb), "AprSockaddrT", mrb->object_class);
  MRB_SET_INSTANCE_TT(AprSockaddrT_class, MRB_TT_DATA);
/* MRUBY_BINDING_END */

/* MRUBY_BINDING: AprSockaddrT::pre_class_method_definitions */
/* sha: user_defined */

/* MRUBY_BINDING_END */

/* MRUBY_BINDING: AprSockaddrT::class_method_definitions */
/* sha: ec1a9ebad95012dca89b09cba980cd229985ee00d77f97a551a50785fb330cab */
#if BIND_AprSockaddrT_INITIALIZE
  mrb_define_method(mrb, AprSockaddrT_class, "initialize", mrb_APR_AprSockaddrT_initialize, MRB_ARGS_NONE());
#endif
/* MRUBY_BINDING_END */

/* MRUBY_BINDING: AprSockaddrT::pre_attr_definitions */
/* sha: user_defined */

/* MRUBY_BINDING_END */

/* MRUBY_BINDING: AprSockaddrT::attr_definitions */
/* sha: c7b1bd975e4d3dad450f2ea032b96b1601c73c7ac0938eeab54292402a33b670 */
  /*
   * Fields
   */
#if BIND_AprSockaddrT_pool_FIELD_READER
  mrb_define_method(mrb, AprSockaddrT_class, "pool", mrb_APR_AprSockaddrT_get_pool, MRB_ARGS_ARG(0, 0));
#endif
#if BIND_AprSockaddrT_pool_FIELD_WRITER
  mrb_define_method(mrb, AprSockaddrT_class, "pool=", mrb_APR_AprSockaddrT_set_pool, MRB_ARGS_ARG(1, 0));
#endif
#if BIND_AprSockaddrT_hostname_FIELD_READER
  mrb_define_method(mrb, AprSockaddrT_class, "hostname", mrb_APR_AprSockaddrT_get_hostname, MRB_ARGS_ARG(0, 0));
#endif
#if BIND_AprSockaddrT_hostname_FIELD_WRITER
  mrb_define_method(mrb, AprSockaddrT_class, "hostname=", mrb_APR_AprSockaddrT_set_hostname, MRB_ARGS_ARG(1, 0));
#endif
#if BIND_AprSockaddrT_servname_FIELD_READER
  mrb_define_method(mrb, AprSockaddrT_class, "servname", mrb_APR_AprSockaddrT_get_servname, MRB_ARGS_ARG(0, 0));
#endif
#if BIND_AprSockaddrT_servname_FIELD_WRITER
  mrb_define_method(mrb, AprSockaddrT_class, "servname=", mrb_APR_AprSockaddrT_set_servname, MRB_ARGS_ARG(1, 0));
#endif
#if BIND_AprSockaddrT_port_FIELD_READER
  mrb_define_method(mrb, AprSockaddrT_class, "port", mrb_APR_AprSockaddrT_get_port, MRB_ARGS_ARG(0, 0));
#endif
#if BIND_AprSockaddrT_port_FIELD_WRITER
  mrb_define_method(mrb, AprSockaddrT_class, "port=", mrb_APR_AprSockaddrT_set_port, MRB_ARGS_ARG(1, 0));
#endif
#if BIND_AprSockaddrT_family_FIELD_READER
  mrb_define_method(mrb, AprSockaddrT_class, "family", mrb_APR_AprSockaddrT_get_family, MRB_ARGS_ARG(0, 0));
#endif
#if BIND_AprSockaddrT_family_FIELD_WRITER
  mrb_define_method(mrb, AprSockaddrT_class, "family=", mrb_APR_AprSockaddrT_set_family, MRB_ARGS_ARG(1, 0));
#endif
#if BIND_AprSockaddrT_salen_FIELD_READER
  mrb_define_method(mrb, AprSockaddrT_class, "salen", mrb_APR_AprSockaddrT_get_salen, MRB_ARGS_ARG(0, 0));
#endif
#if BIND_AprSockaddrT_salen_FIELD_WRITER
  mrb_define_method(mrb, AprSockaddrT_class, "salen=", mrb_APR_AprSockaddrT_set_salen, MRB_ARGS_ARG(1, 0));
#endif
#if BIND_AprSockaddrT_ipaddr_len_FIELD_READER
  mrb_define_method(mrb, AprSockaddrT_class, "ipaddr_len", mrb_APR_AprSockaddrT_get_ipaddr_len, MRB_ARGS_ARG(0, 0));
#endif
#if BIND_AprSockaddrT_ipaddr_len_FIELD_WRITER
  mrb_define_method(mrb, AprSockaddrT_class, "ipaddr_len=", mrb_APR_AprSockaddrT_set_ipaddr_len, MRB_ARGS_ARG(1, 0));
#endif
#if BIND_AprSockaddrT_addr_str_len_FIELD_READER
  mrb_define_method(mrb, AprSockaddrT_class, "addr_str_len", mrb_APR_AprSockaddrT_get_addr_str_len, MRB_ARGS_ARG(0, 0));
#endif
#if BIND_AprSockaddrT_addr_str_len_FIELD_WRITER
  mrb_define_method(mrb, AprSockaddrT_class, "addr_str_len=", mrb_APR_AprSockaddrT_set_addr_str_len, MRB_ARGS_ARG(1, 0));
#endif
#if BIND_AprSockaddrT_ipaddr_ptr_FIELD_READER
  mrb_define_method(mrb, AprSockaddrT_class, "ipaddr_ptr", mrb_APR_AprSockaddrT_get_ipaddr_ptr, MRB_ARGS_ARG(0, 0));
#endif
#if BIND_AprSockaddrT_ipaddr_ptr_FIELD_WRITER
  mrb_define_method(mrb, AprSockaddrT_class, "ipaddr_ptr=", mrb_APR_AprSockaddrT_set_ipaddr_ptr, MRB_ARGS_ARG(1, 0));
#endif
#if BIND_AprSockaddrT_next_FIELD_READER
  mrb_define_method(mrb, AprSockaddrT_class, "next", mrb_APR_AprSockaddrT_get_next, MRB_ARGS_ARG(0, 0));
#endif
#if BIND_AprSockaddrT_next_FIELD_WRITER
  mrb_define_method(mrb, AprSockaddrT_class, "next=", mrb_APR_AprSockaddrT_set_next, MRB_ARGS_ARG(1, 0));
#endif
#if BIND_AprSockaddrT_sa_FIELD_READER
  mrb_define_method(mrb, AprSockaddrT_class, "sa", mrb_APR_AprSockaddrT_get_sa, MRB_ARGS_ARG(0, 0));
#endif
#if BIND_AprSockaddrT_sa_FIELD_WRITER
  mrb_define_method(mrb, AprSockaddrT_class, "sa=", mrb_APR_AprSockaddrT_set_sa, MRB_ARGS_ARG(1, 0));
#endif
/* MRUBY_BINDING_END */


/* MRUBY_BINDING: AprSockaddrT::post_class_definition */
/* sha: user_defined */

/* MRUBY_BINDING_END */
}

/* MRUBY_BINDING: footer */
/* sha: user_defined */

/* MRUBY_BINDING_END */
#endif
