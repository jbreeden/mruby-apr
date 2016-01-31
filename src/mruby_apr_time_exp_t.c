/*
 * apr_time_exp_t
 * Defined in file apr_time.h @ line 91
 */

#include "mruby_APR.h"

#if BIND_AprTimeExpT_TYPE

/* MRUBY_BINDING: header */
/* sha: user_defined */

/* MRUBY_BINDING_END */

/* MRUBY_BINDING: AprTimeExpT::initialize */
/* sha: b3bc966717b6e3cb83eef9b96f33d1653f0aaeee072d1ccf5e83e6c670366725 */
#if BIND_AprTimeExpT_INITIALIZE
mrb_value
mrb_APR_AprTimeExpT_initialize(mrb_state* mrb, mrb_value self) {
  mrb_raise(mrb, E_NOMETHOD_ERROR, "No initializer defined");
/* 
  apr_time_exp_t* native_object = (apr_time_exp_t*)calloc(1, sizeof(apr_time_exp_t));
  mruby_gift_apr_time_exp_t_data_ptr(self, native_object);
  return self;
*/
}
#endif
/* MRUBY_BINDING_END */

/*
 * Fields
 */

/* MRUBY_BINDING: AprTimeExpT::tm_usec_reader */
/* sha: 696ebc848c1afcd923fc24536b16605bfadf787705e80d64b1eace86efd26ec3 */
#if BIND_AprTimeExpT_tm_usec_FIELD_READER
mrb_value
mrb_APR_AprTimeExpT_get_tm_usec(mrb_state* mrb, mrb_value self) {
  apr_time_exp_t * native_self = mruby_unbox_apr_time_exp_t(self);

  apr_int32_t native_tm_usec = native_self->tm_usec;

  mrb_value tm_usec = mrb_fixnum_value(native_tm_usec);

  return tm_usec;
}
#endif
/* MRUBY_BINDING_END */

/* MRUBY_BINDING: AprTimeExpT::tm_usec_writer */
/* sha: 37bf7fe6c8a16b7849a05714e9edc7a03b17942049a6f901af337307144555b4 */
#if BIND_AprTimeExpT_tm_usec_FIELD_WRITER
mrb_value
mrb_APR_AprTimeExpT_set_tm_usec(mrb_state* mrb, mrb_value self) {
  apr_time_exp_t * native_self = mruby_unbox_apr_time_exp_t(self);
  mrb_int native_tm_usec;

  mrb_get_args(mrb, "i", &native_tm_usec);

  native_self->tm_usec = native_tm_usec;
  
  mrb_value value_as_mrb_value;
  mrb_get_args(mrb, "o", &value_as_mrb_value);
  return value_as_mrb_value;
}
#endif
/* MRUBY_BINDING_END */

/* MRUBY_BINDING: AprTimeExpT::tm_sec_reader */
/* sha: de4d1695674fb88349220f041857fddb499f9be8580b2ac0a4c6fed0578996d3 */
#if BIND_AprTimeExpT_tm_sec_FIELD_READER
mrb_value
mrb_APR_AprTimeExpT_get_tm_sec(mrb_state* mrb, mrb_value self) {
  apr_time_exp_t * native_self = mruby_unbox_apr_time_exp_t(self);

  apr_int32_t native_tm_sec = native_self->tm_sec;

  mrb_value tm_sec = mrb_fixnum_value(native_tm_sec);

  return tm_sec;
}
#endif
/* MRUBY_BINDING_END */

/* MRUBY_BINDING: AprTimeExpT::tm_sec_writer */
/* sha: f37cd4111d31a4b67be53f8b60dc2485571cad59d5d06470c98fe3225dada38b */
#if BIND_AprTimeExpT_tm_sec_FIELD_WRITER
mrb_value
mrb_APR_AprTimeExpT_set_tm_sec(mrb_state* mrb, mrb_value self) {
  apr_time_exp_t * native_self = mruby_unbox_apr_time_exp_t(self);
  mrb_int native_tm_sec;

  mrb_get_args(mrb, "i", &native_tm_sec);

  native_self->tm_sec = native_tm_sec;
  
  mrb_value value_as_mrb_value;
  mrb_get_args(mrb, "o", &value_as_mrb_value);
  return value_as_mrb_value;
}
#endif
/* MRUBY_BINDING_END */

