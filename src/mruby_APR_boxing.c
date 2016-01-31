/*
 * Boxing Code (Generated)
 * =======================
 *
 * The code generator learns the data types declared in the C/C++ source files
 * it is run against, and generates this boxing, unboxing, and GC code.
 * 
 * Terms
 * ------
 *
 * ### Boxing
 * In general refers to wrapping a native object in an mrb_value.
 * 
 * ### Gift Wrapping
 * A specific type of boxing, indicating that the object belongs
 * to Ruby and should be free'd when the mrb_value is GC'ed.
 * 
 * ### Unboxing
 * Retrieving the wrapped native object from an mrb_value.
 *
 * Customizing
 * -----------
 * 
 * By default, all data types are assumed to be destructable by the `free`
 * function. To use a custom destructor for your type, tell CTypes with
 * `CTypes.set_destructor`.
 *
 * Example
 * ```
 * // I have `struct GError` objects from glib,
 * // which should be freed with `g_error_free`
 * CTypes.set_destructor('struct GError', 'g_error_free')
 * ```
 */
#include "mruby_APR.h"

/* MRUBY_BINDING: header */
/* sha: user_defined */

/* MRUBY_BINDING_END */

/* MRUBY_BINDING: AprDirT_boxing */
/* sha: abb7c189f4ef97a73e12b163ac081bba0976c799b7aed90d35357c9eab446bfc */
#if BIND_AprDirT_TYPE
/*
 * Boxing implementation for apr_dir_t
 */

static void free_apr_dir_t(mrb_state* mrb, void* ptr) {
  mruby_to_native_ref* box = (mruby_to_native_ref*)ptr;
  if (box->belongs_to_ruby) {
    if (box->obj != NULL) {
      free(box->obj);
      box->obj = NULL;
    }
  }
  free(box);
}

static const mrb_data_type apr_dir_t_data_type = {
   "apr_dir_t", free_apr_dir_t
};

mrb_value
mruby_box_apr_dir_t(mrb_state* mrb, apr_dir_t *unboxed) {
  mruby_to_native_ref* box = (mruby_to_native_ref*)malloc(sizeof(mruby_to_native_ref));
  box->belongs_to_ruby = FALSE;
  box->obj = unboxed;
  return mrb_obj_value(Data_Wrap_Struct(mrb, AprDirT_class(mrb), &apr_dir_t_data_type, box));
}

mrb_value
mruby_giftwrap_apr_dir_t(mrb_state* mrb, apr_dir_t *unboxed) {
   mruby_to_native_ref* box = (mruby_to_native_ref*)malloc(sizeof(mruby_to_native_ref));
   box->belongs_to_ruby = TRUE;
   box->obj = unboxed;
   return mrb_obj_value(Data_Wrap_Struct(mrb, AprDirT_class(mrb), &apr_dir_t_data_type, box));
}

void
mruby_set_apr_dir_t_data_ptr(mrb_value obj, apr_dir_t *unboxed) {
  mruby_to_native_ref* box = (mruby_to_native_ref*)malloc(sizeof(mruby_to_native_ref));
  box->belongs_to_ruby = FALSE;
  box->obj = unboxed;
  mrb_data_init(obj, box, &apr_dir_t_data_type);
}

void
mruby_gift_apr_dir_t_data_ptr(mrb_value obj, apr_dir_t *unboxed) {
  mruby_to_native_ref* box = (mruby_to_native_ref*)malloc(sizeof(mruby_to_native_ref));
  box->belongs_to_ruby = TRUE;
  box->obj = unboxed;
  mrb_data_init(obj, box, &apr_dir_t_data_type);
}

apr_dir_t *
mruby_unbox_apr_dir_t(mrb_value boxed) {
  return (apr_dir_t *)((mruby_to_native_ref *)DATA_PTR(boxed))->obj;
}
#endif
/* MRUBY_BINDING_END */

/* MRUBY_BINDING: AprFileT_boxing */
/* sha: 3e95888ddc819aa07f1ec374f694e02418c1b40dc322e0d26af921702881d828 */
#if BIND_AprFileT_TYPE
/*
 * Boxing implementation for apr_file_t
 */

static void free_apr_file_t(mrb_state* mrb, void* ptr) {
  mruby_to_native_ref* box = (mruby_to_native_ref*)ptr;
  if (box->belongs_to_ruby) {
    if (box->obj != NULL) {
      free(box->obj);
      box->obj = NULL;
    }
  }
  free(box);
}

static const mrb_data_type apr_file_t_data_type = {
   "apr_file_t", free_apr_file_t
};

mrb_value
mruby_box_apr_file_t(mrb_state* mrb, apr_file_t *unboxed) {
  mruby_to_native_ref* box = (mruby_to_native_ref*)malloc(sizeof(mruby_to_native_ref));
  box->belongs_to_ruby = FALSE;
  box->obj = unboxed;
  return mrb_obj_value(Data_Wrap_Struct(mrb, AprFileT_class(mrb), &apr_file_t_data_type, box));
}

mrb_value
mruby_giftwrap_apr_file_t(mrb_state* mrb, apr_file_t *unboxed) {
   mruby_to_native_ref* box = (mruby_to_native_ref*)malloc(sizeof(mruby_to_native_ref));
   box->belongs_to_ruby = TRUE;
   box->obj = unboxed;
   return mrb_obj_value(Data_Wrap_Struct(mrb, AprFileT_class(mrb), &apr_file_t_data_type, box));
}

void
mruby_set_apr_file_t_data_ptr(mrb_value obj, apr_file_t *unboxed) {
  mruby_to_native_ref* box = (mruby_to_native_ref*)malloc(sizeof(mruby_to_native_ref));
  box->belongs_to_ruby = FALSE;
  box->obj = unboxed;
  mrb_data_init(obj, box, &apr_file_t_data_type);
}

void
mruby_gift_apr_file_t_data_ptr(mrb_value obj, apr_file_t *unboxed) {
  mruby_to_native_ref* box = (mruby_to_native_ref*)malloc(sizeof(mruby_to_native_ref));
  box->belongs_to_ruby = TRUE;
  box->obj = unboxed;
  mrb_data_init(obj, box, &apr_file_t_data_type);
}

apr_file_t *
mruby_unbox_apr_file_t(mrb_value boxed) {
  return (apr_file_t *)((mruby_to_native_ref *)DATA_PTR(boxed))->obj;
}
#endif
/* MRUBY_BINDING_END */

