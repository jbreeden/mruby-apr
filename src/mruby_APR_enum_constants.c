#include "mruby_APR.h"

/* MRUBY_BINDING: header */
/* sha: user_defined */

/* MRUBY_BINDING_END */

void
mruby_APR_define_enum_constants(mrb_state* mrb) {
  struct RClass * APR_module = APR_module(mrb);
  mrb_value APR_mod = mrb_obj_value(APR_module(mrb));

/* MRUBY_BINDING: AprCmdtypeE_enum */
/* sha: 7608bd50543546ea27a4f0d0b2fc446ac2530d8bba63b033bbc90ec041165fbc */
  struct RClass * AprCmdtypeE_module = mrb_define_module_under(mrb, APR_module, "AprCmdtypeE");
  mrb_value AprCmdtypeE_mod = mrb_obj_value(AprCmdtypeE_module);
  mrb_const_set(mrb, AprCmdtypeE_mod, mrb_intern_lit(mrb, "APR_SHELLCMD"), mrb_fixnum_value(APR_SHELLCMD));
  mrb_const_set(mrb, APR_mod, mrb_intern_lit(mrb, "APR_SHELLCMD"), mrb_fixnum_value(APR_SHELLCMD));
  mrb_const_set(mrb, AprCmdtypeE_mod, mrb_intern_lit(mrb, "APR_PROGRAM"), mrb_fixnum_value(APR_PROGRAM));
  mrb_const_set(mrb, APR_mod, mrb_intern_lit(mrb, "APR_PROGRAM"), mrb_fixnum_value(APR_PROGRAM));
  mrb_const_set(mrb, AprCmdtypeE_mod, mrb_intern_lit(mrb, "APR_PROGRAM_ENV"), mrb_fixnum_value(APR_PROGRAM_ENV));
  mrb_const_set(mrb, APR_mod, mrb_intern_lit(mrb, "APR_PROGRAM_ENV"), mrb_fixnum_value(APR_PROGRAM_ENV));
  mrb_const_set(mrb, AprCmdtypeE_mod, mrb_intern_lit(mrb, "APR_PROGRAM_PATH"), mrb_fixnum_value(APR_PROGRAM_PATH));
  mrb_const_set(mrb, APR_mod, mrb_intern_lit(mrb, "APR_PROGRAM_PATH"), mrb_fixnum_value(APR_PROGRAM_PATH));
  mrb_const_set(mrb, AprCmdtypeE_mod, mrb_intern_lit(mrb, "APR_SHELLCMD_ENV"), mrb_fixnum_value(APR_SHELLCMD_ENV));
  mrb_const_set(mrb, APR_mod, mrb_intern_lit(mrb, "APR_SHELLCMD_ENV"), mrb_fixnum_value(APR_SHELLCMD_ENV));
/* MRUBY_BINDING_END */

/* MRUBY_BINDING: AprExitWhyE_enum */
/* sha: 20d02eaec8fbaff918b4153c97154de7e0f2226ace5e9083c5e70d7e04c318eb */
  struct RClass * AprExitWhyE_module = mrb_define_module_under(mrb, APR_module, "AprExitWhyE");
  mrb_value AprExitWhyE_mod = mrb_obj_value(AprExitWhyE_module);
  mrb_const_set(mrb, AprExitWhyE_mod, mrb_intern_lit(mrb, "APR_PROC_EXIT"), mrb_fixnum_value(APR_PROC_EXIT));
  mrb_const_set(mrb, APR_mod, mrb_intern_lit(mrb, "APR_PROC_EXIT"), mrb_fixnum_value(APR_PROC_EXIT));
  mrb_const_set(mrb, AprExitWhyE_mod, mrb_intern_lit(mrb, "APR_PROC_SIGNAL"), mrb_fixnum_value(APR_PROC_SIGNAL));
  mrb_const_set(mrb, APR_mod, mrb_intern_lit(mrb, "APR_PROC_SIGNAL"), mrb_fixnum_value(APR_PROC_SIGNAL));
  mrb_const_set(mrb, AprExitWhyE_mod, mrb_intern_lit(mrb, "APR_PROC_SIGNAL_CORE"), mrb_fixnum_value(APR_PROC_SIGNAL_CORE));
  mrb_const_set(mrb, APR_mod, mrb_intern_lit(mrb, "APR_PROC_SIGNAL_CORE"), mrb_fixnum_value(APR_PROC_SIGNAL_CORE));
/* MRUBY_BINDING_END */

/* MRUBY_BINDING: AprFiletypeE_enum */
/* sha: 9b576dc4c2979d93b2864cfaff2329e7f9f0c939bfbebe4c47816b2ec1069aa0 */
  struct RClass * AprFiletypeE_module = mrb_define_module_under(mrb, APR_module, "AprFiletypeE");
  mrb_value AprFiletypeE_mod = mrb_obj_value(AprFiletypeE_module);
  mrb_const_set(mrb, AprFiletypeE_mod, mrb_intern_lit(mrb, "APR_NOFILE"), mrb_fixnum_value(APR_NOFILE));
  mrb_const_set(mrb, APR_mod, mrb_intern_lit(mrb, "APR_NOFILE"), mrb_fixnum_value(APR_NOFILE));
  mrb_const_set(mrb, AprFiletypeE_mod, mrb_intern_lit(mrb, "APR_REG"), mrb_fixnum_value(APR_REG));
  mrb_const_set(mrb, APR_mod, mrb_intern_lit(mrb, "APR_REG"), mrb_fixnum_value(APR_REG));
  mrb_const_set(mrb, AprFiletypeE_mod, mrb_intern_lit(mrb, "APR_DIR"), mrb_fixnum_value(APR_DIR));
  mrb_const_set(mrb, APR_mod, mrb_intern_lit(mrb, "APR_DIR"), mrb_fixnum_value(APR_DIR));
  mrb_const_set(mrb, AprFiletypeE_mod, mrb_intern_lit(mrb, "APR_CHR"), mrb_fixnum_value(APR_CHR));
  mrb_const_set(mrb, APR_mod, mrb_intern_lit(mrb, "APR_CHR"), mrb_fixnum_value(APR_CHR));
  mrb_const_set(mrb, AprFiletypeE_mod, mrb_intern_lit(mrb, "APR_BLK"), mrb_fixnum_value(APR_BLK));
  mrb_const_set(mrb, APR_mod, mrb_intern_lit(mrb, "APR_BLK"), mrb_fixnum_value(APR_BLK));
  mrb_const_set(mrb, AprFiletypeE_mod, mrb_intern_lit(mrb, "APR_PIPE"), mrb_fixnum_value(APR_PIPE));
  mrb_const_set(mrb, APR_mod, mrb_intern_lit(mrb, "APR_PIPE"), mrb_fixnum_value(APR_PIPE));
  mrb_const_set(mrb, AprFiletypeE_mod, mrb_intern_lit(mrb, "APR_LNK"), mrb_fixnum_value(APR_LNK));
  mrb_const_set(mrb, APR_mod, mrb_intern_lit(mrb, "APR_LNK"), mrb_fixnum_value(APR_LNK));
  mrb_const_set(mrb, AprFiletypeE_mod, mrb_intern_lit(mrb, "APR_SOCK"), mrb_fixnum_value(APR_SOCK));
  mrb_const_set(mrb, APR_mod, mrb_intern_lit(mrb, "APR_SOCK"), mrb_fixnum_value(APR_SOCK));
  mrb_const_set(mrb, AprFiletypeE_mod, mrb_intern_lit(mrb, "APR_UNKFILE"), mrb_fixnum_value(APR_UNKFILE));
  mrb_const_set(mrb, APR_mod, mrb_intern_lit(mrb, "APR_UNKFILE"), mrb_fixnum_value(APR_UNKFILE));
/* MRUBY_BINDING_END */

/* MRUBY_BINDING: AprInterfaceE_enum */
/* sha: f6a91fbfa56fa691b1a4edc2ad3a9ca7f1f4badd09155365d83a00d0173e6b48 */
  struct RClass * AprInterfaceE_module = mrb_define_module_under(mrb, APR_module, "AprInterfaceE");
  mrb_value AprInterfaceE_mod = mrb_obj_value(AprInterfaceE_module);
  mrb_const_set(mrb, AprInterfaceE_mod, mrb_intern_lit(mrb, "APR_LOCAL"), mrb_fixnum_value(APR_LOCAL));
  mrb_const_set(mrb, APR_mod, mrb_intern_lit(mrb, "APR_LOCAL"), mrb_fixnum_value(APR_LOCAL));
  mrb_const_set(mrb, AprInterfaceE_mod, mrb_intern_lit(mrb, "APR_REMOTE"), mrb_fixnum_value(APR_REMOTE));
  mrb_const_set(mrb, APR_mod, mrb_intern_lit(mrb, "APR_REMOTE"), mrb_fixnum_value(APR_REMOTE));
/* MRUBY_BINDING_END */

/* MRUBY_BINDING: AprKillConditionsE_enum */
/* sha: 163c92201255e49b8bccd6d6d2d52f84d7df8bc71550773e806dc79c1880a22a */
  struct RClass * AprKillConditionsE_module = mrb_define_module_under(mrb, APR_module, "AprKillConditionsE");
  mrb_value AprKillConditionsE_mod = mrb_obj_value(AprKillConditionsE_module);
  mrb_const_set(mrb, AprKillConditionsE_mod, mrb_intern_lit(mrb, "APR_KILL_NEVER"), mrb_fixnum_value(APR_KILL_NEVER));
  mrb_const_set(mrb, APR_mod, mrb_intern_lit(mrb, "APR_KILL_NEVER"), mrb_fixnum_value(APR_KILL_NEVER));
  mrb_const_set(mrb, AprKillConditionsE_mod, mrb_intern_lit(mrb, "APR_KILL_ALWAYS"), mrb_fixnum_value(APR_KILL_ALWAYS));
  mrb_const_set(mrb, APR_mod, mrb_intern_lit(mrb, "APR_KILL_ALWAYS"), mrb_fixnum_value(APR_KILL_ALWAYS));
  mrb_const_set(mrb, AprKillConditionsE_mod, mrb_intern_lit(mrb, "APR_KILL_AFTER_TIMEOUT"), mrb_fixnum_value(APR_KILL_AFTER_TIMEOUT));
  mrb_const_set(mrb, APR_mod, mrb_intern_lit(mrb, "APR_KILL_AFTER_TIMEOUT"), mrb_fixnum_value(APR_KILL_AFTER_TIMEOUT));
  mrb_const_set(mrb, AprKillConditionsE_mod, mrb_intern_lit(mrb, "APR_JUST_WAIT"), mrb_fixnum_value(APR_JUST_WAIT));
  mrb_const_set(mrb, APR_mod, mrb_intern_lit(mrb, "APR_JUST_WAIT"), mrb_fixnum_value(APR_JUST_WAIT));
  mrb_const_set(mrb, AprKillConditionsE_mod, mrb_intern_lit(mrb, "APR_KILL_ONLY_ONCE"), mrb_fixnum_value(APR_KILL_ONLY_ONCE));
  mrb_const_set(mrb, APR_mod, mrb_intern_lit(mrb, "APR_KILL_ONLY_ONCE"), mrb_fixnum_value(APR_KILL_ONLY_ONCE));
/* MRUBY_BINDING_END */

/* MRUBY_BINDING: AprLockmechE_enum */
/* sha: 84dae2a84ddb6eb8f3218b8b098bb9d30c0e0942a07f58e807f734fdaf8cf364 */
  struct RClass * AprLockmechE_module = mrb_define_module_under(mrb, APR_module, "AprLockmechE");
  mrb_value AprLockmechE_mod = mrb_obj_value(AprLockmechE_module);
  mrb_const_set(mrb, AprLockmechE_mod, mrb_intern_lit(mrb, "APR_LOCK_FCNTL"), mrb_fixnum_value(APR_LOCK_FCNTL));
  mrb_const_set(mrb, APR_mod, mrb_intern_lit(mrb, "APR_LOCK_FCNTL"), mrb_fixnum_value(APR_LOCK_FCNTL));
  mrb_const_set(mrb, AprLockmechE_mod, mrb_intern_lit(mrb, "APR_LOCK_FLOCK"), mrb_fixnum_value(APR_LOCK_FLOCK));
  mrb_const_set(mrb, APR_mod, mrb_intern_lit(mrb, "APR_LOCK_FLOCK"), mrb_fixnum_value(APR_LOCK_FLOCK));
  mrb_const_set(mrb, AprLockmechE_mod, mrb_intern_lit(mrb, "APR_LOCK_SYSVSEM"), mrb_fixnum_value(APR_LOCK_SYSVSEM));
  mrb_const_set(mrb, APR_mod, mrb_intern_lit(mrb, "APR_LOCK_SYSVSEM"), mrb_fixnum_value(APR_LOCK_SYSVSEM));
  mrb_const_set(mrb, AprLockmechE_mod, mrb_intern_lit(mrb, "APR_LOCK_PROC_PTHREAD"), mrb_fixnum_value(APR_LOCK_PROC_PTHREAD));
  mrb_const_set(mrb, APR_mod, mrb_intern_lit(mrb, "APR_LOCK_PROC_PTHREAD"), mrb_fixnum_value(APR_LOCK_PROC_PTHREAD));
  mrb_const_set(mrb, AprLockmechE_mod, mrb_intern_lit(mrb, "APR_LOCK_POSIXSEM"), mrb_fixnum_value(APR_LOCK_POSIXSEM));
  mrb_const_set(mrb, APR_mod, mrb_intern_lit(mrb, "APR_LOCK_POSIXSEM"), mrb_fixnum_value(APR_LOCK_POSIXSEM));
  mrb_const_set(mrb, AprLockmechE_mod, mrb_intern_lit(mrb, "APR_LOCK_DEFAULT"), mrb_fixnum_value(APR_LOCK_DEFAULT));
  mrb_const_set(mrb, APR_mod, mrb_intern_lit(mrb, "APR_LOCK_DEFAULT"), mrb_fixnum_value(APR_LOCK_DEFAULT));
/* MRUBY_BINDING_END */

/* MRUBY_BINDING: AprShutdownHowE_enum */
/* sha: 710eb77a99c089f59dfb4ce46d5fdf97e6aaefb0d29edc8fa37bbfc4139f951e */
  struct RClass * AprShutdownHowE_module = mrb_define_module_under(mrb, APR_module, "AprShutdownHowE");
  mrb_value AprShutdownHowE_mod = mrb_obj_value(AprShutdownHowE_module);
  mrb_const_set(mrb, AprShutdownHowE_mod, mrb_intern_lit(mrb, "APR_SHUTDOWN_READ"), mrb_fixnum_value(APR_SHUTDOWN_READ));
  mrb_const_set(mrb, APR_mod, mrb_intern_lit(mrb, "APR_SHUTDOWN_READ"), mrb_fixnum_value(APR_SHUTDOWN_READ));
  mrb_const_set(mrb, AprShutdownHowE_mod, mrb_intern_lit(mrb, "APR_SHUTDOWN_WRITE"), mrb_fixnum_value(APR_SHUTDOWN_WRITE));
  mrb_const_set(mrb, APR_mod, mrb_intern_lit(mrb, "APR_SHUTDOWN_WRITE"), mrb_fixnum_value(APR_SHUTDOWN_WRITE));
  mrb_const_set(mrb, AprShutdownHowE_mod, mrb_intern_lit(mrb, "APR_SHUTDOWN_READWRITE"), mrb_fixnum_value(APR_SHUTDOWN_READWRITE));
  mrb_const_set(mrb, APR_mod, mrb_intern_lit(mrb, "APR_SHUTDOWN_READWRITE"), mrb_fixnum_value(APR_SHUTDOWN_READWRITE));
/* MRUBY_BINDING_END */

/* MRUBY_BINDING: AprWaitHowE_enum */
/* sha: 25919fda1be49b2c6392a64c2c3ea1303e3699f5e1be37fec1e013a3a39d7703 */
  struct RClass * AprWaitHowE_module = mrb_define_module_under(mrb, APR_module, "AprWaitHowE");
  mrb_value AprWaitHowE_mod = mrb_obj_value(AprWaitHowE_module);
  mrb_const_set(mrb, AprWaitHowE_mod, mrb_intern_lit(mrb, "APR_WAIT"), mrb_fixnum_value(APR_WAIT));
  mrb_const_set(mrb, APR_mod, mrb_intern_lit(mrb, "APR_WAIT"), mrb_fixnum_value(APR_WAIT));
  mrb_const_set(mrb, AprWaitHowE_mod, mrb_intern_lit(mrb, "APR_NOWAIT"), mrb_fixnum_value(APR_NOWAIT));
  mrb_const_set(mrb, APR_mod, mrb_intern_lit(mrb, "APR_NOWAIT"), mrb_fixnum_value(APR_NOWAIT));
/* MRUBY_BINDING_END */

}

/* MRUBY_BINDING: footer */
/* sha: user_defined */

/* MRUBY_BINDING_END */
