/*
 * apr_finfo_t
 * Defined in file apr_file_info.h @ line 143
 */

#include "mruby_APR.h"

#if BIND_AprFinfoT_TYPE

/* MRUBY_BINDING: header */
/* sha: user_defined */

/* MRUBY_BINDING_END */

/* MRUBY_BINDING: AprFinfoT::initialize */
/* sha: de2f12052816683d9afd1963d40b81b41cc25bbe86dae3888389377e59a40217 */
#if BIND_AprFinfoT_INITIALIZE
mrb_value
mrb_APR_AprFinfoT_initialize(mrb_state* mrb, mrb_value self) {
  mrb_raise(mrb, E_NOMETHOD_ERROR, "No initializer defined");
/* 
  apr_finfo_t* native_object = (apr_finfo_t*)calloc(1, sizeof(apr_finfo_t));
  mruby_gift_apr_finfo_t_data_ptr(self, native_object);
  return self;
*/
}
#endif
/* MRUBY_BINDING_END */

/*
 * Fields
 */

/* MRUBY_BINDING: AprFinfoT::pool_reader */
/* sha: deb48401d27c4a24aa53763d150a61e8875136e35cf375e1bafb88b645f8c150 */
#if BIND_AprFinfoT_pool_FIELD_READER
mrb_value
mrb_APR_AprFinfoT_get_pool(mrb_state* mrb, mrb_value self) {
  apr_finfo_t * native_self = mruby_unbox_apr_finfo_t(self);

  apr_pool_t * native_pool = native_self->pool;

  mrb_value pool = (native_pool == NULL ? mrb_nil_value() : mruby_box_apr_pool_t(mrb, native_pool));

  return pool;
}
#endif
/* MRUBY_BINDING_END */

/* MRUBY_BINDING: AprFinfoT::pool_writer */
/* sha: a2626aa312c96f8e2299071fa86bce981114c34303df264cb4a3d2d38eda111c */
#if BIND_AprFinfoT_pool_FIELD_WRITER
mrb_value
mrb_APR_AprFinfoT_set_pool(mrb_state* mrb, mrb_value self) {
  apr_finfo_t * native_self = mruby_unbox_apr_finfo_t(self);
  mrb_value pool;

  mrb_get_args(mrb, "o", &pool);

  /* type checking */
  if (!mrb_obj_is_kind_of(mrb, pool, AprPoolT_class(mrb))) {
    mrb_raise(mrb, E_TYPE_ERROR, "AprPoolT expected");
    return mrb_nil_value();
  }

  apr_pool_t * native_pool = (mrb_nil_p(pool) ? NULL : mruby_unbox_apr_pool_t(pool));

  native_self->pool = native_pool;
  
  mrb_value value_as_mrb_value;
  mrb_get_args(mrb, "o", &value_as_mrb_value);
  return value_as_mrb_value;
}
#endif
/* MRUBY_BINDING_END */

/* MRUBY_BINDING: AprFinfoT::valid_reader */
/* sha: feec72f320bc7004e58d7d1038658a38aa3665ea48fbc6a3e2c4e7ac62b15458 */
#if BIND_AprFinfoT_valid_FIELD_READER
mrb_value
mrb_APR_AprFinfoT_get_valid(mrb_state* mrb, mrb_value self) {
  apr_finfo_t * native_self = mruby_unbox_apr_finfo_t(self);

  apr_int32_t native_valid = native_self->valid;

  mrb_value valid = mrb_fixnum_value(native_valid);

  return valid;
}
#endif
/* MRUBY_BINDING_END */

/* MRUBY_BINDING: AprFinfoT::valid_writer */
/* sha: c3fb31044b2c19742960aa99e49cc53e0f9e438c8f81ccd3d2880b72caf688b5 */
#if BIND_AprFinfoT_valid_FIELD_WRITER
mrb_value
mrb_APR_AprFinfoT_set_valid(mrb_state* mrb, mrb_value self) {
  apr_finfo_t * native_self = mruby_unbox_apr_finfo_t(self);
  mrb_int native_valid;

  mrb_get_args(mrb, "i", &native_valid);

  native_self->valid = native_valid;
  
  mrb_value value_as_mrb_value;
  mrb_get_args(mrb, "o", &value_as_mrb_value);
  return value_as_mrb_value;
}
#endif
/* MRUBY_BINDING_END */

/* MRUBY_BINDING: AprFinfoT::protection_reader */
/* sha: 1af28f33e36554d99eaabab41faf6d2e88699892f465c5c6fc335bdf3b78c0e9 */
#if BIND_AprFinfoT_protection_FIELD_READER
mrb_value
mrb_APR_AprFinfoT_get_protection(mrb_state* mrb, mrb_value self) {
  apr_finfo_t * native_self = mruby_unbox_apr_finfo_t(self);

  apr_fileperms_t native_protection = native_self->protection;

  mrb_value protection = mrb_fixnum_value(native_protection);

  return protection;
}
#endif
/* MRUBY_BINDING_END */