/* MRUBY_BINDING: AprFinfoT_boxing */
/* sha: 7e968eb591b46e7655339e07be269069ef2327ab57e0bad4f4abf184a3d719e3 */
#if BIND_AprFinfoT_TYPE
/*
 * Boxing implementation for apr_finfo_t
 */

static void free_apr_finfo_t(mrb_state* mrb, void* ptr) {
  mruby_to_native_ref* box = (mruby_to_native_ref*)ptr;
  if (box->belongs_to_ruby) {
    if (box->obj != NULL) {
      free(box->obj);
      box->obj = NULL;
    }
  }
  free(box);
}

static const mrb_data_type apr_finfo_t_data_type = {
   "apr_finfo_t", free_apr_finfo_t
};

mrb_value
mruby_box_apr_finfo_t(mrb_state* mrb, apr_finfo_t *unboxed) {
  mruby_to_native_ref* box = (mruby_to_native_ref*)malloc(sizeof(mruby_to_native_ref));
  box->belongs_to_ruby = FALSE;
  box->obj = unboxed;
  return mrb_obj_value(Data_Wrap_Struct(mrb, AprFinfoT_class(mrb), &apr_finfo_t_data_type, box));
}

mrb_value
mruby_giftwrap_apr_finfo_t(mrb_state* mrb, apr_finfo_t *unboxed) {
   mruby_to_native_ref* box = (mruby_to_native_ref*)malloc(sizeof(mruby_to_native_ref));
   box->belongs_to_ruby = TRUE;
   box->obj = unboxed;
   return mrb_obj_value(Data_Wrap_Struct(mrb, AprFinfoT_class(mrb), &apr_finfo_t_data_type, box));
}

void
mruby_set_apr_finfo_t_data_ptr(mrb_value obj, apr_finfo_t *unboxed) {
  mruby_to_native_ref* box = (mruby_to_native_ref*)malloc(sizeof(mruby_to_native_ref));
  box->belongs_to_ruby = FALSE;
  box->obj = unboxed;
  mrb_data_init(obj, box, &apr_finfo_t_data_type);
}

void
mruby_gift_apr_finfo_t_data_ptr(mrb_value obj, apr_finfo_t *unboxed) {
  mruby_to_native_ref* box = (mruby_to_native_ref*)malloc(sizeof(mruby_to_native_ref));
  box->belongs_to_ruby = TRUE;
  box->obj = unboxed;
  mrb_data_init(obj, box, &apr_finfo_t_data_type);
}

apr_finfo_t *
mruby_unbox_apr_finfo_t(mrb_value boxed) {
  return (apr_finfo_t *)((mruby_to_native_ref *)DATA_PTR(boxed))->obj;
}
#endif
/* MRUBY_BINDING_END */

/* MRUBY_BINDING: AprGlobalMutexT_boxing */
/* sha: d3fede68e5d5fbbeef23f8f677f44fea3129be45363882916a0a08b385743662 */
#if BIND_AprGlobalMutexT_TYPE
/*
 * Boxing implementation for apr_global_mutex_t
 */

static void free_apr_global_mutex_t(mrb_state* mrb, void* ptr) {
  mruby_to_native_ref* box = (mruby_to_native_ref*)ptr;
  if (box->belongs_to_ruby) {
    if (box->obj != NULL) {
      free(box->obj);
      box->obj = NULL;
    }
  }
  free(box);
}

static const mrb_data_type apr_global_mutex_t_data_type = {
   "apr_global_mutex_t", free_apr_global_mutex_t
};

mrb_value
mruby_box_apr_global_mutex_t(mrb_state* mrb, apr_global_mutex_t *unboxed) {
  mruby_to_native_ref* box = (mruby_to_native_ref*)malloc(sizeof(mruby_to_native_ref));
  box->belongs_to_ruby = FALSE;
  box->obj = unboxed;
  return mrb_obj_value(Data_Wrap_Struct(mrb, AprGlobalMutexT_class(mrb), &apr_global_mutex_t_data_type, box));
}

mrb_value
mruby_giftwrap_apr_global_mutex_t(mrb_state* mrb, apr_global_mutex_t *unboxed) {
   mruby_to_native_ref* box = (mruby_to_native_ref*)malloc(sizeof(mruby_to_native_ref));
   box->belongs_to_ruby = TRUE;
   box->obj = unboxed;
   return mrb_obj_value(Data_Wrap_Struct(mrb, AprGlobalMutexT_class(mrb), &apr_global_mutex_t_data_type, box));
}

void
mruby_set_apr_global_mutex_t_data_ptr(mrb_value obj, apr_global_mutex_t *unboxed) {
  mruby_to_native_ref* box = (mruby_to_native_ref*)malloc(sizeof(mruby_to_native_ref));
  box->belongs_to_ruby = FALSE;
  box->obj = unboxed;
  mrb_data_init(obj, box, &apr_global_mutex_t_data_type);
}

void
mruby_gift_apr_global_mutex_t_data_ptr(mrb_value obj, apr_global_mutex_t *unboxed) {
  mruby_to_native_ref* box = (mruby_to_native_ref*)malloc(sizeof(mruby_to_native_ref));
  box->belongs_to_ruby = TRUE;
  box->obj = unboxed;
  mrb_data_init(obj, box, &apr_global_mutex_t_data_type);
}

apr_global_mutex_t *
mruby_unbox_apr_global_mutex_t(mrb_value boxed) {
  return (apr_global_mutex_t *)((mruby_to_native_ref *)DATA_PTR(boxed))->obj;
}
#endif
/* MRUBY_BINDING_END */

/* MRUBY_BINDING: AprHdtrT_boxing */
/* sha: e854040bc57d0291156b481cc9fb9ed0e4dbe4d393e4f24c5d6c2d1545c757b8 */
#if BIND_AprHdtrT_TYPE
/*
 * Boxing implementation for apr_hdtr_t
 */

static void free_apr_hdtr_t(mrb_state* mrb, void* ptr) {
  mruby_to_native_ref* box = (mruby_to_native_ref*)ptr;
  if (box->belongs_to_ruby) {
    if (box->obj != NULL) {
      free(box->obj);
      box->obj = NULL;
    }
  }
  free(box);
}

static const mrb_data_type apr_hdtr_t_data_type = {
   "apr_hdtr_t", free_apr_hdtr_t
};

