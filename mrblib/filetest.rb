module FileTest
  # Define module's own methods as module functions
  extend FileTest

  def blockdev?(path)
    stat = File::Stat.new(path) rescue nil
    !stat.nil? && stat.blockdev?
  end

  def chardev?(path)
    stat = File::Stat.new(path) rescue nil
    !stat.nil? && stat.chardev?
  end

  def directory?(path)
    stat = File::Stat.new(path) rescue nil
    !stat.nil? && stat.directory?
  end

  # def executable?(path)
  #   stat = File::Stat.new(path) rescue nil
  #   stat.executable?
  # end
  #
  # def executable_real?(path)
  #   stat = File::Stat.new(path) rescue nil
  #   stat.executable_real?
  # end

  def exists?(path)
    exists = true
    APR.with_pool do |pool|
      err, f = APR.apr_file_open(path, APR::APR_FOPEN_READ, 0, pool)
      exists = false if APR::APR_STATUS_IS_ENOENT(err)
      APR.apr_file_close(f) if f
    end
    exists
  end
  alias exist? exists?

  def file?(path)
    stat = File::Stat.new(path) rescue nil
    !stat.nil? && stat.file?
  end

  # def grpowned?(path)
  #   stat = File::Stat.new(path) rescue nil
  #   stat.grpowned?
  # end

  # def identical?(path1, path2)
  #
  # end
  #
  # def owned?(path)
  #   stat = File::Stat.new(path) rescue nil
  #   stat.owned?
  # end

  def pipe?(path)
    stat = File::Stat.new(path) rescue nil
    !stat.nil? && stat.pipe?
  end

  # def readable?(path)
  #   stat = File::Stat.new(path) rescue nil
  #   stat.readable?
  # end
  #
  # def readable_real?(path)
  #   stat = File::Stat.new(path) rescue nil
  #   stat.readable_real?
  # end
  #
  # def setgid?(path)
  #   stat = File::Stat.new(path) rescue nil
  #   stat.setgid?
  # end
  #
  # def setuid?(path)
  #   stat = File::Stat.new(path) rescue nil
  #   stat.setuid?
  # end

  def size(path)
    stat = File::Stat.new(path)
    stat.size
  end
  alias size? size

  def socket?(path)
    stat = File::Stat.new(path) rescue nil
    !stat.nil? && stat.socket?
  end

  # def sticky?(path)
  #   stat = File::Stat.new(path) rescue nil
  #   stat.sticky?
  # end

  def symlink?(path)
    stat = File::Stat.new(path) rescue nil
    !stat.nil? && stat.symlink?
  end

  # def world_readable?(path)
  #   stat = File::Stat.new(path) rescue nil
  #   stat.world_readable?
  # end
  #
  # def world_writable?(path)
  #   stat = File::Stat.new(path) rescue nil
  #   stat.world_writable?
  # end
  #
  # def writable?(path)
  #   stat = File::Stat.new(path) rescue nil
  #   stat.writable?
  # end
  #
  # def writable_real?(path)
  #   stat = File::Stat.new(path) rescue nil
  #   stat.writable_real?
  # end

  def zero?(path)
    stat = File::Stat.new(path) rescue nil
    !stat.nil? && stat.zero?
  end
end

class File
  extend FileTest
end
