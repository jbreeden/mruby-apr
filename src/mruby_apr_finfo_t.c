/* - MRUBY_BINDINGS_NO_CLOBBER -
 * apr_finfo_t
 * Defined in file apr_file_info.h @ line 143
 */
 
#include "mruby_APR.h"

#if BIND_Finfo_TYPE

mrb_value
mrb_APR_Finfo_initialize(mrb_state* mrb, mrb_value self) {
  apr_finfo_t* native_object = (apr_finfo_t*)malloc(sizeof(apr_finfo_t));
  mruby_gift_apr_finfo_t_data_ptr(self, native_object);
  return self;
}

mrb_value
mrb_APR_Finfo_get_pool(mrb_state* mrb, mrb_value self) {
  apr_finfo_t * native_self = mruby_unbox_apr_finfo_t(self);

  apr_pool_t * native_field = native_self->pool;

  mrb_value ruby_field = (native_field == NULL ? mrb_nil_value() : mruby_box_apr_pool_t(mrb, native_field));
  /* Store the ruby object to prevent garage collection of the underlying native object */
  mrb_iv_set(mrb, self, mrb_intern_cstr(mrb, "@pool_box"), ruby_field);

  return ruby_field;
}

mrb_value
mrb_APR_Finfo_get_valid(mrb_state* mrb, mrb_value self) {
  apr_finfo_t * native_self = mruby_unbox_apr_finfo_t(self);
  apr_int32_t native_field = native_self->valid;
  mrb_value ruby_field = mrb_fixnum_value(native_field);
  return ruby_field;
}


mrb_value
mrb_APR_Finfo_get_protection(mrb_state* mrb, mrb_value self) {
  apr_finfo_t * native_self = mruby_unbox_apr_finfo_t(self);
  apr_fileperms_t native_field = native_self->protection;
  mrb_value ruby_field = mrb_fixnum_value(native_field);
  return ruby_field;
}


mrb_value
mrb_APR_Finfo_get_filetype(mrb_state* mrb, mrb_value self) {
  apr_finfo_t * native_self = mruby_unbox_apr_finfo_t(self);
  apr_filetype_e native_field = native_self->filetype;
  mrb_value ruby_field = mrb_fixnum_value(native_field);
  return ruby_field;
}


mrb_value
mrb_APR_Finfo_get_device(mrb_state* mrb, mrb_value self) {
  apr_finfo_t * native_self = mruby_unbox_apr_finfo_t(self);
  apr_dev_t native_field = native_self->device;
  mrb_value ruby_field = mrb_fixnum_value(native_field);
  return ruby_field;
}

mrb_value
mrb_APR_Finfo_get_nlink(mrb_state* mrb, mrb_value self) {
  apr_finfo_t * native_self = mruby_unbox_apr_finfo_t(self);
  apr_int32_t native_field = native_self->nlink;
  if (native_field > MRB_INT_MAX) {
    mrb_raise(mrb, mrb->eStandardError_class, "MRuby cannot represent integers greater than MRB_INT_MAX");
    return mrb_nil_value();
  }
  mrb_value ruby_field = mrb_fixnum_value(native_field);
  return ruby_field;
}

mrb_value
mrb_APR_Finfo_get_size(mrb_state* mrb, mrb_value self) {
  apr_finfo_t * native_self = mruby_unbox_apr_finfo_t(self);
  apr_off_t native_field = native_self->size;
  if (native_field > MRB_INT_MAX) {
     mrb_raise(mrb, mrb->eStandardError_class, "MRuby cannot represent integers greater than MRB_INT_MAX");
     return mrb_nil_value();
  }
  mrb_value ruby_field = mrb_fixnum_value(native_field);
  return ruby_field;
}

mrb_value
mrb_APR_Finfo_get_csize(mrb_state* mrb, mrb_value self) {
  apr_finfo_t * native_self = mruby_unbox_apr_finfo_t(self);
  apr_off_t native_field = native_self->csize;
  if (native_field > MRB_INT_MAX) {
     mrb_raise(mrb, mrb->eStandardError_class, "MRuby cannot represent integers greater than MRB_INT_MAX");
     return mrb_nil_value();
  }
  mrb_value ruby_field = mrb_fixnum_value(native_field);
  return ruby_field;
}