mrb_value
mruby_box_apr_hdtr_t(mrb_state* mrb, apr_hdtr_t *unboxed) {
  mruby_to_native_ref* box = (mruby_to_native_ref*)malloc(sizeof(mruby_to_native_ref));
  box->belongs_to_ruby = FALSE;
  box->obj = unboxed;
  return mrb_obj_value(Data_Wrap_Struct(mrb, AprHdtrT_class(mrb), &apr_hdtr_t_data_type, box));
}

mrb_value
mruby_giftwrap_apr_hdtr_t(mrb_state* mrb, apr_hdtr_t *unboxed) {
   mruby_to_native_ref* box = (mruby_to_native_ref*)malloc(sizeof(mruby_to_native_ref));
   box->belongs_to_ruby = TRUE;
   box->obj = unboxed;
   return mrb_obj_value(Data_Wrap_Struct(mrb, AprHdtrT_class(mrb), &apr_hdtr_t_data_type, box));
}

void
mruby_set_apr_hdtr_t_data_ptr(mrb_value obj, apr_hdtr_t *unboxed) {
  mruby_to_native_ref* box = (mruby_to_native_ref*)malloc(sizeof(mruby_to_native_ref));
  box->belongs_to_ruby = FALSE;
  box->obj = unboxed;
  mrb_data_init(obj, box, &apr_hdtr_t_data_type);
}

void
mruby_gift_apr_hdtr_t_data_ptr(mrb_value obj, apr_hdtr_t *unboxed) {
  mruby_to_native_ref* box = (mruby_to_native_ref*)malloc(sizeof(mruby_to_native_ref));
  box->belongs_to_ruby = TRUE;
  box->obj = unboxed;
  mrb_data_init(obj, box, &apr_hdtr_t_data_type);
}

apr_hdtr_t *
mruby_unbox_apr_hdtr_t(mrb_value boxed) {
  return (apr_hdtr_t *)((mruby_to_native_ref *)DATA_PTR(boxed))->obj;
}
#endif
/* MRUBY_BINDING_END */

/* MRUBY_BINDING: AprIpsubnetT_boxing */
/* sha: 0542ee05d4e2c6303680ba56cfae14d285371f29689887e798d6e664e4a17979 */
#if BIND_AprIpsubnetT_TYPE
/*
 * Boxing implementation for apr_ipsubnet_t
 */

static void free_apr_ipsubnet_t(mrb_state* mrb, void* ptr) {
  mruby_to_native_ref* box = (mruby_to_native_ref*)ptr;
  if (box->belongs_to_ruby) {
    if (box->obj != NULL) {
      free(box->obj);
      box->obj = NULL;
    }
  }
  free(box);
}

static const mrb_data_type apr_ipsubnet_t_data_type = {
   "apr_ipsubnet_t", free_apr_ipsubnet_t
};

mrb_value
mruby_box_apr_ipsubnet_t(mrb_state* mrb, apr_ipsubnet_t *unboxed) {
  mruby_to_native_ref* box = (mruby_to_native_ref*)malloc(sizeof(mruby_to_native_ref));
  box->belongs_to_ruby = FALSE;
  box->obj = unboxed;
  return mrb_obj_value(Data_Wrap_Struct(mrb, AprIpsubnetT_class(mrb), &apr_ipsubnet_t_data_type, box));
}

mrb_value
mruby_giftwrap_apr_ipsubnet_t(mrb_state* mrb, apr_ipsubnet_t *unboxed) {
   mruby_to_native_ref* box = (mruby_to_native_ref*)malloc(sizeof(mruby_to_native_ref));
   box->belongs_to_ruby = TRUE;
   box->obj = unboxed;
   return mrb_obj_value(Data_Wrap_Struct(mrb, AprIpsubnetT_class(mrb), &apr_ipsubnet_t_data_type, box));
}

void
mruby_set_apr_ipsubnet_t_data_ptr(mrb_value obj, apr_ipsubnet_t *unboxed) {
  mruby_to_native_ref* box = (mruby_to_native_ref*)malloc(sizeof(mruby_to_native_ref));
  box->belongs_to_ruby = FALSE;
  box->obj = unboxed;
  mrb_data_init(obj, box, &apr_ipsubnet_t_data_type);
}

void
mruby_gift_apr_ipsubnet_t_data_ptr(mrb_value obj, apr_ipsubnet_t *unboxed) {
  mruby_to_native_ref* box = (mruby_to_native_ref*)malloc(sizeof(mruby_to_native_ref));
  box->belongs_to_ruby = TRUE;
  box->obj = unboxed;
  mrb_data_init(obj, box, &apr_ipsubnet_t_data_type);
}

apr_ipsubnet_t *
mruby_unbox_apr_ipsubnet_t(mrb_value boxed) {
  return (apr_ipsubnet_t *)((mruby_to_native_ref *)DATA_PTR(boxed))->obj;
}
#endif
/* MRUBY_BINDING_END */

/* MRUBY_BINDING: AprOtherChildRecT_boxing */
/* sha: 1a766ad5808ac3ce228686aa5c392bc7526b1828385b0d4c4d7b42fac4ad3b12 */
#if BIND_AprOtherChildRecT_TYPE
/*
 * Boxing implementation for apr_other_child_rec_t
 */

static void free_apr_other_child_rec_t(mrb_state* mrb, void* ptr) {
  mruby_to_native_ref* box = (mruby_to_native_ref*)ptr;
  if (box->belongs_to_ruby) {
    if (box->obj != NULL) {
      free(box->obj);
      box->obj = NULL;
    }
  }
  free(box);
}

static const mrb_data_type apr_other_child_rec_t_data_type = {
   "apr_other_child_rec_t", free_apr_other_child_rec_t
};

mrb_value
mruby_box_apr_other_child_rec_t(mrb_state* mrb, apr_other_child_rec_t *unboxed) {
  mruby_to_native_ref* box = (mruby_to_native_ref*)malloc(sizeof(mruby_to_native_ref));
  box->belongs_to_ruby = FALSE;
  box->obj = unboxed;
  return mrb_obj_value(Data_Wrap_Struct(mrb, AprOtherChildRecT_class(mrb), &apr_other_child_rec_t_data_type, box));
}

