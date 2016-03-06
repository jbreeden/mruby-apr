# APR.rb is auto generated.
# This file contains hand-written extensions to the module.

module APR
  # If apr_errno is an error code, and it doesn't appear in `opt[:ignore]`,
  # raise it as a Ruby exception.
  def self.raise_apr_errno(apr_errno, opt = {ignore: []})
    [opt[:ignore]].flatten.each do |err|
      return if apr_errno == err
    end
    if apr_errno != APR::APR_SUCCESS
      raise SystemCallError.new("ERROR: #{apr_errno} #{APR.strerror(apr_errno)}", APR.to_os_error(apr_errno))
    end
  end

  # Use this method to get a pool via the 'loan' pattern.
  def self.with_pool(&block)
    err, pool = APR.pool_create(nil)
    return block[pool]
  end

  # Creating pools is slow. If you don't need to keep any native handles
  # from the pool around, use this method instead. It re-uses a pool,
  # clearing the contents after each use.
  def self.with_stack_pool(&block)
    @stack_pool_handle ||= stack_pool
    stack_pool_enter
    result = yield @stack_pool_handle
    stack_pool_leave
    result
  end

  # APR_FINFO_* Flags
  # -----------------
  #
  # For quick reference, the flags made available by APR are listed here.
  # Below this listing, predefined combinations of flags are defined
  #
  # ### Standard flags
  #
  # define APR_FINFO_LINK   0x00000001 /**< Stat the link not the file itself if it is a link */
  # define APR_FINFO_MTIME  0x00000010 /**< Modification Time */
  # define APR_FINFO_CTIME  0x00000020 /**< Creation or inode-changed time */
  # define APR_FINFO_ATIME  0x00000040 /**< Access Time */
  # define APR_FINFO_SIZE   0x00000100 /**< Size of the file */
  # define APR_FINFO_CSIZE  0x00000200 /**< Storage size consumed by the file */
  # define APR_FINFO_DEV    0x00001000 /**< Device */
  # define APR_FINFO_INODE  0x00002000 /**< Inode */
  # define APR_FINFO_NLINK  0x00004000 /**< Number of links */
  # define APR_FINFO_TYPE   0x00008000 /**< Type */
  # define APR_FINFO_USER   0x00010000 /**< User */
  # define APR_FINFO_GROUP  0x00020000 /**< Group */
  # define APR_FINFO_UPROT  0x00100000 /**< User protection bits */
  # define APR_FINFO_GPROT  0x00200000 /**< Group protection bits */
  # define APR_FINFO_WPROT  0x00400000 /**< World protection bits */
  # define APR_FINFO_ICASE  0x01000000 /**< if dev is case insensitive */
  # define APR_FINFO_NAME   0x02000000 /**< ->name in proper case */
  #
  # ### Aggregate Flags
  #
  # define APR_FINFO_MIN    0x00008170 /**< type, mtime, ctime, atime, size */
  # define APR_FINFO_IDENT  0x00003000 /**< dev and inode */
  # define APR_FINFO_OWNER  0x00030000 /**< user and group */
  # define APR_FINFO_PROT   0x00700000 /**<  all protections */
  # define APR_FINFO_NORM   0x0073b170 /**<  an atomic unix apr_stat() */
  # define APR_FINFO_DIRENT 0x02000000 /**<  an atomic unix apr_dir_read() */

  # Default file info fields "want" flags
  APR_FINFO_DEFAULT = APR_FINFO_MTIME |
    APR_FINFO_CTIME |
    APR_FINFO_ATIME |
    APR_FINFO_SIZE  |
    APR_FINFO_TYPE  |
    APR_FINFO_USER  |
    APR_FINFO_GROUP |
    APR_FINFO_UPROT |
    APR_FINFO_GPROT |
    APR_FINFO_WPROT |
    APR_FINFO_NAME

  # Info fields "want" flags for statusing a link instead of the file itself
  APR_FINFO_LINK = APR_FINFO_DEFAULT | APR_FINFO_LINK

  module Convert
    # Convert an APR representation of time
    # into a Ruby Time object.
    def self.apr_time_to_rb(apr_time)
      Time.at(APR.time_sec(apr_time))
    end
  end
end