/* MRUBY_BINDING: AprTimeExpT::tm_min_reader */
/* sha: 4be84759b81e1618726faae9d63f04a07eab46ec2f208bca26c10dba66a70d95 */
#if BIND_AprTimeExpT_tm_min_FIELD_READER
mrb_value
mrb_APR_AprTimeExpT_get_tm_min(mrb_state* mrb, mrb_value self) {
  apr_time_exp_t * native_self = mruby_unbox_apr_time_exp_t(self);

  apr_int32_t native_tm_min = native_self->tm_min;

  mrb_value tm_min = mrb_fixnum_value(native_tm_min);

  return tm_min;
}
#endif
/* MRUBY_BINDING_END */

/* MRUBY_BINDING: AprTimeExpT::tm_min_writer */
/* sha: a8fa72f62eca01e91cf54809066362131bfb8fbf02ef86972aa9cee548468486 */
#if BIND_AprTimeExpT_tm_min_FIELD_WRITER
mrb_value
mrb_APR_AprTimeExpT_set_tm_min(mrb_state* mrb, mrb_value self) {
  apr_time_exp_t * native_self = mruby_unbox_apr_time_exp_t(self);
  mrb_int native_tm_min;

  mrb_get_args(mrb, "i", &native_tm_min);

  native_self->tm_min = native_tm_min;
  
  mrb_value value_as_mrb_value;
  mrb_get_args(mrb, "o", &value_as_mrb_value);
  return value_as_mrb_value;
}
#endif
/* MRUBY_BINDING_END */

/* MRUBY_BINDING: AprTimeExpT::tm_hour_reader */
/* sha: 7d6186e298629b93407d1dea8987f485f2eaa9926bfe01cf9ef84d96032e25fa */
#if BIND_AprTimeExpT_tm_hour_FIELD_READER
mrb_value
mrb_APR_AprTimeExpT_get_tm_hour(mrb_state* mrb, mrb_value self) {
  apr_time_exp_t * native_self = mruby_unbox_apr_time_exp_t(self);

  apr_int32_t native_tm_hour = native_self->tm_hour;

  mrb_value tm_hour = mrb_fixnum_value(native_tm_hour);

  return tm_hour;
}
#endif
/* MRUBY_BINDING_END */

/* MRUBY_BINDING: AprTimeExpT::tm_hour_writer */
/* sha: 24d0a3a166b00504c7301dbe1bf8bb92babae334654f2120bf696265a5188042 */
#if BIND_AprTimeExpT_tm_hour_FIELD_WRITER
mrb_value
mrb_APR_AprTimeExpT_set_tm_hour(mrb_state* mrb, mrb_value self) {
  apr_time_exp_t * native_self = mruby_unbox_apr_time_exp_t(self);
  mrb_int native_tm_hour;

  mrb_get_args(mrb, "i", &native_tm_hour);

  native_self->tm_hour = native_tm_hour;
  
  mrb_value value_as_mrb_value;
  mrb_get_args(mrb, "o", &value_as_mrb_value);
  return value_as_mrb_value;
}
#endif
/* MRUBY_BINDING_END */

/* MRUBY_BINDING: AprTimeExpT::tm_mday_reader */
/* sha: b7b174bd52575635a155cb11a37997e8dc6286c2d0e5f442d8759ff909339765 */
#if BIND_AprTimeExpT_tm_mday_FIELD_READER
mrb_value
mrb_APR_AprTimeExpT_get_tm_mday(mrb_state* mrb, mrb_value self) {
  apr_time_exp_t * native_self = mruby_unbox_apr_time_exp_t(self);

  apr_int32_t native_tm_mday = native_self->tm_mday;

  mrb_value tm_mday = mrb_fixnum_value(native_tm_mday);

  return tm_mday;
}
#endif
/* MRUBY_BINDING_END */

/* MRUBY_BINDING: AprTimeExpT::tm_mday_writer */
/* sha: b339c518e3394901e4cd8f42875471432537d70c6594f205f4431eed275bdd03 */
#if BIND_AprTimeExpT_tm_mday_FIELD_WRITER
mrb_value
mrb_APR_AprTimeExpT_set_tm_mday(mrb_state* mrb, mrb_value self) {
  apr_time_exp_t * native_self = mruby_unbox_apr_time_exp_t(self);
  mrb_int native_tm_mday;

  mrb_get_args(mrb, "i", &native_tm_mday);

  native_self->tm_mday = native_tm_mday;
  
  mrb_value value_as_mrb_value;
  mrb_get_args(mrb, "o", &value_as_mrb_value);
  return value_as_mrb_value;
}
#endif
/* MRUBY_BINDING_END */