/* MRUBY_BINDING: AprFinfoT::protection_writer */
/* sha: d9e624715ad3517e7ac305d192310a64c9748f75628be12128011c1cbad90ab4 */
#if BIND_AprFinfoT_protection_FIELD_WRITER
mrb_value
mrb_APR_AprFinfoT_set_protection(mrb_state* mrb, mrb_value self) {
  apr_finfo_t * native_self = mruby_unbox_apr_finfo_t(self);
  mrb_int native_protection;

  mrb_get_args(mrb, "i", &native_protection);

  native_self->protection = native_protection;
  
  mrb_value value_as_mrb_value;
  mrb_get_args(mrb, "o", &value_as_mrb_value);
  return value_as_mrb_value;
}
#endif
/* MRUBY_BINDING_END */

/* MRUBY_BINDING: AprFinfoT::filetype_reader */
/* sha: 32f5534f9a83925d8663a20596613784a1f9075d41c9614667b5aa7a46a7f62a */
#if BIND_AprFinfoT_filetype_FIELD_READER
mrb_value
mrb_APR_AprFinfoT_get_filetype(mrb_state* mrb, mrb_value self) {
  apr_finfo_t * native_self = mruby_unbox_apr_finfo_t(self);

  apr_filetype_e native_filetype = native_self->filetype;

  mrb_value filetype = mrb_fixnum_value(native_filetype);

  return filetype;
}
#endif
/* MRUBY_BINDING_END */

/* MRUBY_BINDING: AprFinfoT::filetype_writer */
/* sha: 7f1a825798e3f21e0c1eb0a4c88b5a0f27090c557f728e566a302b2afe657203 */
#if BIND_AprFinfoT_filetype_FIELD_WRITER
mrb_value
mrb_APR_AprFinfoT_set_filetype(mrb_state* mrb, mrb_value self) {
  apr_finfo_t * native_self = mruby_unbox_apr_finfo_t(self);
  mrb_int native_filetype;

  mrb_get_args(mrb, "i", &native_filetype);

  native_self->filetype = native_filetype;
  
  mrb_value value_as_mrb_value;
  mrb_get_args(mrb, "o", &value_as_mrb_value);
  return value_as_mrb_value;
}
#endif
/* MRUBY_BINDING_END */

/* MRUBY_BINDING: AprFinfoT::user_reader */
/* sha: 428abea1a6abe0576f084561663fdd66c5998a42a5a2b1a9f9a118fa5bcf5fbe */
#if BIND_AprFinfoT_user_FIELD_READER
mrb_value
mrb_APR_AprFinfoT_get_user(mrb_state* mrb, mrb_value self) {
  apr_finfo_t * native_self = mruby_unbox_apr_finfo_t(self);

  apr_uid_t native_user = native_self->user;

  mrb_value user = TODO_mruby_box_apr_uid_t(mrb, native_user);

  return user;
}
#endif
/* MRUBY_BINDING_END */

/* MRUBY_BINDING: AprFinfoT::user_writer */
/* sha: 28793d59b80132399bd894715c6a44122db6ce3091c05e4ef7f07032babd708f */
#if BIND_AprFinfoT_user_FIELD_WRITER
mrb_value
mrb_APR_AprFinfoT_set_user(mrb_state* mrb, mrb_value self) {
  apr_finfo_t * native_self = mruby_unbox_apr_finfo_t(self);
  mrb_value user;

  mrb_get_args(mrb, "o", &user);

  /* type checking */
  TODO_type_check_apr_uid_t(user);

  apr_uid_t native_user = TODO_mruby_unbox_apr_uid_t(user);

  native_self->user = native_user;
  
  mrb_value value_as_mrb_value;
  mrb_get_args(mrb, "o", &value_as_mrb_value);
  return value_as_mrb_value;
}
#endif
/* MRUBY_BINDING_END */

/* MRUBY_BINDING: AprFinfoT::group_reader */
/* sha: 2a78ebea23ba1bd88db4ed59328df46ee8c10c72cc4de71fde3cd8fc78692ea5 */
#if BIND_AprFinfoT_group_FIELD_READER
mrb_value
mrb_APR_AprFinfoT_get_group(mrb_state* mrb, mrb_value self) {
  apr_finfo_t * native_self = mruby_unbox_apr_finfo_t(self);

  apr_gid_t native_group = native_self->group;

  mrb_value group = TODO_mruby_box_apr_gid_t(mrb, native_group);

  return group;
}
#endif
/* MRUBY_BINDING_END */

