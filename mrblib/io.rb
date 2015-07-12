class IO
  def self.pipe
    shared_pool = APR::SharedPool.new

    err, readEnd, writeEnd = APR.apr_file_pipe_create shared_pool.pool
    APR.raise_apr_errno(err)

    read_file = PipeFile.new(readEnd, 'r', shared_pool)
    write_file = PipeFile.new(writeEnd, 'w', shared_pool)

    [read_file, write_file]
  end

  def self.popen()

  end
end
