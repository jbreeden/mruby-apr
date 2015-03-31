#ifndef MRUBY_APR_H
#define MRUBY_APR_H

#include "mruby.h"
#include "mruby/compile.h"

#define GUARD_APR_ERRNO(ERR, MSG) \
   if (ERR != APR_SUCCESS) { \
      mrb_raise_apr_errno(mrb, ERR, MSG); \
      return mrb_nil_value(); \
   }

#define SYM_CHECK(sym, name) \
   (sym == mrb_intern_cstr(mrb, #name))

#define SYM_TO_IO_FLAG(sym, flag) \
   if (SYM_CHECK(sym, APR_NO_PIPE)) {\
      flag = APR_NO_PIPE; \
   }\
   else if (SYM_CHECK(sym, APR_NO_FILE)) {\
      flag = APR_NO_FILE; \
   }\
   else if (SYM_CHECK(sym, APR_FULL_BLOCK)) {\
      flag = APR_FULL_BLOCK; \
   }\
   else {\
      mrb_raise(mrb, mrb->eStandardError_class, "Invalid proc IO flag"); \
      return mrb_nil_value(); \
   }

#define GET_APR_PROC_DATA(MRB_VAL) \
   ((AprProc*)DATA_PTR(mrb_iv_get(mrb, MRB_VAL, mrb_intern_cstr(mrb, "data"))))

#define GUARD_ALREADY_EXECED(MSG) \
   if (mrb_test(mrb_iv_get(mrb, self, mrb_intern_cstr(mrb, "execed")))) { \
      mrb_raise(mrb, mrb->eStandardError_class, MSG); \
      return mrb_nil_value(); \
   }

#define GUARD_NO_EXEC(MSG) \
   if (!mrb_test(mrb_iv_get(mrb, self, mrb_intern_cstr(mrb, "execed")))) { \
      mrb_raise(mrb, mrb->eStandardError_class, MSG); \
      return mrb_nil_value(); \
   }

#ifdef __cplusplus
extern "C" {
#endif
   void mrb_raise_apr_errno(mrb_state* mrb, int apr_errno, char* message);
   void mrb_mruby_apr_file_init(mrb_state* mrb, RClass* apr_module);
   void mrb_mruby_apr_env_init(mrb_state* mrb, RClass* apr_module);
   void mrb_mruby_apr_process_init(mrb_state* mrb, RClass* apr_module);
   void mrb_mruby_apr_system_init(mrb_state* mrb, RClass* apr_module);
   void mrb_mruby_apr_tcp_init(mrb_state* mrb, RClass* apr_module);
   void mrb_mruby_apr_gem_init(mrb_state* mrb);
   void mrb_mruby_apr_gem_final(mrb_state* mrb);

#ifdef __cplusplus
}
#endif

#endif /* MRUBY_APR_H */