/* MRUBY_BINDING: AprFinfoT::group_writer */
/* sha: b874663d70d221daef769062f1e20f702ef287b89574595f566a3fb9bcf65690 */
#if BIND_AprFinfoT_group_FIELD_WRITER
mrb_value
mrb_APR_AprFinfoT_set_group(mrb_state* mrb, mrb_value self) {
  apr_finfo_t * native_self = mruby_unbox_apr_finfo_t(self);
  mrb_value group;

  mrb_get_args(mrb, "o", &group);

  /* type checking */
  TODO_type_check_apr_gid_t(group);

  apr_gid_t native_group = TODO_mruby_unbox_apr_gid_t(group);

  native_self->group = native_group;
  
  mrb_value value_as_mrb_value;
  mrb_get_args(mrb, "o", &value_as_mrb_value);
  return value_as_mrb_value;
}
#endif
/* MRUBY_BINDING_END */

/* MRUBY_BINDING: AprFinfoT::inode_reader */
/* sha: e1e169cd624f29b5b830e1bb27e5a525d5796f59b947e1bb074bc3a6d1428438 */
#if BIND_AprFinfoT_inode_FIELD_READER
mrb_value
mrb_APR_AprFinfoT_get_inode(mrb_state* mrb, mrb_value self) {
  apr_finfo_t * native_self = mruby_unbox_apr_finfo_t(self);

  apr_ino_t native_inode = native_self->inode;

  mrb_value inode = TODO_mruby_box_apr_ino_t(mrb, native_inode);

  return inode;
}
#endif
/* MRUBY_BINDING_END */

/* MRUBY_BINDING: AprFinfoT::inode_writer */
/* sha: 8d23761da53b1ea94b76577156a116eceba170a7aea93c515c52a69dab45885f */
#if BIND_AprFinfoT_inode_FIELD_WRITER
mrb_value
mrb_APR_AprFinfoT_set_inode(mrb_state* mrb, mrb_value self) {
  apr_finfo_t * native_self = mruby_unbox_apr_finfo_t(self);
  mrb_value inode;

  mrb_get_args(mrb, "o", &inode);

  /* type checking */
  TODO_type_check_apr_ino_t(inode);

  apr_ino_t native_inode = TODO_mruby_unbox_apr_ino_t(inode);

  native_self->inode = native_inode;
  
  mrb_value value_as_mrb_value;
  mrb_get_args(mrb, "o", &value_as_mrb_value);
  return value_as_mrb_value;
}
#endif
/* MRUBY_BINDING_END */

/* MRUBY_BINDING: AprFinfoT::device_reader */
/* sha: a285afd8545c29ad5c1db95219d505dd9216c93362d6cc80927b652052949058 */
#if BIND_AprFinfoT_device_FIELD_READER
mrb_value
mrb_APR_AprFinfoT_get_device(mrb_state* mrb, mrb_value self) {
  apr_finfo_t * native_self = mruby_unbox_apr_finfo_t(self);

  apr_dev_t native_device = native_self->device;

  mrb_value device = TODO_mruby_box_apr_dev_t(mrb, native_device);

  return device;
}
#endif
/* MRUBY_BINDING_END */

/* MRUBY_BINDING: AprFinfoT::device_writer */
/* sha: eafb6f50b835dd731f7de595740da3eb7e3e587c08fc8a6e4d4c2df92b58cb84 */
#if BIND_AprFinfoT_device_FIELD_WRITER
mrb_value
mrb_APR_AprFinfoT_set_device(mrb_state* mrb, mrb_value self) {
  apr_finfo_t * native_self = mruby_unbox_apr_finfo_t(self);
  mrb_value device;

  mrb_get_args(mrb, "o", &device);

  /* type checking */
  TODO_type_check_apr_dev_t(device);

  apr_dev_t native_device = TODO_mruby_unbox_apr_dev_t(device);

  native_self->device = native_device;
  
  mrb_value value_as_mrb_value;
  mrb_get_args(mrb, "o", &value_as_mrb_value);
  return value_as_mrb_value;
}
#endif
/* MRUBY_BINDING_END */

/* MRUBY_BINDING: AprFinfoT::nlink_reader */
/* sha: 347ce1c5305d83e43a3fabf5d72402bfcacb9a66856fef10e22a6c0478d108b2 */
#if BIND_AprFinfoT_nlink_FIELD_READER
mrb_value
mrb_APR_AprFinfoT_get_nlink(mrb_state* mrb, mrb_value self) {
  apr_finfo_t * native_self = mruby_unbox_apr_finfo_t(self);

  apr_int32_t native_nlink = native_self->nlink;

  mrb_value nlink = mrb_fixnum_value(native_nlink);

  return nlink;
}
#endif
/* MRUBY_BINDING_END */