mrb_value
mruby_giftwrap_apr_other_child_rec_t(mrb_state* mrb, apr_other_child_rec_t *unboxed) {
   mruby_to_native_ref* box = (mruby_to_native_ref*)malloc(sizeof(mruby_to_native_ref));
   box->belongs_to_ruby = TRUE;
   box->obj = unboxed;
   return mrb_obj_value(Data_Wrap_Struct(mrb, AprOtherChildRecT_class(mrb), &apr_other_child_rec_t_data_type, box));
}

void
mruby_set_apr_other_child_rec_t_data_ptr(mrb_value obj, apr_other_child_rec_t *unboxed) {
  mruby_to_native_ref* box = (mruby_to_native_ref*)malloc(sizeof(mruby_to_native_ref));
  box->belongs_to_ruby = FALSE;
  box->obj = unboxed;
  mrb_data_init(obj, box, &apr_other_child_rec_t_data_type);
}

void
mruby_gift_apr_other_child_rec_t_data_ptr(mrb_value obj, apr_other_child_rec_t *unboxed) {
  mruby_to_native_ref* box = (mruby_to_native_ref*)malloc(sizeof(mruby_to_native_ref));
  box->belongs_to_ruby = TRUE;
  box->obj = unboxed;
  mrb_data_init(obj, box, &apr_other_child_rec_t_data_type);
}

apr_other_child_rec_t *
mruby_unbox_apr_other_child_rec_t(mrb_value boxed) {
  return (apr_other_child_rec_t *)((mruby_to_native_ref *)DATA_PTR(boxed))->obj;
}
#endif
/* MRUBY_BINDING_END */

/* MRUBY_BINDING: AprPoolT_boxing */
/* sha: e06c7ab7fc799c6f29a65e7e0291a5c18b84afdce6ef7b61af1e5007ee3433be */
#if BIND_AprPoolT_TYPE
/*
 * Boxing implementation for apr_pool_t
 */

static void free_apr_pool_t(mrb_state* mrb, void* ptr) {
  mruby_to_native_ref* box = (mruby_to_native_ref*)ptr;
  if (box->belongs_to_ruby) {
    if (box->obj != NULL) {
      free(box->obj);
      box->obj = NULL;
    }
  }
  free(box);
}

static const mrb_data_type apr_pool_t_data_type = {
   "apr_pool_t", free_apr_pool_t
};

mrb_value
mruby_box_apr_pool_t(mrb_state* mrb, apr_pool_t *unboxed) {
  mruby_to_native_ref* box = (mruby_to_native_ref*)malloc(sizeof(mruby_to_native_ref));
  box->belongs_to_ruby = FALSE;
  box->obj = unboxed;
  return mrb_obj_value(Data_Wrap_Struct(mrb, AprPoolT_class(mrb), &apr_pool_t_data_type, box));
}

mrb_value
mruby_giftwrap_apr_pool_t(mrb_state* mrb, apr_pool_t *unboxed) {
   mruby_to_native_ref* box = (mruby_to_native_ref*)malloc(sizeof(mruby_to_native_ref));
   box->belongs_to_ruby = TRUE;
   box->obj = unboxed;
   return mrb_obj_value(Data_Wrap_Struct(mrb, AprPoolT_class(mrb), &apr_pool_t_data_type, box));
}

void
mruby_set_apr_pool_t_data_ptr(mrb_value obj, apr_pool_t *unboxed) {
  mruby_to_native_ref* box = (mruby_to_native_ref*)malloc(sizeof(mruby_to_native_ref));
  box->belongs_to_ruby = FALSE;
  box->obj = unboxed;
  mrb_data_init(obj, box, &apr_pool_t_data_type);
}

void
mruby_gift_apr_pool_t_data_ptr(mrb_value obj, apr_pool_t *unboxed) {
  mruby_to_native_ref* box = (mruby_to_native_ref*)malloc(sizeof(mruby_to_native_ref));
  box->belongs_to_ruby = TRUE;
  box->obj = unboxed;
  mrb_data_init(obj, box, &apr_pool_t_data_type);
}

apr_pool_t *
mruby_unbox_apr_pool_t(mrb_value boxed) {
  return (apr_pool_t *)((mruby_to_native_ref *)DATA_PTR(boxed))->obj;
}
#endif
/* MRUBY_BINDING_END */

/* MRUBY_BINDING: AprProcMutexT_boxing */
/* sha: e0ddebd00fa557e628c58f352c3298b505f8b383d2d0b8e08465de5a4e831900 */
#if BIND_AprProcMutexT_TYPE
/*
 * Boxing implementation for apr_proc_mutex_t
 */

static void free_apr_proc_mutex_t(mrb_state* mrb, void* ptr) {
  mruby_to_native_ref* box = (mruby_to_native_ref*)ptr;
  if (box->belongs_to_ruby) {
    if (box->obj != NULL) {
      free(box->obj);
      box->obj = NULL;
    }
  }
  free(box);
}

static const mrb_data_type apr_proc_mutex_t_data_type = {
   "apr_proc_mutex_t", free_apr_proc_mutex_t
};

mrb_value
mruby_box_apr_proc_mutex_t(mrb_state* mrb, apr_proc_mutex_t *unboxed) {
  mruby_to_native_ref* box = (mruby_to_native_ref*)malloc(sizeof(mruby_to_native_ref));
  box->belongs_to_ruby = FALSE;
  box->obj = unboxed;
  return mrb_obj_value(Data_Wrap_Struct(mrb, AprProcMutexT_class(mrb), &apr_proc_mutex_t_data_type, box));
}

mrb_value
mruby_giftwrap_apr_proc_mutex_t(mrb_state* mrb, apr_proc_mutex_t *unboxed) {
   mruby_to_native_ref* box = (mruby_to_native_ref*)malloc(sizeof(mruby_to_native_ref));
   box->belongs_to_ruby = TRUE;
   box->obj = unboxed;
   return mrb_obj_value(Data_Wrap_Struct(mrb, AprProcMutexT_class(mrb), &apr_proc_mutex_t_data_type, box));
}

void
mruby_set_apr_proc_mutex_t_data_ptr(mrb_value obj, apr_proc_mutex_t *unboxed) {
  mruby_to_native_ref* box = (mruby_to_native_ref*)malloc(sizeof(mruby_to_native_ref));
  box->belongs_to_ruby = FALSE;
  box->obj = unboxed;
  mrb_data_init(obj, box, &apr_proc_mutex_t_data_type);
}

