#include <thread>
#include <chrono>
#include "mruby.h"
#include "mruby_apr.h"

using namespace std;

//<
// # Module APR::System
//>

//<
// ## `::sleep(count, unit)`
// - Args
//   + `count`: the number of `units` to sleep for (must be an integer)
//   + `unit`: One of
//     - :microseconds
//     - :milliseconds
//     - :seconds
//     - :minutes
//     - :hours
//>
mrb_value
mrb_apr_system_sleep(mrb_state*  mrb, mrb_value self) {
   mrb_int count;
   mrb_sym unit;
   mrb_get_args(mrb, "in", &count, &unit);

   if (count < 0) {
      mrb_raise(mrb, mrb->eStandardError_class, "Cannot sleep for negative time");
      return mrb_nil_value();
   }

   if (count > LONG_MAX) {
      mrb_raise(mrb, mrb->eStandardError_class, "Count too large to convert to long");
      return mrb_nil_value();
   }

   if (SYM_CHECK(unit, microseconds))  {
      this_thread::sleep_for(chrono::microseconds((long)count));
   }
   else if (SYM_CHECK(unit, milliseconds))  {
      this_thread::sleep_for(chrono::milliseconds((long)count));
   }
   else if (SYM_CHECK(unit, seconds))  {
      this_thread::sleep_for(chrono::seconds((long)count));
   }
   else if (SYM_CHECK(unit, minutes))  {
      this_thread::sleep_for(chrono::minutes((long)count));
   }
   else if (SYM_CHECK(unit, hours))  {
      this_thread::sleep_for(chrono::hours((long)count));
   }
   else {
      mrb_raise(mrb, mrb->eStandardError_class, "Invalid unit parameter");
      return mrb_nil_value();
   }

   return self;
}

void mrb_mruby_apr_system_init(mrb_state* mrb, RClass* apr_module) {
   auto apr_system_module = mrb_define_module_under(mrb, apr_module, "System");
   mrb_define_module_function(mrb, apr_system_module, "sleep", mrb_apr_system_sleep, MRB_ARGS_REQ(2));
}