/* MRUBY_BINDING: AprFinfoT::nlink_writer */
/* sha: fe9641f8f6ce64cd1cdbc7effb3efdf5ec89fe61d064fcb4f1bcb8dfd1cfb4d8 */
#if BIND_AprFinfoT_nlink_FIELD_WRITER
mrb_value
mrb_APR_AprFinfoT_set_nlink(mrb_state* mrb, mrb_value self) {
  apr_finfo_t * native_self = mruby_unbox_apr_finfo_t(self);
  mrb_int native_nlink;

  mrb_get_args(mrb, "i", &native_nlink);

  native_self->nlink = native_nlink;
  
  mrb_value value_as_mrb_value;
  mrb_get_args(mrb, "o", &value_as_mrb_value);
  return value_as_mrb_value;
}
#endif
/* MRUBY_BINDING_END */

/* MRUBY_BINDING: AprFinfoT::size_reader */
/* sha: 2c9029d5f130e97f989c34a36e1ec4464c1256d8b3a4897ca9ae2cdd79396011 */
#if BIND_AprFinfoT_size_FIELD_READER
mrb_value
mrb_APR_AprFinfoT_get_size(mrb_state* mrb, mrb_value self) {
  apr_finfo_t * native_self = mruby_unbox_apr_finfo_t(self);

  apr_off_t native_size = native_self->size;

  mrb_value size = TODO_mruby_box_apr_off_t(mrb, native_size);

  return size;
}
#endif
/* MRUBY_BINDING_END */

/* MRUBY_BINDING: AprFinfoT::size_writer */
/* sha: 5b3656f96794babffd0a3fdeae9df9a805736c0ed2d93e98d7f77cf31d990fbe */
#if BIND_AprFinfoT_size_FIELD_WRITER
mrb_value
mrb_APR_AprFinfoT_set_size(mrb_state* mrb, mrb_value self) {
  apr_finfo_t * native_self = mruby_unbox_apr_finfo_t(self);
  mrb_value size;

  mrb_get_args(mrb, "o", &size);

  /* type checking */
  TODO_type_check_apr_off_t(size);

  apr_off_t native_size = TODO_mruby_unbox_apr_off_t(size);

  native_self->size = native_size;
  
  mrb_value value_as_mrb_value;
  mrb_get_args(mrb, "o", &value_as_mrb_value);
  return value_as_mrb_value;
}
#endif
/* MRUBY_BINDING_END */

/* MRUBY_BINDING: AprFinfoT::csize_reader */
/* sha: b0e1e25e95a2bebdba4a9a3027433e5b9574c4b269aa2e9aa5100b17362b743c */
#if BIND_AprFinfoT_csize_FIELD_READER
mrb_value
mrb_APR_AprFinfoT_get_csize(mrb_state* mrb, mrb_value self) {
  apr_finfo_t * native_self = mruby_unbox_apr_finfo_t(self);

  apr_off_t native_csize = native_self->csize;

  mrb_value csize = TODO_mruby_box_apr_off_t(mrb, native_csize);

  return csize;
}
#endif
/* MRUBY_BINDING_END */

/* MRUBY_BINDING: AprFinfoT::csize_writer */
/* sha: 3369cd4d06957ffa7bd658a7af7de384e1fb5c111ef43230cb358b0d33bc31f8 */
#if BIND_AprFinfoT_csize_FIELD_WRITER
mrb_value
mrb_APR_AprFinfoT_set_csize(mrb_state* mrb, mrb_value self) {
  apr_finfo_t * native_self = mruby_unbox_apr_finfo_t(self);
  mrb_value csize;

  mrb_get_args(mrb, "o", &csize);

  /* type checking */
  TODO_type_check_apr_off_t(csize);

  apr_off_t native_csize = TODO_mruby_unbox_apr_off_t(csize);

  native_self->csize = native_csize;
  
  mrb_value value_as_mrb_value;
  mrb_get_args(mrb, "o", &value_as_mrb_value);
  return value_as_mrb_value;
}
#endif
/* MRUBY_BINDING_END */

/* MRUBY_BINDING: AprFinfoT::atime_reader */
/* sha: 5bfd63209dc1f5c39de30dbea287e25d4f1ad238c57e2d41204c66ccf6fba02e */
#if BIND_AprFinfoT_atime_FIELD_READER
mrb_value
mrb_APR_AprFinfoT_get_atime(mrb_state* mrb, mrb_value self) {
  apr_finfo_t * native_self = mruby_unbox_apr_finfo_t(self);

  apr_time_t native_atime = native_self->atime;

  mrb_value atime = TODO_mruby_box_apr_time_t(mrb, native_atime);

  return atime;
}
#endif
/* MRUBY_BINDING_END */

