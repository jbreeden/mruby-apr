/*
 * apr_proc_t
 * Defined in file apr_thread_proc.h @ line 133
 */

#include "mruby_APR.h"

#if BIND_AprProcT_TYPE

/* MRUBY_BINDING: header */
/* sha: user_defined */

/* MRUBY_BINDING_END */

/* MRUBY_BINDING: AprProcT::initialize */
/* sha: f7853bdf8ac5f48dde8ebb44bb5a2b7192c658046a155d523452de9d48e3a91e */
#if BIND_AprProcT_INITIALIZE
mrb_value
mrb_APR_AprProcT_initialize(mrb_state* mrb, mrb_value self) {
  mrb_raise(mrb, E_NOMETHOD_ERROR, "No initializer defined");
/* 
  apr_proc_t* native_object = (apr_proc_t*)calloc(1, sizeof(apr_proc_t));
  mruby_gift_apr_proc_t_data_ptr(self, native_object);
  return self;
*/
}
#endif
/* MRUBY_BINDING_END */

/*
 * Fields
 */

/* MRUBY_BINDING: AprProcT::pid_reader */
/* sha: 6facb654e8b022237ebf7529eeb629e5e2ec2ba47df2df709fe2fb2656479da5 */
#if BIND_AprProcT_pid_FIELD_READER
mrb_value
mrb_APR_AprProcT_get_pid(mrb_state* mrb, mrb_value self) {
  apr_proc_t * native_self = mruby_unbox_apr_proc_t(self);

  pid_t native_pid = native_self->pid;

  mrb_value pid = TODO_mruby_box_pid_t(mrb, native_pid);

  return pid;
}
#endif
/* MRUBY_BINDING_END */

/* MRUBY_BINDING: AprProcT::pid_writer */
/* sha: 7f4ff21f02faf8dcdde3624772b87ca539986571b63f559fc454bbf50775a0f0 */
#if BIND_AprProcT_pid_FIELD_WRITER
mrb_value
mrb_APR_AprProcT_set_pid(mrb_state* mrb, mrb_value self) {
  apr_proc_t * native_self = mruby_unbox_apr_proc_t(self);
  mrb_value pid;

  mrb_get_args(mrb, "o", &pid);

  /* type checking */
  TODO_type_check_pid_t(pid);

  pid_t native_pid = TODO_mruby_unbox_pid_t(pid);

  native_self->pid = native_pid;
  
  mrb_value value_as_mrb_value;
  mrb_get_args(mrb, "o", &value_as_mrb_value);
  return value_as_mrb_value;
}
#endif
/* MRUBY_BINDING_END */

/* MRUBY_BINDING: AprProcT::in_reader */
/* sha: 18a11e8e72b7a203718f4d5f423a553a2188b0ceab8bf03cdeb6424ec38d1527 */
#if BIND_AprProcT_in_FIELD_READER
mrb_value
mrb_APR_AprProcT_get_in(mrb_state* mrb, mrb_value self) {
  apr_proc_t * native_self = mruby_unbox_apr_proc_t(self);

  apr_file_t * native_in = native_self->in;

  mrb_value in = (native_in == NULL ? mrb_nil_value() : mruby_box_apr_file_t(mrb, native_in));

  return in;
}
#endif
/* MRUBY_BINDING_END */

/* MRUBY_BINDING: AprProcT::in_writer */
/* sha: 21a220619fd38ed2766317e43f386cb15cca8e5536db04d943f4dfabda174c6b */
#if BIND_AprProcT_in_FIELD_WRITER
mrb_value
mrb_APR_AprProcT_set_in(mrb_state* mrb, mrb_value self) {
  apr_proc_t * native_self = mruby_unbox_apr_proc_t(self);
  mrb_value in;

  mrb_get_args(mrb, "o", &in);

  /* type checking */
  if (!mrb_obj_is_kind_of(mrb, in, AprFileT_class(mrb))) {
    mrb_raise(mrb, E_TYPE_ERROR, "AprFileT expected");
    return mrb_nil_value();
  }

  apr_file_t * native_in = (mrb_nil_p(in) ? NULL : mruby_unbox_apr_file_t(in));

  native_self->in = native_in;
  
  mrb_value value_as_mrb_value;
  mrb_get_args(mrb, "o", &value_as_mrb_value);
  return value_as_mrb_value;
}
#endif
/* MRUBY_BINDING_END */

