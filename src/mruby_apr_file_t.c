/*
 * apr_file_t
 * Defined in file apr_file_info.h @ line 212
 */

#include "mruby_APR.h"

#if BIND_AprFileT_TYPE

/* MRUBY_BINDING: header */
/* sha: user_defined */

/* MRUBY_BINDING_END */

/* MRUBY_BINDING: AprFileT::initialize */
/* sha: ad752012bb3077691103841716a38b406cd006b6078ef49ad8187bc182baf3a9 */
#if BIND_AprFileT_INITIALIZE
mrb_value
mrb_APR_AprFileT_initialize(mrb_state* mrb, mrb_value self) {
  mrb_raise(mrb, E_NOMETHOD_ERROR, "No initializer defined");
/* 
  apr_file_t* native_object = (apr_file_t*)calloc(1, sizeof(apr_file_t));
  mruby_gift_apr_file_t_data_ptr(self, native_object);
  return self;
*/
}
#endif
/* MRUBY_BINDING_END */


void mrb_APR_AprFileT_init(mrb_state* mrb) {
  static int initialized = 0;
  if (initialized) return;
  else initialized = 1;

/* MRUBY_BINDING: pre_class_definition */
/* sha: user_defined */

/* MRUBY_BINDING_END */

/* MRUBY_BINDING: AprFileT::class_definition */
/* sha: 9d421e7e23c120fca14c8204fb0ae70e97e1d102c798e3deab2a3783343651dd */
  struct RClass* AprFileT_class = mrb_define_class_under(mrb, APR_module(mrb), "AprFileT", mrb->object_class);
  MRB_SET_INSTANCE_TT(AprFileT_class, MRB_TT_DATA);
/* MRUBY_BINDING_END */

/* MRUBY_BINDING: AprFileT::pre_class_method_definitions */
/* sha: user_defined */

/* MRUBY_BINDING_END */

/* MRUBY_BINDING: AprFileT::class_method_definitions */
/* sha: d56ea486ecd8f29a40db525f3f81e2926833b0a8fadb34cdfc6874f2b6cd66e7 */
#if BIND_AprFileT_INITIALIZE
  mrb_define_method(mrb, AprFileT_class, "initialize", mrb_APR_AprFileT_initialize, MRB_ARGS_NONE());
#endif
/* MRUBY_BINDING_END */



/* MRUBY_BINDING: AprFileT::post_class_definition */
/* sha: user_defined */

/* MRUBY_BINDING_END */
}

/* MRUBY_BINDING: footer */
/* sha: user_defined */

/* MRUBY_BINDING_END */
#endif
