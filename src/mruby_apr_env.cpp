#include "mruby.h"
#include "mruby_apr.h"
#include "mruby/string.h"
#include "apr.h"
#include "apr_pools.h"
#include "apr_env.h"

//<
// # object ENV
// ## `#[](name)`
// Returns the value of the environemnt variable named `name`
//>
mrb_value
mrb_apr_env_get(mrb_state* mrb, mrb_value self) {
   mrb_value key;
   mrb_get_args(mrb, "S", &key);
   
   char* key_cstr = mrb_str_to_cstr(mrb, key);
   apr_pool_t* pool;
   apr_pool_create(&pool, NULL);
   char* value;
   apr_status_t status = apr_env_get(&value, key_cstr, pool);

   mrb_value result;
   if (status == APR_SUCCESS) {
      result = mrb_str_new_cstr(mrb, value);
   }
   else {
      result = mrb_nil_value();
   }

   apr_pool_destroy(pool);
   return result;
}

//<
// ## `#[]=(name, value)`
// Sets the value of the environemnt variable named `name` to `value`
//>
mrb_value
mrb_apr_env_set(mrb_state* mrb, mrb_value self) {
   mrb_value key;
   mrb_value value;
   mrb_get_args(mrb, "SS", &key, &value);

   apr_pool_t* pool;
   apr_pool_create(&pool, NULL);
   char* key_cstr = mrb_str_to_cstr(mrb, key);
   char* value_cstr = mrb_str_to_cstr(mrb, value);
   apr_status_t status = apr_env_set(key_cstr, value_cstr, pool);
   apr_pool_destroy(pool);

   if (status == APR_SUCCESS) {
      return value;
   }
   else {
      return mrb_nil_value();
   }
}

//<
// ## `#delete(name)`
// Deletes the environemnt variable named `name`
//>
mrb_value
mrb_apr_env_delete(mrb_state* mrb, mrb_value self) {
   mrb_value key;
   mrb_get_args(mrb, "S", &key);

   char* key_cstr = mrb_str_to_cstr(mrb, key);

   char* value;
   apr_pool_t* pool;
   apr_pool_create(&pool, NULL);
   apr_status_t get_status = apr_env_get(&value, key_cstr, pool);

   if (get_status != APR_SUCCESS) {
      return mrb_nil_value();
   }

   mrb_value result = mrb_str_new_cstr(mrb, value);
   apr_status_t status = apr_env_delete(key_cstr, pool);
   apr_pool_destroy(pool);

   return result;
}

void mrb_mruby_apr_env_init(mrb_state* mrb, RClass* apr_module) {
   auto env = mrb_instance_new(mrb, mrb_obj_value(mrb->object_class));
   mrb_define_singleton_method(mrb, mrb_obj_ptr(env), "[]", mrb_apr_env_get, MRB_ARGS_REQ(1));
   mrb_define_singleton_method(mrb, mrb_obj_ptr(env), "[]=", mrb_apr_env_set, MRB_ARGS_REQ(2));
   mrb_define_singleton_method(mrb, mrb_obj_ptr(env), "delete", mrb_apr_env_delete, MRB_ARGS_REQ(1));
   mrb_define_global_const(mrb, "ENV", env);
}
