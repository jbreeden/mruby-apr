#include "mruby_APR.h"

/* MRUBY_BINDING: header */
/* sha: user_defined */
#define RETURN_ERRNO_AND_OUTPUT(err, output) \
   do { \
      mrb_value results = mrb_ary_new(mrb); \
      mrb_ary_push(mrb, results, mrb_fixnum_value(err)); \
      if (result == 0) \
        mrb_ary_push(mrb, results, output); \
            else \
         mrb_ary_push(mrb, results, mrb_nil_value()); \
      return results; \
      } while (0);
      
#define apr_file_inherit_unset_REQUIRED_ARGC 1
#define apr_file_inherit_unset_OPTIONAL_ARGC 0
mrb_value
mrb_APR_apr_file_inherit_unset(mrb_state* mrb, mrb_value self) {
  mrb_value thefile;
  mrb_get_args(mrb, "o", &thefile);

  /* Type checking */
  if (!mrb_obj_is_kind_of(mrb, thefile, AprFileT_class(mrb))) {
    mrb_raise(mrb, E_TYPE_ERROR, "AprFileT expected");
    return mrb_nil_value();
  }

  apr_file_t * native_thefile = (mrb_nil_p(thefile) ? NULL : mruby_unbox_apr_file_t(thefile));

  apr_status_t result = apr_file_inherit_unset(native_thefile);

  return mrb_fixnum_value(result);
}

#define apr_to_os_error_REQUIRED_ARGC 1
#define apr_to_os_error_OPTIONAL_ARGC 0
mrb_value
mrb_APR_apr_to_os_error(mrb_state *mrb, mrb_value self) {
  mrb_int apr_errno;
  mrb_get_args(mrb, "i", &apr_errno);
  int os_errno = APR_TO_OS_ERROR(apr_errno);
  return mrb_fixnum_value(os_errno);
}

mrb_value
mrb_APR_apr_proc_from_pid(mrb_state* mrb, mrb_value self) {
  mrb_int pid;
  mrb_get_args(mrb, "i", &pid);

  apr_proc_t* proc = (apr_proc_t*)malloc(sizeof(apr_proc_t));
  proc->pid = pid;
#if defined(_WIN32) || defined(_WIN64)
   proc->hproc = OpenProcess(MAXIMUM_ALLOWED, false, pid);
#endif

  /* Wasn't made from an apr pool, so "giftwrap" so the ruby gc free's it */
  return mruby_giftwrap_apr_proc_t(mrb, proc);
}
      
#define apr_pool_create_REQUIRED_ARGC 1
#define apr_pool_create_OPTIONAL_ARGC 0
/* apr_pool_create_core_ex
*
* Parameters:
* - parent: apr_pool_t
* Return Type: [apr_status_t, apr_pool_t]
*/
mrb_value
mrb_APR_apr_pool_create(mrb_state* mrb, mrb_value self) {
   mrb_value parent;

   /* Fetch the args */
   mrb_get_args(mrb, "o", &parent);

   /* Type checking */
   if (!mrb_nil_p(parent) && !mrb_obj_is_kind_of(mrb, parent, AprPoolT_class(mrb))) {
      mrb_raise(mrb, E_TYPE_ERROR, "AprPoolT expected");
      return mrb_nil_value();
   }

   /* Unbox parameters */
   apr_pool_t * native_parent = (mrb_nil_p(parent) ? NULL : mruby_unbox_apr_pool_t(parent));

   /* Invocation */
   apr_pool_t * native_newpool = NULL;
   apr_status_t result = apr_pool_create_ex(&native_newpool, native_parent, NULL, NULL);

   /* Box the return value */
   mrb_value return_value = mrb_fixnum_value(result);

   mrb_value results = mrb_ary_new(mrb);
   mrb_ary_push(mrb, results, return_value);
   if (result == 0) {
      /*
       * Giftwrapping the pool ensures it is destroyed when all references to
       * the pool from MRuby are GC'ed
       */
      mrb_ary_push(mrb, results, mruby_giftwrap_apr_pool_t(mrb, native_newpool));
   }
   else {
      mrb_ary_push(mrb, results, mrb_nil_value());
   }

   return results;
}

#define chdir_REQUIRED_ARGC 1
#define chdir_OPTIONAL_ARGC 0
mrb_value
mrb_APR_dir_chdir(mrb_state* mrb, mrb_value self) {
  char* native_thedir;
  mrb_get_args(mrb, "z", &native_thedir);
  int result = APR_FROM_OS_ERROR(chdir(native_thedir));
  mrb_value return_value = mrb_fixnum_value(result);
  return return_value;
}

#define getcwd_REQUIRED_ARGC 0
#define getcwd_OPTIONAL_ARGC 0
mrb_value
mrb_APR_dir_getcwd(mrb_state* mrb, mrb_value self) {
  char* buf = (char*)malloc(sizeof(char) * PATH_MAX + 1);
  char* cwd = getcwd(buf, PATH_MAX);

  mrb_value results = mrb_ary_new(mrb);
  if (cwd == NULL) {
    free(buf);
    mrb_ary_push(mrb, results, mrb_fixnum_value(APR_FROM_OS_ERROR(errno)));
    mrb_ary_push(mrb, results, mrb_nil_value());
  } else {
    mrb_ary_push(mrb, results, mrb_fixnum_value(APR_SUCCESS));
    mrb_ary_push(mrb, results, mrb_str_new_cstr(mrb, cwd));
    free(cwd);
  }
  return results;
}

/* Error Status Checks */

#define STATUS_CHECK(err) \
  mrb_value\
  mrb_APR_APR_STATUS_IS_ ## err (mrb_state* mrb, mrb_value self) {\
    mrb_int status;\
    mrb_get_args(mrb, "i", &status);\
    if (APR_STATUS_IS_ ## err ((apr_status_t)status)) {\
      return mrb_true_value();\
    } else {\
      return mrb_false_value();\
    }\
  }

STATUS_CHECK(EACCES);
STATUS_CHECK(ENOSTAT);
STATUS_CHECK(ENOPOOL);
STATUS_CHECK(EBADDATE);
STATUS_CHECK(EINVALSOCK);
STATUS_CHECK(ENOPROC);
STATUS_CHECK(ENOTIME);
STATUS_CHECK(ENODIR);
STATUS_CHECK(ENOLOCK);
STATUS_CHECK(ENOPOLL);
STATUS_CHECK(ENOSOCKET);
STATUS_CHECK(ENOTHREAD);
STATUS_CHECK(ENOTHDKEY);
STATUS_CHECK(EGENERAL);
STATUS_CHECK(ENOSHMAVAIL);
STATUS_CHECK(EBADIP);
STATUS_CHECK(EBADMASK);
STATUS_CHECK(EDSOOPEN);
STATUS_CHECK(EABSOLUTE);
STATUS_CHECK(ERELATIVE);
STATUS_CHECK(EINCOMPLETE);
STATUS_CHECK(EABOVEROOT);
STATUS_CHECK(EBADPATH);
STATUS_CHECK(EPATHWILD);
STATUS_CHECK(ESYMNOTFOUND);
STATUS_CHECK(EPROC_UNKNOWN);
STATUS_CHECK(ENOTENOUGHENTROPY);
STATUS_CHECK(INCHILD);
STATUS_CHECK(INPARENT);
STATUS_CHECK(DETACH);
STATUS_CHECK(NOTDETACH);
STATUS_CHECK(CHILD_DONE);
STATUS_CHECK(CHILD_NOTDONE);
STATUS_CHECK(TIMEUP);
STATUS_CHECK(INCOMPLETE);
STATUS_CHECK(BADCH);
STATUS_CHECK(BADARG);
STATUS_CHECK(EOF);
STATUS_CHECK(NOTFOUND);
STATUS_CHECK(ANONYMOUS);
STATUS_CHECK(FILEBASED);
STATUS_CHECK(KEYBASED);
STATUS_CHECK(EINIT);
STATUS_CHECK(ENOTIMPL);
STATUS_CHECK(EMISMATCH);
STATUS_CHECK(EBUSY);
STATUS_CHECK(EEXIST);
STATUS_CHECK(ENAMETOOLONG);
STATUS_CHECK(ENOENT);
STATUS_CHECK(ENOTDIR);
STATUS_CHECK(ENOSPC);
STATUS_CHECK(ENOMEM);
STATUS_CHECK(EMFILE);
STATUS_CHECK(ENFILE);
STATUS_CHECK(EBADF);
STATUS_CHECK(EINVAL);
STATUS_CHECK(ESPIPE);
STATUS_CHECK(EAGAIN);
STATUS_CHECK(EINTR);
STATUS_CHECK(ENOTSOCK);
STATUS_CHECK(ECONNREFUSED);
STATUS_CHECK(EINPROGRESS);
STATUS_CHECK(ECONNABORTED);
STATUS_CHECK(ECONNRESET);
STATUS_CHECK(ETIMEDOUT);
STATUS_CHECK(EHOSTUNREACH);
STATUS_CHECK(ENETUNREACH);
STATUS_CHECK(EFTYPE);
STATUS_CHECK(EPIPE);
STATUS_CHECK(EXDEV);
STATUS_CHECK(ENOTEMPTY);
STATUS_CHECK(EAFNOSUPPORT);

/* MRUBY_BINDING_END */

#ifdef __cplusplus
extern "C" {
#endif

/* MRUBY_BINDING: apr_app_initialize */
/* sha: 58846d203ad4f48632181935d51b9461b2ecc645a414627fbe014ab2b2688e7d */
#if BIND_apr_app_initialize_FUNCTION
#define apr_app_initialize_REQUIRED_ARGC 3
#define apr_app_initialize_OPTIONAL_ARGC 0
/* apr_status_t apr_app_initialize(int * argc, const char *const ** argv, const char *const ** env) */
mrb_value
mrb_APR_apr_app_initialize(mrb_state* mrb, mrb_value self) {
  mrb_value argc;
  mrb_value argv;
  mrb_value env;

  /* Fetch the args */
  mrb_get_args(mrb, "ooo", &argc, &argv, &env);

  /* Type checking */
  TODO_type_check_int_PTR(argc);
  TODO_type_check_char_PTR_const_PTR_PTR(argv);
  TODO_type_check_char_PTR_const_PTR_PTR(env);

  /* Unbox param: argc */
  int * native_argc = TODO_mruby_unbox_int_PTR(argc);

  /* Unbox param: argv */
  const char *const ** native_argv = TODO_mruby_unbox_char_PTR_const_PTR_PTR(argv);

  /* Unbox param: env */
  const char *const ** native_env = TODO_mruby_unbox_char_PTR_const_PTR_PTR(env);

  /* Invocation */
  apr_status_t native_return_value = apr_app_initialize(native_argc, native_argv, native_env);

  /* Box the return value */
  mrb_value return_value = mrb_fixnum_value(native_return_value);
  
  return return_value;
}
#endif
/* MRUBY_BINDING_END */

/* MRUBY_BINDING: apr_atoi64 */
/* sha: a7d5bb96c138c35c70c0914a091abc065eef6fc8c0b1fac560fec03870514ea6 */
#if BIND_apr_atoi64_FUNCTION
#define apr_atoi64_REQUIRED_ARGC 1
#define apr_atoi64_OPTIONAL_ARGC 0
/* apr_int64_t apr_atoi64(const char * buf) */
mrb_value
mrb_APR_apr_atoi64(mrb_state* mrb, mrb_value self) {
  char * native_buf = NULL;

  /* Fetch the args */
  mrb_get_args(mrb, "z", &native_buf);

  /* Invocation */
  apr_int64_t native_return_value = apr_atoi64(native_buf);

  /* Box the return value */
  mrb_value return_value = TODO_mruby_box_apr_int64_t(mrb, native_return_value);
  
  return return_value;
}
#endif
/* MRUBY_BINDING_END */

/* MRUBY_BINDING: apr_collapse_spaces */
/* sha: 4907a0f56d99963a1929a9cac32fe818ab7f48789a3a1339b84803d708262bc6 */
#if BIND_apr_collapse_spaces_FUNCTION
#define apr_collapse_spaces_REQUIRED_ARGC 2
#define apr_collapse_spaces_OPTIONAL_ARGC 0
/* char * apr_collapse_spaces(char * dest, const char * src) */
mrb_value
mrb_APR_apr_collapse_spaces(mrb_state* mrb, mrb_value self) {
  mrb_value dest;
  char * native_src = NULL;

  /* Fetch the args */
  mrb_get_args(mrb, "oz", &dest, &native_src);

  /* Type checking */
  TODO_type_check_char_PTR(dest);

  /* Unbox param: dest */
  char * native_dest = TODO_mruby_unbox_char_PTR(dest);

  /* Invocation */
  char * native_return_value = apr_collapse_spaces(native_dest, native_src);

  /* Box the return value */
  mrb_value return_value = TODO_mruby_box_char_PTR(mrb, native_return_value);
  
  return return_value;
}
#endif
/* MRUBY_BINDING_END */

/* MRUBY_BINDING: apr_cpystrn */
/* sha: 3954aef91bb4007bcc70c036d5e8f2bd8f9396f5df6ac5754394baf86f8baa19 */
#if BIND_apr_cpystrn_FUNCTION
#define apr_cpystrn_REQUIRED_ARGC 3
#define apr_cpystrn_OPTIONAL_ARGC 0
/* char * apr_cpystrn(char * dst, const char * src, apr_size_t dst_size) */
mrb_value
mrb_APR_apr_cpystrn(mrb_state* mrb, mrb_value self) {
  mrb_value dst;
  char * native_src = NULL;
  mrb_int native_dst_size;

  /* Fetch the args */
  mrb_get_args(mrb, "ozi", &dst, &native_src, &native_dst_size);

  /* Type checking */
  TODO_type_check_char_PTR(dst);

  /* Unbox param: dst */
  char * native_dst = TODO_mruby_unbox_char_PTR(dst);

  /* Invocation */
  char * native_return_value = apr_cpystrn(native_dst, native_src, native_dst_size);

  /* Box the return value */
  mrb_value return_value = TODO_mruby_box_char_PTR(mrb, native_return_value);
  
  return return_value;
}
#endif
/* MRUBY_BINDING_END */

/* MRUBY_BINDING: apr_ctime */
/* sha: d3f2162f66614f5cf1da5f71930b9b1d1c93c45d09bdbcca18208fc725084d6f */
#if BIND_apr_ctime_FUNCTION
#define apr_ctime_REQUIRED_ARGC 1
#define apr_ctime_OPTIONAL_ARGC 0
/* apr_status_t apr_ctime(char * date_str, apr_time_t t) */
mrb_value
mrb_APR_apr_ctime(mrb_state* mrb, mrb_value self) {
  mrb_int native_t;

  /* Fetch the args */
  mrb_get_args(mrb, "i", &native_t);

  /* Invocation */
  char * native_date_str = (char*)malloc(APR_CTIME_LEN);
  apr_status_t result = apr_ctime(native_date_str, native_t);
  
  /* Box the return value */
  if (result > MRB_INT_MAX) {
    mrb_raise(mrb, mrb->eStandardError_class, "MRuby cannot represent integers greater than MRB_INT_MAX");
    return mrb_nil_value();
  }
  mrb_value return_value = mrb_fixnum_value(result);

  mrb_value results = mrb_ary_new(mrb);
  mrb_ary_push(mrb, results, return_value);
  if (result == 0) {
     mrb_ary_push(mrb, results, mrb_str_new_cstr(mrb, native_date_str));
  }
  else {
     mrb_ary_push(mrb, results, mrb_nil_value());
  }

  free(native_date_str);
  native_date_str = NULL;

  return results;
}
#endif
/* MRUBY_BINDING_END */

/* MRUBY_BINDING: apr_dir_close */
/* sha: user_edited */
#if BIND_apr_dir_close_FUNCTION
#define apr_dir_close_REQUIRED_ARGC 1
#define apr_dir_close_OPTIONAL_ARGC 0
/* apr_dir_close
 *
 * Parameters:
 * - thedir: apr_dir_t *
 * Return Type: apr_status_t
 */
mrb_value
mrb_APR_apr_dir_close(mrb_state* mrb, mrb_value self) {
  mrb_value thedir;

  /* Fetch the args */
  mrb_get_args(mrb, "o", &thedir);

  /* Type checking */
  if (!mrb_obj_is_kind_of(mrb, thedir, AprDirT_class(mrb))) {
    mrb_raise(mrb, E_TYPE_ERROR, "AprDirT expected");
    return mrb_nil_value();
  }

  /* Unbox parameters */
  apr_dir_t * native_thedir = (mrb_nil_p(thedir) ? NULL : mruby_unbox_apr_dir_t(thedir));

  /* Invocation */
  apr_status_t result = apr_dir_close(native_thedir);

  /* Box the return value */
  if (result > MRB_INT_MAX) {
    mrb_raise(mrb, mrb->eStandardError_class, "MRuby cannot represent integers greater than MRB_INT_MAX");
    return mrb_nil_value();
  }
  mrb_value return_value = mrb_fixnum_value(result);

  return return_value;
}
#endif
/* MRUBY_BINDING_END */

/* MRUBY_BINDING: apr_dir_make */
/* sha: user_edited */
#if BIND_apr_dir_make_FUNCTION
#define apr_dir_make_REQUIRED_ARGC 3
#define apr_dir_make_OPTIONAL_ARGC 0
/* apr_dir_make
 *
 * Parameters:
 * - path: const char *
 * - perm: int
 * - pool: apr_pool_t *
 * Return Type: apr_status_t
 */
mrb_value
mrb_APR_apr_dir_make(mrb_state* mrb, mrb_value self) {
  char * native_path;
  mrb_int native_perm;
  mrb_value pool;

  /* Fetch the args */
  mrb_get_args(mrb, "zio", &native_path, &native_perm, &pool);

  /* Type checking */
  if (!mrb_obj_is_kind_of(mrb, pool, AprPoolT_class(mrb))) {
    mrb_raise(mrb, E_TYPE_ERROR, "AprPoolT expected");
    return mrb_nil_value();
  }

  /* Unbox parameters */

  apr_pool_t * native_pool = (mrb_nil_p(pool) ? NULL : mruby_unbox_apr_pool_t(pool));

  /* Invocation */
  apr_status_t result = apr_dir_make(native_path, native_perm, native_pool);

  /* Box the return value */
  if (result > MRB_INT_MAX) {
    mrb_raise(mrb, mrb->eStandardError_class, "MRuby cannot represent integers greater than MRB_INT_MAX");
    return mrb_nil_value();
  }
  mrb_value return_value = mrb_fixnum_value(result);

  return return_value;
}
#endif
/* MRUBY_BINDING_END */

/* MRUBY_BINDING: apr_dir_make_recursive */
/* sha: user_edited */
#if BIND_apr_dir_make_recursive_FUNCTION
#define apr_dir_make_recursive_REQUIRED_ARGC 3
#define apr_dir_make_recursive_OPTIONAL_ARGC 0
/* apr_dir_make_recursive
 *
 * Parameters:
 * - path: const char *
 * - perm: int
 * - pool: apr_pool_t *
 * Return Type: apr_status_t
 */
mrb_value
mrb_APR_apr_dir_make_recursive(mrb_state* mrb, mrb_value self) {
  char * native_path;
  mrb_int native_perm;
  mrb_value pool;

  /* Fetch the args */
  mrb_get_args(mrb, "zio", &native_path, &native_perm, &pool);

  /* Type checking */
  if (!mrb_obj_is_kind_of(mrb, pool, AprPoolT_class(mrb))) {
    mrb_raise(mrb, E_TYPE_ERROR, "AprPoolT expected");
    return mrb_nil_value();
  }

  /* Unbox parameters */

  apr_pool_t * native_pool = (mrb_nil_p(pool) ? NULL : mruby_unbox_apr_pool_t(pool));

  /* Invocation */
  apr_status_t result = apr_dir_make_recursive(native_path, native_perm, native_pool);

  /* Box the return value */
  if (result > MRB_INT_MAX) {
    mrb_raise(mrb, mrb->eStandardError_class, "MRuby cannot represent integers greater than MRB_INT_MAX");
    return mrb_nil_value();
  }
  mrb_value return_value = mrb_fixnum_value(result);

  return return_value;
}
#endif
/* MRUBY_BINDING_END */

/* MRUBY_BINDING: apr_dir_open */
/* sha: user_edited */
#if BIND_apr_dir_open_FUNCTION
#define apr_dir_open_REQUIRED_ARGC 2
#define apr_dir_open_OPTIONAL_ARGC 0
/* apr_dir_open
 *
 * Parameters:
 * - dirname: const char *
 * - pool: apr_pool_t *
 * Return Type: apr_status_t
 */
mrb_value
mrb_APR_apr_dir_open(mrb_state* mrb, mrb_value self) {
  char * native_dirname;
  mrb_value pool;

  /* Fetch the args */
  mrb_get_args(mrb, "zo", &native_dirname, &pool);

  /* Type checking */
  if (!mrb_obj_is_kind_of(mrb, pool, AprPoolT_class(mrb))) {
    mrb_raise(mrb, E_TYPE_ERROR, "AprPoolT expected");
    return mrb_nil_value();
  }

  /* Unbox parameters */

  apr_pool_t * native_pool = (mrb_nil_p(pool) ? NULL : mruby_unbox_apr_pool_t(pool));

  /* Invocation */
  apr_dir_t * native_new_dir;
  apr_status_t result = apr_dir_open(&native_new_dir, native_dirname, native_pool);

  /* Box the return value */
  if (result > MRB_INT_MAX) {
    mrb_raise(mrb, mrb->eStandardError_class, "MRuby cannot represent integers greater than MRB_INT_MAX");
    return mrb_nil_value();
  }
  mrb_value return_value = mrb_fixnum_value(result);

  mrb_value results = mrb_ary_new(mrb);
  mrb_ary_push(mrb, results, return_value);
  if (result == 0) {
     mrb_ary_push(mrb, results, mruby_box_apr_dir_t(mrb, native_new_dir));
  }
  else {
     mrb_ary_push(mrb, results, mrb_nil_value());
  }

  return results;
}
#endif
/* MRUBY_BINDING_END */

/* MRUBY_BINDING: apr_dir_read */
/* sha: user_edited */
#if BIND_apr_dir_read_FUNCTION
#define apr_dir_read_REQUIRED_ARGC 2
#define apr_dir_read_OPTIONAL_ARGC 0
/* apr_dir_read
 *
 * Parameters:
 * - wanted: int
 * - thedir: apr_dir_t *
 * Return Type: apr_status_t
 */
mrb_value
mrb_APR_apr_dir_read(mrb_state* mrb, mrb_value self) {
  mrb_int native_wanted;
  mrb_value thedir;

  /* Fetch the args */
  mrb_get_args(mrb, "io", &native_wanted, &thedir);

  /* Type checking */
  if (!mrb_obj_is_kind_of(mrb, thedir, AprDirT_class(mrb))) {
    mrb_raise(mrb, E_TYPE_ERROR, "AprDirT expected");
    return mrb_nil_value();
  }

  /* Unbox parameters */

  apr_dir_t * native_thedir = (mrb_nil_p(thedir) ? NULL : mruby_unbox_apr_dir_t(thedir));

  /* Invocation */
  apr_finfo_t native_finfo;
  apr_status_t result = apr_dir_read(&native_finfo, native_wanted, native_thedir);

  /* Box the return value */
  mrb_value return_value = mrb_fixnum_value(result);

  mrb_value results = mrb_ary_new(mrb);
  mrb_ary_push(mrb, results, return_value);
  /* Even when incomplete is returned, some values are valid */
  if (result == APR_SUCCESS || result == APR_INCOMPLETE) {
     apr_finfo_t* new_finfo = (apr_finfo_t*)malloc(sizeof(apr_finfo_t));
     memcpy(new_finfo, &native_finfo, sizeof(apr_finfo_t));
     mrb_ary_push(mrb, results, mruby_giftwrap_apr_finfo_t(mrb, new_finfo));
  }
  else {
     mrb_ary_push(mrb, results, mrb_nil_value());
  }

  return results;
}
#endif
/* MRUBY_BINDING_END */

/* MRUBY_BINDING: apr_dir_remove */
/* sha: user_edited */
#if BIND_apr_dir_remove_FUNCTION
#define apr_dir_remove_REQUIRED_ARGC 2
#define apr_dir_remove_OPTIONAL_ARGC 0
/* apr_dir_remove
 *
 * Parameters:
 * - path: const char *
 * - pool: apr_pool_t *
 * Return Type: apr_status_t
 */
mrb_value
mrb_APR_apr_dir_remove(mrb_state* mrb, mrb_value self) {
  char * native_path;
  mrb_value pool;

  /* Fetch the args */
  mrb_get_args(mrb, "zo", &native_path, &pool);

  /* Type checking */
  if (!mrb_obj_is_kind_of(mrb, pool, AprPoolT_class(mrb))) {
    mrb_raise(mrb, E_TYPE_ERROR, "AprPoolT expected");
    return mrb_nil_value();
  }

  /* Unbox parameters */

  apr_pool_t * native_pool = (mrb_nil_p(pool) ? NULL : mruby_unbox_apr_pool_t(pool));

  /* Invocation */
  apr_status_t result = apr_dir_remove(native_path, native_pool);

  /* Box the return value */
  if (result > MRB_INT_MAX) {
    mrb_raise(mrb, mrb->eStandardError_class, "MRuby cannot represent integers greater than MRB_INT_MAX");
    return mrb_nil_value();
  }
  mrb_value return_value = mrb_fixnum_value(result);

  return return_value;
}
#endif
/* MRUBY_BINDING_END */

/* MRUBY_BINDING: apr_dir_rewind */
/* sha: user_edited */
#if BIND_apr_dir_rewind_FUNCTION
#define apr_dir_rewind_REQUIRED_ARGC 1
#define apr_dir_rewind_OPTIONAL_ARGC 0
/* apr_dir_rewind
 *
 * Parameters:
 * - thedir: apr_dir_t *
 * Return Type: apr_status_t
 */
mrb_value
mrb_APR_apr_dir_rewind(mrb_state* mrb, mrb_value self) {
  mrb_value thedir;

  /* Fetch the args */
  mrb_get_args(mrb, "o", &thedir);

  /* Type checking */
  if (!mrb_obj_is_kind_of(mrb, thedir, AprDirT_class(mrb))) {
    mrb_raise(mrb, E_TYPE_ERROR, "AprDirT expected");
    return mrb_nil_value();
  }

  /* Unbox parameters */
  apr_dir_t * native_thedir = (mrb_nil_p(thedir) ? NULL : mruby_unbox_apr_dir_t(thedir));

  /* Invocation */
  apr_status_t result = apr_dir_rewind(native_thedir);

  /* Box the return value */
  if (result > MRB_INT_MAX) {
    mrb_raise(mrb, mrb->eStandardError_class, "MRuby cannot represent integers greater than MRB_INT_MAX");
    return mrb_nil_value();
  }
  mrb_value return_value = mrb_fixnum_value(result);

  return return_value;
}
#endif
/* MRUBY_BINDING_END */

/* MRUBY_BINDING: apr_env_delete */
/* sha: user_edited */
#if BIND_apr_env_delete_FUNCTION
#define apr_env_delete_REQUIRED_ARGC 2
#define apr_env_delete_OPTIONAL_ARGC 0
/* apr_env_delete
 *
 * Parameters:
 * - envvar: const char *
 * - pool: apr_pool_t *
 * Return Type: apr_status_t
 */
mrb_value
mrb_APR_apr_env_delete(mrb_state* mrb, mrb_value self) {
  char * native_envvar;
  mrb_value pool;

  /* Fetch the args */
  mrb_get_args(mrb, "zo", &native_envvar, &pool);

  /* Type checking */
  if (!mrb_obj_is_kind_of(mrb, pool, AprPoolT_class(mrb))) {
    mrb_raise(mrb, E_TYPE_ERROR, "AprPoolT expected");
    return mrb_nil_value();
  }

  /* Unbox parameters */

  apr_pool_t * native_pool = (mrb_nil_p(pool) ? NULL : mruby_unbox_apr_pool_t(pool));

  /* Invocation */
  apr_status_t result = apr_env_delete(native_envvar, native_pool);

  /* Box the return value */
  if (result > MRB_INT_MAX) {
    mrb_raise(mrb, mrb->eStandardError_class, "MRuby cannot represent integers greater than MRB_INT_MAX");
    return mrb_nil_value();
  }
  mrb_value return_value = mrb_fixnum_value(result);

  return return_value;
}
#endif
/* MRUBY_BINDING_END */

/* MRUBY_BINDING: apr_env_get */
/* sha: user_edited */
#if BIND_apr_env_get_FUNCTION
#define apr_env_get_REQUIRED_ARGC 2
#define apr_env_get_OPTIONAL_ARGC 0
/* apr_env_get
 *
 * Parameters:
 * - envvar: String
 * - pool: AprPoolT
 * Return Type: [errno: Fixnum, value: String]
 */
mrb_value
mrb_APR_apr_env_get(mrb_state* mrb, mrb_value self) {
  char * native_envvar;
  mrb_value pool;

  /* Fetch the args */
  mrb_get_args(mrb, "zo", &native_envvar, &pool);

  /* Type checking */
  if (!mrb_obj_is_kind_of(mrb, pool, AprPoolT_class(mrb))) {
    mrb_raise(mrb, E_TYPE_ERROR, "AprPoolT expected");
    return mrb_nil_value();
  }

  /* Unbox parameters */

  apr_pool_t * native_pool = (mrb_nil_p(pool) ? NULL : mruby_unbox_apr_pool_t(pool));

  /* Invocation */
  char * native_value;
  apr_status_t result = apr_env_get(&native_value, native_envvar, native_pool);

  /* Box the return value */
  if (result > MRB_INT_MAX) {
    mrb_raise(mrb, mrb->eStandardError_class, "MRuby cannot represent integers greater than MRB_INT_MAX");
    return mrb_nil_value();
  }
  mrb_value return_value = mrb_fixnum_value(result);

  mrb_value results = mrb_ary_new(mrb);
  mrb_ary_push(mrb, results, return_value);
  if (result == 0){
     mrb_ary_push(mrb, results, mrb_str_new_cstr(mrb, native_value));
  }
  else {
     mrb_ary_push(mrb, results, mrb_nil_value());
  }

  return results;
}
#endif
/* MRUBY_BINDING_END */

/* MRUBY_BINDING: apr_env_set */
/* sha: user_edited */
#if BIND_apr_env_set_FUNCTION
#define apr_env_set_REQUIRED_ARGC 3
#define apr_env_set_OPTIONAL_ARGC 0
/* apr_env_set
 *
 * Parameters:
 * - envvar: String
 * - value: String
 * - pool: apr_pool_t *
 * Return Type: apr_status_t
 */
mrb_value
mrb_APR_apr_env_set(mrb_state* mrb, mrb_value self) {
  char * native_envvar;
  char * native_value;
  mrb_value pool;

  /* Fetch the args */
  mrb_get_args(mrb, "zzo", &native_envvar, &native_value, &pool);

  /* Type checking */
  if (!mrb_obj_is_kind_of(mrb, pool, AprPoolT_class(mrb))) {
    mrb_raise(mrb, E_TYPE_ERROR, "AprPoolT expected");
    return mrb_nil_value();
  }

  /* Unbox parameters */

  apr_pool_t * native_pool = (mrb_nil_p(pool) ? NULL : mruby_unbox_apr_pool_t(pool));

  /* Invocation */
  apr_status_t result = apr_env_set(native_envvar, native_value, native_pool);

  /* Box the return value */
  if (result > MRB_INT_MAX) {
    mrb_raise(mrb, mrb->eStandardError_class, "MRuby cannot represent integers greater than MRB_INT_MAX");
    return mrb_nil_value();
  }
  mrb_value return_value = mrb_fixnum_value(result);

  return return_value;
}
#endif
/* MRUBY_BINDING_END */

/* MRUBY_BINDING: apr_file_append */
/* sha: user_edited */
#if BIND_apr_file_append_FUNCTION
#define apr_file_append_REQUIRED_ARGC 4
#define apr_file_append_OPTIONAL_ARGC 0
/* apr_file_append
 *
 * Parameters:
 * - from_path: const char *
 * - to_path: const char *
 * - perms: int
 * - pool: apr_pool_t *
 * Return Type: apr_status_t
 */
mrb_value
mrb_APR_apr_file_append(mrb_state* mrb, mrb_value self) {
  char * native_from_path;
  char * native_to_path;
  mrb_int native_perms;
  mrb_value pool;

  /* Fetch the args */
  mrb_get_args(mrb, "zzio", &native_from_path, &native_to_path, &native_perms, &pool);

  /* Type checking */
  if (!mrb_obj_is_kind_of(mrb, pool, AprPoolT_class(mrb))) {
    mrb_raise(mrb, E_TYPE_ERROR, "AprPoolT expected");
    return mrb_nil_value();
  }

  /* Unbox parameters */

  apr_pool_t * native_pool = (mrb_nil_p(pool) ? NULL : mruby_unbox_apr_pool_t(pool));

  /* Invocation */
  apr_status_t result = apr_file_append(native_from_path, native_to_path, native_perms, native_pool);

  /* Box the return value */
  if (result > MRB_INT_MAX) {
    mrb_raise(mrb, mrb->eStandardError_class, "MRuby cannot represent integers greater than MRB_INT_MAX");
    return mrb_nil_value();
  }
  mrb_value return_value = mrb_fixnum_value(result);

  return return_value;
}
#endif
/* MRUBY_BINDING_END */

/* MRUBY_BINDING: apr_file_attrs_set */
/* sha: user_edited */
#if BIND_apr_file_attrs_set_FUNCTION
#define apr_file_attrs_set_REQUIRED_ARGC 4
#define apr_file_attrs_set_OPTIONAL_ARGC 0
/* apr_file_attrs_set
 *
 * Parameters:
 * - fname: String
 * - attributes: Fixnum
 * - attr_mask: Fixnum
 * - pool: AprPoolT
 * Return Type: Fixnum (errno)
 */
mrb_value
mrb_APR_apr_file_attrs_set(mrb_state* mrb, mrb_value self) {
  char * native_fname;
  mrb_int native_attributes;
  mrb_int native_attr_mask;
  mrb_value pool;

  /* Fetch the args */
  mrb_get_args(mrb, "ziio", &native_fname, &native_attributes, &native_attr_mask, &pool);

  /* Type checking */
  if (!mrb_obj_is_kind_of(mrb, pool, AprPoolT_class(mrb))) {
    mrb_raise(mrb, E_TYPE_ERROR, "AprPoolT expected");
    return mrb_nil_value();
  }

  /* Unbox parameters */

  apr_pool_t * native_pool = (mrb_nil_p(pool) ? NULL : mruby_unbox_apr_pool_t(pool));

  /* Invocation */
  apr_status_t result = apr_file_attrs_set(native_fname, native_attributes, native_attr_mask, native_pool);

  /* Box the return value */
  if (result > MRB_INT_MAX) {
    mrb_raise(mrb, mrb->eStandardError_class, "MRuby cannot represent integers greater than MRB_INT_MAX");
    return mrb_nil_value();
  }
  mrb_value return_value = mrb_fixnum_value(result);

  return return_value;
}
#endif
/* MRUBY_BINDING_END */

/* MRUBY_BINDING: apr_file_buffer_set */
/* sha: 233e90b3adf396b23a87723ce2a1a24b941d32e57c6cb0251cc6277d23be52c2 */
#if BIND_apr_file_buffer_set_FUNCTION
#define apr_file_buffer_set_REQUIRED_ARGC 3
#define apr_file_buffer_set_OPTIONAL_ARGC 0
/* apr_status_t apr_file_buffer_set(apr_file_t * thefile, char * buffer, apr_size_t bufsize) */
mrb_value
mrb_APR_apr_file_buffer_set(mrb_state* mrb, mrb_value self) {
  mrb_value thefile;
  mrb_value buffer;
  mrb_int native_bufsize;

  /* Fetch the args */
  mrb_get_args(mrb, "ooi", &thefile, &buffer, &native_bufsize);

  /* Type checking */
  if (!mrb_obj_is_kind_of(mrb, thefile, AprFileT_class(mrb))) {
    mrb_raise(mrb, E_TYPE_ERROR, "AprFileT expected");
    return mrb_nil_value();
  }
  TODO_type_check_char_PTR(buffer);

  /* Unbox param: thefile */
  apr_file_t * native_thefile = (mrb_nil_p(thefile) ? NULL : mruby_unbox_apr_file_t(thefile));

  /* Unbox param: buffer */
  char * native_buffer = TODO_mruby_unbox_char_PTR(buffer);

  /* Invocation */
  apr_status_t native_return_value = apr_file_buffer_set(native_thefile, native_buffer, native_bufsize);

  /* Box the return value */
  mrb_value return_value = mrb_fixnum_value(native_return_value);
  
  return return_value;
}
#endif
/* MRUBY_BINDING_END */

/* MRUBY_BINDING: apr_file_buffer_size_get */
/* sha: user_edited */
#if BIND_apr_file_buffer_size_get_FUNCTION
#define apr_file_buffer_size_get_REQUIRED_ARGC 1
#define apr_file_buffer_size_get_OPTIONAL_ARGC 0
/* apr_file_buffer_size_get
 *
 * Parameters:
 * - thefile: apr_file_t *
 * Return Type: apr_size_t
 */
mrb_value
mrb_APR_apr_file_buffer_size_get(mrb_state* mrb, mrb_value self) {
  mrb_value thefile;

  /* Fetch the args */
  mrb_get_args(mrb, "o", &thefile);

  /* Type checking */
  if (!mrb_obj_is_kind_of(mrb, thefile, AprFileT_class(mrb))) {
    mrb_raise(mrb, E_TYPE_ERROR, "AprFileT expected");
    return mrb_nil_value();
  }

  /* Unbox parameters */
  apr_file_t * native_thefile = (mrb_nil_p(thefile) ? NULL : mruby_unbox_apr_file_t(thefile));

  /* Invocation */
  apr_size_t result = apr_file_buffer_size_get(native_thefile);

  /* Box the return value */
  if (result > MRB_INT_MAX) {
    mrb_raise(mrb, mrb->eStandardError_class, "MRuby cannot represent integers greater than MRB_INT_MAX");
    return mrb_nil_value();
  }
  mrb_value return_value = mrb_fixnum_value(result);

  return return_value;
}
#endif
/* MRUBY_BINDING_END */

/* MRUBY_BINDING: apr_file_close */
/* sha: user_edited */
#if BIND_apr_file_close_FUNCTION
#define apr_file_close_REQUIRED_ARGC 1
#define apr_file_close_OPTIONAL_ARGC 0
/* apr_file_close
 *
 * Parameters:
 * - file: apr_file_t *
 * Return Type: apr_status_t
 */
mrb_value
mrb_APR_apr_file_close(mrb_state* mrb, mrb_value self) {
  mrb_value file;

  /* Fetch the args */
  mrb_get_args(mrb, "o", &file);

  /* Type checking */
  if (!mrb_obj_is_kind_of(mrb, file, AprFileT_class(mrb))) {
    mrb_raise(mrb, E_TYPE_ERROR, "AprFileT expected");
    return mrb_nil_value();
  }

  /* Unbox parameters */
  apr_file_t * native_file = (mrb_nil_p(file) ? NULL : mruby_unbox_apr_file_t(file));

  /* Invocation */
  apr_status_t result = apr_file_close(native_file);

  /* Box the return value */
  if (result > MRB_INT_MAX) {
    mrb_raise(mrb, mrb->eStandardError_class, "MRuby cannot represent integers greater than MRB_INT_MAX");
    return mrb_nil_value();
  }
  mrb_value return_value = mrb_fixnum_value(result);

  return return_value;
}
#endif
/* MRUBY_BINDING_END */

/* MRUBY_BINDING: apr_file_copy */
/* sha: user_edited */
#if BIND_apr_file_copy_FUNCTION
#define apr_file_copy_REQUIRED_ARGC 4
#define apr_file_copy_OPTIONAL_ARGC 0
/* apr_file_copy
 *
 * Parameters:
 * - from_path: String
 * - to_path: String
 * - perms: int
 * - pool: AprPoolType
 * Return Type: AprStatusT
 */
mrb_value
mrb_APR_apr_file_copy(mrb_state* mrb, mrb_value self) {
  char * native_from_path;
  char * native_to_path;
  mrb_int native_perms;
  mrb_value pool;

  /* Fetch the args */
  mrb_get_args(mrb, "zzio", &native_from_path, &native_to_path, &native_perms, &pool);

  /* Type checking */
  if (!mrb_obj_is_kind_of(mrb, pool, AprPoolT_class(mrb))) {
    mrb_raise(mrb, E_TYPE_ERROR, "AprPoolT expected");
    return mrb_nil_value();
  }

  /* Unbox parameters */

  apr_pool_t * native_pool = (mrb_nil_p(pool) ? NULL : mruby_unbox_apr_pool_t(pool));

  /* Invocation */
  apr_status_t result = apr_file_copy(native_from_path, native_to_path, native_perms, native_pool);

  /* Box the return value */
  if (result > MRB_INT_MAX) {
    mrb_raise(mrb, mrb->eStandardError_class, "MRuby cannot represent integers greater than MRB_INT_MAX");
    return mrb_nil_value();
  }
  mrb_value return_value = mrb_fixnum_value(result);

  return return_value;
}
#endif
/* MRUBY_BINDING_END */

/* MRUBY_BINDING: apr_file_data_get */
/* sha: b44e1b63e2423746f376dfcab0ee39b48304b71547c0e1ac5bae143e750b589a */
#if BIND_apr_file_data_get_FUNCTION
#define apr_file_data_get_REQUIRED_ARGC 3
#define apr_file_data_get_OPTIONAL_ARGC 0
/* apr_status_t apr_file_data_get(void ** data, const char * key, apr_file_t * file) */
mrb_value
mrb_APR_apr_file_data_get(mrb_state* mrb, mrb_value self) {
  mrb_value data;
  char * native_key = NULL;
  mrb_value file;

  /* Fetch the args */
  mrb_get_args(mrb, "ozo", &data, &native_key, &file);

  /* Type checking */
  TODO_type_check_void_PTR_PTR(data);
  if (!mrb_obj_is_kind_of(mrb, file, AprFileT_class(mrb))) {
    mrb_raise(mrb, E_TYPE_ERROR, "AprFileT expected");
    return mrb_nil_value();
  }

  /* Unbox param: data */
  void ** native_data = TODO_mruby_unbox_void_PTR_PTR(data);

  /* Unbox param: file */
  apr_file_t * native_file = (mrb_nil_p(file) ? NULL : mruby_unbox_apr_file_t(file));

  /* Invocation */
  apr_status_t native_return_value = apr_file_data_get(native_data, native_key, native_file);

  /* Box the return value */
  mrb_value return_value = mrb_fixnum_value(native_return_value);
  
  return return_value;
}
#endif
/* MRUBY_BINDING_END */

/* MRUBY_BINDING: apr_file_data_set */
/* sha: 24d5243a23f5ea5bf6c04cedf80fdfcf2e77af7016d76d61795303d3c5620fca */
#if BIND_apr_file_data_set_FUNCTION
#define apr_file_data_set_REQUIRED_ARGC 4
#define apr_file_data_set_OPTIONAL_ARGC 0
/* apr_status_t apr_file_data_set(apr_file_t * file, void * data, const char * key, apr_status_t (*)(void *) cleanup) */
mrb_value
mrb_APR_apr_file_data_set(mrb_state* mrb, mrb_value self) {
  mrb_value file;
  mrb_value data;
  char * native_key = NULL;
  mrb_value cleanup;

  /* Fetch the args */
  mrb_get_args(mrb, "oozo", &file, &data, &native_key, &cleanup);

  /* Type checking */
  if (!mrb_obj_is_kind_of(mrb, file, AprFileT_class(mrb))) {
    mrb_raise(mrb, E_TYPE_ERROR, "AprFileT expected");
    return mrb_nil_value();
  }
  TODO_type_check_void_PTR(data);
  TODO_type_check_apr_status_t_LPAREN_PTR_RPAREN_LPAREN_void_PTR_RPAREN(cleanup);

  /* Unbox param: file */
  apr_file_t * native_file = (mrb_nil_p(file) ? NULL : mruby_unbox_apr_file_t(file));

  /* Unbox param: data */
  void * native_data = TODO_mruby_unbox_void_PTR(data);

  /* Unbox param: cleanup */
  apr_status_t (*native_cleanup)(void *) = TODO_mruby_unbox_apr_status_t_LPAREN_PTR_RPAREN_LPAREN_void_PTR_RPAREN(cleanup);

  /* Invocation */
  apr_status_t native_return_value = apr_file_data_set(native_file, native_data, native_key, native_cleanup);

  /* Box the return value */
  mrb_value return_value = mrb_fixnum_value(native_return_value);
  
  return return_value;
}
#endif
/* MRUBY_BINDING_END */

/* MRUBY_BINDING: apr_file_datasync */
/* sha: user_edited */
#if BIND_apr_file_datasync_FUNCTION
#define apr_file_datasync_REQUIRED_ARGC 1
#define apr_file_datasync_OPTIONAL_ARGC 0
/* apr_file_datasync
 *
 * Parameters:
 * - thefile: apr_file_t *
 * Return Type: apr_status_t
 */
mrb_value
mrb_APR_apr_file_datasync(mrb_state* mrb, mrb_value self) {
  mrb_value thefile;

  /* Fetch the args */
  mrb_get_args(mrb, "o", &thefile);

  /* Type checking */
  if (!mrb_obj_is_kind_of(mrb, thefile, AprFileT_class(mrb))) {
    mrb_raise(mrb, E_TYPE_ERROR, "AprFileT expected");
    return mrb_nil_value();
  }

  /* Unbox parameters */
  apr_file_t * native_thefile = (mrb_nil_p(thefile) ? NULL : mruby_unbox_apr_file_t(thefile));

  /* Invocation */
  apr_status_t result = apr_file_datasync(native_thefile);

  /* Box the return value */
  if (result > MRB_INT_MAX) {
    mrb_raise(mrb, mrb->eStandardError_class, "MRuby cannot represent integers greater than MRB_INT_MAX");
    return mrb_nil_value();
  }
  mrb_value return_value = mrb_fixnum_value(result);

  return return_value;
}
#endif
/* MRUBY_BINDING_END */

/* MRUBY_BINDING: apr_file_dup */
/* sha: 61427bfe5bebe6511628dd54b5a1ea4bb0c30f13eab67313275dd3287fa9fb9a */
#if BIND_apr_file_dup_FUNCTION
#define apr_file_dup_REQUIRED_ARGC 3
#define apr_file_dup_OPTIONAL_ARGC 0
/* apr_status_t apr_file_dup(apr_file_t ** new_file, apr_file_t * old_file, apr_pool_t * p) */
mrb_value
mrb_APR_apr_file_dup(mrb_state* mrb, mrb_value self) {
  mrb_value new_file;
  mrb_value old_file;
  mrb_value p;

  /* Fetch the args */
  mrb_get_args(mrb, "ooo", &new_file, &old_file, &p);

  /* Type checking */
  TODO_type_check_apr_file_t_PTR_PTR(new_file);
  if (!mrb_obj_is_kind_of(mrb, old_file, AprFileT_class(mrb))) {
    mrb_raise(mrb, E_TYPE_ERROR, "AprFileT expected");
    return mrb_nil_value();
  }
  if (!mrb_obj_is_kind_of(mrb, p, AprPoolT_class(mrb))) {
    mrb_raise(mrb, E_TYPE_ERROR, "AprPoolT expected");
    return mrb_nil_value();
  }

  /* Unbox param: new_file */
  apr_file_t ** native_new_file = TODO_mruby_unbox_apr_file_t_PTR_PTR(new_file);

  /* Unbox param: old_file */
  apr_file_t * native_old_file = (mrb_nil_p(old_file) ? NULL : mruby_unbox_apr_file_t(old_file));

  /* Unbox param: p */
  apr_pool_t * native_p = (mrb_nil_p(p) ? NULL : mruby_unbox_apr_pool_t(p));

  /* Invocation */
  apr_status_t native_return_value = apr_file_dup(native_new_file, native_old_file, native_p);

  /* Box the return value */
  mrb_value return_value = mrb_fixnum_value(native_return_value);
  
  return return_value;
}
#endif
/* MRUBY_BINDING_END */

/* MRUBY_BINDING: apr_file_dup2 */
/* sha: 16682dd99880b3955c1d31dd1fcc058892928f3c4ea343fa2142076043dda146 */
#if BIND_apr_file_dup2_FUNCTION
#define apr_file_dup2_REQUIRED_ARGC 3
#define apr_file_dup2_OPTIONAL_ARGC 0
/* apr_status_t apr_file_dup2(apr_file_t * new_file, apr_file_t * old_file, apr_pool_t * p) */
mrb_value
mrb_APR_apr_file_dup2(mrb_state* mrb, mrb_value self) {
  mrb_value new_file;
  mrb_value old_file;
  mrb_value p;

  /* Fetch the args */
  mrb_get_args(mrb, "ooo", &new_file, &old_file, &p);

  /* Type checking */
  if (!mrb_obj_is_kind_of(mrb, new_file, AprFileT_class(mrb))) {
    mrb_raise(mrb, E_TYPE_ERROR, "AprFileT expected");
    return mrb_nil_value();
  }
  if (!mrb_obj_is_kind_of(mrb, old_file, AprFileT_class(mrb))) {
    mrb_raise(mrb, E_TYPE_ERROR, "AprFileT expected");
    return mrb_nil_value();
  }
  if (!mrb_obj_is_kind_of(mrb, p, AprPoolT_class(mrb))) {
    mrb_raise(mrb, E_TYPE_ERROR, "AprPoolT expected");
    return mrb_nil_value();
  }

  /* Unbox param: new_file */
  apr_file_t * native_new_file = (mrb_nil_p(new_file) ? NULL : mruby_unbox_apr_file_t(new_file));

  /* Unbox param: old_file */
  apr_file_t * native_old_file = (mrb_nil_p(old_file) ? NULL : mruby_unbox_apr_file_t(old_file));

  /* Unbox param: p */
  apr_pool_t * native_p = (mrb_nil_p(p) ? NULL : mruby_unbox_apr_pool_t(p));

  /* Invocation */
  apr_status_t native_return_value = apr_file_dup2(native_new_file, native_old_file, native_p);

  /* Box the return value */
  mrb_value return_value = mrb_fixnum_value(native_return_value);
  
  return return_value;
}
#endif
/* MRUBY_BINDING_END */

/* MRUBY_BINDING: apr_file_eof */
/* sha: user_edited */
#if BIND_apr_file_eof_FUNCTION
#define apr_file_eof_REQUIRED_ARGC 1
#define apr_file_eof_OPTIONAL_ARGC 0
/* apr_file_eof
 *
 * Parameters:
 * - fptr: apr_file_t *
 * Return Type: apr_status_t
 */
mrb_value
mrb_APR_apr_file_eof(mrb_state* mrb, mrb_value self) {
  mrb_value fptr;

  /* Fetch the args */
  mrb_get_args(mrb, "o", &fptr);

  /* Type checking */
  if (!mrb_obj_is_kind_of(mrb, fptr, AprFileT_class(mrb))) {
    mrb_raise(mrb, E_TYPE_ERROR, "AprFileT expected");
    return mrb_nil_value();
  }

  /* Unbox parameters */
  apr_file_t * native_fptr = (mrb_nil_p(fptr) ? NULL : mruby_unbox_apr_file_t(fptr));

  /* Invocation */
  apr_status_t result = apr_file_eof(native_fptr);

  /* Box the return value */
  if (result > MRB_INT_MAX) {
    mrb_raise(mrb, mrb->eStandardError_class, "MRuby cannot represent integers greater than MRB_INT_MAX");
    return mrb_nil_value();
  }
  mrb_value return_value = mrb_fixnum_value(result);

  return return_value;
}
#endif
/* MRUBY_BINDING_END */

/* MRUBY_BINDING: apr_file_flags_get */
/* sha: user_edited */
#if BIND_apr_file_flags_get_FUNCTION
#define apr_file_flags_get_REQUIRED_ARGC 1
#define apr_file_flags_get_OPTIONAL_ARGC 0
/* apr_file_flags_get
 *
 * Parameters:
 * - f: apr_file_t *
 * Return Type: apr_int32_t
 */
mrb_value
mrb_APR_apr_file_flags_get(mrb_state* mrb, mrb_value self) {
  mrb_value f;

  /* Fetch the args */
  mrb_get_args(mrb, "o", &f);

  /* Type checking */
  if (!mrb_obj_is_kind_of(mrb, f, AprFileT_class(mrb))) {
    mrb_raise(mrb, E_TYPE_ERROR, "AprFileT expected");
    return mrb_nil_value();
  }

  /* Unbox parameters */
  apr_file_t * native_f = (mrb_nil_p(f) ? NULL : mruby_unbox_apr_file_t(f));

  /* Invocation */
  apr_int32_t result = apr_file_flags_get(native_f);

  /* Box the return value */
  if (result > MRB_INT_MAX) {
    mrb_raise(mrb, mrb->eStandardError_class, "MRuby cannot represent integers greater than MRB_INT_MAX");
    return mrb_nil_value();
  }
  mrb_value return_value = mrb_fixnum_value(result);

  return return_value;
}
#endif
/* MRUBY_BINDING_END */

/* MRUBY_BINDING: apr_file_flush */
/* sha: user_edited */
#if BIND_apr_file_flush_FUNCTION
#define apr_file_flush_REQUIRED_ARGC 1
#define apr_file_flush_OPTIONAL_ARGC 0
/* apr_file_flush
 *
 * Parameters:
 * - thefile: apr_file_t *
 * Return Type: apr_status_t
 */
mrb_value
mrb_APR_apr_file_flush(mrb_state* mrb, mrb_value self) {
  mrb_value thefile;

  /* Fetch the args */
  mrb_get_args(mrb, "o", &thefile);

  /* Type checking */
  if (!mrb_obj_is_kind_of(mrb, thefile, AprFileT_class(mrb))) {
    mrb_raise(mrb, E_TYPE_ERROR, "AprFileT expected");
    return mrb_nil_value();
  }

  /* Unbox parameters */
  apr_file_t * native_thefile = (mrb_nil_p(thefile) ? NULL : mruby_unbox_apr_file_t(thefile));

  /* Invocation */
  apr_status_t result = apr_file_flush(native_thefile);

  /* Box the return value */
  if (result > MRB_INT_MAX) {
    mrb_raise(mrb, mrb->eStandardError_class, "MRuby cannot represent integers greater than MRB_INT_MAX");
    return mrb_nil_value();
  }
  mrb_value return_value = mrb_fixnum_value(result);

  return return_value;
}
#endif
/* MRUBY_BINDING_END */

/* MRUBY_BINDING: apr_file_getc */
/* sha: user_edited */
#if BIND_apr_file_getc_FUNCTION
#define apr_file_getc_REQUIRED_ARGC 1
#define apr_file_getc_OPTIONAL_ARGC 0
/* apr_file_getc
 *
 * Parameters:
 * - thefile: AprFileT
 * Return Type: errno: Fixnum, char: String
 */
mrb_value
mrb_APR_apr_file_getc(mrb_state* mrb, mrb_value self) {
  mrb_value thefile;

  /* Fetch the args */
  mrb_get_args(mrb, "o", &thefile);
  if (!mrb_obj_is_kind_of(mrb, thefile, AprFileT_class(mrb))) {
    mrb_raise(mrb, E_TYPE_ERROR, "AprFileT expected");
    return mrb_nil_value();
  }
  apr_file_t * native_thefile = (mrb_nil_p(thefile) ? NULL : mruby_unbox_apr_file_t(thefile));

  /* Invocation */
  char native_ch;
  apr_status_t result = apr_file_getc(&native_ch, native_thefile);
  if (result == APR_SUCCESS) {
    RETURN_ERRNO_AND_OUTPUT(result, mrb_str_new(mrb, &native_ch, 1));
  } else {
    RETURN_ERRNO_AND_OUTPUT(result, mrb_nil_value());
  }
}
#endif
/* MRUBY_BINDING_END */

/* MRUBY_BINDING: apr_file_gets */
/* sha: user_edited */
#if BIND_apr_file_gets_FUNCTION
#define apr_file_gets_REQUIRED_ARGC 2
#define apr_file_gets_OPTIONAL_ARGC 0
/* apr_file_gets
 *
 * Parameters:
 * - len: int
 * - thefile: apr_file_t *
 * Return Type: [int, String]
 */
mrb_value
mrb_APR_apr_file_gets(mrb_state* mrb, mrb_value self) {
  mrb_int native_len;
  mrb_value thefile;

  /* Fetch the args */
  mrb_get_args(mrb, "io", &native_len, &thefile);
  if (!mrb_obj_is_kind_of(mrb, thefile, AprFileT_class(mrb))) {
    mrb_raise(mrb, E_TYPE_ERROR, "AprFileT expected");
    return mrb_nil_value();
  }

  /* Unbox parameters */

  apr_file_t * native_thefile = (mrb_nil_p(thefile) ? NULL : mruby_unbox_apr_file_t(thefile));

  /* Invocation */
  char * native_str = (char*)malloc(sizeof(char) * (native_len + 1)); /* gets adds a null terminter */
  apr_status_t result = apr_file_gets(native_str, native_len + 1, native_thefile); /* len argument is length of buffer, NOT the string, so add one for null */

  /* Box the return value */
  if (result > MRB_INT_MAX) {
    mrb_raise(mrb, mrb->eStandardError_class, "MRuby cannot represent integers greater than MRB_INT_MAX");
    return mrb_nil_value();
  }
  mrb_value return_value = mrb_fixnum_value(result);

  mrb_value results = mrb_ary_new(mrb);
  mrb_ary_push(mrb, results, return_value);
  if (result == 0) {
     mrb_value ruby_str = mrb_str_new(mrb, native_str, strlen(native_str));
     mrb_ary_push(mrb, results, ruby_str);
  }
  else {
     mrb_ary_push(mrb, results, mrb_nil_value());
  }

  /* Clean up memory */
  free(native_str);
  native_str = NULL;

  return results;
}
#endif
/* MRUBY_BINDING_END */

/* MRUBY_BINDING: apr_file_info_get */
/* sha: user_edited */
#if BIND_apr_file_info_get_FUNCTION
#define apr_file_info_get_REQUIRED_ARGC 2
#define apr_file_info_get_OPTIONAL_ARGC 0
/* apr_file_info_get
 *
 * Parameters:
 * - wanted: Fixnum
 * - thefile: AprFileT
 * Return Type: [errno: Fixnum, stat: AprStatusT]
 */
mrb_value
mrb_APR_apr_file_info_get(mrb_state* mrb, mrb_value self) {
  mrb_int native_wanted;
  mrb_value thefile;

  /* Fetch the args */
  mrb_get_args(mrb, "io", &native_wanted, &thefile);

  /* Type checking */
  if (!mrb_obj_is_kind_of(mrb, thefile, AprFileT_class(mrb))) {
    mrb_raise(mrb, E_TYPE_ERROR, "AprFileT expected");
    return mrb_nil_value();
  }

  /* Unbox parameters */
  apr_file_t * native_thefile = (mrb_nil_p(thefile) ? NULL : mruby_unbox_apr_file_t(thefile));

  /* Invocation */
  apr_finfo_t * native_finfo = (apr_finfo_t*)malloc(sizeof(apr_finfo_t));
  apr_status_t result = apr_file_info_get(native_finfo, native_wanted, native_thefile);

  /* Box the return */
  mrb_value results = mrb_ary_new(mrb);
  mrb_ary_push(mrb, results, mrb_fixnum_value(result));
  if (result == APR_SUCCESS || result == APR_INCOMPLETE) {
    mrb_ary_push(mrb, results, mruby_giftwrap_apr_finfo_t(mrb, native_finfo));
  } else {
    mrb_ary_push(mrb, results, mrb_nil_value());
  }
  return results;
}
#endif
/* MRUBY_BINDING_END */

/* MRUBY_BINDING: apr_file_link */
/* sha: user_edited */
#if BIND_apr_file_link_FUNCTION
#define apr_file_link_REQUIRED_ARGC 2
#define apr_file_link_OPTIONAL_ARGC 0
/* apr_file_link
 *
 * Parameters:
 * - from_path: const char *
 * - to_path: const char *
 * Return Type: apr_status_t
 */
mrb_value
mrb_APR_apr_file_link(mrb_state* mrb, mrb_value self) {
  char * native_from_path;
  char * native_to_path;

  /* Fetch the args */
  mrb_get_args(mrb, "zz", &native_from_path, &native_to_path);

  /* Invocation */
  apr_status_t result = apr_file_link(native_from_path, native_to_path);

  /* Box the return value */
  if (result > MRB_INT_MAX) {
    mrb_raise(mrb, mrb->eStandardError_class, "MRuby cannot represent integers greater than MRB_INT_MAX");
    return mrb_nil_value();
  }
  mrb_value return_value = mrb_fixnum_value(result);

  return return_value;
}
#endif
/* MRUBY_BINDING_END */

/* MRUBY_BINDING: apr_file_lock */
/* sha: user_edited */
#if BIND_apr_file_lock_FUNCTION
#define apr_file_lock_REQUIRED_ARGC 2
#define apr_file_lock_OPTIONAL_ARGC 0
/* apr_file_lock
 *
 * Parameters:
 * - thefile: AprFileT
 * - type: Fixnum
 * Return Type: Fixnum (errno)
 */
mrb_value
mrb_APR_apr_file_lock(mrb_state* mrb, mrb_value self) {
  mrb_value thefile;
  mrb_int native_type;

  /* Fetch the args */
  mrb_get_args(mrb, "oi", &thefile, &native_type);

  /* Type checking */
  if (!mrb_obj_is_kind_of(mrb, thefile, AprFileT_class(mrb))) {
    mrb_raise(mrb, E_TYPE_ERROR, "AprFileT expected");
    return mrb_nil_value();
  }

  /* Unbox parameters */
  apr_file_t * native_thefile = (mrb_nil_p(thefile) ? NULL : mruby_unbox_apr_file_t(thefile));

  /* Invocation */
  apr_status_t result = apr_file_lock(native_thefile, native_type);

  /* Box the return value */
  if (result > MRB_INT_MAX) {
    mrb_raise(mrb, mrb->eStandardError_class, "MRuby cannot represent integers greater than MRB_INT_MAX");
    return mrb_nil_value();
  }
  mrb_value return_value = mrb_fixnum_value(result);

  return return_value;
}
#endif
/* MRUBY_BINDING_END */

/* MRUBY_BINDING: apr_file_mktemp */
/* sha: d697340f65a9c9d6d98cb6f466451d59c155f14a98c85392e580268ac5b9e55c */
#if BIND_apr_file_mktemp_FUNCTION
#define apr_file_mktemp_REQUIRED_ARGC 4
#define apr_file_mktemp_OPTIONAL_ARGC 0
/* apr_status_t apr_file_mktemp(apr_file_t ** fp, char * templ, apr_int32_t flags, apr_pool_t * p) */
mrb_value
mrb_APR_apr_file_mktemp(mrb_state* mrb, mrb_value self) {
  mrb_value fp;
  mrb_value templ;
  mrb_int native_flags;
  mrb_value p;

  /* Fetch the args */
  mrb_get_args(mrb, "ooio", &fp, &templ, &native_flags, &p);

  /* Type checking */
  TODO_type_check_apr_file_t_PTR_PTR(fp);
  TODO_type_check_char_PTR(templ);
  if (!mrb_obj_is_kind_of(mrb, p, AprPoolT_class(mrb))) {
    mrb_raise(mrb, E_TYPE_ERROR, "AprPoolT expected");
    return mrb_nil_value();
  }

  /* Unbox param: fp */
  apr_file_t ** native_fp = TODO_mruby_unbox_apr_file_t_PTR_PTR(fp);

  /* Unbox param: templ */
  char * native_templ = TODO_mruby_unbox_char_PTR(templ);

  /* Unbox param: p */
  apr_pool_t * native_p = (mrb_nil_p(p) ? NULL : mruby_unbox_apr_pool_t(p));

  /* Invocation */
  apr_status_t native_return_value = apr_file_mktemp(native_fp, native_templ, native_flags, native_p);

  /* Box the return value */
  mrb_value return_value = mrb_fixnum_value(native_return_value);
  
  return return_value;
}
#endif
/* MRUBY_BINDING_END */

/* MRUBY_BINDING: apr_file_mtime_set */
/* sha: abeb5962e1bbb6ad1497a261ed70798798d42392cdbe74611c67d5814c01d7d1 */
#if BIND_apr_file_mtime_set_FUNCTION
#define apr_file_mtime_set_REQUIRED_ARGC 3
#define apr_file_mtime_set_OPTIONAL_ARGC 0
/* apr_status_t apr_file_mtime_set(const char * fname, apr_time_t mtime, apr_pool_t * pool) */
mrb_value
mrb_APR_apr_file_mtime_set(mrb_state* mrb, mrb_value self) {
  char * native_fname = NULL;
  mrb_int native_mtime;
  mrb_value pool;

  /* Fetch the args */
  mrb_get_args(mrb, "zio", &native_fname, &native_mtime, &pool);

  /* Type checking */
  if (!mrb_obj_is_kind_of(mrb, pool, AprPoolT_class(mrb))) {
    mrb_raise(mrb, E_TYPE_ERROR, "AprPoolT expected");
    return mrb_nil_value();
  }

  /* Unbox param: pool */
  apr_pool_t * native_pool = (mrb_nil_p(pool) ? NULL : mruby_unbox_apr_pool_t(pool));

  /* Invocation */
  apr_status_t native_return_value = apr_file_mtime_set(native_fname, native_mtime, native_pool);

  /* Box the return value */
  mrb_value return_value = mrb_fixnum_value(native_return_value);
  
  return return_value;
}
#endif
/* MRUBY_BINDING_END */

/* MRUBY_BINDING: apr_file_name_get */
/* sha: 05d0e7d684338451046df3ab09ee81d96027aecdf87e9d91ecf67b4812550cd2 */
#if BIND_apr_file_name_get_FUNCTION
#define apr_file_name_get_REQUIRED_ARGC 2
#define apr_file_name_get_OPTIONAL_ARGC 0
/* apr_status_t apr_file_name_get(const char ** new_path, apr_file_t * thefile) */
mrb_value
mrb_APR_apr_file_name_get(mrb_state* mrb, mrb_value self) {
  mrb_value new_path;
  mrb_value thefile;

  /* Fetch the args */
  mrb_get_args(mrb, "oo", &new_path, &thefile);

  /* Type checking */
  TODO_type_check_char_PTR_PTR(new_path);
  if (!mrb_obj_is_kind_of(mrb, thefile, AprFileT_class(mrb))) {
    mrb_raise(mrb, E_TYPE_ERROR, "AprFileT expected");
    return mrb_nil_value();
  }

  /* Unbox param: new_path */
  const char ** native_new_path = TODO_mruby_unbox_char_PTR_PTR(new_path);

  /* Unbox param: thefile */
  apr_file_t * native_thefile = (mrb_nil_p(thefile) ? NULL : mruby_unbox_apr_file_t(thefile));

  /* Invocation */
  apr_status_t native_return_value = apr_file_name_get(native_new_path, native_thefile);

  /* Box the return value */
  mrb_value return_value = mrb_fixnum_value(native_return_value);
  
  return return_value;
}
#endif
/* MRUBY_BINDING_END */

/* MRUBY_BINDING: apr_file_namedpipe_create */
/* sha: user_edited */
#if BIND_apr_file_namedpipe_create_FUNCTION
#define apr_file_namedpipe_create_REQUIRED_ARGC 3
#define apr_file_namedpipe_create_OPTIONAL_ARGC 0
/* apr_file_namedpipe_create
 *
 * Parameters:
 * - filename: String
 * - perm: Fixnum
 * - pool: AprPoolT
 * Return Type: Fixnum (errno)
 */
mrb_value
mrb_APR_apr_file_namedpipe_create(mrb_state* mrb, mrb_value self) {
  char * native_filename;
  mrb_int native_perm;
  mrb_value pool;

  /* Fetch the args */
  mrb_get_args(mrb, "zio", &native_filename, &native_perm, &pool);

  /* Type checking */
  if (!mrb_obj_is_kind_of(mrb, pool, AprPoolT_class(mrb))) {
    mrb_raise(mrb, E_TYPE_ERROR, "AprPoolT expected");
    return mrb_nil_value();
  }

  /* Unbox parameters */

  apr_pool_t * native_pool = (mrb_nil_p(pool) ? NULL : mruby_unbox_apr_pool_t(pool));

  /* Invocation */
  apr_status_t result = apr_file_namedpipe_create(native_filename, native_perm, native_pool);

  /* Box the return value */
  if (result > MRB_INT_MAX) {
    mrb_raise(mrb, mrb->eStandardError_class, "MRuby cannot represent integers greater than MRB_INT_MAX");
    return mrb_nil_value();
  }
  mrb_value return_value = mrb_fixnum_value(result);

  return return_value;
}
#endif
/* MRUBY_BINDING_END */

/* MRUBY_BINDING: apr_file_open */
/* sha: user_edited */
#if BIND_apr_file_open_FUNCTION
#define apr_file_open_REQUIRED_ARGC 4
#define apr_file_open_OPTIONAL_ARGC 0
/* apr_file_open
 *
 * Parameters:
 * - fname: const char *
 * - flag: int
 * - perm: int
 * - pool: apr_pool_t *
 * Return Type: [apr_status_t, apr_file_t]
 */
mrb_value
mrb_APR_apr_file_open(mrb_state* mrb, mrb_value self) {
  const char* native_fname;
  mrb_int native_flag;
  mrb_int native_perm;
  mrb_value pool;

  /* Fetch the args */
  mrb_get_args(mrb, "ziio", &native_fname, &native_flag, &native_perm, &pool);

  /* Type checking */
  if (!mrb_obj_is_kind_of(mrb, pool, AprPoolT_class(mrb))) {
    mrb_raise(mrb, E_TYPE_ERROR, "AprPoolT expected");
    return mrb_nil_value();
  }

  /* Unbox parameters */

  apr_pool_t * native_pool = (mrb_nil_p(pool) ? NULL : mruby_unbox_apr_pool_t(pool));

  /* Invocation */
  apr_file_t * native_newf;
  apr_status_t result = apr_file_open(&native_newf, native_fname, native_flag, native_perm, native_pool);

  /* Box the return value */
  if (result > MRB_INT_MAX) {
    mrb_raise(mrb, mrb->eStandardError_class, "MRuby cannot represent integers greater than MRB_INT_MAX");
    return mrb_nil_value();
  }
  mrb_value return_value = mrb_fixnum_value(result);

  mrb_value results = mrb_ary_new(mrb);
  mrb_ary_push(mrb, results, return_value);
  if (result == 0) {
     mrb_ary_push(mrb, results, mruby_box_apr_file_t(mrb, native_newf));
  }
  else {
     mrb_ary_push(mrb, results, mrb_nil_value());
  }

  return results;
}
#endif
/* MRUBY_BINDING_END */

/* MRUBY_BINDING: apr_file_open_flags_stderr */
/* sha: user_edited */
#if BIND_apr_file_open_flags_stderr_FUNCTION
#define apr_file_open_flags_stderr_REQUIRED_ARGC 2
#define apr_file_open_flags_stderr_OPTIONAL_ARGC 0
/* apr_file_open_flags_stderr
 *
 * Parameters:
 * - flags: int
 * - pool: apr_pool_t *
 * Return Type: apr_status_t
 */
mrb_value
mrb_APR_apr_file_open_flags_stderr(mrb_state* mrb, mrb_value self) {
  mrb_int native_flags;
  mrb_value pool;

  /* Fetch the args */
  mrb_get_args(mrb, "io", &native_flags, &pool);

  /* Type checking */
  if (!mrb_obj_is_kind_of(mrb, pool, AprPoolT_class(mrb))) {
    mrb_raise(mrb, E_TYPE_ERROR, "AprPoolT expected");
    return mrb_nil_value();
  }

  /* Unbox parameters */

  apr_pool_t * native_pool = (mrb_nil_p(pool) ? NULL : mruby_unbox_apr_pool_t(pool));

  /* Invocation */
  apr_file_t * native_thefile;
  apr_status_t result = apr_file_open_flags_stderr(&native_thefile, native_flags, native_pool);

  /* Box the return value */
  RETURN_ERRNO_AND_OUTPUT(result, mruby_box_apr_file_t(mrb, native_thefile));
}
#endif
/* MRUBY_BINDING_END */

/* MRUBY_BINDING: apr_file_open_flags_stdin */
/* sha: user_edited */
#if BIND_apr_file_open_flags_stdin_FUNCTION
#define apr_file_open_flags_stdin_REQUIRED_ARGC 2
#define apr_file_open_flags_stdin_OPTIONAL_ARGC 0
/* apr_file_open_flags_stderr
 *
 * Parameters:
 * - flags: int
 * - pool: apr_pool_t *
 * Return Type: apr_status_t
 */
mrb_value
mrb_APR_apr_file_open_flags_stdin(mrb_state* mrb, mrb_value self) {
  mrb_int native_flags;
  mrb_value pool;

  /* Fetch the args */
  mrb_get_args(mrb, "io", &native_flags, &pool);

  /* Type checking */
  if (!mrb_obj_is_kind_of(mrb, pool, AprPoolT_class(mrb))) {
    mrb_raise(mrb, E_TYPE_ERROR, "AprPoolT expected");
    return mrb_nil_value();
  }

  /* Unbox parameters */

  apr_pool_t * native_pool = (mrb_nil_p(pool) ? NULL : mruby_unbox_apr_pool_t(pool));

  /* Invocation */
  apr_file_t * native_thefile;
  apr_status_t result = apr_file_open_flags_stdin(&native_thefile, native_flags, native_pool);

  /* Box the return value */
  RETURN_ERRNO_AND_OUTPUT(result, mruby_box_apr_file_t(mrb, native_thefile));
}
#endif
/* MRUBY_BINDING_END */

/* MRUBY_BINDING: apr_file_open_flags_stdout */
/* sha: user_edited */
#if BIND_apr_file_open_flags_stdout_FUNCTION
#define apr_file_open_flags_stdout_REQUIRED_ARGC 2
#define apr_file_open_flags_stdout_OPTIONAL_ARGC 0
/* apr_file_open_flags_stderr
 *
 * Parameters:
 * - flags: int
 * - pool: apr_pool_t *
 * Return Type: apr_status_t
 */
mrb_value
mrb_APR_apr_file_open_flags_stdout(mrb_state* mrb, mrb_value self) {
  mrb_int native_flags;
  mrb_value pool;

  /* Fetch the args */
  mrb_get_args(mrb, "io", &native_flags, &pool);

  /* Type checking */
  if (!mrb_obj_is_kind_of(mrb, pool, AprPoolT_class(mrb))) {
    mrb_raise(mrb, E_TYPE_ERROR, "AprPoolT expected");
    return mrb_nil_value();
  }

  /* Unbox parameters */

  apr_pool_t * native_pool = (mrb_nil_p(pool) ? NULL : mruby_unbox_apr_pool_t(pool));

  /* Invocation */
  apr_file_t * native_thefile;
  apr_status_t result = apr_file_open_flags_stdout(&native_thefile, native_flags, native_pool);

  /* Box the return value */
  RETURN_ERRNO_AND_OUTPUT(result, mruby_box_apr_file_t(mrb, native_thefile));
}
#endif
/* MRUBY_BINDING_END */

/* MRUBY_BINDING: apr_file_open_stderr */
/* sha: user_edited */
#if BIND_apr_file_open_stderr_FUNCTION
#define apr_file_open_stderr_REQUIRED_ARGC 1
#define apr_file_open_stderr_OPTIONAL_ARGC 0
/* apr_file_open_stderr
 *
 * Parameters:
 * - pool: apr_pool_t *
 * Return Type: apr_status_t
 */
mrb_value
mrb_APR_apr_file_open_stderr(mrb_state* mrb, mrb_value self) {
  mrb_value pool;

  /* Fetch the args */
  mrb_get_args(mrb, "o", &pool);

  /* Type checking */
  if (!mrb_obj_is_kind_of(mrb, pool, AprPoolT_class(mrb))) {
    mrb_raise(mrb, E_TYPE_ERROR, "AprPoolT expected");
    return mrb_nil_value();
  }

  /* Unbox parameters */
  apr_pool_t * native_pool = (mrb_nil_p(pool) ? NULL : mruby_unbox_apr_pool_t(pool));

  /* Invocation */
  apr_file_t * native_thefile;
  apr_status_t result = apr_file_open_stderr(&native_thefile, native_pool);

  /* Box the return value */
  if (result > MRB_INT_MAX) {
    mrb_raise(mrb, mrb->eStandardError_class, "MRuby cannot represent integers greater than MRB_INT_MAX");
    return mrb_nil_value();
  }
  mrb_value return_value = mrb_fixnum_value(result);

  mrb_value results = mrb_ary_new(mrb);
  mrb_ary_push(mrb, results, return_value);
  if (result == 0) {
     mrb_ary_push(mrb, results, mruby_box_apr_file_t(mrb, native_thefile));
  }
  else {
     mrb_ary_push(mrb, results, mrb_nil_value());
  }

  return results;
}
#endif
/* MRUBY_BINDING_END */

/* MRUBY_BINDING: apr_file_open_stdin */
/* sha: user_edited */
#if BIND_apr_file_open_stdin_FUNCTION
#define apr_file_open_stdin_REQUIRED_ARGC 1
#define apr_file_open_stdin_OPTIONAL_ARGC 0
/* apr_file_open_stdin
 *
 * Parameters:
 * - thefile: apr_file_t **
 * - pool: apr_pool_t *
 * Return Type: apr_status_t
 */
mrb_value
mrb_APR_apr_file_open_stdin(mrb_state* mrb, mrb_value self) {
  mrb_value pool;

  /* Fetch the args */
  mrb_get_args(mrb, "o", &pool);

  /* Type checking */
  if (!mrb_obj_is_kind_of(mrb, pool, AprPoolT_class(mrb))) {
    mrb_raise(mrb, E_TYPE_ERROR, "AprPoolT expected");
    return mrb_nil_value();
  }

  /* Unbox parameters */
  apr_pool_t * native_pool = (mrb_nil_p(pool) ? NULL : mruby_unbox_apr_pool_t(pool));

  /* Invocation */
  apr_file_t * native_thefile;
  apr_status_t result = apr_file_open_stdin(&native_thefile, native_pool);

  /* Box the return value */
  if (result > MRB_INT_MAX) {
     mrb_raise(mrb, mrb->eStandardError_class, "MRuby cannot represent integers greater than MRB_INT_MAX");
     return mrb_nil_value();
  }
  mrb_value return_value = mrb_fixnum_value(result);

  mrb_value results = mrb_ary_new(mrb);
  mrb_ary_push(mrb, results, return_value);
  if (result == 0) {
     mrb_ary_push(mrb, results, mruby_box_apr_file_t(mrb, native_thefile));
  }
  else {
     mrb_ary_push(mrb, results, mrb_nil_value());
  }

  return results;
}
#endif
/* MRUBY_BINDING_END */

/* MRUBY_BINDING: apr_file_open_stdout */
/* sha: user_edited */
#if BIND_apr_file_open_stdout_FUNCTION
#define apr_file_open_stdout_REQUIRED_ARGC 1
#define apr_file_open_stdout_OPTIONAL_ARGC 0
/* apr_file_open_stdout
 *
 * Parameters:
 * - thefile: apr_file_t **
 * - pool: apr_pool_t *
 * Return Type: apr_status_t
 */
mrb_value
mrb_APR_apr_file_open_stdout(mrb_state* mrb, mrb_value self) {
   mrb_value pool;

   /* Fetch the args */
   mrb_get_args(mrb, "o", &pool);

   /* Type checking */
   if (!mrb_obj_is_kind_of(mrb, pool, AprPoolT_class(mrb))) {
      mrb_raise(mrb, E_TYPE_ERROR, "AprPoolT expected");
      return mrb_nil_value();
   }

   /* Unbox parameters */
   apr_pool_t * native_pool = (mrb_nil_p(pool) ? NULL : mruby_unbox_apr_pool_t(pool));

   /* Invocation */
   apr_file_t * native_thefile;
   apr_status_t result = apr_file_open_stdout(&native_thefile, native_pool);

   /* Box the return value */
   if (result > MRB_INT_MAX) {
      mrb_raise(mrb, mrb->eStandardError_class, "MRuby cannot represent integers greater than MRB_INT_MAX");
      return mrb_nil_value();
   }
   mrb_value return_value = mrb_fixnum_value(result);

   mrb_value results = mrb_ary_new(mrb);
   mrb_ary_push(mrb, results, return_value);
   if (result == 0) {
      mrb_ary_push(mrb, results, mruby_box_apr_file_t(mrb, native_thefile));
   }
   else {
      mrb_ary_push(mrb, results, mrb_nil_value());
   }

   return results;
}
#endif
/* MRUBY_BINDING_END */

/* MRUBY_BINDING: apr_file_perms_set */
/* sha: user_edited */
#if BIND_apr_file_perms_set_FUNCTION
#define apr_file_perms_set_REQUIRED_ARGC 2
#define apr_file_perms_set_OPTIONAL_ARGC 0
/* apr_file_perms_set
 *
 * Parameters:
 * - fname: const char *
 * - perms: int
 * Return Type: apr_status_t
 */
mrb_value
mrb_APR_apr_file_perms_set(mrb_state* mrb, mrb_value self) {
  char * native_fname;
  mrb_int native_perms;

  /* Fetch the args */
  mrb_get_args(mrb, "zi", &native_fname, &native_perms);

  /* Invocation */
  apr_status_t result = apr_file_perms_set(native_fname, native_perms);

  /* Box the return value */
  if (result > MRB_INT_MAX) {
    mrb_raise(mrb, mrb->eStandardError_class, "MRuby cannot represent integers greater than MRB_INT_MAX");
    return mrb_nil_value();
  }
  mrb_value return_value = mrb_fixnum_value(result);

  return return_value;
}
#endif
/* MRUBY_BINDING_END */

/* MRUBY_BINDING: apr_file_pipe_create */
/* sha: user_edited */
#if BIND_apr_file_pipe_create_FUNCTION
#define apr_file_pipe_create_REQUIRED_ARGC 1
#define apr_file_pipe_create_OPTIONAL_ARGC 0
/* apr_file_pipe_create
 *
 * Parameters:
 * - pool: AprPoolT
 * Return Type: [errno: Fixnum, readEnd: AprFileT, writeEnd: AprFileT]
 */
mrb_value
mrb_APR_apr_file_pipe_create(mrb_state* mrb, mrb_value self) {
   mrb_value pool;

   /* Fetch the args */
   mrb_get_args(mrb, "o", &pool);

   /* Type checking */
   if (!mrb_obj_is_kind_of(mrb, pool, AprPoolT_class(mrb))) {
      mrb_raise(mrb, E_TYPE_ERROR, "AprPoolT expected");
      return mrb_nil_value();
   }

   /* Unbox parameters */
   apr_pool_t * native_pool = (mrb_nil_p(pool) ? NULL : mruby_unbox_apr_pool_t(pool));

   /* Invocation */
   apr_file_t * native_in;
   apr_file_t * native_out;
   apr_status_t result = apr_file_pipe_create(&native_in, &native_out, native_pool);

   /* Box the return value */
   if (result > MRB_INT_MAX) {
      mrb_raise(mrb, mrb->eStandardError_class, "MRuby cannot represent integers greater than MRB_INT_MAX");
      return mrb_nil_value();
   }
   mrb_value return_value = mrb_fixnum_value(result);

   mrb_value results = mrb_ary_new(mrb);
   mrb_ary_push(mrb, results, return_value);
   if (result == 0) {
      mrb_ary_push(mrb, results, mruby_box_apr_file_t(mrb, native_in));
      mrb_ary_push(mrb, results, mruby_box_apr_file_t(mrb, native_out));
   }
   else {
      mrb_ary_push(mrb, results, mrb_nil_value());
      mrb_ary_push(mrb, results, mrb_nil_value());
   }

  return results;
}
#endif
/* MRUBY_BINDING_END */

/* MRUBY_BINDING: apr_file_pipe_create_ex */
/* sha: 04af7a631ee45ca3733c1caf77050c7e0486965169c0d9262fcb0df1e324ec00 */
#if BIND_apr_file_pipe_create_ex_FUNCTION
#define apr_file_pipe_create_ex_REQUIRED_ARGC 4
#define apr_file_pipe_create_ex_OPTIONAL_ARGC 0
/* apr_status_t apr_file_pipe_create_ex(apr_file_t ** in, apr_file_t ** out, apr_int32_t blocking, apr_pool_t * pool) */
mrb_value
mrb_APR_apr_file_pipe_create_ex(mrb_state* mrb, mrb_value self) {
  mrb_value in;
  mrb_value out;
  mrb_int native_blocking;
  mrb_value pool;

  /* Fetch the args */
  mrb_get_args(mrb, "ooio", &in, &out, &native_blocking, &pool);

  /* Type checking */
  TODO_type_check_apr_file_t_PTR_PTR(in);
  TODO_type_check_apr_file_t_PTR_PTR(out);
  if (!mrb_obj_is_kind_of(mrb, pool, AprPoolT_class(mrb))) {
    mrb_raise(mrb, E_TYPE_ERROR, "AprPoolT expected");
    return mrb_nil_value();
  }

  /* Unbox param: in */
  apr_file_t ** native_in = TODO_mruby_unbox_apr_file_t_PTR_PTR(in);

  /* Unbox param: out */
  apr_file_t ** native_out = TODO_mruby_unbox_apr_file_t_PTR_PTR(out);

  /* Unbox param: pool */
  apr_pool_t * native_pool = (mrb_nil_p(pool) ? NULL : mruby_unbox_apr_pool_t(pool));

  /* Invocation */
  apr_status_t native_return_value = apr_file_pipe_create_ex(native_in, native_out, native_blocking, native_pool);

  /* Box the return value */
  mrb_value return_value = mrb_fixnum_value(native_return_value);
  
  return return_value;
}
#endif
/* MRUBY_BINDING_END */

/* MRUBY_BINDING: apr_file_pipe_timeout_get */
/* sha: b322ba6ee5917e0de178487b8ab522013786040e041ba4c80208471534e1b0ab */
#if BIND_apr_file_pipe_timeout_get_FUNCTION
#define apr_file_pipe_timeout_get_REQUIRED_ARGC 2
#define apr_file_pipe_timeout_get_OPTIONAL_ARGC 0
/* apr_status_t apr_file_pipe_timeout_get(apr_file_t * thepipe, apr_interval_time_t * timeout) */
mrb_value
mrb_APR_apr_file_pipe_timeout_get(mrb_state* mrb, mrb_value self) {
  mrb_value thepipe;
  mrb_value timeout;

  /* Fetch the args */
  mrb_get_args(mrb, "oo", &thepipe, &timeout);

  /* Type checking */
  if (!mrb_obj_is_kind_of(mrb, thepipe, AprFileT_class(mrb))) {
    mrb_raise(mrb, E_TYPE_ERROR, "AprFileT expected");
    return mrb_nil_value();
  }
  TODO_type_check_apr_interval_time_t_PTR(timeout);

  /* Unbox param: thepipe */
  apr_file_t * native_thepipe = (mrb_nil_p(thepipe) ? NULL : mruby_unbox_apr_file_t(thepipe));

  /* Unbox param: timeout */
  apr_interval_time_t * native_timeout = TODO_mruby_unbox_apr_interval_time_t_PTR(timeout);

  /* Invocation */
  apr_status_t native_return_value = apr_file_pipe_timeout_get(native_thepipe, native_timeout);

  /* Box the return value */
  mrb_value return_value = mrb_fixnum_value(native_return_value);
  
  return return_value;
}
#endif
/* MRUBY_BINDING_END */

/* MRUBY_BINDING: apr_file_pipe_timeout_set */
/* sha: ecec52e66bd648b8ad50a41db16b068d658b28d107941ab6bc67d4c8b2d6e51d */
#if BIND_apr_file_pipe_timeout_set_FUNCTION
#define apr_file_pipe_timeout_set_REQUIRED_ARGC 2
#define apr_file_pipe_timeout_set_OPTIONAL_ARGC 0
/* apr_status_t apr_file_pipe_timeout_set(apr_file_t * thepipe, apr_interval_time_t timeout) */
mrb_value
mrb_APR_apr_file_pipe_timeout_set(mrb_state* mrb, mrb_value self) {
  mrb_value thepipe;
  mrb_value timeout;

  /* Fetch the args */
  mrb_get_args(mrb, "oo", &thepipe, &timeout);

  /* Type checking */
  if (!mrb_obj_is_kind_of(mrb, thepipe, AprFileT_class(mrb))) {
    mrb_raise(mrb, E_TYPE_ERROR, "AprFileT expected");
    return mrb_nil_value();
  }
  TODO_type_check_apr_interval_time_t(timeout);

  /* Unbox param: thepipe */
  apr_file_t * native_thepipe = (mrb_nil_p(thepipe) ? NULL : mruby_unbox_apr_file_t(thepipe));

  /* Unbox param: timeout */
  apr_interval_time_t native_timeout = TODO_mruby_unbox_apr_interval_time_t(timeout);

  /* Invocation */
  apr_status_t native_return_value = apr_file_pipe_timeout_set(native_thepipe, native_timeout);

  /* Box the return value */
  mrb_value return_value = mrb_fixnum_value(native_return_value);
  
  return return_value;
}
#endif
/* MRUBY_BINDING_END */

/* MRUBY_BINDING: apr_file_printf */
/* sha: 0b9b90b2136e4a6d3621ff334945a5a924d52d903618ee4b19d8b69c3b14b2db */
#if BIND_apr_file_printf_FUNCTION
#define apr_file_printf_REQUIRED_ARGC 2
#define apr_file_printf_OPTIONAL_ARGC 0
/* int apr_file_printf(apr_file_t * fptr, const char * format) */
mrb_value
mrb_APR_apr_file_printf(mrb_state* mrb, mrb_value self) {
  mrb_value fptr;
  char * native_format = NULL;

  /* Fetch the args */
  mrb_get_args(mrb, "oz", &fptr, &native_format);

  /* Type checking */
  if (!mrb_obj_is_kind_of(mrb, fptr, AprFileT_class(mrb))) {
    mrb_raise(mrb, E_TYPE_ERROR, "AprFileT expected");
    return mrb_nil_value();
  }

  /* Unbox param: fptr */
  apr_file_t * native_fptr = (mrb_nil_p(fptr) ? NULL : mruby_unbox_apr_file_t(fptr));

  /* Invocation */
  int native_return_value = apr_file_printf(native_fptr, native_format);

  /* Box the return value */
  mrb_value return_value = mrb_fixnum_value(native_return_value);
  
  return return_value;
}
#endif
/* MRUBY_BINDING_END */

/* MRUBY_BINDING: apr_file_putc */
/* sha: a37a85e0c2314aac2fd8a4e66aa3e6bb26f3b3dbfda754e94299701e0b01f9e6 */
#if BIND_apr_file_putc_FUNCTION
#define apr_file_putc_REQUIRED_ARGC 2
#define apr_file_putc_OPTIONAL_ARGC 0
/* apr_status_t apr_file_putc(char ch, apr_file_t * thefile) */
mrb_value
mrb_APR_apr_file_putc(mrb_state* mrb, mrb_value self) {
  mrb_int native_ch;
  mrb_value thefile;

  /* Fetch the args */
  mrb_get_args(mrb, "io", &native_ch, &thefile);

  /* Type checking */
  if (!mrb_obj_is_kind_of(mrb, thefile, AprFileT_class(mrb))) {
    mrb_raise(mrb, E_TYPE_ERROR, "AprFileT expected");
    return mrb_nil_value();
  }

  /* Unbox param: thefile */
  apr_file_t * native_thefile = (mrb_nil_p(thefile) ? NULL : mruby_unbox_apr_file_t(thefile));

  /* Invocation */
  apr_status_t native_return_value = apr_file_putc(native_ch, native_thefile);

  /* Box the return value */
  mrb_value return_value = mrb_fixnum_value(native_return_value);
  
  return return_value;
}
#endif
/* MRUBY_BINDING_END */

/* MRUBY_BINDING: apr_file_puts */
/* sha: user_edited */
#if BIND_apr_file_puts_FUNCTION
#define apr_file_puts_REQUIRED_ARGC 2
#define apr_file_puts_OPTIONAL_ARGC 0
/* apr_file_puts
 *
 * Parameters:
 * - str: const char *
 * - thefile: apr_file_t *
 * Return Type: apr_status_t
 */
mrb_value
mrb_APR_apr_file_puts(mrb_state* mrb, mrb_value self) {
  char * native_str;
  mrb_value thefile;

  /* Fetch the args */
  mrb_get_args(mrb, "zo", &native_str, &thefile);

  /* Type checking */
  if (!mrb_obj_is_kind_of(mrb, thefile, AprFileT_class(mrb))) {
    mrb_raise(mrb, E_TYPE_ERROR, "AprFileT expected");
    return mrb_nil_value();
  }

  /* Unbox parameters */

  apr_file_t * native_thefile = (mrb_nil_p(thefile) ? NULL : mruby_unbox_apr_file_t(thefile));

  /* Invocation */
  apr_status_t result = apr_file_puts(native_str, native_thefile);

  /* Box the return value */
  if (result > MRB_INT_MAX) {
    mrb_raise(mrb, mrb->eStandardError_class, "MRuby cannot represent integers greater than MRB_INT_MAX");
    return mrb_nil_value();
  }
  mrb_value return_value = mrb_fixnum_value(result);

  return return_value;
}
#endif
/* MRUBY_BINDING_END */

/* MRUBY_BINDING: apr_file_read */
/* sha: user_edited */
#if BIND_apr_file_read_FUNCTION
#define apr_file_read_REQUIRED_ARGC 2
#define apr_file_read_OPTIONAL_ARGC 0
/* apr_file_read
 *
 * Parameters:
 * - thefile: AprFileT
 * - nbytes: Fixnum
 * Return Type: [int, String] (error & string of bytes read)
 */
mrb_value
mrb_APR_apr_file_read(mrb_state* mrb, mrb_value self) {
  mrb_value thefile;
  mrb_int native_nbytes;

  /* Fetch the args */
  mrb_get_args(mrb, "oi", &thefile, &native_nbytes);

  /* Type checking */
  if (!mrb_obj_is_kind_of(mrb, thefile, AprFileT_class(mrb))) {
    mrb_raise(mrb, E_TYPE_ERROR, "AprFileT expected");
    return mrb_nil_value();
  }

  /* Unbox parameters */
  apr_file_t * native_thefile = (mrb_nil_p(thefile) ? NULL : mruby_unbox_apr_file_t(thefile));

  /* Invocation */
  char * native_buf = (char*)malloc(native_nbytes); /* No null terminator will be appended */
  apr_size_t size = native_nbytes;
  apr_status_t result = apr_file_read(native_thefile, native_buf, &size);

  /* Box the return value */
  if (result > MRB_INT_MAX) {
    mrb_raise(mrb, mrb->eStandardError_class, "MRuby cannot represent integers greater than MRB_INT_MAX");
    return mrb_nil_value();
  }
  mrb_value return_value = mrb_fixnum_value(result);

  mrb_value ruby_buf = mrb_str_new(mrb, native_buf, size);
  free(native_buf);
  native_buf = NULL;

  mrb_value results = mrb_ary_new(mrb);
  mrb_ary_push(mrb, results, return_value);
  mrb_ary_push(mrb, results, ruby_buf);

  return results;
}
#endif
/* MRUBY_BINDING_END */

/* MRUBY_BINDING: apr_file_read_full */
/* sha: 0d4cdbd478015cb54e97f5f7e3c3de51217b0c1b9cca89747927ed749626784d */
#if BIND_apr_file_read_full_FUNCTION
#define apr_file_read_full_REQUIRED_ARGC 4
#define apr_file_read_full_OPTIONAL_ARGC 0
/* apr_status_t apr_file_read_full(apr_file_t * thefile, void * buf, apr_size_t nbytes, apr_size_t * bytes_read) */
mrb_value
mrb_APR_apr_file_read_full(mrb_state* mrb, mrb_value self) {
  mrb_value thefile;
  mrb_value buf;
  mrb_int native_nbytes;
  mrb_value bytes_read;

  /* Fetch the args */
  mrb_get_args(mrb, "ooio", &thefile, &buf, &native_nbytes, &bytes_read);

  /* Type checking */
  if (!mrb_obj_is_kind_of(mrb, thefile, AprFileT_class(mrb))) {
    mrb_raise(mrb, E_TYPE_ERROR, "AprFileT expected");
    return mrb_nil_value();
  }
  TODO_type_check_void_PTR(buf);
  TODO_type_check_apr_size_t_PTR(bytes_read);

  /* Unbox param: thefile */
  apr_file_t * native_thefile = (mrb_nil_p(thefile) ? NULL : mruby_unbox_apr_file_t(thefile));

  /* Unbox param: buf */
  void * native_buf = TODO_mruby_unbox_void_PTR(buf);

  /* Unbox param: bytes_read */
  apr_size_t * native_bytes_read = TODO_mruby_unbox_apr_size_t_PTR(bytes_read);

  /* Invocation */
  apr_status_t native_return_value = apr_file_read_full(native_thefile, native_buf, native_nbytes, native_bytes_read);

  /* Box the return value */
  mrb_value return_value = mrb_fixnum_value(native_return_value);
  
  return return_value;
}
#endif
/* MRUBY_BINDING_END */

/* MRUBY_BINDING: apr_file_remove */
/* sha: user_edited */
#if BIND_apr_file_remove_FUNCTION
#define apr_file_remove_REQUIRED_ARGC 2
#define apr_file_remove_OPTIONAL_ARGC 0
/* apr_file_remove
 *
 * Parameters:
 * - path: String
 * - pool: AprPoolT
 * Return Type: Fixnum (errno)
 */
mrb_value
mrb_APR_apr_file_remove(mrb_state* mrb, mrb_value self) {
  char * native_path;
  mrb_value pool;

  /* Fetch the args */
  mrb_get_args(mrb, "zo", &native_path, &pool);

  /* Type checking */
  if (!mrb_obj_is_kind_of(mrb, pool, AprPoolT_class(mrb))) {
    mrb_raise(mrb, E_TYPE_ERROR, "AprPoolT expected");
    return mrb_nil_value();
  }

  /* Unbox parameters */

  apr_pool_t * native_pool = (mrb_nil_p(pool) ? NULL : mruby_unbox_apr_pool_t(pool));

  /* Invocation */
  apr_status_t result = apr_file_remove(native_path, native_pool);

  /* Box the return value */
  if (result > MRB_INT_MAX) {
    mrb_raise(mrb, mrb->eStandardError_class, "MRuby cannot represent integers greater than MRB_INT_MAX");
    return mrb_nil_value();
  }
  mrb_value return_value = mrb_fixnum_value(result);

  return return_value;
}
#endif
/* MRUBY_BINDING_END */

/* MRUBY_BINDING: apr_file_rename */
/* sha: user_edited */
#if BIND_apr_file_rename_FUNCTION
#define apr_file_rename_REQUIRED_ARGC 3
#define apr_file_rename_OPTIONAL_ARGC 0
/* apr_file_rename
 *
 * Parameters:
 * - from_path: String
 * - to_path: String
 * - pool: AprPoolT
 * Return Type: Fixnum (errno)
 */
mrb_value
mrb_APR_apr_file_rename(mrb_state* mrb, mrb_value self) {
  char * native_from_path;
  char * native_to_path;
  mrb_value pool;

  /* Fetch the args */
  mrb_get_args(mrb, "zzo", &native_from_path, &native_to_path, &pool);

  /* Type checking */
  if (!mrb_obj_is_kind_of(mrb, pool, AprPoolT_class(mrb))) {
    mrb_raise(mrb, E_TYPE_ERROR, "AprPoolT expected");
    return mrb_nil_value();
  }

  /* Unbox parameters */

  apr_pool_t * native_pool = (mrb_nil_p(pool) ? NULL : mruby_unbox_apr_pool_t(pool));

  /* Invocation */
  apr_status_t result = apr_file_rename(native_from_path, native_to_path, native_pool);

  /* Box the return value */
  if (result > MRB_INT_MAX) {
    mrb_raise(mrb, mrb->eStandardError_class, "MRuby cannot represent integers greater than MRB_INT_MAX");
    return mrb_nil_value();
  }
  mrb_value return_value = mrb_fixnum_value(result);

  return return_value;
}
#endif
/* MRUBY_BINDING_END */

/* MRUBY_BINDING: apr_file_seek */
/* sha: user_edited */
#if BIND_apr_file_seek_FUNCTION
#define apr_file_seek_REQUIRED_ARGC 3
#define apr_file_seek_OPTIONAL_ARGC 0
/* apr_file_seek
 *
 * Parameters:
 * - thefile: AprFileT
 * - where: Fixnum
 * - offset: Fixnum
 * Return Type: [int, int] (errno & the actuall offset that resulted)
 */
mrb_value
mrb_APR_apr_file_seek(mrb_state* mrb, mrb_value self) {
  mrb_value thefile;
  mrb_int native_where;
  mrb_int native_offset;

  /* Fetch the args */
  mrb_get_args(mrb, "oii", &thefile, &native_where, &native_offset);

  /* Type checking */
  if (!mrb_obj_is_kind_of(mrb, thefile, AprFileT_class(mrb))) {
    mrb_raise(mrb, E_TYPE_ERROR, "AprFileT expected");
    return mrb_nil_value();
  }

  /* Unbox parameters */
  apr_file_t * native_thefile = (mrb_nil_p(thefile) ? NULL : mruby_unbox_apr_file_t(thefile));

  /* Invocation */
  apr_off_t offset = native_offset;
  apr_status_t result = apr_file_seek(native_thefile, native_where, &offset);

  /* Box the return value */
  if (result > MRB_INT_MAX) {
    mrb_raise(mrb, mrb->eStandardError_class, "MRuby cannot represent integers greater than MRB_INT_MAX");
    return mrb_nil_value();
  }
  mrb_value return_value = mrb_fixnum_value(result);

  mrb_value results = mrb_ary_new(mrb);
  mrb_ary_push(mrb, results, return_value);
  mrb_ary_push(mrb, results, mrb_fixnum_value(offset));

  return results;
}
#endif
/* MRUBY_BINDING_END */

/* MRUBY_BINDING: apr_file_setaside */
/* sha: 8ea061cff4ffe5c5ac3dcba633070c23c54439eb0a92204748f100d03c547544 */
#if BIND_apr_file_setaside_FUNCTION
#define apr_file_setaside_REQUIRED_ARGC 3
#define apr_file_setaside_OPTIONAL_ARGC 0
/* apr_status_t apr_file_setaside(apr_file_t ** new_file, apr_file_t * old_file, apr_pool_t * p) */
mrb_value
mrb_APR_apr_file_setaside(mrb_state* mrb, mrb_value self) {
  mrb_value new_file;
  mrb_value old_file;
  mrb_value p;

  /* Fetch the args */
  mrb_get_args(mrb, "ooo", &new_file, &old_file, &p);

  /* Type checking */
  TODO_type_check_apr_file_t_PTR_PTR(new_file);
  if (!mrb_obj_is_kind_of(mrb, old_file, AprFileT_class(mrb))) {
    mrb_raise(mrb, E_TYPE_ERROR, "AprFileT expected");
    return mrb_nil_value();
  }
  if (!mrb_obj_is_kind_of(mrb, p, AprPoolT_class(mrb))) {
    mrb_raise(mrb, E_TYPE_ERROR, "AprPoolT expected");
    return mrb_nil_value();
  }

  /* Unbox param: new_file */
  apr_file_t ** native_new_file = TODO_mruby_unbox_apr_file_t_PTR_PTR(new_file);

  /* Unbox param: old_file */
  apr_file_t * native_old_file = (mrb_nil_p(old_file) ? NULL : mruby_unbox_apr_file_t(old_file));

  /* Unbox param: p */
  apr_pool_t * native_p = (mrb_nil_p(p) ? NULL : mruby_unbox_apr_pool_t(p));

  /* Invocation */
  apr_status_t native_return_value = apr_file_setaside(native_new_file, native_old_file, native_p);

  /* Box the return value */
  mrb_value return_value = mrb_fixnum_value(native_return_value);
  
  return return_value;
}
#endif
/* MRUBY_BINDING_END */

/* MRUBY_BINDING: apr_file_sync */
/* sha: user_edited */
#if BIND_apr_file_sync_FUNCTION
#define apr_file_sync_REQUIRED_ARGC 1
#define apr_file_sync_OPTIONAL_ARGC 0
/* apr_file_sync
 *
 * Parameters:
 * - thefile: apr_file_t *
 * Return Type: apr_status_t
 */
mrb_value
mrb_APR_apr_file_sync(mrb_state* mrb, mrb_value self) {
  mrb_value thefile;

  /* Fetch the args */
  mrb_get_args(mrb, "o", &thefile);

  /* Type checking */
  if (!mrb_obj_is_kind_of(mrb, thefile, AprFileT_class(mrb))) {
    mrb_raise(mrb, E_TYPE_ERROR, "AprFileT expected");
    return mrb_nil_value();
  }

  /* Unbox parameters */
  apr_file_t * native_thefile = (mrb_nil_p(thefile) ? NULL : mruby_unbox_apr_file_t(thefile));

  /* Invocation */
  apr_status_t result = apr_file_sync(native_thefile);

  /* Box the return value */
  if (result > MRB_INT_MAX) {
    mrb_raise(mrb, mrb->eStandardError_class, "MRuby cannot represent integers greater than MRB_INT_MAX");
    return mrb_nil_value();
  }
  mrb_value return_value = mrb_fixnum_value(result);

  return return_value;
}
#endif
/* MRUBY_BINDING_END */

/* MRUBY_BINDING: apr_file_trunc */
/* sha: user_edited */
#if BIND_apr_file_trunc_FUNCTION
#define apr_file_trunc_REQUIRED_ARGC 2
#define apr_file_trunc_OPTIONAL_ARGC 0
/* apr_file_trunc
 *
 * Parameters:
 * - fp: apr_file_t *
 * - offset: long long
 * Return Type: apr_status_t
 */
mrb_value
mrb_APR_apr_file_trunc(mrb_state* mrb, mrb_value self) {
  mrb_value fp;
  mrb_int native_offset;

  /* Fetch the args */
  mrb_get_args(mrb, "oi", &fp, &native_offset);

  /* Type checking */
  if (!mrb_obj_is_kind_of(mrb, fp, AprFileT_class(mrb))) {
    mrb_raise(mrb, E_TYPE_ERROR, "AprFileT expected");
    return mrb_nil_value();
  }

  /* Unbox parameters */
  apr_file_t * native_fp = (mrb_nil_p(fp) ? NULL : mruby_unbox_apr_file_t(fp));

  /* Invocation */
  apr_status_t result = apr_file_trunc(native_fp, native_offset);

  /* Box the return value */
  if (result > MRB_INT_MAX) {
    mrb_raise(mrb, mrb->eStandardError_class, "MRuby cannot represent integers greater than MRB_INT_MAX");
    return mrb_nil_value();
  }
  mrb_value return_value = mrb_fixnum_value(result);

  return return_value;
}
#endif
/* MRUBY_BINDING_END */

/* MRUBY_BINDING: apr_file_ungetc */
/* sha: user_edited */
#if BIND_apr_file_ungetc_FUNCTION
#define apr_file_ungetc_REQUIRED_ARGC 2
#define apr_file_ungetc_OPTIONAL_ARGC 0
/* apr_file_ungetc
 *
 * Parameters:
 * - ch: char
 * - thefile: apr_file_t *
 * Return Type: apr_status_t
 */
mrb_value
mrb_APR_apr_file_ungetc(mrb_state* mrb, mrb_value self) {
  mrb_value ch;
  mrb_value thefile;

  /* Fetch the args */
  mrb_get_args(mrb, "oo", &ch, &thefile);

  /* Type checking */
  if (!mrb_obj_is_kind_of(mrb, ch, mrb->string_class)) {
    mrb_raise(mrb, E_TYPE_ERROR, "String expected");
    return mrb_nil_value();
  }
  if (!mrb_obj_is_kind_of(mrb, thefile, AprFileT_class(mrb))) {
    mrb_raise(mrb, E_TYPE_ERROR, "AprFileT expected");
    return mrb_nil_value();
  }

  /* Unbox parameters */
  char native_ch = mrb_string_value_ptr(mrb, ch)[0];
  apr_file_t * native_thefile = (mrb_nil_p(thefile) ? NULL : mruby_unbox_apr_file_t(thefile));

  /* Invocation */
  apr_status_t result = apr_file_ungetc(native_ch, native_thefile);

  /* Box the return value */
  mrb_value return_value = mrb_fixnum_value(result);

  return return_value;
}
#endif
/* MRUBY_BINDING_END */

/* MRUBY_BINDING: apr_file_unlock */
/* sha: user_edited */
#if BIND_apr_file_unlock_FUNCTION
#define apr_file_unlock_REQUIRED_ARGC 1
#define apr_file_unlock_OPTIONAL_ARGC 0
/* apr_file_unlock
 *
 * Parameters:
 * - thefile: AprFileT
 * Return Type: Fixnum (errno)
 */
mrb_value
mrb_APR_apr_file_unlock(mrb_state* mrb, mrb_value self) {
  mrb_value thefile;

  /* Fetch the args */
  mrb_get_args(mrb, "o", &thefile);

  /* Type checking */
  if (!mrb_obj_is_kind_of(mrb, thefile, AprFileT_class(mrb))) {
    mrb_raise(mrb, E_TYPE_ERROR, "AprFileT expected");
    return mrb_nil_value();
  }

  /* Unbox parameters */
  apr_file_t * native_thefile = (mrb_nil_p(thefile) ? NULL : mruby_unbox_apr_file_t(thefile));

  /* Invocation */
  apr_status_t result = apr_file_unlock(native_thefile);

  /* Box the return value */
  if (result > MRB_INT_MAX) {
    mrb_raise(mrb, mrb->eStandardError_class, "MRuby cannot represent integers greater than MRB_INT_MAX");
    return mrb_nil_value();
  }
  mrb_value return_value = mrb_fixnum_value(result);

  return return_value;
}
#endif
/* MRUBY_BINDING_END */

/* MRUBY_BINDING: apr_file_write */
/* sha: user_edited */
#if BIND_apr_file_write_FUNCTION
#define apr_file_write_REQUIRED_ARGC 3
#define apr_file_write_OPTIONAL_ARGC 0
/* apr_file_write
 *
 * Parameters:
 * - thefile: AprFileT
 * - buf: String
 * - nbytes: Fixnum
 * Return Type: [err, int] (error code & bytes written)
 */
mrb_value
mrb_APR_apr_file_write(mrb_state* mrb, mrb_value self) {
  mrb_value thefile;
  mrb_value buf;
  mrb_int native_nbytes;

  /* Fetch the args */
  mrb_get_args(mrb, "ooi", &thefile, &buf, &native_nbytes);

  /* Type checking */
  if (!mrb_obj_is_kind_of(mrb, thefile, AprFileT_class(mrb))) {
    mrb_raise(mrb, E_TYPE_ERROR, "AprFileT expected");
    return mrb_nil_value();
  }

  if (!mrb_obj_is_kind_of(mrb, buf, mrb->string_class)) {
     mrb_raise(mrb, E_TYPE_ERROR, "String expected");
     return mrb_nil_value();
  }

  /* Unbox parameters */
  apr_file_t * native_thefile = (mrb_nil_p(thefile) ? NULL : mruby_unbox_apr_file_t(thefile));
  /* Just writing, no need to copy */
  char * native_buf = RSTRING_PTR(buf);

  /* Invocation */
  apr_size_t size = native_nbytes;
  apr_status_t result = apr_file_write(native_thefile, native_buf, &size);

  /* Box the return value */
  if (result > MRB_INT_MAX) {
    mrb_raise(mrb, mrb->eStandardError_class, "MRuby cannot represent integers greater than MRB_INT_MAX");
    return mrb_nil_value();
  }
  mrb_value return_value = mrb_fixnum_value(result);

  mrb_value results = mrb_ary_new(mrb);
  mrb_ary_push(mrb, results, return_value);
  mrb_ary_push(mrb, results, mrb_fixnum_value(size));

  return results;
}
#endif
/* MRUBY_BINDING_END */

/* MRUBY_BINDING: apr_file_write_full */
/* sha: 2f2efb8c2dbe1ec45614ef1073a1ffc6a55b2400548fb5cc520ad96b5ce018a1 */
#if BIND_apr_file_write_full_FUNCTION
#define apr_file_write_full_REQUIRED_ARGC 4
#define apr_file_write_full_OPTIONAL_ARGC 0
/* apr_status_t apr_file_write_full(apr_file_t * thefile, const void * buf, apr_size_t nbytes, apr_size_t * bytes_written) */
mrb_value
mrb_APR_apr_file_write_full(mrb_state* mrb, mrb_value self) {
  mrb_value thefile;
  mrb_value buf;
  mrb_int native_nbytes;
  mrb_value bytes_written;

  /* Fetch the args */
  mrb_get_args(mrb, "ooio", &thefile, &buf, &native_nbytes, &bytes_written);

  /* Type checking */
  if (!mrb_obj_is_kind_of(mrb, thefile, AprFileT_class(mrb))) {
    mrb_raise(mrb, E_TYPE_ERROR, "AprFileT expected");
    return mrb_nil_value();
  }
  TODO_type_check_void_PTR(buf);
  TODO_type_check_apr_size_t_PTR(bytes_written);

  /* Unbox param: thefile */
  apr_file_t * native_thefile = (mrb_nil_p(thefile) ? NULL : mruby_unbox_apr_file_t(thefile));

  /* Unbox param: buf */
  const void * native_buf = TODO_mruby_unbox_void_PTR(buf);

  /* Unbox param: bytes_written */
  apr_size_t * native_bytes_written = TODO_mruby_unbox_apr_size_t_PTR(bytes_written);

  /* Invocation */
  apr_status_t native_return_value = apr_file_write_full(native_thefile, native_buf, native_nbytes, native_bytes_written);

  /* Box the return value */
  mrb_value return_value = mrb_fixnum_value(native_return_value);
  
  return return_value;
}
#endif
/* MRUBY_BINDING_END */

/* MRUBY_BINDING: apr_file_writev */
/* sha: 32b1b8e25a5eb12c76710ae2936a1249076750ccf3c3645c60092f21f547cfa8 */
#if BIND_apr_file_writev_FUNCTION
#define apr_file_writev_REQUIRED_ARGC 4
#define apr_file_writev_OPTIONAL_ARGC 0
/* apr_status_t apr_file_writev(apr_file_t * thefile, const struct iovec * vec, apr_size_t nvec, apr_size_t * nbytes) */
mrb_value
mrb_APR_apr_file_writev(mrb_state* mrb, mrb_value self) {
  mrb_value thefile;
  mrb_value vec;
  mrb_int native_nvec;
  mrb_value nbytes;

  /* Fetch the args */
  mrb_get_args(mrb, "ooio", &thefile, &vec, &native_nvec, &nbytes);

  /* Type checking */
  if (!mrb_obj_is_kind_of(mrb, thefile, AprFileT_class(mrb))) {
    mrb_raise(mrb, E_TYPE_ERROR, "AprFileT expected");
    return mrb_nil_value();
  }
  TODO_type_check_iovec_PTR(vec);
  TODO_type_check_apr_size_t_PTR(nbytes);

  /* Unbox param: thefile */
  apr_file_t * native_thefile = (mrb_nil_p(thefile) ? NULL : mruby_unbox_apr_file_t(thefile));

  /* Unbox param: vec */
  const struct iovec * native_vec = TODO_mruby_unbox_iovec_PTR(vec);

  /* Unbox param: nbytes */
  apr_size_t * native_nbytes = TODO_mruby_unbox_apr_size_t_PTR(nbytes);

  /* Invocation */
  apr_status_t native_return_value = apr_file_writev(native_thefile, native_vec, native_nvec, native_nbytes);

  /* Box the return value */
  mrb_value return_value = mrb_fixnum_value(native_return_value);
  
  return return_value;
}
#endif
/* MRUBY_BINDING_END */

/* MRUBY_BINDING: apr_file_writev_full */
/* sha: adfe3c187edbd87ef53331912c13ee0c1e690d30d444c6be0e2406d27319ad22 */
#if BIND_apr_file_writev_full_FUNCTION
#define apr_file_writev_full_REQUIRED_ARGC 4
#define apr_file_writev_full_OPTIONAL_ARGC 0
/* apr_status_t apr_file_writev_full(apr_file_t * thefile, const struct iovec * vec, apr_size_t nvec, apr_size_t * nbytes) */
mrb_value
mrb_APR_apr_file_writev_full(mrb_state* mrb, mrb_value self) {
  mrb_value thefile;
  mrb_value vec;
  mrb_int native_nvec;
  mrb_value nbytes;

  /* Fetch the args */
  mrb_get_args(mrb, "ooio", &thefile, &vec, &native_nvec, &nbytes);

  /* Type checking */
  if (!mrb_obj_is_kind_of(mrb, thefile, AprFileT_class(mrb))) {
    mrb_raise(mrb, E_TYPE_ERROR, "AprFileT expected");
    return mrb_nil_value();
  }
  TODO_type_check_iovec_PTR(vec);
  TODO_type_check_apr_size_t_PTR(nbytes);

  /* Unbox param: thefile */
  apr_file_t * native_thefile = (mrb_nil_p(thefile) ? NULL : mruby_unbox_apr_file_t(thefile));

  /* Unbox param: vec */
  const struct iovec * native_vec = TODO_mruby_unbox_iovec_PTR(vec);

  /* Unbox param: nbytes */
  apr_size_t * native_nbytes = TODO_mruby_unbox_apr_size_t_PTR(nbytes);

  /* Invocation */
  apr_status_t native_return_value = apr_file_writev_full(native_thefile, native_vec, native_nvec, native_nbytes);

  /* Box the return value */
  mrb_value return_value = mrb_fixnum_value(native_return_value);
  
  return return_value;
}
#endif
/* MRUBY_BINDING_END */

/* MRUBY_BINDING: apr_filepath_encoding */
/* sha: 656acc02862d402be2a375ec2908e2332c1d993247464681736ad2f1b9d4ebda */
#if BIND_apr_filepath_encoding_FUNCTION
#define apr_filepath_encoding_REQUIRED_ARGC 2
#define apr_filepath_encoding_OPTIONAL_ARGC 0
/* apr_status_t apr_filepath_encoding(int * style, apr_pool_t * p) */
mrb_value
mrb_APR_apr_filepath_encoding(mrb_state* mrb, mrb_value self) {
  mrb_value style;
  mrb_value p;

  /* Fetch the args */
  mrb_get_args(mrb, "oo", &style, &p);

  /* Type checking */
  TODO_type_check_int_PTR(style);
  if (!mrb_obj_is_kind_of(mrb, p, AprPoolT_class(mrb))) {
    mrb_raise(mrb, E_TYPE_ERROR, "AprPoolT expected");
    return mrb_nil_value();
  }

  /* Unbox param: style */
  int * native_style = TODO_mruby_unbox_int_PTR(style);

  /* Unbox param: p */
  apr_pool_t * native_p = (mrb_nil_p(p) ? NULL : mruby_unbox_apr_pool_t(p));

  /* Invocation */
  apr_status_t native_return_value = apr_filepath_encoding(native_style, native_p);

  /* Box the return value */
  mrb_value return_value = mrb_fixnum_value(native_return_value);
  
  return return_value;
}
#endif
/* MRUBY_BINDING_END */

/* MRUBY_BINDING: apr_filepath_get */
/* sha: b3e53af19d0835e12db5ff7e6d8746970e7aece6ded9dfda3138f32818000ea9 */
#if BIND_apr_filepath_get_FUNCTION
#define apr_filepath_get_REQUIRED_ARGC 3
#define apr_filepath_get_OPTIONAL_ARGC 0
/* apr_status_t apr_filepath_get(char ** path, apr_int32_t flags, apr_pool_t * p) */
mrb_value
mrb_APR_apr_filepath_get(mrb_state* mrb, mrb_value self) {
  mrb_value path;
  mrb_int native_flags;
  mrb_value p;

  /* Fetch the args */
  mrb_get_args(mrb, "oio", &path, &native_flags, &p);

  /* Type checking */
  TODO_type_check_char_PTR_PTR(path);
  if (!mrb_obj_is_kind_of(mrb, p, AprPoolT_class(mrb))) {
    mrb_raise(mrb, E_TYPE_ERROR, "AprPoolT expected");
    return mrb_nil_value();
  }

  /* Unbox param: path */
  char ** native_path = TODO_mruby_unbox_char_PTR_PTR(path);

  /* Unbox param: p */
  apr_pool_t * native_p = (mrb_nil_p(p) ? NULL : mruby_unbox_apr_pool_t(p));

  /* Invocation */
  apr_status_t native_return_value = apr_filepath_get(native_path, native_flags, native_p);

  /* Box the return value */
  mrb_value return_value = mrb_fixnum_value(native_return_value);
  
  return return_value;
}
#endif
/* MRUBY_BINDING_END */

/* MRUBY_BINDING: apr_filepath_list_merge */
/* sha: 96a823959f6bdc7cc0f9407e84e8cdb064c6c2fa0a6a1fbcf6402fc631c0fc7b */
#if BIND_apr_filepath_list_merge_FUNCTION
#define apr_filepath_list_merge_REQUIRED_ARGC 3
#define apr_filepath_list_merge_OPTIONAL_ARGC 0
/* apr_status_t apr_filepath_list_merge(char ** liststr, apr_array_header_t * pathelts, apr_pool_t * p) */
mrb_value
mrb_APR_apr_filepath_list_merge(mrb_state* mrb, mrb_value self) {
  mrb_value liststr;
  mrb_value pathelts;
  mrb_value p;

  /* Fetch the args */
  mrb_get_args(mrb, "ooo", &liststr, &pathelts, &p);

  /* Type checking */
  TODO_type_check_char_PTR_PTR(liststr);
  TODO_type_check_apr_array_header_t_PTR(pathelts);
  if (!mrb_obj_is_kind_of(mrb, p, AprPoolT_class(mrb))) {
    mrb_raise(mrb, E_TYPE_ERROR, "AprPoolT expected");
    return mrb_nil_value();
  }

  /* Unbox param: liststr */
  char ** native_liststr = TODO_mruby_unbox_char_PTR_PTR(liststr);

  /* Unbox param: pathelts */
  apr_array_header_t * native_pathelts = TODO_mruby_unbox_apr_array_header_t_PTR(pathelts);

  /* Unbox param: p */
  apr_pool_t * native_p = (mrb_nil_p(p) ? NULL : mruby_unbox_apr_pool_t(p));

  /* Invocation */
  apr_status_t native_return_value = apr_filepath_list_merge(native_liststr, native_pathelts, native_p);

  /* Box the return value */
  mrb_value return_value = mrb_fixnum_value(native_return_value);
  
  return return_value;
}
#endif
/* MRUBY_BINDING_END */

/* MRUBY_BINDING: apr_filepath_list_split */
/* sha: bccb6b76188a6b66a0e77e3ff80ce899438a1555c90269c88b16cd78ce669437 */
#if BIND_apr_filepath_list_split_FUNCTION
#define apr_filepath_list_split_REQUIRED_ARGC 3
#define apr_filepath_list_split_OPTIONAL_ARGC 0
/* apr_status_t apr_filepath_list_split(apr_array_header_t ** pathelts, const char * liststr, apr_pool_t * p) */
mrb_value
mrb_APR_apr_filepath_list_split(mrb_state* mrb, mrb_value self) {
  mrb_value pathelts;
  char * native_liststr = NULL;
  mrb_value p;

  /* Fetch the args */
  mrb_get_args(mrb, "ozo", &pathelts, &native_liststr, &p);

  /* Type checking */
  TODO_type_check_apr_array_header_t_PTR_PTR(pathelts);
  if (!mrb_obj_is_kind_of(mrb, p, AprPoolT_class(mrb))) {
    mrb_raise(mrb, E_TYPE_ERROR, "AprPoolT expected");
    return mrb_nil_value();
  }

  /* Unbox param: pathelts */
  apr_array_header_t ** native_pathelts = TODO_mruby_unbox_apr_array_header_t_PTR_PTR(pathelts);

  /* Unbox param: p */
  apr_pool_t * native_p = (mrb_nil_p(p) ? NULL : mruby_unbox_apr_pool_t(p));

  /* Invocation */
  apr_status_t native_return_value = apr_filepath_list_split(native_pathelts, native_liststr, native_p);

  /* Box the return value */
  mrb_value return_value = mrb_fixnum_value(native_return_value);
  
  return return_value;
}
#endif
/* MRUBY_BINDING_END */

/* MRUBY_BINDING: apr_filepath_merge */
/* sha: 53a5cd5767bce076e59ba7dd2f2a8c3a8ae1d47ac3a7626ddf2591e135a059a2 */
#if BIND_apr_filepath_merge_FUNCTION
#define apr_filepath_merge_REQUIRED_ARGC 5
#define apr_filepath_merge_OPTIONAL_ARGC 0
/* apr_status_t apr_filepath_merge(char ** newpath, const char * rootpath, const char * addpath, apr_int32_t flags, apr_pool_t * p) */
mrb_value
mrb_APR_apr_filepath_merge(mrb_state* mrb, mrb_value self) {
  mrb_value newpath;
  char * native_rootpath = NULL;
  char * native_addpath = NULL;
  mrb_int native_flags;
  mrb_value p;

  /* Fetch the args */
  mrb_get_args(mrb, "ozzio", &newpath, &native_rootpath, &native_addpath, &native_flags, &p);

  /* Type checking */
  TODO_type_check_char_PTR_PTR(newpath);
  if (!mrb_obj_is_kind_of(mrb, p, AprPoolT_class(mrb))) {
    mrb_raise(mrb, E_TYPE_ERROR, "AprPoolT expected");
    return mrb_nil_value();
  }

  /* Unbox param: newpath */
  char ** native_newpath = TODO_mruby_unbox_char_PTR_PTR(newpath);

  /* Unbox param: p */
  apr_pool_t * native_p = (mrb_nil_p(p) ? NULL : mruby_unbox_apr_pool_t(p));

  /* Invocation */
  apr_status_t native_return_value = apr_filepath_merge(native_newpath, native_rootpath, native_addpath, native_flags, native_p);

  /* Box the return value */
  mrb_value return_value = mrb_fixnum_value(native_return_value);
  
  return return_value;
}
#endif
/* MRUBY_BINDING_END */

/* MRUBY_BINDING: apr_filepath_root */
/* sha: 3461e2c21e201e89378f43b174a647483b4fa8335d5035a6526cd73a585c8630 */
#if BIND_apr_filepath_root_FUNCTION
#define apr_filepath_root_REQUIRED_ARGC 4
#define apr_filepath_root_OPTIONAL_ARGC 0
/* apr_status_t apr_filepath_root(const char ** rootpath, const char ** filepath, apr_int32_t flags, apr_pool_t * p) */
mrb_value
mrb_APR_apr_filepath_root(mrb_state* mrb, mrb_value self) {
  mrb_value rootpath;
  mrb_value filepath;
  mrb_int native_flags;
  mrb_value p;

  /* Fetch the args */
  mrb_get_args(mrb, "ooio", &rootpath, &filepath, &native_flags, &p);

  /* Type checking */
  TODO_type_check_char_PTR_PTR(rootpath);
  TODO_type_check_char_PTR_PTR(filepath);
  if (!mrb_obj_is_kind_of(mrb, p, AprPoolT_class(mrb))) {
    mrb_raise(mrb, E_TYPE_ERROR, "AprPoolT expected");
    return mrb_nil_value();
  }

  /* Unbox param: rootpath */
  const char ** native_rootpath = TODO_mruby_unbox_char_PTR_PTR(rootpath);

  /* Unbox param: filepath */
  const char ** native_filepath = TODO_mruby_unbox_char_PTR_PTR(filepath);

  /* Unbox param: p */
  apr_pool_t * native_p = (mrb_nil_p(p) ? NULL : mruby_unbox_apr_pool_t(p));

  /* Invocation */
  apr_status_t native_return_value = apr_filepath_root(native_rootpath, native_filepath, native_flags, native_p);

  /* Box the return value */
  mrb_value return_value = mrb_fixnum_value(native_return_value);
  
  return return_value;
}
#endif
/* MRUBY_BINDING_END */

/* MRUBY_BINDING: apr_filepath_set */
/* sha: 8b2b81ce81f6167555cc1e623cbeedcfb0d663069762aee2eca4542ddf197a62 */
#if BIND_apr_filepath_set_FUNCTION
#define apr_filepath_set_REQUIRED_ARGC 2
#define apr_filepath_set_OPTIONAL_ARGC 0
/* apr_status_t apr_filepath_set(const char * path, apr_pool_t * p) */
mrb_value
mrb_APR_apr_filepath_set(mrb_state* mrb, mrb_value self) {
  char * native_path = NULL;
  mrb_value p;

  /* Fetch the args */
  mrb_get_args(mrb, "zo", &native_path, &p);

  /* Type checking */
  if (!mrb_obj_is_kind_of(mrb, p, AprPoolT_class(mrb))) {
    mrb_raise(mrb, E_TYPE_ERROR, "AprPoolT expected");
    return mrb_nil_value();
  }

  /* Unbox param: p */
  apr_pool_t * native_p = (mrb_nil_p(p) ? NULL : mruby_unbox_apr_pool_t(p));

  /* Invocation */
  apr_status_t native_return_value = apr_filepath_set(native_path, native_p);

  /* Box the return value */
  mrb_value return_value = mrb_fixnum_value(native_return_value);
  
  return return_value;
}
#endif
/* MRUBY_BINDING_END */

/* MRUBY_BINDING: apr_fnmatch */
/* sha: user_edited */
#if BIND_apr_fnmatch_FUNCTION
#define apr_fnmatch_REQUIRED_ARGC 3
#define apr_fnmatch_OPTIONAL_ARGC 0
/* apr_fnmatch
 *
 * Parameters:
 * - pattern: const char *
 * - strings: const char *
 * - flags: int
 * Return Type: apr_status_t
 */
mrb_value
mrb_APR_apr_fnmatch(mrb_state* mrb, mrb_value self) {
  char * native_pattern;
  char * native_strings;
  mrb_int native_flags;

  /* Fetch the args */
  mrb_get_args(mrb, "zzi", &native_pattern, &native_strings, &native_flags);

  /* Invocation */
  apr_status_t result = apr_fnmatch(native_pattern, native_strings, native_flags);

  /* Box the return value */
  mrb_value return_value = mrb_fixnum_value(result);

  return return_value;
}
#endif
/* MRUBY_BINDING_END */

/* MRUBY_BINDING: apr_fnmatch_test */
/* sha: user_edited */
#if BIND_apr_fnmatch_test_FUNCTION
#define apr_fnmatch_test_REQUIRED_ARGC 1
#define apr_fnmatch_test_OPTIONAL_ARGC 0
/* apr_fnmatch_test
 *
 * Parameters:
 * - pattern: const char *
 * Return Type: int
 */
mrb_value
mrb_APR_apr_fnmatch_test(mrb_state* mrb, mrb_value self) {
  char * native_pattern;

  /* Fetch the args */
  mrb_get_args(mrb, "z", &native_pattern);

  /* Invocation */
  int result = apr_fnmatch_test(native_pattern);

  /* Box the return value */
  if (result > MRB_INT_MAX) {
    mrb_raise(mrb, mrb->eStandardError_class, "MRuby cannot represent integers greater than MRB_INT_MAX");
    return mrb_nil_value();
  }
  mrb_value return_value = mrb_fixnum_value(result);

  return return_value;
}
#endif
/* MRUBY_BINDING_END */

/* MRUBY_BINDING: apr_generate_random_bytes */
/* sha: fefc6790e23048378a0a3524deecd8eebf6d62c5057fb2ca8f855072b49a902d */
#if BIND_apr_generate_random_bytes_FUNCTION
#define apr_generate_random_bytes_REQUIRED_ARGC 2
#define apr_generate_random_bytes_OPTIONAL_ARGC 0
/* apr_status_t apr_generate_random_bytes(unsigned char * buf, apr_size_t length) */
mrb_value
mrb_APR_apr_generate_random_bytes(mrb_state* mrb, mrb_value self) {
  mrb_value buf;
  mrb_int native_length;

  /* Fetch the args */
  mrb_get_args(mrb, "oi", &buf, &native_length);

  /* Type checking */
  TODO_type_check_unsigned_char_PTR(buf);

  /* Unbox param: buf */
  unsigned char * native_buf = TODO_mruby_unbox_unsigned_char_PTR(buf);

  /* Invocation */
  apr_status_t native_return_value = apr_generate_random_bytes(native_buf, native_length);

  /* Box the return value */
  mrb_value return_value = mrb_fixnum_value(native_return_value);
  
  return return_value;
}
#endif
/* MRUBY_BINDING_END */

/* MRUBY_BINDING: apr_gethostname */
/* sha: user_edited */
#if BIND_apr_gethostname_FUNCTION
#define apr_gethostname_REQUIRED_ARGC 1
#define apr_gethostname_OPTIONAL_ARGC 0
/* apr_gethostname
 *
 * Parameters:
 * - cont: apr_pool_t *
 * Return Type: apr_status_t
 */
mrb_value
mrb_APR_apr_gethostname(mrb_state* mrb, mrb_value self) {
  mrb_value pool;

  /* Fetch the args */
  mrb_get_args(mrb, "o", &pool);

  /* Type checking */
  if (!mrb_obj_is_kind_of(mrb, pool, AprPoolT_class(mrb))) {
    mrb_raise(mrb, E_TYPE_ERROR, "AprPoolT expected");
    return mrb_nil_value();
  }

  apr_pool_t * native_pool = (mrb_nil_p(pool) ? NULL : mruby_unbox_apr_pool_t(pool));

  /* Invocation */
  int native_len = APRMAXHOSTLEN;
  char* native_buf = (char*)malloc(native_len * (sizeof(char)));
  apr_status_t result = apr_gethostname(native_buf, native_len, native_pool);

  mrb_value hostname = mrb_str_new_cstr(mrb, native_buf);
  free(native_buf);
  RETURN_ERRNO_AND_OUTPUT(result, hostname);
}
#endif
/* MRUBY_BINDING_END */

/* MRUBY_BINDING: apr_getnameinfo */
/* sha: user_edited */
#if BIND_apr_getnameinfo_FUNCTION
#define apr_getnameinfo_REQUIRED_ARGC 1
#define apr_getnameinfo_OPTIONAL_ARGC 0
/* apr_getnameinfo
 *
 * Parameters:
 * - sa: apr_sockaddr_t *
 * Return Type: apr_status_t
 */
mrb_value
mrb_APR_apr_getnameinfo(mrb_state* mrb, mrb_value self) {
  mrb_value sa;

  /* Fetch the args */
  mrb_get_args(mrb, "o", &sa);

  /* Type checking */
  if (!mrb_obj_is_kind_of(mrb, sa, AprSockaddrT_class(mrb))) {
    mrb_raise(mrb, E_TYPE_ERROR, "AprSockaddrT expected");
    return mrb_nil_value();
  }

  /* Unbox parameters */
  apr_sockaddr_t * native_sa = (mrb_nil_p(sa) ? NULL : mruby_unbox_apr_sockaddr_t(sa));

  /* Invocation */
  char * native_hostname;
  apr_status_t result = apr_getnameinfo(&native_hostname, native_sa, 0);

  if (result == APR_SUCCESS) {
    RETURN_ERRNO_AND_OUTPUT(result, mrb_str_new_cstr(mrb, native_hostname));
  } else {
    RETURN_ERRNO_AND_OUTPUT(result, mrb_nil_value());
  }
}
#endif
/* MRUBY_BINDING_END */

/* MRUBY_BINDING: apr_getservbyname */
/* sha: 047db930bb94a2ee222135caf59554de2dbcc789c3bc51a219e88c32f63b2053 */
#if BIND_apr_getservbyname_FUNCTION
#define apr_getservbyname_REQUIRED_ARGC 2
#define apr_getservbyname_OPTIONAL_ARGC 0
/* apr_status_t apr_getservbyname(apr_sockaddr_t * sockaddr, const char * servname) */
mrb_value
mrb_APR_apr_getservbyname(mrb_state* mrb, mrb_value self) {
  mrb_value sockaddr;
  char * native_servname = NULL;

  /* Fetch the args */
  mrb_get_args(mrb, "oz", &sockaddr, &native_servname);

  /* Type checking */
  if (!mrb_obj_is_kind_of(mrb, sockaddr, AprSockaddrT_class(mrb))) {
    mrb_raise(mrb, E_TYPE_ERROR, "AprSockaddrT expected");
    return mrb_nil_value();
  }

  /* Unbox param: sockaddr */
  apr_sockaddr_t * native_sockaddr = (mrb_nil_p(sockaddr) ? NULL : mruby_unbox_apr_sockaddr_t(sockaddr));

  /* Invocation */
  apr_status_t native_return_value = apr_getservbyname(native_sockaddr, native_servname);

  /* Box the return value */
  mrb_value return_value = mrb_fixnum_value(native_return_value);
  
  return return_value;
}
#endif
/* MRUBY_BINDING_END */

/* MRUBY_BINDING: apr_global_mutex_child_init */
/* sha: 240d39205ffcbc3ddf560a4c6f9cdcc28359cc22a0fc3d22920e9e3631a9b61c */
#if BIND_apr_global_mutex_child_init_FUNCTION
#define apr_global_mutex_child_init_REQUIRED_ARGC 3
#define apr_global_mutex_child_init_OPTIONAL_ARGC 0
/* apr_status_t apr_global_mutex_child_init(apr_global_mutex_t ** mutex, const char * fname, apr_pool_t * pool) */
mrb_value
mrb_APR_apr_global_mutex_child_init(mrb_state* mrb, mrb_value self) {
  mrb_value mutex;
  char * native_fname = NULL;
  mrb_value pool;

  /* Fetch the args */
  mrb_get_args(mrb, "ozo", &mutex, &native_fname, &pool);

  /* Type checking */
  TODO_type_check_apr_global_mutex_t_PTR_PTR(mutex);
  if (!mrb_obj_is_kind_of(mrb, pool, AprPoolT_class(mrb))) {
    mrb_raise(mrb, E_TYPE_ERROR, "AprPoolT expected");
    return mrb_nil_value();
  }

  /* Unbox param: mutex */
  apr_global_mutex_t ** native_mutex = TODO_mruby_unbox_apr_global_mutex_t_PTR_PTR(mutex);

  /* Unbox param: pool */
  apr_pool_t * native_pool = (mrb_nil_p(pool) ? NULL : mruby_unbox_apr_pool_t(pool));

  /* Invocation */
  apr_status_t native_return_value = apr_global_mutex_child_init(native_mutex, native_fname, native_pool);

  /* Box the return value */
  mrb_value return_value = mrb_fixnum_value(native_return_value);
  
  return return_value;
}
#endif
/* MRUBY_BINDING_END */

/* MRUBY_BINDING: apr_global_mutex_create */
/* sha: b320e093452340ca9db8d0ce0aa2f099acde15fcdf4486cbafbbabe073c56e3c */
#if BIND_apr_global_mutex_create_FUNCTION
#define apr_global_mutex_create_REQUIRED_ARGC 4
#define apr_global_mutex_create_OPTIONAL_ARGC 0
/* apr_status_t apr_global_mutex_create(apr_global_mutex_t ** mutex, const char * fname, apr_lockmech_e mech, apr_pool_t * pool) */
mrb_value
mrb_APR_apr_global_mutex_create(mrb_state* mrb, mrb_value self) {
  mrb_value mutex;
  char * native_fname = NULL;
  mrb_int native_mech;
  mrb_value pool;

  /* Fetch the args */
  mrb_get_args(mrb, "ozio", &mutex, &native_fname, &native_mech, &pool);

  /* Type checking */
  TODO_type_check_apr_global_mutex_t_PTR_PTR(mutex);
  if (!mrb_obj_is_kind_of(mrb, pool, AprPoolT_class(mrb))) {
    mrb_raise(mrb, E_TYPE_ERROR, "AprPoolT expected");
    return mrb_nil_value();
  }

  /* Unbox param: mutex */
  apr_global_mutex_t ** native_mutex = TODO_mruby_unbox_apr_global_mutex_t_PTR_PTR(mutex);

  /* Unbox param: pool */
  apr_pool_t * native_pool = (mrb_nil_p(pool) ? NULL : mruby_unbox_apr_pool_t(pool));

  /* Invocation */
  apr_status_t native_return_value = apr_global_mutex_create(native_mutex, native_fname, native_mech, native_pool);

  /* Box the return value */
  mrb_value return_value = mrb_fixnum_value(native_return_value);
  
  return return_value;
}
#endif
/* MRUBY_BINDING_END */

/* MRUBY_BINDING: apr_global_mutex_destroy */
/* sha: 484b676cac1bcedc23bd5f0315036aba213ce8ffc1c3f38b833635d652787a42 */
#if BIND_apr_global_mutex_destroy_FUNCTION
#define apr_global_mutex_destroy_REQUIRED_ARGC 1
#define apr_global_mutex_destroy_OPTIONAL_ARGC 0
/* apr_status_t apr_global_mutex_destroy(apr_global_mutex_t * mutex) */
mrb_value
mrb_APR_apr_global_mutex_destroy(mrb_state* mrb, mrb_value self) {
  mrb_value mutex;

  /* Fetch the args */
  mrb_get_args(mrb, "o", &mutex);

  /* Type checking */
  if (!mrb_obj_is_kind_of(mrb, mutex, AprGlobalMutexT_class(mrb))) {
    mrb_raise(mrb, E_TYPE_ERROR, "AprGlobalMutexT expected");
    return mrb_nil_value();
  }

  /* Unbox param: mutex */
  apr_global_mutex_t * native_mutex = (mrb_nil_p(mutex) ? NULL : mruby_unbox_apr_global_mutex_t(mutex));

  /* Invocation */
  apr_status_t native_return_value = apr_global_mutex_destroy(native_mutex);

  /* Box the return value */
  mrb_value return_value = mrb_fixnum_value(native_return_value);
  
  return return_value;
}
#endif
/* MRUBY_BINDING_END */

/* MRUBY_BINDING: apr_global_mutex_lock */
/* sha: 4d51a06464aff9cac7b724478a31d15717a8b2d70f814731ffbf8b781a2d732c */
#if BIND_apr_global_mutex_lock_FUNCTION
#define apr_global_mutex_lock_REQUIRED_ARGC 1
#define apr_global_mutex_lock_OPTIONAL_ARGC 0
/* apr_status_t apr_global_mutex_lock(apr_global_mutex_t * mutex) */
mrb_value
mrb_APR_apr_global_mutex_lock(mrb_state* mrb, mrb_value self) {
  mrb_value mutex;

  /* Fetch the args */
  mrb_get_args(mrb, "o", &mutex);

  /* Type checking */
  if (!mrb_obj_is_kind_of(mrb, mutex, AprGlobalMutexT_class(mrb))) {
    mrb_raise(mrb, E_TYPE_ERROR, "AprGlobalMutexT expected");
    return mrb_nil_value();
  }

  /* Unbox param: mutex */
  apr_global_mutex_t * native_mutex = (mrb_nil_p(mutex) ? NULL : mruby_unbox_apr_global_mutex_t(mutex));

  /* Invocation */
  apr_status_t native_return_value = apr_global_mutex_lock(native_mutex);

  /* Box the return value */
  mrb_value return_value = mrb_fixnum_value(native_return_value);
  
  return return_value;
}
#endif
/* MRUBY_BINDING_END */

/* MRUBY_BINDING: apr_global_mutex_lockfile */
/* sha: 06c10bba548d1c143fe3814e679766ef533e47471b79fec2f4bc36060689f517 */
#if BIND_apr_global_mutex_lockfile_FUNCTION
#define apr_global_mutex_lockfile_REQUIRED_ARGC 1
#define apr_global_mutex_lockfile_OPTIONAL_ARGC 0
/* const char * apr_global_mutex_lockfile(apr_global_mutex_t * mutex) */
mrb_value
mrb_APR_apr_global_mutex_lockfile(mrb_state* mrb, mrb_value self) {
  mrb_value mutex;

  /* Fetch the args */
  mrb_get_args(mrb, "o", &mutex);

  /* Type checking */
  if (!mrb_obj_is_kind_of(mrb, mutex, AprGlobalMutexT_class(mrb))) {
    mrb_raise(mrb, E_TYPE_ERROR, "AprGlobalMutexT expected");
    return mrb_nil_value();
  }

  /* Unbox param: mutex */
  apr_global_mutex_t * native_mutex = (mrb_nil_p(mutex) ? NULL : mruby_unbox_apr_global_mutex_t(mutex));

  /* Invocation */
  const char * native_return_value = apr_global_mutex_lockfile(native_mutex);

  /* Box the return value */
  mrb_value return_value = native_return_value == NULL ? mrb_nil_value() : mrb_str_new_cstr(mrb, native_return_value);
  
  return return_value;
}
#endif
/* MRUBY_BINDING_END */

/* MRUBY_BINDING: apr_global_mutex_name */
/* sha: 53037b8d38e4f9b748a412b23babdde4108689c781b9e2fe20da8cc65f45581c */
#if BIND_apr_global_mutex_name_FUNCTION
#define apr_global_mutex_name_REQUIRED_ARGC 1
#define apr_global_mutex_name_OPTIONAL_ARGC 0
/* const char * apr_global_mutex_name(apr_global_mutex_t * mutex) */
mrb_value
mrb_APR_apr_global_mutex_name(mrb_state* mrb, mrb_value self) {
  mrb_value mutex;

  /* Fetch the args */
  mrb_get_args(mrb, "o", &mutex);

  /* Type checking */
  if (!mrb_obj_is_kind_of(mrb, mutex, AprGlobalMutexT_class(mrb))) {
    mrb_raise(mrb, E_TYPE_ERROR, "AprGlobalMutexT expected");
    return mrb_nil_value();
  }

  /* Unbox param: mutex */
  apr_global_mutex_t * native_mutex = (mrb_nil_p(mutex) ? NULL : mruby_unbox_apr_global_mutex_t(mutex));

  /* Invocation */
  const char * native_return_value = apr_global_mutex_name(native_mutex);

  /* Box the return value */
  mrb_value return_value = native_return_value == NULL ? mrb_nil_value() : mrb_str_new_cstr(mrb, native_return_value);
  
  return return_value;
}
#endif
/* MRUBY_BINDING_END */

/* MRUBY_BINDING: apr_global_mutex_trylock */
/* sha: 964d97f1bfc4889a9e4369d79c3457969dabd8005df8d8312be8caf8b4dda85c */
#if BIND_apr_global_mutex_trylock_FUNCTION
#define apr_global_mutex_trylock_REQUIRED_ARGC 1
#define apr_global_mutex_trylock_OPTIONAL_ARGC 0
/* apr_status_t apr_global_mutex_trylock(apr_global_mutex_t * mutex) */
mrb_value
mrb_APR_apr_global_mutex_trylock(mrb_state* mrb, mrb_value self) {
  mrb_value mutex;

  /* Fetch the args */
  mrb_get_args(mrb, "o", &mutex);

  /* Type checking */
  if (!mrb_obj_is_kind_of(mrb, mutex, AprGlobalMutexT_class(mrb))) {
    mrb_raise(mrb, E_TYPE_ERROR, "AprGlobalMutexT expected");
    return mrb_nil_value();
  }

  /* Unbox param: mutex */
  apr_global_mutex_t * native_mutex = (mrb_nil_p(mutex) ? NULL : mruby_unbox_apr_global_mutex_t(mutex));

  /* Invocation */
  apr_status_t native_return_value = apr_global_mutex_trylock(native_mutex);

  /* Box the return value */
  mrb_value return_value = mrb_fixnum_value(native_return_value);
  
  return return_value;
}
#endif
/* MRUBY_BINDING_END */

/* MRUBY_BINDING: apr_global_mutex_unlock */
/* sha: 25dafa9645e560c5cf8074ff8bf59fed47a6ddad8b694e53b9bec107c7329470 */
#if BIND_apr_global_mutex_unlock_FUNCTION
#define apr_global_mutex_unlock_REQUIRED_ARGC 1
#define apr_global_mutex_unlock_OPTIONAL_ARGC 0
/* apr_status_t apr_global_mutex_unlock(apr_global_mutex_t * mutex) */
mrb_value
mrb_APR_apr_global_mutex_unlock(mrb_state* mrb, mrb_value self) {
  mrb_value mutex;

  /* Fetch the args */
  mrb_get_args(mrb, "o", &mutex);

  /* Type checking */
  if (!mrb_obj_is_kind_of(mrb, mutex, AprGlobalMutexT_class(mrb))) {
    mrb_raise(mrb, E_TYPE_ERROR, "AprGlobalMutexT expected");
    return mrb_nil_value();
  }

  /* Unbox param: mutex */
  apr_global_mutex_t * native_mutex = (mrb_nil_p(mutex) ? NULL : mruby_unbox_apr_global_mutex_t(mutex));

  /* Invocation */
  apr_status_t native_return_value = apr_global_mutex_unlock(native_mutex);

  /* Box the return value */
  mrb_value return_value = mrb_fixnum_value(native_return_value);
  
  return return_value;
}
#endif
/* MRUBY_BINDING_END */

/* MRUBY_BINDING: apr_initialize */
/* sha: user_edited */
#if BIND_apr_initialize_FUNCTION
#define apr_initialize_REQUIRED_ARGC 0
#define apr_initialize_OPTIONAL_ARGC 0
/* apr_initialize
 *
 * Parameters: None
 * Return Type: apr_status_t
 */
mrb_value
mrb_APR_apr_initialize(mrb_state* mrb, mrb_value self) {
  /* Invocation */
  apr_status_t result = apr_initialize();

  /* Box the return value */
  if (result > MRB_INT_MAX) {
    mrb_raise(mrb, mrb->eStandardError_class, "MRuby cannot represent integers greater than MRB_INT_MAX");
    return mrb_nil_value();
  }
  mrb_value return_value = mrb_fixnum_value(result);

  return return_value;
}
#endif
/* MRUBY_BINDING_END */

/* MRUBY_BINDING: apr_ipsubnet_create */
/* sha: 9626a152b9bc70575f2ee483e9781396eb55db45b5202f1a9177c079b6e56725 */
#if BIND_apr_ipsubnet_create_FUNCTION
#define apr_ipsubnet_create_REQUIRED_ARGC 4
#define apr_ipsubnet_create_OPTIONAL_ARGC 0
/* apr_status_t apr_ipsubnet_create(apr_ipsubnet_t ** ipsub, const char * ipstr, const char * mask_or_numbits, apr_pool_t * p) */
mrb_value
mrb_APR_apr_ipsubnet_create(mrb_state* mrb, mrb_value self) {
  mrb_value ipsub;
  char * native_ipstr = NULL;
  char * native_mask_or_numbits = NULL;
  mrb_value p;

  /* Fetch the args */
  mrb_get_args(mrb, "ozzo", &ipsub, &native_ipstr, &native_mask_or_numbits, &p);

  /* Type checking */
  TODO_type_check_apr_ipsubnet_t_PTR_PTR(ipsub);
  if (!mrb_obj_is_kind_of(mrb, p, AprPoolT_class(mrb))) {
    mrb_raise(mrb, E_TYPE_ERROR, "AprPoolT expected");
    return mrb_nil_value();
  }

  /* Unbox param: ipsub */
  apr_ipsubnet_t ** native_ipsub = TODO_mruby_unbox_apr_ipsubnet_t_PTR_PTR(ipsub);

  /* Unbox param: p */
  apr_pool_t * native_p = (mrb_nil_p(p) ? NULL : mruby_unbox_apr_pool_t(p));

  /* Invocation */
  apr_status_t native_return_value = apr_ipsubnet_create(native_ipsub, native_ipstr, native_mask_or_numbits, native_p);

  /* Box the return value */
  mrb_value return_value = mrb_fixnum_value(native_return_value);
  
  return return_value;
}
#endif
/* MRUBY_BINDING_END */

/* MRUBY_BINDING: apr_ipsubnet_test */
/* sha: 8a0cf2679f2cadc29627bfb7261f7150533d593ac21eb6465837019bba0f75a6 */
#if BIND_apr_ipsubnet_test_FUNCTION
#define apr_ipsubnet_test_REQUIRED_ARGC 2
#define apr_ipsubnet_test_OPTIONAL_ARGC 0
/* int apr_ipsubnet_test(apr_ipsubnet_t * ipsub, apr_sockaddr_t * sa) */
mrb_value
mrb_APR_apr_ipsubnet_test(mrb_state* mrb, mrb_value self) {
  mrb_value ipsub;
  mrb_value sa;

  /* Fetch the args */
  mrb_get_args(mrb, "oo", &ipsub, &sa);

  /* Type checking */
  if (!mrb_obj_is_kind_of(mrb, ipsub, AprIpsubnetT_class(mrb))) {
    mrb_raise(mrb, E_TYPE_ERROR, "AprIpsubnetT expected");
    return mrb_nil_value();
  }
  if (!mrb_obj_is_kind_of(mrb, sa, AprSockaddrT_class(mrb))) {
    mrb_raise(mrb, E_TYPE_ERROR, "AprSockaddrT expected");
    return mrb_nil_value();
  }

  /* Unbox param: ipsub */
  apr_ipsubnet_t * native_ipsub = (mrb_nil_p(ipsub) ? NULL : mruby_unbox_apr_ipsubnet_t(ipsub));

  /* Unbox param: sa */
  apr_sockaddr_t * native_sa = (mrb_nil_p(sa) ? NULL : mruby_unbox_apr_sockaddr_t(sa));

  /* Invocation */
  int native_return_value = apr_ipsubnet_test(native_ipsub, native_sa);

  /* Box the return value */
  mrb_value return_value = mrb_fixnum_value(native_return_value);
  
  return return_value;
}
#endif
/* MRUBY_BINDING_END */

/* MRUBY_BINDING: apr_itoa */
/* sha: 1cc4b78a381a12d2da493fed8b32730858153fe8cf090ed45bbf5998b4294a87 */
#if BIND_apr_itoa_FUNCTION
#define apr_itoa_REQUIRED_ARGC 2
#define apr_itoa_OPTIONAL_ARGC 0
/* char * apr_itoa(apr_pool_t * p, int n) */
mrb_value
mrb_APR_apr_itoa(mrb_state* mrb, mrb_value self) {
  mrb_value p;
  mrb_int native_n;

  /* Fetch the args */
  mrb_get_args(mrb, "oi", &p, &native_n);

  /* Type checking */
  if (!mrb_obj_is_kind_of(mrb, p, AprPoolT_class(mrb))) {
    mrb_raise(mrb, E_TYPE_ERROR, "AprPoolT expected");
    return mrb_nil_value();
  }

  /* Unbox param: p */
  apr_pool_t * native_p = (mrb_nil_p(p) ? NULL : mruby_unbox_apr_pool_t(p));

  /* Invocation */
  char * native_return_value = apr_itoa(native_p, native_n);

  /* Box the return value */
  mrb_value return_value = TODO_mruby_box_char_PTR(mrb, native_return_value);
  
  return return_value;
}
#endif
/* MRUBY_BINDING_END */

/* MRUBY_BINDING: apr_ltoa */
/* sha: 1a165bb570f035e687e565514468dd6c22e29f584d122f048309fe39a4aa18dd */
#if BIND_apr_ltoa_FUNCTION
#define apr_ltoa_REQUIRED_ARGC 2
#define apr_ltoa_OPTIONAL_ARGC 0
/* char * apr_ltoa(apr_pool_t * p, long n) */
mrb_value
mrb_APR_apr_ltoa(mrb_state* mrb, mrb_value self) {
  mrb_value p;
  mrb_int native_n;

  /* Fetch the args */
  mrb_get_args(mrb, "oi", &p, &native_n);

  /* Type checking */
  if (!mrb_obj_is_kind_of(mrb, p, AprPoolT_class(mrb))) {
    mrb_raise(mrb, E_TYPE_ERROR, "AprPoolT expected");
    return mrb_nil_value();
  }

  /* Unbox param: p */
  apr_pool_t * native_p = (mrb_nil_p(p) ? NULL : mruby_unbox_apr_pool_t(p));

  /* Invocation */
  char * native_return_value = apr_ltoa(native_p, native_n);

  /* Box the return value */
  mrb_value return_value = TODO_mruby_box_char_PTR(mrb, native_return_value);
  
  return return_value;
}
#endif
/* MRUBY_BINDING_END */

/* MRUBY_BINDING: apr_match_glob */
/* sha: db00b094f97c02ddfd1fd9ca67b8ff4c13c35bfc57771905b69612e1b2cfea16 */
#if BIND_apr_match_glob_FUNCTION
#define apr_match_glob_REQUIRED_ARGC 3
#define apr_match_glob_OPTIONAL_ARGC 0
/* apr_status_t apr_match_glob(const char * pattern, apr_array_header_t ** result, apr_pool_t * p) */
mrb_value
mrb_APR_apr_match_glob(mrb_state* mrb, mrb_value self) {
  char * native_pattern = NULL;
  mrb_value result;
  mrb_value p;

  /* Fetch the args */
  mrb_get_args(mrb, "zoo", &native_pattern, &result, &p);

  /* Type checking */
  TODO_type_check_apr_array_header_t_PTR_PTR(result);
  if (!mrb_obj_is_kind_of(mrb, p, AprPoolT_class(mrb))) {
    mrb_raise(mrb, E_TYPE_ERROR, "AprPoolT expected");
    return mrb_nil_value();
  }

  /* Unbox param: result */
  apr_array_header_t ** native_result = TODO_mruby_unbox_apr_array_header_t_PTR_PTR(result);

  /* Unbox param: p */
  apr_pool_t * native_p = (mrb_nil_p(p) ? NULL : mruby_unbox_apr_pool_t(p));

  /* Invocation */
  apr_status_t native_return_value = apr_match_glob(native_pattern, native_result, native_p);

  /* Box the return value */
  mrb_value return_value = mrb_fixnum_value(native_return_value);
  
  return return_value;
}
#endif
/* MRUBY_BINDING_END */

/* MRUBY_BINDING: apr_mcast_hops */
/* sha: 213bc0ceb4dca8956d1bc729294ffb2dedb81740194e7f648ab74fce553e7735 */
#if BIND_apr_mcast_hops_FUNCTION
#define apr_mcast_hops_REQUIRED_ARGC 2
#define apr_mcast_hops_OPTIONAL_ARGC 0
/* apr_status_t apr_mcast_hops(apr_socket_t * sock, apr_byte_t ttl) */
mrb_value
mrb_APR_apr_mcast_hops(mrb_state* mrb, mrb_value self) {
  mrb_value sock;
  mrb_int native_ttl;

  /* Fetch the args */
  mrb_get_args(mrb, "oi", &sock, &native_ttl);

  /* Type checking */
  if (!mrb_obj_is_kind_of(mrb, sock, AprSocketT_class(mrb))) {
    mrb_raise(mrb, E_TYPE_ERROR, "AprSocketT expected");
    return mrb_nil_value();
  }

  /* Unbox param: sock */
  apr_socket_t * native_sock = (mrb_nil_p(sock) ? NULL : mruby_unbox_apr_socket_t(sock));

  /* Invocation */
  apr_status_t native_return_value = apr_mcast_hops(native_sock, native_ttl);

  /* Box the return value */
  mrb_value return_value = mrb_fixnum_value(native_return_value);
  
  return return_value;
}
#endif
/* MRUBY_BINDING_END */

/* MRUBY_BINDING: apr_mcast_interface */
/* sha: 6a7618e3dfb7a3524a75ef710bc99e0d00ae0308a74d7560e19139631f579caa */
#if BIND_apr_mcast_interface_FUNCTION
#define apr_mcast_interface_REQUIRED_ARGC 2
#define apr_mcast_interface_OPTIONAL_ARGC 0
/* apr_status_t apr_mcast_interface(apr_socket_t * sock, apr_sockaddr_t * iface) */
mrb_value
mrb_APR_apr_mcast_interface(mrb_state* mrb, mrb_value self) {
  mrb_value sock;
  mrb_value iface;

  /* Fetch the args */
  mrb_get_args(mrb, "oo", &sock, &iface);

  /* Type checking */
  if (!mrb_obj_is_kind_of(mrb, sock, AprSocketT_class(mrb))) {
    mrb_raise(mrb, E_TYPE_ERROR, "AprSocketT expected");
    return mrb_nil_value();
  }
  if (!mrb_obj_is_kind_of(mrb, iface, AprSockaddrT_class(mrb))) {
    mrb_raise(mrb, E_TYPE_ERROR, "AprSockaddrT expected");
    return mrb_nil_value();
  }

  /* Unbox param: sock */
  apr_socket_t * native_sock = (mrb_nil_p(sock) ? NULL : mruby_unbox_apr_socket_t(sock));

  /* Unbox param: iface */
  apr_sockaddr_t * native_iface = (mrb_nil_p(iface) ? NULL : mruby_unbox_apr_sockaddr_t(iface));

  /* Invocation */
  apr_status_t native_return_value = apr_mcast_interface(native_sock, native_iface);

  /* Box the return value */
  mrb_value return_value = mrb_fixnum_value(native_return_value);
  
  return return_value;
}
#endif
/* MRUBY_BINDING_END */

/* MRUBY_BINDING: apr_mcast_join */
/* sha: 55918493ac454d59ccb77f01388aeeae32d1cb3f651238e70cfd9c313da25c61 */
#if BIND_apr_mcast_join_FUNCTION
#define apr_mcast_join_REQUIRED_ARGC 4
#define apr_mcast_join_OPTIONAL_ARGC 0
/* apr_status_t apr_mcast_join(apr_socket_t * sock, apr_sockaddr_t * join, apr_sockaddr_t * iface, apr_sockaddr_t * source) */
mrb_value
mrb_APR_apr_mcast_join(mrb_state* mrb, mrb_value self) {
  mrb_value sock;
  mrb_value join;
  mrb_value iface;
  mrb_value source;

  /* Fetch the args */
  mrb_get_args(mrb, "oooo", &sock, &join, &iface, &source);

  /* Type checking */
  if (!mrb_obj_is_kind_of(mrb, sock, AprSocketT_class(mrb))) {
    mrb_raise(mrb, E_TYPE_ERROR, "AprSocketT expected");
    return mrb_nil_value();
  }
  if (!mrb_obj_is_kind_of(mrb, join, AprSockaddrT_class(mrb))) {
    mrb_raise(mrb, E_TYPE_ERROR, "AprSockaddrT expected");
    return mrb_nil_value();
  }
  if (!mrb_obj_is_kind_of(mrb, iface, AprSockaddrT_class(mrb))) {
    mrb_raise(mrb, E_TYPE_ERROR, "AprSockaddrT expected");
    return mrb_nil_value();
  }
  if (!mrb_obj_is_kind_of(mrb, source, AprSockaddrT_class(mrb))) {
    mrb_raise(mrb, E_TYPE_ERROR, "AprSockaddrT expected");
    return mrb_nil_value();
  }

  /* Unbox param: sock */
  apr_socket_t * native_sock = (mrb_nil_p(sock) ? NULL : mruby_unbox_apr_socket_t(sock));

  /* Unbox param: join */
  apr_sockaddr_t * native_join = (mrb_nil_p(join) ? NULL : mruby_unbox_apr_sockaddr_t(join));

  /* Unbox param: iface */
  apr_sockaddr_t * native_iface = (mrb_nil_p(iface) ? NULL : mruby_unbox_apr_sockaddr_t(iface));

  /* Unbox param: source */
  apr_sockaddr_t * native_source = (mrb_nil_p(source) ? NULL : mruby_unbox_apr_sockaddr_t(source));

  /* Invocation */
  apr_status_t native_return_value = apr_mcast_join(native_sock, native_join, native_iface, native_source);

  /* Box the return value */
  mrb_value return_value = mrb_fixnum_value(native_return_value);
  
  return return_value;
}
#endif
/* MRUBY_BINDING_END */

/* MRUBY_BINDING: apr_mcast_leave */
/* sha: d0f1b2df945c4bb7760983da2c21ba2c9056f13d2df8fa1f423f1ede68d88add */
#if BIND_apr_mcast_leave_FUNCTION
#define apr_mcast_leave_REQUIRED_ARGC 4
#define apr_mcast_leave_OPTIONAL_ARGC 0
/* apr_status_t apr_mcast_leave(apr_socket_t * sock, apr_sockaddr_t * addr, apr_sockaddr_t * iface, apr_sockaddr_t * source) */
mrb_value
mrb_APR_apr_mcast_leave(mrb_state* mrb, mrb_value self) {
  mrb_value sock;
  mrb_value addr;
  mrb_value iface;
  mrb_value source;

  /* Fetch the args */
  mrb_get_args(mrb, "oooo", &sock, &addr, &iface, &source);

  /* Type checking */
  if (!mrb_obj_is_kind_of(mrb, sock, AprSocketT_class(mrb))) {
    mrb_raise(mrb, E_TYPE_ERROR, "AprSocketT expected");
    return mrb_nil_value();
  }
  if (!mrb_obj_is_kind_of(mrb, addr, AprSockaddrT_class(mrb))) {
    mrb_raise(mrb, E_TYPE_ERROR, "AprSockaddrT expected");
    return mrb_nil_value();
  }
  if (!mrb_obj_is_kind_of(mrb, iface, AprSockaddrT_class(mrb))) {
    mrb_raise(mrb, E_TYPE_ERROR, "AprSockaddrT expected");
    return mrb_nil_value();
  }
  if (!mrb_obj_is_kind_of(mrb, source, AprSockaddrT_class(mrb))) {
    mrb_raise(mrb, E_TYPE_ERROR, "AprSockaddrT expected");
    return mrb_nil_value();
  }

  /* Unbox param: sock */
  apr_socket_t * native_sock = (mrb_nil_p(sock) ? NULL : mruby_unbox_apr_socket_t(sock));

  /* Unbox param: addr */
  apr_sockaddr_t * native_addr = (mrb_nil_p(addr) ? NULL : mruby_unbox_apr_sockaddr_t(addr));

  /* Unbox param: iface */
  apr_sockaddr_t * native_iface = (mrb_nil_p(iface) ? NULL : mruby_unbox_apr_sockaddr_t(iface));

  /* Unbox param: source */
  apr_sockaddr_t * native_source = (mrb_nil_p(source) ? NULL : mruby_unbox_apr_sockaddr_t(source));

  /* Invocation */
  apr_status_t native_return_value = apr_mcast_leave(native_sock, native_addr, native_iface, native_source);

  /* Box the return value */
  mrb_value return_value = mrb_fixnum_value(native_return_value);
  
  return return_value;
}
#endif
/* MRUBY_BINDING_END */

/* MRUBY_BINDING: apr_mcast_loopback */
/* sha: 53c60eccf79a5f6399cc1acaa11673650046c2971e89359dbcf65caeb3806fad */
#if BIND_apr_mcast_loopback_FUNCTION
#define apr_mcast_loopback_REQUIRED_ARGC 2
#define apr_mcast_loopback_OPTIONAL_ARGC 0
/* apr_status_t apr_mcast_loopback(apr_socket_t * sock, apr_byte_t opt) */
mrb_value
mrb_APR_apr_mcast_loopback(mrb_state* mrb, mrb_value self) {
  mrb_value sock;
  mrb_int native_opt;

  /* Fetch the args */
  mrb_get_args(mrb, "oi", &sock, &native_opt);

  /* Type checking */
  if (!mrb_obj_is_kind_of(mrb, sock, AprSocketT_class(mrb))) {
    mrb_raise(mrb, E_TYPE_ERROR, "AprSocketT expected");
    return mrb_nil_value();
  }

  /* Unbox param: sock */
  apr_socket_t * native_sock = (mrb_nil_p(sock) ? NULL : mruby_unbox_apr_socket_t(sock));

  /* Invocation */
  apr_status_t native_return_value = apr_mcast_loopback(native_sock, native_opt);

  /* Box the return value */
  mrb_value return_value = mrb_fixnum_value(native_return_value);
  
  return return_value;
}
#endif
/* MRUBY_BINDING_END */

/* MRUBY_BINDING: apr_off_t_toa */
/* sha: 7643b113b0e9c64cf054f569be2ae82eacb6704cef8e6512a8bbdb4ac5fd7a24 */
#if BIND_apr_off_t_toa_FUNCTION
#define apr_off_t_toa_REQUIRED_ARGC 2
#define apr_off_t_toa_OPTIONAL_ARGC 0
/* char * apr_off_t_toa(apr_pool_t * p, apr_off_t n) */
mrb_value
mrb_APR_apr_off_t_toa(mrb_state* mrb, mrb_value self) {
  mrb_value p;
  mrb_value n;

  /* Fetch the args */
  mrb_get_args(mrb, "oo", &p, &n);

  /* Type checking */
  if (!mrb_obj_is_kind_of(mrb, p, AprPoolT_class(mrb))) {
    mrb_raise(mrb, E_TYPE_ERROR, "AprPoolT expected");
    return mrb_nil_value();
  }
  TODO_type_check_apr_off_t(n);

  /* Unbox param: p */
  apr_pool_t * native_p = (mrb_nil_p(p) ? NULL : mruby_unbox_apr_pool_t(p));

  /* Unbox param: n */
  apr_off_t native_n = TODO_mruby_unbox_apr_off_t(n);

  /* Invocation */
  char * native_return_value = apr_off_t_toa(native_p, native_n);

  /* Box the return value */
  mrb_value return_value = TODO_mruby_box_char_PTR(mrb, native_return_value);
  
  return return_value;
}
#endif
/* MRUBY_BINDING_END */

/* MRUBY_BINDING: apr_palloc */
/* sha: fc5e2f2fb8e7170da2fa9680c7440512225229f856f3c3d93ef72f8289f051b1 */
#if BIND_apr_palloc_FUNCTION
#define apr_palloc_REQUIRED_ARGC 2
#define apr_palloc_OPTIONAL_ARGC 0
/* void * apr_palloc(apr_pool_t * p, apr_size_t size) */
mrb_value
mrb_APR_apr_palloc(mrb_state* mrb, mrb_value self) {
  mrb_value p;
  mrb_int native_size;

  /* Fetch the args */
  mrb_get_args(mrb, "oi", &p, &native_size);

  /* Type checking */
  if (!mrb_obj_is_kind_of(mrb, p, AprPoolT_class(mrb))) {
    mrb_raise(mrb, E_TYPE_ERROR, "AprPoolT expected");
    return mrb_nil_value();
  }

  /* Unbox param: p */
  apr_pool_t * native_p = (mrb_nil_p(p) ? NULL : mruby_unbox_apr_pool_t(p));

  /* Invocation */
  void * native_return_value = apr_palloc(native_p, native_size);

  /* Box the return value */
  mrb_value return_value = TODO_mruby_box_void_PTR(mrb, native_return_value);
  
  return return_value;
}
#endif
/* MRUBY_BINDING_END */

/* MRUBY_BINDING: apr_palloc_debug */
/* sha: 26c0e3be3dda4bebec473f7ff9e8247160e3a3535ce5a87d391c0d94751c877c */
#if BIND_apr_palloc_debug_FUNCTION
#define apr_palloc_debug_REQUIRED_ARGC 3
#define apr_palloc_debug_OPTIONAL_ARGC 0
/* void * apr_palloc_debug(apr_pool_t * p, apr_size_t size, const char * file_line) */
mrb_value
mrb_APR_apr_palloc_debug(mrb_state* mrb, mrb_value self) {
  mrb_value p;
  mrb_int native_size;
  char * native_file_line = NULL;

  /* Fetch the args */
  mrb_get_args(mrb, "oiz", &p, &native_size, &native_file_line);

  /* Type checking */
  if (!mrb_obj_is_kind_of(mrb, p, AprPoolT_class(mrb))) {
    mrb_raise(mrb, E_TYPE_ERROR, "AprPoolT expected");
    return mrb_nil_value();
  }

  /* Unbox param: p */
  apr_pool_t * native_p = (mrb_nil_p(p) ? NULL : mruby_unbox_apr_pool_t(p));

  /* Invocation */
  void * native_return_value = apr_palloc_debug(native_p, native_size, native_file_line);

  /* Box the return value */
  mrb_value return_value = TODO_mruby_box_void_PTR(mrb, native_return_value);
  
  return return_value;
}
#endif
/* MRUBY_BINDING_END */

/* MRUBY_BINDING: apr_parse_addr_port */
/* sha: 28dc6d39294d8430d2fcfc8a57cfac135f3586209fd218ae7cbec09e34f1fcc6 */
#if BIND_apr_parse_addr_port_FUNCTION
#define apr_parse_addr_port_REQUIRED_ARGC 5
#define apr_parse_addr_port_OPTIONAL_ARGC 0
/* apr_status_t apr_parse_addr_port(char ** addr, char ** scope_id, apr_port_t * port, const char * str, apr_pool_t * p) */
mrb_value
mrb_APR_apr_parse_addr_port(mrb_state* mrb, mrb_value self) {
  mrb_value addr;
  mrb_value scope_id;
  mrb_value port;
  char * native_str = NULL;
  mrb_value p;

  /* Fetch the args */
  mrb_get_args(mrb, "ooozo", &addr, &scope_id, &port, &native_str, &p);

  /* Type checking */
  TODO_type_check_char_PTR_PTR(addr);
  TODO_type_check_char_PTR_PTR(scope_id);
  TODO_type_check_apr_port_t_PTR(port);
  if (!mrb_obj_is_kind_of(mrb, p, AprPoolT_class(mrb))) {
    mrb_raise(mrb, E_TYPE_ERROR, "AprPoolT expected");
    return mrb_nil_value();
  }

  /* Unbox param: addr */
  char ** native_addr = TODO_mruby_unbox_char_PTR_PTR(addr);

  /* Unbox param: scope_id */
  char ** native_scope_id = TODO_mruby_unbox_char_PTR_PTR(scope_id);

  /* Unbox param: port */
  apr_port_t * native_port = TODO_mruby_unbox_apr_port_t_PTR(port);

  /* Unbox param: p */
  apr_pool_t * native_p = (mrb_nil_p(p) ? NULL : mruby_unbox_apr_pool_t(p));

  /* Invocation */
  apr_status_t native_return_value = apr_parse_addr_port(native_addr, native_scope_id, native_port, native_str, native_p);

  /* Box the return value */
  mrb_value return_value = mrb_fixnum_value(native_return_value);
  
  return return_value;
}
#endif
/* MRUBY_BINDING_END */

/* MRUBY_BINDING: apr_pcalloc_debug */
/* sha: 1caf1ed057d8fb5ff30c379f40ffb1bc03e25d43af72585ca3bdb421aabf673f */
#if BIND_apr_pcalloc_debug_FUNCTION
#define apr_pcalloc_debug_REQUIRED_ARGC 3
#define apr_pcalloc_debug_OPTIONAL_ARGC 0
/* void * apr_pcalloc_debug(apr_pool_t * p, apr_size_t size, const char * file_line) */
mrb_value
mrb_APR_apr_pcalloc_debug(mrb_state* mrb, mrb_value self) {
  mrb_value p;
  mrb_int native_size;
  char * native_file_line = NULL;

  /* Fetch the args */
  mrb_get_args(mrb, "oiz", &p, &native_size, &native_file_line);

  /* Type checking */
  if (!mrb_obj_is_kind_of(mrb, p, AprPoolT_class(mrb))) {
    mrb_raise(mrb, E_TYPE_ERROR, "AprPoolT expected");
    return mrb_nil_value();
  }

  /* Unbox param: p */
  apr_pool_t * native_p = (mrb_nil_p(p) ? NULL : mruby_unbox_apr_pool_t(p));

  /* Invocation */
  void * native_return_value = apr_pcalloc_debug(native_p, native_size, native_file_line);

  /* Box the return value */
  mrb_value return_value = TODO_mruby_box_void_PTR(mrb, native_return_value);
  
  return return_value;
}
#endif
/* MRUBY_BINDING_END */

/* MRUBY_BINDING: apr_pmemdup */
/* sha: 29d2a1b74e4ce5fe0c241dc449cb28f8981b14a6564277b2609f6e7c6bf88045 */
#if BIND_apr_pmemdup_FUNCTION
#define apr_pmemdup_REQUIRED_ARGC 3
#define apr_pmemdup_OPTIONAL_ARGC 0
/* void * apr_pmemdup(apr_pool_t * p, const void * m, apr_size_t n) */
mrb_value
mrb_APR_apr_pmemdup(mrb_state* mrb, mrb_value self) {
  mrb_value p;
  mrb_value m;
  mrb_int native_n;

  /* Fetch the args */
  mrb_get_args(mrb, "ooi", &p, &m, &native_n);

  /* Type checking */
  if (!mrb_obj_is_kind_of(mrb, p, AprPoolT_class(mrb))) {
    mrb_raise(mrb, E_TYPE_ERROR, "AprPoolT expected");
    return mrb_nil_value();
  }
  TODO_type_check_void_PTR(m);

  /* Unbox param: p */
  apr_pool_t * native_p = (mrb_nil_p(p) ? NULL : mruby_unbox_apr_pool_t(p));

  /* Unbox param: m */
  const void * native_m = TODO_mruby_unbox_void_PTR(m);

  /* Invocation */
  void * native_return_value = apr_pmemdup(native_p, native_m, native_n);

  /* Box the return value */
  mrb_value return_value = TODO_mruby_box_void_PTR(mrb, native_return_value);
  
  return return_value;
}
#endif
/* MRUBY_BINDING_END */

/* MRUBY_BINDING: apr_pool_abort_get */
/* sha: e8616fc332beac50d25c37b8dfeb6be3d44e4aa673ca27894d20f4fa56155974 */
#if BIND_apr_pool_abort_get_FUNCTION
#define apr_pool_abort_get_REQUIRED_ARGC 1
#define apr_pool_abort_get_OPTIONAL_ARGC 0
/* apr_abortfunc_t apr_pool_abort_get(apr_pool_t * pool) */
mrb_value
mrb_APR_apr_pool_abort_get(mrb_state* mrb, mrb_value self) {
  mrb_value pool;

  /* Fetch the args */
  mrb_get_args(mrb, "o", &pool);

  /* Type checking */
  if (!mrb_obj_is_kind_of(mrb, pool, AprPoolT_class(mrb))) {
    mrb_raise(mrb, E_TYPE_ERROR, "AprPoolT expected");
    return mrb_nil_value();
  }

  /* Unbox param: pool */
  apr_pool_t * native_pool = (mrb_nil_p(pool) ? NULL : mruby_unbox_apr_pool_t(pool));

  /* Invocation */
  apr_abortfunc_t native_return_value = apr_pool_abort_get(native_pool);

  /* Box the return value */
  mrb_value return_value = TODO_mruby_box_apr_abortfunc_t(mrb, native_return_value);
  
  return return_value;
}
#endif
/* MRUBY_BINDING_END */

/* MRUBY_BINDING: apr_pool_abort_set */
/* sha: 40a87b2546cd93c612ca346d57e69380416d6c0b23b50cb4fa0496ebecce03e7 */
#if BIND_apr_pool_abort_set_FUNCTION
#define apr_pool_abort_set_REQUIRED_ARGC 2
#define apr_pool_abort_set_OPTIONAL_ARGC 0
/* void apr_pool_abort_set(apr_abortfunc_t abortfunc, apr_pool_t * pool) */
mrb_value
mrb_APR_apr_pool_abort_set(mrb_state* mrb, mrb_value self) {
  mrb_value abortfunc;
  mrb_value pool;

  /* Fetch the args */
  mrb_get_args(mrb, "oo", &abortfunc, &pool);

  /* Type checking */
  TODO_type_check_apr_abortfunc_t(abortfunc);
  if (!mrb_obj_is_kind_of(mrb, pool, AprPoolT_class(mrb))) {
    mrb_raise(mrb, E_TYPE_ERROR, "AprPoolT expected");
    return mrb_nil_value();
  }

  /* Unbox param: abortfunc */
  apr_abortfunc_t native_abortfunc = TODO_mruby_unbox_apr_abortfunc_t(abortfunc);

  /* Unbox param: pool */
  apr_pool_t * native_pool = (mrb_nil_p(pool) ? NULL : mruby_unbox_apr_pool_t(pool));

  /* Invocation */
  apr_pool_abort_set(native_abortfunc, native_pool);

  return mrb_nil_value();
}
#endif
/* MRUBY_BINDING_END */

/* MRUBY_BINDING: apr_pool_allocator_get */
/* sha: 608912e99c7b08729154364b655fffd40088c48968bc7d2dc5608af1ae035292 */
#if BIND_apr_pool_allocator_get_FUNCTION
#define apr_pool_allocator_get_REQUIRED_ARGC 1
#define apr_pool_allocator_get_OPTIONAL_ARGC 0
/* apr_allocator_t * apr_pool_allocator_get(apr_pool_t * pool) */
mrb_value
mrb_APR_apr_pool_allocator_get(mrb_state* mrb, mrb_value self) {
  mrb_value pool;

  /* Fetch the args */
  mrb_get_args(mrb, "o", &pool);

  /* Type checking */
  if (!mrb_obj_is_kind_of(mrb, pool, AprPoolT_class(mrb))) {
    mrb_raise(mrb, E_TYPE_ERROR, "AprPoolT expected");
    return mrb_nil_value();
  }

  /* Unbox param: pool */
  apr_pool_t * native_pool = (mrb_nil_p(pool) ? NULL : mruby_unbox_apr_pool_t(pool));

  /* Invocation */
  apr_allocator_t * native_return_value = apr_pool_allocator_get(native_pool);

  /* Box the return value */
  mrb_value return_value = TODO_mruby_box_apr_allocator_t_PTR(mrb, native_return_value);
  
  return return_value;
}
#endif
/* MRUBY_BINDING_END */

/* MRUBY_BINDING: apr_pool_child_cleanup_set */
/* sha: 012afa4ab11bd403f9cb62ca2abe7d43818cc14147584e40c05b70ad4615f3f4 */
#if BIND_apr_pool_child_cleanup_set_FUNCTION
#define apr_pool_child_cleanup_set_REQUIRED_ARGC 4
#define apr_pool_child_cleanup_set_OPTIONAL_ARGC 0
/* void apr_pool_child_cleanup_set(apr_pool_t * p, const void * data, apr_status_t (*)(void *) plain_cleanup, apr_status_t (*)(void *) child_cleanup) */
mrb_value
mrb_APR_apr_pool_child_cleanup_set(mrb_state* mrb, mrb_value self) {
  mrb_value p;
  mrb_value data;
  mrb_value plain_cleanup;
  mrb_value child_cleanup;

  /* Fetch the args */
  mrb_get_args(mrb, "oooo", &p, &data, &plain_cleanup, &child_cleanup);

  /* Type checking */
  if (!mrb_obj_is_kind_of(mrb, p, AprPoolT_class(mrb))) {
    mrb_raise(mrb, E_TYPE_ERROR, "AprPoolT expected");
    return mrb_nil_value();
  }
  TODO_type_check_void_PTR(data);
  TODO_type_check_apr_status_t_LPAREN_PTR_RPAREN_LPAREN_void_PTR_RPAREN(plain_cleanup);
  TODO_type_check_apr_status_t_LPAREN_PTR_RPAREN_LPAREN_void_PTR_RPAREN(child_cleanup);

  /* Unbox param: p */
  apr_pool_t * native_p = (mrb_nil_p(p) ? NULL : mruby_unbox_apr_pool_t(p));

  /* Unbox param: data */
  const void * native_data = TODO_mruby_unbox_void_PTR(data);

  /* Unbox param: plain_cleanup */
  apr_status_t (*native_plain_cleanup)(void *) = TODO_mruby_unbox_apr_status_t_LPAREN_PTR_RPAREN_LPAREN_void_PTR_RPAREN(plain_cleanup);

  /* Unbox param: child_cleanup */
  apr_status_t (*native_child_cleanup)(void *) = TODO_mruby_unbox_apr_status_t_LPAREN_PTR_RPAREN_LPAREN_void_PTR_RPAREN(child_cleanup);

  /* Invocation */
  apr_pool_child_cleanup_set(native_p, native_data, native_plain_cleanup, native_child_cleanup);

  return mrb_nil_value();
}
#endif
/* MRUBY_BINDING_END */

/* MRUBY_BINDING: apr_pool_cleanup_for_exec */
/* sha: 2ea19dd44e48f5c30a7d535cb73499877be4038b7f458ad0d3f233f70b33bea9 */
#if BIND_apr_pool_cleanup_for_exec_FUNCTION
#define apr_pool_cleanup_for_exec_REQUIRED_ARGC 0
#define apr_pool_cleanup_for_exec_OPTIONAL_ARGC 0
/* void apr_pool_cleanup_for_exec() */
mrb_value
mrb_APR_apr_pool_cleanup_for_exec(mrb_state* mrb, mrb_value self) {
  /* Invocation */
  apr_pool_cleanup_for_exec();

  return mrb_nil_value();
}
#endif
/* MRUBY_BINDING_END */

/* MRUBY_BINDING: apr_pool_cleanup_kill */
/* sha: 6fbb531f6e51a11cce6e429dcd36ae8273fb8e4f4e251b748e7b8c86b97d53c2 */
#if BIND_apr_pool_cleanup_kill_FUNCTION
#define apr_pool_cleanup_kill_REQUIRED_ARGC 3
#define apr_pool_cleanup_kill_OPTIONAL_ARGC 0
/* void apr_pool_cleanup_kill(apr_pool_t * p, const void * data, apr_status_t (*)(void *) cleanup) */
mrb_value
mrb_APR_apr_pool_cleanup_kill(mrb_state* mrb, mrb_value self) {
  mrb_value p;
  mrb_value data;
  mrb_value cleanup;

  /* Fetch the args */
  mrb_get_args(mrb, "ooo", &p, &data, &cleanup);

  /* Type checking */
  if (!mrb_obj_is_kind_of(mrb, p, AprPoolT_class(mrb))) {
    mrb_raise(mrb, E_TYPE_ERROR, "AprPoolT expected");
    return mrb_nil_value();
  }
  TODO_type_check_void_PTR(data);
  TODO_type_check_apr_status_t_LPAREN_PTR_RPAREN_LPAREN_void_PTR_RPAREN(cleanup);

  /* Unbox param: p */
  apr_pool_t * native_p = (mrb_nil_p(p) ? NULL : mruby_unbox_apr_pool_t(p));

  /* Unbox param: data */
  const void * native_data = TODO_mruby_unbox_void_PTR(data);

  /* Unbox param: cleanup */
  apr_status_t (*native_cleanup)(void *) = TODO_mruby_unbox_apr_status_t_LPAREN_PTR_RPAREN_LPAREN_void_PTR_RPAREN(cleanup);

  /* Invocation */
  apr_pool_cleanup_kill(native_p, native_data, native_cleanup);

  return mrb_nil_value();
}
#endif
/* MRUBY_BINDING_END */

/* MRUBY_BINDING: apr_pool_cleanup_null */
/* sha: 1c5ddec36984af63c4507cf95468290d627b38e05cfe51040952cb21f6548de5 */
#if BIND_apr_pool_cleanup_null_FUNCTION
#define apr_pool_cleanup_null_REQUIRED_ARGC 1
#define apr_pool_cleanup_null_OPTIONAL_ARGC 0
/* apr_status_t apr_pool_cleanup_null(void * data) */
mrb_value
mrb_APR_apr_pool_cleanup_null(mrb_state* mrb, mrb_value self) {
  mrb_value data;

  /* Fetch the args */
  mrb_get_args(mrb, "o", &data);

  /* Type checking */
  TODO_type_check_void_PTR(data);

  /* Unbox param: data */
  void * native_data = TODO_mruby_unbox_void_PTR(data);

  /* Invocation */
  apr_status_t native_return_value = apr_pool_cleanup_null(native_data);

  /* Box the return value */
  mrb_value return_value = mrb_fixnum_value(native_return_value);
  
  return return_value;
}
#endif
/* MRUBY_BINDING_END */

/* MRUBY_BINDING: apr_pool_cleanup_register */
/* sha: 5b5c625cc6e4c2c105b638a5d72f5df4344e5dcb567082b233e02ef137b3f444 */
#if BIND_apr_pool_cleanup_register_FUNCTION
#define apr_pool_cleanup_register_REQUIRED_ARGC 4
#define apr_pool_cleanup_register_OPTIONAL_ARGC 0
/* void apr_pool_cleanup_register(apr_pool_t * p, const void * data, apr_status_t (*)(void *) plain_cleanup, apr_status_t (*)(void *) child_cleanup) */
mrb_value
mrb_APR_apr_pool_cleanup_register(mrb_state* mrb, mrb_value self) {
  mrb_value p;
  mrb_value data;
  mrb_value plain_cleanup;
  mrb_value child_cleanup;

  /* Fetch the args */
  mrb_get_args(mrb, "oooo", &p, &data, &plain_cleanup, &child_cleanup);

  /* Type checking */
  if (!mrb_obj_is_kind_of(mrb, p, AprPoolT_class(mrb))) {
    mrb_raise(mrb, E_TYPE_ERROR, "AprPoolT expected");
    return mrb_nil_value();
  }
  TODO_type_check_void_PTR(data);
  TODO_type_check_apr_status_t_LPAREN_PTR_RPAREN_LPAREN_void_PTR_RPAREN(plain_cleanup);
  TODO_type_check_apr_status_t_LPAREN_PTR_RPAREN_LPAREN_void_PTR_RPAREN(child_cleanup);

  /* Unbox param: p */
  apr_pool_t * native_p = (mrb_nil_p(p) ? NULL : mruby_unbox_apr_pool_t(p));

  /* Unbox param: data */
  const void * native_data = TODO_mruby_unbox_void_PTR(data);

  /* Unbox param: plain_cleanup */
  apr_status_t (*native_plain_cleanup)(void *) = TODO_mruby_unbox_apr_status_t_LPAREN_PTR_RPAREN_LPAREN_void_PTR_RPAREN(plain_cleanup);

  /* Unbox param: child_cleanup */
  apr_status_t (*native_child_cleanup)(void *) = TODO_mruby_unbox_apr_status_t_LPAREN_PTR_RPAREN_LPAREN_void_PTR_RPAREN(child_cleanup);

  /* Invocation */
  apr_pool_cleanup_register(native_p, native_data, native_plain_cleanup, native_child_cleanup);

  return mrb_nil_value();
}
#endif
/* MRUBY_BINDING_END */

/* MRUBY_BINDING: apr_pool_cleanup_run */
/* sha: c67faa7f07fadccea9ca36ea7bf0fc1146c00c8b9263cab1a4549a4d0795a78d */
#if BIND_apr_pool_cleanup_run_FUNCTION
#define apr_pool_cleanup_run_REQUIRED_ARGC 3
#define apr_pool_cleanup_run_OPTIONAL_ARGC 0
/* apr_status_t apr_pool_cleanup_run(apr_pool_t * p, void * data, apr_status_t (*)(void *) cleanup) */
mrb_value
mrb_APR_apr_pool_cleanup_run(mrb_state* mrb, mrb_value self) {
  mrb_value p;
  mrb_value data;
  mrb_value cleanup;

  /* Fetch the args */
  mrb_get_args(mrb, "ooo", &p, &data, &cleanup);

  /* Type checking */
  if (!mrb_obj_is_kind_of(mrb, p, AprPoolT_class(mrb))) {
    mrb_raise(mrb, E_TYPE_ERROR, "AprPoolT expected");
    return mrb_nil_value();
  }
  TODO_type_check_void_PTR(data);
  TODO_type_check_apr_status_t_LPAREN_PTR_RPAREN_LPAREN_void_PTR_RPAREN(cleanup);

  /* Unbox param: p */
  apr_pool_t * native_p = (mrb_nil_p(p) ? NULL : mruby_unbox_apr_pool_t(p));

  /* Unbox param: data */
  void * native_data = TODO_mruby_unbox_void_PTR(data);

  /* Unbox param: cleanup */
  apr_status_t (*native_cleanup)(void *) = TODO_mruby_unbox_apr_status_t_LPAREN_PTR_RPAREN_LPAREN_void_PTR_RPAREN(cleanup);

  /* Invocation */
  apr_status_t native_return_value = apr_pool_cleanup_run(native_p, native_data, native_cleanup);

  /* Box the return value */
  mrb_value return_value = mrb_fixnum_value(native_return_value);
  
  return return_value;
}
#endif
/* MRUBY_BINDING_END */

/* MRUBY_BINDING: apr_pool_clear */
/* sha: user_edited */
#if BIND_apr_pool_clear_FUNCTION
#define apr_pool_clear_REQUIRED_ARGC 1
#define apr_pool_clear_OPTIONAL_ARGC 0
/* apr_pool_clear
 *
 * Parameters:
 * - p: apr_pool_t *
 * Return Type: void
 */
mrb_value
mrb_APR_apr_pool_clear(mrb_state* mrb, mrb_value self) {
  mrb_value p;

  /* Fetch the args */
  mrb_get_args(mrb, "o", &p);

  /* Type checking */
  if (!mrb_obj_is_kind_of(mrb, p, AprPoolT_class(mrb))) {
    mrb_raise(mrb, E_TYPE_ERROR, "AprPoolT expected");
    return mrb_nil_value();
  }

  /* Unbox parameters */
  apr_pool_t * native_p = (mrb_nil_p(p) ? NULL : mruby_unbox_apr_pool_t(p));

  /* Invocation */
  apr_pool_clear(native_p);

  return mrb_nil_value();
}
#endif
/* MRUBY_BINDING_END */

/* MRUBY_BINDING: apr_pool_clear_debug */
/* sha: fcfacf2d92ccd061ad91bdea420cea3c2e35b5422707504f10c7b527f34e4ca6 */
#if BIND_apr_pool_clear_debug_FUNCTION
#define apr_pool_clear_debug_REQUIRED_ARGC 2
#define apr_pool_clear_debug_OPTIONAL_ARGC 0
/* void apr_pool_clear_debug(apr_pool_t * p, const char * file_line) */
mrb_value
mrb_APR_apr_pool_clear_debug(mrb_state* mrb, mrb_value self) {
  mrb_value p;
  char * native_file_line = NULL;

  /* Fetch the args */
  mrb_get_args(mrb, "oz", &p, &native_file_line);

  /* Type checking */
  if (!mrb_obj_is_kind_of(mrb, p, AprPoolT_class(mrb))) {
    mrb_raise(mrb, E_TYPE_ERROR, "AprPoolT expected");
    return mrb_nil_value();
  }

  /* Unbox param: p */
  apr_pool_t * native_p = (mrb_nil_p(p) ? NULL : mruby_unbox_apr_pool_t(p));

  /* Invocation */
  apr_pool_clear_debug(native_p, native_file_line);

  return mrb_nil_value();
}
#endif
/* MRUBY_BINDING_END */

/* MRUBY_BINDING: apr_pool_create_core_ex */
/* sha: 7647ac4b1f816010594ffc9fb252381d18537d950b2b92459d3cb98e0826571b */
#if BIND_apr_pool_create_core_ex_FUNCTION
#define apr_pool_create_core_ex_REQUIRED_ARGC 3
#define apr_pool_create_core_ex_OPTIONAL_ARGC 0
/* apr_status_t apr_pool_create_core_ex(apr_pool_t ** newpool, apr_abortfunc_t abort_fn, apr_allocator_t * allocator) */
mrb_value
mrb_APR_apr_pool_create_core_ex(mrb_state* mrb, mrb_value self) {
  mrb_value newpool;
  mrb_value abort_fn;
  mrb_value allocator;

  /* Fetch the args */
  mrb_get_args(mrb, "ooo", &newpool, &abort_fn, &allocator);

  /* Type checking */
  TODO_type_check_apr_pool_t_PTR_PTR(newpool);
  TODO_type_check_apr_abortfunc_t(abort_fn);
  TODO_type_check_apr_allocator_t_PTR(allocator);

  /* Unbox param: newpool */
  apr_pool_t ** native_newpool = TODO_mruby_unbox_apr_pool_t_PTR_PTR(newpool);

  /* Unbox param: abort_fn */
  apr_abortfunc_t native_abort_fn = TODO_mruby_unbox_apr_abortfunc_t(abort_fn);

  /* Unbox param: allocator */
  apr_allocator_t * native_allocator = TODO_mruby_unbox_apr_allocator_t_PTR(allocator);

  /* Invocation */
  apr_status_t native_return_value = apr_pool_create_core_ex(native_newpool, native_abort_fn, native_allocator);

  /* Box the return value */
  mrb_value return_value = mrb_fixnum_value(native_return_value);
  
  return return_value;
}
#endif
/* MRUBY_BINDING_END */

/* MRUBY_BINDING: apr_pool_create_core_ex_debug */
/* sha: 99db37941352d30fdae30bb6d78ea807179249281399ec35d774ae098077ee47 */
#if BIND_apr_pool_create_core_ex_debug_FUNCTION
#define apr_pool_create_core_ex_debug_REQUIRED_ARGC 4
#define apr_pool_create_core_ex_debug_OPTIONAL_ARGC 0
/* apr_status_t apr_pool_create_core_ex_debug(apr_pool_t ** newpool, apr_abortfunc_t abort_fn, apr_allocator_t * allocator, const char * file_line) */
mrb_value
mrb_APR_apr_pool_create_core_ex_debug(mrb_state* mrb, mrb_value self) {
  mrb_value newpool;
  mrb_value abort_fn;
  mrb_value allocator;
  char * native_file_line = NULL;

  /* Fetch the args */
  mrb_get_args(mrb, "oooz", &newpool, &abort_fn, &allocator, &native_file_line);

  /* Type checking */
  TODO_type_check_apr_pool_t_PTR_PTR(newpool);
  TODO_type_check_apr_abortfunc_t(abort_fn);
  TODO_type_check_apr_allocator_t_PTR(allocator);

  /* Unbox param: newpool */
  apr_pool_t ** native_newpool = TODO_mruby_unbox_apr_pool_t_PTR_PTR(newpool);

  /* Unbox param: abort_fn */
  apr_abortfunc_t native_abort_fn = TODO_mruby_unbox_apr_abortfunc_t(abort_fn);

  /* Unbox param: allocator */
  apr_allocator_t * native_allocator = TODO_mruby_unbox_apr_allocator_t_PTR(allocator);

  /* Invocation */
  apr_status_t native_return_value = apr_pool_create_core_ex_debug(native_newpool, native_abort_fn, native_allocator, native_file_line);

  /* Box the return value */
  mrb_value return_value = mrb_fixnum_value(native_return_value);
  
  return return_value;
}
#endif
/* MRUBY_BINDING_END */

/* MRUBY_BINDING: apr_pool_create_ex */
/* sha: bd1fc5dcd9d08c8c5b1f0fba501ce3a772d1040d4a11236540d940942f07f989 */
#if BIND_apr_pool_create_ex_FUNCTION
#define apr_pool_create_ex_REQUIRED_ARGC 4
#define apr_pool_create_ex_OPTIONAL_ARGC 0
/* apr_status_t apr_pool_create_ex(apr_pool_t ** newpool, apr_pool_t * parent, apr_abortfunc_t abort_fn, apr_allocator_t * allocator) */
mrb_value
mrb_APR_apr_pool_create_ex(mrb_state* mrb, mrb_value self) {
  mrb_value newpool;
  mrb_value parent;
  mrb_value abort_fn;
  mrb_value allocator;

  /* Fetch the args */
  mrb_get_args(mrb, "oooo", &newpool, &parent, &abort_fn, &allocator);

  /* Type checking */
  TODO_type_check_apr_pool_t_PTR_PTR(newpool);
  if (!mrb_obj_is_kind_of(mrb, parent, AprPoolT_class(mrb))) {
    mrb_raise(mrb, E_TYPE_ERROR, "AprPoolT expected");
    return mrb_nil_value();
  }
  TODO_type_check_apr_abortfunc_t(abort_fn);
  TODO_type_check_apr_allocator_t_PTR(allocator);

  /* Unbox param: newpool */
  apr_pool_t ** native_newpool = TODO_mruby_unbox_apr_pool_t_PTR_PTR(newpool);

  /* Unbox param: parent */
  apr_pool_t * native_parent = (mrb_nil_p(parent) ? NULL : mruby_unbox_apr_pool_t(parent));

  /* Unbox param: abort_fn */
  apr_abortfunc_t native_abort_fn = TODO_mruby_unbox_apr_abortfunc_t(abort_fn);

  /* Unbox param: allocator */
  apr_allocator_t * native_allocator = TODO_mruby_unbox_apr_allocator_t_PTR(allocator);

  /* Invocation */
  apr_status_t native_return_value = apr_pool_create_ex(native_newpool, native_parent, native_abort_fn, native_allocator);

  /* Box the return value */
  mrb_value return_value = mrb_fixnum_value(native_return_value);
  
  return return_value;
}
#endif
/* MRUBY_BINDING_END */

/* MRUBY_BINDING: apr_pool_create_ex_debug */
/* sha: 4a46ba52a800772e611244198af58375e254e9ed8439905ca2f726755a0623ce */
#if BIND_apr_pool_create_ex_debug_FUNCTION
#define apr_pool_create_ex_debug_REQUIRED_ARGC 5
#define apr_pool_create_ex_debug_OPTIONAL_ARGC 0
/* apr_status_t apr_pool_create_ex_debug(apr_pool_t ** newpool, apr_pool_t * parent, apr_abortfunc_t abort_fn, apr_allocator_t * allocator, const char * file_line) */
mrb_value
mrb_APR_apr_pool_create_ex_debug(mrb_state* mrb, mrb_value self) {
  mrb_value newpool;
  mrb_value parent;
  mrb_value abort_fn;
  mrb_value allocator;
  char * native_file_line = NULL;

  /* Fetch the args */
  mrb_get_args(mrb, "ooooz", &newpool, &parent, &abort_fn, &allocator, &native_file_line);

  /* Type checking */
  TODO_type_check_apr_pool_t_PTR_PTR(newpool);
  if (!mrb_obj_is_kind_of(mrb, parent, AprPoolT_class(mrb))) {
    mrb_raise(mrb, E_TYPE_ERROR, "AprPoolT expected");
    return mrb_nil_value();
  }
  TODO_type_check_apr_abortfunc_t(abort_fn);
  TODO_type_check_apr_allocator_t_PTR(allocator);

  /* Unbox param: newpool */
  apr_pool_t ** native_newpool = TODO_mruby_unbox_apr_pool_t_PTR_PTR(newpool);

  /* Unbox param: parent */
  apr_pool_t * native_parent = (mrb_nil_p(parent) ? NULL : mruby_unbox_apr_pool_t(parent));

  /* Unbox param: abort_fn */
  apr_abortfunc_t native_abort_fn = TODO_mruby_unbox_apr_abortfunc_t(abort_fn);

  /* Unbox param: allocator */
  apr_allocator_t * native_allocator = TODO_mruby_unbox_apr_allocator_t_PTR(allocator);

  /* Invocation */
  apr_status_t native_return_value = apr_pool_create_ex_debug(native_newpool, native_parent, native_abort_fn, native_allocator, native_file_line);

  /* Box the return value */
  mrb_value return_value = mrb_fixnum_value(native_return_value);
  
  return return_value;
}
#endif
/* MRUBY_BINDING_END */

/* MRUBY_BINDING: apr_pool_create_unmanaged_ex */
/* sha: a6311e3be03a4ecfe9649fe4f0b61ac69e1084c0141725e3a12d01f88d8b39a2 */
#if BIND_apr_pool_create_unmanaged_ex_FUNCTION
#define apr_pool_create_unmanaged_ex_REQUIRED_ARGC 3
#define apr_pool_create_unmanaged_ex_OPTIONAL_ARGC 0
/* apr_status_t apr_pool_create_unmanaged_ex(apr_pool_t ** newpool, apr_abortfunc_t abort_fn, apr_allocator_t * allocator) */
mrb_value
mrb_APR_apr_pool_create_unmanaged_ex(mrb_state* mrb, mrb_value self) {
  mrb_value newpool;
  mrb_value abort_fn;
  mrb_value allocator;

  /* Fetch the args */
  mrb_get_args(mrb, "ooo", &newpool, &abort_fn, &allocator);

  /* Type checking */
  TODO_type_check_apr_pool_t_PTR_PTR(newpool);
  TODO_type_check_apr_abortfunc_t(abort_fn);
  TODO_type_check_apr_allocator_t_PTR(allocator);

  /* Unbox param: newpool */
  apr_pool_t ** native_newpool = TODO_mruby_unbox_apr_pool_t_PTR_PTR(newpool);

  /* Unbox param: abort_fn */
  apr_abortfunc_t native_abort_fn = TODO_mruby_unbox_apr_abortfunc_t(abort_fn);

  /* Unbox param: allocator */
  apr_allocator_t * native_allocator = TODO_mruby_unbox_apr_allocator_t_PTR(allocator);

  /* Invocation */
  apr_status_t native_return_value = apr_pool_create_unmanaged_ex(native_newpool, native_abort_fn, native_allocator);

  /* Box the return value */
  mrb_value return_value = mrb_fixnum_value(native_return_value);
  
  return return_value;
}
#endif
/* MRUBY_BINDING_END */

/* MRUBY_BINDING: apr_pool_create_unmanaged_ex_debug */
/* sha: 5ac815ea764fe3e9223add763940518155ca43a33d7eebca5b289ab48481f3ac */
#if BIND_apr_pool_create_unmanaged_ex_debug_FUNCTION
#define apr_pool_create_unmanaged_ex_debug_REQUIRED_ARGC 4
#define apr_pool_create_unmanaged_ex_debug_OPTIONAL_ARGC 0
/* apr_status_t apr_pool_create_unmanaged_ex_debug(apr_pool_t ** newpool, apr_abortfunc_t abort_fn, apr_allocator_t * allocator, const char * file_line) */
mrb_value
mrb_APR_apr_pool_create_unmanaged_ex_debug(mrb_state* mrb, mrb_value self) {
  mrb_value newpool;
  mrb_value abort_fn;
  mrb_value allocator;
  char * native_file_line = NULL;

  /* Fetch the args */
  mrb_get_args(mrb, "oooz", &newpool, &abort_fn, &allocator, &native_file_line);

  /* Type checking */
  TODO_type_check_apr_pool_t_PTR_PTR(newpool);
  TODO_type_check_apr_abortfunc_t(abort_fn);
  TODO_type_check_apr_allocator_t_PTR(allocator);

  /* Unbox param: newpool */
  apr_pool_t ** native_newpool = TODO_mruby_unbox_apr_pool_t_PTR_PTR(newpool);

  /* Unbox param: abort_fn */
  apr_abortfunc_t native_abort_fn = TODO_mruby_unbox_apr_abortfunc_t(abort_fn);

  /* Unbox param: allocator */
  apr_allocator_t * native_allocator = TODO_mruby_unbox_apr_allocator_t_PTR(allocator);

  /* Invocation */
  apr_status_t native_return_value = apr_pool_create_unmanaged_ex_debug(native_newpool, native_abort_fn, native_allocator, native_file_line);

  /* Box the return value */
  mrb_value return_value = mrb_fixnum_value(native_return_value);
  
  return return_value;
}
#endif
/* MRUBY_BINDING_END */

/* MRUBY_BINDING: apr_pool_destroy */
/* sha: user_edited */
#if BIND_apr_pool_destroy_FUNCTION
#define apr_pool_destroy_REQUIRED_ARGC 1
#define apr_pool_destroy_OPTIONAL_ARGC 0
/* apr_pool_destroy
 *
 * Parameters:
 * - p: apr_pool_t *
 * Return Type: void
 */
mrb_value
mrb_APR_apr_pool_destroy(mrb_state* mrb, mrb_value self) {
  mrb_value p;

  /* Fetch the args */
  mrb_get_args(mrb, "o", &p);

  /* Type checking */
  if (!mrb_obj_is_kind_of(mrb, p, AprPoolT_class(mrb))) {
    mrb_raise(mrb, E_TYPE_ERROR, "AprPoolT expected");
    return mrb_nil_value();
  }

  /* Unbox parameters */
  apr_pool_t * native_p = (mrb_nil_p(p) ? NULL : mruby_unbox_apr_pool_t(p));

  /* Invocation */
  apr_pool_destroy(native_p);

  return mrb_nil_value();
}
#endif
/* MRUBY_BINDING_END */

/* MRUBY_BINDING: apr_pool_destroy_debug */
/* sha: 5ec2256a61877bd1be498e78bc1b2fd7104f07ae82845da17392d41ef389ecf6 */
#if BIND_apr_pool_destroy_debug_FUNCTION
#define apr_pool_destroy_debug_REQUIRED_ARGC 2
#define apr_pool_destroy_debug_OPTIONAL_ARGC 0
/* void apr_pool_destroy_debug(apr_pool_t * p, const char * file_line) */
mrb_value
mrb_APR_apr_pool_destroy_debug(mrb_state* mrb, mrb_value self) {
  mrb_value p;
  char * native_file_line = NULL;

  /* Fetch the args */
  mrb_get_args(mrb, "oz", &p, &native_file_line);

  /* Type checking */
  if (!mrb_obj_is_kind_of(mrb, p, AprPoolT_class(mrb))) {
    mrb_raise(mrb, E_TYPE_ERROR, "AprPoolT expected");
    return mrb_nil_value();
  }

  /* Unbox param: p */
  apr_pool_t * native_p = (mrb_nil_p(p) ? NULL : mruby_unbox_apr_pool_t(p));

  /* Invocation */
  apr_pool_destroy_debug(native_p, native_file_line);

  return mrb_nil_value();
}
#endif
/* MRUBY_BINDING_END */

/* MRUBY_BINDING: apr_pool_initialize */
/* sha: b3cba50fe5340c21efa849d94b6d9291a70c52e82b67877f88dc5a04e28ac726 */
#if BIND_apr_pool_initialize_FUNCTION
#define apr_pool_initialize_REQUIRED_ARGC 0
#define apr_pool_initialize_OPTIONAL_ARGC 0
/* apr_status_t apr_pool_initialize() */
mrb_value
mrb_APR_apr_pool_initialize(mrb_state* mrb, mrb_value self) {
  /* Invocation */
  apr_status_t native_return_value = apr_pool_initialize();

  /* Box the return value */
  mrb_value return_value = mrb_fixnum_value(native_return_value);
  
  return return_value;
}
#endif
/* MRUBY_BINDING_END */

/* MRUBY_BINDING: apr_pool_is_ancestor */
/* sha: cc0127013f9f58d8acc09fa2ada8527386f9e1931f08976786b2abe971a88a15 */
#if BIND_apr_pool_is_ancestor_FUNCTION
#define apr_pool_is_ancestor_REQUIRED_ARGC 2
#define apr_pool_is_ancestor_OPTIONAL_ARGC 0
/* int apr_pool_is_ancestor(apr_pool_t * a, apr_pool_t * b) */
mrb_value
mrb_APR_apr_pool_is_ancestor(mrb_state* mrb, mrb_value self) {
  mrb_value a;
  mrb_value b;

  /* Fetch the args */
  mrb_get_args(mrb, "oo", &a, &b);

  /* Type checking */
  if (!mrb_obj_is_kind_of(mrb, a, AprPoolT_class(mrb))) {
    mrb_raise(mrb, E_TYPE_ERROR, "AprPoolT expected");
    return mrb_nil_value();
  }
  if (!mrb_obj_is_kind_of(mrb, b, AprPoolT_class(mrb))) {
    mrb_raise(mrb, E_TYPE_ERROR, "AprPoolT expected");
    return mrb_nil_value();
  }

  /* Unbox param: a */
  apr_pool_t * native_a = (mrb_nil_p(a) ? NULL : mruby_unbox_apr_pool_t(a));

  /* Unbox param: b */
  apr_pool_t * native_b = (mrb_nil_p(b) ? NULL : mruby_unbox_apr_pool_t(b));

  /* Invocation */
  int native_return_value = apr_pool_is_ancestor(native_a, native_b);

  /* Box the return value */
  mrb_value return_value = mrb_fixnum_value(native_return_value);
  
  return return_value;
}
#endif
/* MRUBY_BINDING_END */

/* MRUBY_BINDING: apr_pool_note_subprocess */
/* sha: 568a4b46bd7d8b51276b30fd98daa798257acc08e3bf6d7be2503bb9dec02507 */
#if BIND_apr_pool_note_subprocess_FUNCTION
#define apr_pool_note_subprocess_REQUIRED_ARGC 3
#define apr_pool_note_subprocess_OPTIONAL_ARGC 0
/* void apr_pool_note_subprocess(apr_pool_t * a, apr_proc_t * proc, apr_kill_conditions_e how) */
mrb_value
mrb_APR_apr_pool_note_subprocess(mrb_state* mrb, mrb_value self) {
  mrb_value a;
  mrb_value proc;
  mrb_int native_how;

  /* Fetch the args */
  mrb_get_args(mrb, "ooi", &a, &proc, &native_how);

  /* Type checking */
  if (!mrb_obj_is_kind_of(mrb, a, AprPoolT_class(mrb))) {
    mrb_raise(mrb, E_TYPE_ERROR, "AprPoolT expected");
    return mrb_nil_value();
  }
  if (!mrb_obj_is_kind_of(mrb, proc, AprProcT_class(mrb))) {
    mrb_raise(mrb, E_TYPE_ERROR, "AprProcT expected");
    return mrb_nil_value();
  }

  /* Unbox param: a */
  apr_pool_t * native_a = (mrb_nil_p(a) ? NULL : mruby_unbox_apr_pool_t(a));

  /* Unbox param: proc */
  apr_proc_t * native_proc = (mrb_nil_p(proc) ? NULL : mruby_unbox_apr_proc_t(proc));

  /* Invocation */
  apr_pool_note_subprocess(native_a, native_proc, native_how);

  return mrb_nil_value();
}
#endif
/* MRUBY_BINDING_END */

/* MRUBY_BINDING: apr_pool_parent_get */
/* sha: 9ab0fc3856b2e1df67e69e11141a9f074bb4bf21fcccfd285589734662fe461f */
#if BIND_apr_pool_parent_get_FUNCTION
#define apr_pool_parent_get_REQUIRED_ARGC 1
#define apr_pool_parent_get_OPTIONAL_ARGC 0
/* apr_pool_t * apr_pool_parent_get(apr_pool_t * pool) */
mrb_value
mrb_APR_apr_pool_parent_get(mrb_state* mrb, mrb_value self) {
  mrb_value pool;

  /* Fetch the args */
  mrb_get_args(mrb, "o", &pool);

  /* Type checking */
  if (!mrb_obj_is_kind_of(mrb, pool, AprPoolT_class(mrb))) {
    mrb_raise(mrb, E_TYPE_ERROR, "AprPoolT expected");
    return mrb_nil_value();
  }

  /* Unbox param: pool */
  apr_pool_t * native_pool = (mrb_nil_p(pool) ? NULL : mruby_unbox_apr_pool_t(pool));

  /* Invocation */
  apr_pool_t * native_return_value = apr_pool_parent_get(native_pool);

  /* Box the return value */
  mrb_value return_value = (native_return_value == NULL ? mrb_nil_value() : mruby_box_apr_pool_t(mrb, native_return_value));
  
  return return_value;
}
#endif
/* MRUBY_BINDING_END */

/* MRUBY_BINDING: apr_pool_pre_cleanup_register */
/* sha: d157bdb3803083152c4e9933ba7d5fc665a69140742ee155c358d39c5a45dcd8 */
#if BIND_apr_pool_pre_cleanup_register_FUNCTION
#define apr_pool_pre_cleanup_register_REQUIRED_ARGC 3
#define apr_pool_pre_cleanup_register_OPTIONAL_ARGC 0
/* void apr_pool_pre_cleanup_register(apr_pool_t * p, const void * data, apr_status_t (*)(void *) plain_cleanup) */
mrb_value
mrb_APR_apr_pool_pre_cleanup_register(mrb_state* mrb, mrb_value self) {
  mrb_value p;
  mrb_value data;
  mrb_value plain_cleanup;

  /* Fetch the args */
  mrb_get_args(mrb, "ooo", &p, &data, &plain_cleanup);

  /* Type checking */
  if (!mrb_obj_is_kind_of(mrb, p, AprPoolT_class(mrb))) {
    mrb_raise(mrb, E_TYPE_ERROR, "AprPoolT expected");
    return mrb_nil_value();
  }
  TODO_type_check_void_PTR(data);
  TODO_type_check_apr_status_t_LPAREN_PTR_RPAREN_LPAREN_void_PTR_RPAREN(plain_cleanup);

  /* Unbox param: p */
  apr_pool_t * native_p = (mrb_nil_p(p) ? NULL : mruby_unbox_apr_pool_t(p));

  /* Unbox param: data */
  const void * native_data = TODO_mruby_unbox_void_PTR(data);

  /* Unbox param: plain_cleanup */
  apr_status_t (*native_plain_cleanup)(void *) = TODO_mruby_unbox_apr_status_t_LPAREN_PTR_RPAREN_LPAREN_void_PTR_RPAREN(plain_cleanup);

  /* Invocation */
  apr_pool_pre_cleanup_register(native_p, native_data, native_plain_cleanup);

  return mrb_nil_value();
}
#endif
/* MRUBY_BINDING_END */

/* MRUBY_BINDING: apr_pool_tag */
/* sha: cca71f2f6e7b0672b7c07806c0a0169d5c475f37837c66241613438a116ef415 */
#if BIND_apr_pool_tag_FUNCTION
#define apr_pool_tag_REQUIRED_ARGC 2
#define apr_pool_tag_OPTIONAL_ARGC 0
/* void apr_pool_tag(apr_pool_t * pool, const char * tag) */
mrb_value
mrb_APR_apr_pool_tag(mrb_state* mrb, mrb_value self) {
  mrb_value pool;
  char * native_tag = NULL;

  /* Fetch the args */
  mrb_get_args(mrb, "oz", &pool, &native_tag);

  /* Type checking */
  if (!mrb_obj_is_kind_of(mrb, pool, AprPoolT_class(mrb))) {
    mrb_raise(mrb, E_TYPE_ERROR, "AprPoolT expected");
    return mrb_nil_value();
  }

  /* Unbox param: pool */
  apr_pool_t * native_pool = (mrb_nil_p(pool) ? NULL : mruby_unbox_apr_pool_t(pool));

  /* Invocation */
  apr_pool_tag(native_pool, native_tag);

  return mrb_nil_value();
}
#endif
/* MRUBY_BINDING_END */

/* MRUBY_BINDING: apr_pool_terminate */
/* sha: 67ccbe970030de7964254576c7fd660dc40e45dbde4a11207a146b8a05a4702a */
#if BIND_apr_pool_terminate_FUNCTION
#define apr_pool_terminate_REQUIRED_ARGC 0
#define apr_pool_terminate_OPTIONAL_ARGC 0
/* void apr_pool_terminate() */
mrb_value
mrb_APR_apr_pool_terminate(mrb_state* mrb, mrb_value self) {
  /* Invocation */
  apr_pool_terminate();

  return mrb_nil_value();
}
#endif
/* MRUBY_BINDING_END */

/* MRUBY_BINDING: apr_pool_userdata_get */
/* sha: 67ba5122094210c6249cd5af86d9fa1d8c6956e4c051aa653e75aa433f48a0c2 */
#if BIND_apr_pool_userdata_get_FUNCTION
#define apr_pool_userdata_get_REQUIRED_ARGC 3
#define apr_pool_userdata_get_OPTIONAL_ARGC 0
/* apr_status_t apr_pool_userdata_get(void ** data, const char * key, apr_pool_t * pool) */
mrb_value
mrb_APR_apr_pool_userdata_get(mrb_state* mrb, mrb_value self) {
  mrb_value data;
  char * native_key = NULL;
  mrb_value pool;

  /* Fetch the args */
  mrb_get_args(mrb, "ozo", &data, &native_key, &pool);

  /* Type checking */
  TODO_type_check_void_PTR_PTR(data);
  if (!mrb_obj_is_kind_of(mrb, pool, AprPoolT_class(mrb))) {
    mrb_raise(mrb, E_TYPE_ERROR, "AprPoolT expected");
    return mrb_nil_value();
  }

  /* Unbox param: data */
  void ** native_data = TODO_mruby_unbox_void_PTR_PTR(data);

  /* Unbox param: pool */
  apr_pool_t * native_pool = (mrb_nil_p(pool) ? NULL : mruby_unbox_apr_pool_t(pool));

  /* Invocation */
  apr_status_t native_return_value = apr_pool_userdata_get(native_data, native_key, native_pool);

  /* Box the return value */
  mrb_value return_value = mrb_fixnum_value(native_return_value);
  
  return return_value;
}
#endif
/* MRUBY_BINDING_END */

/* MRUBY_BINDING: apr_pool_userdata_set */
/* sha: 5be91ba5f6f365bd75c453e5d3f6efe63c3d5025ceb20f02283f0b96af751344 */
#if BIND_apr_pool_userdata_set_FUNCTION
#define apr_pool_userdata_set_REQUIRED_ARGC 4
#define apr_pool_userdata_set_OPTIONAL_ARGC 0
/* apr_status_t apr_pool_userdata_set(const void * data, const char * key, apr_status_t (*)(void *) cleanup, apr_pool_t * pool) */
mrb_value
mrb_APR_apr_pool_userdata_set(mrb_state* mrb, mrb_value self) {
  mrb_value data;
  char * native_key = NULL;
  mrb_value cleanup;
  mrb_value pool;

  /* Fetch the args */
  mrb_get_args(mrb, "ozoo", &data, &native_key, &cleanup, &pool);

  /* Type checking */
  TODO_type_check_void_PTR(data);
  TODO_type_check_apr_status_t_LPAREN_PTR_RPAREN_LPAREN_void_PTR_RPAREN(cleanup);
  if (!mrb_obj_is_kind_of(mrb, pool, AprPoolT_class(mrb))) {
    mrb_raise(mrb, E_TYPE_ERROR, "AprPoolT expected");
    return mrb_nil_value();
  }

  /* Unbox param: data */
  const void * native_data = TODO_mruby_unbox_void_PTR(data);

  /* Unbox param: cleanup */
  apr_status_t (*native_cleanup)(void *) = TODO_mruby_unbox_apr_status_t_LPAREN_PTR_RPAREN_LPAREN_void_PTR_RPAREN(cleanup);

  /* Unbox param: pool */
  apr_pool_t * native_pool = (mrb_nil_p(pool) ? NULL : mruby_unbox_apr_pool_t(pool));

  /* Invocation */
  apr_status_t native_return_value = apr_pool_userdata_set(native_data, native_key, native_cleanup, native_pool);

  /* Box the return value */
  mrb_value return_value = mrb_fixnum_value(native_return_value);
  
  return return_value;
}
#endif
/* MRUBY_BINDING_END */

/* MRUBY_BINDING: apr_pool_userdata_setn */
/* sha: e97fe1dcffff65c76aa293e0c65df64c78e0a0b27e7de0a9901734aef8ec82ea */
#if BIND_apr_pool_userdata_setn_FUNCTION
#define apr_pool_userdata_setn_REQUIRED_ARGC 4
#define apr_pool_userdata_setn_OPTIONAL_ARGC 0
/* apr_status_t apr_pool_userdata_setn(const void * data, const char * key, apr_status_t (*)(void *) cleanup, apr_pool_t * pool) */
mrb_value
mrb_APR_apr_pool_userdata_setn(mrb_state* mrb, mrb_value self) {
  mrb_value data;
  char * native_key = NULL;
  mrb_value cleanup;
  mrb_value pool;

  /* Fetch the args */
  mrb_get_args(mrb, "ozoo", &data, &native_key, &cleanup, &pool);

  /* Type checking */
  TODO_type_check_void_PTR(data);
  TODO_type_check_apr_status_t_LPAREN_PTR_RPAREN_LPAREN_void_PTR_RPAREN(cleanup);
  if (!mrb_obj_is_kind_of(mrb, pool, AprPoolT_class(mrb))) {
    mrb_raise(mrb, E_TYPE_ERROR, "AprPoolT expected");
    return mrb_nil_value();
  }

  /* Unbox param: data */
  const void * native_data = TODO_mruby_unbox_void_PTR(data);

  /* Unbox param: cleanup */
  apr_status_t (*native_cleanup)(void *) = TODO_mruby_unbox_apr_status_t_LPAREN_PTR_RPAREN_LPAREN_void_PTR_RPAREN(cleanup);

  /* Unbox param: pool */
  apr_pool_t * native_pool = (mrb_nil_p(pool) ? NULL : mruby_unbox_apr_pool_t(pool));

  /* Invocation */
  apr_status_t native_return_value = apr_pool_userdata_setn(native_data, native_key, native_cleanup, native_pool);

  /* Box the return value */
  mrb_value return_value = mrb_fixnum_value(native_return_value);
  
  return return_value;
}
#endif
/* MRUBY_BINDING_END */

/* MRUBY_BINDING: apr_proc_create */
/* sha: f5c3403537b9450ddf69c06e7cf1cee6238738da9be9ccedd0ac1e7a475acc0d */
#if BIND_apr_proc_create_FUNCTION
#define apr_proc_create_REQUIRED_ARGC 6
#define apr_proc_create_OPTIONAL_ARGC 0
/* apr_proc_create
 *
 * Parameters:
 * - progname: const char *
 * - args: const char *const *
 * - env: const char *const *
 * - attr: apr_procattr_t *
 * - pool: apr_pool_t *
 * Return Type: [Fixnum, AprProcT]
 */
mrb_value
mrb_APR_apr_proc_create(mrb_state* mrb, mrb_value self) {
  char * native_progname;
  mrb_value args;
  mrb_value env;
  mrb_value attr;
  mrb_value pool;

  /* Fetch the args */
  mrb_get_args(mrb, "zoooo", &native_progname, &args, &env, &attr, &pool);

  /* Type checking */
  if (!mrb_obj_is_kind_of(mrb, args, mrb->array_class) && !mrb_nil_p(args)) {
     mrb_raise(mrb, E_TYPE_ERROR, "Array expected");
     return mrb_nil_value();
  }
  if (!mrb_obj_is_kind_of(mrb, env, mrb->array_class) && !mrb_nil_p(env)) {
     mrb_raise(mrb, E_TYPE_ERROR, "Array expected");
     return mrb_nil_value();
  }
  if (!mrb_obj_is_kind_of(mrb, attr, AprProcattrT_class(mrb))) {
    mrb_raise(mrb, E_TYPE_ERROR, "AprProcattrT expected");
    return mrb_nil_value();
  }
  if (!mrb_obj_is_kind_of(mrb, pool, AprPoolT_class(mrb))) {
    mrb_raise(mrb, E_TYPE_ERROR, "AprPoolT expected");
    return mrb_nil_value();
  }

  /* Unbox parameters */

  const char ** native_args;
  if (mrb_nil_p(args)) {
    native_args = NULL;
  }
  else {
     int argc = mrb_ary_len(mrb, args);
     native_args = (const char**)malloc(sizeof(char*) * (argc + 1));
     for (int i = 0; i < argc; ++i) {
        mrb_value ruby_string = mrb_ary_entry(args, i);
        native_args[i] = mrb_string_value_cstr(mrb, &ruby_string);
     }
     native_args[argc] = NULL;
  }

  const char ** native_env;
  if (mrb_nil_p(env)) {
     native_env = NULL;
  }
  else {
     int envc = mrb_ary_len(mrb, env);
     native_env = (const char**)malloc(sizeof(char*) * (envc + 1));
     for (int i = 0; i < envc; ++i) {
        mrb_value ruby_string = mrb_ary_entry(env, i);
        native_env[i] = mrb_string_value_cstr(mrb, &ruby_string);
     }
     native_env[envc] = NULL;
  }

  apr_procattr_t * native_attr = (mrb_nil_p(attr) ? NULL : mruby_unbox_apr_procattr_t(attr));
  apr_pool_t * native_pool = (mrb_nil_p(pool) ? NULL : mruby_unbox_apr_pool_t(pool));

  /* Invocation */
  apr_proc_t* native_new_proc = (apr_proc_t*)malloc(sizeof(apr_proc_t));
  apr_status_t result = apr_proc_create(native_new_proc, native_progname, native_args, native_env, native_attr, native_pool);
  if (native_args != NULL) free(native_args);
  if (native_env != NULL) free(native_env);

  /* Box the return value */
  if (result > MRB_INT_MAX) {
    mrb_raise(mrb, mrb->eStandardError_class, "MRuby cannot represent integers greater than MRB_INT_MAX");
    return mrb_nil_value();
  }
  mrb_value return_value = mrb_fixnum_value(result);

  mrb_value results = mrb_ary_new(mrb);
  mrb_ary_push(mrb, results, return_value);
  if (result == 0) {
     mrb_ary_push(mrb, results, mruby_giftwrap_apr_proc_t(mrb, native_new_proc));
  }
  else {
     free(native_new_proc);
     mrb_ary_push(mrb, results, mrb_nil_value());
  }

  return results;
}
#endif
/* MRUBY_BINDING_END */

/* MRUBY_BINDING: apr_proc_detach */
/* sha: 8e04042a8ff354cd46906492557d00d8597489b696fded0e3864707f2ca02df6 */
#if BIND_apr_proc_detach_FUNCTION
#define apr_proc_detach_REQUIRED_ARGC 1
#define apr_proc_detach_OPTIONAL_ARGC 0
/* apr_status_t apr_proc_detach(int daemonize) */
mrb_value
mrb_APR_apr_proc_detach(mrb_state* mrb, mrb_value self) {
  mrb_int native_daemonize;

  /* Fetch the args */
  mrb_get_args(mrb, "i", &native_daemonize);

  /* Invocation */
  apr_status_t native_return_value = apr_proc_detach(native_daemonize);

  /* Box the return value */
  mrb_value return_value = mrb_fixnum_value(native_return_value);
  
  return return_value;
}
#endif
/* MRUBY_BINDING_END */

/* MRUBY_BINDING: apr_proc_fork */
/* sha: 73b213b492a0e4e4d2d4de5c68f2c05ddfa0a021057a4260ea64ea1d1d06f2ec */
#if BIND_apr_proc_fork_FUNCTION
#define apr_proc_fork_REQUIRED_ARGC 2
#define apr_proc_fork_OPTIONAL_ARGC 0
/* apr_status_t apr_proc_fork(apr_proc_t * proc, apr_pool_t * cont) */
mrb_value
mrb_APR_apr_proc_fork(mrb_state* mrb, mrb_value self) {
  mrb_value proc;
  mrb_value cont;

  /* Fetch the args */
  mrb_get_args(mrb, "oo", &proc, &cont);

  /* Type checking */
  if (!mrb_obj_is_kind_of(mrb, proc, AprProcT_class(mrb))) {
    mrb_raise(mrb, E_TYPE_ERROR, "AprProcT expected");
    return mrb_nil_value();
  }
  if (!mrb_obj_is_kind_of(mrb, cont, AprPoolT_class(mrb))) {
    mrb_raise(mrb, E_TYPE_ERROR, "AprPoolT expected");
    return mrb_nil_value();
  }

  /* Unbox param: proc */
  apr_proc_t * native_proc = (mrb_nil_p(proc) ? NULL : mruby_unbox_apr_proc_t(proc));

  /* Unbox param: cont */
  apr_pool_t * native_cont = (mrb_nil_p(cont) ? NULL : mruby_unbox_apr_pool_t(cont));

  /* Invocation */
  apr_status_t native_return_value = apr_proc_fork(native_proc, native_cont);

  /* Box the return value */
  mrb_value return_value = mrb_fixnum_value(native_return_value);
  
  return return_value;
}
#endif
/* MRUBY_BINDING_END */

/* MRUBY_BINDING: apr_proc_kill */
/* sha: f3b2e5e4e2c92f9700a5d25d7c3b988a8b4d3857969d0d993c59e17fd59fa813 */
#if BIND_apr_proc_kill_FUNCTION
#define apr_proc_kill_REQUIRED_ARGC 2
#define apr_proc_kill_OPTIONAL_ARGC 0
/* apr_status_t apr_proc_kill(apr_proc_t * proc, int sig) */
mrb_value
mrb_APR_apr_proc_kill(mrb_state* mrb, mrb_value self) {
  mrb_value proc;
  mrb_int native_sig;

  /* Fetch the args */
  mrb_get_args(mrb, "oi", &proc, &native_sig);

  /* Type checking */
  if (!mrb_obj_is_kind_of(mrb, proc, AprProcT_class(mrb))) {
    mrb_raise(mrb, E_TYPE_ERROR, "AprProcT expected");
    return mrb_nil_value();
  }

  /* Unbox param: proc */
  apr_proc_t * native_proc = (mrb_nil_p(proc) ? NULL : mruby_unbox_apr_proc_t(proc));

  /* Invocation */
  apr_status_t native_return_value = apr_proc_kill(native_proc, native_sig);

  /* Box the return value */
  mrb_value return_value = mrb_fixnum_value(native_return_value);
  
  return return_value;
}
#endif
/* MRUBY_BINDING_END */

/* MRUBY_BINDING: apr_proc_mutex_child_init */
/* sha: 5efcd091fe483ee5845a06a154e79cef4088d84d3325c4646536eb7a8611d4aa */
#if BIND_apr_proc_mutex_child_init_FUNCTION
#define apr_proc_mutex_child_init_REQUIRED_ARGC 3
#define apr_proc_mutex_child_init_OPTIONAL_ARGC 0
/* apr_status_t apr_proc_mutex_child_init(apr_proc_mutex_t ** mutex, const char * fname, apr_pool_t * pool) */
mrb_value
mrb_APR_apr_proc_mutex_child_init(mrb_state* mrb, mrb_value self) {
  mrb_value mutex;
  char * native_fname = NULL;
  mrb_value pool;

  /* Fetch the args */
  mrb_get_args(mrb, "ozo", &mutex, &native_fname, &pool);

  /* Type checking */
  TODO_type_check_apr_proc_mutex_t_PTR_PTR(mutex);
  if (!mrb_obj_is_kind_of(mrb, pool, AprPoolT_class(mrb))) {
    mrb_raise(mrb, E_TYPE_ERROR, "AprPoolT expected");
    return mrb_nil_value();
  }

  /* Unbox param: mutex */
  apr_proc_mutex_t ** native_mutex = TODO_mruby_unbox_apr_proc_mutex_t_PTR_PTR(mutex);

  /* Unbox param: pool */
  apr_pool_t * native_pool = (mrb_nil_p(pool) ? NULL : mruby_unbox_apr_pool_t(pool));

  /* Invocation */
  apr_status_t native_return_value = apr_proc_mutex_child_init(native_mutex, native_fname, native_pool);

  /* Box the return value */
  mrb_value return_value = mrb_fixnum_value(native_return_value);
  
  return return_value;
}
#endif
/* MRUBY_BINDING_END */

/* MRUBY_BINDING: apr_proc_mutex_cleanup */
/* sha: 29f57af137f4b4a947c60a2e6c15b049fbe99baad1e49b20e45527a2b8d480ed */
#if BIND_apr_proc_mutex_cleanup_FUNCTION
#define apr_proc_mutex_cleanup_REQUIRED_ARGC 1
#define apr_proc_mutex_cleanup_OPTIONAL_ARGC 0
/* apr_status_t apr_proc_mutex_cleanup(void * mutex) */
mrb_value
mrb_APR_apr_proc_mutex_cleanup(mrb_state* mrb, mrb_value self) {
  mrb_value mutex;

  /* Fetch the args */
  mrb_get_args(mrb, "o", &mutex);

  /* Type checking */
  TODO_type_check_void_PTR(mutex);

  /* Unbox param: mutex */
  void * native_mutex = TODO_mruby_unbox_void_PTR(mutex);

  /* Invocation */
  apr_status_t native_return_value = apr_proc_mutex_cleanup(native_mutex);

  /* Box the return value */
  mrb_value return_value = mrb_fixnum_value(native_return_value);
  
  return return_value;
}
#endif
/* MRUBY_BINDING_END */

/* MRUBY_BINDING: apr_proc_mutex_create */
/* sha: 087d0227f10b78507fa890b581a1414112675c904b9a5a3d82dca2143589ae4a */
#if BIND_apr_proc_mutex_create_FUNCTION
#define apr_proc_mutex_create_REQUIRED_ARGC 4
#define apr_proc_mutex_create_OPTIONAL_ARGC 0
/* apr_status_t apr_proc_mutex_create(apr_proc_mutex_t ** mutex, const char * fname, apr_lockmech_e mech, apr_pool_t * pool) */
mrb_value
mrb_APR_apr_proc_mutex_create(mrb_state* mrb, mrb_value self) {
  mrb_value mutex;
  char * native_fname = NULL;
  mrb_int native_mech;
  mrb_value pool;

  /* Fetch the args */
  mrb_get_args(mrb, "ozio", &mutex, &native_fname, &native_mech, &pool);

  /* Type checking */
  TODO_type_check_apr_proc_mutex_t_PTR_PTR(mutex);
  if (!mrb_obj_is_kind_of(mrb, pool, AprPoolT_class(mrb))) {
    mrb_raise(mrb, E_TYPE_ERROR, "AprPoolT expected");
    return mrb_nil_value();
  }

  /* Unbox param: mutex */
  apr_proc_mutex_t ** native_mutex = TODO_mruby_unbox_apr_proc_mutex_t_PTR_PTR(mutex);

  /* Unbox param: pool */
  apr_pool_t * native_pool = (mrb_nil_p(pool) ? NULL : mruby_unbox_apr_pool_t(pool));

  /* Invocation */
  apr_status_t native_return_value = apr_proc_mutex_create(native_mutex, native_fname, native_mech, native_pool);

  /* Box the return value */
  mrb_value return_value = mrb_fixnum_value(native_return_value);
  
  return return_value;
}
#endif
/* MRUBY_BINDING_END */

/* MRUBY_BINDING: apr_proc_mutex_defname */
/* sha: 841ef66980a8b195790dedb2cd679ebd4ff0700f1e1c3517828295a4f21ef7ee */
#if BIND_apr_proc_mutex_defname_FUNCTION
#define apr_proc_mutex_defname_REQUIRED_ARGC 0
#define apr_proc_mutex_defname_OPTIONAL_ARGC 0
/* const char * apr_proc_mutex_defname() */
mrb_value
mrb_APR_apr_proc_mutex_defname(mrb_state* mrb, mrb_value self) {
  /* Invocation */
  const char * native_return_value = apr_proc_mutex_defname();

  /* Box the return value */
  mrb_value return_value = native_return_value == NULL ? mrb_nil_value() : mrb_str_new_cstr(mrb, native_return_value);
  
  return return_value;
}
#endif
/* MRUBY_BINDING_END */

/* MRUBY_BINDING: apr_proc_mutex_destroy */
/* sha: 38f002ff480a2cb5c5d0e1876c0c847683ffe201cd6aa0b5bd5d1f1dbdf65334 */
#if BIND_apr_proc_mutex_destroy_FUNCTION
#define apr_proc_mutex_destroy_REQUIRED_ARGC 1
#define apr_proc_mutex_destroy_OPTIONAL_ARGC 0
/* apr_status_t apr_proc_mutex_destroy(apr_proc_mutex_t * mutex) */
mrb_value
mrb_APR_apr_proc_mutex_destroy(mrb_state* mrb, mrb_value self) {
  mrb_value mutex;

  /* Fetch the args */
  mrb_get_args(mrb, "o", &mutex);

  /* Type checking */
  if (!mrb_obj_is_kind_of(mrb, mutex, AprProcMutexT_class(mrb))) {
    mrb_raise(mrb, E_TYPE_ERROR, "AprProcMutexT expected");
    return mrb_nil_value();
  }

  /* Unbox param: mutex */
  apr_proc_mutex_t * native_mutex = (mrb_nil_p(mutex) ? NULL : mruby_unbox_apr_proc_mutex_t(mutex));

  /* Invocation */
  apr_status_t native_return_value = apr_proc_mutex_destroy(native_mutex);

  /* Box the return value */
  mrb_value return_value = mrb_fixnum_value(native_return_value);
  
  return return_value;
}
#endif
/* MRUBY_BINDING_END */

/* MRUBY_BINDING: apr_proc_mutex_lock */
/* sha: 06945b3338ba3c5088f7568fb3536781a77811f6148cc48490f6e4f18ac8d488 */
#if BIND_apr_proc_mutex_lock_FUNCTION
#define apr_proc_mutex_lock_REQUIRED_ARGC 1
#define apr_proc_mutex_lock_OPTIONAL_ARGC 0
/* apr_status_t apr_proc_mutex_lock(apr_proc_mutex_t * mutex) */
mrb_value
mrb_APR_apr_proc_mutex_lock(mrb_state* mrb, mrb_value self) {
  mrb_value mutex;

  /* Fetch the args */
  mrb_get_args(mrb, "o", &mutex);

  /* Type checking */
  if (!mrb_obj_is_kind_of(mrb, mutex, AprProcMutexT_class(mrb))) {
    mrb_raise(mrb, E_TYPE_ERROR, "AprProcMutexT expected");
    return mrb_nil_value();
  }

  /* Unbox param: mutex */
  apr_proc_mutex_t * native_mutex = (mrb_nil_p(mutex) ? NULL : mruby_unbox_apr_proc_mutex_t(mutex));

  /* Invocation */
  apr_status_t native_return_value = apr_proc_mutex_lock(native_mutex);

  /* Box the return value */
  mrb_value return_value = mrb_fixnum_value(native_return_value);
  
  return return_value;
}
#endif
/* MRUBY_BINDING_END */

/* MRUBY_BINDING: apr_proc_mutex_lockfile */
/* sha: 0d7ef153851066ea9db553864b6a5a6a112aba9202d9c6d299645ffca1de3237 */
#if BIND_apr_proc_mutex_lockfile_FUNCTION
#define apr_proc_mutex_lockfile_REQUIRED_ARGC 1
#define apr_proc_mutex_lockfile_OPTIONAL_ARGC 0
/* const char * apr_proc_mutex_lockfile(apr_proc_mutex_t * mutex) */
mrb_value
mrb_APR_apr_proc_mutex_lockfile(mrb_state* mrb, mrb_value self) {
  mrb_value mutex;

  /* Fetch the args */
  mrb_get_args(mrb, "o", &mutex);

  /* Type checking */
  if (!mrb_obj_is_kind_of(mrb, mutex, AprProcMutexT_class(mrb))) {
    mrb_raise(mrb, E_TYPE_ERROR, "AprProcMutexT expected");
    return mrb_nil_value();
  }

  /* Unbox param: mutex */
  apr_proc_mutex_t * native_mutex = (mrb_nil_p(mutex) ? NULL : mruby_unbox_apr_proc_mutex_t(mutex));

  /* Invocation */
  const char * native_return_value = apr_proc_mutex_lockfile(native_mutex);

  /* Box the return value */
  mrb_value return_value = native_return_value == NULL ? mrb_nil_value() : mrb_str_new_cstr(mrb, native_return_value);
  
  return return_value;
}
#endif
/* MRUBY_BINDING_END */

/* MRUBY_BINDING: apr_proc_mutex_name */
/* sha: 878615c22a0df0e8d8eb7dabecb1bc6a96b2d583cb4820867d1f3feaf05e05e7 */
#if BIND_apr_proc_mutex_name_FUNCTION
#define apr_proc_mutex_name_REQUIRED_ARGC 1
#define apr_proc_mutex_name_OPTIONAL_ARGC 0
/* const char * apr_proc_mutex_name(apr_proc_mutex_t * mutex) */
mrb_value
mrb_APR_apr_proc_mutex_name(mrb_state* mrb, mrb_value self) {
  mrb_value mutex;

  /* Fetch the args */
  mrb_get_args(mrb, "o", &mutex);

  /* Type checking */
  if (!mrb_obj_is_kind_of(mrb, mutex, AprProcMutexT_class(mrb))) {
    mrb_raise(mrb, E_TYPE_ERROR, "AprProcMutexT expected");
    return mrb_nil_value();
  }

  /* Unbox param: mutex */
  apr_proc_mutex_t * native_mutex = (mrb_nil_p(mutex) ? NULL : mruby_unbox_apr_proc_mutex_t(mutex));

  /* Invocation */
  const char * native_return_value = apr_proc_mutex_name(native_mutex);

  /* Box the return value */
  mrb_value return_value = native_return_value == NULL ? mrb_nil_value() : mrb_str_new_cstr(mrb, native_return_value);
  
  return return_value;
}
#endif
/* MRUBY_BINDING_END */

/* MRUBY_BINDING: apr_proc_mutex_trylock */
/* sha: 52b16baf36d0cef243f852eee4773652c04aa02385b98ed21e8dc98f6f9e0993 */
#if BIND_apr_proc_mutex_trylock_FUNCTION
#define apr_proc_mutex_trylock_REQUIRED_ARGC 1
#define apr_proc_mutex_trylock_OPTIONAL_ARGC 0
/* apr_status_t apr_proc_mutex_trylock(apr_proc_mutex_t * mutex) */
mrb_value
mrb_APR_apr_proc_mutex_trylock(mrb_state* mrb, mrb_value self) {
  mrb_value mutex;

  /* Fetch the args */
  mrb_get_args(mrb, "o", &mutex);

  /* Type checking */
  if (!mrb_obj_is_kind_of(mrb, mutex, AprProcMutexT_class(mrb))) {
    mrb_raise(mrb, E_TYPE_ERROR, "AprProcMutexT expected");
    return mrb_nil_value();
  }

  /* Unbox param: mutex */
  apr_proc_mutex_t * native_mutex = (mrb_nil_p(mutex) ? NULL : mruby_unbox_apr_proc_mutex_t(mutex));

  /* Invocation */
  apr_status_t native_return_value = apr_proc_mutex_trylock(native_mutex);

  /* Box the return value */
  mrb_value return_value = mrb_fixnum_value(native_return_value);
  
  return return_value;
}
#endif
/* MRUBY_BINDING_END */

/* MRUBY_BINDING: apr_proc_mutex_unlock */
/* sha: 657f309a3a0b3715c7b522fa118f0b973d23e08f64744c1c12ec23be84d3866a */
#if BIND_apr_proc_mutex_unlock_FUNCTION
#define apr_proc_mutex_unlock_REQUIRED_ARGC 1
#define apr_proc_mutex_unlock_OPTIONAL_ARGC 0
/* apr_status_t apr_proc_mutex_unlock(apr_proc_mutex_t * mutex) */
mrb_value
mrb_APR_apr_proc_mutex_unlock(mrb_state* mrb, mrb_value self) {
  mrb_value mutex;

  /* Fetch the args */
  mrb_get_args(mrb, "o", &mutex);

  /* Type checking */
  if (!mrb_obj_is_kind_of(mrb, mutex, AprProcMutexT_class(mrb))) {
    mrb_raise(mrb, E_TYPE_ERROR, "AprProcMutexT expected");
    return mrb_nil_value();
  }

  /* Unbox param: mutex */
  apr_proc_mutex_t * native_mutex = (mrb_nil_p(mutex) ? NULL : mruby_unbox_apr_proc_mutex_t(mutex));

  /* Invocation */
  apr_status_t native_return_value = apr_proc_mutex_unlock(native_mutex);

  /* Box the return value */
  mrb_value return_value = mrb_fixnum_value(native_return_value);
  
  return return_value;
}
#endif
/* MRUBY_BINDING_END */

/* MRUBY_BINDING: apr_proc_other_child_alert */
/* sha: 32d83ff9440e545f8e1b9b427a3f5e09cdca870947c18b153dd4be0bc015674e */
#if BIND_apr_proc_other_child_alert_FUNCTION
#define apr_proc_other_child_alert_REQUIRED_ARGC 3
#define apr_proc_other_child_alert_OPTIONAL_ARGC 0
/* apr_status_t apr_proc_other_child_alert(apr_proc_t * proc, int reason, int status) */
mrb_value
mrb_APR_apr_proc_other_child_alert(mrb_state* mrb, mrb_value self) {
  mrb_value proc;
  mrb_int native_reason;
  mrb_int native_status;

  /* Fetch the args */
  mrb_get_args(mrb, "oii", &proc, &native_reason, &native_status);

  /* Type checking */
  if (!mrb_obj_is_kind_of(mrb, proc, AprProcT_class(mrb))) {
    mrb_raise(mrb, E_TYPE_ERROR, "AprProcT expected");
    return mrb_nil_value();
  }

  /* Unbox param: proc */
  apr_proc_t * native_proc = (mrb_nil_p(proc) ? NULL : mruby_unbox_apr_proc_t(proc));

  /* Invocation */
  apr_status_t native_return_value = apr_proc_other_child_alert(native_proc, native_reason, native_status);

  /* Box the return value */
  mrb_value return_value = mrb_fixnum_value(native_return_value);
  
  return return_value;
}
#endif
/* MRUBY_BINDING_END */

/* MRUBY_BINDING: apr_proc_other_child_refresh */
/* sha: 5e20d0382c0069d5148e898ce2bd7fcb2d35dcfcd2c6f9292c1f03cef25c2eef */
#if BIND_apr_proc_other_child_refresh_FUNCTION
#define apr_proc_other_child_refresh_REQUIRED_ARGC 2
#define apr_proc_other_child_refresh_OPTIONAL_ARGC 0
/* void apr_proc_other_child_refresh(apr_other_child_rec_t * ocr, int reason) */
mrb_value
mrb_APR_apr_proc_other_child_refresh(mrb_state* mrb, mrb_value self) {
  mrb_value ocr;
  mrb_int native_reason;

  /* Fetch the args */
  mrb_get_args(mrb, "oi", &ocr, &native_reason);

  /* Type checking */
  if (!mrb_obj_is_kind_of(mrb, ocr, AprOtherChildRecT_class(mrb))) {
    mrb_raise(mrb, E_TYPE_ERROR, "AprOtherChildRecT expected");
    return mrb_nil_value();
  }

  /* Unbox param: ocr */
  apr_other_child_rec_t * native_ocr = (mrb_nil_p(ocr) ? NULL : mruby_unbox_apr_other_child_rec_t(ocr));

  /* Invocation */
  apr_proc_other_child_refresh(native_ocr, native_reason);

  return mrb_nil_value();
}
#endif
/* MRUBY_BINDING_END */

/* MRUBY_BINDING: apr_proc_other_child_refresh_all */
/* sha: 550c76eaa29ee4537bdbb6a8d4d22b068141687ac0725112d321b8ef97b0392f */
#if BIND_apr_proc_other_child_refresh_all_FUNCTION
#define apr_proc_other_child_refresh_all_REQUIRED_ARGC 1
#define apr_proc_other_child_refresh_all_OPTIONAL_ARGC 0
/* void apr_proc_other_child_refresh_all(int reason) */
mrb_value
mrb_APR_apr_proc_other_child_refresh_all(mrb_state* mrb, mrb_value self) {
  mrb_int native_reason;

  /* Fetch the args */
  mrb_get_args(mrb, "i", &native_reason);

  /* Invocation */
  apr_proc_other_child_refresh_all(native_reason);

  return mrb_nil_value();
}
#endif
/* MRUBY_BINDING_END */

/* MRUBY_BINDING: apr_proc_other_child_register */
/* sha: b9a97872173516ea1f2eadf3a8de003082a4e117461bd11251074b3bbd2426a0 */
#if BIND_apr_proc_other_child_register_FUNCTION
#define apr_proc_other_child_register_REQUIRED_ARGC 5
#define apr_proc_other_child_register_OPTIONAL_ARGC 0
/* void apr_proc_other_child_register(apr_proc_t * proc, void (*)(int, void *, int) maintenance, void * data, apr_file_t * write_fd, apr_pool_t * p) */
mrb_value
mrb_APR_apr_proc_other_child_register(mrb_state* mrb, mrb_value self) {
  mrb_value proc;
  mrb_value maintenance;
  mrb_value data;
  mrb_value write_fd;
  mrb_value p;

  /* Fetch the args */
  mrb_get_args(mrb, "ooooo", &proc, &maintenance, &data, &write_fd, &p);

  /* Type checking */
  if (!mrb_obj_is_kind_of(mrb, proc, AprProcT_class(mrb))) {
    mrb_raise(mrb, E_TYPE_ERROR, "AprProcT expected");
    return mrb_nil_value();
  }
  TODO_type_check_void_LPAREN_PTR_RPAREN_LPAREN_intCOMMA_void_PTR_COMMA_int_RPAREN(maintenance);
  TODO_type_check_void_PTR(data);
  if (!mrb_obj_is_kind_of(mrb, write_fd, AprFileT_class(mrb))) {
    mrb_raise(mrb, E_TYPE_ERROR, "AprFileT expected");
    return mrb_nil_value();
  }
  if (!mrb_obj_is_kind_of(mrb, p, AprPoolT_class(mrb))) {
    mrb_raise(mrb, E_TYPE_ERROR, "AprPoolT expected");
    return mrb_nil_value();
  }

  /* Unbox param: proc */
  apr_proc_t * native_proc = (mrb_nil_p(proc) ? NULL : mruby_unbox_apr_proc_t(proc));

  /* Unbox param: maintenance */
  void (*native_maintenance)(int, void *, int) = TODO_mruby_unbox_void_LPAREN_PTR_RPAREN_LPAREN_intCOMMA_void_PTR_COMMA_int_RPAREN(maintenance);

  /* Unbox param: data */
  void * native_data = TODO_mruby_unbox_void_PTR(data);

  /* Unbox param: write_fd */
  apr_file_t * native_write_fd = (mrb_nil_p(write_fd) ? NULL : mruby_unbox_apr_file_t(write_fd));

  /* Unbox param: p */
  apr_pool_t * native_p = (mrb_nil_p(p) ? NULL : mruby_unbox_apr_pool_t(p));

  /* Invocation */
  apr_proc_other_child_register(native_proc, native_maintenance, native_data, native_write_fd, native_p);

  return mrb_nil_value();
}
#endif
/* MRUBY_BINDING_END */

/* MRUBY_BINDING: apr_proc_other_child_unregister */
/* sha: b1c4f432cd0a3518d632766d0b6bb23b28b21daab5990a92b25d028417d75ac8 */
#if BIND_apr_proc_other_child_unregister_FUNCTION
#define apr_proc_other_child_unregister_REQUIRED_ARGC 1
#define apr_proc_other_child_unregister_OPTIONAL_ARGC 0
/* void apr_proc_other_child_unregister(void * data) */
mrb_value
mrb_APR_apr_proc_other_child_unregister(mrb_state* mrb, mrb_value self) {
  mrb_value data;

  /* Fetch the args */
  mrb_get_args(mrb, "o", &data);

  /* Type checking */
  TODO_type_check_void_PTR(data);

  /* Unbox param: data */
  void * native_data = TODO_mruby_unbox_void_PTR(data);

  /* Invocation */
  apr_proc_other_child_unregister(native_data);

  return mrb_nil_value();
}
#endif
/* MRUBY_BINDING_END */

/* MRUBY_BINDING: apr_proc_wait */
/* sha: 99890aa72087837ef4a28043f4835c9444faf26c0bb8980e30e05e038d081a20 */
#if BIND_apr_proc_wait_FUNCTION
#define apr_proc_wait_REQUIRED_ARGC 4
#define apr_proc_wait_OPTIONAL_ARGC 0
/* apr_proc_wait
 *
 * Parameters:
 * - proc: apr_proc_t *
 * - waithow: apr_wait_how_e
 * Return Type: [errno: Fixnum, exitcode: Fixnum, exitwhy: Fixnum]
 */
mrb_value
mrb_APR_apr_proc_wait(mrb_state* mrb, mrb_value self) {
  mrb_value proc;
  mrb_int native_waithow;

  /* Fetch the args */
  mrb_get_args(mrb, "oi", &proc, &native_waithow);

  /* Type checking */
  if (!mrb_obj_is_kind_of(mrb, proc, AprProcT_class(mrb))) {
    mrb_raise(mrb, E_TYPE_ERROR, "AprProcT expected");
    return mrb_nil_value();
  }

  /* Unbox parameters */
  apr_proc_t * native_proc = (mrb_nil_p(proc) ? NULL : mruby_unbox_apr_proc_t(proc));

  /* Invocation */
  int native_exitcode;
  apr_exit_why_e native_exitwhy;
  apr_status_t result = apr_proc_wait(native_proc, &native_exitcode, &native_exitwhy, native_waithow);

  /* Box the return value */
  if (result > MRB_INT_MAX) {
    mrb_raise(mrb, mrb->eStandardError_class, "MRuby cannot represent integers greater than MRB_INT_MAX");
    return mrb_nil_value();
  }

  mrb_value results = mrb_ary_new(mrb);
  mrb_ary_push(mrb, results, mrb_fixnum_value(result));
  if (result == APR_CHILD_DONE) {
     mrb_ary_push(mrb, results, mrb_fixnum_value(native_exitcode));
     mrb_ary_push(mrb, results, mrb_fixnum_value(native_exitwhy));
  }
  else {
     mrb_ary_push(mrb, results, mrb_nil_value());
     mrb_ary_push(mrb, results, mrb_nil_value());
  }

  return results;
}
#endif
/* MRUBY_BINDING_END */

/* MRUBY_BINDING: apr_proc_wait_all_procs */
/* sha: c1a81a267f1745439ea904682488537c27805cdc13c5fe70c09657372e639ece */
#if BIND_apr_proc_wait_all_procs_FUNCTION
#define apr_proc_wait_all_procs_REQUIRED_ARGC 5
#define apr_proc_wait_all_procs_OPTIONAL_ARGC 0
/* apr_status_t apr_proc_wait_all_procs(apr_proc_t * proc, int * exitcode, apr_exit_why_e * exitwhy, apr_wait_how_e waithow, apr_pool_t * p) */
mrb_value
mrb_APR_apr_proc_wait_all_procs(mrb_state* mrb, mrb_value self) {
  mrb_value proc;
  mrb_value exitcode;
  mrb_value exitwhy;
  mrb_int native_waithow;
  mrb_value p;

  /* Fetch the args */
  mrb_get_args(mrb, "oooio", &proc, &exitcode, &exitwhy, &native_waithow, &p);

  /* Type checking */
  if (!mrb_obj_is_kind_of(mrb, proc, AprProcT_class(mrb))) {
    mrb_raise(mrb, E_TYPE_ERROR, "AprProcT expected");
    return mrb_nil_value();
  }
  TODO_type_check_int_PTR(exitcode);
  TODO_type_check_apr_exit_why_e_PTR(exitwhy);
  if (!mrb_obj_is_kind_of(mrb, p, AprPoolT_class(mrb))) {
    mrb_raise(mrb, E_TYPE_ERROR, "AprPoolT expected");
    return mrb_nil_value();
  }

  /* Unbox param: proc */
  apr_proc_t * native_proc = (mrb_nil_p(proc) ? NULL : mruby_unbox_apr_proc_t(proc));

  /* Unbox param: exitcode */
  int * native_exitcode = TODO_mruby_unbox_int_PTR(exitcode);

  /* Unbox param: exitwhy */
  apr_exit_why_e * native_exitwhy = TODO_mruby_unbox_apr_exit_why_e_PTR(exitwhy);

  /* Unbox param: p */
  apr_pool_t * native_p = (mrb_nil_p(p) ? NULL : mruby_unbox_apr_pool_t(p));

  /* Invocation */
  apr_status_t native_return_value = apr_proc_wait_all_procs(native_proc, native_exitcode, native_exitwhy, native_waithow, native_p);

  /* Box the return value */
  mrb_value return_value = mrb_fixnum_value(native_return_value);
  
  return return_value;
}
#endif
/* MRUBY_BINDING_END */

/* MRUBY_BINDING: apr_procattr_addrspace_set */
/* sha: f74c4e74190b70cd7f7d9eba2f6d0b553ee64a7e0df38809a17fae38714bfc63 */
#if BIND_apr_procattr_addrspace_set_FUNCTION
#define apr_procattr_addrspace_set_REQUIRED_ARGC 2
#define apr_procattr_addrspace_set_OPTIONAL_ARGC 0
/* apr_status_t apr_procattr_addrspace_set(apr_procattr_t * attr, apr_int32_t addrspace) */
mrb_value
mrb_APR_apr_procattr_addrspace_set(mrb_state* mrb, mrb_value self) {
  mrb_value attr;
  mrb_int native_addrspace;

  /* Fetch the args */
  mrb_get_args(mrb, "oi", &attr, &native_addrspace);

  /* Type checking */
  if (!mrb_obj_is_kind_of(mrb, attr, AprProcattrT_class(mrb))) {
    mrb_raise(mrb, E_TYPE_ERROR, "AprProcattrT expected");
    return mrb_nil_value();
  }

  /* Unbox param: attr */
  apr_procattr_t * native_attr = (mrb_nil_p(attr) ? NULL : mruby_unbox_apr_procattr_t(attr));

  /* Invocation */
  apr_status_t native_return_value = apr_procattr_addrspace_set(native_attr, native_addrspace);

  /* Box the return value */
  mrb_value return_value = mrb_fixnum_value(native_return_value);
  
  return return_value;
}
#endif
/* MRUBY_BINDING_END */

/* MRUBY_BINDING: apr_procattr_child_err_set */
/* sha: b5571d591b5d08f7d0e77dbc277304c06606e15e86e1bcd3e787cf3ddf2593f5 */
#if BIND_apr_procattr_child_err_set_FUNCTION
#define apr_procattr_child_err_set_REQUIRED_ARGC 3
#define apr_procattr_child_err_set_OPTIONAL_ARGC 0
/* apr_status_t apr_procattr_child_err_set(struct apr_procattr_t * attr, apr_file_t * child_err, apr_file_t * parent_err) */
mrb_value
mrb_APR_apr_procattr_child_err_set(mrb_state* mrb, mrb_value self) {
  mrb_value attr;
  mrb_value child_err;
  mrb_value parent_err;

  /* Fetch the args */
  mrb_get_args(mrb, "ooo", &attr, &child_err, &parent_err);

  /* Type checking */
  if (!mrb_obj_is_kind_of(mrb, attr, AprProcattrT_class(mrb))) {
    mrb_raise(mrb, E_TYPE_ERROR, "AprProcattrT expected");
    return mrb_nil_value();
  }
  if (!mrb_obj_is_kind_of(mrb, child_err, AprFileT_class(mrb))) {
    mrb_raise(mrb, E_TYPE_ERROR, "AprFileT expected");
    return mrb_nil_value();
  }
  if (!mrb_obj_is_kind_of(mrb, parent_err, AprFileT_class(mrb)) && !mrb_nil_p(parent_err)) {
    mrb_raise(mrb, E_TYPE_ERROR, "AprFileT expected");
    return mrb_nil_value();
  }

  /* Unbox param: attr */
  struct apr_procattr_t * native_attr = (mrb_nil_p(attr) ? NULL : mruby_unbox_apr_procattr_t(attr));

  /* Unbox param: child_err */
  apr_file_t * native_child_err = (mrb_nil_p(child_err) ? NULL : mruby_unbox_apr_file_t(child_err));

  /* Unbox param: parent_err */
  apr_file_t * native_parent_err = (mrb_nil_p(parent_err) ? NULL : mruby_unbox_apr_file_t(parent_err));

  /* Invocation */
  apr_status_t native_return_value = apr_procattr_child_err_set(native_attr, native_child_err, native_parent_err);

  /* Box the return value */
  mrb_value return_value = mrb_fixnum_value(native_return_value);
  
  return return_value;
}
#endif
/* MRUBY_BINDING_END */

/* MRUBY_BINDING: apr_procattr_child_errfn_set */
/* sha: a5c0b95c17148b073073bb64dd904f421087e739ba42661c286913191e264770 */
#if BIND_apr_procattr_child_errfn_set_FUNCTION
#define apr_procattr_child_errfn_set_REQUIRED_ARGC 2
#define apr_procattr_child_errfn_set_OPTIONAL_ARGC 0
/* apr_status_t apr_procattr_child_errfn_set(apr_procattr_t * attr, apr_child_errfn_t * errfn) */
mrb_value
mrb_APR_apr_procattr_child_errfn_set(mrb_state* mrb, mrb_value self) {
  mrb_value attr;
  mrb_value errfn;

  /* Fetch the args */
  mrb_get_args(mrb, "oo", &attr, &errfn);

  /* Type checking */
  if (!mrb_obj_is_kind_of(mrb, attr, AprProcattrT_class(mrb))) {
    mrb_raise(mrb, E_TYPE_ERROR, "AprProcattrT expected");
    return mrb_nil_value();
  }
  TODO_type_check_apr_child_errfn_t_PTR(errfn);

  /* Unbox param: attr */
  apr_procattr_t * native_attr = (mrb_nil_p(attr) ? NULL : mruby_unbox_apr_procattr_t(attr));

  /* Unbox param: errfn */
  apr_child_errfn_t * native_errfn = TODO_mruby_unbox_apr_child_errfn_t_PTR(errfn);

  /* Invocation */
  apr_status_t native_return_value = apr_procattr_child_errfn_set(native_attr, native_errfn);

  /* Box the return value */
  mrb_value return_value = mrb_fixnum_value(native_return_value);
  
  return return_value;
}
#endif
/* MRUBY_BINDING_END */

/* MRUBY_BINDING: apr_procattr_child_in_set */
/* sha: 87d9754bcb5c91d677da70538cea1e1d8f415f108f3da746861d5b2f919ffab4 */
#if BIND_apr_procattr_child_in_set_FUNCTION
#define apr_procattr_child_in_set_REQUIRED_ARGC 3
#define apr_procattr_child_in_set_OPTIONAL_ARGC 0
/* apr_status_t apr_procattr_child_in_set(struct apr_procattr_t * attr, apr_file_t * child_in, apr_file_t * parent_in) */
mrb_value
mrb_APR_apr_procattr_child_in_set(mrb_state* mrb, mrb_value self) {
  mrb_value attr;
  mrb_value child_in;
  mrb_value parent_in;

  /* Fetch the args */
  mrb_get_args(mrb, "ooo", &attr, &child_in, &parent_in);

  /* Type checking */
  if (!mrb_obj_is_kind_of(mrb, attr, AprProcattrT_class(mrb))) {
    mrb_raise(mrb, E_TYPE_ERROR, "AprProcattrT expected");
    return mrb_nil_value();
  }
  if (!mrb_obj_is_kind_of(mrb, child_in, AprFileT_class(mrb))) {
    mrb_raise(mrb, E_TYPE_ERROR, "AprFileT expected");
    return mrb_nil_value();
  }
  if (!mrb_obj_is_kind_of(mrb, parent_in, AprFileT_class(mrb)) && !mrb_nil_p(parent_in)) {
    mrb_raise(mrb, E_TYPE_ERROR, "AprFileT expected");
    return mrb_nil_value();
  }

  /* Unbox param: attr */
  struct apr_procattr_t * native_attr = (mrb_nil_p(attr) ? NULL : mruby_unbox_apr_procattr_t(attr));

  /* Unbox param: child_in */
  apr_file_t * native_child_in = (mrb_nil_p(child_in) ? NULL : mruby_unbox_apr_file_t(child_in));

  /* Unbox param: parent_in */
  apr_file_t * native_parent_in = (mrb_nil_p(parent_in) ? NULL : mruby_unbox_apr_file_t(parent_in));

  /* Invocation */
  apr_status_t native_return_value = apr_procattr_child_in_set(native_attr, native_child_in, native_parent_in);

  /* Box the return value */
  mrb_value return_value = mrb_fixnum_value(native_return_value);
  
  return return_value;
}
#endif
/* MRUBY_BINDING_END */

/* MRUBY_BINDING: apr_procattr_child_out_set */
/* sha: e2137e029ca564c4c4324162d7d6bba558df792f375e082c8080d605d972ebcd */
#if BIND_apr_procattr_child_out_set_FUNCTION
#define apr_procattr_child_out_set_REQUIRED_ARGC 2
#define apr_procattr_child_out_set_OPTIONAL_ARGC 1
/* apr_status_t apr_procattr_child_out_set(struct apr_procattr_t * attr, apr_file_t * child_out, apr_file_t * parent_out) */
mrb_value
mrb_APR_apr_procattr_child_out_set(mrb_state* mrb, mrb_value self) {
  mrb_value attr;
  mrb_value child_out;
  mrb_value parent_out = mrb_nil_value();

  /* Fetch the args */
  mrb_get_args(mrb, "oo|o", &attr, &child_out, &parent_out);

  /* Type checking */
  if (!mrb_obj_is_kind_of(mrb, attr, AprProcattrT_class(mrb))) {
    mrb_raise(mrb, E_TYPE_ERROR, "AprProcattrT expected");
    return mrb_nil_value();
  }
  if (!mrb_obj_is_kind_of(mrb, child_out, AprFileT_class(mrb))) {
    mrb_raise(mrb, E_TYPE_ERROR, "AprFileT expected");
    return mrb_nil_value();
  }
  if (!mrb_obj_is_kind_of(mrb, parent_out, AprFileT_class(mrb)) && !mrb_nil_p(parent_out)) {
    mrb_raise(mrb, E_TYPE_ERROR, "AprFileT expected");
    return mrb_nil_value();
  }

  /* Unbox param: attr */
  struct apr_procattr_t * native_attr = (mrb_nil_p(attr) ? NULL : mruby_unbox_apr_procattr_t(attr));

  /* Unbox param: child_out */
  apr_file_t * native_child_out = (mrb_nil_p(child_out) ? NULL : mruby_unbox_apr_file_t(child_out));

  /* Unbox param: parent_out */
  apr_file_t * native_parent_out = (mrb_nil_p(parent_out) ? NULL : mruby_unbox_apr_file_t(parent_out));

  /* Invocation */
  apr_status_t native_return_value = apr_procattr_child_out_set(native_attr, native_child_out, native_parent_out);

  /* Box the return value */
  mrb_value return_value = mrb_fixnum_value(native_return_value);
  
  return return_value;
}
#endif
/* MRUBY_BINDING_END */

/* MRUBY_BINDING: apr_procattr_cmdtype_set */
/* sha: d2b10ea2263fd8c2fe2762f7c6a9819617534cf181d2a638b734c3e600643c8e */
#if BIND_apr_procattr_cmdtype_set_FUNCTION
#define apr_procattr_cmdtype_set_REQUIRED_ARGC 2
#define apr_procattr_cmdtype_set_OPTIONAL_ARGC 0
/* apr_status_t apr_procattr_cmdtype_set(apr_procattr_t * attr, apr_cmdtype_e cmd) */
mrb_value
mrb_APR_apr_procattr_cmdtype_set(mrb_state* mrb, mrb_value self) {
  mrb_value attr;
  mrb_int native_cmd;

  /* Fetch the args */
  mrb_get_args(mrb, "oi", &attr, &native_cmd);

  /* Type checking */
  if (!mrb_obj_is_kind_of(mrb, attr, AprProcattrT_class(mrb))) {
    mrb_raise(mrb, E_TYPE_ERROR, "AprProcattrT expected");
    return mrb_nil_value();
  }

  /* Unbox param: attr */
  apr_procattr_t * native_attr = (mrb_nil_p(attr) ? NULL : mruby_unbox_apr_procattr_t(attr));

  /* Invocation */
  apr_status_t native_return_value = apr_procattr_cmdtype_set(native_attr, native_cmd);

  /* Box the return value */
  mrb_value return_value = mrb_fixnum_value(native_return_value);
  
  return return_value;
}
#endif
/* MRUBY_BINDING_END */

/* MRUBY_BINDING: apr_procattr_create */
/* sha: 7511c2c3fd7433080993ef57994eb25d450b4888a73d9adeea5e17d6b2bf52d7 */
#if BIND_apr_procattr_create_FUNCTION
#define apr_procattr_create_REQUIRED_ARGC 1
#define apr_procattr_create_OPTIONAL_ARGC 0
/* apr_procattr_create
 *
 * Parameters:
 * - cont: AprPoolT
 * Return Type: [Fixnum, AprProcattrT]
 */
mrb_value
mrb_APR_apr_procattr_create(mrb_state* mrb, mrb_value self) {
  mrb_value cont;

  /* Fetch the args */
  mrb_get_args(mrb, "o", &cont);

  /* Type checking */
  if (!mrb_obj_is_kind_of(mrb, cont, AprPoolT_class(mrb))) {
    mrb_raise(mrb, E_TYPE_ERROR, "AprPoolT expected");
    return mrb_nil_value();
  }

  /* Unbox parameters */
  apr_pool_t * native_cont = (mrb_nil_p(cont) ? NULL : mruby_unbox_apr_pool_t(cont));

  /* Invocation */
  apr_procattr_t * native_new_attr;
  apr_status_t result = apr_procattr_create(&native_new_attr, native_cont);

  /* Box the return value */
  if (result > MRB_INT_MAX) {
    mrb_raise(mrb, mrb->eStandardError_class, "MRuby cannot represent integers greater than MRB_INT_MAX");
    return mrb_nil_value();
  }
  mrb_value return_value = mrb_fixnum_value(result);

  mrb_value results = mrb_ary_new(mrb);
  mrb_ary_push(mrb, results, return_value);
  if (result == 0) {
     mrb_ary_push(mrb, results, mruby_box_apr_procattr_t(mrb, native_new_attr));
  }
  else {
     mrb_ary_push(mrb, results, mrb_nil_value());
  }

  return results;
}
#endif
/* MRUBY_BINDING_END */

/* MRUBY_BINDING: apr_procattr_detach_set */
/* sha: 719768406ffe05a09663f1fe001493ef91914dec896c8f3c0a49a4334db2c1d8 */
#if BIND_apr_procattr_detach_set_FUNCTION
#define apr_procattr_detach_set_REQUIRED_ARGC 2
#define apr_procattr_detach_set_OPTIONAL_ARGC 0
/* apr_status_t apr_procattr_detach_set(apr_procattr_t * attr, apr_int32_t detach) */
mrb_value
mrb_APR_apr_procattr_detach_set(mrb_state* mrb, mrb_value self) {
  mrb_value attr;
  mrb_int native_detach;

  /* Fetch the args */
  mrb_get_args(mrb, "oi", &attr, &native_detach);

  /* Type checking */
  if (!mrb_obj_is_kind_of(mrb, attr, AprProcattrT_class(mrb))) {
    mrb_raise(mrb, E_TYPE_ERROR, "AprProcattrT expected");
    return mrb_nil_value();
  }

  /* Unbox param: attr */
  apr_procattr_t * native_attr = (mrb_nil_p(attr) ? NULL : mruby_unbox_apr_procattr_t(attr));

  /* Invocation */
  apr_status_t native_return_value = apr_procattr_detach_set(native_attr, native_detach);

  /* Box the return value */
  mrb_value return_value = mrb_fixnum_value(native_return_value);
  
  return return_value;
}
#endif
/* MRUBY_BINDING_END */

/* MRUBY_BINDING: apr_procattr_dir_set */
/* sha: b99977736de5e791ac2d5ae1407adf39856a07576626c3c7f94a79fd85db4501 */
#if BIND_apr_procattr_dir_set_FUNCTION
#define apr_procattr_dir_set_REQUIRED_ARGC 2
#define apr_procattr_dir_set_OPTIONAL_ARGC 0
/* apr_status_t apr_procattr_dir_set(apr_procattr_t * attr, const char * dir) */
mrb_value
mrb_APR_apr_procattr_dir_set(mrb_state* mrb, mrb_value self) {
  mrb_value attr;
  char * native_dir = NULL;

  /* Fetch the args */
  mrb_get_args(mrb, "oz", &attr, &native_dir);

  /* Type checking */
  if (!mrb_obj_is_kind_of(mrb, attr, AprProcattrT_class(mrb))) {
    mrb_raise(mrb, E_TYPE_ERROR, "AprProcattrT expected");
    return mrb_nil_value();
  }

  /* Unbox param: attr */
  apr_procattr_t * native_attr = (mrb_nil_p(attr) ? NULL : mruby_unbox_apr_procattr_t(attr));

  /* Invocation */
  apr_status_t native_return_value = apr_procattr_dir_set(native_attr, native_dir);

  /* Box the return value */
  mrb_value return_value = mrb_fixnum_value(native_return_value);
  
  return return_value;
}
#endif
/* MRUBY_BINDING_END */

/* MRUBY_BINDING: apr_procattr_error_check_set */
/* sha: a92a7a4ad78f9a7bc34e44dea292f6b6ecdec192fd6904a6a8fa9307feed74ef */
#if BIND_apr_procattr_error_check_set_FUNCTION
#define apr_procattr_error_check_set_REQUIRED_ARGC 2
#define apr_procattr_error_check_set_OPTIONAL_ARGC 0
/* apr_status_t apr_procattr_error_check_set(apr_procattr_t * attr, apr_int32_t chk) */
mrb_value
mrb_APR_apr_procattr_error_check_set(mrb_state* mrb, mrb_value self) {
  mrb_value attr;
  mrb_int native_chk;

  /* Fetch the args */
  mrb_get_args(mrb, "oi", &attr, &native_chk);

  /* Type checking */
  if (!mrb_obj_is_kind_of(mrb, attr, AprProcattrT_class(mrb))) {
    mrb_raise(mrb, E_TYPE_ERROR, "AprProcattrT expected");
    return mrb_nil_value();
  }

  /* Unbox param: attr */
  apr_procattr_t * native_attr = (mrb_nil_p(attr) ? NULL : mruby_unbox_apr_procattr_t(attr));

  /* Invocation */
  apr_status_t native_return_value = apr_procattr_error_check_set(native_attr, native_chk);

  /* Box the return value */
  mrb_value return_value = mrb_fixnum_value(native_return_value);
  
  return return_value;
}
#endif
/* MRUBY_BINDING_END */

/* MRUBY_BINDING: apr_procattr_group_set */
/* sha: d98bc606551e394b5b2cf30494c144f87080a87f9ad2dd8cc22c135c9e496402 */
#if BIND_apr_procattr_group_set_FUNCTION
#define apr_procattr_group_set_REQUIRED_ARGC 2
#define apr_procattr_group_set_OPTIONAL_ARGC 0
/* apr_status_t apr_procattr_group_set(apr_procattr_t * attr, const char * groupname) */
mrb_value
mrb_APR_apr_procattr_group_set(mrb_state* mrb, mrb_value self) {
  mrb_value attr;
  char * native_groupname = NULL;

  /* Fetch the args */
  mrb_get_args(mrb, "oz", &attr, &native_groupname);

  /* Type checking */
  if (!mrb_obj_is_kind_of(mrb, attr, AprProcattrT_class(mrb))) {
    mrb_raise(mrb, E_TYPE_ERROR, "AprProcattrT expected");
    return mrb_nil_value();
  }

  /* Unbox param: attr */
  apr_procattr_t * native_attr = (mrb_nil_p(attr) ? NULL : mruby_unbox_apr_procattr_t(attr));

  /* Invocation */
  apr_status_t native_return_value = apr_procattr_group_set(native_attr, native_groupname);

  /* Box the return value */
  mrb_value return_value = mrb_fixnum_value(native_return_value);
  
  return return_value;
}
#endif
/* MRUBY_BINDING_END */

/* MRUBY_BINDING: apr_procattr_io_set */
/* sha: 694990d6e8fb6548407b6b16d603db0e3ebe00ca90e563b65d8f2d8c0d235d85 */
#if BIND_apr_procattr_io_set_FUNCTION
#define apr_procattr_io_set_REQUIRED_ARGC 4
#define apr_procattr_io_set_OPTIONAL_ARGC 0
/* apr_status_t apr_procattr_io_set(apr_procattr_t * attr, apr_int32_t in, apr_int32_t out, apr_int32_t err) */
mrb_value
mrb_APR_apr_procattr_io_set(mrb_state* mrb, mrb_value self) {
  mrb_value attr;
  mrb_int native_in;
  mrb_int native_out;
  mrb_int native_err;

  /* Fetch the args */
  mrb_get_args(mrb, "oiii", &attr, &native_in, &native_out, &native_err);

  /* Type checking */
  if (!mrb_obj_is_kind_of(mrb, attr, AprProcattrT_class(mrb))) {
    mrb_raise(mrb, E_TYPE_ERROR, "AprProcattrT expected");
    return mrb_nil_value();
  }

  /* Unbox param: attr */
  apr_procattr_t * native_attr = (mrb_nil_p(attr) ? NULL : mruby_unbox_apr_procattr_t(attr));

  /* Invocation */
  apr_status_t native_return_value = apr_procattr_io_set(native_attr, native_in, native_out, native_err);

  /* Box the return value */
  mrb_value return_value = mrb_fixnum_value(native_return_value);
  
  return return_value;
}
#endif
/* MRUBY_BINDING_END */

/* MRUBY_BINDING: apr_procattr_limit_set */
/* sha: dca13a5b19713b1405a77a294afed37fb24a92047a169c0ca62b89d2e3ec2415 */
#if BIND_apr_procattr_limit_set_FUNCTION
#define apr_procattr_limit_set_REQUIRED_ARGC 3
#define apr_procattr_limit_set_OPTIONAL_ARGC 0
/* apr_status_t apr_procattr_limit_set(apr_procattr_t * attr, apr_int32_t what, struct rlimit * limit) */
mrb_value
mrb_APR_apr_procattr_limit_set(mrb_state* mrb, mrb_value self) {
  mrb_value attr;
  mrb_int native_what;
  mrb_value limit;

  /* Fetch the args */
  mrb_get_args(mrb, "oio", &attr, &native_what, &limit);

  /* Type checking */
  if (!mrb_obj_is_kind_of(mrb, attr, AprProcattrT_class(mrb))) {
    mrb_raise(mrb, E_TYPE_ERROR, "AprProcattrT expected");
    return mrb_nil_value();
  }
  TODO_type_check_rlimit_PTR(limit);

  /* Unbox param: attr */
  apr_procattr_t * native_attr = (mrb_nil_p(attr) ? NULL : mruby_unbox_apr_procattr_t(attr));

  /* Unbox param: limit */
  struct rlimit * native_limit = TODO_mruby_unbox_rlimit_PTR(limit);

  /* Invocation */
  apr_status_t native_return_value = apr_procattr_limit_set(native_attr, native_what, native_limit);

  /* Box the return value */
  mrb_value return_value = mrb_fixnum_value(native_return_value);
  
  return return_value;
}
#endif
/* MRUBY_BINDING_END */

/* MRUBY_BINDING: apr_procattr_user_set */
/* sha: ed8b0aece867e2c908b50ed44336f2347fd85105d4e90e35741c786eb5b55da0 */
#if BIND_apr_procattr_user_set_FUNCTION
#define apr_procattr_user_set_REQUIRED_ARGC 3
#define apr_procattr_user_set_OPTIONAL_ARGC 0
/* apr_status_t apr_procattr_user_set(apr_procattr_t * attr, const char * username, const char * password) */
mrb_value
mrb_APR_apr_procattr_user_set(mrb_state* mrb, mrb_value self) {
  mrb_value attr;
  char * native_username = NULL;
  char * native_password = NULL;

  /* Fetch the args */
  mrb_get_args(mrb, "ozz", &attr, &native_username, &native_password);

  /* Type checking */
  if (!mrb_obj_is_kind_of(mrb, attr, AprProcattrT_class(mrb))) {
    mrb_raise(mrb, E_TYPE_ERROR, "AprProcattrT expected");
    return mrb_nil_value();
  }

  /* Unbox param: attr */
  apr_procattr_t * native_attr = (mrb_nil_p(attr) ? NULL : mruby_unbox_apr_procattr_t(attr));

  /* Invocation */
  apr_status_t native_return_value = apr_procattr_user_set(native_attr, native_username, native_password);

  /* Box the return value */
  mrb_value return_value = mrb_fixnum_value(native_return_value);
  
  return return_value;
}
#endif
/* MRUBY_BINDING_END */

/* MRUBY_BINDING: apr_psprintf */
/* sha: 34ba8b01516446989ec2a3030b965fae0fda9257ea71bcec538fbabe21766fe0 */
#if BIND_apr_psprintf_FUNCTION
#define apr_psprintf_REQUIRED_ARGC 2
#define apr_psprintf_OPTIONAL_ARGC 0
/* char * apr_psprintf(apr_pool_t * p, const char * fmt) */
mrb_value
mrb_APR_apr_psprintf(mrb_state* mrb, mrb_value self) {
  mrb_value p;
  char * native_fmt = NULL;

  /* Fetch the args */
  mrb_get_args(mrb, "oz", &p, &native_fmt);

  /* Type checking */
  if (!mrb_obj_is_kind_of(mrb, p, AprPoolT_class(mrb))) {
    mrb_raise(mrb, E_TYPE_ERROR, "AprPoolT expected");
    return mrb_nil_value();
  }

  /* Unbox param: p */
  apr_pool_t * native_p = (mrb_nil_p(p) ? NULL : mruby_unbox_apr_pool_t(p));

  /* Invocation */
  char * native_return_value = apr_psprintf(native_p, native_fmt);

  /* Box the return value */
  mrb_value return_value = TODO_mruby_box_char_PTR(mrb, native_return_value);
  
  return return_value;
}
#endif
/* MRUBY_BINDING_END */

/* MRUBY_BINDING: apr_pstrcat */
/* sha: dbf8ab1149dfe338ace7b976000b0614dfbe86fb2f93c9d8bb06dd92a734d574 */
#if BIND_apr_pstrcat_FUNCTION
#define apr_pstrcat_REQUIRED_ARGC 1
#define apr_pstrcat_OPTIONAL_ARGC 0
/* char * apr_pstrcat(apr_pool_t * p) */
mrb_value
mrb_APR_apr_pstrcat(mrb_state* mrb, mrb_value self) {
  mrb_value p;

  /* Fetch the args */
  mrb_get_args(mrb, "o", &p);

  /* Type checking */
  if (!mrb_obj_is_kind_of(mrb, p, AprPoolT_class(mrb))) {
    mrb_raise(mrb, E_TYPE_ERROR, "AprPoolT expected");
    return mrb_nil_value();
  }

  /* Unbox param: p */
  apr_pool_t * native_p = (mrb_nil_p(p) ? NULL : mruby_unbox_apr_pool_t(p));

  /* Invocation */
  char * native_return_value = apr_pstrcat(native_p);

  /* Box the return value */
  mrb_value return_value = TODO_mruby_box_char_PTR(mrb, native_return_value);
  
  return return_value;
}
#endif
/* MRUBY_BINDING_END */

/* MRUBY_BINDING: apr_pstrcatv */
/* sha: 7ce7e7d46a322dc3e9ec054a8d839753c9571aeb0feb412a2478828ecaae3b20 */
#if BIND_apr_pstrcatv_FUNCTION
#define apr_pstrcatv_REQUIRED_ARGC 4
#define apr_pstrcatv_OPTIONAL_ARGC 0
/* char * apr_pstrcatv(apr_pool_t * p, const struct iovec * vec, apr_size_t nvec, apr_size_t * nbytes) */
mrb_value
mrb_APR_apr_pstrcatv(mrb_state* mrb, mrb_value self) {
  mrb_value p;
  mrb_value vec;
  mrb_int native_nvec;
  mrb_value nbytes;

  /* Fetch the args */
  mrb_get_args(mrb, "ooio", &p, &vec, &native_nvec, &nbytes);

  /* Type checking */
  if (!mrb_obj_is_kind_of(mrb, p, AprPoolT_class(mrb))) {
    mrb_raise(mrb, E_TYPE_ERROR, "AprPoolT expected");
    return mrb_nil_value();
  }
  TODO_type_check_iovec_PTR(vec);
  TODO_type_check_apr_size_t_PTR(nbytes);

  /* Unbox param: p */
  apr_pool_t * native_p = (mrb_nil_p(p) ? NULL : mruby_unbox_apr_pool_t(p));

  /* Unbox param: vec */
  const struct iovec * native_vec = TODO_mruby_unbox_iovec_PTR(vec);

  /* Unbox param: nbytes */
  apr_size_t * native_nbytes = TODO_mruby_unbox_apr_size_t_PTR(nbytes);

  /* Invocation */
  char * native_return_value = apr_pstrcatv(native_p, native_vec, native_nvec, native_nbytes);

  /* Box the return value */
  mrb_value return_value = TODO_mruby_box_char_PTR(mrb, native_return_value);
  
  return return_value;
}
#endif
/* MRUBY_BINDING_END */

/* MRUBY_BINDING: apr_pstrdup */
/* sha: 6bdab8efbff7290d0461d0bca4b4eb376816da3bd716e281b1fa1a8fcd70949f */
#if BIND_apr_pstrdup_FUNCTION
#define apr_pstrdup_REQUIRED_ARGC 2
#define apr_pstrdup_OPTIONAL_ARGC 0
/* char * apr_pstrdup(apr_pool_t * p, const char * s) */
mrb_value
mrb_APR_apr_pstrdup(mrb_state* mrb, mrb_value self) {
  mrb_value p;
  char * native_s = NULL;

  /* Fetch the args */
  mrb_get_args(mrb, "oz", &p, &native_s);

  /* Type checking */
  if (!mrb_obj_is_kind_of(mrb, p, AprPoolT_class(mrb))) {
    mrb_raise(mrb, E_TYPE_ERROR, "AprPoolT expected");
    return mrb_nil_value();
  }

  /* Unbox param: p */
  apr_pool_t * native_p = (mrb_nil_p(p) ? NULL : mruby_unbox_apr_pool_t(p));

  /* Invocation */
  char * native_return_value = apr_pstrdup(native_p, native_s);

  /* Box the return value */
  mrb_value return_value = TODO_mruby_box_char_PTR(mrb, native_return_value);
  
  return return_value;
}
#endif
/* MRUBY_BINDING_END */

/* MRUBY_BINDING: apr_pstrmemdup */
/* sha: 41f4a509d0897814faba10d0111b74908fb4b664de63221448cbda5ef9476cfa */
#if BIND_apr_pstrmemdup_FUNCTION
#define apr_pstrmemdup_REQUIRED_ARGC 3
#define apr_pstrmemdup_OPTIONAL_ARGC 0
/* char * apr_pstrmemdup(apr_pool_t * p, const char * s, apr_size_t n) */
mrb_value
mrb_APR_apr_pstrmemdup(mrb_state* mrb, mrb_value self) {
  mrb_value p;
  char * native_s = NULL;
  mrb_int native_n;

  /* Fetch the args */
  mrb_get_args(mrb, "ozi", &p, &native_s, &native_n);

  /* Type checking */
  if (!mrb_obj_is_kind_of(mrb, p, AprPoolT_class(mrb))) {
    mrb_raise(mrb, E_TYPE_ERROR, "AprPoolT expected");
    return mrb_nil_value();
  }

  /* Unbox param: p */
  apr_pool_t * native_p = (mrb_nil_p(p) ? NULL : mruby_unbox_apr_pool_t(p));

  /* Invocation */
  char * native_return_value = apr_pstrmemdup(native_p, native_s, native_n);

  /* Box the return value */
  mrb_value return_value = TODO_mruby_box_char_PTR(mrb, native_return_value);
  
  return return_value;
}
#endif
/* MRUBY_BINDING_END */

/* MRUBY_BINDING: apr_pstrndup */
/* sha: 643a2fa671185d3a807131cffbcc603603d06d56b4e25255af79a47d62b453cf */
#if BIND_apr_pstrndup_FUNCTION
#define apr_pstrndup_REQUIRED_ARGC 3
#define apr_pstrndup_OPTIONAL_ARGC 0
/* char * apr_pstrndup(apr_pool_t * p, const char * s, apr_size_t n) */
mrb_value
mrb_APR_apr_pstrndup(mrb_state* mrb, mrb_value self) {
  mrb_value p;
  char * native_s = NULL;
  mrb_int native_n;

  /* Fetch the args */
  mrb_get_args(mrb, "ozi", &p, &native_s, &native_n);

  /* Type checking */
  if (!mrb_obj_is_kind_of(mrb, p, AprPoolT_class(mrb))) {
    mrb_raise(mrb, E_TYPE_ERROR, "AprPoolT expected");
    return mrb_nil_value();
  }

  /* Unbox param: p */
  apr_pool_t * native_p = (mrb_nil_p(p) ? NULL : mruby_unbox_apr_pool_t(p));

  /* Invocation */
  char * native_return_value = apr_pstrndup(native_p, native_s, native_n);

  /* Box the return value */
  mrb_value return_value = TODO_mruby_box_char_PTR(mrb, native_return_value);
  
  return return_value;
}
#endif
/* MRUBY_BINDING_END */

/* MRUBY_BINDING: apr_pvsprintf */
/* sha: d1f1b125e1cc69797b7bd8dde462a9c07ea3f07f152a7d3e4a8e517adf41d1dd */
#if BIND_apr_pvsprintf_FUNCTION
#define apr_pvsprintf_REQUIRED_ARGC 3
#define apr_pvsprintf_OPTIONAL_ARGC 0
/* char * apr_pvsprintf(apr_pool_t * p, const char * fmt, int ap) */
mrb_value
mrb_APR_apr_pvsprintf(mrb_state* mrb, mrb_value self) {
  mrb_value p;
  char * native_fmt = NULL;
  mrb_int native_ap;

  /* Fetch the args */
  mrb_get_args(mrb, "ozi", &p, &native_fmt, &native_ap);

  /* Type checking */
  if (!mrb_obj_is_kind_of(mrb, p, AprPoolT_class(mrb))) {
    mrb_raise(mrb, E_TYPE_ERROR, "AprPoolT expected");
    return mrb_nil_value();
  }

  /* Unbox param: p */
  apr_pool_t * native_p = (mrb_nil_p(p) ? NULL : mruby_unbox_apr_pool_t(p));

  /* Invocation */
  char * native_return_value = apr_pvsprintf(native_p, native_fmt, native_ap);

  /* Box the return value */
  mrb_value return_value = TODO_mruby_box_char_PTR(mrb, native_return_value);
  
  return return_value;
}
#endif
/* MRUBY_BINDING_END */

/* MRUBY_BINDING: apr_rfc822_date */
/* sha: 9e32ac3d40f86d6cd4bedc474a05943c01f4cf43631135fd9ceed8aa69cca88f */
#if BIND_apr_rfc822_date_FUNCTION
#define apr_rfc822_date_REQUIRED_ARGC 2
#define apr_rfc822_date_OPTIONAL_ARGC 0
/* apr_status_t apr_rfc822_date(char * date_str, apr_time_t t) */
mrb_value
mrb_APR_apr_rfc822_date(mrb_state* mrb, mrb_value self) {
  mrb_value date_str;
  mrb_int native_t;

  /* Fetch the args */
  mrb_get_args(mrb, "oi", &date_str, &native_t);

  /* Type checking */
  TODO_type_check_char_PTR(date_str);

  /* Unbox param: date_str */
  char * native_date_str = TODO_mruby_unbox_char_PTR(date_str);

  /* Invocation */
  apr_status_t native_return_value = apr_rfc822_date(native_date_str, native_t);

  /* Box the return value */
  mrb_value return_value = mrb_fixnum_value(native_return_value);
  
  return return_value;
}
#endif
/* MRUBY_BINDING_END */

/* MRUBY_BINDING: apr_setup_signal_thread */
/* sha: 315aaf6f259b68b74281b2bb8a42638faa426578d8b05b58f03d457f6be23aaf */
#if BIND_apr_setup_signal_thread_FUNCTION
#define apr_setup_signal_thread_REQUIRED_ARGC 0
#define apr_setup_signal_thread_OPTIONAL_ARGC 0
/* apr_status_t apr_setup_signal_thread() */
mrb_value
mrb_APR_apr_setup_signal_thread(mrb_state* mrb, mrb_value self) {
  /* Invocation */
  apr_status_t native_return_value = apr_setup_signal_thread();

  /* Box the return value */
  mrb_value return_value = mrb_fixnum_value(native_return_value);
  
  return return_value;
}
#endif
/* MRUBY_BINDING_END */

/* MRUBY_BINDING: apr_signal */
/* sha: 0d09458b1394b2f7b6afba51ee0c587991504ca337f2f12f9dd83affbe4e789f */
#if BIND_apr_signal_FUNCTION
#define apr_signal_REQUIRED_ARGC 2
#define apr_signal_OPTIONAL_ARGC 0
/* apr_sigfunc_t * apr_signal(int signo, apr_sigfunc_t * func) */
mrb_value
mrb_APR_apr_signal(mrb_state* mrb, mrb_value self) {
  mrb_int native_signo;
  mrb_value func;

  /* Fetch the args */
  mrb_get_args(mrb, "io", &native_signo, &func);

  /* Type checking */
  TODO_type_check_apr_sigfunc_t_PTR(func);

  /* Unbox param: func */
  apr_sigfunc_t * native_func = TODO_mruby_unbox_apr_sigfunc_t_PTR(func);

  /* Invocation */
  apr_sigfunc_t * native_return_value = apr_signal(native_signo, native_func);

  /* Box the return value */
  mrb_value return_value = TODO_mruby_box_apr_sigfunc_t_PTR(mrb, native_return_value);
  
  return return_value;
}
#endif
/* MRUBY_BINDING_END */

/* MRUBY_BINDING: apr_signal_block */
/* sha: b4934e412113d4f09a63799948a7ce1c321b3eabf0f4359b8685a0206ff51199 */
#if BIND_apr_signal_block_FUNCTION
#define apr_signal_block_REQUIRED_ARGC 1
#define apr_signal_block_OPTIONAL_ARGC 0
/* apr_status_t apr_signal_block(int signum) */
mrb_value
mrb_APR_apr_signal_block(mrb_state* mrb, mrb_value self) {
  mrb_int native_signum;

  /* Fetch the args */
  mrb_get_args(mrb, "i", &native_signum);

  /* Invocation */
  apr_status_t native_return_value = apr_signal_block(native_signum);

  /* Box the return value */
  mrb_value return_value = mrb_fixnum_value(native_return_value);
  
  return return_value;
}
#endif
/* MRUBY_BINDING_END */

/* MRUBY_BINDING: apr_signal_description_get */
/* sha: ba9c8d5430f365bfdebfa11b4db0bb79057d779701616a11b4935c52f67be317 */
#if BIND_apr_signal_description_get_FUNCTION
#define apr_signal_description_get_REQUIRED_ARGC 1
#define apr_signal_description_get_OPTIONAL_ARGC 0
/* const char * apr_signal_description_get(int signum) */
mrb_value
mrb_APR_apr_signal_description_get(mrb_state* mrb, mrb_value self) {
  mrb_int native_signum;

  /* Fetch the args */
  mrb_get_args(mrb, "i", &native_signum);

  /* Invocation */
  const char * native_return_value = apr_signal_description_get(native_signum);

  /* Box the return value */
  mrb_value return_value = native_return_value == NULL ? mrb_nil_value() : mrb_str_new_cstr(mrb, native_return_value);
  
  return return_value;
}
#endif
/* MRUBY_BINDING_END */

/* MRUBY_BINDING: apr_signal_init */
/* sha: 9ce8d395a582139f2de800fc84458265c751ba362378c1eda3e53bd9ad75a1d9 */
#if BIND_apr_signal_init_FUNCTION
#define apr_signal_init_REQUIRED_ARGC 1
#define apr_signal_init_OPTIONAL_ARGC 0
/* void apr_signal_init(apr_pool_t * pglobal) */
mrb_value
mrb_APR_apr_signal_init(mrb_state* mrb, mrb_value self) {
  mrb_value pglobal;

  /* Fetch the args */
  mrb_get_args(mrb, "o", &pglobal);

  /* Type checking */
  if (!mrb_obj_is_kind_of(mrb, pglobal, AprPoolT_class(mrb))) {
    mrb_raise(mrb, E_TYPE_ERROR, "AprPoolT expected");
    return mrb_nil_value();
  }

  /* Unbox param: pglobal */
  apr_pool_t * native_pglobal = (mrb_nil_p(pglobal) ? NULL : mruby_unbox_apr_pool_t(pglobal));

  /* Invocation */
  apr_signal_init(native_pglobal);

  return mrb_nil_value();
}
#endif
/* MRUBY_BINDING_END */

/* MRUBY_BINDING: apr_signal_thread */
/* sha: 60c34d9273a7f31d65e42fddd21eb58647be0f69bdbc00bee758b7a2283fc524 */
#if BIND_apr_signal_thread_FUNCTION
#define apr_signal_thread_REQUIRED_ARGC 1
#define apr_signal_thread_OPTIONAL_ARGC 0
/* apr_status_t apr_signal_thread(int (*)(int) signal_handler) */
mrb_value
mrb_APR_apr_signal_thread(mrb_state* mrb, mrb_value self) {
  mrb_value signal_handler;

  /* Fetch the args */
  mrb_get_args(mrb, "o", &signal_handler);

  /* Type checking */
  TODO_type_check_int_LPAREN_PTR_RPAREN_LPAREN_int_RPAREN(signal_handler);

  /* Unbox param: signal_handler */
  int (*native_signal_handler)(int) = TODO_mruby_unbox_int_LPAREN_PTR_RPAREN_LPAREN_int_RPAREN(signal_handler);

  /* Invocation */
  apr_status_t native_return_value = apr_signal_thread(native_signal_handler);

  /* Box the return value */
  mrb_value return_value = mrb_fixnum_value(native_return_value);
  
  return return_value;
}
#endif
/* MRUBY_BINDING_END */

/* MRUBY_BINDING: apr_signal_unblock */
/* sha: 4d04fb9ce621936c84b6eaadde570bee38c56a4a05cf7e43b186c217cd6248a6 */
#if BIND_apr_signal_unblock_FUNCTION
#define apr_signal_unblock_REQUIRED_ARGC 1
#define apr_signal_unblock_OPTIONAL_ARGC 0
/* apr_status_t apr_signal_unblock(int signum) */
mrb_value
mrb_APR_apr_signal_unblock(mrb_state* mrb, mrb_value self) {
  mrb_int native_signum;

  /* Fetch the args */
  mrb_get_args(mrb, "i", &native_signum);

  /* Invocation */
  apr_status_t native_return_value = apr_signal_unblock(native_signum);

  /* Box the return value */
  mrb_value return_value = mrb_fixnum_value(native_return_value);
  
  return return_value;
}
#endif
/* MRUBY_BINDING_END */

/* MRUBY_BINDING: apr_sleep */
/* sha: user_edited */
#if BIND_apr_sleep_FUNCTION
#define apr_sleep_REQUIRED_ARGC 1
#define apr_sleep_OPTIONAL_ARGC 0
/* apr_sleep
 *
 * Parameters:
 * - t: long long
 * Return Type: void
 */
mrb_value
mrb_APR_apr_sleep(mrb_state* mrb, mrb_value self) {
  mrb_int t;
  mrb_get_args(mrb, "i", &t);
  apr_sleep(t);
  return mrb_nil_value();
}
#endif
/* MRUBY_BINDING_END */

/* MRUBY_BINDING: apr_snprintf */
/* sha: 6566497c036737ad8e5f17c2447657899b80a419abac6a8a28fb47b4433171f6 */
#if BIND_apr_snprintf_FUNCTION
#define apr_snprintf_REQUIRED_ARGC 3
#define apr_snprintf_OPTIONAL_ARGC 0
/* int apr_snprintf(char * buf, apr_size_t len, const char * format) */
mrb_value
mrb_APR_apr_snprintf(mrb_state* mrb, mrb_value self) {
  mrb_value buf;
  mrb_int native_len;
  char * native_format = NULL;

  /* Fetch the args */
  mrb_get_args(mrb, "oiz", &buf, &native_len, &native_format);

  /* Type checking */
  TODO_type_check_char_PTR(buf);

  /* Unbox param: buf */
  char * native_buf = TODO_mruby_unbox_char_PTR(buf);

  /* Invocation */
  int native_return_value = apr_snprintf(native_buf, native_len, native_format);

  /* Box the return value */
  mrb_value return_value = mrb_fixnum_value(native_return_value);
  
  return return_value;
}
#endif
/* MRUBY_BINDING_END */

/* MRUBY_BINDING: apr_sockaddr_equal */
/* sha: user_edited */
#if BIND_apr_sockaddr_equal_FUNCTION
#define apr_sockaddr_equal_REQUIRED_ARGC 2
#define apr_sockaddr_equal_OPTIONAL_ARGC 0
/* apr_sockaddr_equal
 *
 * Parameters:
 * - addr1: const apr_sockaddr_t *
 * - addr2: const apr_sockaddr_t *
 * Return Type: int (0 for false, non-zero otherwise)
 */
mrb_value
mrb_APR_apr_sockaddr_equal(mrb_state* mrb, mrb_value self) {
  mrb_value addr1;
  mrb_value addr2;

  /* Fetch the args */
  mrb_get_args(mrb, "oo", &addr1, &addr2);

  /* Type checking */
  if (!mrb_obj_is_kind_of(mrb, addr1, AprSockaddrT_class(mrb))) {
    mrb_raise(mrb, E_TYPE_ERROR, "AprSockaddrT expected");
    return mrb_nil_value();
  }
  if (!mrb_obj_is_kind_of(mrb, addr2, AprSockaddrT_class(mrb))) {
    mrb_raise(mrb, E_TYPE_ERROR, "AprSockaddrT expected");
    return mrb_nil_value();
  }

  /* Unbox parameters */
  const apr_sockaddr_t * native_addr1 = (mrb_nil_p(addr1) ? NULL : mruby_unbox_apr_sockaddr_t(addr1));
  const apr_sockaddr_t * native_addr2 = (mrb_nil_p(addr2) ? NULL : mruby_unbox_apr_sockaddr_t(addr2));

  /* Invocation */
  int result = apr_sockaddr_equal(native_addr1, native_addr2);

  /* Box the return value */
  if (result > MRB_INT_MAX) {
    mrb_raise(mrb, mrb->eStandardError_class, "MRuby cannot represent integers greater than MRB_INT_MAX");
    return mrb_nil_value();
  }
  mrb_value return_value = mrb_fixnum_value(result);

  return return_value;
}
#endif
/* MRUBY_BINDING_END */

/* MRUBY_BINDING: apr_sockaddr_info_get */
/* sha: user_edited */
#if BIND_apr_sockaddr_info_get_FUNCTION
#define apr_sockaddr_info_get_REQUIRED_ARGC 5
#define apr_sockaddr_info_get_OPTIONAL_ARGC 0
/* apr_sockaddr_info_get
 *
 * Parameters:
 * - hostname: const char *
 * - family: int
 * - port: unsigned short
 * - flags: int
 * - p: apr_pool_t *
 * Return Type: [errno, Fixnum, sock_add, AprSockaddrT]
 */
mrb_value
mrb_APR_apr_sockaddr_info_get(mrb_state* mrb, mrb_value self) {
  mrb_value hostname;
  mrb_int native_family;
  mrb_int native_port;
  mrb_int native_flags;
  mrb_value p;

  /* Fetch the args */
  mrb_get_args(mrb, "oiiio", &hostname, &native_family, &native_port, &native_flags, &p);

  /* Type checking */
  if (!(mrb_obj_is_kind_of(mrb, hostname, mrb->string_class) || mrb_nil_p(hostname))) {
    mrb_raise(mrb, E_TYPE_ERROR, "String expected");
    return mrb_nil_value();
  }
  if (!mrb_obj_is_kind_of(mrb, p, AprPoolT_class(mrb))) {
    mrb_raise(mrb, E_TYPE_ERROR, "AprPoolT expected");
    return mrb_nil_value();
  }

  /* Unbox parameters */
  const char * native_hostname = mrb_nil_p(hostname) ? NULL : mrb_string_value_cstr(mrb, &hostname);

  apr_pool_t * native_p = (mrb_nil_p(p) ? NULL : mruby_unbox_apr_pool_t(p));

  /* Invocation */
  apr_sockaddr_t * native_sa;
  apr_status_t result = apr_sockaddr_info_get(&native_sa, native_hostname, native_family, native_port, native_flags, native_p);
  RETURN_ERRNO_AND_OUTPUT(result, mruby_box_apr_sockaddr_t(mrb, native_sa));
}
#endif
/* MRUBY_BINDING_END */

/* MRUBY_BINDING: apr_sockaddr_ip_get */
/* sha: user_edited */
#if BIND_apr_sockaddr_ip_get_FUNCTION
#define apr_sockaddr_ip_get_REQUIRED_ARGC 1
#define apr_sockaddr_ip_get_OPTIONAL_ARGC 0
/* apr_sockaddr_ip_get
 *
 * Parameters:
 * - sockaddr: apr_sockaddr_t *
 * Return Type: apr_status_t
 */
mrb_value
mrb_APR_apr_sockaddr_ip_get(mrb_state* mrb, mrb_value self) {
  mrb_value sockaddr;

  /* Fetch the args */
  mrb_get_args(mrb, "o", &sockaddr);

  /* Type checking */
  if (!mrb_obj_is_kind_of(mrb, sockaddr, AprSockaddrT_class(mrb))) {
     mrb_raise(mrb, E_TYPE_ERROR, "AprSockaddrT expected");
     return mrb_nil_value();
  }

  /* Unbox parameters */
  apr_sockaddr_t * native_sockaddr = (mrb_nil_p(sockaddr) ? NULL : mruby_unbox_apr_sockaddr_t(sockaddr));

  /* Invocation */
  char* native_addr;
  apr_status_t result = apr_sockaddr_ip_get(&native_addr, native_sockaddr);
  if (result == APR_SUCCESS) {
    mrb_value ruby_addr = mrb_str_new_cstr(mrb, native_addr);
    RETURN_ERRNO_AND_OUTPUT(result, ruby_addr);
  } else {
    free(native_addr);
    RETURN_ERRNO_AND_OUTPUT(result, mrb_nil_value());
  }
}
#endif
/* MRUBY_BINDING_END */

/* MRUBY_BINDING: apr_sockaddr_ip_getbuf */
/* sha: 3df09845e74400c4bc0ad71a851abe7f1c348bcfd0ba899e7a3bf6d6a422c754 */
#if BIND_apr_sockaddr_ip_getbuf_FUNCTION
#define apr_sockaddr_ip_getbuf_REQUIRED_ARGC 3
#define apr_sockaddr_ip_getbuf_OPTIONAL_ARGC 0
/* apr_status_t apr_sockaddr_ip_getbuf(char * buf, apr_size_t buflen, apr_sockaddr_t * sockaddr) */
mrb_value
mrb_APR_apr_sockaddr_ip_getbuf(mrb_state* mrb, mrb_value self) {
  mrb_value buf;
  mrb_int native_buflen;
  mrb_value sockaddr;

  /* Fetch the args */
  mrb_get_args(mrb, "oio", &buf, &native_buflen, &sockaddr);

  /* Type checking */
  TODO_type_check_char_PTR(buf);
  if (!mrb_obj_is_kind_of(mrb, sockaddr, AprSockaddrT_class(mrb))) {
    mrb_raise(mrb, E_TYPE_ERROR, "AprSockaddrT expected");
    return mrb_nil_value();
  }

  /* Unbox param: buf */
  char * native_buf = TODO_mruby_unbox_char_PTR(buf);

  /* Unbox param: sockaddr */
  apr_sockaddr_t * native_sockaddr = (mrb_nil_p(sockaddr) ? NULL : mruby_unbox_apr_sockaddr_t(sockaddr));

  /* Invocation */
  apr_status_t native_return_value = apr_sockaddr_ip_getbuf(native_buf, native_buflen, native_sockaddr);

  /* Box the return value */
  mrb_value return_value = mrb_fixnum_value(native_return_value);
  
  return return_value;
}
#endif
/* MRUBY_BINDING_END */

/* MRUBY_BINDING: apr_socket_accept */
/* sha: user_edited */
#if BIND_apr_socket_accept_FUNCTION
#define apr_socket_accept_REQUIRED_ARGC 2
#define apr_socket_accept_OPTIONAL_ARGC 0
/* apr_socket_accept
 *
 * Parameters:
 * - sock: apr_socket_t *
 * - connection_pool: apr_pool_t *
 * Return Type: [apr_status_t, apr_socket_t]
 */
mrb_value
mrb_APR_apr_socket_accept(mrb_state* mrb, mrb_value self) {
  mrb_value sock;
  mrb_value connection_pool;

  /* Fetch the args */
  mrb_get_args(mrb, "oo", &sock, &connection_pool);

  /* Type checking */
  if (!mrb_obj_is_kind_of(mrb, sock, AprSocketT_class(mrb))) {
    mrb_raise(mrb, E_TYPE_ERROR, "AprSocketT expected");
    return mrb_nil_value();
  }
  if (!mrb_obj_is_kind_of(mrb, connection_pool, AprPoolT_class(mrb))) {
    mrb_raise(mrb, E_TYPE_ERROR, "AprPoolT expected");
    return mrb_nil_value();
  }

  /* Unbox parameters */
  apr_socket_t * native_sock = (mrb_nil_p(sock) ? NULL : mruby_unbox_apr_socket_t(sock));
  apr_pool_t * native_connection_pool = (mrb_nil_p(connection_pool) ? NULL : mruby_unbox_apr_pool_t(connection_pool));

  /* Invocation */
  apr_socket_t * native_new_sock;
  apr_status_t result = apr_socket_accept(&native_new_sock, native_sock, native_connection_pool);

  /* Box the return value */
  if (result > MRB_INT_MAX) {
    mrb_raise(mrb, mrb->eStandardError_class, "MRuby cannot represent integers greater than MRB_INT_MAX");
    return mrb_nil_value();
  }
  RETURN_ERRNO_AND_OUTPUT(result, mruby_box_apr_socket_t(mrb, native_new_sock));
}
#endif
/* MRUBY_BINDING_END */

/* MRUBY_BINDING: apr_socket_addr_get */
/* sha: user_edited */
#if BIND_apr_socket_addr_get_FUNCTION
#define apr_socket_addr_get_REQUIRED_ARGC 2
#define apr_socket_addr_get_OPTIONAL_ARGC 0
/* apr_socket_addr_get
 *
 * Parameters:
 * - which: Fixnum
 * - sock: AprSocketT
 * Return Type: [errno: Fixnum, sock_addr: AprSockaddrT]
 */
mrb_value
mrb_APR_apr_socket_addr_get(mrb_state* mrb, mrb_value self) {
  mrb_int native_which;
  mrb_value sock;

  /* Fetch the args */
  mrb_get_args(mrb, "io", &native_which, &sock);

  /* Type checking */
  if (!mrb_obj_is_kind_of(mrb, sock, AprSocketT_class(mrb))) {
    mrb_raise(mrb, E_TYPE_ERROR, "AprSocketT expected");
    return mrb_nil_value();
  }

  /* Unbox parameters */

  apr_socket_t * native_sock = (mrb_nil_p(sock) ? NULL : mruby_unbox_apr_socket_t(sock));

  /* Invocation */
  apr_sockaddr_t * native_sa;
  apr_status_t result = apr_socket_addr_get(&native_sa, native_which, native_sock);
  RETURN_ERRNO_AND_OUTPUT(result, mruby_box_apr_sockaddr_t(mrb, native_sa));
}
#endif
/* MRUBY_BINDING_END */

/* MRUBY_BINDING: apr_socket_atmark */
/* sha: 59a6192e1a8de836103a411a7acf99265d0e443e4c6bf5497763471146dcf0b6 */
#if BIND_apr_socket_atmark_FUNCTION
#define apr_socket_atmark_REQUIRED_ARGC 2
#define apr_socket_atmark_OPTIONAL_ARGC 0
/* apr_status_t apr_socket_atmark(apr_socket_t * sock, int * atmark) */
mrb_value
mrb_APR_apr_socket_atmark(mrb_state* mrb, mrb_value self) {
  mrb_value sock;
  mrb_value atmark;

  /* Fetch the args */
  mrb_get_args(mrb, "oo", &sock, &atmark);

  /* Type checking */
  if (!mrb_obj_is_kind_of(mrb, sock, AprSocketT_class(mrb))) {
    mrb_raise(mrb, E_TYPE_ERROR, "AprSocketT expected");
    return mrb_nil_value();
  }
  TODO_type_check_int_PTR(atmark);

  /* Unbox param: sock */
  apr_socket_t * native_sock = (mrb_nil_p(sock) ? NULL : mruby_unbox_apr_socket_t(sock));

  /* Unbox param: atmark */
  int * native_atmark = TODO_mruby_unbox_int_PTR(atmark);

  /* Invocation */
  apr_status_t native_return_value = apr_socket_atmark(native_sock, native_atmark);

  /* Box the return value */
  mrb_value return_value = mrb_fixnum_value(native_return_value);
  
  return return_value;
}
#endif
/* MRUBY_BINDING_END */

/* MRUBY_BINDING: apr_socket_atreadeof */
/* sha: user_edited */
#if BIND_apr_socket_atreadeof_FUNCTION
#define apr_socket_atreadeof_REQUIRED_ARGC 1
#define apr_socket_atreadeof_OPTIONAL_ARGC 0
/* apr_socket_atreadeof
 *
 * Parameters:
 * - sock: apr_socket_t *
 * Return Type: [err: AprStatusT, at_eof: Boolean]
 */
mrb_value
mrb_APR_apr_socket_atreadeof(mrb_state* mrb, mrb_value self) {
  mrb_value sock;

  /* Fetch the args */
  mrb_get_args(mrb, "o", &sock);

  /* Type checking */
  if (!mrb_obj_is_kind_of(mrb, sock, AprSocketT_class(mrb))) {
    mrb_raise(mrb, E_TYPE_ERROR, "AprSocketT expected");
    return mrb_nil_value();
  }

  /* Unbox parameters */
  apr_socket_t * native_sock = (mrb_nil_p(sock) ? NULL : mruby_unbox_apr_socket_t(sock));

  /* Invocation */
  int native_atreadeof = 0;
  apr_status_t result = apr_socket_atreadeof(native_sock, &native_atreadeof);

  RETURN_ERRNO_AND_OUTPUT(result, mrb_bool_value(native_atreadeof));
}
#endif
/* MRUBY_BINDING_END */

/* MRUBY_BINDING: apr_socket_bind */
/* sha: user_edited */
#if BIND_apr_socket_bind_FUNCTION
#define apr_socket_bind_REQUIRED_ARGC 2
#define apr_socket_bind_OPTIONAL_ARGC 0
/* apr_socket_bind
 *
 * Parameters:
 * - sock: apr_socket_t *
 * - sa: apr_sockaddr_t *
 * Return Type: apr_status_t
 */
mrb_value
mrb_APR_apr_socket_bind(mrb_state* mrb, mrb_value self) {
  mrb_value sock;
  mrb_value sa;

  /* Fetch the args */
  mrb_get_args(mrb, "oo", &sock, &sa);

  /* Type checking */
  if (!mrb_obj_is_kind_of(mrb, sock, AprSocketT_class(mrb))) {
    mrb_raise(mrb, E_TYPE_ERROR, "AprSocketT expected");
    return mrb_nil_value();
  }
  if (!mrb_obj_is_kind_of(mrb, sa, AprSockaddrT_class(mrb))) {
    mrb_raise(mrb, E_TYPE_ERROR, "AprSockaddrT expected");
    return mrb_nil_value();
  }

  /* Unbox parameters */
  apr_socket_t * native_sock = (mrb_nil_p(sock) ? NULL : mruby_unbox_apr_socket_t(sock));
  apr_sockaddr_t * native_sa = (mrb_nil_p(sa) ? NULL : mruby_unbox_apr_sockaddr_t(sa));

  /* Invocation */
  apr_status_t result = apr_socket_bind(native_sock, native_sa);

  /* Box the return value */
  if (result > MRB_INT_MAX) {
    mrb_raise(mrb, mrb->eStandardError_class, "MRuby cannot represent integers greater than MRB_INT_MAX");
    return mrb_nil_value();
  }
  mrb_value return_value = mrb_fixnum_value(result);

  return return_value;
}
#endif
/* MRUBY_BINDING_END */

/* MRUBY_BINDING: apr_socket_close */
/* sha: user_edited */
#if BIND_apr_socket_close_FUNCTION
#define apr_socket_close_REQUIRED_ARGC 1
#define apr_socket_close_OPTIONAL_ARGC 0
/* apr_socket_close
 *
 * Parameters:
 * - thesocket: apr_socket_t *
 * Return Type: apr_status_t
 */
mrb_value
mrb_APR_apr_socket_close(mrb_state* mrb, mrb_value self) {
  mrb_value thesocket;

  /* Fetch the args */
  mrb_get_args(mrb, "o", &thesocket);

  /* Type checking */
  if (!mrb_obj_is_kind_of(mrb, thesocket, AprSocketT_class(mrb))) {
    mrb_raise(mrb, E_TYPE_ERROR, "AprSocketT expected");
    return mrb_nil_value();
  }

  /* Unbox parameters */
  apr_socket_t * native_thesocket = (mrb_nil_p(thesocket) ? NULL : mruby_unbox_apr_socket_t(thesocket));

  /* Invocation */
  apr_status_t result = apr_socket_close(native_thesocket);

  /* Box the return value */
  if (result > MRB_INT_MAX) {
    mrb_raise(mrb, mrb->eStandardError_class, "MRuby cannot represent integers greater than MRB_INT_MAX");
    return mrb_nil_value();
  }
  mrb_value return_value = mrb_fixnum_value(result);

  return return_value;
}
#endif
/* MRUBY_BINDING_END */

/* MRUBY_BINDING: apr_socket_connect */
/* sha: user_edited */
#if BIND_apr_socket_connect_FUNCTION
#define apr_socket_connect_REQUIRED_ARGC 2
#define apr_socket_connect_OPTIONAL_ARGC 0
/* apr_socket_connect
 *
 * Parameters:
 * - sock: apr_socket_t *
 * - sa: apr_sockaddr_t *
 * Return Type: apr_status_t
 */
mrb_value
mrb_APR_apr_socket_connect(mrb_state* mrb, mrb_value self) {
  mrb_value sock;
  mrb_value sa;

  /* Fetch the args */
  mrb_get_args(mrb, "oo", &sock, &sa);

  /* Type checking */
  if (!mrb_obj_is_kind_of(mrb, sock, AprSocketT_class(mrb))) {
    mrb_raise(mrb, E_TYPE_ERROR, "AprSocketT expected");
    return mrb_nil_value();
  }
  if (!mrb_obj_is_kind_of(mrb, sa, AprSockaddrT_class(mrb))) {
    mrb_raise(mrb, E_TYPE_ERROR, "AprSockaddrT expected");
    return mrb_nil_value();
  }

  /* Unbox parameters */
  apr_socket_t * native_sock = (mrb_nil_p(sock) ? NULL : mruby_unbox_apr_socket_t(sock));
  apr_sockaddr_t * native_sa = (mrb_nil_p(sa) ? NULL : mruby_unbox_apr_sockaddr_t(sa));

  /* Invocation */
  apr_status_t result = apr_socket_connect(native_sock, native_sa);

  /* Box the return value */
  if (result > MRB_INT_MAX) {
    mrb_raise(mrb, mrb->eStandardError_class, "MRuby cannot represent integers greater than MRB_INT_MAX");
    return mrb_nil_value();
  }
  mrb_value return_value = mrb_fixnum_value(result);

  return return_value;
}
#endif
/* MRUBY_BINDING_END */

/* MRUBY_BINDING: apr_socket_create */
/* sha: user_edited */
#if BIND_apr_socket_create_FUNCTION
#define apr_socket_create_REQUIRED_ARGC 5
#define apr_socket_create_OPTIONAL_ARGC 0
/* apr_socket_create
 *
 * Parameters:
 * - family: int
 * - type: int
 * - protocol: int
 * - cont: apr_pool_t *
 * Return Type: apr_status_t
 */
mrb_value
mrb_APR_apr_socket_create(mrb_state* mrb, mrb_value self) {
  mrb_int native_family;
  mrb_int native_type;
  mrb_int native_protocol;
  mrb_value cont;

  /* Fetch the args */
  mrb_get_args(mrb, "iiio", &native_family, &native_type, &native_protocol, &cont);

  /* Type checking */
  if (!mrb_obj_is_kind_of(mrb, cont, AprPoolT_class(mrb))) {
    mrb_raise(mrb, E_TYPE_ERROR, "AprPoolT expected");
    return mrb_nil_value();
  }

  /* Unbox parameters */

  apr_pool_t * native_cont = (mrb_nil_p(cont) ? NULL : mruby_unbox_apr_pool_t(cont));

  /* Invocation */
  apr_socket_t * native_new_sock;
  apr_status_t result = apr_socket_create(&native_new_sock, native_family, native_type, native_protocol, native_cont);

  /* Box the return value */
  if (result > MRB_INT_MAX) {
    mrb_raise(mrb, mrb->eStandardError_class, "MRuby cannot represent integers greater than MRB_INT_MAX");
    return mrb_nil_value();
  }
  RETURN_ERRNO_AND_OUTPUT(result, mruby_box_apr_socket_t(mrb, native_new_sock));
}
#endif
/* MRUBY_BINDING_END */

/* MRUBY_BINDING: apr_socket_data_get */
/* sha: 42040e11c5af5353f1ca867234f54a590a2390035ff314c40544de206920212f */
#if BIND_apr_socket_data_get_FUNCTION
#define apr_socket_data_get_REQUIRED_ARGC 3
#define apr_socket_data_get_OPTIONAL_ARGC 0
/* apr_status_t apr_socket_data_get(void ** data, const char * key, apr_socket_t * sock) */
mrb_value
mrb_APR_apr_socket_data_get(mrb_state* mrb, mrb_value self) {
  mrb_value data;
  char * native_key = NULL;
  mrb_value sock;

  /* Fetch the args */
  mrb_get_args(mrb, "ozo", &data, &native_key, &sock);

  /* Type checking */
  TODO_type_check_void_PTR_PTR(data);
  if (!mrb_obj_is_kind_of(mrb, sock, AprSocketT_class(mrb))) {
    mrb_raise(mrb, E_TYPE_ERROR, "AprSocketT expected");
    return mrb_nil_value();
  }

  /* Unbox param: data */
  void ** native_data = TODO_mruby_unbox_void_PTR_PTR(data);

  /* Unbox param: sock */
  apr_socket_t * native_sock = (mrb_nil_p(sock) ? NULL : mruby_unbox_apr_socket_t(sock));

  /* Invocation */
  apr_status_t native_return_value = apr_socket_data_get(native_data, native_key, native_sock);

  /* Box the return value */
  mrb_value return_value = mrb_fixnum_value(native_return_value);
  
  return return_value;
}
#endif
/* MRUBY_BINDING_END */

/* MRUBY_BINDING: apr_socket_data_set */
/* sha: 12f5c480e9df7c594b9f2e3d0b7845010d15db5be4088f721a191e42a1000e94 */
#if BIND_apr_socket_data_set_FUNCTION
#define apr_socket_data_set_REQUIRED_ARGC 4
#define apr_socket_data_set_OPTIONAL_ARGC 0
/* apr_status_t apr_socket_data_set(apr_socket_t * sock, void * data, const char * key, apr_status_t (*)(void *) cleanup) */
mrb_value
mrb_APR_apr_socket_data_set(mrb_state* mrb, mrb_value self) {
  mrb_value sock;
  mrb_value data;
  char * native_key = NULL;
  mrb_value cleanup;

  /* Fetch the args */
  mrb_get_args(mrb, "oozo", &sock, &data, &native_key, &cleanup);

  /* Type checking */
  if (!mrb_obj_is_kind_of(mrb, sock, AprSocketT_class(mrb))) {
    mrb_raise(mrb, E_TYPE_ERROR, "AprSocketT expected");
    return mrb_nil_value();
  }
  TODO_type_check_void_PTR(data);
  TODO_type_check_apr_status_t_LPAREN_PTR_RPAREN_LPAREN_void_PTR_RPAREN(cleanup);

  /* Unbox param: sock */
  apr_socket_t * native_sock = (mrb_nil_p(sock) ? NULL : mruby_unbox_apr_socket_t(sock));

  /* Unbox param: data */
  void * native_data = TODO_mruby_unbox_void_PTR(data);

  /* Unbox param: cleanup */
  apr_status_t (*native_cleanup)(void *) = TODO_mruby_unbox_apr_status_t_LPAREN_PTR_RPAREN_LPAREN_void_PTR_RPAREN(cleanup);

  /* Invocation */
  apr_status_t native_return_value = apr_socket_data_set(native_sock, native_data, native_key, native_cleanup);

  /* Box the return value */
  mrb_value return_value = mrb_fixnum_value(native_return_value);
  
  return return_value;
}
#endif
/* MRUBY_BINDING_END */

/* MRUBY_BINDING: apr_socket_listen */
/* sha: user_edited */
#if BIND_apr_socket_listen_FUNCTION
#define apr_socket_listen_REQUIRED_ARGC 2
#define apr_socket_listen_OPTIONAL_ARGC 0
/* apr_socket_listen
 *
 * Parameters:
 * - sock: apr_socket_t *
 * - backlog: int
 * Return Type: apr_status_t
 */
mrb_value
mrb_APR_apr_socket_listen(mrb_state* mrb, mrb_value self) {
  mrb_value sock;
  mrb_int native_backlog;

  /* Fetch the args */
  mrb_get_args(mrb, "oi", &sock, &native_backlog);

  /* Type checking */
  if (!mrb_obj_is_kind_of(mrb, sock, AprSocketT_class(mrb))) {
    mrb_raise(mrb, E_TYPE_ERROR, "AprSocketT expected");
    return mrb_nil_value();
  }

  /* Unbox parameters */
  apr_socket_t * native_sock = (mrb_nil_p(sock) ? NULL : mruby_unbox_apr_socket_t(sock));

  /* Invocation */
  apr_status_t result = apr_socket_listen(native_sock, native_backlog);

  /* Box the return value */
  if (result > MRB_INT_MAX) {
    mrb_raise(mrb, mrb->eStandardError_class, "MRuby cannot represent integers greater than MRB_INT_MAX");
    return mrb_nil_value();
  }
  mrb_value return_value = mrb_fixnum_value(result);

  return return_value;
}
#endif
/* MRUBY_BINDING_END */

/* MRUBY_BINDING: apr_socket_opt_get */
/* sha: user_edited */
#if BIND_apr_socket_opt_get_FUNCTION
#define apr_socket_opt_get_REQUIRED_ARGC 2
#define apr_socket_opt_get_OPTIONAL_ARGC 0
/* apr_socket_opt_get
 *
 * Parameters:
 * - sock: apr_socket_t *
 * - opt: int
 * Return Type: apr_status_t
 */
mrb_value
mrb_APR_apr_socket_opt_get(mrb_state* mrb, mrb_value self) {
  mrb_value sock;
  mrb_int native_opt;

  /* Fetch the args */
  mrb_get_args(mrb, "oi", &sock, &native_opt);

  /* Type checking */
  if (!mrb_obj_is_kind_of(mrb, sock, AprSocketT_class(mrb))) {
    mrb_raise(mrb, E_TYPE_ERROR, "AprSocketT expected");
    return mrb_nil_value();
  }

  /* Unbox parameters */
  apr_socket_t * native_sock = (mrb_nil_p(sock) ? NULL : mruby_unbox_apr_socket_t(sock));

  /* Invocation */
  apr_int32_t native_on = 0;
  apr_status_t result = apr_socket_opt_get(native_sock, native_opt, &native_on);

  /* Box the return value */
  if (result > MRB_INT_MAX) {
    mrb_raise(mrb, mrb->eStandardError_class, "MRuby cannot represent integers greater than MRB_INT_MAX");
    return mrb_nil_value();
  }
  RETURN_ERRNO_AND_OUTPUT(result, mrb_fixnum_value(native_on));
}
#endif
/* MRUBY_BINDING_END */

/* MRUBY_BINDING: apr_socket_opt_set */
/* sha: user_edited */
#if BIND_apr_socket_opt_set_FUNCTION
#define apr_socket_opt_set_REQUIRED_ARGC 3
#define apr_socket_opt_set_OPTIONAL_ARGC 0
/* apr_socket_opt_set
 *
 * Parameters:
 * - sock: apr_socket_t *
 * - opt: int
 * - on: int
 * Return Type: apr_status_t
 */
mrb_value
mrb_APR_apr_socket_opt_set(mrb_state* mrb, mrb_value self) {
  mrb_value sock;
  mrb_int native_opt;
  mrb_int native_on;

  /* Fetch the args */
  mrb_get_args(mrb, "oii", &sock, &native_opt, &native_on);

  /* Type checking */
  if (!mrb_obj_is_kind_of(mrb, sock, AprSocketT_class(mrb))) {
    mrb_raise(mrb, E_TYPE_ERROR, "AprSocketT expected");
    return mrb_nil_value();
  }

  /* Unbox parameters */
  apr_socket_t * native_sock = (mrb_nil_p(sock) ? NULL : mruby_unbox_apr_socket_t(sock));

  /* Invocation */
  apr_status_t result = apr_socket_opt_set(native_sock, native_opt, native_on);

  /* Box the return value */
  if (result > MRB_INT_MAX) {
    mrb_raise(mrb, mrb->eStandardError_class, "MRuby cannot represent integers greater than MRB_INT_MAX");
    return mrb_nil_value();
  }
  mrb_value return_value = mrb_fixnum_value(result);

  return return_value;
}
#endif
/* MRUBY_BINDING_END */

/* MRUBY_BINDING: apr_socket_protocol_get */
/* sha: user_edited */
#if BIND_apr_socket_protocol_get_FUNCTION
#define apr_socket_protocol_get_REQUIRED_ARGC 1
#define apr_socket_protocol_get_OPTIONAL_ARGC 0
/* apr_socket_protocol_get
 *
 * Parameters:
 * - sock: apr_socket_t *
 * Return Type: [errno: Fixnum, protocol: Fixnum]
 */
mrb_value
mrb_APR_apr_socket_protocol_get(mrb_state* mrb, mrb_value self) {
  mrb_value sock;

  /* Fetch the args */
  mrb_get_args(mrb, "o", &sock);

  /* Type checking */
  if (!mrb_obj_is_kind_of(mrb, sock, AprSocketT_class(mrb))) {
    mrb_raise(mrb, E_TYPE_ERROR, "AprSocketT expected");
    return mrb_nil_value();
  }

  /* Unbox parameters */
  apr_socket_t * native_sock = (mrb_nil_p(sock) ? NULL : mruby_unbox_apr_socket_t(sock));

  /* Invocation */
  int native_protocol;
  apr_status_t result = apr_socket_protocol_get(native_sock, &native_protocol);

  /* Box the return value */
  if (result > MRB_INT_MAX) {
    mrb_raise(mrb, mrb->eStandardError_class, "MRuby cannot represent integers greater than MRB_INT_MAX");
    return mrb_nil_value();
  }
  RETURN_ERRNO_AND_OUTPUT(result, mrb_fixnum_value(native_protocol));
}
#endif
/* MRUBY_BINDING_END */

/* MRUBY_BINDING: apr_socket_recv */
/* sha: user_edited */
#if BIND_apr_socket_recv_FUNCTION
#define apr_socket_recv_REQUIRED_ARGC 2
#define apr_socket_recv_OPTIONAL_ARGC 0
/* apr_socket_recv
 *
 * Parameters:
 * - sock: AprSocketT
 * - len: Fixnum
 * Return Type: [errno: Fixnum, message: String]
 */
mrb_value
mrb_APR_apr_socket_recv(mrb_state* mrb, mrb_value self) {
  mrb_value sock;
  mrb_int native_len;

  /* Fetch the args */
  mrb_get_args(mrb, "oi", &sock, &native_len);

  /* Type checking */
  if (!mrb_obj_is_kind_of(mrb, sock, AprSocketT_class(mrb))) {
    mrb_raise(mrb, E_TYPE_ERROR, "AprSocketT expected");
    return mrb_nil_value();
  }

  /* Unbox parameters */
  apr_socket_t * native_sock = (mrb_nil_p(sock) ? NULL : mruby_unbox_apr_socket_t(sock));

  /* Invocation */
  char * native_buf = (char*)malloc(native_len);
  apr_size_t size = native_len;
  apr_status_t result = apr_socket_recv(native_sock, native_buf, &size);

  /* Box the return value */
  if (result > MRB_INT_MAX) {
    mrb_raise(mrb, mrb->eStandardError_class, "MRuby cannot represent integers greater than MRB_INT_MAX");
    return mrb_nil_value();
  }

  mrb_value result_string = mrb_str_new(mrb, native_buf, size);
  free(native_buf);
  native_buf = NULL;

  mrb_value results = mrb_ary_new(mrb);
  mrb_ary_push(mrb, results, mrb_fixnum_value(result));
  /* There can be an error, such as EOF, and still have bytes read, so always return this string. */
  mrb_ary_push(mrb, results, result_string);

  return results;
}
#endif
/* MRUBY_BINDING_END */

/* MRUBY_BINDING: apr_socket_recvfrom */
/* sha: user_edited */
#if BIND_apr_socket_recvfrom_FUNCTION
#define apr_socket_recvfrom_REQUIRED_ARGC 3
#define apr_socket_recvfrom_OPTIONAL_ARGC 0
/* apr_socket_recvfrom
 *
 * Parameters:
 * - sock: AprSocketT
 * - flags: Fixnum
 * - len: Fixnum
 * Return Type: [errno: Fixnum, from: AprSocketT, buffer: String]
 */
mrb_value
mrb_APR_apr_socket_recvfrom(mrb_state* mrb, mrb_value self) {
  mrb_value sock;
  mrb_int native_flags;
  mrb_int native_len;

  /* Fetch the args */
  mrb_get_args(mrb, "oii", &sock, &native_flags, &native_len);

  /* Type checking */
  if (!mrb_obj_is_kind_of(mrb, sock, AprSocketT_class(mrb))) {
    mrb_raise(mrb, E_TYPE_ERROR, "AprSocketT expected");
    return mrb_nil_value();
  }

  /* Unbox parameters */
  apr_socket_t * native_sock = (mrb_nil_p(sock) ? NULL : mruby_unbox_apr_socket_t(sock));

  /* Invocation */
  char * native_buf = (char*)malloc(sizeof(char)*native_len); /* to free after duplicating via mrb_str_new */
  apr_sockaddr_t * native_from = (apr_sockaddr_t*)malloc(sizeof(apr_sockaddr_t)); /* to free in mrb GC (giftwrapped pointer) */
  apr_size_t size = native_len;
  apr_status_t result = apr_socket_recvfrom(native_from, native_sock, native_flags, native_buf, &size);

  /* Box the return value */
  if (result > MRB_INT_MAX) {
    mrb_raise(mrb, mrb->eStandardError_class, "MRuby cannot represent integers greater than MRB_INT_MAX");
    return mrb_nil_value();
  }
  mrb_value return_value = mrb_fixnum_value(result);

  mrb_value buffer = mrb_str_new(mrb, native_buf, size);
  free(native_buf);
  native_buf = NULL;

  /* The APR functions that operate on a sockaddr tend to require
   * a functioning `pool` member, but they don't come out with one.
   * So, create one, and reference it from the Ruby object so the GC
   * can take care of cleaning it up later.
   */
  mrb_value from = mruby_giftwrap_apr_sockaddr_t(mrb, native_from);
  apr_pool_create(&(native_from->pool), NULL);
  mrb_iv_set(mrb, from, mrb_intern_cstr(mrb, "@pool"), mruby_giftwrap_apr_pool_t(mrb, native_from->pool));

  mrb_value results = mrb_ary_new(mrb);
  mrb_ary_push(mrb, results, return_value);
  mrb_ary_push(mrb, results, from);
  mrb_ary_push(mrb, results, buffer);

  return results;
}
#endif
/* MRUBY_BINDING_END */

/* MRUBY_BINDING: apr_socket_send */
/* sha: user_edited */
#if BIND_apr_socket_send_FUNCTION
#define apr_socket_send_REQUIRED_ARGC 3
#define apr_socket_send_OPTIONAL_ARGC 0
/* apr_socket_send
 *
 * Parameters:
 * - sock: AprSocketT
 * - buf: String
 * - len: Fixnum
 * Return Type: [errno: Fixnum, bytes_sent: Fixnum]
 */
mrb_value
mrb_APR_apr_socket_send(mrb_state* mrb, mrb_value self) {
  mrb_value sock;
  mrb_value buf;
  mrb_int native_len;

  /* Fetch the args */
  mrb_get_args(mrb, "ooi", &sock, &buf, &native_len);

  /* Type checking */
  if (!mrb_obj_is_kind_of(mrb, sock, AprSocketT_class(mrb))) {
    mrb_raise(mrb, E_TYPE_ERROR, "AprSocketT expected");
    return mrb_nil_value();
  }
  if (!mrb_obj_is_kind_of(mrb, buf, mrb->string_class)) {
    mrb_raise(mrb, E_TYPE_ERROR, "String expected");
    return mrb_nil_value();
  }

  /* Unbox parameters */
  apr_socket_t * native_sock = (mrb_nil_p(sock) ? NULL : mruby_unbox_apr_socket_t(sock));
  const char * native_buf = mrb_string_value_ptr(mrb, buf);

  /* Invocation */
  apr_size_t size = native_len;
  apr_status_t result = apr_socket_send(native_sock, native_buf, &size);

  /* Box the return value */
  if (result > MRB_INT_MAX) {
    mrb_raise(mrb, mrb->eStandardError_class, "MRuby cannot represent integers greater than MRB_INT_MAX");
    return mrb_nil_value();
  }
  RETURN_ERRNO_AND_OUTPUT(result, mrb_fixnum_value(size));
}
#endif
/* MRUBY_BINDING_END */

/* MRUBY_BINDING: apr_socket_sendfile */
/* sha: 25112d380f59506a3bbdf22d04cab2789c99738a0ff0c29e5e7063b1bea6461a */
#if BIND_apr_socket_sendfile_FUNCTION
#define apr_socket_sendfile_REQUIRED_ARGC 6
#define apr_socket_sendfile_OPTIONAL_ARGC 0
/* apr_status_t apr_socket_sendfile(apr_socket_t * sock, apr_file_t * file, apr_hdtr_t * hdtr, apr_off_t * offset, apr_size_t * len, apr_int32_t flags) */
mrb_value
mrb_APR_apr_socket_sendfile(mrb_state* mrb, mrb_value self) {
  mrb_value sock;
  mrb_value file;
  mrb_value hdtr;
  mrb_value offset;
  mrb_value len;
  mrb_int native_flags;

  /* Fetch the args */
  mrb_get_args(mrb, "oooooi", &sock, &file, &hdtr, &offset, &len, &native_flags);

  /* Type checking */
  if (!mrb_obj_is_kind_of(mrb, sock, AprSocketT_class(mrb))) {
    mrb_raise(mrb, E_TYPE_ERROR, "AprSocketT expected");
    return mrb_nil_value();
  }
  if (!mrb_obj_is_kind_of(mrb, file, AprFileT_class(mrb))) {
    mrb_raise(mrb, E_TYPE_ERROR, "AprFileT expected");
    return mrb_nil_value();
  }
  if (!mrb_obj_is_kind_of(mrb, hdtr, AprHdtrT_class(mrb))) {
    mrb_raise(mrb, E_TYPE_ERROR, "AprHdtrT expected");
    return mrb_nil_value();
  }
  TODO_type_check_apr_off_t_PTR(offset);
  TODO_type_check_apr_size_t_PTR(len);

  /* Unbox param: sock */
  apr_socket_t * native_sock = (mrb_nil_p(sock) ? NULL : mruby_unbox_apr_socket_t(sock));

  /* Unbox param: file */
  apr_file_t * native_file = (mrb_nil_p(file) ? NULL : mruby_unbox_apr_file_t(file));

  /* Unbox param: hdtr */
  apr_hdtr_t * native_hdtr = (mrb_nil_p(hdtr) ? NULL : mruby_unbox_apr_hdtr_t(hdtr));

  /* Unbox param: offset */
  apr_off_t * native_offset = TODO_mruby_unbox_apr_off_t_PTR(offset);

  /* Unbox param: len */
  apr_size_t * native_len = TODO_mruby_unbox_apr_size_t_PTR(len);

  /* Invocation */
  apr_status_t native_return_value = apr_socket_sendfile(native_sock, native_file, native_hdtr, native_offset, native_len, native_flags);

  /* Box the return value */
  mrb_value return_value = mrb_fixnum_value(native_return_value);
  
  return return_value;
}
#endif
/* MRUBY_BINDING_END */

/* MRUBY_BINDING: apr_socket_sendto */
/* sha: user_edited */
#if BIND_apr_socket_sendto_FUNCTION
#define apr_socket_sendto_REQUIRED_ARGC 5
#define apr_socket_sendto_OPTIONAL_ARGC 0
/* apr_socket_sendto
 *
 * Parameters:
 * - sock: apr_socket_t *
 * - where: apr_sockaddr_t *
 * - flags: int
 * - buf: const char *
 * - len: int *
 * Return Type: errno: Fixnum, bytes_written: Fixnum
 */
mrb_value
mrb_APR_apr_socket_sendto(mrb_state* mrb, mrb_value self) {
  mrb_value sock;
  mrb_value where;
  mrb_int native_flags;
  char * native_buf;
  mrb_int native_len;

  /* Fetch the args */
  mrb_get_args(mrb, "ooizi", &sock, &where, &native_flags, &native_buf, &native_len);

  /* Type checking */
  if (!mrb_obj_is_kind_of(mrb, sock, AprSocketT_class(mrb))) {
    mrb_raise(mrb, E_TYPE_ERROR, "AprSocketT expected");
    return mrb_nil_value();
  }
  if (!mrb_obj_is_kind_of(mrb, where, AprSockaddrT_class(mrb))) {
    mrb_raise(mrb, E_TYPE_ERROR, "AprSockaddrT expected");
    return mrb_nil_value();
  }

  /* Unbox parameters */
  apr_socket_t * native_sock = (mrb_nil_p(sock) ? NULL : mruby_unbox_apr_socket_t(sock));
  apr_sockaddr_t * native_where = (mrb_nil_p(where) ? NULL : mruby_unbox_apr_sockaddr_t(where));

  /* Invocation */
  apr_size_t size = native_len;
  apr_status_t result = apr_socket_sendto(native_sock, native_where, native_flags, native_buf, &size);

  /* Box the return value */
  if (result > MRB_INT_MAX) {
    mrb_raise(mrb, mrb->eStandardError_class, "MRuby cannot represent integers greater than MRB_INT_MAX");
    return mrb_nil_value();
  }

  RETURN_ERRNO_AND_OUTPUT(result, mrb_fixnum_value(size));
}
#endif
/* MRUBY_BINDING_END */

/* MRUBY_BINDING: apr_socket_sendv */
/* sha: 0f64b8bb81bd03b397c98a550406d89c1dbd142385624557f29a3b86d9c2ca84 */
#if BIND_apr_socket_sendv_FUNCTION
#define apr_socket_sendv_REQUIRED_ARGC 4
#define apr_socket_sendv_OPTIONAL_ARGC 0
/* apr_status_t apr_socket_sendv(apr_socket_t * sock, const struct iovec * vec, apr_int32_t nvec, apr_size_t * len) */
mrb_value
mrb_APR_apr_socket_sendv(mrb_state* mrb, mrb_value self) {
  mrb_value sock;
  mrb_value vec;
  mrb_int native_nvec;
  mrb_value len;

  /* Fetch the args */
  mrb_get_args(mrb, "ooio", &sock, &vec, &native_nvec, &len);

  /* Type checking */
  if (!mrb_obj_is_kind_of(mrb, sock, AprSocketT_class(mrb))) {
    mrb_raise(mrb, E_TYPE_ERROR, "AprSocketT expected");
    return mrb_nil_value();
  }
  TODO_type_check_iovec_PTR(vec);
  TODO_type_check_apr_size_t_PTR(len);

  /* Unbox param: sock */
  apr_socket_t * native_sock = (mrb_nil_p(sock) ? NULL : mruby_unbox_apr_socket_t(sock));

  /* Unbox param: vec */
  const struct iovec * native_vec = TODO_mruby_unbox_iovec_PTR(vec);

  /* Unbox param: len */
  apr_size_t * native_len = TODO_mruby_unbox_apr_size_t_PTR(len);

  /* Invocation */
  apr_status_t native_return_value = apr_socket_sendv(native_sock, native_vec, native_nvec, native_len);

  /* Box the return value */
  mrb_value return_value = mrb_fixnum_value(native_return_value);
  
  return return_value;
}
#endif
/* MRUBY_BINDING_END */

/* MRUBY_BINDING: apr_socket_shutdown */
/* sha: user_edited */
#if BIND_apr_socket_shutdown_FUNCTION
#define apr_socket_shutdown_REQUIRED_ARGC 2
#define apr_socket_shutdown_OPTIONAL_ARGC 0
/* apr_socket_shutdown
 *
 * Parameters:
 * - thesocket: apr_socket_t *
 * - how: apr_shutdown_how_e
 * Return Type: apr_status_t
 */
mrb_value
mrb_APR_apr_socket_shutdown(mrb_state* mrb, mrb_value self) {
  mrb_value thesocket;
  mrb_int native_how;

  /* Fetch the args */
  mrb_get_args(mrb, "oi", &thesocket, &native_how);

  /* Type checking */
  if (!mrb_obj_is_kind_of(mrb, thesocket, AprSocketT_class(mrb))) {
    mrb_raise(mrb, E_TYPE_ERROR, "AprSocketT expected");
    return mrb_nil_value();
  }

  /* Unbox parameters */
  apr_socket_t * native_thesocket = (mrb_nil_p(thesocket) ? NULL : mruby_unbox_apr_socket_t(thesocket));

  /* Invocation */
  apr_status_t result = apr_socket_shutdown(native_thesocket, native_how);

  /* Box the return value */
  if (result > MRB_INT_MAX) {
    mrb_raise(mrb, mrb->eStandardError_class, "MRuby cannot represent integers greater than MRB_INT_MAX");
    return mrb_nil_value();
  }
  mrb_value return_value = mrb_fixnum_value(result);

  return return_value;
}
#endif
/* MRUBY_BINDING_END */

/* MRUBY_BINDING: apr_socket_timeout_get */
/* sha: user_edited */
#if BIND_apr_socket_timeout_get_FUNCTION
#define apr_socket_timeout_get_REQUIRED_ARGC 2
#define apr_socket_timeout_get_OPTIONAL_ARGC 0
/* apr_socket_timeout_get
 *
 * Parameters:
 * - sock: apr_socket_t *
 * Return Type: [errno: Fixnum, timeout: Fixnum]
 */
mrb_value
mrb_APR_apr_socket_timeout_get(mrb_state* mrb, mrb_value self) {
  mrb_value sock;

  /* Fetch the args */
  mrb_get_args(mrb, "o", &sock);

  /* Type checking */
  if (!mrb_obj_is_kind_of(mrb, sock, AprSocketT_class(mrb))) {
    mrb_raise(mrb, E_TYPE_ERROR, "AprSocketT expected");
    return mrb_nil_value();
  }

  /* Unbox parameters */
  apr_socket_t * native_sock = (mrb_nil_p(sock) ? NULL : mruby_unbox_apr_socket_t(sock));

  /* Invocation */
  apr_interval_time_t native_t;
  apr_status_t result = apr_socket_timeout_get(native_sock, &native_t);

  /* Box the return value */
  if (result > MRB_INT_MAX) {
    mrb_raise(mrb, mrb->eStandardError_class, "MRuby cannot represent integers greater than MRB_INT_MAX");
    return mrb_nil_value();
  }
  if (native_t > MRB_INT_MAX) {
     mrb_raise(mrb, mrb->eStandardError_class, "MRuby cannot represent integers greater than MRB_INT_MAX");
     return mrb_nil_value();
  }
  RETURN_ERRNO_AND_OUTPUT(result, mrb_fixnum_value(native_t));
}
#endif
/* MRUBY_BINDING_END */

/* MRUBY_BINDING: apr_socket_timeout_set */
/* sha: user_edited */
#if BIND_apr_socket_timeout_set_FUNCTION
#define apr_socket_timeout_set_REQUIRED_ARGC 2
#define apr_socket_timeout_set_OPTIONAL_ARGC 0
/* apr_socket_timeout_set
 *
 * Parameters:
 * - sock: apr_socket_t *
 * - t: long long
 * Return Type: apr_status_t
 */
mrb_value
mrb_APR_apr_socket_timeout_set(mrb_state* mrb, mrb_value self) {
  mrb_value sock;
  mrb_int native_t;

  /* Fetch the args */
  mrb_get_args(mrb, "oi", &sock, &native_t);

  /* Type checking */
  if (!mrb_obj_is_kind_of(mrb, sock, AprSocketT_class(mrb))) {
    mrb_raise(mrb, E_TYPE_ERROR, "AprSocketT expected");
    return mrb_nil_value();
  }

  /* Unbox parameters */
  apr_socket_t * native_sock = (mrb_nil_p(sock) ? NULL : mruby_unbox_apr_socket_t(sock));

  /* Invocation */
  apr_status_t result = apr_socket_timeout_set(native_sock, native_t);

  /* Box the return value */
  if (result > MRB_INT_MAX) {
    mrb_raise(mrb, mrb->eStandardError_class, "MRuby cannot represent integers greater than MRB_INT_MAX");
    return mrb_nil_value();
  }
  mrb_value return_value = mrb_fixnum_value(result);

  return return_value;
}
#endif
/* MRUBY_BINDING_END */

/* MRUBY_BINDING: apr_socket_type_get */
/* sha: user_edited */
#if BIND_apr_socket_type_get_FUNCTION
#define apr_socket_type_get_REQUIRED_ARGC 2
#define apr_socket_type_get_OPTIONAL_ARGC 0
/* apr_socket_type_get
 *
 * Parameters:
 * - sock: apr_socket_t *
 * - type: int *
 * Return Type: apr_status_t
 */
mrb_value
mrb_APR_apr_socket_type_get(mrb_state* mrb, mrb_value self) {
  mrb_value sock;
  mrb_int native_type;

  /* Fetch the args */
  mrb_get_args(mrb, "oi", &sock, &native_type);

  /* Type checking */
  if (!mrb_obj_is_kind_of(mrb, sock, AprSocketT_class(mrb))) {
    mrb_raise(mrb, E_TYPE_ERROR, "AprSocketT expected");
    return mrb_nil_value();
  }

  /* Unbox parameters */
  apr_socket_t * native_sock = (mrb_nil_p(sock) ? NULL : mruby_unbox_apr_socket_t(sock));

  /* Invocation */
  apr_status_t result = apr_socket_type_get(native_sock, &native_type);

  /* Box the return value */
  if (result > MRB_INT_MAX) {
    mrb_raise(mrb, mrb->eStandardError_class, "MRuby cannot represent integers greater than MRB_INT_MAX");
    return mrb_nil_value();
  }
  RETURN_ERRNO_AND_OUTPUT(result, mrb_fixnum_value(native_type));
}
#endif
/* MRUBY_BINDING_END */

/* MRUBY_BINDING: apr_stat */
/* sha: user_edited */
#if BIND_apr_stat_FUNCTION
#define apr_stat_REQUIRED_ARGC 3
#define apr_stat_OPTIONAL_ARGC 0
/* apr_stat
 *
 * Parameters:
 * - fname: const char *
 * - wanted: int
 * - pool: apr_pool_t *
 * Return Type: apr_status_t
 */
mrb_value
mrb_APR_apr_stat(mrb_state* mrb, mrb_value self) {
  char* native_fname;
  mrb_int native_wanted;
  mrb_value pool;

  /* Fetch the args */
  mrb_get_args(mrb, "zio", &native_fname, &native_wanted, &pool);

  /* Type checking */
  if (!mrb_obj_is_kind_of(mrb, pool, AprPoolT_class(mrb))) {
    mrb_raise(mrb, E_TYPE_ERROR, "AprPoolT expected");
    return mrb_nil_value();
  }

  /* Unbox parameters */
  apr_pool_t * native_pool = (mrb_nil_p(pool) ? NULL : mruby_unbox_apr_pool_t(pool));

  /* Invocation */
  apr_finfo_t * native_finfo = (apr_finfo_t*)malloc(sizeof(apr_finfo_t));
  apr_status_t result = apr_stat(native_finfo, native_fname, native_wanted, native_pool);

  /* Box the return value */
  mrb_value results = mrb_ary_new(mrb);
  mrb_ary_push(mrb, results, mrb_fixnum_value(result));
  if (result == APR_SUCCESS || result == APR_INCOMPLETE) {
    mrb_ary_push(mrb, results, mruby_giftwrap_apr_finfo_t(mrb, native_finfo));
  } else {
    mrb_ary_push(mrb, results, mrb_nil_value());
  }
  return results;
}
#endif
/* MRUBY_BINDING_END */

/* MRUBY_BINDING: apr_strerror */
/* sha: user_edited */
#if BIND_apr_strerror_FUNCTION
#define apr_strerror_REQUIRED_ARGC 1
#define apr_strerror_OPTIONAL_ARGC 0
/* apr_strerror
 *
 * Parameters:
 * - statcode: Fixnum
 * Return Type: String
 */
mrb_value
mrb_APR_apr_strerror(mrb_state* mrb, mrb_value self) {
  mrb_int native_statcode;

  /* Fetch the args */
  mrb_get_args(mrb, "i", &native_statcode);

  /* Invocation */
  char*  native_buf = (char*)malloc(100);
  char * result = apr_strerror(native_statcode, native_buf, 100);

  /* Box the return value */
  mrb_value return_value = mrb_str_new_cstr(mrb, result);

  free(native_buf);
  native_buf = NULL;

  return return_value;
}
#endif
/* MRUBY_BINDING_END */

/* MRUBY_BINDING: apr_strfsize */
/* sha: 34c5b98316cd1e1e9fd2d62a22706704c6b27d38f3047b9aeb95eed05f71d0de */
#if BIND_apr_strfsize_FUNCTION
#define apr_strfsize_REQUIRED_ARGC 2
#define apr_strfsize_OPTIONAL_ARGC 0
/* char * apr_strfsize(apr_off_t size, char * buf) */
mrb_value
mrb_APR_apr_strfsize(mrb_state* mrb, mrb_value self) {
  mrb_value size;
  mrb_value buf;

  /* Fetch the args */
  mrb_get_args(mrb, "oo", &size, &buf);

  /* Type checking */
  TODO_type_check_apr_off_t(size);
  TODO_type_check_char_PTR(buf);

  /* Unbox param: size */
  apr_off_t native_size = TODO_mruby_unbox_apr_off_t(size);

  /* Unbox param: buf */
  char * native_buf = TODO_mruby_unbox_char_PTR(buf);

  /* Invocation */
  char * native_return_value = apr_strfsize(native_size, native_buf);

  /* Box the return value */
  mrb_value return_value = TODO_mruby_box_char_PTR(mrb, native_return_value);
  
  return return_value;
}
#endif
/* MRUBY_BINDING_END */

/* MRUBY_BINDING: apr_strftime */
/* sha: aaac83a0e043e8ec9426e6209a20ce45942d640c869087f306b48d071499cf25 */
#if BIND_apr_strftime_FUNCTION
#define apr_strftime_REQUIRED_ARGC 5
#define apr_strftime_OPTIONAL_ARGC 0
/* apr_status_t apr_strftime(char * s, apr_size_t * retsize, apr_size_t max, const char * format, apr_time_exp_t * tm) */
mrb_value
mrb_APR_apr_strftime(mrb_state* mrb, mrb_value self) {
  mrb_value s;
  mrb_value retsize;
  mrb_int native_max;
  char * native_format = NULL;
  mrb_value tm;

  /* Fetch the args */
  mrb_get_args(mrb, "ooizo", &s, &retsize, &native_max, &native_format, &tm);

  /* Type checking */
  TODO_type_check_char_PTR(s);
  TODO_type_check_apr_size_t_PTR(retsize);
  if (!mrb_obj_is_kind_of(mrb, tm, AprTimeExpT_class(mrb))) {
    mrb_raise(mrb, E_TYPE_ERROR, "AprTimeExpT expected");
    return mrb_nil_value();
  }

  /* Unbox param: s */
  char * native_s = TODO_mruby_unbox_char_PTR(s);

  /* Unbox param: retsize */
  apr_size_t * native_retsize = TODO_mruby_unbox_apr_size_t_PTR(retsize);

  /* Unbox param: tm */
  apr_time_exp_t * native_tm = (mrb_nil_p(tm) ? NULL : mruby_unbox_apr_time_exp_t(tm));

  /* Invocation */
  apr_status_t native_return_value = apr_strftime(native_s, native_retsize, native_max, native_format, native_tm);

  /* Box the return value */
  mrb_value return_value = mrb_fixnum_value(native_return_value);
  
  return return_value;
}
#endif
/* MRUBY_BINDING_END */

/* MRUBY_BINDING: apr_strnatcasecmp */
/* sha: 2cb35256f6d852314b90d9438345aac77d95592db8c6d8fee09f46bee0f92123 */
#if BIND_apr_strnatcasecmp_FUNCTION
#define apr_strnatcasecmp_REQUIRED_ARGC 2
#define apr_strnatcasecmp_OPTIONAL_ARGC 0
/* int apr_strnatcasecmp(const char * a, const char * b) */
mrb_value
mrb_APR_apr_strnatcasecmp(mrb_state* mrb, mrb_value self) {
  char * native_a = NULL;
  char * native_b = NULL;

  /* Fetch the args */
  mrb_get_args(mrb, "zz", &native_a, &native_b);

  /* Invocation */
  int native_return_value = apr_strnatcasecmp(native_a, native_b);

  /* Box the return value */
  mrb_value return_value = mrb_fixnum_value(native_return_value);
  
  return return_value;
}
#endif
/* MRUBY_BINDING_END */

/* MRUBY_BINDING: apr_strnatcmp */
/* sha: 760c3d15cf40bb8e1f1c618232a6ffcf5de2f8707d95020247d966d48a08941d */
#if BIND_apr_strnatcmp_FUNCTION
#define apr_strnatcmp_REQUIRED_ARGC 2
#define apr_strnatcmp_OPTIONAL_ARGC 0
/* int apr_strnatcmp(const char * a, const char * b) */
mrb_value
mrb_APR_apr_strnatcmp(mrb_state* mrb, mrb_value self) {
  char * native_a = NULL;
  char * native_b = NULL;

  /* Fetch the args */
  mrb_get_args(mrb, "zz", &native_a, &native_b);

  /* Invocation */
  int native_return_value = apr_strnatcmp(native_a, native_b);

  /* Box the return value */
  mrb_value return_value = mrb_fixnum_value(native_return_value);
  
  return return_value;
}
#endif
/* MRUBY_BINDING_END */

/* MRUBY_BINDING: apr_strtoff */
/* sha: 14a8f9f0435231cd74f2cb8a53c6091f48972b2b9a5623c9ebf97991b988da74 */
#if BIND_apr_strtoff_FUNCTION
#define apr_strtoff_REQUIRED_ARGC 4
#define apr_strtoff_OPTIONAL_ARGC 0
/* apr_status_t apr_strtoff(apr_off_t * offset, const char * buf, char ** end, int base) */
mrb_value
mrb_APR_apr_strtoff(mrb_state* mrb, mrb_value self) {
  mrb_value offset;
  char * native_buf = NULL;
  mrb_value end;
  mrb_int native_base;

  /* Fetch the args */
  mrb_get_args(mrb, "ozoi", &offset, &native_buf, &end, &native_base);

  /* Type checking */
  TODO_type_check_apr_off_t_PTR(offset);
  TODO_type_check_char_PTR_PTR(end);

  /* Unbox param: offset */
  apr_off_t * native_offset = TODO_mruby_unbox_apr_off_t_PTR(offset);

  /* Unbox param: end */
  char ** native_end = TODO_mruby_unbox_char_PTR_PTR(end);

  /* Invocation */
  apr_status_t native_return_value = apr_strtoff(native_offset, native_buf, native_end, native_base);

  /* Box the return value */
  mrb_value return_value = mrb_fixnum_value(native_return_value);
  
  return return_value;
}
#endif
/* MRUBY_BINDING_END */

/* MRUBY_BINDING: apr_strtoi64 */
/* sha: 5df149938b67e25a2ecc36210ce0d1635d2979e5380f9e200b48e60201b84228 */
#if BIND_apr_strtoi64_FUNCTION
#define apr_strtoi64_REQUIRED_ARGC 3
#define apr_strtoi64_OPTIONAL_ARGC 0
/* apr_int64_t apr_strtoi64(const char * buf, char ** end, int base) */
mrb_value
mrb_APR_apr_strtoi64(mrb_state* mrb, mrb_value self) {
  char * native_buf = NULL;
  mrb_value end;
  mrb_int native_base;

  /* Fetch the args */
  mrb_get_args(mrb, "zoi", &native_buf, &end, &native_base);

  /* Type checking */
  TODO_type_check_char_PTR_PTR(end);

  /* Unbox param: end */
  char ** native_end = TODO_mruby_unbox_char_PTR_PTR(end);

  /* Invocation */
  apr_int64_t native_return_value = apr_strtoi64(native_buf, native_end, native_base);

  /* Box the return value */
  mrb_value return_value = TODO_mruby_box_apr_int64_t(mrb, native_return_value);
  
  return return_value;
}
#endif
/* MRUBY_BINDING_END */

/* MRUBY_BINDING: apr_strtok */
/* sha: 8d8bea4f72fd3d57fc535b109717c63aaa9e0193f80fc8f63f002e56f2918b13 */
#if BIND_apr_strtok_FUNCTION
#define apr_strtok_REQUIRED_ARGC 3
#define apr_strtok_OPTIONAL_ARGC 0
/* char * apr_strtok(char * str, const char * sep, char ** last) */
mrb_value
mrb_APR_apr_strtok(mrb_state* mrb, mrb_value self) {
  mrb_value str;
  char * native_sep = NULL;
  mrb_value last;

  /* Fetch the args */
  mrb_get_args(mrb, "ozo", &str, &native_sep, &last);

  /* Type checking */
  TODO_type_check_char_PTR(str);
  TODO_type_check_char_PTR_PTR(last);

  /* Unbox param: str */
  char * native_str = TODO_mruby_unbox_char_PTR(str);

  /* Unbox param: last */
  char ** native_last = TODO_mruby_unbox_char_PTR_PTR(last);

  /* Invocation */
  char * native_return_value = apr_strtok(native_str, native_sep, native_last);

  /* Box the return value */
  mrb_value return_value = TODO_mruby_box_char_PTR(mrb, native_return_value);
  
  return return_value;
}
#endif
/* MRUBY_BINDING_END */

/* MRUBY_BINDING: apr_temp_dir_get */
/* sha: user_edited */
#if BIND_apr_temp_dir_get_FUNCTION
#define apr_temp_dir_get_REQUIRED_ARGC 1
#define apr_temp_dir_get_OPTIONAL_ARGC 0
/* apr_temp_dir_get
 *
 * Parameters:
 * - p: apr_pool_t *
 * Return Type: apr_status_t
 */
mrb_value
mrb_APR_apr_temp_dir_get(mrb_state* mrb, mrb_value self) {
  mrb_value p;

  /* Fetch the args */
  mrb_get_args(mrb, "o", &p);

  /* Type checking */
  if (!mrb_obj_is_kind_of(mrb, p, AprPoolT_class(mrb))) {
    mrb_raise(mrb, E_TYPE_ERROR, "AprPoolT expected");
    return mrb_nil_value();
  }

  /* Unbox parameters */
  apr_pool_t * native_p = (mrb_nil_p(p) ? NULL : mruby_unbox_apr_pool_t(p));

  /* Invocation */
  const char* native_temp_dir;
  apr_status_t result = apr_temp_dir_get(&native_temp_dir, native_p);

  /* Box the return value */
  if (result > MRB_INT_MAX) {
    mrb_raise(mrb, mrb->eStandardError_class, "MRuby cannot represent integers greater than MRB_INT_MAX");
    return mrb_nil_value();
  }
  mrb_value return_value = mrb_fixnum_value(result);

  mrb_value results = mrb_ary_new(mrb);
  mrb_ary_push(mrb, results, return_value);
  if (result == 0) {
     mrb_ary_push(mrb, results, mrb_str_new_cstr(mrb, native_temp_dir));
  }
  else {
     mrb_ary_push(mrb, results, mrb_nil_value());
  }

  return results;
}
#endif
/* MRUBY_BINDING_END */

/* MRUBY_BINDING: apr_terminate */
/* sha: user_edited */
#if BIND_apr_terminate_FUNCTION
#define apr_terminate_REQUIRED_ARGC 0
#define apr_terminate_OPTIONAL_ARGC 0
/* apr_terminate
 *
 * Parameters: None
 * Return Type: void
 */
mrb_value
mrb_APR_apr_terminate(mrb_state* mrb, mrb_value self) {
  /* Invocation */
  apr_terminate();

  return mrb_nil_value();
}
#endif
/* MRUBY_BINDING_END */

/* MRUBY_BINDING: apr_terminate2 */
/* sha: user_edited */
#if BIND_apr_terminate2_FUNCTION
#define apr_terminate2_REQUIRED_ARGC 0
#define apr_terminate2_OPTIONAL_ARGC 0
/* apr_terminate2
 *
 * Parameters: None
 * Return Type: void
 */
mrb_value
mrb_APR_apr_terminate2(mrb_state* mrb, mrb_value self) {
  /* Invocation */
  apr_terminate2();

  return mrb_nil_value();
}
#endif
/* MRUBY_BINDING_END */

/* MRUBY_BINDING: apr_thread_create */
/* sha: ee98f5ca472216c193602dffd7b59785fe50dc03483eb7e5c4ba080e6d2b8e05 */
#if BIND_apr_thread_create_FUNCTION
#define apr_thread_create_REQUIRED_ARGC 5
#define apr_thread_create_OPTIONAL_ARGC 0
/* apr_status_t apr_thread_create(apr_thread_t ** new_thread, apr_threadattr_t * attr, apr_thread_start_t func, void * data, apr_pool_t * cont) */
mrb_value
mrb_APR_apr_thread_create(mrb_state* mrb, mrb_value self) {
  mrb_value new_thread;
  mrb_value attr;
  mrb_value func;
  mrb_value data;
  mrb_value cont;

  /* Fetch the args */
  mrb_get_args(mrb, "ooooo", &new_thread, &attr, &func, &data, &cont);

  /* Type checking */
  TODO_type_check_apr_thread_t_PTR_PTR(new_thread);
  if (!mrb_obj_is_kind_of(mrb, attr, AprThreadattrT_class(mrb))) {
    mrb_raise(mrb, E_TYPE_ERROR, "AprThreadattrT expected");
    return mrb_nil_value();
  }
  TODO_type_check_apr_thread_start_t(func);
  TODO_type_check_void_PTR(data);
  if (!mrb_obj_is_kind_of(mrb, cont, AprPoolT_class(mrb))) {
    mrb_raise(mrb, E_TYPE_ERROR, "AprPoolT expected");
    return mrb_nil_value();
  }

  /* Unbox param: new_thread */
  apr_thread_t ** native_new_thread = TODO_mruby_unbox_apr_thread_t_PTR_PTR(new_thread);

  /* Unbox param: attr */
  apr_threadattr_t * native_attr = (mrb_nil_p(attr) ? NULL : mruby_unbox_apr_threadattr_t(attr));

  /* Unbox param: func */
  apr_thread_start_t native_func = TODO_mruby_unbox_apr_thread_start_t(func);

  /* Unbox param: data */
  void * native_data = TODO_mruby_unbox_void_PTR(data);

  /* Unbox param: cont */
  apr_pool_t * native_cont = (mrb_nil_p(cont) ? NULL : mruby_unbox_apr_pool_t(cont));

  /* Invocation */
  apr_status_t native_return_value = apr_thread_create(native_new_thread, native_attr, native_func, native_data, native_cont);

  /* Box the return value */
  mrb_value return_value = mrb_fixnum_value(native_return_value);
  
  return return_value;
}
#endif
/* MRUBY_BINDING_END */

/* MRUBY_BINDING: apr_thread_data_get */
/* sha: 00bbaeed593c86edd3e70fa6f1b3008325ae3ebabee597eba8262f19024d480a */
#if BIND_apr_thread_data_get_FUNCTION
#define apr_thread_data_get_REQUIRED_ARGC 3
#define apr_thread_data_get_OPTIONAL_ARGC 0
/* apr_status_t apr_thread_data_get(void ** data, const char * key, apr_thread_t * thread) */
mrb_value
mrb_APR_apr_thread_data_get(mrb_state* mrb, mrb_value self) {
  mrb_value data;
  char * native_key = NULL;
  mrb_value thread;

  /* Fetch the args */
  mrb_get_args(mrb, "ozo", &data, &native_key, &thread);

  /* Type checking */
  TODO_type_check_void_PTR_PTR(data);
  if (!mrb_obj_is_kind_of(mrb, thread, AprThreadT_class(mrb))) {
    mrb_raise(mrb, E_TYPE_ERROR, "AprThreadT expected");
    return mrb_nil_value();
  }

  /* Unbox param: data */
  void ** native_data = TODO_mruby_unbox_void_PTR_PTR(data);

  /* Unbox param: thread */
  apr_thread_t * native_thread = (mrb_nil_p(thread) ? NULL : mruby_unbox_apr_thread_t(thread));

  /* Invocation */
  apr_status_t native_return_value = apr_thread_data_get(native_data, native_key, native_thread);

  /* Box the return value */
  mrb_value return_value = mrb_fixnum_value(native_return_value);
  
  return return_value;
}
#endif
/* MRUBY_BINDING_END */

/* MRUBY_BINDING: apr_thread_data_set */
/* sha: 9eb76f1777de86cc57c5217de128980d0607b75866e4edf848c42551cea98be2 */
#if BIND_apr_thread_data_set_FUNCTION
#define apr_thread_data_set_REQUIRED_ARGC 4
#define apr_thread_data_set_OPTIONAL_ARGC 0
/* apr_status_t apr_thread_data_set(void * data, const char * key, apr_status_t (*)(void *) cleanup, apr_thread_t * thread) */
mrb_value
mrb_APR_apr_thread_data_set(mrb_state* mrb, mrb_value self) {
  mrb_value data;
  char * native_key = NULL;
  mrb_value cleanup;
  mrb_value thread;

  /* Fetch the args */
  mrb_get_args(mrb, "ozoo", &data, &native_key, &cleanup, &thread);

  /* Type checking */
  TODO_type_check_void_PTR(data);
  TODO_type_check_apr_status_t_LPAREN_PTR_RPAREN_LPAREN_void_PTR_RPAREN(cleanup);
  if (!mrb_obj_is_kind_of(mrb, thread, AprThreadT_class(mrb))) {
    mrb_raise(mrb, E_TYPE_ERROR, "AprThreadT expected");
    return mrb_nil_value();
  }

  /* Unbox param: data */
  void * native_data = TODO_mruby_unbox_void_PTR(data);

  /* Unbox param: cleanup */
  apr_status_t (*native_cleanup)(void *) = TODO_mruby_unbox_apr_status_t_LPAREN_PTR_RPAREN_LPAREN_void_PTR_RPAREN(cleanup);

  /* Unbox param: thread */
  apr_thread_t * native_thread = (mrb_nil_p(thread) ? NULL : mruby_unbox_apr_thread_t(thread));

  /* Invocation */
  apr_status_t native_return_value = apr_thread_data_set(native_data, native_key, native_cleanup, native_thread);

  /* Box the return value */
  mrb_value return_value = mrb_fixnum_value(native_return_value);
  
  return return_value;
}
#endif
/* MRUBY_BINDING_END */

/* MRUBY_BINDING: apr_thread_detach */
/* sha: b571fe52c66a0697adce7a10f3819d9dc9505d9f9dc58a64f9cd46a43a987126 */
#if BIND_apr_thread_detach_FUNCTION
#define apr_thread_detach_REQUIRED_ARGC 1
#define apr_thread_detach_OPTIONAL_ARGC 0
/* apr_status_t apr_thread_detach(apr_thread_t * thd) */
mrb_value
mrb_APR_apr_thread_detach(mrb_state* mrb, mrb_value self) {
  mrb_value thd;

  /* Fetch the args */
  mrb_get_args(mrb, "o", &thd);

  /* Type checking */
  if (!mrb_obj_is_kind_of(mrb, thd, AprThreadT_class(mrb))) {
    mrb_raise(mrb, E_TYPE_ERROR, "AprThreadT expected");
    return mrb_nil_value();
  }

  /* Unbox param: thd */
  apr_thread_t * native_thd = (mrb_nil_p(thd) ? NULL : mruby_unbox_apr_thread_t(thd));

  /* Invocation */
  apr_status_t native_return_value = apr_thread_detach(native_thd);

  /* Box the return value */
  mrb_value return_value = mrb_fixnum_value(native_return_value);
  
  return return_value;
}
#endif
/* MRUBY_BINDING_END */

/* MRUBY_BINDING: apr_thread_exit */
/* sha: 8fe6a1df1ba9e092a3999ecc648da43cad5eb83a4730a111b994c7e557ad0e9f */
#if BIND_apr_thread_exit_FUNCTION
#define apr_thread_exit_REQUIRED_ARGC 2
#define apr_thread_exit_OPTIONAL_ARGC 0
/* apr_status_t apr_thread_exit(apr_thread_t * thd, apr_status_t retval) */
mrb_value
mrb_APR_apr_thread_exit(mrb_state* mrb, mrb_value self) {
  mrb_value thd;
  mrb_int native_retval;

  /* Fetch the args */
  mrb_get_args(mrb, "oi", &thd, &native_retval);

  /* Type checking */
  if (!mrb_obj_is_kind_of(mrb, thd, AprThreadT_class(mrb))) {
    mrb_raise(mrb, E_TYPE_ERROR, "AprThreadT expected");
    return mrb_nil_value();
  }

  /* Unbox param: thd */
  apr_thread_t * native_thd = (mrb_nil_p(thd) ? NULL : mruby_unbox_apr_thread_t(thd));

  /* Invocation */
  apr_status_t native_return_value = apr_thread_exit(native_thd, native_retval);

  /* Box the return value */
  mrb_value return_value = mrb_fixnum_value(native_return_value);
  
  return return_value;
}
#endif
/* MRUBY_BINDING_END */

/* MRUBY_BINDING: apr_thread_join */
/* sha: 787e5cd1ea10a6fc7ec1ee13c0d5639fc3588c651803f8a885e727b87960992b */
#if BIND_apr_thread_join_FUNCTION
#define apr_thread_join_REQUIRED_ARGC 2
#define apr_thread_join_OPTIONAL_ARGC 0
/* apr_status_t apr_thread_join(apr_status_t * retval, apr_thread_t * thd) */
mrb_value
mrb_APR_apr_thread_join(mrb_state* mrb, mrb_value self) {
  mrb_value retval;
  mrb_value thd;

  /* Fetch the args */
  mrb_get_args(mrb, "oo", &retval, &thd);

  /* Type checking */
  TODO_type_check_apr_status_t_PTR(retval);
  if (!mrb_obj_is_kind_of(mrb, thd, AprThreadT_class(mrb))) {
    mrb_raise(mrb, E_TYPE_ERROR, "AprThreadT expected");
    return mrb_nil_value();
  }

  /* Unbox param: retval */
  apr_status_t * native_retval = TODO_mruby_unbox_apr_status_t_PTR(retval);

  /* Unbox param: thd */
  apr_thread_t * native_thd = (mrb_nil_p(thd) ? NULL : mruby_unbox_apr_thread_t(thd));

  /* Invocation */
  apr_status_t native_return_value = apr_thread_join(native_retval, native_thd);

  /* Box the return value */
  mrb_value return_value = mrb_fixnum_value(native_return_value);
  
  return return_value;
}
#endif
/* MRUBY_BINDING_END */

/* MRUBY_BINDING: apr_thread_once */
/* sha: 54c225da95326b3010b346cc86f1d2812399341944a873641cf45efd44798a42 */
#if BIND_apr_thread_once_FUNCTION
#define apr_thread_once_REQUIRED_ARGC 2
#define apr_thread_once_OPTIONAL_ARGC 0
/* apr_status_t apr_thread_once(apr_thread_once_t * control, void (*)(void) func) */
mrb_value
mrb_APR_apr_thread_once(mrb_state* mrb, mrb_value self) {
  mrb_value control;
  mrb_value func;

  /* Fetch the args */
  mrb_get_args(mrb, "oo", &control, &func);

  /* Type checking */
  if (!mrb_obj_is_kind_of(mrb, control, AprThreadOnceT_class(mrb))) {
    mrb_raise(mrb, E_TYPE_ERROR, "AprThreadOnceT expected");
    return mrb_nil_value();
  }
  TODO_type_check_void_LPAREN_PTR_RPAREN_LPAREN_void_RPAREN(func);

  /* Unbox param: control */
  apr_thread_once_t * native_control = (mrb_nil_p(control) ? NULL : mruby_unbox_apr_thread_once_t(control));

  /* Unbox param: func */
  void (*native_func)(void) = TODO_mruby_unbox_void_LPAREN_PTR_RPAREN_LPAREN_void_RPAREN(func);

  /* Invocation */
  apr_status_t native_return_value = apr_thread_once(native_control, native_func);

  /* Box the return value */
  mrb_value return_value = mrb_fixnum_value(native_return_value);
  
  return return_value;
}
#endif
/* MRUBY_BINDING_END */

/* MRUBY_BINDING: apr_thread_once_init */
/* sha: bd4ad38a0aa41b96095df346d6f2373bb5848a13316aaef9c9d7104bd8747e3f */
#if BIND_apr_thread_once_init_FUNCTION
#define apr_thread_once_init_REQUIRED_ARGC 2
#define apr_thread_once_init_OPTIONAL_ARGC 0
/* apr_status_t apr_thread_once_init(apr_thread_once_t ** control, apr_pool_t * p) */
mrb_value
mrb_APR_apr_thread_once_init(mrb_state* mrb, mrb_value self) {
  mrb_value control;
  mrb_value p;

  /* Fetch the args */
  mrb_get_args(mrb, "oo", &control, &p);

  /* Type checking */
  TODO_type_check_apr_thread_once_t_PTR_PTR(control);
  if (!mrb_obj_is_kind_of(mrb, p, AprPoolT_class(mrb))) {
    mrb_raise(mrb, E_TYPE_ERROR, "AprPoolT expected");
    return mrb_nil_value();
  }

  /* Unbox param: control */
  apr_thread_once_t ** native_control = TODO_mruby_unbox_apr_thread_once_t_PTR_PTR(control);

  /* Unbox param: p */
  apr_pool_t * native_p = (mrb_nil_p(p) ? NULL : mruby_unbox_apr_pool_t(p));

  /* Invocation */
  apr_status_t native_return_value = apr_thread_once_init(native_control, native_p);

  /* Box the return value */
  mrb_value return_value = mrb_fixnum_value(native_return_value);
  
  return return_value;
}
#endif
/* MRUBY_BINDING_END */

/* MRUBY_BINDING: apr_thread_yield */
/* sha: 10746a73ed001e88f94d661f52a416301a1bbceb19bfbdd1170354fd88cea289 */
#if BIND_apr_thread_yield_FUNCTION
#define apr_thread_yield_REQUIRED_ARGC 0
#define apr_thread_yield_OPTIONAL_ARGC 0
/* void apr_thread_yield() */
mrb_value
mrb_APR_apr_thread_yield(mrb_state* mrb, mrb_value self) {
  /* Invocation */
  apr_thread_yield();

  return mrb_nil_value();
}
#endif
/* MRUBY_BINDING_END */

/* MRUBY_BINDING: apr_threadattr_create */
/* sha: bca5becbef61b97df3e86cf9f0fda70a84964abd4473e55906da39d46a6360a4 */
#if BIND_apr_threadattr_create_FUNCTION
#define apr_threadattr_create_REQUIRED_ARGC 2
#define apr_threadattr_create_OPTIONAL_ARGC 0
/* apr_status_t apr_threadattr_create(apr_threadattr_t ** new_attr, apr_pool_t * cont) */
mrb_value
mrb_APR_apr_threadattr_create(mrb_state* mrb, mrb_value self) {
  mrb_value new_attr;
  mrb_value cont;

  /* Fetch the args */
  mrb_get_args(mrb, "oo", &new_attr, &cont);

  /* Type checking */
  TODO_type_check_apr_threadattr_t_PTR_PTR(new_attr);
  if (!mrb_obj_is_kind_of(mrb, cont, AprPoolT_class(mrb))) {
    mrb_raise(mrb, E_TYPE_ERROR, "AprPoolT expected");
    return mrb_nil_value();
  }

  /* Unbox param: new_attr */
  apr_threadattr_t ** native_new_attr = TODO_mruby_unbox_apr_threadattr_t_PTR_PTR(new_attr);

  /* Unbox param: cont */
  apr_pool_t * native_cont = (mrb_nil_p(cont) ? NULL : mruby_unbox_apr_pool_t(cont));

  /* Invocation */
  apr_status_t native_return_value = apr_threadattr_create(native_new_attr, native_cont);

  /* Box the return value */
  mrb_value return_value = mrb_fixnum_value(native_return_value);
  
  return return_value;
}
#endif
/* MRUBY_BINDING_END */

/* MRUBY_BINDING: apr_threadattr_detach_get */
/* sha: 42306d64aa7e664747c055e3170ce1d616d2803866e3f5e8b2bd896af6101842 */
#if BIND_apr_threadattr_detach_get_FUNCTION
#define apr_threadattr_detach_get_REQUIRED_ARGC 1
#define apr_threadattr_detach_get_OPTIONAL_ARGC 0
/* apr_status_t apr_threadattr_detach_get(apr_threadattr_t * attr) */
mrb_value
mrb_APR_apr_threadattr_detach_get(mrb_state* mrb, mrb_value self) {
  mrb_value attr;

  /* Fetch the args */
  mrb_get_args(mrb, "o", &attr);

  /* Type checking */
  if (!mrb_obj_is_kind_of(mrb, attr, AprThreadattrT_class(mrb))) {
    mrb_raise(mrb, E_TYPE_ERROR, "AprThreadattrT expected");
    return mrb_nil_value();
  }

  /* Unbox param: attr */
  apr_threadattr_t * native_attr = (mrb_nil_p(attr) ? NULL : mruby_unbox_apr_threadattr_t(attr));

  /* Invocation */
  apr_status_t native_return_value = apr_threadattr_detach_get(native_attr);

  /* Box the return value */
  mrb_value return_value = mrb_fixnum_value(native_return_value);
  
  return return_value;
}
#endif
/* MRUBY_BINDING_END */

/* MRUBY_BINDING: apr_threadattr_detach_set */
/* sha: d5efda4f482c7d2904e8e983b1409cd5470987b2dec334a3a302dbbfa9a272bc */
#if BIND_apr_threadattr_detach_set_FUNCTION
#define apr_threadattr_detach_set_REQUIRED_ARGC 2
#define apr_threadattr_detach_set_OPTIONAL_ARGC 0
/* apr_status_t apr_threadattr_detach_set(apr_threadattr_t * attr, apr_int32_t on) */
mrb_value
mrb_APR_apr_threadattr_detach_set(mrb_state* mrb, mrb_value self) {
  mrb_value attr;
  mrb_int native_on;

  /* Fetch the args */
  mrb_get_args(mrb, "oi", &attr, &native_on);

  /* Type checking */
  if (!mrb_obj_is_kind_of(mrb, attr, AprThreadattrT_class(mrb))) {
    mrb_raise(mrb, E_TYPE_ERROR, "AprThreadattrT expected");
    return mrb_nil_value();
  }

  /* Unbox param: attr */
  apr_threadattr_t * native_attr = (mrb_nil_p(attr) ? NULL : mruby_unbox_apr_threadattr_t(attr));

  /* Invocation */
  apr_status_t native_return_value = apr_threadattr_detach_set(native_attr, native_on);

  /* Box the return value */
  mrb_value return_value = mrb_fixnum_value(native_return_value);
  
  return return_value;
}
#endif
/* MRUBY_BINDING_END */

/* MRUBY_BINDING: apr_threadattr_guardsize_set */
/* sha: d828ae69f85219a922f25aeadb66be89cee9cd83c42c5fd96e501eaf5124a0d2 */
#if BIND_apr_threadattr_guardsize_set_FUNCTION
#define apr_threadattr_guardsize_set_REQUIRED_ARGC 2
#define apr_threadattr_guardsize_set_OPTIONAL_ARGC 0
/* apr_status_t apr_threadattr_guardsize_set(apr_threadattr_t * attr, apr_size_t guardsize) */
mrb_value
mrb_APR_apr_threadattr_guardsize_set(mrb_state* mrb, mrb_value self) {
  mrb_value attr;
  mrb_int native_guardsize;

  /* Fetch the args */
  mrb_get_args(mrb, "oi", &attr, &native_guardsize);

  /* Type checking */
  if (!mrb_obj_is_kind_of(mrb, attr, AprThreadattrT_class(mrb))) {
    mrb_raise(mrb, E_TYPE_ERROR, "AprThreadattrT expected");
    return mrb_nil_value();
  }

  /* Unbox param: attr */
  apr_threadattr_t * native_attr = (mrb_nil_p(attr) ? NULL : mruby_unbox_apr_threadattr_t(attr));

  /* Invocation */
  apr_status_t native_return_value = apr_threadattr_guardsize_set(native_attr, native_guardsize);

  /* Box the return value */
  mrb_value return_value = mrb_fixnum_value(native_return_value);
  
  return return_value;
}
#endif
/* MRUBY_BINDING_END */

/* MRUBY_BINDING: apr_threadattr_stacksize_set */
/* sha: 058deb326942313d3bf6bc6422225f4d97b310f45e3311890d482aab3190bbed */
#if BIND_apr_threadattr_stacksize_set_FUNCTION
#define apr_threadattr_stacksize_set_REQUIRED_ARGC 2
#define apr_threadattr_stacksize_set_OPTIONAL_ARGC 0
/* apr_status_t apr_threadattr_stacksize_set(apr_threadattr_t * attr, apr_size_t stacksize) */
mrb_value
mrb_APR_apr_threadattr_stacksize_set(mrb_state* mrb, mrb_value self) {
  mrb_value attr;
  mrb_int native_stacksize;

  /* Fetch the args */
  mrb_get_args(mrb, "oi", &attr, &native_stacksize);

  /* Type checking */
  if (!mrb_obj_is_kind_of(mrb, attr, AprThreadattrT_class(mrb))) {
    mrb_raise(mrb, E_TYPE_ERROR, "AprThreadattrT expected");
    return mrb_nil_value();
  }

  /* Unbox param: attr */
  apr_threadattr_t * native_attr = (mrb_nil_p(attr) ? NULL : mruby_unbox_apr_threadattr_t(attr));

  /* Invocation */
  apr_status_t native_return_value = apr_threadattr_stacksize_set(native_attr, native_stacksize);

  /* Box the return value */
  mrb_value return_value = mrb_fixnum_value(native_return_value);
  
  return return_value;
}
#endif
/* MRUBY_BINDING_END */

/* MRUBY_BINDING: apr_threadkey_data_get */
/* sha: f5f8e678ef755d28c1c93398d010e8549305e227350936cc5540e69c6a58204e */
#if BIND_apr_threadkey_data_get_FUNCTION
#define apr_threadkey_data_get_REQUIRED_ARGC 3
#define apr_threadkey_data_get_OPTIONAL_ARGC 0
/* apr_status_t apr_threadkey_data_get(void ** data, const char * key, apr_threadkey_t * threadkey) */
mrb_value
mrb_APR_apr_threadkey_data_get(mrb_state* mrb, mrb_value self) {
  mrb_value data;
  char * native_key = NULL;
  mrb_value threadkey;

  /* Fetch the args */
  mrb_get_args(mrb, "ozo", &data, &native_key, &threadkey);

  /* Type checking */
  TODO_type_check_void_PTR_PTR(data);
  if (!mrb_obj_is_kind_of(mrb, threadkey, AprThreadkeyT_class(mrb))) {
    mrb_raise(mrb, E_TYPE_ERROR, "AprThreadkeyT expected");
    return mrb_nil_value();
  }

  /* Unbox param: data */
  void ** native_data = TODO_mruby_unbox_void_PTR_PTR(data);

  /* Unbox param: threadkey */
  apr_threadkey_t * native_threadkey = (mrb_nil_p(threadkey) ? NULL : mruby_unbox_apr_threadkey_t(threadkey));

  /* Invocation */
  apr_status_t native_return_value = apr_threadkey_data_get(native_data, native_key, native_threadkey);

  /* Box the return value */
  mrb_value return_value = mrb_fixnum_value(native_return_value);
  
  return return_value;
}
#endif
/* MRUBY_BINDING_END */

/* MRUBY_BINDING: apr_threadkey_data_set */
/* sha: 5695d2d4dc0a45df16a918ce084e99bb4296f90b92dc8ece9e676fc57b80684f */
#if BIND_apr_threadkey_data_set_FUNCTION
#define apr_threadkey_data_set_REQUIRED_ARGC 4
#define apr_threadkey_data_set_OPTIONAL_ARGC 0
/* apr_status_t apr_threadkey_data_set(void * data, const char * key, apr_status_t (*)(void *) cleanup, apr_threadkey_t * threadkey) */
mrb_value
mrb_APR_apr_threadkey_data_set(mrb_state* mrb, mrb_value self) {
  mrb_value data;
  char * native_key = NULL;
  mrb_value cleanup;
  mrb_value threadkey;

  /* Fetch the args */
  mrb_get_args(mrb, "ozoo", &data, &native_key, &cleanup, &threadkey);

  /* Type checking */
  TODO_type_check_void_PTR(data);
  TODO_type_check_apr_status_t_LPAREN_PTR_RPAREN_LPAREN_void_PTR_RPAREN(cleanup);
  if (!mrb_obj_is_kind_of(mrb, threadkey, AprThreadkeyT_class(mrb))) {
    mrb_raise(mrb, E_TYPE_ERROR, "AprThreadkeyT expected");
    return mrb_nil_value();
  }

  /* Unbox param: data */
  void * native_data = TODO_mruby_unbox_void_PTR(data);

  /* Unbox param: cleanup */
  apr_status_t (*native_cleanup)(void *) = TODO_mruby_unbox_apr_status_t_LPAREN_PTR_RPAREN_LPAREN_void_PTR_RPAREN(cleanup);

  /* Unbox param: threadkey */
  apr_threadkey_t * native_threadkey = (mrb_nil_p(threadkey) ? NULL : mruby_unbox_apr_threadkey_t(threadkey));

  /* Invocation */
  apr_status_t native_return_value = apr_threadkey_data_set(native_data, native_key, native_cleanup, native_threadkey);

  /* Box the return value */
  mrb_value return_value = mrb_fixnum_value(native_return_value);
  
  return return_value;
}
#endif
/* MRUBY_BINDING_END */

/* MRUBY_BINDING: apr_threadkey_private_create */
/* sha: e20fb2176bcb5a7fecbba66943666481611a1a16dc447d4bd26138cc3187a55c */
#if BIND_apr_threadkey_private_create_FUNCTION
#define apr_threadkey_private_create_REQUIRED_ARGC 3
#define apr_threadkey_private_create_OPTIONAL_ARGC 0
/* apr_status_t apr_threadkey_private_create(apr_threadkey_t ** key, void (*)(void *) dest, apr_pool_t * cont) */
mrb_value
mrb_APR_apr_threadkey_private_create(mrb_state* mrb, mrb_value self) {
  mrb_value key;
  mrb_value dest;
  mrb_value cont;

  /* Fetch the args */
  mrb_get_args(mrb, "ooo", &key, &dest, &cont);

  /* Type checking */
  TODO_type_check_apr_threadkey_t_PTR_PTR(key);
  TODO_type_check_void_LPAREN_PTR_RPAREN_LPAREN_void_PTR_RPAREN(dest);
  if (!mrb_obj_is_kind_of(mrb, cont, AprPoolT_class(mrb))) {
    mrb_raise(mrb, E_TYPE_ERROR, "AprPoolT expected");
    return mrb_nil_value();
  }

  /* Unbox param: key */
  apr_threadkey_t ** native_key = TODO_mruby_unbox_apr_threadkey_t_PTR_PTR(key);

  /* Unbox param: dest */
  void (*native_dest)(void *) = TODO_mruby_unbox_void_LPAREN_PTR_RPAREN_LPAREN_void_PTR_RPAREN(dest);

  /* Unbox param: cont */
  apr_pool_t * native_cont = (mrb_nil_p(cont) ? NULL : mruby_unbox_apr_pool_t(cont));

  /* Invocation */
  apr_status_t native_return_value = apr_threadkey_private_create(native_key, native_dest, native_cont);

  /* Box the return value */
  mrb_value return_value = mrb_fixnum_value(native_return_value);
  
  return return_value;
}
#endif
/* MRUBY_BINDING_END */

/* MRUBY_BINDING: apr_threadkey_private_delete */
/* sha: 889143945e9820b5a686b7d06ffb959fad8bf665469c8bae1244f5a4ceb39bb0 */
#if BIND_apr_threadkey_private_delete_FUNCTION
#define apr_threadkey_private_delete_REQUIRED_ARGC 1
#define apr_threadkey_private_delete_OPTIONAL_ARGC 0
/* apr_status_t apr_threadkey_private_delete(apr_threadkey_t * key) */
mrb_value
mrb_APR_apr_threadkey_private_delete(mrb_state* mrb, mrb_value self) {
  mrb_value key;

  /* Fetch the args */
  mrb_get_args(mrb, "o", &key);

  /* Type checking */
  if (!mrb_obj_is_kind_of(mrb, key, AprThreadkeyT_class(mrb))) {
    mrb_raise(mrb, E_TYPE_ERROR, "AprThreadkeyT expected");
    return mrb_nil_value();
  }

  /* Unbox param: key */
  apr_threadkey_t * native_key = (mrb_nil_p(key) ? NULL : mruby_unbox_apr_threadkey_t(key));

  /* Invocation */
  apr_status_t native_return_value = apr_threadkey_private_delete(native_key);

  /* Box the return value */
  mrb_value return_value = mrb_fixnum_value(native_return_value);
  
  return return_value;
}
#endif
/* MRUBY_BINDING_END */

/* MRUBY_BINDING: apr_threadkey_private_get */
/* sha: 71f208b479459294e51501e6a1bc4f66e1715cca430d88a5722ef6467578e858 */
#if BIND_apr_threadkey_private_get_FUNCTION
#define apr_threadkey_private_get_REQUIRED_ARGC 2
#define apr_threadkey_private_get_OPTIONAL_ARGC 0
/* apr_status_t apr_threadkey_private_get(void ** new_mem, apr_threadkey_t * key) */
mrb_value
mrb_APR_apr_threadkey_private_get(mrb_state* mrb, mrb_value self) {
  mrb_value new_mem;
  mrb_value key;

  /* Fetch the args */
  mrb_get_args(mrb, "oo", &new_mem, &key);

  /* Type checking */
  TODO_type_check_void_PTR_PTR(new_mem);
  if (!mrb_obj_is_kind_of(mrb, key, AprThreadkeyT_class(mrb))) {
    mrb_raise(mrb, E_TYPE_ERROR, "AprThreadkeyT expected");
    return mrb_nil_value();
  }

  /* Unbox param: new_mem */
  void ** native_new_mem = TODO_mruby_unbox_void_PTR_PTR(new_mem);

  /* Unbox param: key */
  apr_threadkey_t * native_key = (mrb_nil_p(key) ? NULL : mruby_unbox_apr_threadkey_t(key));

  /* Invocation */
  apr_status_t native_return_value = apr_threadkey_private_get(native_new_mem, native_key);

  /* Box the return value */
  mrb_value return_value = mrb_fixnum_value(native_return_value);
  
  return return_value;
}
#endif
/* MRUBY_BINDING_END */

/* MRUBY_BINDING: apr_threadkey_private_set */
/* sha: bd9849ab0cc7fd1e3c8b0df7f0f962b59e1c3330493d48ca088af91fcc800bfd */
#if BIND_apr_threadkey_private_set_FUNCTION
#define apr_threadkey_private_set_REQUIRED_ARGC 2
#define apr_threadkey_private_set_OPTIONAL_ARGC 0
/* apr_status_t apr_threadkey_private_set(void * priv, apr_threadkey_t * key) */
mrb_value
mrb_APR_apr_threadkey_private_set(mrb_state* mrb, mrb_value self) {
  mrb_value priv;
  mrb_value key;

  /* Fetch the args */
  mrb_get_args(mrb, "oo", &priv, &key);

  /* Type checking */
  TODO_type_check_void_PTR(priv);
  if (!mrb_obj_is_kind_of(mrb, key, AprThreadkeyT_class(mrb))) {
    mrb_raise(mrb, E_TYPE_ERROR, "AprThreadkeyT expected");
    return mrb_nil_value();
  }

  /* Unbox param: priv */
  void * native_priv = TODO_mruby_unbox_void_PTR(priv);

  /* Unbox param: key */
  apr_threadkey_t * native_key = (mrb_nil_p(key) ? NULL : mruby_unbox_apr_threadkey_t(key));

  /* Invocation */
  apr_status_t native_return_value = apr_threadkey_private_set(native_priv, native_key);

  /* Box the return value */
  mrb_value return_value = mrb_fixnum_value(native_return_value);
  
  return return_value;
}
#endif
/* MRUBY_BINDING_END */

/* MRUBY_BINDING: apr_time_ansi_put */
/* sha: b48b37ea3d473b78e11ca632479f46809ccc151eb97995eaa2d4c45cace86eb9 */
#if BIND_apr_time_ansi_put_FUNCTION
#define apr_time_ansi_put_REQUIRED_ARGC 2
#define apr_time_ansi_put_OPTIONAL_ARGC 0
/* apr_status_t apr_time_ansi_put(apr_time_t * result, time_t input) */
mrb_value
mrb_APR_apr_time_ansi_put(mrb_state* mrb, mrb_value self) {
  mrb_value result;
  mrb_int native_input;

  /* Fetch the args */
  mrb_get_args(mrb, "oi", &result, &native_input);

  /* Type checking */
  TODO_type_check_apr_time_t_PTR(result);

  /* Unbox param: result */
  apr_time_t * native_result = TODO_mruby_unbox_apr_time_t_PTR(result);

  /* Invocation */
  apr_status_t native_return_value = apr_time_ansi_put(native_result, native_input);

  /* Box the return value */
  mrb_value return_value = mrb_fixnum_value(native_return_value);
  
  return return_value;
}
#endif
/* MRUBY_BINDING_END */

/* MRUBY_BINDING: apr_time_clock_hires */
/* sha: 9ab2898fe5433fef37b4de9b4d1463eee82a3cf450b9b63f504e4221c1c3ba5f */
#if BIND_apr_time_clock_hires_FUNCTION
#define apr_time_clock_hires_REQUIRED_ARGC 1
#define apr_time_clock_hires_OPTIONAL_ARGC 0
/* void apr_time_clock_hires(apr_pool_t * p) */
mrb_value
mrb_APR_apr_time_clock_hires(mrb_state* mrb, mrb_value self) {
  mrb_value p;

  /* Fetch the args */
  mrb_get_args(mrb, "o", &p);

  /* Type checking */
  if (!mrb_obj_is_kind_of(mrb, p, AprPoolT_class(mrb))) {
    mrb_raise(mrb, E_TYPE_ERROR, "AprPoolT expected");
    return mrb_nil_value();
  }

  /* Unbox param: p */
  apr_pool_t * native_p = (mrb_nil_p(p) ? NULL : mruby_unbox_apr_pool_t(p));

  /* Invocation */
  apr_time_clock_hires(native_p);

  return mrb_nil_value();
}
#endif
/* MRUBY_BINDING_END */

/* MRUBY_BINDING: apr_time_exp_get */
/* sha: 8feb6e89ee548d3b38ce203117945cb1f5776e5b42202a3aa20da8c3aac86c17 */
#if BIND_apr_time_exp_get_FUNCTION
#define apr_time_exp_get_REQUIRED_ARGC 2
#define apr_time_exp_get_OPTIONAL_ARGC 0
/* apr_status_t apr_time_exp_get(apr_time_t * result, apr_time_exp_t * input) */
mrb_value
mrb_APR_apr_time_exp_get(mrb_state* mrb, mrb_value self) {
  mrb_value result;
  mrb_value input;

  /* Fetch the args */
  mrb_get_args(mrb, "oo", &result, &input);

  /* Type checking */
  TODO_type_check_apr_time_t_PTR(result);
  if (!mrb_obj_is_kind_of(mrb, input, AprTimeExpT_class(mrb))) {
    mrb_raise(mrb, E_TYPE_ERROR, "AprTimeExpT expected");
    return mrb_nil_value();
  }

  /* Unbox param: result */
  apr_time_t * native_result = TODO_mruby_unbox_apr_time_t_PTR(result);

  /* Unbox param: input */
  apr_time_exp_t * native_input = (mrb_nil_p(input) ? NULL : mruby_unbox_apr_time_exp_t(input));

  /* Invocation */
  apr_status_t native_return_value = apr_time_exp_get(native_result, native_input);

  /* Box the return value */
  mrb_value return_value = mrb_fixnum_value(native_return_value);
  
  return return_value;
}
#endif
/* MRUBY_BINDING_END */

/* MRUBY_BINDING: apr_time_exp_gmt */
/* sha: 911c1e57ee11422c00508e712de17b65b8e892156e521dd071d43d55b73567ec */
#if BIND_apr_time_exp_gmt_FUNCTION
#define apr_time_exp_gmt_REQUIRED_ARGC 2
#define apr_time_exp_gmt_OPTIONAL_ARGC 0
/* apr_status_t apr_time_exp_gmt(apr_time_exp_t * result, apr_time_t input) */
mrb_value
mrb_APR_apr_time_exp_gmt(mrb_state* mrb, mrb_value self) {
  mrb_value result;
  mrb_int native_input;

  /* Fetch the args */
  mrb_get_args(mrb, "oi", &result, &native_input);

  /* Type checking */
  if (!mrb_obj_is_kind_of(mrb, result, AprTimeExpT_class(mrb))) {
    mrb_raise(mrb, E_TYPE_ERROR, "AprTimeExpT expected");
    return mrb_nil_value();
  }

  /* Unbox param: result */
  apr_time_exp_t * native_result = (mrb_nil_p(result) ? NULL : mruby_unbox_apr_time_exp_t(result));

  /* Invocation */
  apr_status_t native_return_value = apr_time_exp_gmt(native_result, native_input);

  /* Box the return value */
  mrb_value return_value = mrb_fixnum_value(native_return_value);
  
  return return_value;
}
#endif
/* MRUBY_BINDING_END */

/* MRUBY_BINDING: apr_time_exp_gmt_get */
/* sha: 0f4100b1612e89c4bc9d80046a69650248dddff0055fec66679fb93826d45715 */
#if BIND_apr_time_exp_gmt_get_FUNCTION
#define apr_time_exp_gmt_get_REQUIRED_ARGC 2
#define apr_time_exp_gmt_get_OPTIONAL_ARGC 0
/* apr_status_t apr_time_exp_gmt_get(apr_time_t * result, apr_time_exp_t * input) */
mrb_value
mrb_APR_apr_time_exp_gmt_get(mrb_state* mrb, mrb_value self) {
  mrb_value result;
  mrb_value input;

  /* Fetch the args */
  mrb_get_args(mrb, "oo", &result, &input);

  /* Type checking */
  TODO_type_check_apr_time_t_PTR(result);
  if (!mrb_obj_is_kind_of(mrb, input, AprTimeExpT_class(mrb))) {
    mrb_raise(mrb, E_TYPE_ERROR, "AprTimeExpT expected");
    return mrb_nil_value();
  }

  /* Unbox param: result */
  apr_time_t * native_result = TODO_mruby_unbox_apr_time_t_PTR(result);

  /* Unbox param: input */
  apr_time_exp_t * native_input = (mrb_nil_p(input) ? NULL : mruby_unbox_apr_time_exp_t(input));

  /* Invocation */
  apr_status_t native_return_value = apr_time_exp_gmt_get(native_result, native_input);

  /* Box the return value */
  mrb_value return_value = mrb_fixnum_value(native_return_value);
  
  return return_value;
}
#endif
/* MRUBY_BINDING_END */

/* MRUBY_BINDING: apr_time_exp_lt */
/* sha: fefd31d57439c8fe6317eb908c5eb637019920b8b29e26bc73fed2fb2f6c7dbc */
#if BIND_apr_time_exp_lt_FUNCTION
#define apr_time_exp_lt_REQUIRED_ARGC 2
#define apr_time_exp_lt_OPTIONAL_ARGC 0
/* apr_status_t apr_time_exp_lt(apr_time_exp_t * result, apr_time_t input) */
mrb_value
mrb_APR_apr_time_exp_lt(mrb_state* mrb, mrb_value self) {
  mrb_value result;
  mrb_int native_input;

  /* Fetch the args */
  mrb_get_args(mrb, "oi", &result, &native_input);

  /* Type checking */
  if (!mrb_obj_is_kind_of(mrb, result, AprTimeExpT_class(mrb))) {
    mrb_raise(mrb, E_TYPE_ERROR, "AprTimeExpT expected");
    return mrb_nil_value();
  }

  /* Unbox param: result */
  apr_time_exp_t * native_result = (mrb_nil_p(result) ? NULL : mruby_unbox_apr_time_exp_t(result));

  /* Invocation */
  apr_status_t native_return_value = apr_time_exp_lt(native_result, native_input);

  /* Box the return value */
  mrb_value return_value = mrb_fixnum_value(native_return_value);
  
  return return_value;
}
#endif
/* MRUBY_BINDING_END */

/* MRUBY_BINDING: apr_time_exp_tz */
/* sha: 08848a2836f1f0af248c456125644829e4e10f051a6e1de46b0925e3098e9ac8 */
#if BIND_apr_time_exp_tz_FUNCTION
#define apr_time_exp_tz_REQUIRED_ARGC 3
#define apr_time_exp_tz_OPTIONAL_ARGC 0
/* apr_status_t apr_time_exp_tz(apr_time_exp_t * result, apr_time_t input, apr_int32_t offs) */
mrb_value
mrb_APR_apr_time_exp_tz(mrb_state* mrb, mrb_value self) {
  mrb_value result;
  mrb_int native_input;
  mrb_int native_offs;

  /* Fetch the args */
  mrb_get_args(mrb, "oii", &result, &native_input, &native_offs);

  /* Type checking */
  if (!mrb_obj_is_kind_of(mrb, result, AprTimeExpT_class(mrb))) {
    mrb_raise(mrb, E_TYPE_ERROR, "AprTimeExpT expected");
    return mrb_nil_value();
  }

  /* Unbox param: result */
  apr_time_exp_t * native_result = (mrb_nil_p(result) ? NULL : mruby_unbox_apr_time_exp_t(result));

  /* Invocation */
  apr_status_t native_return_value = apr_time_exp_tz(native_result, native_input, native_offs);

  /* Box the return value */
  mrb_value return_value = mrb_fixnum_value(native_return_value);
  
  return return_value;
}
#endif
/* MRUBY_BINDING_END */

/* MRUBY_BINDING: apr_time_now */
/* sha: 8fcc2565f090474e686700395d33eb0d59689a0b986df231312e5544a2abf4ab */
#if BIND_apr_time_now_FUNCTION
#define apr_time_now_REQUIRED_ARGC 0
#define apr_time_now_OPTIONAL_ARGC 0
/* apr_time_t apr_time_now() */
mrb_value
mrb_APR_apr_time_now(mrb_state* mrb, mrb_value self) {
  /* Invocation */
  apr_time_t native_return_value = apr_time_now();

  /* Box the return value */
  mrb_value return_value = mrb_fixnum_value(native_return_value);
  
  return return_value;
}
#endif
/* MRUBY_BINDING_END */

/* MRUBY_BINDING: apr_time_sec */
/* sha: e35d1720f84afdc3f643766f863c619f308735a966c1d683bd176641e038fbfb */
#if BIND_apr_time_sec_FUNCTION
#define apr_time_sec_REQUIRED_ARGC 1
#define apr_time_sec_OPTIONAL_ARGC 0
/* int apr_time_sec(int time) */
mrb_value
mrb_APR_apr_time_sec(mrb_state* mrb, mrb_value self) {
  mrb_int native_time;

  /* Fetch the args */
  mrb_get_args(mrb, "i", &native_time);

  /* Invocation */
  int native_return_value = apr_time_sec(native_time);

  /* Box the return value */
  mrb_value return_value = mrb_fixnum_value(native_return_value);
  
  return return_value;
}
#endif
/* MRUBY_BINDING_END */

/* MRUBY_BINDING: apr_tokenize_to_argv */
/* sha: user_edited */
#if BIND_apr_tokenize_to_argv_FUNCTION
#define apr_tokenize_to_argv_REQUIRED_ARGC 2
#define apr_tokenize_to_argv_OPTIONAL_ARGC 0
/* apr_tokenize_to_argv
 *
 * Parameters:
 * - arg_str: String
 * - token_context: AprPoolType
 * Return Type: [Fixnum, Array[String]]
 */
mrb_value
mrb_APR_apr_tokenize_to_argv(mrb_state* mrb, mrb_value self) {
  char * native_arg_str;
  mrb_value token_context;

  /* Fetch the args */
  mrb_get_args(mrb, "zo", &native_arg_str, &token_context);

  /* Type checking */
  if (!mrb_obj_is_kind_of(mrb, token_context, AprPoolT_class(mrb))) {
    mrb_raise(mrb, E_TYPE_ERROR, "AprPoolT expected");
    return mrb_nil_value();
  }

  /* Unbox parameters */

  apr_pool_t * native_token_context = (mrb_nil_p(token_context) ? NULL : mruby_unbox_apr_pool_t(token_context));

  /* Invocation */
  char ** native_argv_out;
  apr_status_t result = apr_tokenize_to_argv(native_arg_str, &native_argv_out, native_token_context);

  /* Box the return value */
  if (result > MRB_INT_MAX) {
    mrb_raise(mrb, mrb->eStandardError_class, "MRuby cannot represent integers greater than MRB_INT_MAX");
    return mrb_nil_value();
  }
  mrb_value return_value = mrb_fixnum_value(result);

  mrb_value results = mrb_ary_new(mrb);
  mrb_ary_push(mrb, results, return_value);
  if (result == 0) {
     mrb_value argv = mrb_ary_new(mrb);
     char** current_string_ptr = native_argv_out;
     while (*current_string_ptr != NULL) {
        mrb_ary_push(mrb, argv, mrb_str_new_cstr(mrb, *current_string_ptr));
        current_string_ptr++;
     }
     mrb_ary_push(mrb, results, argv);
  }
  else {
     mrb_ary_push(mrb, results, mrb_nil_value());
  }

  return results;
}
#endif
/* MRUBY_BINDING_END */

/* MRUBY_BINDING: apr_vsnprintf */
/* sha: 9b000669c4becb0ae4e79904e2de5fcad6c42c27b3de80e7cc5c88c8bb28e53a */
#if BIND_apr_vsnprintf_FUNCTION
#define apr_vsnprintf_REQUIRED_ARGC 4
#define apr_vsnprintf_OPTIONAL_ARGC 0
/* int apr_vsnprintf(char * buf, apr_size_t len, const char * format, int ap) */
mrb_value
mrb_APR_apr_vsnprintf(mrb_state* mrb, mrb_value self) {
  mrb_value buf;
  mrb_int native_len;
  char * native_format = NULL;
  mrb_int native_ap;

  /* Fetch the args */
  mrb_get_args(mrb, "oizi", &buf, &native_len, &native_format, &native_ap);

  /* Type checking */
  TODO_type_check_char_PTR(buf);

  /* Unbox param: buf */
  char * native_buf = TODO_mruby_unbox_char_PTR(buf);

  /* Invocation */
  int native_return_value = apr_vsnprintf(native_buf, native_len, native_format, native_ap);

  /* Box the return value */
  mrb_value return_value = mrb_fixnum_value(native_return_value);
  
  return return_value;
}
#endif
/* MRUBY_BINDING_END */


void mrb_mruby_apr_gem_init(mrb_state* mrb) {
/* MRUBY_BINDING: pre_module_definition */
/* sha: user_defined */
  apr_initialize();
/* MRUBY_BINDING_END */
  
  struct RClass* APR_module = mrb_define_module(mrb, "APR");
  mruby_APR_define_macro_constants(mrb);
  mruby_APR_define_enum_constants(mrb);

/* MRUBY_BINDING: pre_class_initializations */
/* sha: user_defined */
  mruby_APR_init_native_ext(mrb);
/* MRUBY_BINDING_END */

/* MRUBY_BINDING: class_initializations */
/* sha: 880ce8dd3fa44e03e75e59218c69fc4ac1cbb0fe73e7c96c6d44c921c33ac1af */
#if BIND_AprDirT_TYPE
  mrb_APR_AprDirT_init(mrb);
#endif
#if BIND_AprFileT_TYPE
  mrb_APR_AprFileT_init(mrb);
#endif
#if BIND_AprFinfoT_TYPE
  mrb_APR_AprFinfoT_init(mrb);
#endif
#if BIND_AprGlobalMutexT_TYPE
  mrb_APR_AprGlobalMutexT_init(mrb);
#endif
#if BIND_AprHdtrT_TYPE
  mrb_APR_AprHdtrT_init(mrb);
#endif
#if BIND_AprIpsubnetT_TYPE
  mrb_APR_AprIpsubnetT_init(mrb);
#endif
#if BIND_AprOtherChildRecT_TYPE
  mrb_APR_AprOtherChildRecT_init(mrb);
#endif
#if BIND_AprPoolT_TYPE
  mrb_APR_AprPoolT_init(mrb);
#endif
#if BIND_AprProcattrT_TYPE
  mrb_APR_AprProcattrT_init(mrb);
#endif
#if BIND_AprProcMutexT_TYPE
  mrb_APR_AprProcMutexT_init(mrb);
#endif
#if BIND_AprProcT_TYPE
  mrb_APR_AprProcT_init(mrb);
#endif
#if BIND_AprSockaddrT_TYPE
  mrb_APR_AprSockaddrT_init(mrb);
#endif
#if BIND_AprSocketT_TYPE
  mrb_APR_AprSocketT_init(mrb);
#endif
#if BIND_AprThreadattrT_TYPE
  mrb_APR_AprThreadattrT_init(mrb);
#endif
#if BIND_AprThreadkeyT_TYPE
  mrb_APR_AprThreadkeyT_init(mrb);
#endif
#if BIND_AprThreadOnceT_TYPE
  mrb_APR_AprThreadOnceT_init(mrb);
#endif
#if BIND_AprThreadT_TYPE
  mrb_APR_AprThreadT_init(mrb);
#endif
#if BIND_AprTimeExpT_TYPE
  mrb_APR_AprTimeExpT_init(mrb);
#endif
/* MRUBY_BINDING_END */

/* MRUBY_BINDING: pre_global_function_initializations */
/* sha: user_defined */
  mrb_define_class_method(mrb, APR_module, "apr_dir_chdir", mrb_APR_dir_chdir, MRB_ARGS_ARG(chdir_REQUIRED_ARGC, chdir_OPTIONAL_ARGC));
  mrb_define_class_method(mrb, APR_module, "apr_dir_getcwd", mrb_APR_dir_getcwd, MRB_ARGS_ARG(getcwd_REQUIRED_ARGC, getcwd_OPTIONAL_ARGC));
  mrb_define_class_method(mrb, APR_module, "apr_proc_from_pid", mrb_APR_apr_proc_from_pid, MRB_ARGS_ARG(1, 0));
  mrb_define_class_method(mrb, APR_module, "apr_pool_create", mrb_APR_apr_pool_create, MRB_ARGS_ARG(apr_pool_create_REQUIRED_ARGC, apr_pool_create_OPTIONAL_ARGC));
  mrb_define_class_method(mrb, APR_module, "apr_to_os_error", mrb_APR_apr_to_os_error, MRB_ARGS_ARG(apr_to_os_error_REQUIRED_ARGC, apr_to_os_error_OPTIONAL_ARGC));
  mrb_define_class_method(mrb, APR_module, "apr_file_inherit_unset", mrb_APR_apr_file_inherit_unset, MRB_ARGS_ARG(apr_file_inherit_unset_REQUIRED_ARGC, apr_file_inherit_unset_OPTIONAL_ARGC));
  
  /* Error Status Checks */

  #define BIND_STATUS_CHECK(err) mrb_define_class_method(mrb, APR_module, "APR_STATUS_IS_" #err , mrb_APR_APR_STATUS_IS_ ## err, MRB_ARGS_ARG(1, 0));

    BIND_STATUS_CHECK(EACCES);
    BIND_STATUS_CHECK(ENOSTAT);
    BIND_STATUS_CHECK(ENOPOOL);
    BIND_STATUS_CHECK(EBADDATE);
    BIND_STATUS_CHECK(EINVALSOCK);
    BIND_STATUS_CHECK(ENOPROC);
    BIND_STATUS_CHECK(ENOTIME);
    BIND_STATUS_CHECK(ENODIR);
    BIND_STATUS_CHECK(ENOLOCK);
    BIND_STATUS_CHECK(ENOPOLL);
    BIND_STATUS_CHECK(ENOSOCKET);
    BIND_STATUS_CHECK(ENOTHREAD);
    BIND_STATUS_CHECK(ENOTHDKEY);
    BIND_STATUS_CHECK(EGENERAL);
    BIND_STATUS_CHECK(ENOSHMAVAIL);
    BIND_STATUS_CHECK(EBADIP);
    BIND_STATUS_CHECK(EBADMASK);
    BIND_STATUS_CHECK(EDSOOPEN);
    BIND_STATUS_CHECK(EABSOLUTE);
    BIND_STATUS_CHECK(ERELATIVE);
    BIND_STATUS_CHECK(EINCOMPLETE);
    BIND_STATUS_CHECK(EABOVEROOT);
    BIND_STATUS_CHECK(EBADPATH);
    BIND_STATUS_CHECK(EPATHWILD);
    BIND_STATUS_CHECK(ESYMNOTFOUND);
    BIND_STATUS_CHECK(EPROC_UNKNOWN);
    BIND_STATUS_CHECK(ENOTENOUGHENTROPY);
    BIND_STATUS_CHECK(INCHILD);
    BIND_STATUS_CHECK(INPARENT);
    BIND_STATUS_CHECK(DETACH);
    BIND_STATUS_CHECK(NOTDETACH);
    BIND_STATUS_CHECK(CHILD_DONE);
    BIND_STATUS_CHECK(CHILD_NOTDONE);
    BIND_STATUS_CHECK(TIMEUP);
    BIND_STATUS_CHECK(INCOMPLETE);
    BIND_STATUS_CHECK(BADCH);
    BIND_STATUS_CHECK(BADARG);
    BIND_STATUS_CHECK(EOF);
    BIND_STATUS_CHECK(NOTFOUND);
    BIND_STATUS_CHECK(ANONYMOUS);
    BIND_STATUS_CHECK(FILEBASED);
    BIND_STATUS_CHECK(KEYBASED);
    BIND_STATUS_CHECK(EINIT);
    BIND_STATUS_CHECK(ENOTIMPL);
    BIND_STATUS_CHECK(EMISMATCH);
    BIND_STATUS_CHECK(EBUSY);
    BIND_STATUS_CHECK(EEXIST);
    BIND_STATUS_CHECK(ENAMETOOLONG);
    BIND_STATUS_CHECK(ENOENT);
    BIND_STATUS_CHECK(ENOTDIR);
    BIND_STATUS_CHECK(ENOSPC);
    BIND_STATUS_CHECK(ENOMEM);
    BIND_STATUS_CHECK(EMFILE);
    BIND_STATUS_CHECK(ENFILE);
    BIND_STATUS_CHECK(EBADF);
    BIND_STATUS_CHECK(EINVAL);
    BIND_STATUS_CHECK(ESPIPE);
    BIND_STATUS_CHECK(EAGAIN);
    BIND_STATUS_CHECK(EINTR);
    BIND_STATUS_CHECK(ENOTSOCK);
    BIND_STATUS_CHECK(ECONNREFUSED);
    BIND_STATUS_CHECK(EINPROGRESS);
    BIND_STATUS_CHECK(ECONNABORTED);
    BIND_STATUS_CHECK(ECONNRESET);
    BIND_STATUS_CHECK(ETIMEDOUT);
    BIND_STATUS_CHECK(EHOSTUNREACH);
    BIND_STATUS_CHECK(ENETUNREACH);
    BIND_STATUS_CHECK(EFTYPE);
    BIND_STATUS_CHECK(EPIPE);
    BIND_STATUS_CHECK(EXDEV);
    BIND_STATUS_CHECK(ENOTEMPTY);
    BIND_STATUS_CHECK(EAFNOSUPPORT);
/* MRUBY_BINDING_END */

/* MRUBY_BINDING: global_function_definitions */
/* sha: 90de25300936d01c8de58dddbd7db4dde951bd316f7dbf74e40cd032a4c7d403 */
  /*
   * Global Functions
   */
#if BIND_apr_app_initialize_FUNCTION
  mrb_define_class_method(mrb, APR_module, "apr_app_initialize", mrb_APR_apr_app_initialize, MRB_ARGS_ARG(apr_app_initialize_REQUIRED_ARGC, apr_app_initialize_OPTIONAL_ARGC));
#endif
#if BIND_apr_atoi64_FUNCTION
  mrb_define_class_method(mrb, APR_module, "apr_atoi64", mrb_APR_apr_atoi64, MRB_ARGS_ARG(apr_atoi64_REQUIRED_ARGC, apr_atoi64_OPTIONAL_ARGC));
#endif
#if BIND_apr_collapse_spaces_FUNCTION
  mrb_define_class_method(mrb, APR_module, "apr_collapse_spaces", mrb_APR_apr_collapse_spaces, MRB_ARGS_ARG(apr_collapse_spaces_REQUIRED_ARGC, apr_collapse_spaces_OPTIONAL_ARGC));
#endif
#if BIND_apr_cpystrn_FUNCTION
  mrb_define_class_method(mrb, APR_module, "apr_cpystrn", mrb_APR_apr_cpystrn, MRB_ARGS_ARG(apr_cpystrn_REQUIRED_ARGC, apr_cpystrn_OPTIONAL_ARGC));
#endif
#if BIND_apr_ctime_FUNCTION
  mrb_define_class_method(mrb, APR_module, "apr_ctime", mrb_APR_apr_ctime, MRB_ARGS_ARG(apr_ctime_REQUIRED_ARGC, apr_ctime_OPTIONAL_ARGC));
#endif
#if BIND_apr_dir_close_FUNCTION
  mrb_define_class_method(mrb, APR_module, "apr_dir_close", mrb_APR_apr_dir_close, MRB_ARGS_ARG(apr_dir_close_REQUIRED_ARGC, apr_dir_close_OPTIONAL_ARGC));
#endif
#if BIND_apr_dir_make_FUNCTION
  mrb_define_class_method(mrb, APR_module, "apr_dir_make", mrb_APR_apr_dir_make, MRB_ARGS_ARG(apr_dir_make_REQUIRED_ARGC, apr_dir_make_OPTIONAL_ARGC));
#endif
#if BIND_apr_dir_make_recursive_FUNCTION
  mrb_define_class_method(mrb, APR_module, "apr_dir_make_recursive", mrb_APR_apr_dir_make_recursive, MRB_ARGS_ARG(apr_dir_make_recursive_REQUIRED_ARGC, apr_dir_make_recursive_OPTIONAL_ARGC));
#endif
#if BIND_apr_dir_open_FUNCTION
  mrb_define_class_method(mrb, APR_module, "apr_dir_open", mrb_APR_apr_dir_open, MRB_ARGS_ARG(apr_dir_open_REQUIRED_ARGC, apr_dir_open_OPTIONAL_ARGC));
#endif
#if BIND_apr_dir_read_FUNCTION
  mrb_define_class_method(mrb, APR_module, "apr_dir_read", mrb_APR_apr_dir_read, MRB_ARGS_ARG(apr_dir_read_REQUIRED_ARGC, apr_dir_read_OPTIONAL_ARGC));
#endif
#if BIND_apr_dir_remove_FUNCTION
  mrb_define_class_method(mrb, APR_module, "apr_dir_remove", mrb_APR_apr_dir_remove, MRB_ARGS_ARG(apr_dir_remove_REQUIRED_ARGC, apr_dir_remove_OPTIONAL_ARGC));
#endif
#if BIND_apr_dir_rewind_FUNCTION
  mrb_define_class_method(mrb, APR_module, "apr_dir_rewind", mrb_APR_apr_dir_rewind, MRB_ARGS_ARG(apr_dir_rewind_REQUIRED_ARGC, apr_dir_rewind_OPTIONAL_ARGC));
#endif
#if BIND_apr_env_delete_FUNCTION
  mrb_define_class_method(mrb, APR_module, "apr_env_delete", mrb_APR_apr_env_delete, MRB_ARGS_ARG(apr_env_delete_REQUIRED_ARGC, apr_env_delete_OPTIONAL_ARGC));
#endif
#if BIND_apr_env_get_FUNCTION
  mrb_define_class_method(mrb, APR_module, "apr_env_get", mrb_APR_apr_env_get, MRB_ARGS_ARG(apr_env_get_REQUIRED_ARGC, apr_env_get_OPTIONAL_ARGC));
#endif
#if BIND_apr_env_set_FUNCTION
  mrb_define_class_method(mrb, APR_module, "apr_env_set", mrb_APR_apr_env_set, MRB_ARGS_ARG(apr_env_set_REQUIRED_ARGC, apr_env_set_OPTIONAL_ARGC));
#endif
#if BIND_apr_file_append_FUNCTION
  mrb_define_class_method(mrb, APR_module, "apr_file_append", mrb_APR_apr_file_append, MRB_ARGS_ARG(apr_file_append_REQUIRED_ARGC, apr_file_append_OPTIONAL_ARGC));
#endif
#if BIND_apr_file_attrs_set_FUNCTION
  mrb_define_class_method(mrb, APR_module, "apr_file_attrs_set", mrb_APR_apr_file_attrs_set, MRB_ARGS_ARG(apr_file_attrs_set_REQUIRED_ARGC, apr_file_attrs_set_OPTIONAL_ARGC));
#endif
#if BIND_apr_file_buffer_set_FUNCTION
  mrb_define_class_method(mrb, APR_module, "apr_file_buffer_set", mrb_APR_apr_file_buffer_set, MRB_ARGS_ARG(apr_file_buffer_set_REQUIRED_ARGC, apr_file_buffer_set_OPTIONAL_ARGC));
#endif
#if BIND_apr_file_buffer_size_get_FUNCTION
  mrb_define_class_method(mrb, APR_module, "apr_file_buffer_size_get", mrb_APR_apr_file_buffer_size_get, MRB_ARGS_ARG(apr_file_buffer_size_get_REQUIRED_ARGC, apr_file_buffer_size_get_OPTIONAL_ARGC));
#endif
#if BIND_apr_file_close_FUNCTION
  mrb_define_class_method(mrb, APR_module, "apr_file_close", mrb_APR_apr_file_close, MRB_ARGS_ARG(apr_file_close_REQUIRED_ARGC, apr_file_close_OPTIONAL_ARGC));
#endif
#if BIND_apr_file_copy_FUNCTION
  mrb_define_class_method(mrb, APR_module, "apr_file_copy", mrb_APR_apr_file_copy, MRB_ARGS_ARG(apr_file_copy_REQUIRED_ARGC, apr_file_copy_OPTIONAL_ARGC));
#endif
#if BIND_apr_file_data_get_FUNCTION
  mrb_define_class_method(mrb, APR_module, "apr_file_data_get", mrb_APR_apr_file_data_get, MRB_ARGS_ARG(apr_file_data_get_REQUIRED_ARGC, apr_file_data_get_OPTIONAL_ARGC));
#endif
#if BIND_apr_file_data_set_FUNCTION
  mrb_define_class_method(mrb, APR_module, "apr_file_data_set", mrb_APR_apr_file_data_set, MRB_ARGS_ARG(apr_file_data_set_REQUIRED_ARGC, apr_file_data_set_OPTIONAL_ARGC));
#endif
#if BIND_apr_file_datasync_FUNCTION
  mrb_define_class_method(mrb, APR_module, "apr_file_datasync", mrb_APR_apr_file_datasync, MRB_ARGS_ARG(apr_file_datasync_REQUIRED_ARGC, apr_file_datasync_OPTIONAL_ARGC));
#endif
#if BIND_apr_file_dup_FUNCTION
  mrb_define_class_method(mrb, APR_module, "apr_file_dup", mrb_APR_apr_file_dup, MRB_ARGS_ARG(apr_file_dup_REQUIRED_ARGC, apr_file_dup_OPTIONAL_ARGC));
#endif
#if BIND_apr_file_dup2_FUNCTION
  mrb_define_class_method(mrb, APR_module, "apr_file_dup2", mrb_APR_apr_file_dup2, MRB_ARGS_ARG(apr_file_dup2_REQUIRED_ARGC, apr_file_dup2_OPTIONAL_ARGC));
#endif
#if BIND_apr_file_eof_FUNCTION
  mrb_define_class_method(mrb, APR_module, "apr_file_eof", mrb_APR_apr_file_eof, MRB_ARGS_ARG(apr_file_eof_REQUIRED_ARGC, apr_file_eof_OPTIONAL_ARGC));
#endif
#if BIND_apr_file_flags_get_FUNCTION
  mrb_define_class_method(mrb, APR_module, "apr_file_flags_get", mrb_APR_apr_file_flags_get, MRB_ARGS_ARG(apr_file_flags_get_REQUIRED_ARGC, apr_file_flags_get_OPTIONAL_ARGC));
#endif
#if BIND_apr_file_flush_FUNCTION
  mrb_define_class_method(mrb, APR_module, "apr_file_flush", mrb_APR_apr_file_flush, MRB_ARGS_ARG(apr_file_flush_REQUIRED_ARGC, apr_file_flush_OPTIONAL_ARGC));
#endif
#if BIND_apr_file_getc_FUNCTION
  mrb_define_class_method(mrb, APR_module, "apr_file_getc", mrb_APR_apr_file_getc, MRB_ARGS_ARG(apr_file_getc_REQUIRED_ARGC, apr_file_getc_OPTIONAL_ARGC));
#endif
#if BIND_apr_file_gets_FUNCTION
  mrb_define_class_method(mrb, APR_module, "apr_file_gets", mrb_APR_apr_file_gets, MRB_ARGS_ARG(apr_file_gets_REQUIRED_ARGC, apr_file_gets_OPTIONAL_ARGC));
#endif
#if BIND_apr_file_info_get_FUNCTION
  mrb_define_class_method(mrb, APR_module, "apr_file_info_get", mrb_APR_apr_file_info_get, MRB_ARGS_ARG(apr_file_info_get_REQUIRED_ARGC, apr_file_info_get_OPTIONAL_ARGC));
#endif
#if BIND_apr_file_link_FUNCTION
  mrb_define_class_method(mrb, APR_module, "apr_file_link", mrb_APR_apr_file_link, MRB_ARGS_ARG(apr_file_link_REQUIRED_ARGC, apr_file_link_OPTIONAL_ARGC));
#endif
#if BIND_apr_file_lock_FUNCTION
  mrb_define_class_method(mrb, APR_module, "apr_file_lock", mrb_APR_apr_file_lock, MRB_ARGS_ARG(apr_file_lock_REQUIRED_ARGC, apr_file_lock_OPTIONAL_ARGC));
#endif
#if BIND_apr_file_mktemp_FUNCTION
  mrb_define_class_method(mrb, APR_module, "apr_file_mktemp", mrb_APR_apr_file_mktemp, MRB_ARGS_ARG(apr_file_mktemp_REQUIRED_ARGC, apr_file_mktemp_OPTIONAL_ARGC));
#endif
#if BIND_apr_file_mtime_set_FUNCTION
  mrb_define_class_method(mrb, APR_module, "apr_file_mtime_set", mrb_APR_apr_file_mtime_set, MRB_ARGS_ARG(apr_file_mtime_set_REQUIRED_ARGC, apr_file_mtime_set_OPTIONAL_ARGC));
#endif
#if BIND_apr_file_name_get_FUNCTION
  mrb_define_class_method(mrb, APR_module, "apr_file_name_get", mrb_APR_apr_file_name_get, MRB_ARGS_ARG(apr_file_name_get_REQUIRED_ARGC, apr_file_name_get_OPTIONAL_ARGC));
#endif
#if BIND_apr_file_namedpipe_create_FUNCTION
  mrb_define_class_method(mrb, APR_module, "apr_file_namedpipe_create", mrb_APR_apr_file_namedpipe_create, MRB_ARGS_ARG(apr_file_namedpipe_create_REQUIRED_ARGC, apr_file_namedpipe_create_OPTIONAL_ARGC));
#endif
#if BIND_apr_file_open_FUNCTION
  mrb_define_class_method(mrb, APR_module, "apr_file_open", mrb_APR_apr_file_open, MRB_ARGS_ARG(apr_file_open_REQUIRED_ARGC, apr_file_open_OPTIONAL_ARGC));
#endif
#if BIND_apr_file_open_flags_stderr_FUNCTION
  mrb_define_class_method(mrb, APR_module, "apr_file_open_flags_stderr", mrb_APR_apr_file_open_flags_stderr, MRB_ARGS_ARG(apr_file_open_flags_stderr_REQUIRED_ARGC, apr_file_open_flags_stderr_OPTIONAL_ARGC));
#endif
#if BIND_apr_file_open_flags_stdin_FUNCTION
  mrb_define_class_method(mrb, APR_module, "apr_file_open_flags_stdin", mrb_APR_apr_file_open_flags_stdin, MRB_ARGS_ARG(apr_file_open_flags_stdin_REQUIRED_ARGC, apr_file_open_flags_stdin_OPTIONAL_ARGC));
#endif
#if BIND_apr_file_open_flags_stdout_FUNCTION
  mrb_define_class_method(mrb, APR_module, "apr_file_open_flags_stdout", mrb_APR_apr_file_open_flags_stdout, MRB_ARGS_ARG(apr_file_open_flags_stdout_REQUIRED_ARGC, apr_file_open_flags_stdout_OPTIONAL_ARGC));
#endif
#if BIND_apr_file_open_stderr_FUNCTION
  mrb_define_class_method(mrb, APR_module, "apr_file_open_stderr", mrb_APR_apr_file_open_stderr, MRB_ARGS_ARG(apr_file_open_stderr_REQUIRED_ARGC, apr_file_open_stderr_OPTIONAL_ARGC));
#endif
#if BIND_apr_file_open_stdin_FUNCTION
  mrb_define_class_method(mrb, APR_module, "apr_file_open_stdin", mrb_APR_apr_file_open_stdin, MRB_ARGS_ARG(apr_file_open_stdin_REQUIRED_ARGC, apr_file_open_stdin_OPTIONAL_ARGC));
#endif
#if BIND_apr_file_open_stdout_FUNCTION
  mrb_define_class_method(mrb, APR_module, "apr_file_open_stdout", mrb_APR_apr_file_open_stdout, MRB_ARGS_ARG(apr_file_open_stdout_REQUIRED_ARGC, apr_file_open_stdout_OPTIONAL_ARGC));
#endif
#if BIND_apr_file_perms_set_FUNCTION
  mrb_define_class_method(mrb, APR_module, "apr_file_perms_set", mrb_APR_apr_file_perms_set, MRB_ARGS_ARG(apr_file_perms_set_REQUIRED_ARGC, apr_file_perms_set_OPTIONAL_ARGC));
#endif
#if BIND_apr_file_pipe_create_FUNCTION
  mrb_define_class_method(mrb, APR_module, "apr_file_pipe_create", mrb_APR_apr_file_pipe_create, MRB_ARGS_ARG(apr_file_pipe_create_REQUIRED_ARGC, apr_file_pipe_create_OPTIONAL_ARGC));
#endif
#if BIND_apr_file_pipe_create_ex_FUNCTION
  mrb_define_class_method(mrb, APR_module, "apr_file_pipe_create_ex", mrb_APR_apr_file_pipe_create_ex, MRB_ARGS_ARG(apr_file_pipe_create_ex_REQUIRED_ARGC, apr_file_pipe_create_ex_OPTIONAL_ARGC));
#endif
#if BIND_apr_file_pipe_timeout_get_FUNCTION
  mrb_define_class_method(mrb, APR_module, "apr_file_pipe_timeout_get", mrb_APR_apr_file_pipe_timeout_get, MRB_ARGS_ARG(apr_file_pipe_timeout_get_REQUIRED_ARGC, apr_file_pipe_timeout_get_OPTIONAL_ARGC));
#endif
#if BIND_apr_file_pipe_timeout_set_FUNCTION
  mrb_define_class_method(mrb, APR_module, "apr_file_pipe_timeout_set", mrb_APR_apr_file_pipe_timeout_set, MRB_ARGS_ARG(apr_file_pipe_timeout_set_REQUIRED_ARGC, apr_file_pipe_timeout_set_OPTIONAL_ARGC));
#endif
#if BIND_apr_file_printf_FUNCTION
  mrb_define_class_method(mrb, APR_module, "apr_file_printf", mrb_APR_apr_file_printf, MRB_ARGS_ARG(apr_file_printf_REQUIRED_ARGC, apr_file_printf_OPTIONAL_ARGC));
#endif
#if BIND_apr_file_putc_FUNCTION
  mrb_define_class_method(mrb, APR_module, "apr_file_putc", mrb_APR_apr_file_putc, MRB_ARGS_ARG(apr_file_putc_REQUIRED_ARGC, apr_file_putc_OPTIONAL_ARGC));
#endif
#if BIND_apr_file_puts_FUNCTION
  mrb_define_class_method(mrb, APR_module, "apr_file_puts", mrb_APR_apr_file_puts, MRB_ARGS_ARG(apr_file_puts_REQUIRED_ARGC, apr_file_puts_OPTIONAL_ARGC));
#endif
#if BIND_apr_file_read_FUNCTION
  mrb_define_class_method(mrb, APR_module, "apr_file_read", mrb_APR_apr_file_read, MRB_ARGS_ARG(apr_file_read_REQUIRED_ARGC, apr_file_read_OPTIONAL_ARGC));
#endif
#if BIND_apr_file_read_full_FUNCTION
  mrb_define_class_method(mrb, APR_module, "apr_file_read_full", mrb_APR_apr_file_read_full, MRB_ARGS_ARG(apr_file_read_full_REQUIRED_ARGC, apr_file_read_full_OPTIONAL_ARGC));
#endif
#if BIND_apr_file_remove_FUNCTION
  mrb_define_class_method(mrb, APR_module, "apr_file_remove", mrb_APR_apr_file_remove, MRB_ARGS_ARG(apr_file_remove_REQUIRED_ARGC, apr_file_remove_OPTIONAL_ARGC));
#endif
#if BIND_apr_file_rename_FUNCTION
  mrb_define_class_method(mrb, APR_module, "apr_file_rename", mrb_APR_apr_file_rename, MRB_ARGS_ARG(apr_file_rename_REQUIRED_ARGC, apr_file_rename_OPTIONAL_ARGC));
#endif
#if BIND_apr_file_seek_FUNCTION
  mrb_define_class_method(mrb, APR_module, "apr_file_seek", mrb_APR_apr_file_seek, MRB_ARGS_ARG(apr_file_seek_REQUIRED_ARGC, apr_file_seek_OPTIONAL_ARGC));
#endif
#if BIND_apr_file_setaside_FUNCTION
  mrb_define_class_method(mrb, APR_module, "apr_file_setaside", mrb_APR_apr_file_setaside, MRB_ARGS_ARG(apr_file_setaside_REQUIRED_ARGC, apr_file_setaside_OPTIONAL_ARGC));
#endif
#if BIND_apr_file_sync_FUNCTION
  mrb_define_class_method(mrb, APR_module, "apr_file_sync", mrb_APR_apr_file_sync, MRB_ARGS_ARG(apr_file_sync_REQUIRED_ARGC, apr_file_sync_OPTIONAL_ARGC));
#endif
#if BIND_apr_file_trunc_FUNCTION
  mrb_define_class_method(mrb, APR_module, "apr_file_trunc", mrb_APR_apr_file_trunc, MRB_ARGS_ARG(apr_file_trunc_REQUIRED_ARGC, apr_file_trunc_OPTIONAL_ARGC));
#endif
#if BIND_apr_file_ungetc_FUNCTION
  mrb_define_class_method(mrb, APR_module, "apr_file_ungetc", mrb_APR_apr_file_ungetc, MRB_ARGS_ARG(apr_file_ungetc_REQUIRED_ARGC, apr_file_ungetc_OPTIONAL_ARGC));
#endif
#if BIND_apr_file_unlock_FUNCTION
  mrb_define_class_method(mrb, APR_module, "apr_file_unlock", mrb_APR_apr_file_unlock, MRB_ARGS_ARG(apr_file_unlock_REQUIRED_ARGC, apr_file_unlock_OPTIONAL_ARGC));
#endif
#if BIND_apr_file_write_FUNCTION
  mrb_define_class_method(mrb, APR_module, "apr_file_write", mrb_APR_apr_file_write, MRB_ARGS_ARG(apr_file_write_REQUIRED_ARGC, apr_file_write_OPTIONAL_ARGC));
#endif
#if BIND_apr_file_write_full_FUNCTION
  mrb_define_class_method(mrb, APR_module, "apr_file_write_full", mrb_APR_apr_file_write_full, MRB_ARGS_ARG(apr_file_write_full_REQUIRED_ARGC, apr_file_write_full_OPTIONAL_ARGC));
#endif
#if BIND_apr_file_writev_FUNCTION
  mrb_define_class_method(mrb, APR_module, "apr_file_writev", mrb_APR_apr_file_writev, MRB_ARGS_ARG(apr_file_writev_REQUIRED_ARGC, apr_file_writev_OPTIONAL_ARGC));
#endif
#if BIND_apr_file_writev_full_FUNCTION
  mrb_define_class_method(mrb, APR_module, "apr_file_writev_full", mrb_APR_apr_file_writev_full, MRB_ARGS_ARG(apr_file_writev_full_REQUIRED_ARGC, apr_file_writev_full_OPTIONAL_ARGC));
#endif
#if BIND_apr_filepath_encoding_FUNCTION
  mrb_define_class_method(mrb, APR_module, "apr_filepath_encoding", mrb_APR_apr_filepath_encoding, MRB_ARGS_ARG(apr_filepath_encoding_REQUIRED_ARGC, apr_filepath_encoding_OPTIONAL_ARGC));
#endif
#if BIND_apr_filepath_get_FUNCTION
  mrb_define_class_method(mrb, APR_module, "apr_filepath_get", mrb_APR_apr_filepath_get, MRB_ARGS_ARG(apr_filepath_get_REQUIRED_ARGC, apr_filepath_get_OPTIONAL_ARGC));
#endif
#if BIND_apr_filepath_list_merge_FUNCTION
  mrb_define_class_method(mrb, APR_module, "apr_filepath_list_merge", mrb_APR_apr_filepath_list_merge, MRB_ARGS_ARG(apr_filepath_list_merge_REQUIRED_ARGC, apr_filepath_list_merge_OPTIONAL_ARGC));
#endif
#if BIND_apr_filepath_list_split_FUNCTION
  mrb_define_class_method(mrb, APR_module, "apr_filepath_list_split", mrb_APR_apr_filepath_list_split, MRB_ARGS_ARG(apr_filepath_list_split_REQUIRED_ARGC, apr_filepath_list_split_OPTIONAL_ARGC));
#endif
#if BIND_apr_filepath_merge_FUNCTION
  mrb_define_class_method(mrb, APR_module, "apr_filepath_merge", mrb_APR_apr_filepath_merge, MRB_ARGS_ARG(apr_filepath_merge_REQUIRED_ARGC, apr_filepath_merge_OPTIONAL_ARGC));
#endif
#if BIND_apr_filepath_root_FUNCTION
  mrb_define_class_method(mrb, APR_module, "apr_filepath_root", mrb_APR_apr_filepath_root, MRB_ARGS_ARG(apr_filepath_root_REQUIRED_ARGC, apr_filepath_root_OPTIONAL_ARGC));
#endif
#if BIND_apr_filepath_set_FUNCTION
  mrb_define_class_method(mrb, APR_module, "apr_filepath_set", mrb_APR_apr_filepath_set, MRB_ARGS_ARG(apr_filepath_set_REQUIRED_ARGC, apr_filepath_set_OPTIONAL_ARGC));
#endif
#if BIND_apr_fnmatch_FUNCTION
  mrb_define_class_method(mrb, APR_module, "apr_fnmatch", mrb_APR_apr_fnmatch, MRB_ARGS_ARG(apr_fnmatch_REQUIRED_ARGC, apr_fnmatch_OPTIONAL_ARGC));
#endif
#if BIND_apr_fnmatch_test_FUNCTION
  mrb_define_class_method(mrb, APR_module, "apr_fnmatch_test", mrb_APR_apr_fnmatch_test, MRB_ARGS_ARG(apr_fnmatch_test_REQUIRED_ARGC, apr_fnmatch_test_OPTIONAL_ARGC));
#endif
#if BIND_apr_generate_random_bytes_FUNCTION
  mrb_define_class_method(mrb, APR_module, "apr_generate_random_bytes", mrb_APR_apr_generate_random_bytes, MRB_ARGS_ARG(apr_generate_random_bytes_REQUIRED_ARGC, apr_generate_random_bytes_OPTIONAL_ARGC));
#endif
#if BIND_apr_gethostname_FUNCTION
  mrb_define_class_method(mrb, APR_module, "apr_gethostname", mrb_APR_apr_gethostname, MRB_ARGS_ARG(apr_gethostname_REQUIRED_ARGC, apr_gethostname_OPTIONAL_ARGC));
#endif
#if BIND_apr_getnameinfo_FUNCTION
  mrb_define_class_method(mrb, APR_module, "apr_getnameinfo", mrb_APR_apr_getnameinfo, MRB_ARGS_ARG(apr_getnameinfo_REQUIRED_ARGC, apr_getnameinfo_OPTIONAL_ARGC));
#endif
#if BIND_apr_getservbyname_FUNCTION
  mrb_define_class_method(mrb, APR_module, "apr_getservbyname", mrb_APR_apr_getservbyname, MRB_ARGS_ARG(apr_getservbyname_REQUIRED_ARGC, apr_getservbyname_OPTIONAL_ARGC));
#endif
#if BIND_apr_global_mutex_child_init_FUNCTION
  mrb_define_class_method(mrb, APR_module, "apr_global_mutex_child_init", mrb_APR_apr_global_mutex_child_init, MRB_ARGS_ARG(apr_global_mutex_child_init_REQUIRED_ARGC, apr_global_mutex_child_init_OPTIONAL_ARGC));
#endif
#if BIND_apr_global_mutex_create_FUNCTION
  mrb_define_class_method(mrb, APR_module, "apr_global_mutex_create", mrb_APR_apr_global_mutex_create, MRB_ARGS_ARG(apr_global_mutex_create_REQUIRED_ARGC, apr_global_mutex_create_OPTIONAL_ARGC));
#endif
#if BIND_apr_global_mutex_destroy_FUNCTION
  mrb_define_class_method(mrb, APR_module, "apr_global_mutex_destroy", mrb_APR_apr_global_mutex_destroy, MRB_ARGS_ARG(apr_global_mutex_destroy_REQUIRED_ARGC, apr_global_mutex_destroy_OPTIONAL_ARGC));
#endif
#if BIND_apr_global_mutex_lock_FUNCTION
  mrb_define_class_method(mrb, APR_module, "apr_global_mutex_lock", mrb_APR_apr_global_mutex_lock, MRB_ARGS_ARG(apr_global_mutex_lock_REQUIRED_ARGC, apr_global_mutex_lock_OPTIONAL_ARGC));
#endif
#if BIND_apr_global_mutex_lockfile_FUNCTION
  mrb_define_class_method(mrb, APR_module, "apr_global_mutex_lockfile", mrb_APR_apr_global_mutex_lockfile, MRB_ARGS_ARG(apr_global_mutex_lockfile_REQUIRED_ARGC, apr_global_mutex_lockfile_OPTIONAL_ARGC));
#endif
#if BIND_apr_global_mutex_name_FUNCTION
  mrb_define_class_method(mrb, APR_module, "apr_global_mutex_name", mrb_APR_apr_global_mutex_name, MRB_ARGS_ARG(apr_global_mutex_name_REQUIRED_ARGC, apr_global_mutex_name_OPTIONAL_ARGC));
#endif
#if BIND_apr_global_mutex_trylock_FUNCTION
  mrb_define_class_method(mrb, APR_module, "apr_global_mutex_trylock", mrb_APR_apr_global_mutex_trylock, MRB_ARGS_ARG(apr_global_mutex_trylock_REQUIRED_ARGC, apr_global_mutex_trylock_OPTIONAL_ARGC));
#endif
#if BIND_apr_global_mutex_unlock_FUNCTION
  mrb_define_class_method(mrb, APR_module, "apr_global_mutex_unlock", mrb_APR_apr_global_mutex_unlock, MRB_ARGS_ARG(apr_global_mutex_unlock_REQUIRED_ARGC, apr_global_mutex_unlock_OPTIONAL_ARGC));
#endif
#if BIND_apr_initialize_FUNCTION
  mrb_define_class_method(mrb, APR_module, "apr_initialize", mrb_APR_apr_initialize, MRB_ARGS_ARG(apr_initialize_REQUIRED_ARGC, apr_initialize_OPTIONAL_ARGC));
#endif
#if BIND_apr_ipsubnet_create_FUNCTION
  mrb_define_class_method(mrb, APR_module, "apr_ipsubnet_create", mrb_APR_apr_ipsubnet_create, MRB_ARGS_ARG(apr_ipsubnet_create_REQUIRED_ARGC, apr_ipsubnet_create_OPTIONAL_ARGC));
#endif
#if BIND_apr_ipsubnet_test_FUNCTION
  mrb_define_class_method(mrb, APR_module, "apr_ipsubnet_test", mrb_APR_apr_ipsubnet_test, MRB_ARGS_ARG(apr_ipsubnet_test_REQUIRED_ARGC, apr_ipsubnet_test_OPTIONAL_ARGC));
#endif
#if BIND_apr_itoa_FUNCTION
  mrb_define_class_method(mrb, APR_module, "apr_itoa", mrb_APR_apr_itoa, MRB_ARGS_ARG(apr_itoa_REQUIRED_ARGC, apr_itoa_OPTIONAL_ARGC));
#endif
#if BIND_apr_ltoa_FUNCTION
  mrb_define_class_method(mrb, APR_module, "apr_ltoa", mrb_APR_apr_ltoa, MRB_ARGS_ARG(apr_ltoa_REQUIRED_ARGC, apr_ltoa_OPTIONAL_ARGC));
#endif
#if BIND_apr_match_glob_FUNCTION
  mrb_define_class_method(mrb, APR_module, "apr_match_glob", mrb_APR_apr_match_glob, MRB_ARGS_ARG(apr_match_glob_REQUIRED_ARGC, apr_match_glob_OPTIONAL_ARGC));
#endif
#if BIND_apr_mcast_hops_FUNCTION
  mrb_define_class_method(mrb, APR_module, "apr_mcast_hops", mrb_APR_apr_mcast_hops, MRB_ARGS_ARG(apr_mcast_hops_REQUIRED_ARGC, apr_mcast_hops_OPTIONAL_ARGC));
#endif
#if BIND_apr_mcast_interface_FUNCTION
  mrb_define_class_method(mrb, APR_module, "apr_mcast_interface", mrb_APR_apr_mcast_interface, MRB_ARGS_ARG(apr_mcast_interface_REQUIRED_ARGC, apr_mcast_interface_OPTIONAL_ARGC));
#endif
#if BIND_apr_mcast_join_FUNCTION
  mrb_define_class_method(mrb, APR_module, "apr_mcast_join", mrb_APR_apr_mcast_join, MRB_ARGS_ARG(apr_mcast_join_REQUIRED_ARGC, apr_mcast_join_OPTIONAL_ARGC));
#endif
#if BIND_apr_mcast_leave_FUNCTION
  mrb_define_class_method(mrb, APR_module, "apr_mcast_leave", mrb_APR_apr_mcast_leave, MRB_ARGS_ARG(apr_mcast_leave_REQUIRED_ARGC, apr_mcast_leave_OPTIONAL_ARGC));
#endif
#if BIND_apr_mcast_loopback_FUNCTION
  mrb_define_class_method(mrb, APR_module, "apr_mcast_loopback", mrb_APR_apr_mcast_loopback, MRB_ARGS_ARG(apr_mcast_loopback_REQUIRED_ARGC, apr_mcast_loopback_OPTIONAL_ARGC));
#endif
#if BIND_apr_off_t_toa_FUNCTION
  mrb_define_class_method(mrb, APR_module, "apr_off_t_toa", mrb_APR_apr_off_t_toa, MRB_ARGS_ARG(apr_off_t_toa_REQUIRED_ARGC, apr_off_t_toa_OPTIONAL_ARGC));
#endif
#if BIND_apr_palloc_FUNCTION
  mrb_define_class_method(mrb, APR_module, "apr_palloc", mrb_APR_apr_palloc, MRB_ARGS_ARG(apr_palloc_REQUIRED_ARGC, apr_palloc_OPTIONAL_ARGC));
#endif
#if BIND_apr_palloc_debug_FUNCTION
  mrb_define_class_method(mrb, APR_module, "apr_palloc_debug", mrb_APR_apr_palloc_debug, MRB_ARGS_ARG(apr_palloc_debug_REQUIRED_ARGC, apr_palloc_debug_OPTIONAL_ARGC));
#endif
#if BIND_apr_parse_addr_port_FUNCTION
  mrb_define_class_method(mrb, APR_module, "apr_parse_addr_port", mrb_APR_apr_parse_addr_port, MRB_ARGS_ARG(apr_parse_addr_port_REQUIRED_ARGC, apr_parse_addr_port_OPTIONAL_ARGC));
#endif
#if BIND_apr_pcalloc_debug_FUNCTION
  mrb_define_class_method(mrb, APR_module, "apr_pcalloc_debug", mrb_APR_apr_pcalloc_debug, MRB_ARGS_ARG(apr_pcalloc_debug_REQUIRED_ARGC, apr_pcalloc_debug_OPTIONAL_ARGC));
#endif
#if BIND_apr_pmemdup_FUNCTION
  mrb_define_class_method(mrb, APR_module, "apr_pmemdup", mrb_APR_apr_pmemdup, MRB_ARGS_ARG(apr_pmemdup_REQUIRED_ARGC, apr_pmemdup_OPTIONAL_ARGC));
#endif
#if BIND_apr_pool_abort_get_FUNCTION
  mrb_define_class_method(mrb, APR_module, "apr_pool_abort_get", mrb_APR_apr_pool_abort_get, MRB_ARGS_ARG(apr_pool_abort_get_REQUIRED_ARGC, apr_pool_abort_get_OPTIONAL_ARGC));
#endif
#if BIND_apr_pool_abort_set_FUNCTION
  mrb_define_class_method(mrb, APR_module, "apr_pool_abort_set", mrb_APR_apr_pool_abort_set, MRB_ARGS_ARG(apr_pool_abort_set_REQUIRED_ARGC, apr_pool_abort_set_OPTIONAL_ARGC));
#endif
#if BIND_apr_pool_allocator_get_FUNCTION
  mrb_define_class_method(mrb, APR_module, "apr_pool_allocator_get", mrb_APR_apr_pool_allocator_get, MRB_ARGS_ARG(apr_pool_allocator_get_REQUIRED_ARGC, apr_pool_allocator_get_OPTIONAL_ARGC));
#endif
#if BIND_apr_pool_child_cleanup_set_FUNCTION
  mrb_define_class_method(mrb, APR_module, "apr_pool_child_cleanup_set", mrb_APR_apr_pool_child_cleanup_set, MRB_ARGS_ARG(apr_pool_child_cleanup_set_REQUIRED_ARGC, apr_pool_child_cleanup_set_OPTIONAL_ARGC));
#endif
#if BIND_apr_pool_cleanup_for_exec_FUNCTION
  mrb_define_class_method(mrb, APR_module, "apr_pool_cleanup_for_exec", mrb_APR_apr_pool_cleanup_for_exec, MRB_ARGS_ARG(apr_pool_cleanup_for_exec_REQUIRED_ARGC, apr_pool_cleanup_for_exec_OPTIONAL_ARGC));
#endif
#if BIND_apr_pool_cleanup_kill_FUNCTION
  mrb_define_class_method(mrb, APR_module, "apr_pool_cleanup_kill", mrb_APR_apr_pool_cleanup_kill, MRB_ARGS_ARG(apr_pool_cleanup_kill_REQUIRED_ARGC, apr_pool_cleanup_kill_OPTIONAL_ARGC));
#endif
#if BIND_apr_pool_cleanup_null_FUNCTION
  mrb_define_class_method(mrb, APR_module, "apr_pool_cleanup_null", mrb_APR_apr_pool_cleanup_null, MRB_ARGS_ARG(apr_pool_cleanup_null_REQUIRED_ARGC, apr_pool_cleanup_null_OPTIONAL_ARGC));
#endif
#if BIND_apr_pool_cleanup_register_FUNCTION
  mrb_define_class_method(mrb, APR_module, "apr_pool_cleanup_register", mrb_APR_apr_pool_cleanup_register, MRB_ARGS_ARG(apr_pool_cleanup_register_REQUIRED_ARGC, apr_pool_cleanup_register_OPTIONAL_ARGC));
#endif
#if BIND_apr_pool_cleanup_run_FUNCTION
  mrb_define_class_method(mrb, APR_module, "apr_pool_cleanup_run", mrb_APR_apr_pool_cleanup_run, MRB_ARGS_ARG(apr_pool_cleanup_run_REQUIRED_ARGC, apr_pool_cleanup_run_OPTIONAL_ARGC));
#endif
#if BIND_apr_pool_clear_FUNCTION
  mrb_define_class_method(mrb, APR_module, "apr_pool_clear", mrb_APR_apr_pool_clear, MRB_ARGS_ARG(apr_pool_clear_REQUIRED_ARGC, apr_pool_clear_OPTIONAL_ARGC));
#endif
#if BIND_apr_pool_clear_debug_FUNCTION
  mrb_define_class_method(mrb, APR_module, "apr_pool_clear_debug", mrb_APR_apr_pool_clear_debug, MRB_ARGS_ARG(apr_pool_clear_debug_REQUIRED_ARGC, apr_pool_clear_debug_OPTIONAL_ARGC));
#endif
#if BIND_apr_pool_create_core_ex_FUNCTION
  mrb_define_class_method(mrb, APR_module, "apr_pool_create_core_ex", mrb_APR_apr_pool_create_core_ex, MRB_ARGS_ARG(apr_pool_create_core_ex_REQUIRED_ARGC, apr_pool_create_core_ex_OPTIONAL_ARGC));
#endif
#if BIND_apr_pool_create_core_ex_debug_FUNCTION
  mrb_define_class_method(mrb, APR_module, "apr_pool_create_core_ex_debug", mrb_APR_apr_pool_create_core_ex_debug, MRB_ARGS_ARG(apr_pool_create_core_ex_debug_REQUIRED_ARGC, apr_pool_create_core_ex_debug_OPTIONAL_ARGC));
#endif
#if BIND_apr_pool_create_ex_FUNCTION
  mrb_define_class_method(mrb, APR_module, "apr_pool_create_ex", mrb_APR_apr_pool_create_ex, MRB_ARGS_ARG(apr_pool_create_ex_REQUIRED_ARGC, apr_pool_create_ex_OPTIONAL_ARGC));
#endif
#if BIND_apr_pool_create_ex_debug_FUNCTION
  mrb_define_class_method(mrb, APR_module, "apr_pool_create_ex_debug", mrb_APR_apr_pool_create_ex_debug, MRB_ARGS_ARG(apr_pool_create_ex_debug_REQUIRED_ARGC, apr_pool_create_ex_debug_OPTIONAL_ARGC));
#endif
#if BIND_apr_pool_create_unmanaged_ex_FUNCTION
  mrb_define_class_method(mrb, APR_module, "apr_pool_create_unmanaged_ex", mrb_APR_apr_pool_create_unmanaged_ex, MRB_ARGS_ARG(apr_pool_create_unmanaged_ex_REQUIRED_ARGC, apr_pool_create_unmanaged_ex_OPTIONAL_ARGC));
#endif
#if BIND_apr_pool_create_unmanaged_ex_debug_FUNCTION
  mrb_define_class_method(mrb, APR_module, "apr_pool_create_unmanaged_ex_debug", mrb_APR_apr_pool_create_unmanaged_ex_debug, MRB_ARGS_ARG(apr_pool_create_unmanaged_ex_debug_REQUIRED_ARGC, apr_pool_create_unmanaged_ex_debug_OPTIONAL_ARGC));
#endif
#if BIND_apr_pool_destroy_FUNCTION
  mrb_define_class_method(mrb, APR_module, "apr_pool_destroy", mrb_APR_apr_pool_destroy, MRB_ARGS_ARG(apr_pool_destroy_REQUIRED_ARGC, apr_pool_destroy_OPTIONAL_ARGC));
#endif
#if BIND_apr_pool_destroy_debug_FUNCTION
  mrb_define_class_method(mrb, APR_module, "apr_pool_destroy_debug", mrb_APR_apr_pool_destroy_debug, MRB_ARGS_ARG(apr_pool_destroy_debug_REQUIRED_ARGC, apr_pool_destroy_debug_OPTIONAL_ARGC));
#endif
#if BIND_apr_pool_initialize_FUNCTION
  mrb_define_class_method(mrb, APR_module, "apr_pool_initialize", mrb_APR_apr_pool_initialize, MRB_ARGS_ARG(apr_pool_initialize_REQUIRED_ARGC, apr_pool_initialize_OPTIONAL_ARGC));
#endif
#if BIND_apr_pool_is_ancestor_FUNCTION
  mrb_define_class_method(mrb, APR_module, "apr_pool_is_ancestor", mrb_APR_apr_pool_is_ancestor, MRB_ARGS_ARG(apr_pool_is_ancestor_REQUIRED_ARGC, apr_pool_is_ancestor_OPTIONAL_ARGC));
#endif
#if BIND_apr_pool_note_subprocess_FUNCTION
  mrb_define_class_method(mrb, APR_module, "apr_pool_note_subprocess", mrb_APR_apr_pool_note_subprocess, MRB_ARGS_ARG(apr_pool_note_subprocess_REQUIRED_ARGC, apr_pool_note_subprocess_OPTIONAL_ARGC));
#endif
#if BIND_apr_pool_parent_get_FUNCTION
  mrb_define_class_method(mrb, APR_module, "apr_pool_parent_get", mrb_APR_apr_pool_parent_get, MRB_ARGS_ARG(apr_pool_parent_get_REQUIRED_ARGC, apr_pool_parent_get_OPTIONAL_ARGC));
#endif
#if BIND_apr_pool_pre_cleanup_register_FUNCTION
  mrb_define_class_method(mrb, APR_module, "apr_pool_pre_cleanup_register", mrb_APR_apr_pool_pre_cleanup_register, MRB_ARGS_ARG(apr_pool_pre_cleanup_register_REQUIRED_ARGC, apr_pool_pre_cleanup_register_OPTIONAL_ARGC));
#endif
#if BIND_apr_pool_tag_FUNCTION
  mrb_define_class_method(mrb, APR_module, "apr_pool_tag", mrb_APR_apr_pool_tag, MRB_ARGS_ARG(apr_pool_tag_REQUIRED_ARGC, apr_pool_tag_OPTIONAL_ARGC));
#endif
#if BIND_apr_pool_terminate_FUNCTION
  mrb_define_class_method(mrb, APR_module, "apr_pool_terminate", mrb_APR_apr_pool_terminate, MRB_ARGS_ARG(apr_pool_terminate_REQUIRED_ARGC, apr_pool_terminate_OPTIONAL_ARGC));
#endif
#if BIND_apr_pool_userdata_get_FUNCTION
  mrb_define_class_method(mrb, APR_module, "apr_pool_userdata_get", mrb_APR_apr_pool_userdata_get, MRB_ARGS_ARG(apr_pool_userdata_get_REQUIRED_ARGC, apr_pool_userdata_get_OPTIONAL_ARGC));
#endif
#if BIND_apr_pool_userdata_set_FUNCTION
  mrb_define_class_method(mrb, APR_module, "apr_pool_userdata_set", mrb_APR_apr_pool_userdata_set, MRB_ARGS_ARG(apr_pool_userdata_set_REQUIRED_ARGC, apr_pool_userdata_set_OPTIONAL_ARGC));
#endif
#if BIND_apr_pool_userdata_setn_FUNCTION
  mrb_define_class_method(mrb, APR_module, "apr_pool_userdata_setn", mrb_APR_apr_pool_userdata_setn, MRB_ARGS_ARG(apr_pool_userdata_setn_REQUIRED_ARGC, apr_pool_userdata_setn_OPTIONAL_ARGC));
#endif
#if BIND_apr_proc_create_FUNCTION
  mrb_define_class_method(mrb, APR_module, "apr_proc_create", mrb_APR_apr_proc_create, MRB_ARGS_ARG(apr_proc_create_REQUIRED_ARGC, apr_proc_create_OPTIONAL_ARGC));
#endif
#if BIND_apr_proc_detach_FUNCTION
  mrb_define_class_method(mrb, APR_module, "apr_proc_detach", mrb_APR_apr_proc_detach, MRB_ARGS_ARG(apr_proc_detach_REQUIRED_ARGC, apr_proc_detach_OPTIONAL_ARGC));
#endif
#if BIND_apr_proc_fork_FUNCTION
  mrb_define_class_method(mrb, APR_module, "apr_proc_fork", mrb_APR_apr_proc_fork, MRB_ARGS_ARG(apr_proc_fork_REQUIRED_ARGC, apr_proc_fork_OPTIONAL_ARGC));
#endif
#if BIND_apr_proc_kill_FUNCTION
  mrb_define_class_method(mrb, APR_module, "apr_proc_kill", mrb_APR_apr_proc_kill, MRB_ARGS_ARG(apr_proc_kill_REQUIRED_ARGC, apr_proc_kill_OPTIONAL_ARGC));
#endif
#if BIND_apr_proc_mutex_child_init_FUNCTION
  mrb_define_class_method(mrb, APR_module, "apr_proc_mutex_child_init", mrb_APR_apr_proc_mutex_child_init, MRB_ARGS_ARG(apr_proc_mutex_child_init_REQUIRED_ARGC, apr_proc_mutex_child_init_OPTIONAL_ARGC));
#endif
#if BIND_apr_proc_mutex_cleanup_FUNCTION
  mrb_define_class_method(mrb, APR_module, "apr_proc_mutex_cleanup", mrb_APR_apr_proc_mutex_cleanup, MRB_ARGS_ARG(apr_proc_mutex_cleanup_REQUIRED_ARGC, apr_proc_mutex_cleanup_OPTIONAL_ARGC));
#endif
#if BIND_apr_proc_mutex_create_FUNCTION
  mrb_define_class_method(mrb, APR_module, "apr_proc_mutex_create", mrb_APR_apr_proc_mutex_create, MRB_ARGS_ARG(apr_proc_mutex_create_REQUIRED_ARGC, apr_proc_mutex_create_OPTIONAL_ARGC));
#endif
#if BIND_apr_proc_mutex_defname_FUNCTION
  mrb_define_class_method(mrb, APR_module, "apr_proc_mutex_defname", mrb_APR_apr_proc_mutex_defname, MRB_ARGS_ARG(apr_proc_mutex_defname_REQUIRED_ARGC, apr_proc_mutex_defname_OPTIONAL_ARGC));
#endif
#if BIND_apr_proc_mutex_destroy_FUNCTION
  mrb_define_class_method(mrb, APR_module, "apr_proc_mutex_destroy", mrb_APR_apr_proc_mutex_destroy, MRB_ARGS_ARG(apr_proc_mutex_destroy_REQUIRED_ARGC, apr_proc_mutex_destroy_OPTIONAL_ARGC));
#endif
#if BIND_apr_proc_mutex_lock_FUNCTION
  mrb_define_class_method(mrb, APR_module, "apr_proc_mutex_lock", mrb_APR_apr_proc_mutex_lock, MRB_ARGS_ARG(apr_proc_mutex_lock_REQUIRED_ARGC, apr_proc_mutex_lock_OPTIONAL_ARGC));
#endif
#if BIND_apr_proc_mutex_lockfile_FUNCTION
  mrb_define_class_method(mrb, APR_module, "apr_proc_mutex_lockfile", mrb_APR_apr_proc_mutex_lockfile, MRB_ARGS_ARG(apr_proc_mutex_lockfile_REQUIRED_ARGC, apr_proc_mutex_lockfile_OPTIONAL_ARGC));
#endif
#if BIND_apr_proc_mutex_name_FUNCTION
  mrb_define_class_method(mrb, APR_module, "apr_proc_mutex_name", mrb_APR_apr_proc_mutex_name, MRB_ARGS_ARG(apr_proc_mutex_name_REQUIRED_ARGC, apr_proc_mutex_name_OPTIONAL_ARGC));
#endif
#if BIND_apr_proc_mutex_trylock_FUNCTION
  mrb_define_class_method(mrb, APR_module, "apr_proc_mutex_trylock", mrb_APR_apr_proc_mutex_trylock, MRB_ARGS_ARG(apr_proc_mutex_trylock_REQUIRED_ARGC, apr_proc_mutex_trylock_OPTIONAL_ARGC));
#endif
#if BIND_apr_proc_mutex_unlock_FUNCTION
  mrb_define_class_method(mrb, APR_module, "apr_proc_mutex_unlock", mrb_APR_apr_proc_mutex_unlock, MRB_ARGS_ARG(apr_proc_mutex_unlock_REQUIRED_ARGC, apr_proc_mutex_unlock_OPTIONAL_ARGC));
#endif
#if BIND_apr_proc_other_child_alert_FUNCTION
  mrb_define_class_method(mrb, APR_module, "apr_proc_other_child_alert", mrb_APR_apr_proc_other_child_alert, MRB_ARGS_ARG(apr_proc_other_child_alert_REQUIRED_ARGC, apr_proc_other_child_alert_OPTIONAL_ARGC));
#endif
#if BIND_apr_proc_other_child_refresh_FUNCTION
  mrb_define_class_method(mrb, APR_module, "apr_proc_other_child_refresh", mrb_APR_apr_proc_other_child_refresh, MRB_ARGS_ARG(apr_proc_other_child_refresh_REQUIRED_ARGC, apr_proc_other_child_refresh_OPTIONAL_ARGC));
#endif
#if BIND_apr_proc_other_child_refresh_all_FUNCTION
  mrb_define_class_method(mrb, APR_module, "apr_proc_other_child_refresh_all", mrb_APR_apr_proc_other_child_refresh_all, MRB_ARGS_ARG(apr_proc_other_child_refresh_all_REQUIRED_ARGC, apr_proc_other_child_refresh_all_OPTIONAL_ARGC));
#endif
#if BIND_apr_proc_other_child_register_FUNCTION
  mrb_define_class_method(mrb, APR_module, "apr_proc_other_child_register", mrb_APR_apr_proc_other_child_register, MRB_ARGS_ARG(apr_proc_other_child_register_REQUIRED_ARGC, apr_proc_other_child_register_OPTIONAL_ARGC));
#endif
#if BIND_apr_proc_other_child_unregister_FUNCTION
  mrb_define_class_method(mrb, APR_module, "apr_proc_other_child_unregister", mrb_APR_apr_proc_other_child_unregister, MRB_ARGS_ARG(apr_proc_other_child_unregister_REQUIRED_ARGC, apr_proc_other_child_unregister_OPTIONAL_ARGC));
#endif
#if BIND_apr_proc_wait_FUNCTION
  mrb_define_class_method(mrb, APR_module, "apr_proc_wait", mrb_APR_apr_proc_wait, MRB_ARGS_ARG(apr_proc_wait_REQUIRED_ARGC, apr_proc_wait_OPTIONAL_ARGC));
#endif
#if BIND_apr_proc_wait_all_procs_FUNCTION
  mrb_define_class_method(mrb, APR_module, "apr_proc_wait_all_procs", mrb_APR_apr_proc_wait_all_procs, MRB_ARGS_ARG(apr_proc_wait_all_procs_REQUIRED_ARGC, apr_proc_wait_all_procs_OPTIONAL_ARGC));
#endif
#if BIND_apr_procattr_addrspace_set_FUNCTION
  mrb_define_class_method(mrb, APR_module, "apr_procattr_addrspace_set", mrb_APR_apr_procattr_addrspace_set, MRB_ARGS_ARG(apr_procattr_addrspace_set_REQUIRED_ARGC, apr_procattr_addrspace_set_OPTIONAL_ARGC));
#endif
#if BIND_apr_procattr_child_err_set_FUNCTION
  mrb_define_class_method(mrb, APR_module, "apr_procattr_child_err_set", mrb_APR_apr_procattr_child_err_set, MRB_ARGS_ARG(apr_procattr_child_err_set_REQUIRED_ARGC, apr_procattr_child_err_set_OPTIONAL_ARGC));
#endif
#if BIND_apr_procattr_child_errfn_set_FUNCTION
  mrb_define_class_method(mrb, APR_module, "apr_procattr_child_errfn_set", mrb_APR_apr_procattr_child_errfn_set, MRB_ARGS_ARG(apr_procattr_child_errfn_set_REQUIRED_ARGC, apr_procattr_child_errfn_set_OPTIONAL_ARGC));
#endif
#if BIND_apr_procattr_child_in_set_FUNCTION
  mrb_define_class_method(mrb, APR_module, "apr_procattr_child_in_set", mrb_APR_apr_procattr_child_in_set, MRB_ARGS_ARG(apr_procattr_child_in_set_REQUIRED_ARGC, apr_procattr_child_in_set_OPTIONAL_ARGC));
#endif
#if BIND_apr_procattr_child_out_set_FUNCTION
  mrb_define_class_method(mrb, APR_module, "apr_procattr_child_out_set", mrb_APR_apr_procattr_child_out_set, MRB_ARGS_ARG(apr_procattr_child_out_set_REQUIRED_ARGC, apr_procattr_child_out_set_OPTIONAL_ARGC));
#endif
#if BIND_apr_procattr_cmdtype_set_FUNCTION
  mrb_define_class_method(mrb, APR_module, "apr_procattr_cmdtype_set", mrb_APR_apr_procattr_cmdtype_set, MRB_ARGS_ARG(apr_procattr_cmdtype_set_REQUIRED_ARGC, apr_procattr_cmdtype_set_OPTIONAL_ARGC));
#endif
#if BIND_apr_procattr_create_FUNCTION
  mrb_define_class_method(mrb, APR_module, "apr_procattr_create", mrb_APR_apr_procattr_create, MRB_ARGS_ARG(apr_procattr_create_REQUIRED_ARGC, apr_procattr_create_OPTIONAL_ARGC));
#endif
#if BIND_apr_procattr_detach_set_FUNCTION
  mrb_define_class_method(mrb, APR_module, "apr_procattr_detach_set", mrb_APR_apr_procattr_detach_set, MRB_ARGS_ARG(apr_procattr_detach_set_REQUIRED_ARGC, apr_procattr_detach_set_OPTIONAL_ARGC));
#endif
#if BIND_apr_procattr_dir_set_FUNCTION
  mrb_define_class_method(mrb, APR_module, "apr_procattr_dir_set", mrb_APR_apr_procattr_dir_set, MRB_ARGS_ARG(apr_procattr_dir_set_REQUIRED_ARGC, apr_procattr_dir_set_OPTIONAL_ARGC));
#endif
#if BIND_apr_procattr_error_check_set_FUNCTION
  mrb_define_class_method(mrb, APR_module, "apr_procattr_error_check_set", mrb_APR_apr_procattr_error_check_set, MRB_ARGS_ARG(apr_procattr_error_check_set_REQUIRED_ARGC, apr_procattr_error_check_set_OPTIONAL_ARGC));
#endif
#if BIND_apr_procattr_group_set_FUNCTION
  mrb_define_class_method(mrb, APR_module, "apr_procattr_group_set", mrb_APR_apr_procattr_group_set, MRB_ARGS_ARG(apr_procattr_group_set_REQUIRED_ARGC, apr_procattr_group_set_OPTIONAL_ARGC));
#endif
#if BIND_apr_procattr_io_set_FUNCTION
  mrb_define_class_method(mrb, APR_module, "apr_procattr_io_set", mrb_APR_apr_procattr_io_set, MRB_ARGS_ARG(apr_procattr_io_set_REQUIRED_ARGC, apr_procattr_io_set_OPTIONAL_ARGC));
#endif
#if BIND_apr_procattr_limit_set_FUNCTION
  mrb_define_class_method(mrb, APR_module, "apr_procattr_limit_set", mrb_APR_apr_procattr_limit_set, MRB_ARGS_ARG(apr_procattr_limit_set_REQUIRED_ARGC, apr_procattr_limit_set_OPTIONAL_ARGC));
#endif
#if BIND_apr_procattr_user_set_FUNCTION
  mrb_define_class_method(mrb, APR_module, "apr_procattr_user_set", mrb_APR_apr_procattr_user_set, MRB_ARGS_ARG(apr_procattr_user_set_REQUIRED_ARGC, apr_procattr_user_set_OPTIONAL_ARGC));
#endif
#if BIND_apr_psprintf_FUNCTION
  mrb_define_class_method(mrb, APR_module, "apr_psprintf", mrb_APR_apr_psprintf, MRB_ARGS_ARG(apr_psprintf_REQUIRED_ARGC, apr_psprintf_OPTIONAL_ARGC));
#endif
#if BIND_apr_pstrcat_FUNCTION
  mrb_define_class_method(mrb, APR_module, "apr_pstrcat", mrb_APR_apr_pstrcat, MRB_ARGS_ARG(apr_pstrcat_REQUIRED_ARGC, apr_pstrcat_OPTIONAL_ARGC));
#endif
#if BIND_apr_pstrcatv_FUNCTION
  mrb_define_class_method(mrb, APR_module, "apr_pstrcatv", mrb_APR_apr_pstrcatv, MRB_ARGS_ARG(apr_pstrcatv_REQUIRED_ARGC, apr_pstrcatv_OPTIONAL_ARGC));
#endif
#if BIND_apr_pstrdup_FUNCTION
  mrb_define_class_method(mrb, APR_module, "apr_pstrdup", mrb_APR_apr_pstrdup, MRB_ARGS_ARG(apr_pstrdup_REQUIRED_ARGC, apr_pstrdup_OPTIONAL_ARGC));
#endif
#if BIND_apr_pstrmemdup_FUNCTION
  mrb_define_class_method(mrb, APR_module, "apr_pstrmemdup", mrb_APR_apr_pstrmemdup, MRB_ARGS_ARG(apr_pstrmemdup_REQUIRED_ARGC, apr_pstrmemdup_OPTIONAL_ARGC));
#endif
#if BIND_apr_pstrndup_FUNCTION
  mrb_define_class_method(mrb, APR_module, "apr_pstrndup", mrb_APR_apr_pstrndup, MRB_ARGS_ARG(apr_pstrndup_REQUIRED_ARGC, apr_pstrndup_OPTIONAL_ARGC));
#endif
#if BIND_apr_pvsprintf_FUNCTION
  mrb_define_class_method(mrb, APR_module, "apr_pvsprintf", mrb_APR_apr_pvsprintf, MRB_ARGS_ARG(apr_pvsprintf_REQUIRED_ARGC, apr_pvsprintf_OPTIONAL_ARGC));
#endif
#if BIND_apr_rfc822_date_FUNCTION
  mrb_define_class_method(mrb, APR_module, "apr_rfc822_date", mrb_APR_apr_rfc822_date, MRB_ARGS_ARG(apr_rfc822_date_REQUIRED_ARGC, apr_rfc822_date_OPTIONAL_ARGC));
#endif
#if BIND_apr_setup_signal_thread_FUNCTION
  mrb_define_class_method(mrb, APR_module, "apr_setup_signal_thread", mrb_APR_apr_setup_signal_thread, MRB_ARGS_ARG(apr_setup_signal_thread_REQUIRED_ARGC, apr_setup_signal_thread_OPTIONAL_ARGC));
#endif
#if BIND_apr_signal_FUNCTION
  mrb_define_class_method(mrb, APR_module, "apr_signal", mrb_APR_apr_signal, MRB_ARGS_ARG(apr_signal_REQUIRED_ARGC, apr_signal_OPTIONAL_ARGC));
#endif
#if BIND_apr_signal_block_FUNCTION
  mrb_define_class_method(mrb, APR_module, "apr_signal_block", mrb_APR_apr_signal_block, MRB_ARGS_ARG(apr_signal_block_REQUIRED_ARGC, apr_signal_block_OPTIONAL_ARGC));
#endif
#if BIND_apr_signal_description_get_FUNCTION
  mrb_define_class_method(mrb, APR_module, "apr_signal_description_get", mrb_APR_apr_signal_description_get, MRB_ARGS_ARG(apr_signal_description_get_REQUIRED_ARGC, apr_signal_description_get_OPTIONAL_ARGC));
#endif
#if BIND_apr_signal_init_FUNCTION
  mrb_define_class_method(mrb, APR_module, "apr_signal_init", mrb_APR_apr_signal_init, MRB_ARGS_ARG(apr_signal_init_REQUIRED_ARGC, apr_signal_init_OPTIONAL_ARGC));
#endif
#if BIND_apr_signal_thread_FUNCTION
  mrb_define_class_method(mrb, APR_module, "apr_signal_thread", mrb_APR_apr_signal_thread, MRB_ARGS_ARG(apr_signal_thread_REQUIRED_ARGC, apr_signal_thread_OPTIONAL_ARGC));
#endif
#if BIND_apr_signal_unblock_FUNCTION
  mrb_define_class_method(mrb, APR_module, "apr_signal_unblock", mrb_APR_apr_signal_unblock, MRB_ARGS_ARG(apr_signal_unblock_REQUIRED_ARGC, apr_signal_unblock_OPTIONAL_ARGC));
#endif
#if BIND_apr_sleep_FUNCTION
  mrb_define_class_method(mrb, APR_module, "apr_sleep", mrb_APR_apr_sleep, MRB_ARGS_ARG(apr_sleep_REQUIRED_ARGC, apr_sleep_OPTIONAL_ARGC));
#endif
#if BIND_apr_snprintf_FUNCTION
  mrb_define_class_method(mrb, APR_module, "apr_snprintf", mrb_APR_apr_snprintf, MRB_ARGS_ARG(apr_snprintf_REQUIRED_ARGC, apr_snprintf_OPTIONAL_ARGC));
#endif
#if BIND_apr_sockaddr_equal_FUNCTION
  mrb_define_class_method(mrb, APR_module, "apr_sockaddr_equal", mrb_APR_apr_sockaddr_equal, MRB_ARGS_ARG(apr_sockaddr_equal_REQUIRED_ARGC, apr_sockaddr_equal_OPTIONAL_ARGC));
#endif
#if BIND_apr_sockaddr_info_get_FUNCTION
  mrb_define_class_method(mrb, APR_module, "apr_sockaddr_info_get", mrb_APR_apr_sockaddr_info_get, MRB_ARGS_ARG(apr_sockaddr_info_get_REQUIRED_ARGC, apr_sockaddr_info_get_OPTIONAL_ARGC));
#endif
#if BIND_apr_sockaddr_ip_get_FUNCTION
  mrb_define_class_method(mrb, APR_module, "apr_sockaddr_ip_get", mrb_APR_apr_sockaddr_ip_get, MRB_ARGS_ARG(apr_sockaddr_ip_get_REQUIRED_ARGC, apr_sockaddr_ip_get_OPTIONAL_ARGC));
#endif
#if BIND_apr_sockaddr_ip_getbuf_FUNCTION
  mrb_define_class_method(mrb, APR_module, "apr_sockaddr_ip_getbuf", mrb_APR_apr_sockaddr_ip_getbuf, MRB_ARGS_ARG(apr_sockaddr_ip_getbuf_REQUIRED_ARGC, apr_sockaddr_ip_getbuf_OPTIONAL_ARGC));
#endif
#if BIND_apr_socket_accept_FUNCTION
  mrb_define_class_method(mrb, APR_module, "apr_socket_accept", mrb_APR_apr_socket_accept, MRB_ARGS_ARG(apr_socket_accept_REQUIRED_ARGC, apr_socket_accept_OPTIONAL_ARGC));
#endif
#if BIND_apr_socket_addr_get_FUNCTION
  mrb_define_class_method(mrb, APR_module, "apr_socket_addr_get", mrb_APR_apr_socket_addr_get, MRB_ARGS_ARG(apr_socket_addr_get_REQUIRED_ARGC, apr_socket_addr_get_OPTIONAL_ARGC));
#endif
#if BIND_apr_socket_atmark_FUNCTION
  mrb_define_class_method(mrb, APR_module, "apr_socket_atmark", mrb_APR_apr_socket_atmark, MRB_ARGS_ARG(apr_socket_atmark_REQUIRED_ARGC, apr_socket_atmark_OPTIONAL_ARGC));
#endif
#if BIND_apr_socket_atreadeof_FUNCTION
  mrb_define_class_method(mrb, APR_module, "apr_socket_atreadeof", mrb_APR_apr_socket_atreadeof, MRB_ARGS_ARG(apr_socket_atreadeof_REQUIRED_ARGC, apr_socket_atreadeof_OPTIONAL_ARGC));
#endif
#if BIND_apr_socket_bind_FUNCTION
  mrb_define_class_method(mrb, APR_module, "apr_socket_bind", mrb_APR_apr_socket_bind, MRB_ARGS_ARG(apr_socket_bind_REQUIRED_ARGC, apr_socket_bind_OPTIONAL_ARGC));
#endif
#if BIND_apr_socket_close_FUNCTION
  mrb_define_class_method(mrb, APR_module, "apr_socket_close", mrb_APR_apr_socket_close, MRB_ARGS_ARG(apr_socket_close_REQUIRED_ARGC, apr_socket_close_OPTIONAL_ARGC));
#endif
#if BIND_apr_socket_connect_FUNCTION
  mrb_define_class_method(mrb, APR_module, "apr_socket_connect", mrb_APR_apr_socket_connect, MRB_ARGS_ARG(apr_socket_connect_REQUIRED_ARGC, apr_socket_connect_OPTIONAL_ARGC));
#endif
#if BIND_apr_socket_create_FUNCTION
  mrb_define_class_method(mrb, APR_module, "apr_socket_create", mrb_APR_apr_socket_create, MRB_ARGS_ARG(apr_socket_create_REQUIRED_ARGC, apr_socket_create_OPTIONAL_ARGC));
#endif
#if BIND_apr_socket_data_get_FUNCTION
  mrb_define_class_method(mrb, APR_module, "apr_socket_data_get", mrb_APR_apr_socket_data_get, MRB_ARGS_ARG(apr_socket_data_get_REQUIRED_ARGC, apr_socket_data_get_OPTIONAL_ARGC));
#endif
#if BIND_apr_socket_data_set_FUNCTION
  mrb_define_class_method(mrb, APR_module, "apr_socket_data_set", mrb_APR_apr_socket_data_set, MRB_ARGS_ARG(apr_socket_data_set_REQUIRED_ARGC, apr_socket_data_set_OPTIONAL_ARGC));
#endif
#if BIND_apr_socket_listen_FUNCTION
  mrb_define_class_method(mrb, APR_module, "apr_socket_listen", mrb_APR_apr_socket_listen, MRB_ARGS_ARG(apr_socket_listen_REQUIRED_ARGC, apr_socket_listen_OPTIONAL_ARGC));
#endif
#if BIND_apr_socket_opt_get_FUNCTION
  mrb_define_class_method(mrb, APR_module, "apr_socket_opt_get", mrb_APR_apr_socket_opt_get, MRB_ARGS_ARG(apr_socket_opt_get_REQUIRED_ARGC, apr_socket_opt_get_OPTIONAL_ARGC));
#endif
#if BIND_apr_socket_opt_set_FUNCTION
  mrb_define_class_method(mrb, APR_module, "apr_socket_opt_set", mrb_APR_apr_socket_opt_set, MRB_ARGS_ARG(apr_socket_opt_set_REQUIRED_ARGC, apr_socket_opt_set_OPTIONAL_ARGC));
#endif
#if BIND_apr_socket_protocol_get_FUNCTION
  mrb_define_class_method(mrb, APR_module, "apr_socket_protocol_get", mrb_APR_apr_socket_protocol_get, MRB_ARGS_ARG(apr_socket_protocol_get_REQUIRED_ARGC, apr_socket_protocol_get_OPTIONAL_ARGC));
#endif
#if BIND_apr_socket_recv_FUNCTION
  mrb_define_class_method(mrb, APR_module, "apr_socket_recv", mrb_APR_apr_socket_recv, MRB_ARGS_ARG(apr_socket_recv_REQUIRED_ARGC, apr_socket_recv_OPTIONAL_ARGC));
#endif
#if BIND_apr_socket_recvfrom_FUNCTION
  mrb_define_class_method(mrb, APR_module, "apr_socket_recvfrom", mrb_APR_apr_socket_recvfrom, MRB_ARGS_ARG(apr_socket_recvfrom_REQUIRED_ARGC, apr_socket_recvfrom_OPTIONAL_ARGC));
#endif
#if BIND_apr_socket_send_FUNCTION
  mrb_define_class_method(mrb, APR_module, "apr_socket_send", mrb_APR_apr_socket_send, MRB_ARGS_ARG(apr_socket_send_REQUIRED_ARGC, apr_socket_send_OPTIONAL_ARGC));
#endif
#if BIND_apr_socket_sendfile_FUNCTION
  mrb_define_class_method(mrb, APR_module, "apr_socket_sendfile", mrb_APR_apr_socket_sendfile, MRB_ARGS_ARG(apr_socket_sendfile_REQUIRED_ARGC, apr_socket_sendfile_OPTIONAL_ARGC));
#endif
#if BIND_apr_socket_sendto_FUNCTION
  mrb_define_class_method(mrb, APR_module, "apr_socket_sendto", mrb_APR_apr_socket_sendto, MRB_ARGS_ARG(apr_socket_sendto_REQUIRED_ARGC, apr_socket_sendto_OPTIONAL_ARGC));
#endif
#if BIND_apr_socket_sendv_FUNCTION
  mrb_define_class_method(mrb, APR_module, "apr_socket_sendv", mrb_APR_apr_socket_sendv, MRB_ARGS_ARG(apr_socket_sendv_REQUIRED_ARGC, apr_socket_sendv_OPTIONAL_ARGC));
#endif
#if BIND_apr_socket_shutdown_FUNCTION
  mrb_define_class_method(mrb, APR_module, "apr_socket_shutdown", mrb_APR_apr_socket_shutdown, MRB_ARGS_ARG(apr_socket_shutdown_REQUIRED_ARGC, apr_socket_shutdown_OPTIONAL_ARGC));
#endif
#if BIND_apr_socket_timeout_get_FUNCTION
  mrb_define_class_method(mrb, APR_module, "apr_socket_timeout_get", mrb_APR_apr_socket_timeout_get, MRB_ARGS_ARG(apr_socket_timeout_get_REQUIRED_ARGC, apr_socket_timeout_get_OPTIONAL_ARGC));
#endif
#if BIND_apr_socket_timeout_set_FUNCTION
  mrb_define_class_method(mrb, APR_module, "apr_socket_timeout_set", mrb_APR_apr_socket_timeout_set, MRB_ARGS_ARG(apr_socket_timeout_set_REQUIRED_ARGC, apr_socket_timeout_set_OPTIONAL_ARGC));
#endif
#if BIND_apr_socket_type_get_FUNCTION
  mrb_define_class_method(mrb, APR_module, "apr_socket_type_get", mrb_APR_apr_socket_type_get, MRB_ARGS_ARG(apr_socket_type_get_REQUIRED_ARGC, apr_socket_type_get_OPTIONAL_ARGC));
#endif
#if BIND_apr_stat_FUNCTION
  mrb_define_class_method(mrb, APR_module, "apr_stat", mrb_APR_apr_stat, MRB_ARGS_ARG(apr_stat_REQUIRED_ARGC, apr_stat_OPTIONAL_ARGC));
#endif
#if BIND_apr_strerror_FUNCTION
  mrb_define_class_method(mrb, APR_module, "apr_strerror", mrb_APR_apr_strerror, MRB_ARGS_ARG(apr_strerror_REQUIRED_ARGC, apr_strerror_OPTIONAL_ARGC));
#endif
#if BIND_apr_strfsize_FUNCTION
  mrb_define_class_method(mrb, APR_module, "apr_strfsize", mrb_APR_apr_strfsize, MRB_ARGS_ARG(apr_strfsize_REQUIRED_ARGC, apr_strfsize_OPTIONAL_ARGC));
#endif
#if BIND_apr_strftime_FUNCTION
  mrb_define_class_method(mrb, APR_module, "apr_strftime", mrb_APR_apr_strftime, MRB_ARGS_ARG(apr_strftime_REQUIRED_ARGC, apr_strftime_OPTIONAL_ARGC));
#endif
#if BIND_apr_strnatcasecmp_FUNCTION
  mrb_define_class_method(mrb, APR_module, "apr_strnatcasecmp", mrb_APR_apr_strnatcasecmp, MRB_ARGS_ARG(apr_strnatcasecmp_REQUIRED_ARGC, apr_strnatcasecmp_OPTIONAL_ARGC));
#endif
#if BIND_apr_strnatcmp_FUNCTION
  mrb_define_class_method(mrb, APR_module, "apr_strnatcmp", mrb_APR_apr_strnatcmp, MRB_ARGS_ARG(apr_strnatcmp_REQUIRED_ARGC, apr_strnatcmp_OPTIONAL_ARGC));
#endif
#if BIND_apr_strtoff_FUNCTION
  mrb_define_class_method(mrb, APR_module, "apr_strtoff", mrb_APR_apr_strtoff, MRB_ARGS_ARG(apr_strtoff_REQUIRED_ARGC, apr_strtoff_OPTIONAL_ARGC));
#endif
#if BIND_apr_strtoi64_FUNCTION
  mrb_define_class_method(mrb, APR_module, "apr_strtoi64", mrb_APR_apr_strtoi64, MRB_ARGS_ARG(apr_strtoi64_REQUIRED_ARGC, apr_strtoi64_OPTIONAL_ARGC));
#endif
#if BIND_apr_strtok_FUNCTION
  mrb_define_class_method(mrb, APR_module, "apr_strtok", mrb_APR_apr_strtok, MRB_ARGS_ARG(apr_strtok_REQUIRED_ARGC, apr_strtok_OPTIONAL_ARGC));
#endif
#if BIND_apr_temp_dir_get_FUNCTION
  mrb_define_class_method(mrb, APR_module, "apr_temp_dir_get", mrb_APR_apr_temp_dir_get, MRB_ARGS_ARG(apr_temp_dir_get_REQUIRED_ARGC, apr_temp_dir_get_OPTIONAL_ARGC));
#endif
#if BIND_apr_terminate_FUNCTION
  mrb_define_class_method(mrb, APR_module, "apr_terminate", mrb_APR_apr_terminate, MRB_ARGS_ARG(apr_terminate_REQUIRED_ARGC, apr_terminate_OPTIONAL_ARGC));
#endif
#if BIND_apr_terminate2_FUNCTION
  mrb_define_class_method(mrb, APR_module, "apr_terminate2", mrb_APR_apr_terminate2, MRB_ARGS_ARG(apr_terminate2_REQUIRED_ARGC, apr_terminate2_OPTIONAL_ARGC));
#endif
#if BIND_apr_thread_create_FUNCTION
  mrb_define_class_method(mrb, APR_module, "apr_thread_create", mrb_APR_apr_thread_create, MRB_ARGS_ARG(apr_thread_create_REQUIRED_ARGC, apr_thread_create_OPTIONAL_ARGC));
#endif
#if BIND_apr_thread_data_get_FUNCTION
  mrb_define_class_method(mrb, APR_module, "apr_thread_data_get", mrb_APR_apr_thread_data_get, MRB_ARGS_ARG(apr_thread_data_get_REQUIRED_ARGC, apr_thread_data_get_OPTIONAL_ARGC));
#endif
#if BIND_apr_thread_data_set_FUNCTION
  mrb_define_class_method(mrb, APR_module, "apr_thread_data_set", mrb_APR_apr_thread_data_set, MRB_ARGS_ARG(apr_thread_data_set_REQUIRED_ARGC, apr_thread_data_set_OPTIONAL_ARGC));
#endif
#if BIND_apr_thread_detach_FUNCTION
  mrb_define_class_method(mrb, APR_module, "apr_thread_detach", mrb_APR_apr_thread_detach, MRB_ARGS_ARG(apr_thread_detach_REQUIRED_ARGC, apr_thread_detach_OPTIONAL_ARGC));
#endif
#if BIND_apr_thread_exit_FUNCTION
  mrb_define_class_method(mrb, APR_module, "apr_thread_exit", mrb_APR_apr_thread_exit, MRB_ARGS_ARG(apr_thread_exit_REQUIRED_ARGC, apr_thread_exit_OPTIONAL_ARGC));
#endif
#if BIND_apr_thread_join_FUNCTION
  mrb_define_class_method(mrb, APR_module, "apr_thread_join", mrb_APR_apr_thread_join, MRB_ARGS_ARG(apr_thread_join_REQUIRED_ARGC, apr_thread_join_OPTIONAL_ARGC));
#endif
#if BIND_apr_thread_once_FUNCTION
  mrb_define_class_method(mrb, APR_module, "apr_thread_once", mrb_APR_apr_thread_once, MRB_ARGS_ARG(apr_thread_once_REQUIRED_ARGC, apr_thread_once_OPTIONAL_ARGC));
#endif
#if BIND_apr_thread_once_init_FUNCTION
  mrb_define_class_method(mrb, APR_module, "apr_thread_once_init", mrb_APR_apr_thread_once_init, MRB_ARGS_ARG(apr_thread_once_init_REQUIRED_ARGC, apr_thread_once_init_OPTIONAL_ARGC));
#endif
#if BIND_apr_thread_yield_FUNCTION
  mrb_define_class_method(mrb, APR_module, "apr_thread_yield", mrb_APR_apr_thread_yield, MRB_ARGS_ARG(apr_thread_yield_REQUIRED_ARGC, apr_thread_yield_OPTIONAL_ARGC));
#endif
#if BIND_apr_threadattr_create_FUNCTION
  mrb_define_class_method(mrb, APR_module, "apr_threadattr_create", mrb_APR_apr_threadattr_create, MRB_ARGS_ARG(apr_threadattr_create_REQUIRED_ARGC, apr_threadattr_create_OPTIONAL_ARGC));
#endif
#if BIND_apr_threadattr_detach_get_FUNCTION
  mrb_define_class_method(mrb, APR_module, "apr_threadattr_detach_get", mrb_APR_apr_threadattr_detach_get, MRB_ARGS_ARG(apr_threadattr_detach_get_REQUIRED_ARGC, apr_threadattr_detach_get_OPTIONAL_ARGC));
#endif
#if BIND_apr_threadattr_detach_set_FUNCTION
  mrb_define_class_method(mrb, APR_module, "apr_threadattr_detach_set", mrb_APR_apr_threadattr_detach_set, MRB_ARGS_ARG(apr_threadattr_detach_set_REQUIRED_ARGC, apr_threadattr_detach_set_OPTIONAL_ARGC));
#endif
#if BIND_apr_threadattr_guardsize_set_FUNCTION
  mrb_define_class_method(mrb, APR_module, "apr_threadattr_guardsize_set", mrb_APR_apr_threadattr_guardsize_set, MRB_ARGS_ARG(apr_threadattr_guardsize_set_REQUIRED_ARGC, apr_threadattr_guardsize_set_OPTIONAL_ARGC));
#endif
#if BIND_apr_threadattr_stacksize_set_FUNCTION
  mrb_define_class_method(mrb, APR_module, "apr_threadattr_stacksize_set", mrb_APR_apr_threadattr_stacksize_set, MRB_ARGS_ARG(apr_threadattr_stacksize_set_REQUIRED_ARGC, apr_threadattr_stacksize_set_OPTIONAL_ARGC));
#endif
#if BIND_apr_threadkey_data_get_FUNCTION
  mrb_define_class_method(mrb, APR_module, "apr_threadkey_data_get", mrb_APR_apr_threadkey_data_get, MRB_ARGS_ARG(apr_threadkey_data_get_REQUIRED_ARGC, apr_threadkey_data_get_OPTIONAL_ARGC));
#endif
#if BIND_apr_threadkey_data_set_FUNCTION
  mrb_define_class_method(mrb, APR_module, "apr_threadkey_data_set", mrb_APR_apr_threadkey_data_set, MRB_ARGS_ARG(apr_threadkey_data_set_REQUIRED_ARGC, apr_threadkey_data_set_OPTIONAL_ARGC));
#endif
#if BIND_apr_threadkey_private_create_FUNCTION
  mrb_define_class_method(mrb, APR_module, "apr_threadkey_private_create", mrb_APR_apr_threadkey_private_create, MRB_ARGS_ARG(apr_threadkey_private_create_REQUIRED_ARGC, apr_threadkey_private_create_OPTIONAL_ARGC));
#endif
#if BIND_apr_threadkey_private_delete_FUNCTION
  mrb_define_class_method(mrb, APR_module, "apr_threadkey_private_delete", mrb_APR_apr_threadkey_private_delete, MRB_ARGS_ARG(apr_threadkey_private_delete_REQUIRED_ARGC, apr_threadkey_private_delete_OPTIONAL_ARGC));
#endif
#if BIND_apr_threadkey_private_get_FUNCTION
  mrb_define_class_method(mrb, APR_module, "apr_threadkey_private_get", mrb_APR_apr_threadkey_private_get, MRB_ARGS_ARG(apr_threadkey_private_get_REQUIRED_ARGC, apr_threadkey_private_get_OPTIONAL_ARGC));
#endif
#if BIND_apr_threadkey_private_set_FUNCTION
  mrb_define_class_method(mrb, APR_module, "apr_threadkey_private_set", mrb_APR_apr_threadkey_private_set, MRB_ARGS_ARG(apr_threadkey_private_set_REQUIRED_ARGC, apr_threadkey_private_set_OPTIONAL_ARGC));
#endif
#if BIND_apr_time_ansi_put_FUNCTION
  mrb_define_class_method(mrb, APR_module, "apr_time_ansi_put", mrb_APR_apr_time_ansi_put, MRB_ARGS_ARG(apr_time_ansi_put_REQUIRED_ARGC, apr_time_ansi_put_OPTIONAL_ARGC));
#endif
#if BIND_apr_time_clock_hires_FUNCTION
  mrb_define_class_method(mrb, APR_module, "apr_time_clock_hires", mrb_APR_apr_time_clock_hires, MRB_ARGS_ARG(apr_time_clock_hires_REQUIRED_ARGC, apr_time_clock_hires_OPTIONAL_ARGC));
#endif
#if BIND_apr_time_exp_get_FUNCTION
  mrb_define_class_method(mrb, APR_module, "apr_time_exp_get", mrb_APR_apr_time_exp_get, MRB_ARGS_ARG(apr_time_exp_get_REQUIRED_ARGC, apr_time_exp_get_OPTIONAL_ARGC));
#endif
#if BIND_apr_time_exp_gmt_FUNCTION
  mrb_define_class_method(mrb, APR_module, "apr_time_exp_gmt", mrb_APR_apr_time_exp_gmt, MRB_ARGS_ARG(apr_time_exp_gmt_REQUIRED_ARGC, apr_time_exp_gmt_OPTIONAL_ARGC));
#endif
#if BIND_apr_time_exp_gmt_get_FUNCTION
  mrb_define_class_method(mrb, APR_module, "apr_time_exp_gmt_get", mrb_APR_apr_time_exp_gmt_get, MRB_ARGS_ARG(apr_time_exp_gmt_get_REQUIRED_ARGC, apr_time_exp_gmt_get_OPTIONAL_ARGC));
#endif
#if BIND_apr_time_exp_lt_FUNCTION
  mrb_define_class_method(mrb, APR_module, "apr_time_exp_lt", mrb_APR_apr_time_exp_lt, MRB_ARGS_ARG(apr_time_exp_lt_REQUIRED_ARGC, apr_time_exp_lt_OPTIONAL_ARGC));
#endif
#if BIND_apr_time_exp_tz_FUNCTION
  mrb_define_class_method(mrb, APR_module, "apr_time_exp_tz", mrb_APR_apr_time_exp_tz, MRB_ARGS_ARG(apr_time_exp_tz_REQUIRED_ARGC, apr_time_exp_tz_OPTIONAL_ARGC));
#endif
#if BIND_apr_time_now_FUNCTION
  mrb_define_class_method(mrb, APR_module, "apr_time_now", mrb_APR_apr_time_now, MRB_ARGS_ARG(apr_time_now_REQUIRED_ARGC, apr_time_now_OPTIONAL_ARGC));
#endif
#if BIND_apr_time_sec_FUNCTION
  mrb_define_class_method(mrb, APR_module, "apr_time_sec", mrb_APR_apr_time_sec, MRB_ARGS_ARG(apr_time_sec_REQUIRED_ARGC, apr_time_sec_OPTIONAL_ARGC));
#endif
#if BIND_apr_tokenize_to_argv_FUNCTION
  mrb_define_class_method(mrb, APR_module, "apr_tokenize_to_argv", mrb_APR_apr_tokenize_to_argv, MRB_ARGS_ARG(apr_tokenize_to_argv_REQUIRED_ARGC, apr_tokenize_to_argv_OPTIONAL_ARGC));
#endif
#if BIND_apr_vsnprintf_FUNCTION
  mrb_define_class_method(mrb, APR_module, "apr_vsnprintf", mrb_APR_apr_vsnprintf, MRB_ARGS_ARG(apr_vsnprintf_REQUIRED_ARGC, apr_vsnprintf_OPTIONAL_ARGC));
#endif
/* MRUBY_BINDING_END */

/* MRUBY_BINDING: post_module_definition */
/* sha: user_defined */

/* MRUBY_BINDING_END */
}

void mrb_mruby_apr_gem_final(mrb_state* mrb){
/* MRUBY_BINDING: module_final */
/* sha: user_defined */

/* MRUBY_BINDING_END */
}

/* MRUBY_BINDING: footer */
/* sha: user_defined */

/* MRUBY_BINDING_END */

#ifdef __cplusplus
}
#endif