/* MRUBY_BINDING: AprProcT::out_reader */
/* sha: 7301e174f06235fbef01f6e7c58f23a3a4b9ca947affd9d20dfb131832892484 */
#if BIND_AprProcT_out_FIELD_READER
mrb_value
mrb_APR_AprProcT_get_out(mrb_state* mrb, mrb_value self) {
  apr_proc_t * native_self = mruby_unbox_apr_proc_t(self);

  apr_file_t * native_out = native_self->out;

  mrb_value out = (native_out == NULL ? mrb_nil_value() : mruby_box_apr_file_t(mrb, native_out));

  return out;
}
#endif
/* MRUBY_BINDING_END */

/* MRUBY_BINDING: AprProcT::out_writer */
/* sha: a961caa08946a06b1ba72f3eb022e9067741075b0a72a6d02bba11970f8ec610 */
#if BIND_AprProcT_out_FIELD_WRITER
mrb_value
mrb_APR_AprProcT_set_out(mrb_state* mrb, mrb_value self) {
  apr_proc_t * native_self = mruby_unbox_apr_proc_t(self);
  mrb_value out;

  mrb_get_args(mrb, "o", &out);

  /* type checking */
  if (!mrb_obj_is_kind_of(mrb, out, AprFileT_class(mrb))) {
    mrb_raise(mrb, E_TYPE_ERROR, "AprFileT expected");
    return mrb_nil_value();
  }

  apr_file_t * native_out = (mrb_nil_p(out) ? NULL : mruby_unbox_apr_file_t(out));

  native_self->out = native_out;
  
  mrb_value value_as_mrb_value;
  mrb_get_args(mrb, "o", &value_as_mrb_value);
  return value_as_mrb_value;
}
#endif
/* MRUBY_BINDING_END */

/* MRUBY_BINDING: AprProcT::err_reader */
/* sha: 0e37031c35a562724e3a51f31b1db42d3e13a1ea0fe7836987f73422c1633bad */
#if BIND_AprProcT_err_FIELD_READER
mrb_value
mrb_APR_AprProcT_get_err(mrb_state* mrb, mrb_value self) {
  apr_proc_t * native_self = mruby_unbox_apr_proc_t(self);

  apr_file_t * native_err = native_self->err;

  mrb_value err = (native_err == NULL ? mrb_nil_value() : mruby_box_apr_file_t(mrb, native_err));

  return err;
}
#endif
/* MRUBY_BINDING_END */

/* MRUBY_BINDING: AprProcT::err_writer */
/* sha: 2dc45d374442cf866ace3fd2b38b06f41952e0942a9e990dc578c92f4b674da9 */
#if BIND_AprProcT_err_FIELD_WRITER
mrb_value
mrb_APR_AprProcT_set_err(mrb_state* mrb, mrb_value self) {
  apr_proc_t * native_self = mruby_unbox_apr_proc_t(self);
  mrb_value err;

  mrb_get_args(mrb, "o", &err);

  /* type checking */
  if (!mrb_obj_is_kind_of(mrb, err, AprFileT_class(mrb))) {
    mrb_raise(mrb, E_TYPE_ERROR, "AprFileT expected");
    return mrb_nil_value();
  }

  apr_file_t * native_err = (mrb_nil_p(err) ? NULL : mruby_unbox_apr_file_t(err));

  native_self->err = native_err;
  
  mrb_value value_as_mrb_value;
  mrb_get_args(mrb, "o", &value_as_mrb_value);
  return value_as_mrb_value;
}
#endif
/* MRUBY_BINDING_END */


