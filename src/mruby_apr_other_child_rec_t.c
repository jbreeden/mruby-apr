/*
 * apr_other_child_rec_t
 * Defined in file apr_thread_proc.h @ line 192
 */

#include "mruby_APR.h"

#if BIND_AprOtherChildRecT_TYPE

/* MRUBY_BINDING: header */
/* sha: user_defined */

/* MRUBY_BINDING_END */

/* MRUBY_BINDING: AprOtherChildRecT::initialize */
/* sha: 158a90c11e5e4c6d72d876341d0aea26f59457a11f5cc4d3fa8dd3a49dd70fcb */
#if BIND_AprOtherChildRecT_INITIALIZE
mrb_value
mrb_APR_AprOtherChildRecT_initialize(mrb_state* mrb, mrb_value self) {
  mrb_raise(mrb, E_NOMETHOD_ERROR, "No initializer defined");
/* 
  apr_other_child_rec_t* native_object = (apr_other_child_rec_t*)calloc(1, sizeof(apr_other_child_rec_t));
  mruby_gift_apr_other_child_rec_t_data_ptr(self, native_object);
  return self;
*/
}
#endif
/* MRUBY_BINDING_END */


void mrb_APR_AprOtherChildRecT_init(mrb_state* mrb) {
  static int initialized = 0;
  if (initialized) return;
  else initialized = 1;

/* MRUBY_BINDING: pre_class_definition */
/* sha: user_defined */

/* MRUBY_BINDING_END */

/* MRUBY_BINDING: AprOtherChildRecT::class_definition */
/* sha: ff9029653d580fb59cfb9ab4c7a9dc36abfc16b709ad79e0a6be650c41bce113 */
  struct RClass* AprOtherChildRecT_class = mrb_define_class_under(mrb, APR_module(mrb), "AprOtherChildRecT", mrb->object_class);
  MRB_SET_INSTANCE_TT(AprOtherChildRecT_class, MRB_TT_DATA);
/* MRUBY_BINDING_END */

/* MRUBY_BINDING: AprOtherChildRecT::pre_class_method_definitions */
/* sha: user_defined */

/* MRUBY_BINDING_END */

/* MRUBY_BINDING: AprOtherChildRecT::class_method_definitions */
/* sha: 553a175d18b53d9adb62ae261245ca52945349ea62df9363860214d9d217e15d */
#if BIND_AprOtherChildRecT_INITIALIZE
  mrb_define_method(mrb, AprOtherChildRecT_class, "initialize", mrb_APR_AprOtherChildRecT_initialize, MRB_ARGS_NONE());
#endif
/* MRUBY_BINDING_END */



/* MRUBY_BINDING: AprOtherChildRecT::post_class_definition */
/* sha: user_defined */

/* MRUBY_BINDING_END */
}

/* MRUBY_BINDING: footer */
/* sha: user_defined */

/* MRUBY_BINDING_END */
#endif
