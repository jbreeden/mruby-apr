#ifndef MRUBY_APR_BOXING_HEADER
#define MRUBY_APR_BOXING_HEADER

/* MRUBY_BINDING: header */
/* sha: user_defined */

/* MRUBY_BINDING_END */


/*
 * Boxing declarations
 * -------------------
 *
 * These declarations are enabled by the macros in mruby_APR_classes.h
 */

/*
* Extra wrapper over native pointer to indicate who owns this memory.
* Owner is mruby (it should be garage collected) or C (it shouldn't be).
*/
typedef struct mruby_to_native_ref_ {
  /* If true, indicates that the object should be freed when
   * mruby garbage collects the ruby object containing this pointer.
   * This is set to true when an object is boxed via the `giftwrap`
   * or `gift_{type}_ptr_set` functions.
   */
  unsigned char belongs_to_ruby;

  /* A pointer to the native object */
  void* obj;

  /* For the convenience of the binding writer,
   * the data pointer can be used to associate arbitrary
   * data with a reference to a C object.
   * 
   * Possible uses:
   * - A function pointer to invoke instead of `free` on GC.
   * - A pointer back to the RObject, to be accessed during GC.
   * - etc.
   */
  void* data;
} mruby_to_native_ref;

/* MRUBY_BINDING: Dir::boxing_decls */
/* sha: c53bed8cd837462797703861a020b497f1ee2cf9cf9c9a193afcd905d1ec0956 */
#if BIND_Dir_TYPE
mrb_value
mruby_box_apr_dir_t(mrb_state* mrb, apr_dir_t *unboxed);

mrb_value
mruby_giftwrap_apr_dir_t(mrb_state* mrb, apr_dir_t *unboxed);

void
mruby_set_apr_dir_t_data_ptr(mrb_value obj, apr_dir_t *unboxed);

void
mruby_gift_apr_dir_t_data_ptr(mrb_value obj, apr_dir_t *unboxed);

apr_dir_t *
mruby_unbox_apr_dir_t(mrb_value boxed);
#endif
/* MRUBY_BINDING_END */

/* MRUBY_BINDING: File::boxing_decls */
/* sha: 6e3df7ac69668179bbbe74b624cb29b07f9ca2ce33cd8fb1295febc8e7e075d1 */
#if BIND_File_TYPE
mrb_value
mruby_box_apr_file_t(mrb_state* mrb, apr_file_t *unboxed);

mrb_value
mruby_giftwrap_apr_file_t(mrb_state* mrb, apr_file_t *unboxed);

void
mruby_set_apr_file_t_data_ptr(mrb_value obj, apr_file_t *unboxed);

void
mruby_gift_apr_file_t_data_ptr(mrb_value obj, apr_file_t *unboxed);

apr_file_t *
mruby_unbox_apr_file_t(mrb_value boxed);
#endif
/* MRUBY_BINDING_END */

/* MRUBY_BINDING: Finfo::boxing_decls */
/* sha: fb6e46e2a883559293f7d4126c9d61836515f9d6a1425fcf2515bb2fd4c21088 */
#if BIND_Finfo_TYPE
mrb_value
mruby_box_apr_finfo_t(mrb_state* mrb, apr_finfo_t *unboxed);

mrb_value
mruby_giftwrap_apr_finfo_t(mrb_state* mrb, apr_finfo_t *unboxed);

void
mruby_set_apr_finfo_t_data_ptr(mrb_value obj, apr_finfo_t *unboxed);

void
mruby_gift_apr_finfo_t_data_ptr(mrb_value obj, apr_finfo_t *unboxed);

apr_finfo_t *
mruby_unbox_apr_finfo_t(mrb_value boxed);
#endif
/* MRUBY_BINDING_END */

/* MRUBY_BINDING: GlobalMutex::boxing_decls */
/* sha: 19018eea66c193f2ab177e93c31a3acecfaf438891dffc83bc6676ce3b19929e */
#if BIND_GlobalMutex_TYPE
mrb_value
mruby_box_apr_global_mutex_t(mrb_state* mrb, apr_global_mutex_t *unboxed);

mrb_value
mruby_giftwrap_apr_global_mutex_t(mrb_state* mrb, apr_global_mutex_t *unboxed);