/* MRUBY_BINDING: AprFinfoT::atime_writer */
/* sha: f302f80acaaadec45dadd235885c50c7e3647386a21bf88474dd5fcb6c8d27cc */
#if BIND_AprFinfoT_atime_FIELD_WRITER
mrb_value
mrb_APR_AprFinfoT_set_atime(mrb_state* mrb, mrb_value self) {
  apr_finfo_t * native_self = mruby_unbox_apr_finfo_t(self);
  mrb_value atime;

  mrb_get_args(mrb, "o", &atime);

  /* type checking */
  TODO_type_check_apr_time_t(atime);

  apr_time_t native_atime = TODO_mruby_unbox_apr_time_t(atime);

  native_self->atime = native_atime;
  
  mrb_value value_as_mrb_value;
  mrb_get_args(mrb, "o", &value_as_mrb_value);
  return value_as_mrb_value;
}
#endif
/* MRUBY_BINDING_END */

/* MRUBY_BINDING: AprFinfoT::mtime_reader */
/* sha: 82cc292a71028f08658949e3eea4a6d359459c6563e1be08aa4ad8fa621ecaa2 */
#if BIND_AprFinfoT_mtime_FIELD_READER
mrb_value
mrb_APR_AprFinfoT_get_mtime(mrb_state* mrb, mrb_value self) {
  apr_finfo_t * native_self = mruby_unbox_apr_finfo_t(self);

  apr_time_t native_mtime = native_self->mtime;

  mrb_value mtime = TODO_mruby_box_apr_time_t(mrb, native_mtime);

  return mtime;
}
#endif
/* MRUBY_BINDING_END */

/* MRUBY_BINDING: AprFinfoT::mtime_writer */
/* sha: fdebed87c8d44ed514a2b4d0c464e72ee34a59b275bbceeb60b4861a7dbfabd5 */
#if BIND_AprFinfoT_mtime_FIELD_WRITER
mrb_value
mrb_APR_AprFinfoT_set_mtime(mrb_state* mrb, mrb_value self) {
  apr_finfo_t * native_self = mruby_unbox_apr_finfo_t(self);
  mrb_value mtime;

  mrb_get_args(mrb, "o", &mtime);

  /* type checking */
  TODO_type_check_apr_time_t(mtime);

  apr_time_t native_mtime = TODO_mruby_unbox_apr_time_t(mtime);

  native_self->mtime = native_mtime;
  
  mrb_value value_as_mrb_value;
  mrb_get_args(mrb, "o", &value_as_mrb_value);
  return value_as_mrb_value;
}
#endif
/* MRUBY_BINDING_END */

/* MRUBY_BINDING: AprFinfoT::ctime_reader */
/* sha: cb7481d986ecbf1e290ef47e331af234c55f12768e78d3e67b3c8276770040ec */
#if BIND_AprFinfoT_ctime_FIELD_READER
mrb_value
mrb_APR_AprFinfoT_get_ctime(mrb_state* mrb, mrb_value self) {
  apr_finfo_t * native_self = mruby_unbox_apr_finfo_t(self);

  apr_time_t native_ctime = native_self->ctime;

  mrb_value ctime = TODO_mruby_box_apr_time_t(mrb, native_ctime);

  return ctime;
}
#endif
/* MRUBY_BINDING_END */

/* MRUBY_BINDING: AprFinfoT::ctime_writer */
/* sha: 5a16b39d84f297c17ea2295070b2b442fbd90aea6e313927c9bf415aacc0f827 */
#if BIND_AprFinfoT_ctime_FIELD_WRITER
mrb_value
mrb_APR_AprFinfoT_set_ctime(mrb_state* mrb, mrb_value self) {
  apr_finfo_t * native_self = mruby_unbox_apr_finfo_t(self);
  mrb_value ctime;

  mrb_get_args(mrb, "o", &ctime);

  /* type checking */
  TODO_type_check_apr_time_t(ctime);

  apr_time_t native_ctime = TODO_mruby_unbox_apr_time_t(ctime);

  native_self->ctime = native_ctime;
  
  mrb_value value_as_mrb_value;
  mrb_get_args(mrb, "o", &value_as_mrb_value);
  return value_as_mrb_value;
}
#endif
/* MRUBY_BINDING_END */

/* MRUBY_BINDING: AprFinfoT::fname_reader */
/* sha: cb06969432cfe6e5b9199a6ba6a9300398dc28c60b8176beb2e14e907eac53aa */
#if BIND_AprFinfoT_fname_FIELD_READER
mrb_value
mrb_APR_AprFinfoT_get_fname(mrb_state* mrb, mrb_value self) {
  apr_finfo_t * native_self = mruby_unbox_apr_finfo_t(self);

  const char * native_fname = native_self->fname;

  mrb_value fname = native_fname == NULL ? mrb_nil_value() : mrb_str_new_cstr(mrb, native_fname);

  return fname;
}
#endif
/* MRUBY_BINDING_END */

