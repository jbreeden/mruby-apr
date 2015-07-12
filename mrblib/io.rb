class IO
  module Util
    def self.mode_str_to_apr_flags(mode)
      case mode
      when 'r'
        APR::APR_FOPEN_READ
      when 'w'
        APR::APR_FOPEN_WRITE | APR::APR_FOPEN_CREATE | APR::APR_FOPEN_TRUNCATE
      when 'a'
        APR::APR_FOPEN_WRITE | APR::APR_FOPEN_CREATE | APR::APR_FOPEN_APPEND
      when 'r+'
        APR::APR_FOPEN_READ | APR::APR_FOPEN_WRITE
      when 'w+'
        APR::APR_FOPEN_READ | APR::APR_FOPEN_WRITE | APR::APR_FOPEN_CREATE | APR::APR_FOPEN_TRUNCATE
      when 'a+'
        APR::APR_FOPEN_READ | APR::APR_FOPEN_WRITE | APR::APR_FOPEN_CREATE | APR::APR_FOPEN_APPEND
      else
        raise ArgumentError.new("Invalid access mode #{mode}")
      end
    end
  end

  # Not using these yet... but here they are, ripped from CRuby
  SEEK_SET = 0
  SEEK_CUR = 1
  SEEK_END = 2
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
  FNM_NOESCAPE = 1
  FNM_PATHNAME = 2
  FNM_DOTMATCH = 4
  FNM_CASEFOLD = 8
  FNM_EXTGLOB = 16
  FNM_SYSCASE = 0

  def self.pipe
    shared_pool = APR::SharedPool.new

    err, readEnd, writeEnd = APR.apr_file_pipe_create shared_pool.pool
    APR.raise_apr_errno(err)

    read_file = Pipe.new(readEnd, 'r', shared_pool)
    write_file = Pipe.new(writeEnd, 'w', shared_pool)
    read_file.sibling = write_file
    write_file.sibling = read_file

    [read_file, write_file]
  end

  def self.popen(*command)
    env = {}
    cmd = nil
    mode = "r"
    opt = {}

    if command.length == 0 || command.length > 4
      raise ArgumentError.new("Wrong number of arguments. #{command.length} for 1..4")
    end
    if command.first.class == Hash
      env = command.shift
    end
    if command.last.class == Hash
      opt = command.pop
    end
    cmd = command.shift
    unless command.empty?
      mode = command.shift
    end

    # mode_str_to_apr_flags throws on invalid, so input is sanitized after
    flags = IO::Util.mode_str_to_apr_flags(mode)
    child_in_pipe_ends = []
    child_out_pipe_ends = []
    read_pipe = nil  # These are set while interpretting the mode
    write_pipe = nil # string, and used to construct the BidirectionalPipe
    if (flags & APR::APR_FOPEN_WRITE) != 0
      child_in_pipe_ends = IO.pipe       # => [read, write]
      opt[:in]   = child_in_pipe_ends[0] # Give child read end
      write_pipe = child_in_pipe_ends[1] # We keep the write end
      # Don't let the child inherit our side of the pipe
      APR.apr_file_inherit_unset(write_pipe.native_file)
    end
    if (flags & APR::APR_FOPEN_READ) != 0
      child_out_pipe_ends = IO.pipe      # => [read, write]
      opt[:out] = child_out_pipe_ends[1] # Give child write end
      read_pipe = child_out_pipe_ends[0] # We keep the read end
      # Don't let the child inherit our side of the pipe
      APR.apr_file_inherit_unset(read_pipe.native_file)
    end

    pid = Process.spawn(env, *cmd, opt)

    # Close the ends of the pipes that belong to the child
    # (This makes sure, for example, end of file is sent when the child
    #  closes their end of stdout )
    if read_pipe
      # We're "reading" the output, so close the write end of the ouput
      child_out_pipe_ends[1].close
      # Don't let the child inherit our side of the pipe
      APR.apr_file_inherit_unset(read_pipe.native_file)
    end
    if write_pipe
      # We're "writing" to the input, so close the read end of the input
      child_in_pipe_ends[0].close
    end

    bidirectional_pipe = BidirectionalPipe.new({
      pid: pid,
      read: read_pipe,
      write: write_pipe
    })

    if block_given?
      yield[bidirectional_pipe]
      bidirectional_pipe.close
    else
      return bidirectional_pipe
    end
  end
end
