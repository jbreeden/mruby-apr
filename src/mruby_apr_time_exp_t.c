/*
 * apr_time_exp_t
 * Defined in file apr_time.h @ line 91
 */

#include "mruby_APR.h"

#if BIND_TimeExp_TYPE

/* MRUBY_BINDING: header */
/* sha: user_defined */

/* MRUBY_BINDING_END */

/* MRUBY_BINDING: TimeExp::initialize */
/* sha: 221aba7e13066f8b0d3766d16aeab8c7e03312d5297620e124fb843838ea482a */
#if BIND_TimeExp_INITIALIZE
mrb_value
mrb_APR_TimeExp_initialize(mrb_state* mrb, mrb_value self) {
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

/* MRUBY_BINDING: TimeExp::tm_usec_reader */
/* sha: 6b8b8e9bdfab47f51e2f10c9bf74dc14f627508e5afd631ac7eaa55812d2ddc9 */
#if BIND_TimeExp_tm_usec_FIELD_READER
mrb_value
mrb_APR_TimeExp_get_tm_usec(mrb_state* mrb, mrb_value self) {
  apr_time_exp_t * native_self = mruby_unbox_apr_time_exp_t(self);

  apr_int32_t native_tm_usec = native_self->tm_usec;

  mrb_value tm_usec = mrb_fixnum_value(native_tm_usec);

  return tm_usec;
}
#endif
/* MRUBY_BINDING_END */

/* MRUBY_BINDING: TimeExp::tm_usec_writer */
/* sha: c4a0ac98129fa13a1f242189e4bc4fb8e439ed2e215fe54854e6b86b1fea9b0e */
#if BIND_TimeExp_tm_usec_FIELD_WRITER
mrb_value
mrb_APR_TimeExp_set_tm_usec(mrb_state* mrb, mrb_value self) {
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

/* MRUBY_BINDING: TimeExp::tm_sec_reader */
/* sha: dcd43e597db66d32bd368c950c2c52216f6b251aab0253ec3ba0cb410bb7a4e0 */
#if BIND_TimeExp_tm_sec_FIELD_READER
mrb_value
mrb_APR_TimeExp_get_tm_sec(mrb_state* mrb, mrb_value self) {
  apr_time_exp_t * native_self = mruby_unbox_apr_time_exp_t(self);

  apr_int32_t native_tm_sec = native_self->tm_sec;

  mrb_value tm_sec = mrb_fixnum_value(native_tm_sec);

  return tm_sec;
}
#endif
/* MRUBY_BINDING_END */

/* MRUBY_BINDING: TimeExp::tm_sec_writer */
/* sha: b3bd82086434d5231bb7270fb21c2d3f5fd7043b419885116e15b763121925c5 */
#if BIND_TimeExp_tm_sec_FIELD_WRITER
mrb_value
mrb_APR_TimeExp_set_tm_sec(mrb_state* mrb, mrb_value self) {
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

/* MRUBY_BINDING: TimeExp::tm_min_reader */
/* sha: be47777ba17d3ccb07f988ed4d0564462c6d1cd652acfa7ec612962f6421b586 */
#if BIND_TimeExp_tm_min_FIELD_READER
mrb_value
mrb_APR_TimeExp_get_tm_min(mrb_state* mrb, mrb_value self) {
  apr_time_exp_t * native_self = mruby_unbox_apr_time_exp_t(self);

  apr_int32_t native_tm_min = native_self->tm_min;

  mrb_value tm_min = mrb_fixnum_value(native_tm_min);

  return tm_min;
}
#endif
/* MRUBY_BINDING_END */

/* MRUBY_BINDING: TimeExp::tm_min_writer */
/* sha: 82eeedbd3aa0d7cd5044f82818543219fdd2a2e969720ba786648f619e90a96e */
#if BIND_TimeExp_tm_min_FIELD_WRITER
mrb_value
mrb_APR_TimeExp_set_tm_min(mrb_state* mrb, mrb_value self) {
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

/* MRUBY_BINDING: TimeExp::tm_hour_reader */
/* sha: b02e965dca9d3f689e7c5595b77c86dd509364469231fd2e4f3414b0696a00da */
#if BIND_TimeExp_tm_hour_FIELD_READER
mrb_value
mrb_APR_TimeExp_get_tm_hour(mrb_state* mrb, mrb_value self) {
  apr_time_exp_t * native_self = mruby_unbox_apr_time_exp_t(self);

  apr_int32_t native_tm_hour = native_self->tm_hour;

  mrb_value tm_hour = mrb_fixnum_value(native_tm_hour);

  return tm_hour;
}
#endif
/* MRUBY_BINDING_END */

/* MRUBY_BINDING: TimeExp::tm_hour_writer */
/* sha: 63fc50b9d9c1e90e8f8341c2fe11025fbe19a9a9490d29c26ba09b5af7058939 */
#if BIND_TimeExp_tm_hour_FIELD_WRITER
mrb_value
mrb_APR_TimeExp_set_tm_hour(mrb_state* mrb, mrb_value self) {
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

/* MRUBY_BINDING: TimeExp::tm_mday_reader */
/* sha: 7babd360e5a7eeb323b92dbfbc769f90f72777e99398a9f129b9fe84624c19a3 */
#if BIND_TimeExp_tm_mday_FIELD_READER
mrb_value
mrb_APR_TimeExp_get_tm_mday(mrb_state* mrb, mrb_value self) {
  apr_time_exp_t * native_self = mruby_unbox_apr_time_exp_t(self);

  apr_int32_t native_tm_mday = native_self->tm_mday;

  mrb_value tm_mday = mrb_fixnum_value(native_tm_mday);

  return tm_mday;
}
#endif
/* MRUBY_BINDING_END */

/* MRUBY_BINDING: TimeExp::tm_mday_writer */
/* sha: e52059c627702d2446197db67d4b4710b0bbedb0b11a329ada444a66bd31de6e */
#if BIND_TimeExp_tm_mday_FIELD_WRITER
mrb_value
mrb_APR_TimeExp_set_tm_mday(mrb_state* mrb, mrb_value self) {
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

/* MRUBY_BINDING: TimeExp::tm_mon_reader */
/* sha: 717aecd664cfe94bb321257d026d092dab2c7fbd998db8986370614b98633bf5 */
#if BIND_TimeExp_tm_mon_FIELD_READER
mrb_value
mrb_APR_TimeExp_get_tm_mon(mrb_state* mrb, mrb_value self) {
  apr_time_exp_t * native_self = mruby_unbox_apr_time_exp_t(self);

  apr_int32_t native_tm_mon = native_self->tm_mon;

  mrb_value tm_mon = mrb_fixnum_value(native_tm_mon);

  return tm_mon;
}
#endif
/* MRUBY_BINDING_END */

/* MRUBY_BINDING: TimeExp::tm_mon_writer */
/* sha: 187de89aa92b988a3bf1e6fcfb47e514ed78bc88ec171b93b98ce29205b47c40 */
#if BIND_TimeExp_tm_mon_FIELD_WRITER
mrb_value
mrb_APR_TimeExp_set_tm_mon(mrb_state* mrb, mrb_value self) {
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

/* MRUBY_BINDING: TimeExp::tm_year_reader */
/* sha: 7988f9dbb7b5a238d06fe2b8b711a98533cf6e7a32f4e90219567f530d59843e */
#if BIND_TimeExp_tm_year_FIELD_READER
mrb_value
mrb_APR_TimeExp_get_tm_year(mrb_state* mrb, mrb_value self) {
  apr_time_exp_t * native_self = mruby_unbox_apr_time_exp_t(self);

  apr_int32_t native_tm_year = native_self->tm_year;

  mrb_value tm_year = mrb_fixnum_value(native_tm_year);

  return tm_year;
}
#endif
/* MRUBY_BINDING_END */

/* MRUBY_BINDING: TimeExp::tm_year_writer */
/* sha: bc42becb146689b6253545f2377b26b08e3de376269bf718e95fa8f586145fce */
#if BIND_TimeExp_tm_year_FIELD_WRITER
mrb_value
mrb_APR_TimeExp_set_tm_year(mrb_state* mrb, mrb_value self) {
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

/* MRUBY_BINDING: TimeExp::tm_wday_reader */
/* sha: bec6c5796d7588a7a5838fe0cd3e9b0fe983fed6d4e4e47d7851fe00cb9b30c5 */
#if BIND_TimeExp_tm_wday_FIELD_READER
mrb_value
mrb_APR_TimeExp_get_tm_wday(mrb_state* mrb, mrb_value self) {
  apr_time_exp_t * native_self = mruby_unbox_apr_time_exp_t(self);

  apr_int32_t native_tm_wday = native_self->tm_wday;

  mrb_value tm_wday = mrb_fixnum_value(native_tm_wday);

  return tm_wday;
}
#endif
/* MRUBY_BINDING_END */

/* MRUBY_BINDING: TimeExp::tm_wday_writer */
/* sha: bd9a2ca4261677945f372491b2e5199357d220ce66d53630734472629abdabc7 */
#if BIND_TimeExp_tm_wday_FIELD_WRITER
mrb_value
mrb_APR_TimeExp_set_tm_wday(mrb_state* mrb, mrb_value self) {
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

/* MRUBY_BINDING: TimeExp::tm_yday_reader */
/* sha: 30e644bb9a307b1173e1cba6192ddd15ee88c44a687e4f158863f3981b746127 */
#if BIND_TimeExp_tm_yday_FIELD_READER
mrb_value
mrb_APR_TimeExp_get_tm_yday(mrb_state* mrb, mrb_value self) {
  apr_time_exp_t * native_self = mruby_unbox_apr_time_exp_t(self);

  apr_int32_t native_tm_yday = native_self->tm_yday;

  mrb_value tm_yday = mrb_fixnum_value(native_tm_yday);

  return tm_yday;
}
#endif
/* MRUBY_BINDING_END */

/* MRUBY_BINDING: TimeExp::tm_yday_writer */
/* sha: 018158f3d0eb6607c988020ea86bae042e22d7b2ea8b0c306efeee4fdc49fc9e */
#if BIND_TimeExp_tm_yday_FIELD_WRITER
mrb_value
mrb_APR_TimeExp_set_tm_yday(mrb_state* mrb, mrb_value self) {
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

/* MRUBY_BINDING: TimeExp::tm_isdst_reader */
/* sha: 9ec44ebc524bc5f0f3c18316c7aa321f8b4249a95561b231404aa39695918d22 */
#if BIND_TimeExp_tm_isdst_FIELD_READER
mrb_value
mrb_APR_TimeExp_get_tm_isdst(mrb_state* mrb, mrb_value self) {
  apr_time_exp_t * native_self = mruby_unbox_apr_time_exp_t(self);

  apr_int32_t native_tm_isdst = native_self->tm_isdst;

  mrb_value tm_isdst = mrb_fixnum_value(native_tm_isdst);

  return tm_isdst;
}
#endif
/* MRUBY_BINDING_END */

/* MRUBY_BINDING: TimeExp::tm_isdst_writer */
/* sha: 9c7dbeaaafacd5f4f73b17d9c571fbedd5e62fafc40309d90edafef4e966435a */
#if BIND_TimeExp_tm_isdst_FIELD_WRITER
mrb_value
mrb_APR_TimeExp_set_tm_isdst(mrb_state* mrb, mrb_value self) {
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

/* MRUBY_BINDING: TimeExp::tm_gmtoff_reader */
/* sha: 4603838277e6f78f9e47c02cbeeed73853a02bc2f1c477b4791dfc67a5c202f5 */
#if BIND_TimeExp_tm_gmtoff_FIELD_READER
mrb_value
mrb_APR_TimeExp_get_tm_gmtoff(mrb_state* mrb, mrb_value self) {
  apr_time_exp_t * native_self = mruby_unbox_apr_time_exp_t(self);

  apr_int32_t native_tm_gmtoff = native_self->tm_gmtoff;

  mrb_value tm_gmtoff = mrb_fixnum_value(native_tm_gmtoff);

  return tm_gmtoff;
}
#endif
/* MRUBY_BINDING_END */

/* MRUBY_BINDING: TimeExp::tm_gmtoff_writer */
/* sha: 9ddc886fc85acad4c629818ef6ab7ad08074a9cbcd77af8c47ce440c75ae08fd */
#if BIND_TimeExp_tm_gmtoff_FIELD_WRITER
mrb_value
mrb_APR_TimeExp_set_tm_gmtoff(mrb_state* mrb, mrb_value self) {
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


void mrb_APR_TimeExp_init(mrb_state* mrb) {
  static int initialized = 0;
  if (initialized) return;
  else initialized = 1;

/* MRUBY_BINDING: pre_class_definition */
/* sha: user_defined */

/* MRUBY_BINDING_END */

/* MRUBY_BINDING: TimeExp::class_definition */
/* sha: 88cce279d1003d1536a1a9087660e94dfb2dca8564369640654452313906e322 */
  struct RClass* TimeExp_class = mrb_define_class_under(mrb, APR_module(mrb), "TimeExp", mrb->object_class);
  MRB_SET_INSTANCE_TT(TimeExp_class, MRB_TT_DATA);
/* MRUBY_BINDING_END */

/* MRUBY_BINDING: TimeExp::pre_class_method_definitions */
/* sha: user_defined */

/* MRUBY_BINDING_END */

/* MRUBY_BINDING: TimeExp::class_method_definitions */
/* sha: 1d58cfa051d3309a6c6f45e7db4362c82909ca70a37a5a67595eb796e4b585eb */
#if BIND_TimeExp_INITIALIZE
  mrb_define_method(mrb, TimeExp_class, "initialize", mrb_APR_TimeExp_initialize, MRB_ARGS_NONE());
#endif
/* MRUBY_BINDING_END */

/* MRUBY_BINDING: TimeExp::pre_attr_definitions */
/* sha: user_defined */

/* MRUBY_BINDING_END */

/* MRUBY_BINDING: TimeExp::attr_definitions */
/* sha: 17971700ffa5f5de367324b4b3830f676ddb7ee8c9a8e533512e5cf52d327b66 */
  /*
   * Fields
   */
#if BIND_TimeExp_tm_usec_FIELD_READER
  mrb_define_method(mrb, TimeExp_class, "tm_usec", mrb_APR_TimeExp_get_tm_usec, MRB_ARGS_ARG(0, 0));
#endif
#if BIND_TimeExp_tm_usec_FIELD_WRITER
  mrb_define_method(mrb, TimeExp_class, "tm_usec=", mrb_APR_TimeExp_set_tm_usec, MRB_ARGS_ARG(1, 0));
#endif
#if BIND_TimeExp_tm_sec_FIELD_READER
  mrb_define_method(mrb, TimeExp_class, "tm_sec", mrb_APR_TimeExp_get_tm_sec, MRB_ARGS_ARG(0, 0));
#endif
#if BIND_TimeExp_tm_sec_FIELD_WRITER
  mrb_define_method(mrb, TimeExp_class, "tm_sec=", mrb_APR_TimeExp_set_tm_sec, MRB_ARGS_ARG(1, 0));
#endif
#if BIND_TimeExp_tm_min_FIELD_READER
  mrb_define_method(mrb, TimeExp_class, "tm_min", mrb_APR_TimeExp_get_tm_min, MRB_ARGS_ARG(0, 0));
#endif
#if BIND_TimeExp_tm_min_FIELD_WRITER
  mrb_define_method(mrb, TimeExp_class, "tm_min=", mrb_APR_TimeExp_set_tm_min, MRB_ARGS_ARG(1, 0));
#endif
#if BIND_TimeExp_tm_hour_FIELD_READER
  mrb_define_method(mrb, TimeExp_class, "tm_hour", mrb_APR_TimeExp_get_tm_hour, MRB_ARGS_ARG(0, 0));
#endif
#if BIND_TimeExp_tm_hour_FIELD_WRITER
  mrb_define_method(mrb, TimeExp_class, "tm_hour=", mrb_APR_TimeExp_set_tm_hour, MRB_ARGS_ARG(1, 0));
#endif
#if BIND_TimeExp_tm_mday_FIELD_READER
  mrb_define_method(mrb, TimeExp_class, "tm_mday", mrb_APR_TimeExp_get_tm_mday, MRB_ARGS_ARG(0, 0));
#endif
#if BIND_TimeExp_tm_mday_FIELD_WRITER
  mrb_define_method(mrb, TimeExp_class, "tm_mday=", mrb_APR_TimeExp_set_tm_mday, MRB_ARGS_ARG(1, 0));
#endif
#if BIND_TimeExp_tm_mon_FIELD_READER
  mrb_define_method(mrb, TimeExp_class, "tm_mon", mrb_APR_TimeExp_get_tm_mon, MRB_ARGS_ARG(0, 0));
#endif
#if BIND_TimeExp_tm_mon_FIELD_WRITER
  mrb_define_method(mrb, TimeExp_class, "tm_mon=", mrb_APR_TimeExp_set_tm_mon, MRB_ARGS_ARG(1, 0));
#endif
#if BIND_TimeExp_tm_year_FIELD_READER
  mrb_define_method(mrb, TimeExp_class, "tm_year", mrb_APR_TimeExp_get_tm_year, MRB_ARGS_ARG(0, 0));
#endif
#if BIND_TimeExp_tm_year_FIELD_WRITER
  mrb_define_method(mrb, TimeExp_class, "tm_year=", mrb_APR_TimeExp_set_tm_year, MRB_ARGS_ARG(1, 0));
#endif
#if BIND_TimeExp_tm_wday_FIELD_READER
  mrb_define_method(mrb, TimeExp_class, "tm_wday", mrb_APR_TimeExp_get_tm_wday, MRB_ARGS_ARG(0, 0));
#endif
#if BIND_TimeExp_tm_wday_FIELD_WRITER
  mrb_define_method(mrb, TimeExp_class, "tm_wday=", mrb_APR_TimeExp_set_tm_wday, MRB_ARGS_ARG(1, 0));
#endif
#if BIND_TimeExp_tm_yday_FIELD_READER
  mrb_define_method(mrb, TimeExp_class, "tm_yday", mrb_APR_TimeExp_get_tm_yday, MRB_ARGS_ARG(0, 0));
#endif
#if BIND_TimeExp_tm_yday_FIELD_WRITER
  mrb_define_method(mrb, TimeExp_class, "tm_yday=", mrb_APR_TimeExp_set_tm_yday, MRB_ARGS_ARG(1, 0));
#endif
#if BIND_TimeExp_tm_isdst_FIELD_READER
  mrb_define_method(mrb, TimeExp_class, "tm_isdst", mrb_APR_TimeExp_get_tm_isdst, MRB_ARGS_ARG(0, 0));
#endif
#if BIND_TimeExp_tm_isdst_FIELD_WRITER
  mrb_define_method(mrb, TimeExp_class, "tm_isdst=", mrb_APR_TimeExp_set_tm_isdst, MRB_ARGS_ARG(1, 0));
#endif
#if BIND_TimeExp_tm_gmtoff_FIELD_READER
  mrb_define_method(mrb, TimeExp_class, "tm_gmtoff", mrb_APR_TimeExp_get_tm_gmtoff, MRB_ARGS_ARG(0, 0));
#endif
#if BIND_TimeExp_tm_gmtoff_FIELD_WRITER
  mrb_define_method(mrb, TimeExp_class, "tm_gmtoff=", mrb_APR_TimeExp_set_tm_gmtoff, MRB_ARGS_ARG(1, 0));
#endif
/* MRUBY_BINDING_END */


/* MRUBY_BINDING: TimeExp::post_class_definition */
/* sha: user_defined */

/* MRUBY_BINDING_END */
}

/* MRUBY_BINDING: footer */
/* sha: user_defined */

/* MRUBY_BINDING_END */
#endif
