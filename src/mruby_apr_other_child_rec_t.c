/*
 * apr_other_child_rec_t
 * Defined in file apr_thread_proc.h @ line 192
 */

#include "mruby_APR.h"

#if BIND_OtherChildRec_TYPE

/* MRUBY_BINDING: header */
/* sha: user_defined */

/* MRUBY_BINDING_END */

/* MRUBY_BINDING: OtherChildRec::initialize */
/* sha: 81afc0525883aaca96c40db02853ebac43af9d9fec62ff3376f6fc54e4d4bfb1 */
#if BIND_OtherChildRec_INITIALIZE
mrb_value
mrb_APR_OtherChildRec_initialize(mrb_state* mrb, mrb_value self) {
  mrb_raise(mrb, E_NOMETHOD_ERROR, "No initializer defined");
/* 
  apr_other_child_rec_t* native_object = (apr_other_child_rec_t*)calloc(1, sizeof(apr_other_child_rec_t));
  mruby_gift_apr_other_child_rec_t_data_ptr(self, native_object);
  return self;
*/
}
#endif
/* MRUBY_BINDING_END */


void mrb_APR_OtherChildRec_init(mrb_state* mrb) {
  static int initialized = 0;
  if (initialized) return;
  else initialized = 1;

/* MRUBY_BINDING: pre_class_definition */
/* sha: user_defined */

/* MRUBY_BINDING_END */

/* MRUBY_BINDING: OtherChildRec::class_definition */
/* sha: 60246a90d5a6be009fdeed81404951eef297f402e9baa72ab50c335065aa647c */
  struct RClass* OtherChildRec_class = mrb_define_class_under(mrb, APR_module(mrb), "OtherChildRec", mrb->object_class);
  MRB_SET_INSTANCE_TT(OtherChildRec_class, MRB_TT_DATA);
/* MRUBY_BINDING_END */

/* MRUBY_BINDING: OtherChildRec::pre_class_method_definitions */
/* sha: user_defined */

/* MRUBY_BINDING_END */

/* MRUBY_BINDING: OtherChildRec::class_method_definitions */
/* sha: 262e9bb11f26b26bf2d13043b2d4e88800d55b850c7e4c54928b49c04a0798e3 */
#if BIND_OtherChildRec_INITIALIZE
  mrb_define_method(mrb, OtherChildRec_class, "initialize", mrb_APR_OtherChildRec_initialize, MRB_ARGS_NONE());
#endif
/* MRUBY_BINDING_END */



/* MRUBY_BINDING: OtherChildRec::post_class_definition */
/* sha: user_defined */

/* MRUBY_BINDING_END */
}

/* MRUBY_BINDING: footer */
/* sha: user_defined */

/* MRUBY_BINDING_END */
#endif