/* MRUBY_BINDING: AprTimeExpT::tm_mon_reader */
/* sha: 0341f454571a1bf6bd22b57f3f3a9e5eff58370177870874a5cca5a5beb3e5b0 */
#if BIND_AprTimeExpT_tm_mon_FIELD_READER
mrb_value
mrb_APR_AprTimeExpT_get_tm_mon(mrb_state* mrb, mrb_value self) {
  apr_time_exp_t * native_self = mruby_unbox_apr_time_exp_t(self);

  apr_int32_t native_tm_mon = native_self->tm_mon;

  mrb_value tm_mon = mrb_fixnum_value(native_tm_mon);

  return tm_mon;
}
#endif
/* MRUBY_BINDING_END */

/* MRUBY_BINDING: AprTimeExpT::tm_mon_writer */
/* sha: 880034dc9c56fc94ed67356451f717d469f96e2597a87c54c99e534dd77055ca */
#if BIND_AprTimeExpT_tm_mon_FIELD_WRITER
mrb_value
mrb_APR_AprTimeExpT_set_tm_mon(mrb_state* mrb, mrb_value self) {
  apr_time_exp_t * native_self = mruby_unbox_apr_time_exp_t(self);
  mrb_int native_tm_mon;

  mrb_get_args(mrb, "i", &native_tm_mon);

  native_self->tm_mon = native_tm_mon;
  
  mrb_value value_as_mrb_value;
  mrb_get_args(mrb, "o", &value_as_mrb_value);
  return value_as_mrb_value;
}
#endif
/* MRUBY_BINDING_END */

/* MRUBY_BINDING: AprTimeExpT::tm_year_reader */
/* sha: 5d812a394e49654c2a0bc5b937329411a3511a8e7f7d15aebbd82fa40ac33a6e */
#if BIND_AprTimeExpT_tm_year_FIELD_READER
mrb_value
mrb_APR_AprTimeExpT_get_tm_year(mrb_state* mrb, mrb_value self) {
  apr_time_exp_t * native_self = mruby_unbox_apr_time_exp_t(self);

  apr_int32_t native_tm_year = native_self->tm_year;

  mrb_value tm_year = mrb_fixnum_value(native_tm_year);

  return tm_year;
}
#endif
/* MRUBY_BINDING_END */

/* MRUBY_BINDING: AprTimeExpT::tm_year_writer */
/* sha: cc861b22d4f14d5ecccb23d42063d7d31a79099e10172fceaa4ac6d4514a5845 */
#if BIND_AprTimeExpT_tm_year_FIELD_WRITER
mrb_value
mrb_APR_AprTimeExpT_set_tm_year(mrb_state* mrb, mrb_value self) {
  apr_time_exp_t * native_self = mruby_unbox_apr_time_exp_t(self);
  mrb_int native_tm_year;

  mrb_get_args(mrb, "i", &native_tm_year);

  native_self->tm_year = native_tm_year;
  
  mrb_value value_as_mrb_value;
  mrb_get_args(mrb, "o", &value_as_mrb_value);
  return value_as_mrb_value;
}
#endif
/* MRUBY_BINDING_END */

/* MRUBY_BINDING: AprTimeExpT::tm_wday_reader */
/* sha: 4d4816578f8bda58685a370946bf26839e0c8a2c4cd7337d11608208d88282cd */
#if BIND_AprTimeExpT_tm_wday_FIELD_READER
mrb_value
mrb_APR_AprTimeExpT_get_tm_wday(mrb_state* mrb, mrb_value self) {
  apr_time_exp_t * native_self = mruby_unbox_apr_time_exp_t(self);

  apr_int32_t native_tm_wday = native_self->tm_wday;

  mrb_value tm_wday = mrb_fixnum_value(native_tm_wday);

  return tm_wday;
}
#endif
/* MRUBY_BINDING_END */

/* MRUBY_BINDING: AprTimeExpT::tm_wday_writer */
/* sha: 363bf3defe05b8d0ec9981bbb2bb32b8c4198fbaee988c0ab4ae6863eb00d4ed */
#if BIND_AprTimeExpT_tm_wday_FIELD_WRITER
mrb_value
mrb_APR_AprTimeExpT_set_tm_wday(mrb_state* mrb, mrb_value self) {
  apr_time_exp_t * native_self = mruby_unbox_apr_time_exp_t(self);
  mrb_int native_tm_wday;

  mrb_get_args(mrb, "i", &native_tm_wday);

  native_self->tm_wday = native_tm_wday;
  
  mrb_value value_as_mrb_value;
  mrb_get_args(mrb, "o", &value_as_mrb_value);
  return value_as_mrb_value;
}
#endif
/* MRUBY_BINDING_END */