/* MRUBY_BINDING: AprFinfoT::fname_writer */
/* sha: cd2c18802b4e765617c897cedc03e7b14262cad2f9e676820cad6b1d3dbf8519 */
#if BIND_AprFinfoT_fname_FIELD_WRITER
mrb_value
mrb_APR_AprFinfoT_set_fname(mrb_state* mrb, mrb_value self) {
  apr_finfo_t * native_self = mruby_unbox_apr_finfo_t(self);
  char * native_fname = NULL;

  mrb_get_args(mrb, "z", &native_fname);

  native_self->fname = native_fname;
  
  mrb_value value_as_mrb_value;
  mrb_get_args(mrb, "o", &value_as_mrb_value);
  return value_as_mrb_value;
}
#endif
/* MRUBY_BINDING_END */

/* MRUBY_BINDING: AprFinfoT::name_reader */
/* sha: be5184a674f04097f421079fa6ca02b14eb6dad93be55c3dedb274d3fecd5574 */
#if BIND_AprFinfoT_name_FIELD_READER
mrb_value
mrb_APR_AprFinfoT_get_name(mrb_state* mrb, mrb_value self) {
  apr_finfo_t * native_self = mruby_unbox_apr_finfo_t(self);

  const char * native_name = native_self->name;

  mrb_value name = native_name == NULL ? mrb_nil_value() : mrb_str_new_cstr(mrb, native_name);

  return name;
}
#endif
/* MRUBY_BINDING_END */

/* MRUBY_BINDING: AprFinfoT::name_writer */
/* sha: 2b6e083e137083feb264587567cb7f7895fe5494c8930a2ad7384c5af3d5937d */
#if BIND_AprFinfoT_name_FIELD_WRITER
mrb_value
mrb_APR_AprFinfoT_set_name(mrb_state* mrb, mrb_value self) {
  apr_finfo_t * native_self = mruby_unbox_apr_finfo_t(self);
  char * native_name = NULL;

  mrb_get_args(mrb, "z", &native_name);

  native_self->name = native_name;
  
  mrb_value value_as_mrb_value;
  mrb_get_args(mrb, "o", &value_as_mrb_value);
  return value_as_mrb_value;
}
#endif
/* MRUBY_BINDING_END */

/* MRUBY_BINDING: AprFinfoT::filehand_reader */
/* sha: 7700ec1844103e52d99291fba8fb361b5087323cd1596685565624ca58214608 */
#if BIND_AprFinfoT_filehand_FIELD_READER
mrb_value
mrb_APR_AprFinfoT_get_filehand(mrb_state* mrb, mrb_value self) {
  apr_finfo_t * native_self = mruby_unbox_apr_finfo_t(self);

  struct apr_file_t * native_filehand = native_self->filehand;

  mrb_value filehand = (native_filehand == NULL ? mrb_nil_value() : mruby_box_apr_file_t(mrb, native_filehand));

  return filehand;
}
#endif
/* MRUBY_BINDING_END */

/* MRUBY_BINDING: AprFinfoT::filehand_writer */
/* sha: 23b262faa6df9132d2eca4ac9e47664798e1d11c44dbed3a8e848d47ddcb26b1 */
#if BIND_AprFinfoT_filehand_FIELD_WRITER
mrb_value
mrb_APR_AprFinfoT_set_filehand(mrb_state* mrb, mrb_value self) {
  apr_finfo_t * native_self = mruby_unbox_apr_finfo_t(self);
  mrb_value filehand;

  mrb_get_args(mrb, "o", &filehand);

  /* type checking */
  if (!mrb_obj_is_kind_of(mrb, filehand, AprFileT_class(mrb))) {
    mrb_raise(mrb, E_TYPE_ERROR, "AprFileT expected");
    return mrb_nil_value();
  }

  struct apr_file_t * native_filehand = (mrb_nil_p(filehand) ? NULL : mruby_unbox_apr_file_t(filehand));

  native_self->filehand = native_filehand;
  
  mrb_value value_as_mrb_value;
  mrb_get_args(mrb, "o", &value_as_mrb_value);
  return value_as_mrb_value;
}
#endif
/* MRUBY_BINDING_END */


