class IO
  # Pipe is essentially a File, the only difference is that
  # it exposed a constructor that takes an AprFileT to wrap.
  # This was required to allow results of apr_file_pipe_create
  # to be wrapped in a File object, without changing the standard
  # API of the File class.
  #
  # Note:
  # The mode & pool MUST be the same that the file was created with.
  class Pipe < File
    def initialize(apr_file, mode, pool)
      if apr_file.class != APR::AprFileT
        raise ArgumentError.new("AprFileT expected in first arg")
      end
      if pool.class != APR::AprPoolT
        raise ArgumentError.new("AprPoolT expected in third arg")
      end
      @native_file = apr_file
      @pool = pool

      if mode.class == Fixnum
        @flags = mode
      else
        @flags = IO::Util.mode_str_to_apr_flags(mode.to_s)
      end
      @closed = false
    end
  end

  # IO like object returned by IO.popen
  # This simply directs read methods to one pipe,
  # and write methods to another.
  # The `close` method closes both ends.
  # Use `close_read` and `close_write` to close one end only.
  class BidirectionalPipe
    # Expects a hash of the form { pid: Fixnum, read: Pipe, write: Pipe }
    # Either pipe may be nil, but not both
    def initialize(opt)
      @pid = opt[:pid]
      @read_pipe = opt[:read]
      @read_pipe.instance_variable_set(:@pid, opt[:pid]) unless @read_pipe.nil?
      @write_pipe = opt[:write]
      @write_pipe.instance_variable_set(:@pid, opt[:pid]) unless @write_pipe.nil?
    end

    def pid
      if closed?
        raise IOError.new("closed stream")
      end
      @pid
    end

    def close
      @write_pipe.close unless (@write_pipe.nil? || @write_pipe.closed?)
      @read_pipe.close unless (@read_pipe.nil? || @read_pipe.closed?)
      Process.wait(@pid) # Sets $? (TODO what if this happens twice? So far, not so good)
      nil
    end

    def closed?
      (@read_pipe.nil? || @read_pipe.closed?) && (@write_pipe.nil? || @write_pipe.closed?)
    end

    def close_read
      raise IOError.new('closed stream') if @read_pipe.nil? || @read_pipe.closed?
      @read_pipe.close
    end

    def close_write
      raise IOError.new('closed stream') if @write_pipe.nil? || @write_pipe.closed?
      @write_pipe.close
    end

    def assert_can_write
      if @write_pipe.nil? || @write_pipe.closed?
        raise IOError.new('not open for writing')
      end
    end

    # IO Write Methods
    # (Some of these aren't actually implemented in the Pipe/File classes yet,
    #  so they will raise an exception)

    def flush(*args)
      assert_can_write
      @write_pipe.flush(*args)
    end

    def <<(*args)
      assert_can_write
      @write_pipe.<<(*args)
    end

    def flush(*args)
      assert_can_write
      @write_pipe.flush(*args)
    end

    def print(*args)
      assert_can_write
      @write_pipe.print(*args)
    end

    def printf(*args)
      assert_can_write
      @write_pipe.printf(*args)
    end

    def putc(*args)
      assert_can_write
      @write_pipe.putc(*args)
    end

    def puts(*args)
      assert_can_write
      @write_pipe.puts(*args)
    end

    def syswrite(*args)
      assert_can_write
      @write_pipe.syswrite(*args)
    end

    def write(*args)
      assert_can_write
      @write_pipe.write(*args)
    end

    def write_nonblock(*args)
      assert_can_write
      @write_pipe.write_nonblock(*args)
    end


    # IO Read Methods
    # (Some of these aren't actually implemented in the Pipe/File classes yet,
    #  so they will raise an exception)

    def assert_can_read
      if @read_pipe.nil? || @read_pipe.closed?
        raise IOError.new('not open for reading')
      end
    end

    def eof
      assert_can_read
      @read_pipe.eof
    end

    def eof?
      assert_can_read
      @read_pipe.eof?
    end

    def bytes(*args)
      assert_can_read
      @read_pipe.bytes(*args)
    end

    def chars(*args)
      assert_can_read
      @read_pipe.chars(*args)
    end

    def codepoints(*args)
      assert_can_read
      @read_pipe.codepoints(*args)
    end

    def each(*args)
      assert_can_read
      @read_pipe.each(*args)
    end

    def each_byte(*args)
      assert_can_read
      @read_pipe.each_byte(*args)
    end

    def each_char(*args)
      assert_can_read
      @read_pipe.each_char(*args)
    end

    def each_codepoint(*args)
      assert_can_read
      @read_pipe.each_codepoint(*args)
    end

    def each_line(*args)
      assert_can_read
      @read_pipe.each_line(*args)
    end

    def getbyte(*args)
      assert_can_read
      @read_pipe.getbyte(*args)
    end

    def getc(*args)
      assert_can_read
      @read_pipe.getc(*args)
    end

    def gets(*args)
      assert_can_read
      @read_pipe.gets(*args)
    end

    def read(*args)
      assert_can_read
      @read_pipe.read(*args)
    end

    def read_nonblock(*args)
      assert_can_read
      @read_pipe.read_nonblock(*args)
    end

    def readbyte(*args)
      assert_can_read
      @read_pipe.readbyte(*args)
    end

    def readchar(*args)
      assert_can_read
      @read_pipe.readchar(*args)
    end

    def readline(*args)
      assert_can_read
      @read_pipe.readline(*args)
    end

    def readlines(*args)
      assert_can_read
      @read_pipe.readlines(*args)
    end

    def readpartial(*args)
      assert_can_read
      @read_pipe.readpartial(*args)
    end

    def sysread(*args)
      assert_can_read
      @read_pipe.sysread(*args)
    end

    def ungetbyte(*args)
      assert_can_read
      @read_pipe.ungetbyte(*args)
    end

    def ungetc(*args)
      assert_can_read
      @read_pipe.ungetc(*args)
    end
  end
end