/* MRUBY_BINDING: AprTimeExpT::tm_yday_reader */
/* sha: 9a450e2e4ca49e175a17dbde8e32fe4bc5e02df164c5316f0b64d07640f6cd98 */
#if BIND_AprTimeExpT_tm_yday_FIELD_READER
mrb_value
mrb_APR_AprTimeExpT_get_tm_yday(mrb_state* mrb, mrb_value self) {
  apr_time_exp_t * native_self = mruby_unbox_apr_time_exp_t(self);

  apr_int32_t native_tm_yday = native_self->tm_yday;

  mrb_value tm_yday = mrb_fixnum_value(native_tm_yday);

  return tm_yday;
}
#endif
/* MRUBY_BINDING_END */

/* MRUBY_BINDING: AprTimeExpT::tm_yday_writer */
/* sha: bb037927d625f58fc18a324366e0536eee5921190a46c7005c3caa4dab5e126a */
#if BIND_AprTimeExpT_tm_yday_FIELD_WRITER
mrb_value
mrb_APR_AprTimeExpT_set_tm_yday(mrb_state* mrb, mrb_value self) {
  apr_time_exp_t * native_self = mruby_unbox_apr_time_exp_t(self);
  mrb_int native_tm_yday;

  mrb_get_args(mrb, "i", &native_tm_yday);

  native_self->tm_yday = native_tm_yday;
  
  mrb_value value_as_mrb_value;
  mrb_get_args(mrb, "o", &value_as_mrb_value);
  return value_as_mrb_value;
}
#endif
/* MRUBY_BINDING_END */

/* MRUBY_BINDING: AprTimeExpT::tm_isdst_reader */
/* sha: ec1caad7eb43817b4db1d2b194e03598425a12c8a2c902ff1dfa9d61fb96f383 */
#if BIND_AprTimeExpT_tm_isdst_FIELD_READER
mrb_value
mrb_APR_AprTimeExpT_get_tm_isdst(mrb_state* mrb, mrb_value self) {
  apr_time_exp_t * native_self = mruby_unbox_apr_time_exp_t(self);

  apr_int32_t native_tm_isdst = native_self->tm_isdst;

  mrb_value tm_isdst = mrb_fixnum_value(native_tm_isdst);

  return tm_isdst;
}
#endif
/* MRUBY_BINDING_END */

/* MRUBY_BINDING: AprTimeExpT::tm_isdst_writer */
/* sha: 6db3de13e62b0bc421b8daddcbc019186abbd97bb7133008737a68d7d579aef8 */
#if BIND_AprTimeExpT_tm_isdst_FIELD_WRITER
mrb_value
mrb_APR_AprTimeExpT_set_tm_isdst(mrb_state* mrb, mrb_value self) {
  apr_time_exp_t * native_self = mruby_unbox_apr_time_exp_t(self);
  mrb_int native_tm_isdst;

  mrb_get_args(mrb, "i", &native_tm_isdst);

  native_self->tm_isdst = native_tm_isdst;
  
  mrb_value value_as_mrb_value;
  mrb_get_args(mrb, "o", &value_as_mrb_value);
  return value_as_mrb_value;
}
#endif
/* MRUBY_BINDING_END */

/* MRUBY_BINDING: AprTimeExpT::tm_gmtoff_reader */
/* sha: f59f8046642d09155d879461b3fe2c49693ae8cee3a32ba4ab2c284c566b991b */
#if BIND_AprTimeExpT_tm_gmtoff_FIELD_READER
mrb_value
mrb_APR_AprTimeExpT_get_tm_gmtoff(mrb_state* mrb, mrb_value self) {
  apr_time_exp_t * native_self = mruby_unbox_apr_time_exp_t(self);

  apr_int32_t native_tm_gmtoff = native_self->tm_gmtoff;

  mrb_value tm_gmtoff = mrb_fixnum_value(native_tm_gmtoff);

  return tm_gmtoff;
}
#endif
/* MRUBY_BINDING_END */

