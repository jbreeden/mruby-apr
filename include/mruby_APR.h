#ifndef APR_HEADER
#define APR_HEADER

/*
 * Header Files
 * ------------
 *
 * These are the header files that defined the
 * classes and functions for which bindings have
 * been generated. If any of these are not needed
 * they should be commented out.
 *
 * TODO: ONLY the filename is inserted here automatically.
 *       If the file is not directly on the include path,
 *       you will need to prepend the relative path.
 */

/* MRUBY_BINDING: pre_includes */
/* sha: user_defined */
#if defined(_WIN32) || defined(_WIN64)
  /* Actually much larger than Window's max path length, but whatevs */
  #define PATH_MAX 1024
  #include <direct.h>
  #define getcwd _getcwd
  #define chdir _chdir
#else
  #include <limits.h>
  #include <unistd.h>
  #if !defined(PATH_MAX) && defined(MRUBY_APR_LINUX)
    #include <linux/limits.h>
  #endif
#endif
/* MRUBY_BINDING_END */

/* MRUBY_BINDING: includes */
/* sha: aabfd2e62a48e757b23f6c2143509287038c61a867f179b46d5a4cb271304ba9 */
#include <stdlib.h>
#include "mruby.h"
#include "mruby/array.h"
#include "mruby/class.h"
#include "mruby/compile.h"
#include "mruby/data.h"
#include "mruby/string.h"
#include "mruby/value.h"
#include "mruby/variable.h"

#include "apr.h"
#include "apr_env.h"
#include "apr_errno.h"
#include "apr_file_info.h"
#include "apr_file_io.h"
#include "apr_fnmatch.h"
#include "apr_general.h"
#include "apr_global_mutex.h"
#include "apr_network_io.h"
#include "apr_pools.h"
#include "apr_proc_mutex.h"
#include "apr_signal.h"
#include "apr_strings.h"
#include "apr_thread_proc.h"
#include "apr_time.h"

#include "mruby_APR_functions.h"
#include "mruby_APR_classes.h"
#include "mruby_APR_boxing.h"
/* MRUBY_BINDING_END */

/* MRUBY_BINDING: post_includes */
/* sha: user_defined */
void mruby_APR_init_native_ext(mrb_state * mrb);
/* MRUBY_BINDING_END */

/*
 * RClass Macros
 * -------------
 *
 * Macros for retrieving the RClass*'s defined by this gem.
 */

/* MRUBY_BINDING: pre_class_macros */
/* sha: user_defined */

/* MRUBY_BINDING_END */

/* MRUBY_BINDING: class_macros */
/* sha: bd2e84dbc47b1834a85fd10f2b28f039c5ba99ff030c553c365db8e3492a97a8 */
#define APR_module(mrb) mrb_module_get(mrb, "APR")
#define AprDirT_class(mrb) mrb_class_get_under(mrb, APR_module(mrb), "AprDirT")
#define AprFileT_class(mrb) mrb_class_get_under(mrb, APR_module(mrb), "AprFileT")
#define AprFinfoT_class(mrb) mrb_class_get_under(mrb, APR_module(mrb), "AprFinfoT")
#define AprGlobalMutexT_class(mrb) mrb_class_get_under(mrb, APR_module(mrb), "AprGlobalMutexT")
#define AprHdtrT_class(mrb) mrb_class_get_under(mrb, APR_module(mrb), "AprHdtrT")
#define AprIpsubnetT_class(mrb) mrb_class_get_under(mrb, APR_module(mrb), "AprIpsubnetT")
#define AprOtherChildRecT_class(mrb) mrb_class_get_under(mrb, APR_module(mrb), "AprOtherChildRecT")
#define AprPoolT_class(mrb) mrb_class_get_under(mrb, APR_module(mrb), "AprPoolT")
#define AprProcattrT_class(mrb) mrb_class_get_under(mrb, APR_module(mrb), "AprProcattrT")
#define AprProcMutexT_class(mrb) mrb_class_get_under(mrb, APR_module(mrb), "AprProcMutexT")
#define AprProcT_class(mrb) mrb_class_get_under(mrb, APR_module(mrb), "AprProcT")
#define AprSockaddrT_class(mrb) mrb_class_get_under(mrb, APR_module(mrb), "AprSockaddrT")
#define AprSocketT_class(mrb) mrb_class_get_under(mrb, APR_module(mrb), "AprSocketT")
#define AprThreadattrT_class(mrb) mrb_class_get_under(mrb, APR_module(mrb), "AprThreadattrT")
#define AprThreadkeyT_class(mrb) mrb_class_get_under(mrb, APR_module(mrb), "AprThreadkeyT")
#define AprThreadOnceT_class(mrb) mrb_class_get_under(mrb, APR_module(mrb), "AprThreadOnceT")
#define AprThreadT_class(mrb) mrb_class_get_under(mrb, APR_module(mrb), "AprThreadT")
#define AprTimeExpT_class(mrb) mrb_class_get_under(mrb, APR_module(mrb), "AprTimeExpT")
/* MRUBY_BINDING_END */

