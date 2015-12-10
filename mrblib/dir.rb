class Dir
  # def initialize(path)
  #
  # end
  #
  # def self.open(path, &block)
  #
  # end

  def self.chdir(path, &block)
    if block.nil?
      err = APR.apr_dir_chdir(path)
      APR.raise_apr_errno(err)
    else
      prev = pwd
      begin
        chdir path
        block[]
      ensure
        chdir prev
      end
    end
  end

  # def self.chroot
  #
  # end

  def self.delete(path)
    APR.with_stack_pool do |pool|
      err = APR.apr_dir_remove(path, pool)
      APR.raise_apr_errno(err)
    end
  end
  class << self
    alias rmdir delete
    alias unlink rmdir
  end

  ########################### Ported to C
  # def self.entries(path)
  #   results = []
  #   APR.with_stack_pool do |pool|
  #     err, dir = APR.apr_dir_open path, pool
  #     APR.raise_apr_errno(err)
  #
  #     err, finfo = APR.apr_dir_read APR::APR_FINFO_NAME, dir
  #     while err == 0 || err == APR::APR_INCOMPLETE
  #       results.push(finfo.name)
  #       err, finfo = APR.apr_dir_read APR::APR_FINFO_NAME, dir
  #     end
  #   end
  #   results
  # end
  ###########################

  def self.exists?(path)
    File.directory?(path)
  end
  class << self
    alias exist? exists?
  end

  def self.foreach(path, &block)
    files = entries(path)
    if block.nil?
      self.to_enum :foreach, path
    else
      files.each &block
    end
  end

  def self.getcwd
    # TODO May need to fix path on windows (Ruby always uses /)
    err, path = APR.apr_dir_getcwd
    APR.raise_apr_errno(err) # Why would this ever happen?
    path
  end
  class << self
    alias pwd getcwd
  end

  # def self.home
  #
  # end

  def self.mkdir(path)
    APR.with_stack_pool do |pool|
      err = APR.apr_dir_make path, APR::APR_FPROT_OS_DEFAULT, pool
      APR.raise_apr_errno(err)
    end
  end

  def self.tmpdir
    APR.with_stack_pool do |pool|
      err, dirname = APR.apr_temp_dir_get(pool)
      dirname
    end
  end

  def self.mktmpdir(prefix_suffix = nil, parent = nil)
    if block_given?
      raise "Cannot securely delete temp dir contents, so mktmpdir does not yet support a block parameter"
      # Need FileUtils::remove_entry_secure to fix
    end

    prefix_suffix = case prefix_suffix
    when NilClass
      ['d', '']
    when String
      [prefix_suffix, '']
    when Array
      prefix_suffix
    else
      raise ArgumentError.new("Invalid first parameter to Dir.mktmpdir")
    end

    parent = case parent
    when String
      parent[parent.length - 1] == '/' ? parent : "#{parent}/"
    when NilClass
      Dir.tmpdir
    else
      raise ArgumentError.new("Invalid second parameter to Dir.mktmpdir")
    end

    now = Time.now
    random_string = (0..5).map { (rand(26) + 'a'.ord).chr }.join('')

    dirname = "%{parent}%{prefix}%{date}-%{pid}-%{rand}%{suffix}" % {
      parent: parent,
      prefix: prefix_suffix.first,
      date: now.year.to_s + ('%02d' % now.month) + ('%02d' % now.day),
      pid: Process.pid,
      rand: random_string,
      suffix: prefix_suffix.last
    }

    self.mkdir(dirname)
    dirname
  end
end