void
mruby_set_apr_global_mutex_t_data_ptr(mrb_value obj, apr_global_mutex_t *unboxed);

void
mruby_gift_apr_global_mutex_t_data_ptr(mrb_value obj, apr_global_mutex_t *unboxed);

apr_global_mutex_t *
mruby_unbox_apr_global_mutex_t(mrb_value boxed);
#endif
/* MRUBY_BINDING_END */

/* MRUBY_BINDING: Hdtr::boxing_decls */
/* sha: 42950747f929080d2614d7aca3808675eac22b412f46a9364971ad11a744c0c0 */
#if BIND_Hdtr_TYPE
mrb_value
mruby_box_apr_hdtr_t(mrb_state* mrb, apr_hdtr_t *unboxed);

mrb_value
mruby_giftwrap_apr_hdtr_t(mrb_state* mrb, apr_hdtr_t *unboxed);

void
mruby_set_apr_hdtr_t_data_ptr(mrb_value obj, apr_hdtr_t *unboxed);

void
mruby_gift_apr_hdtr_t_data_ptr(mrb_value obj, apr_hdtr_t *unboxed);

apr_hdtr_t *
mruby_unbox_apr_hdtr_t(mrb_value boxed);
#endif
/* MRUBY_BINDING_END */

/* MRUBY_BINDING: Ipsubnet::boxing_decls */
/* sha: ddbd817a93680b8554fc1a6ef40e3de6ab986467fb9794917c45a4c7bcb30a89 */
#if BIND_Ipsubnet_TYPE
mrb_value
mruby_box_apr_ipsubnet_t(mrb_state* mrb, apr_ipsubnet_t *unboxed);

mrb_value
mruby_giftwrap_apr_ipsubnet_t(mrb_state* mrb, apr_ipsubnet_t *unboxed);

void
mruby_set_apr_ipsubnet_t_data_ptr(mrb_value obj, apr_ipsubnet_t *unboxed);

void
mruby_gift_apr_ipsubnet_t_data_ptr(mrb_value obj, apr_ipsubnet_t *unboxed);

apr_ipsubnet_t *
mruby_unbox_apr_ipsubnet_t(mrb_value boxed);
#endif
/* MRUBY_BINDING_END */

/* MRUBY_BINDING: OtherChildRec::boxing_decls */
/* sha: eb749e826ba45445cf958c4c20fa58680d63aa61abee00abf60c3362c981b5df */
#if BIND_OtherChildRec_TYPE
mrb_value
mruby_box_apr_other_child_rec_t(mrb_state* mrb, apr_other_child_rec_t *unboxed);

mrb_value
mruby_giftwrap_apr_other_child_rec_t(mrb_state* mrb, apr_other_child_rec_t *unboxed);

void
mruby_set_apr_other_child_rec_t_data_ptr(mrb_value obj, apr_other_child_rec_t *unboxed);

void
mruby_gift_apr_other_child_rec_t_data_ptr(mrb_value obj, apr_other_child_rec_t *unboxed);

apr_other_child_rec_t *
mruby_unbox_apr_other_child_rec_t(mrb_value boxed);
#endif
/* MRUBY_BINDING_END */

/* MRUBY_BINDING: Pool::boxing_decls */
/* sha: 9e10993189d7b7cc24cffd37a66ee62a3f5114798c5fdcb4e991740f4746c0eb */
#if BIND_Pool_TYPE
mrb_value
mruby_box_apr_pool_t(mrb_state* mrb, apr_pool_t *unboxed);

mrb_value
mruby_giftwrap_apr_pool_t(mrb_state* mrb, apr_pool_t *unboxed);

void
mruby_set_apr_pool_t_data_ptr(mrb_value obj, apr_pool_t *unboxed);

void
mruby_gift_apr_pool_t_data_ptr(mrb_value obj, apr_pool_t *unboxed);

apr_pool_t *
mruby_unbox_apr_pool_t(mrb_value boxed);
#endif
/* MRUBY_BINDING_END */

/* MRUBY_BINDING: Proc::boxing_decls */
/* sha: 4b2dfe6258278c53b1fdd41275ae665d45e68555a2cbe9251d5618b5bffe5dc7 */
#if BIND_Proc_TYPE
mrb_value
mruby_box_apr_proc_t(mrb_state* mrb, apr_proc_t *unboxed);

