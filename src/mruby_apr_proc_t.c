/* - MRUBY_BINDINGS_NO_CLOBBER -
 * apr_proc_t
 * Defined in file apr_thread_proc.h @ line 133
 */

#include "mruby_APR.h"

#if BIND_Proc_TYPE

mrb_value
mrb_APR_Proc_initialize(mrb_state* mrb, mrb_value self) {
  apr_proc_t* native_object = (apr_proc_t*)malloc(sizeof(apr_proc_t));
  mruby_gift_apr_proc_t_data_ptr(self, native_object);
  return self;
}

mrb_value
mrb_APR_Proc_get_pid(mrb_state* mrb, mrb_value self) {
  apr_proc_t * native_self = mruby_unbox_apr_proc_t(self);
  pid_t native_field = native_self->pid;
  mrb_value ruby_field = mrb_fixnum_value(native_field);
  return ruby_field;
}

mrb_value
mrb_APR_Proc_get_in(mrb_state* mrb, mrb_value self) {
  apr_proc_t * native_self = mruby_unbox_apr_proc_t(self);
  apr_file_t * native_field = native_self->in;
  mrb_value ruby_field = (native_field == NULL ? mrb_nil_value() : mruby_box_apr_file_t(mrb, native_field));
  return ruby_field;
}

mrb_value
mrb_APR_Proc_get_out(mrb_state* mrb, mrb_value self) {
  apr_proc_t * native_self = mruby_unbox_apr_proc_t(self);
  apr_file_t * native_field = native_self->out;
  mrb_value ruby_field = (native_field == NULL ? mrb_nil_value() : mruby_box_apr_file_t(mrb, native_field));
  return ruby_field;
}

mrb_value
mrb_APR_Proc_get_err(mrb_state* mrb, mrb_value self) {
  apr_proc_t * native_self = mruby_unbox_apr_proc_t(self);
  apr_file_t * native_field = native_self->err;
  mrb_value ruby_field = (native_field == NULL ? mrb_nil_value() : mruby_box_apr_file_t(mrb, native_field));
  return ruby_field;
}

void mrb_APR_Proc_init(mrb_state* mrb) {
  struct RClass* Proc_class = mrb_define_class_under(mrb, APR_module(mrb), "Proc", mrb->object_class);
  MRB_SET_INSTANCE_TT(Proc_class, MRB_TT_DATA);

  mrb_define_method(mrb, Proc_class, "initialize", mrb_APR_Proc_initialize, MRB_ARGS_NONE());

  mrb_define_method(mrb, Proc_class, "pid", mrb_APR_Proc_get_pid, MRB_ARGS_ARG(0, 0));
  mrb_define_method(mrb, Proc_class, "in", mrb_APR_Proc_get_in, MRB_ARGS_ARG(0, 0));
  mrb_define_method(mrb, Proc_class, "out", mrb_APR_Proc_get_out, MRB_ARGS_ARG(0, 0));
  mrb_define_method(mrb, Proc_class, "err", mrb_APR_Proc_get_err, MRB_ARGS_ARG(0, 0));
}

#endif
