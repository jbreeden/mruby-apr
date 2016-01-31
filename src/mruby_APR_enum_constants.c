#include "mruby_APR.h"

/* MRUBY_BINDING: header */
/* sha: user_defined */

/* MRUBY_BINDING_END */

void
mruby_APR_define_enum_constants(mrb_state* mrb) {
  struct RClass * APR_module = APR_module(mrb);
  mrb_value APR_mod = mrb_obj_value(APR_module(mrb));

/* MRUBY_BINDING: Cmdtype_enum */
/* sha: 63209e2ca8ff01111d2cb0f1a85efb4dbab94b5b10f0e984a8bdb6eb85556493 */
  struct RClass * Cmdtype_module = mrb_define_module_under(mrb, APR_module, "Cmdtype");
  mrb_value Cmdtype_mod = mrb_obj_value(Cmdtype_module);
  mrb_const_set(mrb, Cmdtype_mod, mrb_intern_lit(mrb, "APR_SHELLCMD"), mrb_fixnum_value(APR_SHELLCMD));
  mrb_const_set(mrb, APR_mod, mrb_intern_lit(mrb, "APR_SHELLCMD"), mrb_fixnum_value(APR_SHELLCMD));
  mrb_const_set(mrb, Cmdtype_mod, mrb_intern_lit(mrb, "APR_PROGRAM"), mrb_fixnum_value(APR_PROGRAM));
  mrb_const_set(mrb, APR_mod, mrb_intern_lit(mrb, "APR_PROGRAM"), mrb_fixnum_value(APR_PROGRAM));
  mrb_const_set(mrb, Cmdtype_mod, mrb_intern_lit(mrb, "APR_PROGRAM_ENV"), mrb_fixnum_value(APR_PROGRAM_ENV));
  mrb_const_set(mrb, APR_mod, mrb_intern_lit(mrb, "APR_PROGRAM_ENV"), mrb_fixnum_value(APR_PROGRAM_ENV));
  mrb_const_set(mrb, Cmdtype_mod, mrb_intern_lit(mrb, "APR_PROGRAM_PATH"), mrb_fixnum_value(APR_PROGRAM_PATH));
  mrb_const_set(mrb, APR_mod, mrb_intern_lit(mrb, "APR_PROGRAM_PATH"), mrb_fixnum_value(APR_PROGRAM_PATH));
  mrb_const_set(mrb, Cmdtype_mod, mrb_intern_lit(mrb, "APR_SHELLCMD_ENV"), mrb_fixnum_value(APR_SHELLCMD_ENV));
  mrb_const_set(mrb, APR_mod, mrb_intern_lit(mrb, "APR_SHELLCMD_ENV"), mrb_fixnum_value(APR_SHELLCMD_ENV));
/* MRUBY_BINDING_END */

/* MRUBY_BINDING: ExitWhy_enum */
/* sha: a73a505b06edf6d5fbf08dd65e77cb58f6401442df5080d9880c1f96fc27a829 */
  struct RClass * ExitWhy_module = mrb_define_module_under(mrb, APR_module, "ExitWhy");
  mrb_value ExitWhy_mod = mrb_obj_value(ExitWhy_module);
  mrb_const_set(mrb, ExitWhy_mod, mrb_intern_lit(mrb, "APR_PROC_EXIT"), mrb_fixnum_value(APR_PROC_EXIT));
  mrb_const_set(mrb, APR_mod, mrb_intern_lit(mrb, "APR_PROC_EXIT"), mrb_fixnum_value(APR_PROC_EXIT));
  mrb_const_set(mrb, ExitWhy_mod, mrb_intern_lit(mrb, "APR_PROC_SIGNAL"), mrb_fixnum_value(APR_PROC_SIGNAL));
  mrb_const_set(mrb, APR_mod, mrb_intern_lit(mrb, "APR_PROC_SIGNAL"), mrb_fixnum_value(APR_PROC_SIGNAL));
  mrb_const_set(mrb, ExitWhy_mod, mrb_intern_lit(mrb, "APR_PROC_SIGNAL_CORE"), mrb_fixnum_value(APR_PROC_SIGNAL_CORE));
  mrb_const_set(mrb, APR_mod, mrb_intern_lit(mrb, "APR_PROC_SIGNAL_CORE"), mrb_fixnum_value(APR_PROC_SIGNAL_CORE));
/* MRUBY_BINDING_END */

/* MRUBY_BINDING: Filetype_enum */
/* sha: 750076b1f277b15b53c632f70835c729b822b85312ff0783898fbc3906cb7dbb */
  struct RClass * Filetype_module = mrb_define_module_under(mrb, APR_module, "Filetype");
  mrb_value Filetype_mod = mrb_obj_value(Filetype_module);
  mrb_const_set(mrb, Filetype_mod, mrb_intern_lit(mrb, "APR_NOFILE"), mrb_fixnum_value(APR_NOFILE));
  mrb_const_set(mrb, APR_mod, mrb_intern_lit(mrb, "APR_NOFILE"), mrb_fixnum_value(APR_NOFILE));
  mrb_const_set(mrb, Filetype_mod, mrb_intern_lit(mrb, "APR_REG"), mrb_fixnum_value(APR_REG));
  mrb_const_set(mrb, APR_mod, mrb_intern_lit(mrb, "APR_REG"), mrb_fixnum_value(APR_REG));
  mrb_const_set(mrb, Filetype_mod, mrb_intern_lit(mrb, "APR_DIR"), mrb_fixnum_value(APR_DIR));
  mrb_const_set(mrb, APR_mod, mrb_intern_lit(mrb, "APR_DIR"), mrb_fixnum_value(APR_DIR));
  mrb_const_set(mrb, Filetype_mod, mrb_intern_lit(mrb, "APR_CHR"), mrb_fixnum_value(APR_CHR));
  mrb_const_set(mrb, APR_mod, mrb_intern_lit(mrb, "APR_CHR"), mrb_fixnum_value(APR_CHR));
  mrb_const_set(mrb, Filetype_mod, mrb_intern_lit(mrb, "APR_BLK"), mrb_fixnum_value(APR_BLK));
  mrb_const_set(mrb, APR_mod, mrb_intern_lit(mrb, "APR_BLK"), mrb_fixnum_value(APR_BLK));
  mrb_const_set(mrb, Filetype_mod, mrb_intern_lit(mrb, "APR_PIPE"), mrb_fixnum_value(APR_PIPE));
  mrb_const_set(mrb, APR_mod, mrb_intern_lit(mrb, "APR_PIPE"), mrb_fixnum_value(APR_PIPE));
  mrb_const_set(mrb, Filetype_mod, mrb_intern_lit(mrb, "APR_LNK"), mrb_fixnum_value(APR_LNK));
  mrb_const_set(mrb, APR_mod, mrb_intern_lit(mrb, "APR_LNK"), mrb_fixnum_value(APR_LNK));
  mrb_const_set(mrb, Filetype_mod, mrb_intern_lit(mrb, "APR_SOCK"), mrb_fixnum_value(APR_SOCK));
  mrb_const_set(mrb, APR_mod, mrb_intern_lit(mrb, "APR_SOCK"), mrb_fixnum_value(APR_SOCK));
  mrb_const_set(mrb, Filetype_mod, mrb_intern_lit(mrb, "APR_UNKFILE"), mrb_fixnum_value(APR_UNKFILE));
  mrb_const_set(mrb, APR_mod, mrb_intern_lit(mrb, "APR_UNKFILE"), mrb_fixnum_value(APR_UNKFILE));
/* MRUBY_BINDING_END */

/* MRUBY_BINDING: Interface_enum */
/* sha: d691578764318586de20ae2d4a579903e6faab35a27d5aeee36597d4498c8119 */
  struct RClass * Interface_module = mrb_define_module_under(mrb, APR_module, "Interface");
  mrb_value Interface_mod = mrb_obj_value(Interface_module);
  mrb_const_set(mrb, Interface_mod, mrb_intern_lit(mrb, "APR_LOCAL"), mrb_fixnum_value(APR_LOCAL));
  mrb_const_set(mrb, APR_mod, mrb_intern_lit(mrb, "APR_LOCAL"), mrb_fixnum_value(APR_LOCAL));
  mrb_const_set(mrb, Interface_mod, mrb_intern_lit(mrb, "APR_REMOTE"), mrb_fixnum_value(APR_REMOTE));
  mrb_const_set(mrb, APR_mod, mrb_intern_lit(mrb, "APR_REMOTE"), mrb_fixnum_value(APR_REMOTE));
/* MRUBY_BINDING_END */

/* MRUBY_BINDING: KillConditions_enum */
/* sha: 2f2b38e98ea52d23813f4c6220b647d72d74aa520480b5c80ec9f030fa3ea1df */
  struct RClass * KillConditions_module = mrb_define_module_under(mrb, APR_module, "KillConditions");
  mrb_value KillConditions_mod = mrb_obj_value(KillConditions_module);
  mrb_const_set(mrb, KillConditions_mod, mrb_intern_lit(mrb, "APR_KILL_NEVER"), mrb_fixnum_value(APR_KILL_NEVER));
  mrb_const_set(mrb, APR_mod, mrb_intern_lit(mrb, "APR_KILL_NEVER"), mrb_fixnum_value(APR_KILL_NEVER));
  mrb_const_set(mrb, KillConditions_mod, mrb_intern_lit(mrb, "APR_KILL_ALWAYS"), mrb_fixnum_value(APR_KILL_ALWAYS));
  mrb_const_set(mrb, APR_mod, mrb_intern_lit(mrb, "APR_KILL_ALWAYS"), mrb_fixnum_value(APR_KILL_ALWAYS));
  mrb_const_set(mrb, KillConditions_mod, mrb_intern_lit(mrb, "APR_KILL_AFTER_TIMEOUT"), mrb_fixnum_value(APR_KILL_AFTER_TIMEOUT));
  mrb_const_set(mrb, APR_mod, mrb_intern_lit(mrb, "APR_KILL_AFTER_TIMEOUT"), mrb_fixnum_value(APR_KILL_AFTER_TIMEOUT));
  mrb_const_set(mrb, KillConditions_mod, mrb_intern_lit(mrb, "APR_JUST_WAIT"), mrb_fixnum_value(APR_JUST_WAIT));
  mrb_const_set(mrb, APR_mod, mrb_intern_lit(mrb, "APR_JUST_WAIT"), mrb_fixnum_value(APR_JUST_WAIT));
  mrb_const_set(mrb, KillConditions_mod, mrb_intern_lit(mrb, "APR_KILL_ONLY_ONCE"), mrb_fixnum_value(APR_KILL_ONLY_ONCE));
  mrb_const_set(mrb, APR_mod, mrb_intern_lit(mrb, "APR_KILL_ONLY_ONCE"), mrb_fixnum_value(APR_KILL_ONLY_ONCE));
/* MRUBY_BINDING_END */

/* MRUBY_BINDING: Lockmech_enum */
/* sha: 2903c61a3f38ff25982d56cf40ec3d363cb9a531e4e61788b3a57dd4a4c5156b */
  struct RClass * Lockmech_module = mrb_define_module_under(mrb, APR_module, "Lockmech");
  mrb_value Lockmech_mod = mrb_obj_value(Lockmech_module);
  mrb_const_set(mrb, Lockmech_mod, mrb_intern_lit(mrb, "APR_LOCK_FCNTL"), mrb_fixnum_value(APR_LOCK_FCNTL));
  mrb_const_set(mrb, APR_mod, mrb_intern_lit(mrb, "APR_LOCK_FCNTL"), mrb_fixnum_value(APR_LOCK_FCNTL));
  mrb_const_set(mrb, Lockmech_mod, mrb_intern_lit(mrb, "APR_LOCK_FLOCK"), mrb_fixnum_value(APR_LOCK_FLOCK));
  mrb_const_set(mrb, APR_mod, mrb_intern_lit(mrb, "APR_LOCK_FLOCK"), mrb_fixnum_value(APR_LOCK_FLOCK));
  mrb_const_set(mrb, Lockmech_mod, mrb_intern_lit(mrb, "APR_LOCK_SYSVSEM"), mrb_fixnum_value(APR_LOCK_SYSVSEM));
  mrb_const_set(mrb, APR_mod, mrb_intern_lit(mrb, "APR_LOCK_SYSVSEM"), mrb_fixnum_value(APR_LOCK_SYSVSEM));
  mrb_const_set(mrb, Lockmech_mod, mrb_intern_lit(mrb, "APR_LOCK_PROC_PTHREAD"), mrb_fixnum_value(APR_LOCK_PROC_PTHREAD));
  mrb_const_set(mrb, APR_mod, mrb_intern_lit(mrb, "APR_LOCK_PROC_PTHREAD"), mrb_fixnum_value(APR_LOCK_PROC_PTHREAD));
  mrb_const_set(mrb, Lockmech_mod, mrb_intern_lit(mrb, "APR_LOCK_POSIXSEM"), mrb_fixnum_value(APR_LOCK_POSIXSEM));
  mrb_const_set(mrb, APR_mod, mrb_intern_lit(mrb, "APR_LOCK_POSIXSEM"), mrb_fixnum_value(APR_LOCK_POSIXSEM));
  mrb_const_set(mrb, Lockmech_mod, mrb_intern_lit(mrb, "APR_LOCK_DEFAULT"), mrb_fixnum_value(APR_LOCK_DEFAULT));
  mrb_const_set(mrb, APR_mod, mrb_intern_lit(mrb, "APR_LOCK_DEFAULT"), mrb_fixnum_value(APR_LOCK_DEFAULT));
/* MRUBY_BINDING_END */

/* MRUBY_BINDING: ShutdownHow_enum */
/* sha: bb0da2c28d4e696ba15b6216be63a0ccd2e979855ad2be3ce345eefaee0f1160 */
  struct RClass * ShutdownHow_module = mrb_define_module_under(mrb, APR_module, "ShutdownHow");
  mrb_value ShutdownHow_mod = mrb_obj_value(ShutdownHow_module);
  mrb_const_set(mrb, ShutdownHow_mod, mrb_intern_lit(mrb, "APR_SHUTDOWN_READ"), mrb_fixnum_value(APR_SHUTDOWN_READ));
  mrb_const_set(mrb, APR_mod, mrb_intern_lit(mrb, "APR_SHUTDOWN_READ"), mrb_fixnum_value(APR_SHUTDOWN_READ));
  mrb_const_set(mrb, ShutdownHow_mod, mrb_intern_lit(mrb, "APR_SHUTDOWN_WRITE"), mrb_fixnum_value(APR_SHUTDOWN_WRITE));
  mrb_const_set(mrb, APR_mod, mrb_intern_lit(mrb, "APR_SHUTDOWN_WRITE"), mrb_fixnum_value(APR_SHUTDOWN_WRITE));
  mrb_const_set(mrb, ShutdownHow_mod, mrb_intern_lit(mrb, "APR_SHUTDOWN_READWRITE"), mrb_fixnum_value(APR_SHUTDOWN_READWRITE));
  mrb_const_set(mrb, APR_mod, mrb_intern_lit(mrb, "APR_SHUTDOWN_READWRITE"), mrb_fixnum_value(APR_SHUTDOWN_READWRITE));
/* MRUBY_BINDING_END */

/* MRUBY_BINDING: WaitHow_enum */
/* sha: 046927bd973fa1490e8ca12bb1105c5d8f8264b93822d470dda05cd33a9e4e5c */
  struct RClass * WaitHow_module = mrb_define_module_under(mrb, APR_module, "WaitHow");
  mrb_value WaitHow_mod = mrb_obj_value(WaitHow_module);
  mrb_const_set(mrb, WaitHow_mod, mrb_intern_lit(mrb, "APR_WAIT"), mrb_fixnum_value(APR_WAIT));
  mrb_const_set(mrb, APR_mod, mrb_intern_lit(mrb, "APR_WAIT"), mrb_fixnum_value(APR_WAIT));
  mrb_const_set(mrb, WaitHow_mod, mrb_intern_lit(mrb, "APR_NOWAIT"), mrb_fixnum_value(APR_NOWAIT));
  mrb_const_set(mrb, APR_mod, mrb_intern_lit(mrb, "APR_NOWAIT"), mrb_fixnum_value(APR_NOWAIT));
/* MRUBY_BINDING_END */

}

/* MRUBY_BINDING: footer */
/* sha: user_defined */

/* MRUBY_BINDING_END */