void
mruby_gift_apr_proc_mutex_t_data_ptr(mrb_value obj, apr_proc_mutex_t *unboxed) {
  mruby_to_native_ref* box = (mruby_to_native_ref*)malloc(sizeof(mruby_to_native_ref));
  box->belongs_to_ruby = TRUE;
  box->obj = unboxed;
  mrb_data_init(obj, box, &apr_proc_mutex_t_data_type);
}

apr_proc_mutex_t *
mruby_unbox_apr_proc_mutex_t(mrb_value boxed) {
  return (apr_proc_mutex_t *)((mruby_to_native_ref *)DATA_PTR(boxed))->obj;
}
#endif
/* MRUBY_BINDING_END */

/* MRUBY_BINDING: AprProcT_boxing */
/* sha: db60074074b5c8588632acea64581b04355d9b02b2677c6a810b3084d4afc21f */
#if BIND_AprProcT_TYPE
/*
 * Boxing implementation for apr_proc_t
 */

static void free_apr_proc_t(mrb_state* mrb, void* ptr) {
  mruby_to_native_ref* box = (mruby_to_native_ref*)ptr;
  if (box->belongs_to_ruby) {
    if (box->obj != NULL) {
      free(box->obj);
      box->obj = NULL;
    }
  }
  free(box);
}

static const mrb_data_type apr_proc_t_data_type = {
   "apr_proc_t", free_apr_proc_t
};

mrb_value
mruby_box_apr_proc_t(mrb_state* mrb, apr_proc_t *unboxed) {
  mruby_to_native_ref* box = (mruby_to_native_ref*)malloc(sizeof(mruby_to_native_ref));
  box->belongs_to_ruby = FALSE;
  box->obj = unboxed;
  return mrb_obj_value(Data_Wrap_Struct(mrb, AprProcT_class(mrb), &apr_proc_t_data_type, box));
}

mrb_value
mruby_giftwrap_apr_proc_t(mrb_state* mrb, apr_proc_t *unboxed) {
   mruby_to_native_ref* box = (mruby_to_native_ref*)malloc(sizeof(mruby_to_native_ref));
   box->belongs_to_ruby = TRUE;
   box->obj = unboxed;
   return mrb_obj_value(Data_Wrap_Struct(mrb, AprProcT_class(mrb), &apr_proc_t_data_type, box));
}

void
mruby_set_apr_proc_t_data_ptr(mrb_value obj, apr_proc_t *unboxed) {
  mruby_to_native_ref* box = (mruby_to_native_ref*)malloc(sizeof(mruby_to_native_ref));
  box->belongs_to_ruby = FALSE;
  box->obj = unboxed;
  mrb_data_init(obj, box, &apr_proc_t_data_type);
}

void
mruby_gift_apr_proc_t_data_ptr(mrb_value obj, apr_proc_t *unboxed) {
  mruby_to_native_ref* box = (mruby_to_native_ref*)malloc(sizeof(mruby_to_native_ref));
  box->belongs_to_ruby = TRUE;
  box->obj = unboxed;
  mrb_data_init(obj, box, &apr_proc_t_data_type);
}

apr_proc_t *
mruby_unbox_apr_proc_t(mrb_value boxed) {
  return (apr_proc_t *)((mruby_to_native_ref *)DATA_PTR(boxed))->obj;
}
#endif
/* MRUBY_BINDING_END */

/* MRUBY_BINDING: AprProcattrT_boxing */
/* sha: e83f6c216cb76dd92e73c369571e9afa0889ccf5e2bab3d7c284a5fcf49ce550 */
#if BIND_AprProcattrT_TYPE
/*
 * Boxing implementation for apr_procattr_t
 */

static void free_apr_procattr_t(mrb_state* mrb, void* ptr) {
  mruby_to_native_ref* box = (mruby_to_native_ref*)ptr;
  if (box->belongs_to_ruby) {
    if (box->obj != NULL) {
      free(box->obj);
      box->obj = NULL;
    }
  }
  free(box);
}

static const mrb_data_type apr_procattr_t_data_type = {
   "apr_procattr_t", free_apr_procattr_t
};

mrb_value
mruby_box_apr_procattr_t(mrb_state* mrb, apr_procattr_t *unboxed) {
  mruby_to_native_ref* box = (mruby_to_native_ref*)malloc(sizeof(mruby_to_native_ref));
  box->belongs_to_ruby = FALSE;
  box->obj = unboxed;
  return mrb_obj_value(Data_Wrap_Struct(mrb, AprProcattrT_class(mrb), &apr_procattr_t_data_type, box));
}

mrb_value
mruby_giftwrap_apr_procattr_t(mrb_state* mrb, apr_procattr_t *unboxed) {
   mruby_to_native_ref* box = (mruby_to_native_ref*)malloc(sizeof(mruby_to_native_ref));
   box->belongs_to_ruby = TRUE;
   box->obj = unboxed;
   return mrb_obj_value(Data_Wrap_Struct(mrb, AprProcattrT_class(mrb), &apr_procattr_t_data_type, box));
}

void
mruby_set_apr_procattr_t_data_ptr(mrb_value obj, apr_procattr_t *unboxed) {
  mruby_to_native_ref* box = (mruby_to_native_ref*)malloc(sizeof(mruby_to_native_ref));
  box->belongs_to_ruby = FALSE;
  box->obj = unboxed;
  mrb_data_init(obj, box, &apr_procattr_t_data_type);
}

void
mruby_gift_apr_procattr_t_data_ptr(mrb_value obj, apr_procattr_t *unboxed) {
  mruby_to_native_ref* box = (mruby_to_native_ref*)malloc(sizeof(mruby_to_native_ref));
  box->belongs_to_ruby = TRUE;
  box->obj = unboxed;
  mrb_data_init(obj, box, &apr_procattr_t_data_type);
}

apr_procattr_t *
mruby_unbox_apr_procattr_t(mrb_value boxed) {
  return (apr_procattr_t *)((mruby_to_native_ref *)DATA_PTR(boxed))->obj;
}
#endif
/* MRUBY_BINDING_END */

/* MRUBY_BINDING: AprSockaddrT_boxing */
/* sha: f206397a89847276f1857db85b423b5e48f63d05ea006abc6488db975de519bd */
#if BIND_AprSockaddrT_TYPE
/*
 * Boxing implementation for apr_sockaddr_t
 */

