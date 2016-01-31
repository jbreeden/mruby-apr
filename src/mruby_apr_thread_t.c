/*
 * apr_thread_t
 * Defined in file apr_thread_proc.h @ line 177
 */

#include "mruby_APR.h"

#if BIND_Thread_TYPE

/* MRUBY_BINDING: header */
/* sha: user_defined */

/* MRUBY_BINDING_END */

/* MRUBY_BINDING: Thread::initialize */
/* sha: eca0695fb0dc749d2c76e2f42e43a25d03d8c0d881b640a4695b4f67ea6ce432 */
#if BIND_Thread_INITIALIZE
mrb_value
mrb_APR_Thread_initialize(mrb_state* mrb, mrb_value self) {
  mrb_raise(mrb, E_NOMETHOD_ERROR, "No initializer defined");
/* 
  apr_thread_t* native_object = (apr_thread_t*)calloc(1, sizeof(apr_thread_t));
  mruby_gift_apr_thread_t_data_ptr(self, native_object);
  return self;
*/
}
#endif
/* MRUBY_BINDING_END */


void mrb_APR_Thread_init(mrb_state* mrb) {
  static int initialized = 0;
  if (initialized) return;
  else initialized = 1;

/* MRUBY_BINDING: pre_class_definition */
/* sha: user_defined */

/* MRUBY_BINDING_END */

/* MRUBY_BINDING: Thread::class_definition */
/* sha: b1f41192ab79473ff0b5482cddfcd4fb5cdccd7a58afcabbfd158d0611535d47 */
  struct RClass* Thread_class = mrb_define_class_under(mrb, APR_module(mrb), "Thread", mrb->object_class);
  MRB_SET_INSTANCE_TT(Thread_class, MRB_TT_DATA);
/* MRUBY_BINDING_END */

/* MRUBY_BINDING: Thread::pre_class_method_definitions */
/* sha: user_defined */

/* MRUBY_BINDING_END */

/* MRUBY_BINDING: Thread::class_method_definitions */
/* sha: 1d30cd1cd6706e0963a9cec615deb6793aa4ca9ae4bac6567b0e640e658b7d96 */
#if BIND_Thread_INITIALIZE
  mrb_define_method(mrb, Thread_class, "initialize", mrb_APR_Thread_initialize, MRB_ARGS_NONE());
#endif
/* MRUBY_BINDING_END */



/* MRUBY_BINDING: Thread::post_class_definition */
/* sha: user_defined */

/* MRUBY_BINDING_END */
}

/* MRUBY_BINDING: footer */
/* sha: user_defined */

/* MRUBY_BINDING_END */
#endif
