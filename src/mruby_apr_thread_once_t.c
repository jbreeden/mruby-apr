/*
 * apr_thread_once_t
 * Defined in file apr_thread_proc.h @ line 186
 */

#include "mruby_APR.h"

#if BIND_ThreadOnce_TYPE

/* MRUBY_BINDING: header */
/* sha: user_defined */

/* MRUBY_BINDING_END */

/* MRUBY_BINDING: ThreadOnce::initialize */
/* sha: 9bd6cb728e920ece2e9da7fb41930099fbb4fa662ba46ea5e046fa90290fd348 */
#if BIND_ThreadOnce_INITIALIZE
mrb_value
mrb_APR_ThreadOnce_initialize(mrb_state* mrb, mrb_value self) {
  mrb_raise(mrb, E_NOMETHOD_ERROR, "No initializer defined");
/* 
  apr_thread_once_t* native_object = (apr_thread_once_t*)calloc(1, sizeof(apr_thread_once_t));
  mruby_gift_apr_thread_once_t_data_ptr(self, native_object);
  return self;
*/
}
#endif
/* MRUBY_BINDING_END */


void mrb_APR_ThreadOnce_init(mrb_state* mrb) {
  static int initialized = 0;
  if (initialized) return;
  else initialized = 1;

/* MRUBY_BINDING: pre_class_definition */
/* sha: user_defined */

/* MRUBY_BINDING_END */

/* MRUBY_BINDING: ThreadOnce::class_definition */
/* sha: 67e4c7428206bc2128c80b564b9bb377c9be9567e64b8330eab8997aa87dd302 */
  struct RClass* ThreadOnce_class = mrb_define_class_under(mrb, APR_module(mrb), "ThreadOnce", mrb->object_class);
  MRB_SET_INSTANCE_TT(ThreadOnce_class, MRB_TT_DATA);
/* MRUBY_BINDING_END */

/* MRUBY_BINDING: ThreadOnce::pre_class_method_definitions */
/* sha: user_defined */

/* MRUBY_BINDING_END */

/* MRUBY_BINDING: ThreadOnce::class_method_definitions */
/* sha: 6d454b3a48a061141bf745aebf4f4cbab59d11e5e6f0160e65677bad44e0c144 */
#if BIND_ThreadOnce_INITIALIZE
  mrb_define_method(mrb, ThreadOnce_class, "initialize", mrb_APR_ThreadOnce_initialize, MRB_ARGS_NONE());
#endif
/* MRUBY_BINDING_END */



/* MRUBY_BINDING: ThreadOnce::post_class_definition */
/* sha: user_defined */

/* MRUBY_BINDING_END */
}

/* MRUBY_BINDING: footer */
/* sha: user_defined */

/* MRUBY_BINDING_END */
#endif
