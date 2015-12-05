class File
  class Stat
    def initialize(file_name, apr_wanted=nil)
      APR.with_stack_pool do |pool|
        APR.raise_apr_errno(APR::APR_ENOENT) unless File.exists?(file_name)
        err, native_finfo = APR.apr_stat(file_name, apr_wanted || APR::APR_FINFO_DEFAULT, pool)

        @atime = APR::Convert.apr_time_to_rb(native_finfo.atime) if (native_finfo.valid & APR::APR_FINFO_ATIME) != 0
        @ctime = APR::Convert.apr_time_to_rb(native_finfo.ctime) if (native_finfo.valid & APR::APR_FINFO_CTIME) != 0
        @mtime = APR::Convert.apr_time_to_rb(native_finfo.mtime) if (native_finfo.valid & APR::APR_FINFO_MTIME) != 0
        @name  = native_finfo.name if (native_finfo.valid & APR::APR_FINFO_NAME) != 0
        @nlink = native_finfo.nlink if (native_finfo.valid & APR::APR_FINFO_NLINK) != 0
        @size  = native_finfo.size if (native_finfo.valid & APR::APR_FINFO_SIZE) != 0
        @protection = native_finfo.protection if (native_finfo.valid & APR::APR_FINFO_PROT) != 0
        @filetype = native_finfo.filetype if (native_finfo.valid & APR::APR_FINFO_PROT) != 0
      end
    end

    def <=>
      raise NotImplementedError.new('File::Stat#<=> is not yet implemented')
    end

    attr_reader :atime
    attr_reader :ctime
    attr_reader :mtime
    attr_reader :name
    attr_reader :nlink
    attr_reader :size
    alias size? size

    # def blksize
    #   raise NotImplementedError.new('File::Stat#blksize is not yet implemented')
    # end

    def blockdev?
      @filetype == APR::AprFiletypeE::APR_BLK
    end

    # def blocks
    #   raise NotImplementedError.new('File::Stat#blocks is not yet implemented')
    # end

    def chardev?
      @filetype == APR::AprFiletypeE::APR_CHR
    end

    # def dev
    #   raise NotImplementedError.new('File::Stat#dev is not yet implemented')
    # end
    #
    # def dev_major
    #   raise NotImplementedError.new('File::Stat#dev_major is not yet implemented')
    # end
    #
    # def dev_minor
    #   raise NotImplementedError.new('File::Stat#dev_minor is not yet implemented')
    # end

    def directory?
      @filetype == APR::AprFiletypeE::APR_DIR
    end

    # def executable?
    #   raise NotImplementedError.new('File::Stat#executable? is not yet implemented')
    # end
    #
    # def executable_real?
    #   raise NotImplementedError.new('File::Stat#executable_real? is not yet implemented')
    # end

    def file?
      @filetype == APR::AprFiletypeE::APR_REG
    end

    def ftype
      if file?
        "file"
      elsif directory?
        "directory"
      elsif chardev?
        "characterSpecial"
      elsif blockdev?
        "blockSpecial"
      elsif pipe?
        "fifo"
      elsif symlink?
        "link"
      elsif socket?
        "socket"
      else
        "unkown"
      end
    end

    # def gid
    #   raise NotImplementedError.new('File::Stat#gid is not yet implemented')
    # end
    #
    # def grpowned?
    #   raise NotImplementedError.new('File::Stat#grpowned? is not yet implemented')
    # end
    #
    # def ino
    #   raise NotImplementedError.new('File::Stat#ino is not yet implemented')
    # end
    #
    # def mode
    #   raise NotImplementedError.new('File::Stat#mode is not yet implemented')
    # end
    #
    # def owned?
    #   raise NotImplementedError.new('File::Stat#owned? is not yet implemented')
    # end

    def pipe?
      @filetype == APR::AprFiletypeE::APR_PIPE
    end

    # def rdev
    #   raise NotImplementedError.new('File::Stat#rdev is not yet implemented')
    # end
    #
    # def rdev_major
    #   raise NotImplementedError.new('File::Stat#rdev_major is not yet implemented')
    # end
    #
    # def rdev_minor
    #   raise NotImplementedError.new('File::Stat#rdev_minor is not yet implemented')
    # end
    #
    # def readable?
    #   raise NotImplementedError.new('File::Stat#readable? is not yet implemented')
    # end
    #
    # def readable_real?
    #   raise NotImplementedError.new('File::Stat#readable_real? is not yet implemented')
    # end
    #
    # def setgid?
    #   raise NotImplementedError.new('File::Stat#setgid? is not yet implemented')
    # end
    #
    # def setuid?
    #   raise NotImplementedError.new('File::Stat#setuid? is not yet implemented')
    # end

    def socket?
      @filetype == APR::AprFiletypeE::APR_SOCKET
    end

    # def sticky?
    #   raise NotImplementedError.new('File::Stat#sticky? is not yet implemented')
    # end

    def symlink?
      @filetype == APR::AprFiletypeE::APR_LNK
    end

    # def uid
    #   raise NotImplementedError.new('File::Stat#uid is not yet implemented')
    # end
    #
    # def world_readable?
    #   raise NotImplementedError.new('File::Stat#world_readable? is not yet implemented')
    # end
    #
    # def world_writable?
    #   raise NotImplementedError.new('File::Stat#world_writable? is not yet implemented')
    # end
    #
    # def writable?
    #   raise NotImplementedError.new('File::Stat#writable? is not yet implemented')
    # end
    #
    # def writable_real?
    #   raise NotImplementedError.new('File::Stat#writable_real? is not yet implemented')
    # end
    #
    def zero?
      size == 0
    end
  end
end