static void free_apr_sockaddr_t(mrb_state* mrb, void* ptr) {
  mruby_to_native_ref* box = (mruby_to_native_ref*)ptr;
  if (box->belongs_to_ruby) {
    if (box->obj != NULL) {
      free(box->obj);
      box->obj = NULL;
    }
  }
  free(box);
}

static const mrb_data_type apr_sockaddr_t_data_type = {
   "apr_sockaddr_t", free_apr_sockaddr_t
};

mrb_value
mruby_box_apr_sockaddr_t(mrb_state* mrb, apr_sockaddr_t *unboxed) {
  mruby_to_native_ref* box = (mruby_to_native_ref*)malloc(sizeof(mruby_to_native_ref));
  box->belongs_to_ruby = FALSE;
  box->obj = unboxed;
  return mrb_obj_value(Data_Wrap_Struct(mrb, AprSockaddrT_class(mrb), &apr_sockaddr_t_data_type, box));
}

mrb_value
mruby_giftwrap_apr_sockaddr_t(mrb_state* mrb, apr_sockaddr_t *unboxed) {
   mruby_to_native_ref* box = (mruby_to_native_ref*)malloc(sizeof(mruby_to_native_ref));
   box->belongs_to_ruby = TRUE;
   box->obj = unboxed;
   return mrb_obj_value(Data_Wrap_Struct(mrb, AprSockaddrT_class(mrb), &apr_sockaddr_t_data_type, box));
}

void
mruby_set_apr_sockaddr_t_data_ptr(mrb_value obj, apr_sockaddr_t *unboxed) {
  mruby_to_native_ref* box = (mruby_to_native_ref*)malloc(sizeof(mruby_to_native_ref));
  box->belongs_to_ruby = FALSE;
  box->obj = unboxed;
  mrb_data_init(obj, box, &apr_sockaddr_t_data_type);
}

void
mruby_gift_apr_sockaddr_t_data_ptr(mrb_value obj, apr_sockaddr_t *unboxed) {
  mruby_to_native_ref* box = (mruby_to_native_ref*)malloc(sizeof(mruby_to_native_ref));
  box->belongs_to_ruby = TRUE;
  box->obj = unboxed;
  mrb_data_init(obj, box, &apr_sockaddr_t_data_type);
}

apr_sockaddr_t *
mruby_unbox_apr_sockaddr_t(mrb_value boxed) {
  return (apr_sockaddr_t *)((mruby_to_native_ref *)DATA_PTR(boxed))->obj;
}
#endif
/* MRUBY_BINDING_END */

/* MRUBY_BINDING: AprSocketT_boxing */
/* sha: 9daf4f6b339f8528f569b983cdd80fee463af40e0531370e8f8d571edaf76449 */
#if BIND_AprSocketT_TYPE
/*
 * Boxing implementation for apr_socket_t
 */

static void free_apr_socket_t(mrb_state* mrb, void* ptr) {
  mruby_to_native_ref* box = (mruby_to_native_ref*)ptr;
  if (box->belongs_to_ruby) {
    if (box->obj != NULL) {
      free(box->obj);
      box->obj = NULL;
    }
  }
  free(box);
}

static const mrb_data_type apr_socket_t_data_type = {
   "apr_socket_t", free_apr_socket_t
};

mrb_value
mruby_box_apr_socket_t(mrb_state* mrb, apr_socket_t *unboxed) {
  mruby_to_native_ref* box = (mruby_to_native_ref*)malloc(sizeof(mruby_to_native_ref));
  box->belongs_to_ruby = FALSE;
  box->obj = unboxed;
  return mrb_obj_value(Data_Wrap_Struct(mrb, AprSocketT_class(mrb), &apr_socket_t_data_type, box));
}

mrb_value
mruby_giftwrap_apr_socket_t(mrb_state* mrb, apr_socket_t *unboxed) {
   mruby_to_native_ref* box = (mruby_to_native_ref*)malloc(sizeof(mruby_to_native_ref));
   box->belongs_to_ruby = TRUE;
   box->obj = unboxed;
   return mrb_obj_value(Data_Wrap_Struct(mrb, AprSocketT_class(mrb), &apr_socket_t_data_type, box));
}

void
mruby_set_apr_socket_t_data_ptr(mrb_value obj, apr_socket_t *unboxed) {
  mruby_to_native_ref* box = (mruby_to_native_ref*)malloc(sizeof(mruby_to_native_ref));
  box->belongs_to_ruby = FALSE;
  box->obj = unboxed;
  mrb_data_init(obj, box, &apr_socket_t_data_type);
}

void
mruby_gift_apr_socket_t_data_ptr(mrb_value obj, apr_socket_t *unboxed) {
  mruby_to_native_ref* box = (mruby_to_native_ref*)malloc(sizeof(mruby_to_native_ref));
  box->belongs_to_ruby = TRUE;
  box->obj = unboxed;
  mrb_data_init(obj, box, &apr_socket_t_data_type);
}

apr_socket_t *
mruby_unbox_apr_socket_t(mrb_value boxed) {
  return (apr_socket_t *)((mruby_to_native_ref *)DATA_PTR(boxed))->obj;
}
#endif
/* MRUBY_BINDING_END */

/* MRUBY_BINDING: AprThreadOnceT_boxing */
/* sha: ce100ac6386e9d721739c07c0dcca0aa7e3bb00a3f1e3697628129ad7d9a7ee6 */
#if BIND_AprThreadOnceT_TYPE
/*
 * Boxing implementation for apr_thread_once_t
 */

static void free_apr_thread_once_t(mrb_state* mrb, void* ptr) {
  mruby_to_native_ref* box = (mruby_to_native_ref*)ptr;
  if (box->belongs_to_ruby) {
    if (box->obj != NULL) {
      free(box->obj);
      box->obj = NULL;
    }
  }
  free(box);
}

static const mrb_data_type apr_thread_once_t_data_type = {
   "apr_thread_once_t", free_apr_thread_once_t
};

mrb_value
mruby_box_apr_thread_once_t(mrb_state* mrb, apr_thread_once_t *unboxed) {
  mruby_to_native_ref* box = (mruby_to_native_ref*)malloc(sizeof(mruby_to_native_ref));
  box->belongs_to_ruby = FALSE;
  box->obj = unboxed;
  return mrb_obj_value(Data_Wrap_Struct(mrb, AprThreadOnceT_class(mrb), &apr_thread_once_t_data_type, box));
}

