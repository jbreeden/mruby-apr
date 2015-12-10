/*
 * This file is a starting place for porting Ruby API code to C.
 * While the preferred language for CRuby Standard Library implementations
 * is Ruby, some things just need to be fast and efficient. Calling APR
 * through the ruby bindings involves allocating extra objects, and spending
 * extra time copying/moving arguments and results. So, sometimes, we'll
 * fall back to C.
 *
 * An example where this is the case is file globbing. Result sets can
 * easily hit hundreds of thousands if the user simply globs for "**\/*".
 * Saving a few extra objects per file test/directory traverse is significant.
 *
 * Note: This code is not generated. Do not let this file grow to the size
 *       of mruby_APR.c. That was generated with mruby-binings, so it's size
 *       is excusable.
 */


#include "mruby_APR.h"
#if defined(_WIN32)
  #include <process.h> /* _getpid */
  #define getpid _getpid
#else
  #include <unistd.h> /* getpid */
#endif

#ifdef __cplusplus
extern "C" {
#endif

#define RAISE_APR_ERRNO(err) mrb_funcall(mrb, mrb_obj_value(APR_module(mrb)), "raise_apr_errno", 1, mrb_fixnum_value(err));
#define ary_ref(ary, i) mrb_ary_ref(mrb, ary, i)
#define ary_len(ary) mrb_ary_len(mrb, ary)
#define get_class(name) mrb_get_class(mrb, name)
#define funcall(...) mrb_funcall(mrb, __VA_ARGS__)
#define intern_cstr(cstr) mrb_intern_cstr(mrb, cstr)
#define iv_get(obj, name) mrb_iv_get(mrb, obj, mrb_intern_cstr(mrb, name))
#define obj_value(obj) mrb_obj_value(obj)
#define str_new_cstr(cstr) mrb_str_new_cstr(mrb, cstr)
#define string_value_cstr(obj) mrb_string_value_cstr(mrb, obj)
#define obj_is_kind_of(obj, cls) mrb_obj_is_kind_of(mrb, obj, cls)

/*
 * Stack Pool Implementation
 */

static apr_pool_t* _stack_pool = NULL;
static int _stack_pool_enter_count = 0;

apr_pool_t*
stack_pool() {
  return _stack_pool;
}

mrb_value
mruby_APR_stack_pool(mrb_state* mrb, mrb_value self) {
  return mruby_box_apr_pool_t(mrb, _stack_pool);
}

void
stack_pool_enter() {
  _stack_pool_enter_count += _stack_pool_enter_count + 1;
}

mrb_value
mruby_APR_stack_pool_enter(mrb_state* mrb, mrb_value self) {
  stack_pool_enter();
  return mrb_nil_value();
}

void
stack_pool_leave() {
  mrb_int enter_count = _stack_pool_enter_count - 1;
  if (enter_count == 0) {
    apr_pool_clear(_stack_pool);
  }
  _stack_pool_enter_count = enter_count;
}

mrb_value
mruby_APR_stack_pool_leave(mrb_state* mrb, mrb_value self) {
  stack_pool_leave();
  return mrb_nil_value();
}

/*
 * END: Stack Pool Implementation
 */

mrb_value
mruby_Dir_entries(mrb_state* mrb, mrb_value self) {
  stack_pool_enter();
  char* path;
  mrb_get_args(mrb, "z", &path);
  mrb_value results = mrb_ary_new(mrb);

  apr_dir_t* dir;
  apr_status_t err = apr_dir_open(&dir, path, stack_pool());
  if (err != APR_SUCCESS) {
    stack_pool_leave();
    RAISE_APR_ERRNO(err);
    return mrb_nil_value();
  }

  apr_finfo_t finfo;
  int status = apr_dir_read(&finfo, APR_FINFO_NAME, dir);
  while (status == APR_SUCCESS || status == APR_INCOMPLETE) {
    mrb_ary_push(mrb, results, mrb_str_new_cstr(mrb, finfo.name));
    status = apr_dir_read(&finfo, APR_FINFO_NAME, dir);
  }
  stack_pool_leave();
  return results;
}

mrb_value
mruby_FilteTest_is_type(mrb_state* mrb, mrb_value self) {
  char* path;
  mrb_int type;
  mrb_value result = mrb_nil_value();

  stack_pool_enter();
  mrb_get_args(mrb, "zi", &path, &type);

  apr_finfo_t finfo;
  apr_status_t err = apr_stat(&finfo, path, APR_FINFO_TYPE, stack_pool());
  result = (err == APR_SUCCESS && finfo.filetype == type)
    ? mrb_true_value()
    : mrb_false_value();
  stack_pool_leave();
  return result;
}

mrb_value
mruby_Process_pid(mrb_state* mrb, mrb_value self) {
  return mrb_fixnum_value(getpid());
}

struct glob_context {
  mrb_value segments;
  mrb_value block;
  mrb_int segments_length;
  mrb_int match_num;
};

static const char*
explicit_path(char* path) {
  if (strlen(path) == 0) {
    return ".";
  } else {
    return path;
  }
}

char*
path_join(const char* dir, const char* file) {
  char* joined = (char*)calloc(strlen(dir) + strlen(file) + 2, sizeof(char));
  int dir_len = strlen(dir);
  if (dir_len > 0 && dir[dir_len - 1] == '/') {
    strcpy(joined, dir);
    strcat(joined, file);
  } else if (dir_len == 0) {
    strcpy(joined, file);
  } else {
    strcpy(joined, dir);
    strcat(joined, "/");
    strcat(joined, file);
  }
  return joined;
}

static int
fnmatch_file(const char* pattern, const char* file) {
  fprintf(stderr, "enter fnmatch\n");
  if (file[0] == '.' && !(pattern[0] == '.')) {
    return FALSE;
  } else if (strcmp(".", pattern) == 0 && strcmp(".", file) == 0) {
    return TRUE;
  } else if (strcmp("..", pattern) == 0 && strcmp("..", file) == 0) {
    return TRUE;
  } else if (strcmp("*", pattern) == 0) {
    return TRUE;
  } else {
    int status = apr_fnmatch(pattern, file, 0);
    fprintf(stderr, "exit fnmatch\n");
    return status == APR_SUCCESS;
  }
}

static void
glob_recurse(struct glob_context *context, mrb_state* mrb, mrb_value self, char* root, mrb_int segment_num) {
  stack_pool_enter();
  mrb_value segment = ary_ref(context->segments, segment_num);
  mrb_int pattern_count = ary_len(segment);

  apr_dir_t* dir;
  apr_status_t err = apr_dir_open(&dir, explicit_path(root), stack_pool());
  if (err != APR_SUCCESS) {
    stack_pool_leave();
    return;
  }

#define EACH_ENTRY(entry, type) \
  while (1) { \
    apr_finfo_t finfo; \
    int status = apr_dir_read(&finfo, APR_FINFO_NAME | APR_FINFO_TYPE, dir); \
    const char* entry = finfo.name; \
    apr_filetype_e type = finfo.filetype; \
    if (!(status == APR_SUCCESS || status == APR_INCOMPLETE)) { \
      break; \
    }

#define EACH_PATTERN(pattern) \
  for (int i = 0; i < pattern_count - 1; ++i) { \
    mrb_value ruby_pattern = ary_ref(segment, i); \
    const char* pattern = string_value_cstr(&ruby_pattern);

#define END() }

  if (segment_num == context->segments_length - 1) {
    fprintf(stderr, "first\n");
    EACH_ENTRY(entry, type)
      EACH_PATTERN(pattern)
        if (fnmatch_file(pattern, entry)) {
          /* Space for root, separator, file, and null terminator */
          char* joined = path_join(root, entry);
          funcall(context->block, "call", 2, str_new_cstr(joined), mrb_fixnum_value(context->match_num));
          context->match_num += 1;
          free(joined);
          break;
        }
      END()
    END()
  } else if (pattern_count == 1
      && obj_is_kind_of(ary_ref(segment, 0), mrb->symbol_class)
      && mrb_symbol(ary_ref(segment, 0)) == intern_cstr("**")) {
    fprintf(stderr, "second\n");
    EACH_ENTRY(entry, type)
      if (entry[0] != '.' && type == APR_DIR) {
        char* joined = path_join(root, entry);
        glob_recurse(context, mrb, self, joined, segment_num);
        free(joined);
      }
    END()
  } else {
    fprintf(stderr, "third\n");
    EACH_ENTRY(entry, type)
      EACH_PATTERN(pattern)
        char* joined = path_join(root, entry);
        if (type == APR_DIR && fnmatch_file(pattern, entry)) {
          glob_recurse(context, mrb, self, joined, segment_num + 1);
        }
        free(joined);
      END()
    END()
  }

  stack_pool_leave();
}

mrb_value
mruby_Dir_Globber_glob_recurse(mrb_state* mrb, mrb_value self) {
  char* dir;
  mrb_int segment_num;
  mrb_get_args(mrb, "zi", &dir, &segment_num);

  struct glob_context context;
  context.segments = iv_get(self, "@segments");
  context.block = iv_get(self, "@block");
  context.segments_length = ary_len(context.segments);
  context.match_num = 0;
  glob_recurse(&context, mrb, self, dir, 0);
  return mrb_nil_value();
}

void
mruby_APR_init_native_ext(mrb_state* mrb) {
  apr_pool_create(&_stack_pool, NULL);

  mrb_define_class_method(mrb, APR_module(mrb), "stack_pool", mruby_APR_stack_pool, MRB_ARGS_ARG(0, 0));
  mrb_define_class_method(mrb, APR_module(mrb), "stack_pool_enter", mruby_APR_stack_pool_enter, MRB_ARGS_ARG(0, 0));
  mrb_define_class_method(mrb, APR_module(mrb), "stack_pool_leave", mruby_APR_stack_pool_leave, MRB_ARGS_ARG(0, 0));

  struct RClass* Dir_class = mrb_define_class(mrb, "Dir", mrb->object_class);
  mrb_define_class_method(mrb, Dir_class, "entries", mruby_Dir_entries, MRB_ARGS_ARG(1, 0));

  struct RClass* Globber_class = mrb_define_class_under(mrb, Dir_class, "Globber", mrb->object_class);
  mrb_define_method(mrb, Globber_class, "glob_recurse", mruby_Dir_Globber_glob_recurse, MRB_ARGS_ARG(2, 0));

  struct RClass* FileTest_module = mrb_define_module(mrb, "FileTest");
  mrb_define_class_method(mrb, FileTest_module, "is_type?", mruby_FilteTest_is_type, MRB_ARGS_ARG(2, 0));

  struct RClass* Process_module = mrb_define_module(mrb, "Process");
  mrb_define_class_method(mrb, Process_module, "pid", mruby_Process_pid, MRB_ARGS_ARG(0, 0));
}

#ifdef __cplusplus
}
#endif