mrb_value
mrb_APR_Finfo_get_atime(mrb_state* mrb, mrb_value self) {
  apr_finfo_t * native_self = mruby_unbox_apr_finfo_t(self);
  return mrb_fixnum_value(native_self->atime);
}

mrb_value
mrb_APR_Finfo_get_mtime(mrb_state* mrb, mrb_value self) {
  apr_finfo_t * native_self = mruby_unbox_apr_finfo_t(self);
  return mrb_fixnum_value(native_self->mtime);
}

mrb_value
mrb_APR_Finfo_get_ctime(mrb_state* mrb, mrb_value self) {
   apr_finfo_t * native_self = mruby_unbox_apr_finfo_t(self);
   return mrb_fixnum_value(native_self->ctime);
}

mrb_value
mrb_APR_Finfo_get_fname(mrb_state* mrb, mrb_value self) {
  apr_finfo_t * native_self = mruby_unbox_apr_finfo_t(self);
  const char * native_field = native_self->fname;
  mrb_value ruby_field = mrb_str_new_cstr(mrb, native_field);
  return ruby_field;
}

mrb_value
mrb_APR_Finfo_get_name(mrb_state* mrb, mrb_value self) {
  apr_finfo_t * native_self = mruby_unbox_apr_finfo_t(self);
  const char * native_field = native_self->name;
  mrb_value ruby_field = mrb_str_new_cstr(mrb, native_field);
  return ruby_field;
}

mrb_value
mrb_APR_Finfo_get_filehand(mrb_state* mrb, mrb_value self) {
  apr_finfo_t * native_self = mruby_unbox_apr_finfo_t(self);
  struct apr_file_t * native_field = native_self->filehand;
  mrb_value ruby_field = (native_field == NULL ? mrb_nil_value() : mruby_box_apr_file_t(mrb, native_field));
  return ruby_field;
}


void mrb_APR_Finfo_init(mrb_state* mrb) {
  struct RClass* Finfo_class = mrb_define_class_under(mrb, APR_module(mrb), "Finfo", mrb->object_class);
  MRB_SET_INSTANCE_TT(Finfo_class, MRB_TT_DATA);

  mrb_define_method(mrb, Finfo_class, "initialize", mrb_APR_Finfo_initialize, MRB_ARGS_NONE());

  mrb_define_method(mrb, Finfo_class, "pool", mrb_APR_Finfo_get_pool, MRB_ARGS_ARG(0, 0));
  mrb_define_method(mrb, Finfo_class, "valid", mrb_APR_Finfo_get_valid, MRB_ARGS_ARG(0, 0));
  mrb_define_method(mrb, Finfo_class, "protection", mrb_APR_Finfo_get_protection, MRB_ARGS_ARG(0, 0));
  mrb_define_method(mrb, Finfo_class, "filetype", mrb_APR_Finfo_get_filetype, MRB_ARGS_ARG(0, 0));
  mrb_define_method(mrb, Finfo_class, "device", mrb_APR_Finfo_get_device, MRB_ARGS_ARG(0, 0));
  mrb_define_method(mrb, Finfo_class, "nlink", mrb_APR_Finfo_get_nlink, MRB_ARGS_ARG(0, 0));
  mrb_define_method(mrb, Finfo_class, "size", mrb_APR_Finfo_get_size, MRB_ARGS_ARG(0, 0));
  mrb_define_method(mrb, Finfo_class, "csize", mrb_APR_Finfo_get_csize, MRB_ARGS_ARG(0, 0));
  mrb_define_method(mrb, Finfo_class, "atime", mrb_APR_Finfo_get_atime, MRB_ARGS_ARG(0, 0));
  mrb_define_method(mrb, Finfo_class, "mtime", mrb_APR_Finfo_get_mtime, MRB_ARGS_ARG(0, 0));
  mrb_define_method(mrb, Finfo_class, "ctime", mrb_APR_Finfo_get_ctime, MRB_ARGS_ARG(0, 0));
  mrb_define_method(mrb, Finfo_class, "fname", mrb_APR_Finfo_get_fname, MRB_ARGS_ARG(0, 0));
  mrb_define_method(mrb, Finfo_class, "name", mrb_APR_Finfo_get_name, MRB_ARGS_ARG(0, 0));
  mrb_define_method(mrb, Finfo_class, "filehand", mrb_APR_Finfo_get_filehand, MRB_ARGS_ARG(0, 0));

}

#endif
