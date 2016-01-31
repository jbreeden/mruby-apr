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

/* MRUBY_BINDING: apr_ctime */
/* sha: user_edited */
#if BIND_apr_ctime_FUNCTION
#define apr_ctime_REQUIRED_ARGC 1
#define apr_ctime_OPTIONAL_ARGC 0
/* apr_ctime
 *
 * Parameters:
 * - t: AprTimeT
 * Return Type: apr_status_t
 */
mrb_value
mrb_APR_apr_ctime(mrb_state* mrb, mrb_value self) {
  mrb_value t;

  /* Fetch the args */
  mrb_get_args(mrb, "o", &t);

  /* Type checking */
  if (!mrb_obj_is_kind_of(mrb, t, AprTimeT_class(mrb))) {
    mrb_raise(mrb, AprTimeT_class(mrb), "AprTimeT expected");
    return mrb_nil_value();
  }

  /* unboxing parameters */
  apr_time_t native_t = *mruby_unbox_apr_time_t(t);

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

/* MRUBY_BINDING: apr_file_inherit_unset */
/* sha: user_edited */
#if BIND_apr_file_inherit_unset_FUNCTION
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

/* MRUBY_BINDING: apr_filepath_name_get */
/* sha: user_edited */
#if BIND_apr_filepath_name_get_FUNCTION
#define apr_filepath_name_get_REQUIRED_ARGC 1
#define apr_filepath_name_get_OPTIONAL_ARGC 0
/* apr_filepath_name_get
 *
 * Parameters:
 * - pathname: const char *
 * Return Type: const char *
 */
mrb_value
mrb_APR_apr_filepath_name_get(mrb_state* mrb, mrb_value self) {
  char * native_pathname;

  /* Fetch the args */
  mrb_get_args(mrb, "z", &native_pathname);

  /* Invocation */
  const char * result = apr_filepath_name_get(native_pathname);

  /* Box the return value */
  mrb_value return_value = mrb_str_new_cstr(mrb, result);

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

/* MRUBY_BINDING: apr_os_default_encoding */
/* sha: user_edited */
#if BIND_apr_os_default_encoding_FUNCTION
#define apr_os_default_encoding_REQUIRED_ARGC 1
#define apr_os_default_encoding_OPTIONAL_ARGC 0
/* apr_os_default_encoding
 *
 * Parameters:
 * - pool: apr_pool_t *
 * Return Type: const char *
 */
mrb_value
mrb_APR_apr_os_default_encoding(mrb_state* mrb, mrb_value self) {
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
  const char * result = apr_os_default_encoding(native_pool);

  /* Box the return value */
  mrb_value return_value = mrb_str_new_cstr(mrb, result);

  return return_value;
}
#endif
/* MRUBY_BINDING_END */

/* MRUBY_BINDING: apr_os_locale_encoding */
/* sha: user_edited */
#if BIND_apr_os_locale_encoding_FUNCTION
#define apr_os_locale_encoding_REQUIRED_ARGC 1
#define apr_os_locale_encoding_OPTIONAL_ARGC 0
/* apr_os_locale_encoding
 *
 * Parameters:
 * - pool: apr_pool_t *
 * Return Type: const char *
 */
mrb_value
mrb_APR_apr_os_locale_encoding(mrb_state* mrb, mrb_value self) {
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
  const char * result = apr_os_locale_encoding(native_pool);

  /* Box the return value */
  mrb_value return_value = mrb_str_new_cstr(mrb, result);

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

/* MRUBY_BINDING: apr_pool_create */
/* sha: user_edited */
#if BIND_apr_pool_create_FUNCTION
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

   /*
    * APR likes to give you back the same pool when you "create" a new one.
    * (So far, this is happening consistently on the third creation.)
    * To avoid this, use a new allocator for each pool.
    */
  //  apr_allocator_t* allocator = NULL;
  //  apr_allocator_create(&allocator);

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

/* MRUBY_BINDING: apr_proc_create */
/* sha: user_edited */
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
/* sha: user_edited */
#if BIND_apr_proc_detach_FUNCTION
#define apr_proc_detach_REQUIRED_ARGC 1
#define apr_proc_detach_OPTIONAL_ARGC 0
/* apr_proc_detach
 *
 * Parameters:
 * - daemonize: int
 * Return Type: apr_status_t
 */
mrb_value
mrb_APR_apr_proc_detach(mrb_state* mrb, mrb_value self) {
  mrb_int native_daemonize;

  /* Fetch the args */
  mrb_get_args(mrb, "i", &native_daemonize);

  /* Invocation */
  apr_status_t result = apr_proc_detach(native_daemonize);

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

/* MRUBY_BINDING: apr_proc_wait */
/* sha: user_edited */
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

/*
 * EXTENSION
 * This function is not in libapr, it's just useful for
 * implementing some of Ruby's stdlib.
 * Ex. `spawn` returns only the PID, which we'd like to `wait` on later
 */
mrb_value
mrb_APR_apr_proc_from_pid(mrb_state* mrb, mrb_value self) {
  mrb_int pid;
  mrb_get_args(mrb, "i", &pid);

  apr_proc_t* proc = (apr_proc_t*)malloc(sizeof(apr_proc_t));
  proc->pid = pid;
#if defined(_WIN32) || defined(_WIN64)
   proc->hproc = OpenProcess(MAXIMUM_ALLOWED, false, pid);
#endif
/* MRUBY_BINDING_END */

  /* Wasn't made from an apr pool, so "giftwrap" so the ruby gc free's it */
  return mruby_giftwrap_apr_proc_t(mrb, proc);
}

/* MRUBY_BINDING: apr_procattr_addrspace_set */
/* sha: user_edited */
#if BIND_apr_procattr_addrspace_set_FUNCTION
#define apr_procattr_addrspace_set_REQUIRED_ARGC 2
#define apr_procattr_addrspace_set_OPTIONAL_ARGC 0
/* apr_procattr_addrspace_set
 *
 * Parameters:
 * - attr: apr_procattr_t *
 * - addrspace: int
 * Return Type: apr_status_t
 */
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

  /* Unbox parameters */
  apr_procattr_t * native_attr = (mrb_nil_p(attr) ? NULL : mruby_unbox_apr_procattr_t(attr));

  /* Invocation */
  apr_status_t result = apr_procattr_addrspace_set(native_attr, native_addrspace);

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

/* MRUBY_BINDING: apr_procattr_child_err_set */
/* sha: user_edited */
#if BIND_apr_procattr_child_err_set_FUNCTION
#define apr_procattr_child_err_set_REQUIRED_ARGC 3
#define apr_procattr_child_err_set_OPTIONAL_ARGC 0
/* apr_procattr_child_err_set
 *
 * Parameters:
 * - attr: apr_procattr_t *
 * - child_err: apr_file_t *
 * - parent_err: apr_file_t *
 * Return Type: apr_status_t
 */
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
  if (!mrb_obj_is_kind_of(mrb, child_err, AprFileT_class(mrb)) && !mrb_nil_p(child_err)) {
    mrb_raise(mrb, E_TYPE_ERROR, "AprFileT expected");
    return mrb_nil_value();
  }
  if (!mrb_obj_is_kind_of(mrb, parent_err, AprFileT_class(mrb)) && !mrb_nil_p(parent_err)) {
    mrb_raise(mrb, E_TYPE_ERROR, "AprFileT expected");
    return mrb_nil_value();
  }

  /* Unbox parameters */
  apr_procattr_t * native_attr = (mrb_nil_p(attr) ? NULL : mruby_unbox_apr_procattr_t(attr));
  apr_file_t * native_child_err = (mrb_nil_p(child_err) ? NULL : mruby_unbox_apr_file_t(child_err));
  apr_file_t * native_parent_err = (mrb_nil_p(parent_err) ? NULL : mruby_unbox_apr_file_t(parent_err));

  /* Invocation */
  apr_status_t result = apr_procattr_child_err_set(native_attr, native_child_err, native_parent_err);

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

/* MRUBY_BINDING: apr_procattr_child_in_set */
/* sha: user_edited */
#if BIND_apr_procattr_child_in_set_FUNCTION
#define apr_procattr_child_in_set_REQUIRED_ARGC 3
#define apr_procattr_child_in_set_OPTIONAL_ARGC 0
/* apr_procattr_child_in_set
 *
 * Parameters:
 * - attr: apr_procattr_t *
 * - child_in: apr_file_t *
 * - parent_in: apr_file_t *
 * Return Type: apr_status_t
 */
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
  if (!mrb_obj_is_kind_of(mrb, child_in, AprFileT_class(mrb)) && !mrb_nil_p(child_in)) {
    mrb_raise(mrb, E_TYPE_ERROR, "AprFileT expected");
    return mrb_nil_value();
  }
  if (!mrb_obj_is_kind_of(mrb, parent_in, AprFileT_class(mrb)) && !mrb_nil_p(parent_in)) {
    mrb_raise(mrb, E_TYPE_ERROR, "AprFileT expected");
    return mrb_nil_value();
  }

  /* Unbox parameters */
  apr_procattr_t * native_attr = (mrb_nil_p(attr) ? NULL : mruby_unbox_apr_procattr_t(attr));
  apr_file_t * native_child_in = (mrb_nil_p(child_in) ? NULL : mruby_unbox_apr_file_t(child_in));
  apr_file_t * native_parent_in = (mrb_nil_p(parent_in) ? NULL : mruby_unbox_apr_file_t(parent_in));

  /* Invocation */
  apr_status_t result = apr_procattr_child_in_set(native_attr, native_child_in, native_parent_in);

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

/* MRUBY_BINDING: apr_procattr_child_out_set */
/* sha: user_edited */
#if BIND_apr_procattr_child_out_set_FUNCTION
#define apr_procattr_child_out_set_REQUIRED_ARGC 3
#define apr_procattr_child_out_set_OPTIONAL_ARGC 0
/* apr_procattr_child_out_set
 *
 * Parameters:
 * - attr: apr_procattr_t *
 * - child_out: apr_file_t *
 * - parent_out: apr_file_t *
 * Return Type: apr_status_t
 */
mrb_value
mrb_APR_apr_procattr_child_out_set(mrb_state* mrb, mrb_value self) {
  mrb_value attr;
  mrb_value child_out;
  mrb_value parent_out;

  /* Fetch the args */
  mrb_get_args(mrb, "ooo", &attr, &child_out, &parent_out);

  /* Type checking */
  if (!mrb_obj_is_kind_of(mrb, attr, AprProcattrT_class(mrb))) {
    mrb_raise(mrb, E_TYPE_ERROR, "AprProcattrT expected");
    return mrb_nil_value();
  }
  if (!mrb_obj_is_kind_of(mrb, child_out, AprFileT_class(mrb)) && !mrb_nil_p(child_out)) {
    mrb_raise(mrb, E_TYPE_ERROR, "AprFileT expected");
    return mrb_nil_value();
  }
  if (!mrb_obj_is_kind_of(mrb, parent_out, AprFileT_class(mrb)) && !mrb_nil_p(parent_out)) {
    mrb_raise(mrb, E_TYPE_ERROR, "AprFileT expected");
    return mrb_nil_value();
  }

  /* Unbox parameters */
  apr_procattr_t * native_attr = (mrb_nil_p(attr) ? NULL : mruby_unbox_apr_procattr_t(attr));
  apr_file_t * native_child_out = (mrb_nil_p(child_out) ? NULL : mruby_unbox_apr_file_t(child_out));
  apr_file_t * native_parent_out = (mrb_nil_p(parent_out) ? NULL : mruby_unbox_apr_file_t(parent_out));

  /* Invocation */
  apr_status_t result = apr_procattr_child_out_set(native_attr, native_child_out, native_parent_out);

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

/* MRUBY_BINDING: apr_procattr_cmdtype_set */
/* sha: user_edited */
#if BIND_apr_procattr_cmdtype_set_FUNCTION
#define apr_procattr_cmdtype_set_REQUIRED_ARGC 2
#define apr_procattr_cmdtype_set_OPTIONAL_ARGC 0
/* apr_procattr_cmdtype_set
 *
 * Parameters:
 * - attr: apr_procattr_t *
 * - cmd: apr_cmdtype_e
 * Return Type: apr_status_t
 */
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

  /* Unbox parameters */
  apr_procattr_t * native_attr = (mrb_nil_p(attr) ? NULL : mruby_unbox_apr_procattr_t(attr));

  /* Invocation */
  apr_status_t result = apr_procattr_cmdtype_set(native_attr, native_cmd);

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

/* MRUBY_BINDING: apr_procattr_create */
/* sha: user_edited */
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
/* sha: user_edited */
#if BIND_apr_procattr_detach_set_FUNCTION
#define apr_procattr_detach_set_REQUIRED_ARGC 2
#define apr_procattr_detach_set_OPTIONAL_ARGC 0
/* apr_procattr_detach_set
 *
 * Parameters:
 * - attr: apr_procattr_t *
 * - detach: int
 * Return Type: apr_status_t
 */
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

  /* Unbox parameters */
  apr_procattr_t * native_attr = (mrb_nil_p(attr) ? NULL : mruby_unbox_apr_procattr_t(attr));

  /* Invocation */
  apr_status_t result = apr_procattr_detach_set(native_attr, native_detach);

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

/* MRUBY_BINDING: apr_procattr_dir_set */
/* sha: user_edited */
#if BIND_apr_procattr_dir_set_FUNCTION
#define apr_procattr_dir_set_REQUIRED_ARGC 2
#define apr_procattr_dir_set_OPTIONAL_ARGC 0
/* apr_procattr_dir_set
 *
 * Parameters:
 * - attr: apr_procattr_t *
 * - dir: const char *
 * Return Type: apr_status_t
 */
mrb_value
mrb_APR_apr_procattr_dir_set(mrb_state* mrb, mrb_value self) {
  mrb_value attr;
  char * native_dir;

  /* Fetch the args */
  mrb_get_args(mrb, "oz", &attr, &native_dir);

  /* Type checking */
  if (!mrb_obj_is_kind_of(mrb, attr, AprProcattrT_class(mrb))) {
    mrb_raise(mrb, E_TYPE_ERROR, "AprProcattrT expected");
    return mrb_nil_value();
  }

  /* Unbox parameters */
  apr_procattr_t * native_attr = (mrb_nil_p(attr) ? NULL : mruby_unbox_apr_procattr_t(attr));

  /* Invocation */
  apr_status_t result = apr_procattr_dir_set(native_attr, native_dir);

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

/* MRUBY_BINDING: apr_procattr_error_check_set */
/* sha: user_edited */
#if BIND_apr_procattr_error_check_set_FUNCTION
#define apr_procattr_error_check_set_REQUIRED_ARGC 2
#define apr_procattr_error_check_set_OPTIONAL_ARGC 0
/* apr_procattr_error_check_set
 *
 * Parameters:
 * - attr: apr_procattr_t *
 * - chk: int
 * Return Type: apr_status_t
 */
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

  /* Unbox parameters */
  apr_procattr_t * native_attr = (mrb_nil_p(attr) ? NULL : mruby_unbox_apr_procattr_t(attr));

  /* Invocation */
  apr_status_t result = apr_procattr_error_check_set(native_attr, native_chk);

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

/* MRUBY_BINDING: apr_procattr_group_set */
/* sha: user_edited */
#if BIND_apr_procattr_group_set_FUNCTION
#define apr_procattr_group_set_REQUIRED_ARGC 2
#define apr_procattr_group_set_OPTIONAL_ARGC 0
/* apr_procattr_group_set
 *
 * Parameters:
 * - attr: apr_procattr_t *
 * - groupname: const char *
 * Return Type: apr_status_t
 */
mrb_value
mrb_APR_apr_procattr_group_set(mrb_state* mrb, mrb_value self) {
  mrb_value attr;
  char * native_groupname;

  /* Fetch the args */
  mrb_get_args(mrb, "oz", &attr, &native_groupname);

  /* Type checking */
  if (!mrb_obj_is_kind_of(mrb, attr, AprProcattrT_class(mrb))) {
    mrb_raise(mrb, E_TYPE_ERROR, "AprProcattrT expected");
    return mrb_nil_value();
  }

  /* Unbox parameters */
  apr_procattr_t * native_attr = (mrb_nil_p(attr) ? NULL : mruby_unbox_apr_procattr_t(attr));

  /* Invocation */
  apr_status_t result = apr_procattr_group_set(native_attr, native_groupname);

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

/* MRUBY_BINDING: apr_procattr_io_set */
/* sha: user_edited */
#if BIND_apr_procattr_io_set_FUNCTION
#define apr_procattr_io_set_REQUIRED_ARGC 4
#define apr_procattr_io_set_OPTIONAL_ARGC 0
/* apr_procattr_io_set
 *
 * Parameters:
 * - attr: apr_procattr_t *
 * - in: int
 * - out: int
 * - err: int
 * Return Type: apr_status_t
 */
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

  /* Unbox parameters */
  apr_procattr_t * native_attr = (mrb_nil_p(attr) ? NULL : mruby_unbox_apr_procattr_t(attr));

  /* Invocation */
  apr_status_t result = apr_procattr_io_set(native_attr, native_in, native_out, native_err);

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

/* MRUBY_BINDING: apr_procattr_user_set */
/* sha: user_edited */
#if BIND_apr_procattr_user_set_FUNCTION
#define apr_procattr_user_set_REQUIRED_ARGC 3
#define apr_procattr_user_set_OPTIONAL_ARGC 0
/* apr_procattr_user_set
 *
 * Parameters:
 * - attr: apr_procattr_t *
 * - username: const char *
 * - password: const char *
 * Return Type: apr_status_t
 */
mrb_value
mrb_APR_apr_procattr_user_set(mrb_state* mrb, mrb_value self) {
  mrb_value attr;
  char * native_username;
  char * native_password;

  /* Fetch the args */
  mrb_get_args(mrb, "ozz", &attr, &native_username, &native_password);

  /* Type checking */
  if (!mrb_obj_is_kind_of(mrb, attr, AprProcattrT_class(mrb))) {
    mrb_raise(mrb, E_TYPE_ERROR, "AprProcattrT expected");
    return mrb_nil_value();
  }

  /* Unbox parameters */
  apr_procattr_t * native_attr = (mrb_nil_p(attr) ? NULL : mruby_unbox_apr_procattr_t(attr));

  /* Invocation */
  apr_status_t result = apr_procattr_user_set(native_attr, native_username, native_password);

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

/* MRUBY_BINDING: apr_sockaddr_is_wildcard */
/* sha: user_edited */
#if BIND_apr_sockaddr_is_wildcard_FUNCTION
#define apr_sockaddr_is_wildcard_REQUIRED_ARGC 1
#define apr_sockaddr_is_wildcard_OPTIONAL_ARGC 0
/* apr_sockaddr_is_wildcard
 *
 * Parameters:
 * - addr: const apr_sockaddr_t *
 * Return Type: Fixnum (non-zero if the address is initialize and is the wildcard)
 */
mrb_value
mrb_APR_apr_sockaddr_is_wildcard(mrb_state* mrb, mrb_value self) {
  mrb_value addr;

  /* Fetch the args */
  mrb_get_args(mrb, "o", &addr);

  /* Type checking */
  if (!mrb_obj_is_kind_of(mrb, addr, AprSockaddrT_class(mrb))) {
    mrb_raise(mrb, E_TYPE_ERROR, "AprSockaddrT expected");
    return mrb_nil_value();
  }

  /* Unbox parameters */
  const apr_sockaddr_t * native_addr = (mrb_nil_p(addr) ? NULL : mruby_unbox_apr_sockaddr_t(addr));

  /* Invocation */
  int result = apr_sockaddr_is_wildcard(native_addr);

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

/* MRUBY_BINDING: apr_to_os_error */
/* sha: user_edited */
#if BIND_apr_to_os_error_FUNCTION
#define apr_to_os_error_REQUIRED_ARGC 1
#define apr_to_os_error_OPTIONAL_ARGC 0
mrb_value
mrb_APR_apr_to_os_error(mrb_state *mrb, mrb_value self) {
  mrb_int apr_errno;
  mrb_get_args(mrb, "i", &apr_errno);
  int os_errno = APR_TO_OS_ERROR(apr_errno);
  return mrb_fixnum_value(os_errno);
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

/* MRUBY_BINDING: apr_time_now */
/* sha: user_edited */
#if BIND_apr_time_now_FUNCTION
#define apr_time_now_REQUIRED_ARGC 0
#define apr_time_now_OPTIONAL_ARGC 0
/* apr_time_now
 *
 * Parameters: None
 * Return Type: apr_time_t
 */
mrb_value
mrb_APR_apr_time_now(mrb_state* mrb, mrb_value self) {
  /* Invocation */
  apr_time_t result = apr_time_now();

  /* Box the return value */
  apr_time_t* new_time = (apr_time_t*)malloc(sizeof(apr_time_t));
  memcpy(new_time, &result, sizeof(apr_time_t));
  mrb_value return_value = mruby_giftwrap_apr_time_t(mrb, new_time);

  return return_value;
}
#endif
/* MRUBY_BINDING_END */

/* MRUBY_BINDING: apr_time_sec */
/* sha: user_edited */
#if BIND_apr_time_sec_FUNCTION
#define apr_time_sec_REQUIRED_ARGC 1
#define apr_time_sec_OPTIONAL_ARGC 0
/* apr_time_now
 *
 * Parameters: AprTimeT
 * Return Type: Float
 */
mrb_value
mrb_APR_apr_time_sec(mrb_state* mrb, mrb_value self) {
  mrb_value time;
  mrb_get_args(mrb, "o", &time);

  /* Type checking */
  if (!mrb_obj_is_kind_of(mrb, time, AprTimeT_class(mrb))) {
    mrb_raise(mrb, E_TYPE_ERROR, "AprTimeT expected");
  }

  apr_time_t native_time = *mruby_unbox_apr_time_t(time);

  /* Invocation */
  apr_time_t result = apr_time_sec(native_time);

  /* Box the return value */
  return mrb_float_value(mrb, result);
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

void mrb_mruby_apr_gem_init(mrb_state* mrb) {
/* MRUBY_BINDING: pre_module_definition */
/* sha: user_defined */
  apr_initialize();
/* MRUBY_BINDING_END */
  
  struct RClass* APR_module = mrb_define_module(mrb, "APR");
  mruby_APR_define_macro_constants(mrb);
  
  
/* MRUBY_BINDING: pre_class_initializations */
/* sha: user_defined */
  mruby_APR_init_native_ext(mrb);

  mrb_define_class_under(mrb, APR_module, "AprTimeT", mrb->object_class);
/* MRUBY_BINDING_END */
  
  /*
   * Initialize class bindings
   */
#if BIND_AprAllocatorT_TYPE
  mrb_APR_AprAllocatorT_init(mrb);
#endif
#if BIND_AprArrayHeaderT_TYPE
  mrb_APR_AprArrayHeaderT_init(mrb);
#endif
#if BIND_AprCryptoHashT_TYPE
  mrb_APR_AprCryptoHashT_init(mrb);
#endif
#if BIND_AprDirT_TYPE
  mrb_APR_AprDirT_init(mrb);
#endif
#if BIND_AprDsoHandleT_TYPE
  mrb_APR_AprDsoHandleT_init(mrb);
#endif
#if BIND_AprFileT_TYPE
  mrb_APR_AprFileT_init(mrb);
#endif
#if BIND_AprFinfoT_TYPE
  mrb_APR_AprFinfoT_init(mrb);
#endif
#if BIND_AprGetoptOptionT_TYPE
  mrb_APR_AprGetoptOptionT_init(mrb);
#endif
#if BIND_AprGetoptT_TYPE
  mrb_APR_AprGetoptT_init(mrb);
#endif
#if BIND_AprHashIndexT_TYPE
  mrb_APR_AprHashIndexT_init(mrb);
#endif
#if BIND_AprHashT_TYPE
  mrb_APR_AprHashT_init(mrb);
#endif
#if BIND_AprHdtrT_TYPE
  mrb_APR_AprHdtrT_init(mrb);
#endif
#if BIND_AprIpsubnetT_TYPE
  mrb_APR_AprIpsubnetT_init(mrb);
#endif
#if BIND_AprMemnodeT_TYPE
  mrb_APR_AprMemnodeT_init(mrb);
#endif
#if BIND_AprMmapT_TYPE
  mrb_APR_AprMmapT_init(mrb);
#endif
#if BIND_AprOsSockInfoT_TYPE
  mrb_APR_AprOsSockInfoT_init(mrb);
#endif
#if BIND_AprOtherChildRecT_TYPE
  mrb_APR_AprOtherChildRecT_init(mrb);
#endif
#if BIND_AprPollcbT_TYPE
  mrb_APR_AprPollcbT_init(mrb);
#endif
#if BIND_AprPollfdT_TYPE
  mrb_APR_AprPollfdT_init(mrb);
#endif
#if BIND_AprPollsetT_TYPE
  mrb_APR_AprPollsetT_init(mrb);
#endif
#if BIND_AprPoolT_TYPE
  mrb_APR_AprPoolT_init(mrb);
#endif
#if BIND_AprProcMutexT_TYPE
  mrb_APR_AprProcMutexT_init(mrb);
#endif
#if BIND_AprProcT_TYPE
  mrb_APR_AprProcT_init(mrb);
#endif
#if BIND_AprProcattrT_TYPE
  mrb_APR_AprProcattrT_init(mrb);
#endif
#if BIND_AprRandomT_TYPE
  mrb_APR_AprRandomT_init(mrb);
#endif
#if BIND_AprShmT_TYPE
  mrb_APR_AprShmT_init(mrb);
#endif
#if BIND_AprSkiplist_TYPE
  mrb_APR_AprSkiplist_init(mrb);
#endif
#if BIND_AprSkiplistnode_TYPE
  mrb_APR_AprSkiplistnode_init(mrb);
#endif
#if BIND_AprSockaddrT_TYPE
  mrb_APR_AprSockaddrT_init(mrb);
#endif
#if BIND_AprSocketT_TYPE
  mrb_APR_AprSocketT_init(mrb);
#endif
#if BIND_AprTableEntryT_TYPE
  mrb_APR_AprTableEntryT_init(mrb);
#endif
#if BIND_AprTableT_TYPE
  mrb_APR_AprTableT_init(mrb);
#endif
#if BIND_AprThreadCondT_TYPE
  mrb_APR_AprThreadCondT_init(mrb);
#endif
#if BIND_AprThreadMutexT_TYPE
  mrb_APR_AprThreadMutexT_init(mrb);
#endif
#if BIND_AprThreadOnceT_TYPE
  mrb_APR_AprThreadOnceT_init(mrb);
#endif
#if BIND_AprThreadRwlockT_TYPE
  mrb_APR_AprThreadRwlockT_init(mrb);
#endif
#if BIND_AprThreadT_TYPE
  mrb_APR_AprThreadT_init(mrb);
#endif
#if BIND_AprThreadattrT_TYPE
  mrb_APR_AprThreadattrT_init(mrb);
#endif
#if BIND_AprThreadkeyT_TYPE
  mrb_APR_AprThreadkeyT_init(mrb);
#endif
#if BIND_AprTimeExpT_TYPE
  mrb_APR_AprTimeExpT_init(mrb);
#endif
#if BIND_AprVersionT_TYPE
  mrb_APR_AprVersionT_init(mrb);
#endif
#if BIND_AprVformatterBuffT_TYPE
  mrb_APR_AprVformatterBuffT_init(mrb);
#endif

/* MRUBY_BINDING: pre_global_function_initializations */
/* sha: user_defined */
  mrb_define_class_method(mrb, APR_module, "apr_dir_chdir", mrb_APR_dir_chdir, MRB_ARGS_ARG(chdir_REQUIRED_ARGC, chdir_OPTIONAL_ARGC));
  mrb_define_class_method(mrb, APR_module, "apr_dir_getcwd", mrb_APR_dir_getcwd, MRB_ARGS_ARG(getcwd_REQUIRED_ARGC, getcwd_OPTIONAL_ARGC));
  mrb_define_class_method(mrb, APR_module, "apr_proc_from_pid", mrb_APR_apr_proc_from_pid, MRB_ARGS_ARG(1, 0));
  
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

  /*
   * Global Functions
   */
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
#if BIND_apr_file_buffer_size_get_FUNCTION
  mrb_define_class_method(mrb, APR_module, "apr_file_buffer_size_get", mrb_APR_apr_file_buffer_size_get, MRB_ARGS_ARG(apr_file_buffer_size_get_REQUIRED_ARGC, apr_file_buffer_size_get_OPTIONAL_ARGC));
#endif
#if BIND_apr_file_close_FUNCTION
  mrb_define_class_method(mrb, APR_module, "apr_file_close", mrb_APR_apr_file_close, MRB_ARGS_ARG(apr_file_close_REQUIRED_ARGC, apr_file_close_OPTIONAL_ARGC));
#endif
#if BIND_apr_file_copy_FUNCTION
  mrb_define_class_method(mrb, APR_module, "apr_file_copy", mrb_APR_apr_file_copy, MRB_ARGS_ARG(apr_file_copy_REQUIRED_ARGC, apr_file_copy_OPTIONAL_ARGC));
#endif
#if BIND_apr_file_datasync_FUNCTION
  mrb_define_class_method(mrb, APR_module, "apr_file_datasync", mrb_APR_apr_file_datasync, MRB_ARGS_ARG(apr_file_datasync_REQUIRED_ARGC, apr_file_datasync_OPTIONAL_ARGC));
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
#if BIND_apr_file_inherit_unset_FUNCTION
  mrb_define_class_method(mrb, APR_module, "apr_file_inherit_unset", mrb_APR_apr_file_inherit_unset, MRB_ARGS_ARG(apr_file_inherit_unset_REQUIRED_ARGC, apr_file_inherit_unset_OPTIONAL_ARGC));
#endif
#if BIND_apr_file_link_FUNCTION
  mrb_define_class_method(mrb, APR_module, "apr_file_link", mrb_APR_apr_file_link, MRB_ARGS_ARG(apr_file_link_REQUIRED_ARGC, apr_file_link_OPTIONAL_ARGC));
#endif
#if BIND_apr_file_lock_FUNCTION
  mrb_define_class_method(mrb, APR_module, "apr_file_lock", mrb_APR_apr_file_lock, MRB_ARGS_ARG(apr_file_lock_REQUIRED_ARGC, apr_file_lock_OPTIONAL_ARGC));
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
#if BIND_apr_file_puts_FUNCTION
  mrb_define_class_method(mrb, APR_module, "apr_file_puts", mrb_APR_apr_file_puts, MRB_ARGS_ARG(apr_file_puts_REQUIRED_ARGC, apr_file_puts_OPTIONAL_ARGC));
#endif
#if BIND_apr_file_read_FUNCTION
  mrb_define_class_method(mrb, APR_module, "apr_file_read", mrb_APR_apr_file_read, MRB_ARGS_ARG(apr_file_read_REQUIRED_ARGC, apr_file_read_OPTIONAL_ARGC));
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
#if BIND_apr_filepath_name_get_FUNCTION
  mrb_define_class_method(mrb, APR_module, "apr_filepath_name_get", mrb_APR_apr_filepath_name_get, MRB_ARGS_ARG(apr_filepath_name_get_REQUIRED_ARGC, apr_filepath_name_get_OPTIONAL_ARGC));
#endif
#if BIND_apr_fnmatch_FUNCTION
  mrb_define_class_method(mrb, APR_module, "apr_fnmatch", mrb_APR_apr_fnmatch, MRB_ARGS_ARG(apr_fnmatch_REQUIRED_ARGC, apr_fnmatch_OPTIONAL_ARGC));
#endif
#if BIND_apr_fnmatch_test_FUNCTION
  mrb_define_class_method(mrb, APR_module, "apr_fnmatch_test", mrb_APR_apr_fnmatch_test, MRB_ARGS_ARG(apr_fnmatch_test_REQUIRED_ARGC, apr_fnmatch_test_OPTIONAL_ARGC));
#endif
#if BIND_apr_gethostname_FUNCTION
  mrb_define_class_method(mrb, APR_module, "apr_gethostname", mrb_APR_apr_gethostname, MRB_ARGS_ARG(apr_gethostname_REQUIRED_ARGC, apr_gethostname_OPTIONAL_ARGC));
#endif
#if BIND_apr_getnameinfo_FUNCTION
  mrb_define_class_method(mrb, APR_module, "apr_getnameinfo", mrb_APR_apr_getnameinfo, MRB_ARGS_ARG(apr_getnameinfo_REQUIRED_ARGC, apr_getnameinfo_OPTIONAL_ARGC));
#endif
#if BIND_apr_initialize_FUNCTION
  mrb_define_class_method(mrb, APR_module, "apr_initialize", mrb_APR_apr_initialize, MRB_ARGS_ARG(apr_initialize_REQUIRED_ARGC, apr_initialize_OPTIONAL_ARGC));
#endif
#if BIND_apr_os_default_encoding_FUNCTION
  mrb_define_class_method(mrb, APR_module, "apr_os_default_encoding", mrb_APR_apr_os_default_encoding, MRB_ARGS_ARG(apr_os_default_encoding_REQUIRED_ARGC, apr_os_default_encoding_OPTIONAL_ARGC));
#endif
#if BIND_apr_os_locale_encoding_FUNCTION
  mrb_define_class_method(mrb, APR_module, "apr_os_locale_encoding", mrb_APR_apr_os_locale_encoding, MRB_ARGS_ARG(apr_os_locale_encoding_REQUIRED_ARGC, apr_os_locale_encoding_OPTIONAL_ARGC));
#endif
#if BIND_apr_pool_clear_FUNCTION
  mrb_define_class_method(mrb, APR_module, "apr_pool_clear", mrb_APR_apr_pool_clear, MRB_ARGS_ARG(apr_pool_clear_REQUIRED_ARGC, apr_pool_clear_OPTIONAL_ARGC));
#endif
#if BIND_apr_pool_create_FUNCTION
  mrb_define_class_method(mrb, APR_module, "apr_pool_create", mrb_APR_apr_pool_create, MRB_ARGS_ARG(apr_pool_create_REQUIRED_ARGC, apr_pool_create_OPTIONAL_ARGC));
#endif
#if BIND_apr_pool_destroy_FUNCTION
  mrb_define_class_method(mrb, APR_module, "apr_pool_destroy", mrb_APR_apr_pool_destroy, MRB_ARGS_ARG(apr_pool_destroy_REQUIRED_ARGC, apr_pool_destroy_OPTIONAL_ARGC));
#endif
#if BIND_apr_proc_create_FUNCTION
  mrb_define_class_method(mrb, APR_module, "apr_proc_create", mrb_APR_apr_proc_create, MRB_ARGS_ARG(apr_proc_create_REQUIRED_ARGC, apr_proc_create_OPTIONAL_ARGC));
#endif
#if BIND_apr_proc_detach_FUNCTION
  mrb_define_class_method(mrb, APR_module, "apr_proc_detach", mrb_APR_apr_proc_detach, MRB_ARGS_ARG(apr_proc_detach_REQUIRED_ARGC, apr_proc_detach_OPTIONAL_ARGC));
#endif
#if BIND_apr_proc_wait_FUNCTION
  mrb_define_class_method(mrb, APR_module, "apr_proc_wait", mrb_APR_apr_proc_wait, MRB_ARGS_ARG(apr_proc_wait_REQUIRED_ARGC, apr_proc_wait_OPTIONAL_ARGC));
#endif
#if BIND_apr_procattr_addrspace_set_FUNCTION
  mrb_define_class_method(mrb, APR_module, "apr_procattr_addrspace_set", mrb_APR_apr_procattr_addrspace_set, MRB_ARGS_ARG(apr_procattr_addrspace_set_REQUIRED_ARGC, apr_procattr_addrspace_set_OPTIONAL_ARGC));
#endif
#if BIND_apr_procattr_child_err_set_FUNCTION
  mrb_define_class_method(mrb, APR_module, "apr_procattr_child_err_set", mrb_APR_apr_procattr_child_err_set, MRB_ARGS_ARG(apr_procattr_child_err_set_REQUIRED_ARGC, apr_procattr_child_err_set_OPTIONAL_ARGC));
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
#if BIND_apr_procattr_user_set_FUNCTION
  mrb_define_class_method(mrb, APR_module, "apr_procattr_user_set", mrb_APR_apr_procattr_user_set, MRB_ARGS_ARG(apr_procattr_user_set_REQUIRED_ARGC, apr_procattr_user_set_OPTIONAL_ARGC));
#endif
#if BIND_apr_sleep_FUNCTION
  mrb_define_class_method(mrb, APR_module, "apr_sleep", mrb_APR_apr_sleep, MRB_ARGS_ARG(apr_sleep_REQUIRED_ARGC, apr_sleep_OPTIONAL_ARGC));
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
#if BIND_apr_sockaddr_is_wildcard_FUNCTION
  mrb_define_class_method(mrb, APR_module, "apr_sockaddr_is_wildcard", mrb_APR_apr_sockaddr_is_wildcard, MRB_ARGS_ARG(apr_sockaddr_is_wildcard_REQUIRED_ARGC, apr_sockaddr_is_wildcard_OPTIONAL_ARGC));
#endif
#if BIND_apr_socket_accept_FUNCTION
  mrb_define_class_method(mrb, APR_module, "apr_socket_accept", mrb_APR_apr_socket_accept, MRB_ARGS_ARG(apr_socket_accept_REQUIRED_ARGC, apr_socket_accept_OPTIONAL_ARGC));
#endif
#if BIND_apr_socket_addr_get_FUNCTION
  mrb_define_class_method(mrb, APR_module, "apr_socket_addr_get", mrb_APR_apr_socket_addr_get, MRB_ARGS_ARG(apr_socket_addr_get_REQUIRED_ARGC, apr_socket_addr_get_OPTIONAL_ARGC));
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
#if BIND_apr_socket_sendto_FUNCTION
  mrb_define_class_method(mrb, APR_module, "apr_socket_sendto", mrb_APR_apr_socket_sendto, MRB_ARGS_ARG(apr_socket_sendto_REQUIRED_ARGC, apr_socket_sendto_OPTIONAL_ARGC));
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
#if BIND_apr_to_os_error_FUNCTION
  mrb_define_class_method(mrb, APR_module, "apr_to_os_error", mrb_APR_apr_to_os_error, MRB_ARGS_ARG(apr_to_os_error_REQUIRED_ARGC, apr_to_os_error_OPTIONAL_ARGC));
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
#if BIND_apr_time_now_FUNCTION
  mrb_define_class_method(mrb, APR_module, "apr_time_now", mrb_APR_apr_time_now, MRB_ARGS_ARG(apr_time_now_REQUIRED_ARGC, apr_time_now_OPTIONAL_ARGC));
#endif
#if BIND_apr_time_sec_FUNCTION
  mrb_define_class_method(mrb, APR_module, "apr_time_sec", mrb_APR_apr_time_sec, MRB_ARGS_ARG(apr_time_sec_REQUIRED_ARGC, apr_time_sec_OPTIONAL_ARGC));
#endif
#if BIND_apr_tokenize_to_argv_FUNCTION
  mrb_define_class_method(mrb, APR_module, "apr_tokenize_to_argv", mrb_APR_apr_tokenize_to_argv, MRB_ARGS_ARG(apr_tokenize_to_argv_REQUIRED_ARGC, apr_tokenize_to_argv_OPTIONAL_ARGC));
#endif
}

void mrb_mruby_apr_gem_final(mrb_state* mrb){

}

#ifdef __cplusplus
}
#endif
