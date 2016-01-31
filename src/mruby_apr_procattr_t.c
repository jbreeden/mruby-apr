/*
 * apr_procattr_t
 * Defined in file apr_thread_proc.h @ line 183
 */

#include "mruby_APR.h"

#if BIND_Procattr_TYPE

/* MRUBY_BINDING: header */
/* sha: user_defined */

/* MRUBY_BINDING_END */

/* MRUBY_BINDING: Procattr::initialize */
/* sha: f28c9d473065ee206f7b5eb54e026bf8d370af4a321fca9c8b00d74646f3059a */
#if BIND_Procattr_INITIALIZE
mrb_value
mrb_APR_Procattr_initialize(mrb_state* mrb, mrb_value self) {
  mrb_raise(mrb, E_NOMETHOD_ERROR, "No initializer defined");
/* 
  apr_procattr_t* native_object = (apr_procattr_t*)calloc(1, sizeof(apr_procattr_t));
  mruby_gift_apr_procattr_t_data_ptr(self, native_object);
  return self;
*/
}
#endif
/* MRUBY_BINDING_END */


void mrb_APR_Procattr_init(mrb_state* mrb) {
  static int initialized = 0;
  if (initialized) return;
  else initialized = 1;

/* MRUBY_BINDING: pre_class_definition */
/* sha: user_defined */

/* MRUBY_BINDING_END */

/* MRUBY_BINDING: Procattr::class_definition */
/* sha: e01959b617640fc05b2f45ce32f4a8c353d7ad541881291738ce242811e08108 */
  struct RClass* Procattr_class = mrb_define_class_under(mrb, APR_module(mrb), "Procattr", mrb->object_class);
  MRB_SET_INSTANCE_TT(Procattr_class, MRB_TT_DATA);
/* MRUBY_BINDING_END */

/* MRUBY_BINDING: Procattr::pre_class_method_definitions */
/* sha: user_defined */

/* MRUBY_BINDING_END */

/* MRUBY_BINDING: Procattr::class_method_definitions */
/* sha: f77f51ee019e9cf8085c28fe0c7cbeb94451a7d83bc13254d3a687cb64b502d2 */
#if BIND_Procattr_INITIALIZE
  mrb_define_method(mrb, Procattr_class, "initialize", mrb_APR_Procattr_initialize, MRB_ARGS_NONE());
#endif
/* MRUBY_BINDING_END */



/* MRUBY_BINDING: Procattr::post_class_definition */
/* sha: user_defined */

/* MRUBY_BINDING_END */
}

/* MRUBY_BINDING: footer */
/* sha: user_defined */

/* MRUBY_BINDING_END */
#endif
