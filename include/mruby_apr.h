#ifndef MRUBY_APR_H
#define MRUBY_APR_H

#include "mruby.h"
#include "mruby/compile.h"

#ifdef __cplusplus
extern "C" {
#endif

   void mrb_mruby_apr_gem_init(mrb_state* mrb);
   void mrb_mruby_apr_gem_final(mrb_state* mrb);

#ifdef __cplusplus
}
#endif

#endif /* MRUBY_APR_H */