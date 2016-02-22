module FileTest
  ## OPTIMIZATION: Converted to C
  # module Util
  #   # OPTIMIZATION: This is much faster than creating a fule File::Stat object
  #   #               for each test, which significantly impacts globbing with
  #   #               large search area.
  #   def self.FileTest.is_type?(path, type)
  #     result = nil
  #     APR.with_pool do |pool|
  #       err, native_finfo = APR.stat(path, APR::APR_FINFO_TYPE, pool)
  #       if err == APR::APR_SUCCESS
  #         result = native_finfo.filetype == type
  #       end
  #     end
  #     result
  #   end
  # end

  # Define module's own methods as module functions
  extend FileTest

  def blockdev?(path)
    path = File::Private.to_path_str(path)
    FileTest.is_type?(path, APR::Filetype::APR_BLK)
  end

  def chardev?(path)
    path = File::Private.to_path_str(path)
    FileTest.is_type?(path, APR::Filetype::APR_CHR)
  end

  def directory?(path)
    path = File::Private.to_path_str(path)
    FileTest.is_type?(path, APR::Filetype::APR_DIR)
  end

  # def executable?(path)
  #   path = File::Private.to_path_str(path)
  #   stat = File::Stat.new(path) rescue nil
  #   stat.executable?
  # end
  #
  # def executable_real?(path)
  #   path = File::Private.to_path_str(path)
  #   stat = File::Stat.new(path) rescue nil
  #   stat.executable_real?
  # end

  def exists?(path)
    path = File::Private.to_path_str(path)
    exists = true
    APR.with_stack_pool do |pool|
      err, f = APR.file_open(path, APR::APR_FOPEN_READ, 0, pool)
      exists = false if APR::APR_STATUS_IS_ENOENT(err)
      APR.file_close(f) if f
    end
    exists
  end
  alias exist? exists?

  def file?(path)
    path = File::Private.to_path_str(path)
    FileTest.is_type?(path, APR::Filetype::APR_REG)
  end

  # def grpowned?(path)
  #   path = File::Private.to_path_str(path)
  #   stat = File::Stat.new(path) rescue nil
  #   stat.grpowned?
  # end

  # def identical?(path1, path2)
  #
  # end
  #
  # def owned?(path)
  #   path = File::Private.to_path_str(path)
  #   stat = File::Stat.new(path) rescue nil
  #   stat.owned?
  # end

  def pipe?(path)
    path = File::Private.to_path_str(path)
    FileTest.is_type?(path, APR::Filetype::APR_PIPE)
  end

  # def readable?(path)
  #   path = File::Private.to_path_str(path)
  #   stat = File::Stat.new(path) rescue nil
  #   stat.readable?
  # end
  #
  # def readable_real?(path)
  #   path = File::Private.to_path_str(path)
  #   stat = File::Stat.new(path) rescue nil
  #   stat.readable_real?
  # end
  #
  # def setgid?(path)
  #   path = File::Private.to_path_str(path)
  #   stat = File::Stat.new(path) rescue nil
  #   stat.setgid?
  # end
  #
  # def setuid?(path)
  #   path = File::Private.to_path_str(path)
  #   stat = File::Stat.new(path) rescue nil
  #   stat.setuid?
  # end

  def size(path)
    stat = File::Stat.new(path)
    stat.size
  end
  alias size? size

  def socket?(path)
    path = File::Private.to_path_str(path)
    FileTest.is_type?(path, APR::Filetype::APR_SOCKET)
  end

  # def sticky?(path)
  #   path = File::Private.to_path_str(path)
  #   stat = File::Stat.new(path) rescue nil
  #   stat.sticky?
  # end

  def symlink?(path)
    path = File::Private.to_path_str(path)
    FileTest.is_type?(path, APR::Filetype::APR_LNK)
  end

  # def world_readable?(path)
  #   path = File::Private.to_path_str(path)
  #   stat = File::Stat.new(path) rescue nil
  #   stat.world_readable?
  # end
  #
  # def world_writable?(path)
  #   path = File::Private.to_path_str(path)
  #   stat = File::Stat.new(path) rescue nil
  #   stat.world_writable?
  # end
  #
  # def writable?(path)
  #   path = File::Private.to_path_str(path)
  #   stat = File::Stat.new(path) rescue nil
  #   stat.writable?
  # end
  #
  # def writable_real?(path)
  #   path = File::Private.to_path_str(path)
  #   stat = File::Stat.new(path) rescue nil
  #   stat.writable_real?
  # end

  def zero?(path)
    path = File::Private.to_path_str(path)
    stat = File::Stat.new(path) rescue nil
    !stat.nil? && stat.zero?
  end
end

class File
  extend FileTest
end