void mrb_APR_AprFinfoT_init(mrb_state* mrb) {
  static int initialized = 0;
  if (initialized) return;
  else initialized = 1;

/* MRUBY_BINDING: pre_class_definition */
/* sha: user_defined */

/* MRUBY_BINDING_END */

/* MRUBY_BINDING: AprFinfoT::class_definition */
/* sha: 0c9e647c9efb481c79a77aa217dc79c92dbcd80ec73305bd8c45f7497d0868fe */
  struct RClass* AprFinfoT_class = mrb_define_class_under(mrb, APR_module(mrb), "AprFinfoT", mrb->object_class);
  MRB_SET_INSTANCE_TT(AprFinfoT_class, MRB_TT_DATA);
/* MRUBY_BINDING_END */

/* MRUBY_BINDING: AprFinfoT::pre_class_method_definitions */
/* sha: user_defined */

/* MRUBY_BINDING_END */

/* MRUBY_BINDING: AprFinfoT::class_method_definitions */
/* sha: ed873140c171b6d570fe66289d1602cad1aa705590ffd31e3eaa7e1f1ed5130d */
#if BIND_AprFinfoT_INITIALIZE
  mrb_define_method(mrb, AprFinfoT_class, "initialize", mrb_APR_AprFinfoT_initialize, MRB_ARGS_NONE());
#endif
/* MRUBY_BINDING_END */

/* MRUBY_BINDING: AprFinfoT::pre_attr_definitions */
/* sha: user_defined */

/* MRUBY_BINDING_END */

/* MRUBY_BINDING: AprFinfoT::attr_definitions */
/* sha: 5c181bfaa8250188064de5c23a6b8f97876ab3adffc4db46aaa1a51bc1478a96 */
  /*
   * Fields
   */
#if BIND_AprFinfoT_pool_FIELD_READER
  mrb_define_method(mrb, AprFinfoT_class, "pool", mrb_APR_AprFinfoT_get_pool, MRB_ARGS_ARG(0, 0));
#endif
#if BIND_AprFinfoT_pool_FIELD_WRITER
  mrb_define_method(mrb, AprFinfoT_class, "pool=", mrb_APR_AprFinfoT_set_pool, MRB_ARGS_ARG(1, 0));
#endif
#if BIND_AprFinfoT_valid_FIELD_READER
  mrb_define_method(mrb, AprFinfoT_class, "valid", mrb_APR_AprFinfoT_get_valid, MRB_ARGS_ARG(0, 0));
#endif
#if BIND_AprFinfoT_valid_FIELD_WRITER
  mrb_define_method(mrb, AprFinfoT_class, "valid=", mrb_APR_AprFinfoT_set_valid, MRB_ARGS_ARG(1, 0));
#endif
#if BIND_AprFinfoT_protection_FIELD_READER
  mrb_define_method(mrb, AprFinfoT_class, "protection", mrb_APR_AprFinfoT_get_protection, MRB_ARGS_ARG(0, 0));
#endif
#if BIND_AprFinfoT_protection_FIELD_WRITER
  mrb_define_method(mrb, AprFinfoT_class, "protection=", mrb_APR_AprFinfoT_set_protection, MRB_ARGS_ARG(1, 0));
#endif
#if BIND_AprFinfoT_filetype_FIELD_READER
  mrb_define_method(mrb, AprFinfoT_class, "filetype", mrb_APR_AprFinfoT_get_filetype, MRB_ARGS_ARG(0, 0));
#endif
#if BIND_AprFinfoT_filetype_FIELD_WRITER
  mrb_define_method(mrb, AprFinfoT_class, "filetype=", mrb_APR_AprFinfoT_set_filetype, MRB_ARGS_ARG(1, 0));
#endif
#if BIND_AprFinfoT_user_FIELD_READER
  mrb_define_method(mrb, AprFinfoT_class, "user", mrb_APR_AprFinfoT_get_user, MRB_ARGS_ARG(0, 0));
#endif
#if BIND_AprFinfoT_user_FIELD_WRITER
  mrb_define_method(mrb, AprFinfoT_class, "user=", mrb_APR_AprFinfoT_set_user, MRB_ARGS_ARG(1, 0));
#endif
#if BIND_AprFinfoT_group_FIELD_READER
  mrb_define_method(mrb, AprFinfoT_class, "group", mrb_APR_AprFinfoT_get_group, MRB_ARGS_ARG(0, 0));
#endif
#if BIND_AprFinfoT_group_FIELD_WRITER
  mrb_define_method(mrb, AprFinfoT_class, "group=", mrb_APR_AprFinfoT_set_group, MRB_ARGS_ARG(1, 0));
#endif
#if BIND_AprFinfoT_inode_FIELD_READER
  mrb_define_method(mrb, AprFinfoT_class, "inode", mrb_APR_AprFinfoT_get_inode, MRB_ARGS_ARG(0, 0));
#endif
#if BIND_AprFinfoT_inode_FIELD_WRITER
  mrb_define_method(mrb, AprFinfoT_class, "inode=", mrb_APR_AprFinfoT_set_inode, MRB_ARGS_ARG(1, 0));
#endif
#if BIND_AprFinfoT_device_FIELD_READER
  mrb_define_method(mrb, AprFinfoT_class, "device", mrb_APR_AprFinfoT_get_device, MRB_ARGS_ARG(0, 0));
#endif
#if BIND_AprFinfoT_device_FIELD_WRITER
  mrb_define_method(mrb, AprFinfoT_class, "device=", mrb_APR_AprFinfoT_set_device, MRB_ARGS_ARG(1, 0));
#endif
#if BIND_AprFinfoT_nlink_FIELD_READER
  mrb_define_method(mrb, AprFinfoT_class, "nlink", mrb_APR_AprFinfoT_get_nlink, MRB_ARGS_ARG(0, 0));
#endif
#if BIND_AprFinfoT_nlink_FIELD_WRITER
  mrb_define_method(mrb, AprFinfoT_class, "nlink=", mrb_APR_AprFinfoT_set_nlink, MRB_ARGS_ARG(1, 0));
#endif
#if BIND_AprFinfoT_size_FIELD_READER
  mrb_define_method(mrb, AprFinfoT_class, "size", mrb_APR_AprFinfoT_get_size, MRB_ARGS_ARG(0, 0));
#endif
#if BIND_AprFinfoT_size_FIELD_WRITER
  mrb_define_method(mrb, AprFinfoT_class, "size=", mrb_APR_AprFinfoT_set_size, MRB_ARGS_ARG(1, 0));
#endif
#if BIND_AprFinfoT_csize_FIELD_READER
  mrb_define_method(mrb, AprFinfoT_class, "csize", mrb_APR_AprFinfoT_get_csize, MRB_ARGS_ARG(0, 0));
#endif
#if BIND_AprFinfoT_csize_FIELD_WRITER
  mrb_define_method(mrb, AprFinfoT_class, "csize=", mrb_APR_AprFinfoT_set_csize, MRB_ARGS_ARG(1, 0));
#endif
#if BIND_AprFinfoT_atime_FIELD_READER
  mrb_define_method(mrb, AprFinfoT_class, "atime", mrb_APR_AprFinfoT_get_atime, MRB_ARGS_ARG(0, 0));
#endif
#if BIND_AprFinfoT_atime_FIELD_WRITER
  mrb_define_method(mrb, AprFinfoT_class, "atime=", mrb_APR_AprFinfoT_set_atime, MRB_ARGS_ARG(1, 0));
#endif
#if BIND_AprFinfoT_mtime_FIELD_READER
  mrb_define_method(mrb, AprFinfoT_class, "mtime", mrb_APR_AprFinfoT_get_mtime, MRB_ARGS_ARG(0, 0));
#endif
#if BIND_AprFinfoT_mtime_FIELD_WRITER
  mrb_define_method(mrb, AprFinfoT_class, "mtime=", mrb_APR_AprFinfoT_set_mtime, MRB_ARGS_ARG(1, 0));
#endif
#if BIND_AprFinfoT_ctime_FIELD_READER
  mrb_define_method(mrb, AprFinfoT_class, "ctime", mrb_APR_AprFinfoT_get_ctime, MRB_ARGS_ARG(0, 0));
#endif
#if BIND_AprFinfoT_ctime_FIELD_WRITER
  mrb_define_method(mrb, AprFinfoT_class, "ctime=", mrb_APR_AprFinfoT_set_ctime, MRB_ARGS_ARG(1, 0));
#endif
#if BIND_AprFinfoT_fname_FIELD_READER
  mrb_define_method(mrb, AprFinfoT_class, "fname", mrb_APR_AprFinfoT_get_fname, MRB_ARGS_ARG(0, 0));
#endif
#if BIND_AprFinfoT_fname_FIELD_WRITER
  mrb_define_method(mrb, AprFinfoT_class, "fname=", mrb_APR_AprFinfoT_set_fname, MRB_ARGS_ARG(1, 0));
#endif
#if BIND_AprFinfoT_name_FIELD_READER
  mrb_define_method(mrb, AprFinfoT_class, "name", mrb_APR_AprFinfoT_get_name, MRB_ARGS_ARG(0, 0));
#endif
#if BIND_AprFinfoT_name_FIELD_WRITER
  mrb_define_method(mrb, AprFinfoT_class, "name=", mrb_APR_AprFinfoT_set_name, MRB_ARGS_ARG(1, 0));
#endif
#if BIND_AprFinfoT_filehand_FIELD_READER
  mrb_define_method(mrb, AprFinfoT_class, "filehand", mrb_APR_AprFinfoT_get_filehand, MRB_ARGS_ARG(0, 0));
#endif
#if BIND_AprFinfoT_filehand_FIELD_WRITER
  mrb_define_method(mrb, AprFinfoT_class, "filehand=", mrb_APR_AprFinfoT_set_filehand, MRB_ARGS_ARG(1, 0));
#endif
/* MRUBY_BINDING_END */


/* MRUBY_BINDING: AprFinfoT::post_class_definition */
/* sha: user_defined */

/* MRUBY_BINDING_END */
}

/* MRUBY_BINDING: footer */
/* sha: user_defined */

/* MRUBY_BINDING_END */
#endif