mrb_value
mruby_giftwrap_apr_proc_t(mrb_state* mrb, apr_proc_t *unboxed);

void
mruby_set_apr_proc_t_data_ptr(mrb_value obj, apr_proc_t *unboxed);

void
mruby_gift_apr_proc_t_data_ptr(mrb_value obj, apr_proc_t *unboxed);

apr_proc_t *
mruby_unbox_apr_proc_t(mrb_value boxed);
#endif
/* MRUBY_BINDING_END */

/* MRUBY_BINDING: Procattr::boxing_decls */
/* sha: 3b9e038601bf409c7c0f5826aa681b4c9451c87a6a157820ae2db9953c700839 */
#if BIND_Procattr_TYPE
mrb_value
mruby_box_apr_procattr_t(mrb_state* mrb, apr_procattr_t *unboxed);

mrb_value
mruby_giftwrap_apr_procattr_t(mrb_state* mrb, apr_procattr_t *unboxed);

void
mruby_set_apr_procattr_t_data_ptr(mrb_value obj, apr_procattr_t *unboxed);

void
mruby_gift_apr_procattr_t_data_ptr(mrb_value obj, apr_procattr_t *unboxed);

apr_procattr_t *
mruby_unbox_apr_procattr_t(mrb_value boxed);
#endif
/* MRUBY_BINDING_END */

/* MRUBY_BINDING: ProcMutex::boxing_decls */
/* sha: 6ea1d894b2a128cbc5f9716273a5e4b18f6c7f001c57a12b24eb9ec7820027db */
#if BIND_ProcMutex_TYPE
mrb_value
mruby_box_apr_proc_mutex_t(mrb_state* mrb, apr_proc_mutex_t *unboxed);

mrb_value
mruby_giftwrap_apr_proc_mutex_t(mrb_state* mrb, apr_proc_mutex_t *unboxed);

void
mruby_set_apr_proc_mutex_t_data_ptr(mrb_value obj, apr_proc_mutex_t *unboxed);

void
mruby_gift_apr_proc_mutex_t_data_ptr(mrb_value obj, apr_proc_mutex_t *unboxed);

apr_proc_mutex_t *
mruby_unbox_apr_proc_mutex_t(mrb_value boxed);
#endif
/* MRUBY_BINDING_END */

/* MRUBY_BINDING: Sockaddr::boxing_decls */
/* sha: 7ae9c964a377c6fd4ad4dd237b6ed873024f3d18fa4c1124a8d0f10409565d1c */
#if BIND_Sockaddr_TYPE
mrb_value
mruby_box_apr_sockaddr_t(mrb_state* mrb, apr_sockaddr_t *unboxed);

mrb_value
mruby_giftwrap_apr_sockaddr_t(mrb_state* mrb, apr_sockaddr_t *unboxed);

void
mruby_set_apr_sockaddr_t_data_ptr(mrb_value obj, apr_sockaddr_t *unboxed);

void
mruby_gift_apr_sockaddr_t_data_ptr(mrb_value obj, apr_sockaddr_t *unboxed);

apr_sockaddr_t *
mruby_unbox_apr_sockaddr_t(mrb_value boxed);
#endif
/* MRUBY_BINDING_END */

/* MRUBY_BINDING: Socket::boxing_decls */
/* sha: a0f2a39c85fb554f2c7fd1a3ba9306bc6a9627e9428da88cf623f30100ae9e3d */
#if BIND_Socket_TYPE
mrb_value
mruby_box_apr_socket_t(mrb_state* mrb, apr_socket_t *unboxed);

mrb_value
mruby_giftwrap_apr_socket_t(mrb_state* mrb, apr_socket_t *unboxed);

void
mruby_set_apr_socket_t_data_ptr(mrb_value obj, apr_socket_t *unboxed);

void
mruby_gift_apr_socket_t_data_ptr(mrb_value obj, apr_socket_t *unboxed);

apr_socket_t *
mruby_unbox_apr_socket_t(mrb_value boxed);
#endif
/* MRUBY_BINDING_END */

/* MRUBY_BINDING: Thread::boxing_decls */
/* sha: 41f60f28b56d2ad17750fdde451b61c40c6dbf0d8a908a2b6e64d8937388c686 */
#if BIND_Thread_TYPE
mrb_value
mruby_box_apr_thread_t(mrb_state* mrb, apr_thread_t *unboxed);

