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

/* MRUBY_BINDING: AprDirT::boxing_decls */
/* sha: 954d7879d27bbaa0306426d5283a30566cc15fa27ac4838b25a68ee14348d807 */
#if BIND_AprDirT_TYPE
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

/* MRUBY_BINDING: AprFileT::boxing_decls */
/* sha: 3e3f9ba4785ad05341a74f8994394b3d54b7438b15723e666f9567ce6223acfa */
#if BIND_AprFileT_TYPE
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

/* MRUBY_BINDING: AprFinfoT::boxing_decls */
/* sha: 7de759ae8b88e9f68254f42cf9bfb83210cd3d9fa257dc79add32cb6c1b201f8 */
#if BIND_AprFinfoT_TYPE
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

/* MRUBY_BINDING: AprGlobalMutexT::boxing_decls */
/* sha: 1f1ace420e378b9ef717cdd25d53f1e39d24371859a71fafb84299e7890073be */
#if BIND_AprGlobalMutexT_TYPE
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

/* MRUBY_BINDING: AprHdtrT::boxing_decls */
/* sha: aac1c8d14df06772e5e7fb39470533c26bbc5cb7f9f6cac1045710c7612a7b17 */
#if BIND_AprHdtrT_TYPE
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

/* MRUBY_BINDING: AprIpsubnetT::boxing_decls */
/* sha: d8f1561216cd98b95ac7445e5cf2149ba5c6c7ab469fd8b4d01782fc55445d17 */
#if BIND_AprIpsubnetT_TYPE
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

/* MRUBY_BINDING: AprOtherChildRecT::boxing_decls */
/* sha: deffc57d3fac412ab8d58cafbfaec9330d1b148cadbe350af0ed012bda7a3299 */
#if BIND_AprOtherChildRecT_TYPE
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

/* MRUBY_BINDING: AprPoolT::boxing_decls */
/* sha: ff483d0b0dd76af6ecc74d2db56ea3ae070571f8bab3bac4d594d6cfdcf266e9 */
#if BIND_AprPoolT_TYPE
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

/* MRUBY_BINDING: AprProcattrT::boxing_decls */
/* sha: c5eee51349df8db759cbe7970c9e1ad42edf5bb7889145b7a2924d9cf688f925 */
#if BIND_AprProcattrT_TYPE
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

/* MRUBY_BINDING: AprProcMutexT::boxing_decls */
/* sha: 4d7c58cf258fa974193bee529b43e2e94122d4736093ad802f0890645cd60d9a */
#if BIND_AprProcMutexT_TYPE
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

/* MRUBY_BINDING: AprProcT::boxing_decls */
/* sha: 794db237de393aaba45247a92f34a608d11551543b64c8cce03ac76f3eb91557 */
#if BIND_AprProcT_TYPE
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

/* MRUBY_BINDING: AprSockaddrT::boxing_decls */
/* sha: 8d75a59b4a6a6689447136ef1bdf8d3bb1bf77beedd017e3ec331f79f1f155c2 */
#if BIND_AprSockaddrT_TYPE
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

/* MRUBY_BINDING: AprSocketT::boxing_decls */
/* sha: 055d43e9cd966e5037cb9c2bafbafb16503aa2ce4ec3e8f7a650d33cd5b65d86 */
#if BIND_AprSocketT_TYPE
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

/* MRUBY_BINDING: AprThreadattrT::boxing_decls */
/* sha: 0949b6c3ae28bae4ff29450d6e2f7240597537d6d06d5c7a7b7088999e307138 */
#if BIND_AprThreadattrT_TYPE
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

/* MRUBY_BINDING: AprThreadkeyT::boxing_decls */
/* sha: d7ac20d528290c6a2fcccd0260f83f0e335be4c718e2411f7124f687d0eff8aa */
#if BIND_AprThreadkeyT_TYPE
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

/* MRUBY_BINDING: AprThreadOnceT::boxing_decls */
/* sha: fe2634ae49017e3ff93f6a424e0211625db195b724c74156cf3e6b6602f46261 */
#if BIND_AprThreadOnceT_TYPE
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

/* MRUBY_BINDING: AprThreadT::boxing_decls */
/* sha: 37feb80f45f4ccf45d1895f8c04aa065e2884e0a55341c8607bddf2d88644db1 */
#if BIND_AprThreadT_TYPE
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

/* MRUBY_BINDING: AprTimeExpT::boxing_decls */
/* sha: 62e78fd9c4e4a823d0e664f3a0aa44fe69a0b44f4e2680685dec6e0b7f512160 */
#if BIND_AprTimeExpT_TYPE
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
