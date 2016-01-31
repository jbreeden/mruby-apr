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
/* sha: 2ca34a3fd1c59e54ea70663b4692fae30b241463cb5c67bc780256d63c87569e */
#define APR_module(mrb) mrb_module_get(mrb, "APR")
#define Dir_class(mrb) mrb_class_get_under(mrb, APR_module(mrb), "Dir")
#define File_class(mrb) mrb_class_get_under(mrb, APR_module(mrb), "File")
#define Finfo_class(mrb) mrb_class_get_under(mrb, APR_module(mrb), "Finfo")
#define GlobalMutex_class(mrb) mrb_class_get_under(mrb, APR_module(mrb), "GlobalMutex")
#define Hdtr_class(mrb) mrb_class_get_under(mrb, APR_module(mrb), "Hdtr")
#define Ipsubnet_class(mrb) mrb_class_get_under(mrb, APR_module(mrb), "Ipsubnet")
#define OtherChildRec_class(mrb) mrb_class_get_under(mrb, APR_module(mrb), "OtherChildRec")
#define Pool_class(mrb) mrb_class_get_under(mrb, APR_module(mrb), "Pool")
#define Proc_class(mrb) mrb_class_get_under(mrb, APR_module(mrb), "Proc")
#define Procattr_class(mrb) mrb_class_get_under(mrb, APR_module(mrb), "Procattr")
#define ProcMutex_class(mrb) mrb_class_get_under(mrb, APR_module(mrb), "ProcMutex")
#define Sockaddr_class(mrb) mrb_class_get_under(mrb, APR_module(mrb), "Sockaddr")
#define Socket_class(mrb) mrb_class_get_under(mrb, APR_module(mrb), "Socket")
#define Thread_class(mrb) mrb_class_get_under(mrb, APR_module(mrb), "Thread")
#define Threadattr_class(mrb) mrb_class_get_under(mrb, APR_module(mrb), "Threadattr")
#define Threadkey_class(mrb) mrb_class_get_under(mrb, APR_module(mrb), "Threadkey")
#define ThreadOnce_class(mrb) mrb_class_get_under(mrb, APR_module(mrb), "ThreadOnce")
#define TimeExp_class(mrb) mrb_class_get_under(mrb, APR_module(mrb), "TimeExp")
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
/* sha: 2704c36aefe9e99647dbb00d403d031cd881bb76fdc62c143ff0c42282fdbd5e */
#if BIND_Dir_TYPE
void mrb_APR_Dir_init(mrb_state* mrb);
#endif
#if BIND_File_TYPE
void mrb_APR_File_init(mrb_state* mrb);
#endif
#if BIND_Finfo_TYPE
void mrb_APR_Finfo_init(mrb_state* mrb);
#endif
#if BIND_GlobalMutex_TYPE
void mrb_APR_GlobalMutex_init(mrb_state* mrb);
#endif
#if BIND_Hdtr_TYPE
void mrb_APR_Hdtr_init(mrb_state* mrb);
#endif
#if BIND_Ipsubnet_TYPE
void mrb_APR_Ipsubnet_init(mrb_state* mrb);
#endif
#if BIND_OtherChildRec_TYPE
void mrb_APR_OtherChildRec_init(mrb_state* mrb);
#endif
#if BIND_Pool_TYPE
void mrb_APR_Pool_init(mrb_state* mrb);
#endif
#if BIND_Proc_TYPE
void mrb_APR_Proc_init(mrb_state* mrb);
#endif
#if BIND_Procattr_TYPE
void mrb_APR_Procattr_init(mrb_state* mrb);
#endif
#if BIND_ProcMutex_TYPE
void mrb_APR_ProcMutex_init(mrb_state* mrb);
#endif
#if BIND_Sockaddr_TYPE
void mrb_APR_Sockaddr_init(mrb_state* mrb);
#endif
#if BIND_Socket_TYPE
void mrb_APR_Socket_init(mrb_state* mrb);
#endif
#if BIND_Thread_TYPE
void mrb_APR_Thread_init(mrb_state* mrb);
#endif
#if BIND_Threadattr_TYPE
void mrb_APR_Threadattr_init(mrb_state* mrb);
#endif
#if BIND_Threadkey_TYPE
void mrb_APR_Threadkey_init(mrb_state* mrb);
#endif
#if BIND_ThreadOnce_TYPE
void mrb_APR_ThreadOnce_init(mrb_state* mrb);
#endif
#if BIND_TimeExp_TYPE
void mrb_APR_TimeExp_init(mrb_state* mrb);
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
