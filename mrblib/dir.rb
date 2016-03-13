class Dir
  include Enumerable
  
  module Private
    # Replaces alternate path separators with the normalized version in `path`
    def self.normalize_path(path)
      if File::ALT_SEPARATOR
        path.gsub!(File::ALT_SEPARATOR, File::SEPARATOR)
      end
      path
    end
  end
  
  def initialize(path)
    err, @pool = APR.pool_create(nil)
    APR.raise_apr_errno(err)
    @path = File::Private.to_path_str(path)
    err, @native_dir = APR.dir_open @path, @pool
    APR.raise_apr_errno(err)
    @closed = false
    @pos = 0
  end
  
  def self.open(path, &block)
    instance = self.new(path)
    if block_given?
      result = nil
      begin
        result = block[instance]
      ensure
        instance.close
      end
      result
    else
      instance
    end
  end
  
  def assert_open
    raise IOError.new('Closed directory') if @closed
  end
  
  def close
    assert_open
    err = APR.dir_close(@native_dir)
    APR.raise_apr_errno(err)
    @closed = true
  end
  
  def each(&block)
    assert_open
    if block_given?
      while entry = read
        block[entry]
      end
      self
    else
      self.class.entries(@path).enum_for(:each)
    end
  end
  
  def read
    assert_open
    err, finfo = APR.dir_read APR::APR_FINFO_NAME, @native_dir
    APR.raise_apr_errno(err, ignore: [APR::APR_INCOMPLETE, APR::APR_ENOENT])
    @pos += 1
    (err == APR::APR_ENOENT || finfo.nil?) ? nil : finfo.name
  end
  
  def rewind
    assert_open
    @pos = 0
    err = APR.dir_rewind(@native_dir)
    APR.raise_apr_errno(err)
  end
  
  def tell
    assert_open
    @pos
  end
  alias pos tell

  def self.chdir(path = nil, &block)
    path = Dir.home unless path
    path = File::Private.to_path_str(path)
    if block.nil?
      err = APR.dir_chdir(path)
      APR.raise_apr_errno(err)
      0
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
    path = File::Private.to_path_str(path)
    APR.with_stack_pool do |pool|
      err = APR.dir_remove(path, pool)
      APR.raise_apr_errno(err)
    end
    0
  end
  class << self
    alias rmdir delete
    alias unlink rmdir
  end


  class << self
    alias native_entries entries
  end
  def self.entries(path)
    native_entries(File::Private.to_path_str(path, true))
  end

  def self.exists?(path)
    path = File::Private.to_path_str(path)
    File.directory?(path)
  end
  class << self
    alias exist? exists?
  end

  def self.foreach(path, &block)
    path = File::Private.to_path_str(path)
    files = entries(path)
    if block.nil?
      self.to_enum :foreach, path
    else
      files.each(&block)
    end
  end

  def self.getwd
    err, path = APR.dir_getcwd
    APR.raise_apr_errno(err) # Why would this ever happen?
    Private.normalize_path(path)    
  end
  class << self
    alias pwd getwd
  end

  def self.home
    if APR::OS == 'Windows'
      Private.normalize_path(ENV['HOMEPATH'])
    else
      Private.normalize_path(ENV['HOME'])
    end
  end

  def self.mkdir(path)
    path = File::Private.to_path_str(path)
    APR.with_stack_pool do |pool|
      err = APR.dir_make path, APR::APR_FPROT_OS_DEFAULT, pool
      APR.raise_apr_errno(err)
    end
  end

  def self.tmpdir
    APR.with_stack_pool do |pool|
      err, dirname = APR.temp_dir_get(pool)
      Private.normalize_path(dirname)
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