void mrb_APR_AprProcT_init(mrb_state* mrb) {
  static int initialized = 0;
  if (initialized) return;
  else initialized = 1;

/* MRUBY_BINDING: pre_class_definition */
/* sha: user_defined */

/* MRUBY_BINDING_END */

/* MRUBY_BINDING: AprProcT::class_definition */
/* sha: 36a688e938d362130d5aca506e14d0a7e3c7865d11aeaeddbaeab63b522c73d9 */
  struct RClass* AprProcT_class = mrb_define_class_under(mrb, APR_module(mrb), "AprProcT", mrb->object_class);
  MRB_SET_INSTANCE_TT(AprProcT_class, MRB_TT_DATA);
/* MRUBY_BINDING_END */

/* MRUBY_BINDING: AprProcT::pre_class_method_definitions */
/* sha: user_defined */

/* MRUBY_BINDING_END */

/* MRUBY_BINDING: AprProcT::class_method_definitions */
/* sha: 694b0839ebb640e46958f5cd5ed0fd6e9a6971199bee085964c32bf5f1cd1e45 */
#if BIND_AprProcT_INITIALIZE
  mrb_define_method(mrb, AprProcT_class, "initialize", mrb_APR_AprProcT_initialize, MRB_ARGS_NONE());
#endif
/* MRUBY_BINDING_END */

/* MRUBY_BINDING: AprProcT::pre_attr_definitions */
/* sha: user_defined */

/* MRUBY_BINDING_END */

/* MRUBY_BINDING: AprProcT::attr_definitions */
/* sha: 706a57d2ac77c21214944d80593267568a04f4e02381f12c852c388fdaf41f6a */
  /*
   * Fields
   */
#if BIND_AprProcT_pid_FIELD_READER
  mrb_define_method(mrb, AprProcT_class, "pid", mrb_APR_AprProcT_get_pid, MRB_ARGS_ARG(0, 0));
#endif
#if BIND_AprProcT_pid_FIELD_WRITER
  mrb_define_method(mrb, AprProcT_class, "pid=", mrb_APR_AprProcT_set_pid, MRB_ARGS_ARG(1, 0));
#endif
#if BIND_AprProcT_in_FIELD_READER
  mrb_define_method(mrb, AprProcT_class, "in", mrb_APR_AprProcT_get_in, MRB_ARGS_ARG(0, 0));
#endif
#if BIND_AprProcT_in_FIELD_WRITER
  mrb_define_method(mrb, AprProcT_class, "in=", mrb_APR_AprProcT_set_in, MRB_ARGS_ARG(1, 0));
#endif
#if BIND_AprProcT_out_FIELD_READER
  mrb_define_method(mrb, AprProcT_class, "out", mrb_APR_AprProcT_get_out, MRB_ARGS_ARG(0, 0));
#endif
#if BIND_AprProcT_out_FIELD_WRITER
  mrb_define_method(mrb, AprProcT_class, "out=", mrb_APR_AprProcT_set_out, MRB_ARGS_ARG(1, 0));
#endif
#if BIND_AprProcT_err_FIELD_READER
  mrb_define_method(mrb, AprProcT_class, "err", mrb_APR_AprProcT_get_err, MRB_ARGS_ARG(0, 0));
#endif
#if BIND_AprProcT_err_FIELD_WRITER
  mrb_define_method(mrb, AprProcT_class, "err=", mrb_APR_AprProcT_set_err, MRB_ARGS_ARG(1, 0));
#endif
/* MRUBY_BINDING_END */


/* MRUBY_BINDING: AprProcT::post_class_definition */
/* sha: user_defined */

/* MRUBY_BINDING_END */
}

/* MRUBY_BINDING: footer */
/* sha: user_defined */

/* MRUBY_BINDING_END */
#endif