mrb_value
mruby_giftwrap_apr_thread_once_t(mrb_state* mrb, apr_thread_once_t *unboxed) {
   mruby_to_native_ref* box = (mruby_to_native_ref*)malloc(sizeof(mruby_to_native_ref));
   box->belongs_to_ruby = TRUE;
   box->obj = unboxed;
   return mrb_obj_value(Data_Wrap_Struct(mrb, AprThreadOnceT_class(mrb), &apr_thread_once_t_data_type, box));
}

void
mruby_set_apr_thread_once_t_data_ptr(mrb_value obj, apr_thread_once_t *unboxed) {
  mruby_to_native_ref* box = (mruby_to_native_ref*)malloc(sizeof(mruby_to_native_ref));
  box->belongs_to_ruby = FALSE;
  box->obj = unboxed;
  mrb_data_init(obj, box, &apr_thread_once_t_data_type);
}

void
mruby_gift_apr_thread_once_t_data_ptr(mrb_value obj, apr_thread_once_t *unboxed) {
  mruby_to_native_ref* box = (mruby_to_native_ref*)malloc(sizeof(mruby_to_native_ref));
  box->belongs_to_ruby = TRUE;
  box->obj = unboxed;
  mrb_data_init(obj, box, &apr_thread_once_t_data_type);
}

apr_thread_once_t *
mruby_unbox_apr_thread_once_t(mrb_value boxed) {
  return (apr_thread_once_t *)((mruby_to_native_ref *)DATA_PTR(boxed))->obj;
}
#endif
/* MRUBY_BINDING_END */

/* MRUBY_BINDING: AprThreadT_boxing */
/* sha: 465cbfeef1b77df925c64b4d2dc298abbc1adb35b072df47ee531dea1a6e221d */
#if BIND_AprThreadT_TYPE
/*
 * Boxing implementation for apr_thread_t
 */

static void free_apr_thread_t(mrb_state* mrb, void* ptr) {
  mruby_to_native_ref* box = (mruby_to_native_ref*)ptr;
  if (box->belongs_to_ruby) {
    if (box->obj != NULL) {
      free(box->obj);
      box->obj = NULL;
    }
  }
  free(box);
}

static const mrb_data_type apr_thread_t_data_type = {
   "apr_thread_t", free_apr_thread_t
};

mrb_value
mruby_box_apr_thread_t(mrb_state* mrb, apr_thread_t *unboxed) {
  mruby_to_native_ref* box = (mruby_to_native_ref*)malloc(sizeof(mruby_to_native_ref));
  box->belongs_to_ruby = FALSE;
  box->obj = unboxed;
  return mrb_obj_value(Data_Wrap_Struct(mrb, AprThreadT_class(mrb), &apr_thread_t_data_type, box));
}

mrb_value
mruby_giftwrap_apr_thread_t(mrb_state* mrb, apr_thread_t *unboxed) {
   mruby_to_native_ref* box = (mruby_to_native_ref*)malloc(sizeof(mruby_to_native_ref));
   box->belongs_to_ruby = TRUE;
   box->obj = unboxed;
   return mrb_obj_value(Data_Wrap_Struct(mrb, AprThreadT_class(mrb), &apr_thread_t_data_type, box));
}

void
mruby_set_apr_thread_t_data_ptr(mrb_value obj, apr_thread_t *unboxed) {
  mruby_to_native_ref* box = (mruby_to_native_ref*)malloc(sizeof(mruby_to_native_ref));
  box->belongs_to_ruby = FALSE;
  box->obj = unboxed;
  mrb_data_init(obj, box, &apr_thread_t_data_type);
}

void
mruby_gift_apr_thread_t_data_ptr(mrb_value obj, apr_thread_t *unboxed) {
  mruby_to_native_ref* box = (mruby_to_native_ref*)malloc(sizeof(mruby_to_native_ref));
  box->belongs_to_ruby = TRUE;
  box->obj = unboxed;
  mrb_data_init(obj, box, &apr_thread_t_data_type);
}

apr_thread_t *
mruby_unbox_apr_thread_t(mrb_value boxed) {
  return (apr_thread_t *)((mruby_to_native_ref *)DATA_PTR(boxed))->obj;
}
#endif
/* MRUBY_BINDING_END */

/* MRUBY_BINDING: AprThreadattrT_boxing */
/* sha: f4983c425221c286899f3abf373eeaf2bb758ec6be21bbce56559fae8301497c */
#if BIND_AprThreadattrT_TYPE
/*
 * Boxing implementation for apr_threadattr_t
 */

static void free_apr_threadattr_t(mrb_state* mrb, void* ptr) {
  mruby_to_native_ref* box = (mruby_to_native_ref*)ptr;
  if (box->belongs_to_ruby) {
    if (box->obj != NULL) {
      free(box->obj);
      box->obj = NULL;
    }
  }
  free(box);
}

static const mrb_data_type apr_threadattr_t_data_type = {
   "apr_threadattr_t", free_apr_threadattr_t
};

mrb_value
mruby_box_apr_threadattr_t(mrb_state* mrb, apr_threadattr_t *unboxed) {
  mruby_to_native_ref* box = (mruby_to_native_ref*)malloc(sizeof(mruby_to_native_ref));
  box->belongs_to_ruby = FALSE;
  box->obj = unboxed;
  return mrb_obj_value(Data_Wrap_Struct(mrb, AprThreadattrT_class(mrb), &apr_threadattr_t_data_type, box));
}

mrb_value
mruby_giftwrap_apr_threadattr_t(mrb_state* mrb, apr_threadattr_t *unboxed) {
   mruby_to_native_ref* box = (mruby_to_native_ref*)malloc(sizeof(mruby_to_native_ref));
   box->belongs_to_ruby = TRUE;
   box->obj = unboxed;
   return mrb_obj_value(Data_Wrap_Struct(mrb, AprThreadattrT_class(mrb), &apr_threadattr_t_data_type, box));
}

void
mruby_set_apr_threadattr_t_data_ptr(mrb_value obj, apr_threadattr_t *unboxed) {
  mruby_to_native_ref* box = (mruby_to_native_ref*)malloc(sizeof(mruby_to_native_ref));
  box->belongs_to_ruby = FALSE;
  box->obj = unboxed;
  mrb_data_init(obj, box, &apr_threadattr_t_data_type);
}