/* MRUBY_BINDING: AprTimeExpT::tm_gmtoff_writer */
/* sha: bbafe85f3e11c4eecd845f0bb576fc9ef5f0bba129b0637ab0be860221500e83 */
#if BIND_AprTimeExpT_tm_gmtoff_FIELD_WRITER
mrb_value
mrb_APR_AprTimeExpT_set_tm_gmtoff(mrb_state* mrb, mrb_value self) {
  apr_time_exp_t * native_self = mruby_unbox_apr_time_exp_t(self);
  mrb_int native_tm_gmtoff;

  mrb_get_args(mrb, "i", &native_tm_gmtoff);

  native_self->tm_gmtoff = native_tm_gmtoff;
  
  mrb_value value_as_mrb_value;
  mrb_get_args(mrb, "o", &value_as_mrb_value);
  return value_as_mrb_value;
}
#endif
/* MRUBY_BINDING_END */


void mrb_APR_AprTimeExpT_init(mrb_state* mrb) {
  static int initialized = 0;
  if (initialized) return;
  else initialized = 1;

/* MRUBY_BINDING: pre_class_definition */
/* sha: user_defined */

/* MRUBY_BINDING_END */

/* MRUBY_BINDING: AprTimeExpT::class_definition */
/* sha: ea2baaeff12f6deeb010a8a9e83c7777cc4a6bc92f12c2543c65d737a4a69eca */
  struct RClass* AprTimeExpT_class = mrb_define_class_under(mrb, APR_module(mrb), "AprTimeExpT", mrb->object_class);
  MRB_SET_INSTANCE_TT(AprTimeExpT_class, MRB_TT_DATA);
/* MRUBY_BINDING_END */

/* MRUBY_BINDING: AprTimeExpT::pre_class_method_definitions */
/* sha: user_defined */

/* MRUBY_BINDING_END */

/* MRUBY_BINDING: AprTimeExpT::class_method_definitions */
/* sha: 85f8a1317268639df85fd00d4b15d9ba50503eb2fd08db848b8642877a1fe8a6 */
#if BIND_AprTimeExpT_INITIALIZE
  mrb_define_method(mrb, AprTimeExpT_class, "initialize", mrb_APR_AprTimeExpT_initialize, MRB_ARGS_NONE());
#endif
/* MRUBY_BINDING_END */

/* MRUBY_BINDING: AprTimeExpT::pre_attr_definitions */
/* sha: user_defined */

/* MRUBY_BINDING_END */

/* MRUBY_BINDING: AprTimeExpT::attr_definitions */
/* sha: 92cf97fb66649ca935bba200eeb32bafb285509f3a9712f7427de6b53cc67894 */
  /*
   * Fields
   */
#if BIND_AprTimeExpT_tm_usec_FIELD_READER
  mrb_define_method(mrb, AprTimeExpT_class, "tm_usec", mrb_APR_AprTimeExpT_get_tm_usec, MRB_ARGS_ARG(0, 0));
#endif
#if BIND_AprTimeExpT_tm_usec_FIELD_WRITER
  mrb_define_method(mrb, AprTimeExpT_class, "tm_usec=", mrb_APR_AprTimeExpT_set_tm_usec, MRB_ARGS_ARG(1, 0));
#endif
#if BIND_AprTimeExpT_tm_sec_FIELD_READER
  mrb_define_method(mrb, AprTimeExpT_class, "tm_sec", mrb_APR_AprTimeExpT_get_tm_sec, MRB_ARGS_ARG(0, 0));
#endif
#if BIND_AprTimeExpT_tm_sec_FIELD_WRITER
  mrb_define_method(mrb, AprTimeExpT_class, "tm_sec=", mrb_APR_AprTimeExpT_set_tm_sec, MRB_ARGS_ARG(1, 0));
#endif
#if BIND_AprTimeExpT_tm_min_FIELD_READER
  mrb_define_method(mrb, AprTimeExpT_class, "tm_min", mrb_APR_AprTimeExpT_get_tm_min, MRB_ARGS_ARG(0, 0));
#endif
#if BIND_AprTimeExpT_tm_min_FIELD_WRITER
  mrb_define_method(mrb, AprTimeExpT_class, "tm_min=", mrb_APR_AprTimeExpT_set_tm_min, MRB_ARGS_ARG(1, 0));
#endif
#if BIND_AprTimeExpT_tm_hour_FIELD_READER
  mrb_define_method(mrb, AprTimeExpT_class, "tm_hour", mrb_APR_AprTimeExpT_get_tm_hour, MRB_ARGS_ARG(0, 0));
#endif
#if BIND_AprTimeExpT_tm_hour_FIELD_WRITER
  mrb_define_method(mrb, AprTimeExpT_class, "tm_hour=", mrb_APR_AprTimeExpT_set_tm_hour, MRB_ARGS_ARG(1, 0));
#endif
#if BIND_AprTimeExpT_tm_mday_FIELD_READER
  mrb_define_method(mrb, AprTimeExpT_class, "tm_mday", mrb_APR_AprTimeExpT_get_tm_mday, MRB_ARGS_ARG(0, 0));
#endif
#if BIND_AprTimeExpT_tm_mday_FIELD_WRITER
  mrb_define_method(mrb, AprTimeExpT_class, "tm_mday=", mrb_APR_AprTimeExpT_set_tm_mday, MRB_ARGS_ARG(1, 0));
#endif
#if BIND_AprTimeExpT_tm_mon_FIELD_READER
  mrb_define_method(mrb, AprTimeExpT_class, "tm_mon", mrb_APR_AprTimeExpT_get_tm_mon, MRB_ARGS_ARG(0, 0));
#endif
#if BIND_AprTimeExpT_tm_mon_FIELD_WRITER
  mrb_define_method(mrb, AprTimeExpT_class, "tm_mon=", mrb_APR_AprTimeExpT_set_tm_mon, MRB_ARGS_ARG(1, 0));
#endif
#if BIND_AprTimeExpT_tm_year_FIELD_READER
  mrb_define_method(mrb, AprTimeExpT_class, "tm_year", mrb_APR_AprTimeExpT_get_tm_year, MRB_ARGS_ARG(0, 0));
#endif
#if BIND_AprTimeExpT_tm_year_FIELD_WRITER
  mrb_define_method(mrb, AprTimeExpT_class, "tm_year=", mrb_APR_AprTimeExpT_set_tm_year, MRB_ARGS_ARG(1, 0));
#endif
#if BIND_AprTimeExpT_tm_wday_FIELD_READER
  mrb_define_method(mrb, AprTimeExpT_class, "tm_wday", mrb_APR_AprTimeExpT_get_tm_wday, MRB_ARGS_ARG(0, 0));
#endif
#if BIND_AprTimeExpT_tm_wday_FIELD_WRITER
  mrb_define_method(mrb, AprTimeExpT_class, "tm_wday=", mrb_APR_AprTimeExpT_set_tm_wday, MRB_ARGS_ARG(1, 0));
#endif
#if BIND_AprTimeExpT_tm_yday_FIELD_READER
  mrb_define_method(mrb, AprTimeExpT_class, "tm_yday", mrb_APR_AprTimeExpT_get_tm_yday, MRB_ARGS_ARG(0, 0));
#endif
#if BIND_AprTimeExpT_tm_yday_FIELD_WRITER
  mrb_define_method(mrb, AprTimeExpT_class, "tm_yday=", mrb_APR_AprTimeExpT_set_tm_yday, MRB_ARGS_ARG(1, 0));
#endif
#if BIND_AprTimeExpT_tm_isdst_FIELD_READER
  mrb_define_method(mrb, AprTimeExpT_class, "tm_isdst", mrb_APR_AprTimeExpT_get_tm_isdst, MRB_ARGS_ARG(0, 0));
#endif
#if BIND_AprTimeExpT_tm_isdst_FIELD_WRITER
  mrb_define_method(mrb, AprTimeExpT_class, "tm_isdst=", mrb_APR_AprTimeExpT_set_tm_isdst, MRB_ARGS_ARG(1, 0));
#endif
#if BIND_AprTimeExpT_tm_gmtoff_FIELD_READER
  mrb_define_method(mrb, AprTimeExpT_class, "tm_gmtoff", mrb_APR_AprTimeExpT_get_tm_gmtoff, MRB_ARGS_ARG(0, 0));
#endif
#if BIND_AprTimeExpT_tm_gmtoff_FIELD_WRITER
  mrb_define_method(mrb, AprTimeExpT_class, "tm_gmtoff=", mrb_APR_AprTimeExpT_set_tm_gmtoff, MRB_ARGS_ARG(1, 0));
#endif
/* MRUBY_BINDING_END */


/* MRUBY_BINDING: AprTimeExpT::post_class_definition */
/* sha: user_defined */

/* MRUBY_BINDING_END */
}

/* MRUBY_BINDING: footer */
/* sha: user_defined */

/* MRUBY_BINDING_END */
#endif
