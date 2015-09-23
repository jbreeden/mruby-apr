class File < IO
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
  def initialize(filename, mode='r', perm=APR::APR_FPROT_OS_DEFAULT)
    err, @pool = APR.apr_pool_create(nil)
    APR.raise_apr_errno(err)
    @filename = filename

    @flags = APR::APR_FOPEN_BUFFERED # Always at least buffered
    @flags = IO::Util.mode_str_to_apr_flags(mode)

    if mode.include? 'b'
      @flags = @flags | APR::APR_FOPEN_BINARY
    end

    @perm_bits = perm

    err, @native_file = APR.apr_file_open(@filename, @flags, @perm_bits, @pool)
    if err != 0
      APR.apr_pool_destroy(@pool)
      APR.raise_apr_errno(err)
    end
  end

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

  def self.delete(*paths)
    APR.with_pool do |pool|
      paths.each do |path|
        err = APR.apr_file_remove(path, pool)
        APR.raise_apr_errno(err)
      end
    end
  end

  def self.extname(path)
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

  def self.read(path)
    result = nil
    File.open(path) do |f|
      result = f.read
    end
    result
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
      return APR::apr_file_unlock(@native_file)
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
    err = APR.apr_file_lock(@native_file, apr_lock_type)
    APR.raise_apr_errno(err, ignore: APR::APR_EAGAIN)

    if err == APR::APR_EAGAIN
      false
    else
      0
    end
  end

  def close
    APR.apr_file_close(@native_file)
    @closed = true
  end

  def closed?
    @closed
  end

  def native_file
    @native_file
  end

  def check_can_read
    if (!closed? && (@flags & APR::APR_FOPEN_READ) == 0)
      raise IOError.new 'not opened for reading'
    end
  end

  def check_can_write
    if (!closed? && (@flags & APR::APR_FOPEN_WRITE) == 0)
      raise IOError.new 'not opened for writing'
    end
  end

  def flush
    check_can_write
    APR.apr_file_flush(@native_file)
  end

  def gets(sep=nil, limit=nil)
    check_can_read

    _sep = $/
    _limit = nil

    # Either nothing is provided
    if sep.nil? && limit.nil?
      # Just continue
    # Or sep is provided
    elsif sep.class == String && limit.nil?
      _sep = sep
    # Or limit
    elsif sep.class == Fixnum && limit.nil?
      _limit = sep
    # Or both
    elsif sep.class == String && limit.class == Fixnum
      _sep = sep
      _limit = limit
    # Or the call is invalid
    else
      raise ArgumentError.new "Invalid arguments"
    end

    result = nil
    count = 0
    loop do
      if !_limit.nil? && _limit <= count
        result = "" if result == nil
        break
      end

      err, str = APR::apr_file_read(@native_file, 1)
      APR.raise_apr_errno(err, ignore: APR::APR_EOF)

      break if err == APR::APR_EOF

      if result.nil?
        result = str
      else
        result += str
      end
      count += 1
      break if result.end_with? _sep
    end

    result
  end

  def <<(obj)
    as_str = obj.class == String ? obj : obj.to_s
    APR.apr_file_write(@native_file, as_str, as_str.length)
  end

  def print(*objs)
    check_can_write
    objs.each_with_index do |obj, i|
      as_str = obj.class == String ? obj : obj.to_s
      APR.apr_file_write(@native_file, $,.to_s, $,.to_s.length) if i > 0  && !$,.nil?
      APR.apr_file_write(@native_file, as_str, as_str.length)
    end
    APR.apr_file_write(@native_file, $\.to_s, $\.to_s.length) unless $\.nil?
    nil
  end

  def puts(*args)
    check_can_write

    # All array arguments should be flattened such that all elements are written on a new "line"
    args = args.flatten

    sep = $\.nil? ? "\n" : $\

    if args.length > 0
      args.each do |arg|
        as_str = arg.to_s
        unless as_str.end_with?(sep)
          as_str += sep
        end
        err, bytes_written = APR.apr_file_write(@native_file, as_str, as_str.length)
        APR.raise_apr_errno(err)
      end
    else
      err, bytes_written = APR.apr_file_write(@native_file, sep, sep.length)
      APR.raise_apr_errno(err)
    end
    nil
  end

  def read(length = nil)
    check_can_read

    read = ""
    if length.nil?
      loop {
        err, current_read = APR::apr_file_read(@native_file, 100)
        APR.raise_apr_errno(err, ignore: [APR::APR_SUCCESS, APR::APR_EOF])
        break if current_read.length == 0
        read += current_read
      }
    else
      err, read = APR::apr_file_read(@native_file, length)
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
    check_can_write
    as_str = (str.class == String) ? str : str.to_s
    err, bytes_written = APR.apr_file_write(@native_file, as_str, as_str.length)
    APR.raise_apr_errno(err)
    bytes_written
  end

  def each(&block)
    check_can_read
    if block
      while line = self.gets
        block[line]
      end
    else
      enum = self.to_enum(:each)
    end
  end
  alias each_line each

  def each_byte(&block)
    check_can_read
    if block
      while b = self.read(1)
        block[b.ord]
      end
    else
      self.to_enum(:each_byte)
    end
  end

  def eof?
    check_can_read
    is_eof = (APR::APR_EOF == APR.apr_file_eof(@native_file))
    unless is_eof
      # Have to cheat since CRuby returns EOF immediately for an empty file,
      # while APR only returns EOF after you try to read past it.
      # So, we can getc -> check -> ungetc to mimick CRuby
      err, char = APR.apr_file_getc(@native_file)
      APR.raise_apr_errno(err, ignore: APR::APR_EOF)
      is_eof = (APR::APR_EOF == err)
      unless char.nil?
        APR.apr_file_ungetc(char, @native_file)
      end
    end
    is_eof
  end
  alias eof eof?

  def getc
    check_can_read
    err, char = APR.apr_file_getc(@native_file)
    APR.raise_apr_errno(err, ignore: APR::APR_EOF)
    char
  end

  def getbyte
    check_can_read
    err, char = APR.apr_file_getc(@native_file)
    APR.raise_apr_errno(err, ignore: APR::APR_EOF)
    char.nil? ? nil : char.ord
  end

  def ungetbyte(byte)
    check_can_read
    if byte.class == String
      byte.reverse.each_char do |ch|
        err = APR.apr_file_ungetc(ch, @native_file)
        APR.raise_apr_errno(err)
      end
    elsif byte.class == Fixnum
      err = APR.apr_file_ungetc(byte.chr, @native_file)
      APR.raise_apr_errno(err)
    else
      raise ArgumentError.new("Expected a String or Fixnum")
    end
  end
  alias ungetc ungetbyte # No difference between byte & char in mruby

  def seek(amount, whence=IO::SEEK_SET)
    whence = IO::Util.ruby_seek_to_apr(whence)
    err, pos = APR.apr_file_seek(@native_file, whence, amount)
    APR.raise_apr_errno(err)
  end
end
