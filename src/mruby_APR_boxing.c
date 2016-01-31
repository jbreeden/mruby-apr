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

/* MRUBY_BINDING: Dir_boxing */
/* sha: ffa81a3f03900ae45364bf0eef7144415c76ff4f54b15e3a5b791b70e4588364 */
#if BIND_Dir_TYPE
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
  return mrb_obj_value(Data_Wrap_Struct(mrb, Dir_class(mrb), &apr_dir_t_data_type, box));
}

mrb_value
mruby_giftwrap_apr_dir_t(mrb_state* mrb, apr_dir_t *unboxed) {
   mruby_to_native_ref* box = (mruby_to_native_ref*)malloc(sizeof(mruby_to_native_ref));
   box->belongs_to_ruby = TRUE;
   box->obj = unboxed;
   return mrb_obj_value(Data_Wrap_Struct(mrb, Dir_class(mrb), &apr_dir_t_data_type, box));
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

/* MRUBY_BINDING: File_boxing */
/* sha: 7cb942b65c37b911cdb077dbdc2d67e4ab1844bdf45a1ee7086a82e270947166 */
#if BIND_File_TYPE
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
  return mrb_obj_value(Data_Wrap_Struct(mrb, File_class(mrb), &apr_file_t_data_type, box));
}

mrb_value
mruby_giftwrap_apr_file_t(mrb_state* mrb, apr_file_t *unboxed) {
   mruby_to_native_ref* box = (mruby_to_native_ref*)malloc(sizeof(mruby_to_native_ref));
   box->belongs_to_ruby = TRUE;
   box->obj = unboxed;
   return mrb_obj_value(Data_Wrap_Struct(mrb, File_class(mrb), &apr_file_t_data_type, box));
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

/* MRUBY_BINDING: Finfo_boxing */
/* sha: 18dfc92489097f3b76a86b734d09f3b47654c4fdad07c000e077cbbc4d939a91 */
#if BIND_Finfo_TYPE
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
  return mrb_obj_value(Data_Wrap_Struct(mrb, Finfo_class(mrb), &apr_finfo_t_data_type, box));
}

mrb_value
mruby_giftwrap_apr_finfo_t(mrb_state* mrb, apr_finfo_t *unboxed) {
   mruby_to_native_ref* box = (mruby_to_native_ref*)malloc(sizeof(mruby_to_native_ref));
   box->belongs_to_ruby = TRUE;
   box->obj = unboxed;
   return mrb_obj_value(Data_Wrap_Struct(mrb, Finfo_class(mrb), &apr_finfo_t_data_type, box));
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

/* MRUBY_BINDING: GlobalMutex_boxing */
/* sha: 20c365bf2519814e55ad29d25a1ad374ea61d952c97e2d3eaba7ec9e9c243246 */
#if BIND_GlobalMutex_TYPE
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
  return mrb_obj_value(Data_Wrap_Struct(mrb, GlobalMutex_class(mrb), &apr_global_mutex_t_data_type, box));
}

mrb_value
mruby_giftwrap_apr_global_mutex_t(mrb_state* mrb, apr_global_mutex_t *unboxed) {
   mruby_to_native_ref* box = (mruby_to_native_ref*)malloc(sizeof(mruby_to_native_ref));
   box->belongs_to_ruby = TRUE;
   box->obj = unboxed;
   return mrb_obj_value(Data_Wrap_Struct(mrb, GlobalMutex_class(mrb), &apr_global_mutex_t_data_type, box));
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

/* MRUBY_BINDING: Hdtr_boxing */
/* sha: 3d35c3755978ce64c68798c6a5f5d1fc8b8102d8aa06f66347cd3d04b9ec969b */
#if BIND_Hdtr_TYPE
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
  return mrb_obj_value(Data_Wrap_Struct(mrb, Hdtr_class(mrb), &apr_hdtr_t_data_type, box));
}

