class PipeFile < File
  def initialize(apr_file, mode, shared_pool)
    if apr_file.class != APR::AprFileT
      raise ArgumentError.new("AprFileT expected in first arg")
    end
    if shared_pool.class != APR::SharedPool
      raise ArgumentError.new("SharedPool expected in third arg")
    end
    @native_file = apr_file
    @shared_pool = shared_pool
    @shared_pool.join(self)

    if mode.class == Fixnum
      @flags = mode
    else
      @flags = File::Util.mode_str_to_flags(mode.to_s)
    end
    @closed = false
  end

  def close
    APR.apr_file_flush(@native_file)
    APR.apr_file_close(@native_file)
    @shared_pool.leave(self)
    @closed = true
  end
end