/* MRUBY_BINDING: post_class_macros */
/* sha: user_defined */

/* MRUBY_BINDING_END */

/*
 * Class initialization function declarations
 * ------------------------------------------
 */

/* MRUBY_BINDING: pre_class_init_decls */
/* sha: user_defined */

/* MRUBY_BINDING_END */

/* MRUBY_BINDING: pre_class_init_decls */
/* sha: fe745ff0c87c06d518eef7358bbbbfbdee9d1ffdb0868c3b48fc1a87064e7929 */
#if BIND_AprDirT_TYPE
void mrb_APR_AprDirT_init(mrb_state* mrb);
#endif
#if BIND_AprFileT_TYPE
void mrb_APR_AprFileT_init(mrb_state* mrb);
#endif
#if BIND_AprFinfoT_TYPE
void mrb_APR_AprFinfoT_init(mrb_state* mrb);
#endif
#if BIND_AprGlobalMutexT_TYPE
void mrb_APR_AprGlobalMutexT_init(mrb_state* mrb);
#endif
#if BIND_AprHdtrT_TYPE
void mrb_APR_AprHdtrT_init(mrb_state* mrb);
#endif
#if BIND_AprIpsubnetT_TYPE
void mrb_APR_AprIpsubnetT_init(mrb_state* mrb);
#endif
#if BIND_AprOtherChildRecT_TYPE
void mrb_APR_AprOtherChildRecT_init(mrb_state* mrb);
#endif
#if BIND_AprPoolT_TYPE
void mrb_APR_AprPoolT_init(mrb_state* mrb);
#endif
#if BIND_AprProcattrT_TYPE
void mrb_APR_AprProcattrT_init(mrb_state* mrb);
#endif
#if BIND_AprProcMutexT_TYPE
void mrb_APR_AprProcMutexT_init(mrb_state* mrb);
#endif
#if BIND_AprProcT_TYPE
void mrb_APR_AprProcT_init(mrb_state* mrb);
#endif
#if BIND_AprSockaddrT_TYPE
void mrb_APR_AprSockaddrT_init(mrb_state* mrb);
#endif
#if BIND_AprSocketT_TYPE
void mrb_APR_AprSocketT_init(mrb_state* mrb);
#endif
#if BIND_AprThreadattrT_TYPE
void mrb_APR_AprThreadattrT_init(mrb_state* mrb);
#endif
#if BIND_AprThreadkeyT_TYPE
void mrb_APR_AprThreadkeyT_init(mrb_state* mrb);
#endif
#if BIND_AprThreadOnceT_TYPE
void mrb_APR_AprThreadOnceT_init(mrb_state* mrb);
#endif
#if BIND_AprThreadT_TYPE
void mrb_APR_AprThreadT_init(mrb_state* mrb);
#endif
#if BIND_AprTimeExpT_TYPE
void mrb_APR_AprTimeExpT_init(mrb_state* mrb);
#endif
/* MRUBY_BINDING_END */

/* MRUBY_BINDING: post_class_init_decls */
/* sha: user_defined */

/* MRUBY_BINDING_END */

/*
 * Macro & Enum definition function declarations
 * ---------------------------------------------
 */
void mruby_APR_define_macro_constants(mrb_state* mrb);
void mruby_APR_define_enum_constants(mrb_state* mrb);

#endif
