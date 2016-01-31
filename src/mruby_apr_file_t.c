/*
 * apr_file_t
 * Defined in file apr_file_info.h @ line 212
 */

#include "mruby_APR.h"

#if BIND_File_TYPE

/* MRUBY_BINDING: header */
/* sha: user_defined */

/* MRUBY_BINDING_END */

/* MRUBY_BINDING: File::initialize */
/* sha: 7fb1148a0e01622586ac548c8cfae4578c8004d50526f93ebac9ed34d3a3af0e */
#if BIND_File_INITIALIZE
mrb_value
mrb_APR_File_initialize(mrb_state* mrb, mrb_value self) {
  mrb_raise(mrb, E_NOMETHOD_ERROR, "No initializer defined");
/* 
  apr_file_t* native_object = (apr_file_t*)calloc(1, sizeof(apr_file_t));
  mruby_gift_apr_file_t_data_ptr(self, native_object);
  return self;
*/
}
#endif
/* MRUBY_BINDING_END */


void mrb_APR_File_init(mrb_state* mrb) {
  static int initialized = 0;
  if (initialized) return;
  else initialized = 1;

/* MRUBY_BINDING: pre_class_definition */
/* sha: user_defined */

/* MRUBY_BINDING_END */

/* MRUBY_BINDING: File::class_definition */
/* sha: b69fb80aeec311c3f2dd37f1a8fad37541260b56ae6d8b996fda2021d56df681 */
  struct RClass* File_class = mrb_define_class_under(mrb, APR_module(mrb), "File", mrb->object_class);
  MRB_SET_INSTANCE_TT(File_class, MRB_TT_DATA);
/* MRUBY_BINDING_END */

/* MRUBY_BINDING: File::pre_class_method_definitions */
/* sha: user_defined */

/* MRUBY_BINDING_END */

/* MRUBY_BINDING: File::class_method_definitions */
/* sha: f45ddcd7e71c27adc3f1cf68b46c63e1c3333580d941e69087c0f33dce7b071c */
#if BIND_File_INITIALIZE
  mrb_define_method(mrb, File_class, "initialize", mrb_APR_File_initialize, MRB_ARGS_NONE());
#endif
/* MRUBY_BINDING_END */



/* MRUBY_BINDING: File::post_class_definition */
/* sha: user_defined */

/* MRUBY_BINDING_END */
}

/* MRUBY_BINDING: footer */
/* sha: user_defined */

/* MRUBY_BINDING_END */
#endif