mrb_value
mruby_giftwrap_apr_hdtr_t(mrb_state* mrb, apr_hdtr_t *unboxed) {
   mruby_to_native_ref* box = (mruby_to_native_ref*)malloc(sizeof(mruby_to_native_ref));
   box->belongs_to_ruby = TRUE;
   box->obj = unboxed;
   return mrb_obj_value(Data_Wrap_Struct(mrb, Hdtr_class(mrb), &apr_hdtr_t_data_type, box));
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

/* MRUBY_BINDING: Ipsubnet_boxing */
/* sha: 8bc1dba3e3706a32c3b50e50c995114ddfa911ab7d8c0278122e64ea87f957c8 */
#if BIND_Ipsubnet_TYPE
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
  return mrb_obj_value(Data_Wrap_Struct(mrb, Ipsubnet_class(mrb), &apr_ipsubnet_t_data_type, box));
}

mrb_value
mruby_giftwrap_apr_ipsubnet_t(mrb_state* mrb, apr_ipsubnet_t *unboxed) {
   mruby_to_native_ref* box = (mruby_to_native_ref*)malloc(sizeof(mruby_to_native_ref));
   box->belongs_to_ruby = TRUE;
   box->obj = unboxed;
   return mrb_obj_value(Data_Wrap_Struct(mrb, Ipsubnet_class(mrb), &apr_ipsubnet_t_data_type, box));
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

/* MRUBY_BINDING: OtherChildRec_boxing */
/* sha: 6845c5ac69edce601c22db2e3ef6410b4eeb72bb516ad6ae8336627b51ad2293 */
#if BIND_OtherChildRec_TYPE
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
  return mrb_obj_value(Data_Wrap_Struct(mrb, OtherChildRec_class(mrb), &apr_other_child_rec_t_data_type, box));
}

