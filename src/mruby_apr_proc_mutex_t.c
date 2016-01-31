/*
 * apr_proc_mutex_t
 * Defined in file apr_proc_mutex.h @ line 54
 */

#include "mruby_APR.h"

#if BIND_ProcMutex_TYPE

/* MRUBY_BINDING: header */
/* sha: user_defined */

/* MRUBY_BINDING_END */

/* MRUBY_BINDING: ProcMutex::initialize */
/* sha: 2619695d73b69bccc0a6d3bf25cde2450ce683b21a04ba47f37ba416663cc8f6 */
#if BIND_ProcMutex_INITIALIZE
mrb_value
mrb_APR_ProcMutex_initialize(mrb_state* mrb, mrb_value self) {
  mrb_raise(mrb, E_NOMETHOD_ERROR, "No initializer defined");
/* 
  apr_proc_mutex_t* native_object = (apr_proc_mutex_t*)calloc(1, sizeof(apr_proc_mutex_t));
  mruby_gift_apr_proc_mutex_t_data_ptr(self, native_object);
  return self;
*/
}
#endif
/* MRUBY_BINDING_END */


void mrb_APR_ProcMutex_init(mrb_state* mrb) {
  static int initialized = 0;
  if (initialized) return;
  else initialized = 1;

/* MRUBY_BINDING: pre_class_definition */
/* sha: user_defined */

/* MRUBY_BINDING_END */

/* MRUBY_BINDING: ProcMutex::class_definition */
/* sha: b36705547566f5c49979781af8737d3646e1ed9fcd8b6cbe043c41bf306eb9f9 */
  struct RClass* ProcMutex_class = mrb_define_class_under(mrb, APR_module(mrb), "ProcMutex", mrb->object_class);
  MRB_SET_INSTANCE_TT(ProcMutex_class, MRB_TT_DATA);
/* MRUBY_BINDING_END */

/* MRUBY_BINDING: ProcMutex::pre_class_method_definitions */
/* sha: user_defined */

/* MRUBY_BINDING_END */

/* MRUBY_BINDING: ProcMutex::class_method_definitions */
/* sha: b3319f3ac53a91046d80f0e2e80c8cf2636ace82242957605bd0c0ce62eb8717 */
#if BIND_ProcMutex_INITIALIZE
  mrb_define_method(mrb, ProcMutex_class, "initialize", mrb_APR_ProcMutex_initialize, MRB_ARGS_NONE());
#endif
/* MRUBY_BINDING_END */



/* MRUBY_BINDING: ProcMutex::post_class_definition */
/* sha: user_defined */

/* MRUBY_BINDING_END */
}

/* MRUBY_BINDING: footer */
/* sha: user_defined */

/* MRUBY_BINDING_END */
#endif
