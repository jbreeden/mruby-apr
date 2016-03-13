class File < IO
  module Constants
    RDONLY = 0
    WRONLY = 1
    RDWR = 2
    APPEND = 8
    CREAT = 512
    EXCL = 2048
    NONBLOCK = 4
    TRUNC = 1024
    NOCTTY = 131072
    BINARY = 0
    SYNC = 128
    DSYNC = 4194304
    NOFOLLOW = 256
    LOCK_SH = 1
    LOCK_EX = 2
    LOCK_UN = 8
    LOCK_NB = 4
    if APR::OS == 'Windows'
      NULL = 'NUL'
      ALT_SEPARATOR = ?\
    else
      ALT_SEPARATOR = nil
      NULL = '/dev/null'
    end
    FNM_NOESCAPE = 1
    FNM_PATHNAME = 2
    FNM_DOTMATCH = 4
    FNM_CASEFOLD = 8
    FNM_EXTGLOB = 16
    FNM_SYSCASE = 0
  end
  
  include Constants
  
  module Private
    def self.to_path_str(path, is_optional=false)
      if path.kind_of?(String)
        path
      else
        if path.respond_to?(:to_path)
          path = path.to_path
        elsif path.respond_to?(:to_str)
          path = path.to_str
        elsif is_optional && path.nil?
          nil
        else
          raise TypeError.new("String expected")
        end
      end
    end
  end
  
  SEPARATOR = ?/
  Separator = SEPARATOR
  
  # Modes:
  # "r"  Read-only, starts at beginning of file  (default mode).
  #
  # "r+" Read-write, starts at beginning of file.
  #
  # "w"  Write-only, truncates existing file
  #      to zero length or creates a new file for writing.
  #
  # "w+" Read-write, truncates existing file to zero length
  #      or creates a new file for reading and writing.
  #
  # "a"  Write-only, each write call appends data at end of file.
  #      Creates a new file for writing if file does not exist.
  #
  # "a+" Read-write, each write call appends data at end of file.
  #      Creates a new file for reading and writing if file does
  #      not exist.
  #
  #  The following modes must be used separately, and along with one or more of the modes seen above.
  #
  # "b"  Binary file mode
  #    Suppresses EOL <-> CRLF conversion on Windows. And
  #    sets external encoding to ASCII-8BIT unless explicitly
  #    specified.
  #
  # "t"  Text file mode
  def initialize(path, mode='r', perm=APR::APR_FPROT_OS_DEFAULT, apr_pool=nil)
    # Wrapper semantics
    if (path.kind_of?(APR::File))
      @native_file = path
      @flags = APR::APR_FOPEN_BUFFERED # Always at least buffered
      @flags = IO::Util.mode_str_to_apr_flags(mode)
      if perm.kind_of?(APR::Pool)
        @perm_bits = APR::APR_FPROT_OS_DEFAULT
        @pool = perm
      else
        @perm_bits = perm
        @pool = apr_pool
      end
      raise "Must pass apr pool param when wrapping an File" unless @pool
      return
    end

    err, @pool = APR.pool_create(nil)
    APR.raise_apr_errno(err)
    @path = path

    @flags = APR::APR_FOPEN_BUFFERED # Always at least buffered
    @flags = IO::Util.mode_str_to_apr_flags(mode)

    if mode.include? 'b'
      @flags = @flags | APR::APR_FOPEN_BINARY
    end

    @perm_bits = perm

    err, @native_file = APR.file_open(@path, @flags, @perm_bits, @pool)
    if err != 0
      APR.raise_apr_errno(err)
    end
  end
  
  attr_reader :path

  def self.open(*args, &block)
    f = File.new(*args)
    if block
      begin
        block[f]
      ensure
        f.close
      end
    else
      f
    end
  end
  
  def self.absolute_path(path, from = nil)
    path = Pathname.new(path)
    from = Pathname.new(from || Dir.pwd)
    
    if path.absolute?
      path.cleanpath.to_s
    elsif from.absolute?
      (from << path).cleanpath.to_s
    else
      (Pathname.new(Dir.pwd) << from << path).cleanpath.to_s
    end
  end

  def self.atime(path)
    stat = File::Stat.new(path)
    stat.atime
  end
  
  def self.basename(file_name, suffix = nil)
    p = Pathname.new(file_name)
    
    if p.root?
      return '/'
    end
    
    result = ''
    p.each_filename { |f| result = f } # grab the last part of the path
    
    suffix_str = if suffix.kind_of?(String)
      suffix
    elsif suffix.respond_to?(:to_str)
      suffix.to_str
    elsif !suffix.nil?
      raise TypeError.new("String expected")
    end
    
    last_dot_pos = result.rindex('.')
    if suffix_str == '.*' && last_dot_pos
      result = result[0...last_dot_pos]
    elsif suffix && result.end_with?(suffix_str)
      result = result[0...(-suffix_str.length)]
    end
    
    result
  end

  def self.ctime(path)
    stat = File::Stat.new(path)
    stat.ctime
  end

  def self.delete(*paths)
    APR.with_stack_pool do |pool|
      paths.each do |path|
        err = APR.file_remove(path, pool)
        APR.raise_apr_errno(err)
      end
    end
    paths.length
  end
  class << self
    alias unlink delete
  end

  def self.dirname(file_name)
    p = Pathname.new(file_name)
    parts = p.each_filename.to_a
    parts.pop
    
    if p.absolute?
      "/#{parts.join(File::SEPARATOR)}"
    else
      (result = parts.join(File::SEPARATOR)) == '' ? '.' : result
    end
  end
  
  def self.expand_path(path, from = nil)
    path = Private.to_path_str(path)
    from = Private.to_path_str(from, true)
    
    sub_home = proc { |str|
      if str == '~'
        str = Dir.home
      elsif str.start_with?("~#{File::SEPARATOR}")
        str = "#{Dir.home}#{File::SEPARATOR}#{str[2..-1]}"
      end
      str
    }
    
    if path.start_with?('~') || from.kind_of?(String) && from.start_with?("~")
      unless ENV['HOME'] && ENV['HOME'].kind_of?(String) && ENV['HOME'].length > 0
        raise ArgumentError.new("Couldn't find HOME environment variable -- expanding #{path}")
      end
    end
    
    path = sub_home[path]
    from = from ? sub_home[from] : nil
    self.absolute_path(path, from)
  end

  def self.extname(path)
    path = Private.to_path_str(path)
    path = path.gsub('\\', '/')
    dot_idx = path.rindex(".")
    return "" unless dot_idx
    slash_idx = path.rindex("/")
    slash_idx ||= -1
    # no . in the last component of the path
    return "" if dot_idx < slash_idx
    # last component starts with a .
    return "" if dot_idx == slash_idx + 1
    # last component ends with a .
    return "" if dot_idx == path.length - 1

    return path[dot_idx..(path.length)]
  end
  
  def self.fnmatch(pattern, file, flags = 0)
    APR.fnmatch(pattern, file, flags) == 0
  end
  class << self
    alias fnmatch? fnmatch
  end

  def self.join(*strings)
    Pathname.join(*strings)
  end

  def self.path(str)
    Private::to_path_str(str)
  end

  def self.read(path)
    path = Private.to_path_str(path)
    result = nil
    File.open(path) do |f|
      result = f.read
    end
    result
  end
  
  def self.stat(path)
    Stat.new(Private.to_path_str(path))
  end
  
  def self.truncate(path, length)
    raise TypeError.new("Expected length to be a Fixnum") unless length.kind_of?(Fixnum)
    raise Errno::EINVAL.new(length) if length < 0
    
    path = Private.to_path_str(path)
    new_contents = length == 0 ?
      '' :
      File.read(path)[0...length]
      
    File.open(path, 'w') do |f|
      f.write(new_contents)
      if new_contents.length < length
        f.write("\000" * (length - new_contents.length))
      end
    end
    
    length
  end

  #<
  # ## `#flock(locking_constant)`
  # Locks or unlocks a file according to locking_constant.
  # - Args
  #   + `locking_constant` Bitwise or of
  #     - `File::LOCK_EX` (Get an exclusive lock)
  #     - `File::LOCK_NB` (Do not block)
  #     - `File::LOCK_SH` (Get a shared lock)
  #     - `File::LOCK_UN` (Release any held locks)
  # - Returns false if File::LOCK_NB is specified and the operation would otherwise have blocked.
  #>
  def flock(locking_constant)
    if (locking_constant & File::LOCK_UN) > 0
      return APR.file_unlock(@native_file)
    end

    apr_flags = []
    if (locking_constant & File::LOCK_EX) > 0
      apr_flags << APR::APR_FLOCK_EXCLUSIVE
    end
    if (locking_constant & File::LOCK_SH) > 0
      apr_flags << APR::APR_FLOCK_SHARED
    end
    if (locking_constant & File::LOCK_NB) > 0
      apr_flags << APR::APR_FLOCK_NONBLOCK
    end

    apr_lock_type = apr_flags.inject(0) { |acc, cur| (acc | cur) }
    err = APR.file_lock(@native_file, apr_lock_type)
    APR.raise_apr_errno(err, ignore: APR::APR_EAGAIN)

    if err == APR::APR_EAGAIN
      false
    else
      0
    end
  end

  def close
    APR.file_close(@native_file)
    @closed = true
  end

  def closed?
    @closed
  end

  def native_file
    @native_file
  end

  def assert_can_read
    if (!closed? && (@flags & APR::APR_FOPEN_READ) == 0)
      raise IOError.new 'not opened for reading'
    end
  end

  def assert_can_write
    if (!closed? && (@flags & APR::APR_FOPEN_WRITE) == 0)
      raise IOError.new 'not opened for writing'
    end
  end

  def flush
    assert_can_write
    APR.file_flush(@native_file)
  end
  
  # IO Subclass Contract Implementation
  # -----------------------------------

  def read(length = nil)
    assert_can_read

    read = ""
    if length.nil?
      loop {
        err, current_read = APR.file_read(@native_file, 100)
        APR.raise_apr_errno(err, ignore: [APR::APR_SUCCESS, APR::APR_EOF])
        break if current_read.length == 0
        read += current_read
      }
    else
      err, read = APR.file_read(@native_file, length)
      APR.raise_apr_errno(err, ignore: [APR::APR_SUCCESS, APR::APR_EOF])
    end

    if length.nil?
      # should be "" if nothing was read (EOF hit)
      read
    elsif length == 0
      # Per ruby documents, return "" on length == 0
      ""
    else
      # length was provided non-zero, so return nil if nothing read
      read == "" ? nil : read
    end
  end

  def write(str)
    assert_can_write
    as_str = (str.class == String) ? str : str.to_s
    err, bytes_written = APR.file_write(@native_file, as_str, as_str.length)
    APR.raise_apr_errno(err)
    bytes_written
  end

  def eof?
    assert_can_read
    is_eof = (APR::APR_EOF == APR.file_eof(@native_file))
    unless is_eof
      # Have to cheat since CRuby returns EOF immediately for an empty file,
      # while APR only returns EOF after you try to read past it.
      # So, we can getc -> check -> ungetc to mimick CRuby
      err, char = APR.file_getc(@native_file)
      APR.raise_apr_errno(err, ignore: APR::APR_EOF)
      is_eof = (APR::APR_EOF == err)
      unless char.nil?
        APR.file_ungetc(char, @native_file)
      end
    end
    is_eof
  end
  alias eof eof?

  # IO Default Overrides
  # --------------------

  def getc
    assert_can_read
    err, char = APR.file_getc(@native_file)
    APR.raise_apr_errno(err, ignore: APR::APR_EOF)
    char
  end

  def getbyte
    assert_can_read
    err, char = APR.file_getc(@native_file)
    APR.raise_apr_errno(err, ignore: APR::APR_EOF)
    char.nil? ? nil : char.ord
  end

  def ungetbyte(byte)
    assert_can_read
    if byte.class == String
      byte.reverse.each_char do |ch|
        err = APR.file_ungetc(ch, @native_file)
        APR.raise_apr_errno(err)
      end
    elsif byte.class == Fixnum
      err = APR.file_ungetc(byte.chr, @native_file)
      APR.raise_apr_errno(err)
    else
      raise ArgumentError.new("Expected a String or Fixnum")
    end
  end
  alias ungetc ungetbyte # No difference between byte & char in mruby

  def seek(amount, whence=IO::SEEK_SET)
    whence = IO::Util.ruby_seek_to_apr(whence)
    err, pos = APR.file_seek(@native_file, whence, amount)
    APR.raise_apr_errno(err)
    # TODO: Verify expected return value
  end
end