mrb_value
mruby_giftwrap_apr_thread_t(mrb_state* mrb, apr_thread_t *unboxed);

void
mruby_set_apr_thread_t_data_ptr(mrb_value obj, apr_thread_t *unboxed);

void
mruby_gift_apr_thread_t_data_ptr(mrb_value obj, apr_thread_t *unboxed);

apr_thread_t *
mruby_unbox_apr_thread_t(mrb_value boxed);
#endif
/* MRUBY_BINDING_END */

/* MRUBY_BINDING: Threadattr::boxing_decls */
/* sha: 86ed610b2fb972d4a1ae859854d9344544f7f688a3f7620229d66a537ae3d70c */
#if BIND_Threadattr_TYPE
mrb_value
mruby_box_apr_threadattr_t(mrb_state* mrb, apr_threadattr_t *unboxed);

mrb_value
mruby_giftwrap_apr_threadattr_t(mrb_state* mrb, apr_threadattr_t *unboxed);

void
mruby_set_apr_threadattr_t_data_ptr(mrb_value obj, apr_threadattr_t *unboxed);

void
mruby_gift_apr_threadattr_t_data_ptr(mrb_value obj, apr_threadattr_t *unboxed);

apr_threadattr_t *
mruby_unbox_apr_threadattr_t(mrb_value boxed);
#endif
/* MRUBY_BINDING_END */

/* MRUBY_BINDING: Threadkey::boxing_decls */
/* sha: eb8748cd4e91d7aa2dfcbf60cab35f5b1aaf8c4a9a5b2c231ddf5bcce7d52276 */
#if BIND_Threadkey_TYPE
mrb_value
mruby_box_apr_threadkey_t(mrb_state* mrb, apr_threadkey_t *unboxed);

mrb_value
mruby_giftwrap_apr_threadkey_t(mrb_state* mrb, apr_threadkey_t *unboxed);

void
mruby_set_apr_threadkey_t_data_ptr(mrb_value obj, apr_threadkey_t *unboxed);

void
mruby_gift_apr_threadkey_t_data_ptr(mrb_value obj, apr_threadkey_t *unboxed);

apr_threadkey_t *
mruby_unbox_apr_threadkey_t(mrb_value boxed);
#endif
/* MRUBY_BINDING_END */

/* MRUBY_BINDING: ThreadOnce::boxing_decls */
/* sha: beb2f8117043e0acbf1575a23daff6b7872bee63ae13b0d64f89afd64e1b8ca5 */
#if BIND_ThreadOnce_TYPE
mrb_value
mruby_box_apr_thread_once_t(mrb_state* mrb, apr_thread_once_t *unboxed);

mrb_value
mruby_giftwrap_apr_thread_once_t(mrb_state* mrb, apr_thread_once_t *unboxed);

void
mruby_set_apr_thread_once_t_data_ptr(mrb_value obj, apr_thread_once_t *unboxed);

void
mruby_gift_apr_thread_once_t_data_ptr(mrb_value obj, apr_thread_once_t *unboxed);

apr_thread_once_t *
mruby_unbox_apr_thread_once_t(mrb_value boxed);
#endif
/* MRUBY_BINDING_END */

/* MRUBY_BINDING: TimeExp::boxing_decls */
/* sha: 2e727f97d43d19cb368036d03a74b99bbef39251511c017d0c0a7003e6ca2c79 */
#if BIND_TimeExp_TYPE
mrb_value
mruby_box_apr_time_exp_t(mrb_state* mrb, apr_time_exp_t *unboxed);

mrb_value
mruby_giftwrap_apr_time_exp_t(mrb_state* mrb, apr_time_exp_t *unboxed);

void
mruby_set_apr_time_exp_t_data_ptr(mrb_value obj, apr_time_exp_t *unboxed);

void
mruby_gift_apr_time_exp_t_data_ptr(mrb_value obj, apr_time_exp_t *unboxed);

apr_time_exp_t *
mruby_unbox_apr_time_exp_t(mrb_value boxed);
#endif
/* MRUBY_BINDING_END */

/* MRUBY_BINDING: footer */
/* sha: user_defined */

/* MRUBY_BINDING_END */

#endif