mrb_value
mruby_giftwrap_apr_other_child_rec_t(mrb_state* mrb, apr_other_child_rec_t *unboxed) {
   mruby_to_native_ref* box = (mruby_to_native_ref*)malloc(sizeof(mruby_to_native_ref));
   box->belongs_to_ruby = TRUE;
   box->obj = unboxed;
   return mrb_obj_value(Data_Wrap_Struct(mrb, OtherChildRec_class(mrb), &apr_other_child_rec_t_data_type, box));
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

/* MRUBY_BINDING: Pool_boxing */
/* sha: 904ffedd41c9eb209aff1fed61a008b23db573dc77bfda317a9f3d3ccdcf3912 */
#if BIND_Pool_TYPE
/*
 * Boxing implementation for apr_pool_t
 */

static void free_apr_pool_t(mrb_state* mrb, void* ptr) {
  mruby_to_native_ref* box = (mruby_to_native_ref*)ptr;
  if (box->belongs_to_ruby) {
    if (box->obj != NULL) {
      apr_pool_destroy(box->obj);
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
  return mrb_obj_value(Data_Wrap_Struct(mrb, Pool_class(mrb), &apr_pool_t_data_type, box));
}

mrb_value
mruby_giftwrap_apr_pool_t(mrb_state* mrb, apr_pool_t *unboxed) {
   mruby_to_native_ref* box = (mruby_to_native_ref*)malloc(sizeof(mruby_to_native_ref));
   box->belongs_to_ruby = TRUE;
   box->obj = unboxed;
   return mrb_obj_value(Data_Wrap_Struct(mrb, Pool_class(mrb), &apr_pool_t_data_type, box));
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

/* MRUBY_BINDING: ProcMutex_boxing */
/* sha: ce33ef7a74c20ec0fd0e678c9b2b65fec3b1f2ba2593327d6a0667668f4bb2a2 */
#if BIND_ProcMutex_TYPE
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
  return mrb_obj_value(Data_Wrap_Struct(mrb, ProcMutex_class(mrb), &apr_proc_mutex_t_data_type, box));
}

mrb_value
mruby_giftwrap_apr_proc_mutex_t(mrb_state* mrb, apr_proc_mutex_t *unboxed) {
   mruby_to_native_ref* box = (mruby_to_native_ref*)malloc(sizeof(mruby_to_native_ref));
   box->belongs_to_ruby = TRUE;
   box->obj = unboxed;
   return mrb_obj_value(Data_Wrap_Struct(mrb, ProcMutex_class(mrb), &apr_proc_mutex_t_data_type, box));
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

/* MRUBY_BINDING: Proc_boxing */
/* sha: 1b0058400c96a10cd735426702e684b73a2eb8a675b28feb576d9b15d784001c */
#if BIND_Proc_TYPE
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
  return mrb_obj_value(Data_Wrap_Struct(mrb, Proc_class(mrb), &apr_proc_t_data_type, box));
}

mrb_value
mruby_giftwrap_apr_proc_t(mrb_state* mrb, apr_proc_t *unboxed) {
   mruby_to_native_ref* box = (mruby_to_native_ref*)malloc(sizeof(mruby_to_native_ref));
   box->belongs_to_ruby = TRUE;
   box->obj = unboxed;
   return mrb_obj_value(Data_Wrap_Struct(mrb, Proc_class(mrb), &apr_proc_t_data_type, box));
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

/* MRUBY_BINDING: Procattr_boxing */
/* sha: 3e2493af382baec7de0ac3f24e21533a92d52c8b1486b621e1b420896be20108 */
#if BIND_Procattr_TYPE
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
  return mrb_obj_value(Data_Wrap_Struct(mrb, Procattr_class(mrb), &apr_procattr_t_data_type, box));
}

mrb_value
mruby_giftwrap_apr_procattr_t(mrb_state* mrb, apr_procattr_t *unboxed) {
   mruby_to_native_ref* box = (mruby_to_native_ref*)malloc(sizeof(mruby_to_native_ref));
   box->belongs_to_ruby = TRUE;
   box->obj = unboxed;
   return mrb_obj_value(Data_Wrap_Struct(mrb, Procattr_class(mrb), &apr_procattr_t_data_type, box));
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

/* MRUBY_BINDING: Sockaddr_boxing */
/* sha: 5846106ce02281c11cc695f9d72ca199bf2e259e6fba41435db2032cf4a2fff2 */
#if BIND_Sockaddr_TYPE
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
  return mrb_obj_value(Data_Wrap_Struct(mrb, Sockaddr_class(mrb), &apr_sockaddr_t_data_type, box));
}

mrb_value
mruby_giftwrap_apr_sockaddr_t(mrb_state* mrb, apr_sockaddr_t *unboxed) {
   mruby_to_native_ref* box = (mruby_to_native_ref*)malloc(sizeof(mruby_to_native_ref));
   box->belongs_to_ruby = TRUE;
   box->obj = unboxed;
   return mrb_obj_value(Data_Wrap_Struct(mrb, Sockaddr_class(mrb), &apr_sockaddr_t_data_type, box));
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

/* MRUBY_BINDING: Socket_boxing */
/* sha: 83f656f2513c929c0161a40d1d2e77f5e121cd1ffa3f521f0fe9fd18837ad70b */
#if BIND_Socket_TYPE
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
  return mrb_obj_value(Data_Wrap_Struct(mrb, Socket_class(mrb), &apr_socket_t_data_type, box));
}

mrb_value
mruby_giftwrap_apr_socket_t(mrb_state* mrb, apr_socket_t *unboxed) {
   mruby_to_native_ref* box = (mruby_to_native_ref*)malloc(sizeof(mruby_to_native_ref));
   box->belongs_to_ruby = TRUE;
   box->obj = unboxed;
   return mrb_obj_value(Data_Wrap_Struct(mrb, Socket_class(mrb), &apr_socket_t_data_type, box));
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

/* MRUBY_BINDING: ThreadOnce_boxing */
/* sha: 5d0ec171614c89b6278b56e8fcc4474e61bc111234f6d5ce40e3fd746b883f9e */
#if BIND_ThreadOnce_TYPE
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
  return mrb_obj_value(Data_Wrap_Struct(mrb, ThreadOnce_class(mrb), &apr_thread_once_t_data_type, box));
}

mrb_value
mruby_giftwrap_apr_thread_once_t(mrb_state* mrb, apr_thread_once_t *unboxed) {
   mruby_to_native_ref* box = (mruby_to_native_ref*)malloc(sizeof(mruby_to_native_ref));
   box->belongs_to_ruby = TRUE;
   box->obj = unboxed;
   return mrb_obj_value(Data_Wrap_Struct(mrb, ThreadOnce_class(mrb), &apr_thread_once_t_data_type, box));
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

/* MRUBY_BINDING: Thread_boxing */
/* sha: cef59e3ae6cb71017c9827514f6cec42bd7ebbe85006a880ad3b2e279d7abb73 */
#if BIND_Thread_TYPE
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
  return mrb_obj_value(Data_Wrap_Struct(mrb, Thread_class(mrb), &apr_thread_t_data_type, box));
}

mrb_value
mruby_giftwrap_apr_thread_t(mrb_state* mrb, apr_thread_t *unboxed) {
   mruby_to_native_ref* box = (mruby_to_native_ref*)malloc(sizeof(mruby_to_native_ref));
   box->belongs_to_ruby = TRUE;
   box->obj = unboxed;
   return mrb_obj_value(Data_Wrap_Struct(mrb, Thread_class(mrb), &apr_thread_t_data_type, box));
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

/* MRUBY_BINDING: Threadattr_boxing */
/* sha: 723b826ee0a946744ebbf66c4745db6d890d60a07804d84edff3dbecadd8989f */
#if BIND_Threadattr_TYPE
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
  return mrb_obj_value(Data_Wrap_Struct(mrb, Threadattr_class(mrb), &apr_threadattr_t_data_type, box));
}

mrb_value
mruby_giftwrap_apr_threadattr_t(mrb_state* mrb, apr_threadattr_t *unboxed) {
   mruby_to_native_ref* box = (mruby_to_native_ref*)malloc(sizeof(mruby_to_native_ref));
   box->belongs_to_ruby = TRUE;
   box->obj = unboxed;
   return mrb_obj_value(Data_Wrap_Struct(mrb, Threadattr_class(mrb), &apr_threadattr_t_data_type, box));
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

/* MRUBY_BINDING: Threadkey_boxing */
/* sha: 6f27e8568c836515b0224f7fdbd3eca016ab8ee1ccb6649a6bfa897b422ef22a */
#if BIND_Threadkey_TYPE
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
  return mrb_obj_value(Data_Wrap_Struct(mrb, Threadkey_class(mrb), &apr_threadkey_t_data_type, box));
}

mrb_value
mruby_giftwrap_apr_threadkey_t(mrb_state* mrb, apr_threadkey_t *unboxed) {
   mruby_to_native_ref* box = (mruby_to_native_ref*)malloc(sizeof(mruby_to_native_ref));
   box->belongs_to_ruby = TRUE;
   box->obj = unboxed;
   return mrb_obj_value(Data_Wrap_Struct(mrb, Threadkey_class(mrb), &apr_threadkey_t_data_type, box));
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

/* MRUBY_BINDING: TimeExp_boxing */
/* sha: a31db95935db180f51db2c39a6f4819f5b4e526b265e7a09343195d80a2a8350 */
#if BIND_TimeExp_TYPE
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
  return mrb_obj_value(Data_Wrap_Struct(mrb, TimeExp_class(mrb), &apr_time_exp_t_data_type, box));
}

mrb_value
mruby_giftwrap_apr_time_exp_t(mrb_state* mrb, apr_time_exp_t *unboxed) {
   mruby_to_native_ref* box = (mruby_to_native_ref*)malloc(sizeof(mruby_to_native_ref));
   box->belongs_to_ruby = TRUE;
   box->obj = unboxed;
   return mrb_obj_value(Data_Wrap_Struct(mrb, TimeExp_class(mrb), &apr_time_exp_t_data_type, box));
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