void
mruby_gift_apr_threadattr_t_data_ptr(mrb_value obj, apr_threadattr_t *unboxed) {
  mruby_to_native_ref* box = (mruby_to_native_ref*)malloc(sizeof(mruby_to_native_ref));
  box->belongs_to_ruby = TRUE;
  box->obj = unboxed;
  mrb_data_init(obj, box, &apr_threadattr_t_data_type);
}

apr_threadattr_t *
mruby_unbox_apr_threadattr_t(mrb_value boxed) {
  return (apr_threadattr_t *)((mruby_to_native_ref *)DATA_PTR(boxed))->obj;
}
#endif
/* MRUBY_BINDING_END */

/* MRUBY_BINDING: AprThreadkeyT_boxing */
/* sha: ca41d0582a8e9d751c30c9611acb8aba81979cc8bc963f73b1ec9b4d73a55242 */
#if BIND_AprThreadkeyT_TYPE
/*
 * Boxing implementation for apr_threadkey_t
 */

static void free_apr_threadkey_t(mrb_state* mrb, void* ptr) {
  mruby_to_native_ref* box = (mruby_to_native_ref*)ptr;
  if (box->belongs_to_ruby) {
    if (box->obj != NULL) {
      free(box->obj);
      box->obj = NULL;
    }
  }
  free(box);
}

static const mrb_data_type apr_threadkey_t_data_type = {
   "apr_threadkey_t", free_apr_threadkey_t
};

mrb_value
mruby_box_apr_threadkey_t(mrb_state* mrb, apr_threadkey_t *unboxed) {
  mruby_to_native_ref* box = (mruby_to_native_ref*)malloc(sizeof(mruby_to_native_ref));
  box->belongs_to_ruby = FALSE;
  box->obj = unboxed;
  return mrb_obj_value(Data_Wrap_Struct(mrb, AprThreadkeyT_class(mrb), &apr_threadkey_t_data_type, box));
}

mrb_value
mruby_giftwrap_apr_threadkey_t(mrb_state* mrb, apr_threadkey_t *unboxed) {
   mruby_to_native_ref* box = (mruby_to_native_ref*)malloc(sizeof(mruby_to_native_ref));
   box->belongs_to_ruby = TRUE;
   box->obj = unboxed;
   return mrb_obj_value(Data_Wrap_Struct(mrb, AprThreadkeyT_class(mrb), &apr_threadkey_t_data_type, box));
}

void
mruby_set_apr_threadkey_t_data_ptr(mrb_value obj, apr_threadkey_t *unboxed) {
  mruby_to_native_ref* box = (mruby_to_native_ref*)malloc(sizeof(mruby_to_native_ref));
  box->belongs_to_ruby = FALSE;
  box->obj = unboxed;
  mrb_data_init(obj, box, &apr_threadkey_t_data_type);
}

void
mruby_gift_apr_threadkey_t_data_ptr(mrb_value obj, apr_threadkey_t *unboxed) {
  mruby_to_native_ref* box = (mruby_to_native_ref*)malloc(sizeof(mruby_to_native_ref));
  box->belongs_to_ruby = TRUE;
  box->obj = unboxed;
  mrb_data_init(obj, box, &apr_threadkey_t_data_type);
}

apr_threadkey_t *
mruby_unbox_apr_threadkey_t(mrb_value boxed) {
  return (apr_threadkey_t *)((mruby_to_native_ref *)DATA_PTR(boxed))->obj;
}
#endif
/* MRUBY_BINDING_END */

/* MRUBY_BINDING: AprTimeExpT_boxing */
/* sha: 688a68a69aad321dd9de8438dddf9dfd3dd2e7ea190b8ef71e8713c6934d7c62 */
#if BIND_AprTimeExpT_TYPE
/*
 * Boxing implementation for apr_time_exp_t
 */

static void free_apr_time_exp_t(mrb_state* mrb, void* ptr) {
  mruby_to_native_ref* box = (mruby_to_native_ref*)ptr;
  if (box->belongs_to_ruby) {
    if (box->obj != NULL) {
      free(box->obj);
      box->obj = NULL;
    }
  }
  free(box);
}

static const mrb_data_type apr_time_exp_t_data_type = {
   "apr_time_exp_t", free_apr_time_exp_t
};

mrb_value
mruby_box_apr_time_exp_t(mrb_state* mrb, apr_time_exp_t *unboxed) {
  mruby_to_native_ref* box = (mruby_to_native_ref*)malloc(sizeof(mruby_to_native_ref));
  box->belongs_to_ruby = FALSE;
  box->obj = unboxed;
  return mrb_obj_value(Data_Wrap_Struct(mrb, AprTimeExpT_class(mrb), &apr_time_exp_t_data_type, box));
}

mrb_value
mruby_giftwrap_apr_time_exp_t(mrb_state* mrb, apr_time_exp_t *unboxed) {
   mruby_to_native_ref* box = (mruby_to_native_ref*)malloc(sizeof(mruby_to_native_ref));
   box->belongs_to_ruby = TRUE;
   box->obj = unboxed;
   return mrb_obj_value(Data_Wrap_Struct(mrb, AprTimeExpT_class(mrb), &apr_time_exp_t_data_type, box));
}

void
mruby_set_apr_time_exp_t_data_ptr(mrb_value obj, apr_time_exp_t *unboxed) {
  mruby_to_native_ref* box = (mruby_to_native_ref*)malloc(sizeof(mruby_to_native_ref));
  box->belongs_to_ruby = FALSE;
  box->obj = unboxed;
  mrb_data_init(obj, box, &apr_time_exp_t_data_type);
}

void
mruby_gift_apr_time_exp_t_data_ptr(mrb_value obj, apr_time_exp_t *unboxed) {
  mruby_to_native_ref* box = (mruby_to_native_ref*)malloc(sizeof(mruby_to_native_ref));
  box->belongs_to_ruby = TRUE;
  box->obj = unboxed;
  mrb_data_init(obj, box, &apr_time_exp_t_data_type);
}

apr_time_exp_t *
mruby_unbox_apr_time_exp_t(mrb_value boxed) {
  return (apr_time_exp_t *)((mruby_to_native_ref *)DATA_PTR(boxed))->obj;
}
#endif
/* MRUBY_BINDING_END */

/* MRUBY_BINDING: footer */
/* sha: user_defined */

/* MRUBY_BINDING_END */
