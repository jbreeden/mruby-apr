/*
 * apr_pool_t
 * Defined in file apr_pools.h @ line 60
 */

#include "mruby_APR.h"

#if BIND_Pool_TYPE

/* MRUBY_BINDING: header */
/* sha: user_defined */

/* MRUBY_BINDING_END */

/* MRUBY_BINDING: Pool::initialize */
/* sha: 188a895df6ae319edaabc00533d3faa5487c060ec49b9bb6b04765fa8ad39340 */
#if BIND_Pool_INITIALIZE
mrb_value
mrb_APR_Pool_initialize(mrb_state* mrb, mrb_value self) {
  mrb_raise(mrb, E_NOMETHOD_ERROR, "No initializer defined");
/* 
  apr_pool_t* native_object = (apr_pool_t*)calloc(1, sizeof(apr_pool_t));
  mruby_gift_apr_pool_t_data_ptr(self, native_object);
  return self;
*/
}
#endif
/* MRUBY_BINDING_END */


void mrb_APR_Pool_init(mrb_state* mrb) {
  static int initialized = 0;
  if (initialized) return;
  else initialized = 1;

/* MRUBY_BINDING: pre_class_definition */
/* sha: user_defined */

/* MRUBY_BINDING_END */

/* MRUBY_BINDING: Pool::class_definition */
/* sha: 5075c7cb95f4205b6c43e98ba02e2898126a85beb5ff1dbd026782ffaa3ed48d */
  struct RClass* Pool_class = mrb_define_class_under(mrb, APR_module(mrb), "Pool", mrb->object_class);
  MRB_SET_INSTANCE_TT(Pool_class, MRB_TT_DATA);
/* MRUBY_BINDING_END */

/* MRUBY_BINDING: Pool::pre_class_method_definitions */
/* sha: user_defined */

/* MRUBY_BINDING_END */

/* MRUBY_BINDING: Pool::class_method_definitions */
/* sha: ad3762668a91ddc8a364ac98ed88530023c05663bb065f37533eccddf609e1f1 */
#if BIND_Pool_INITIALIZE
  mrb_define_method(mrb, Pool_class, "initialize", mrb_APR_Pool_initialize, MRB_ARGS_NONE());
#endif
/* MRUBY_BINDING_END */



/* MRUBY_BINDING: Pool::post_class_definition */
/* sha: user_defined */

/* MRUBY_BINDING_END */
}

/* MRUBY_BINDING: footer */
/* sha: user_defined */

/* MRUBY_BINDING_END */
#endif
