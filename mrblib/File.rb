#<
# # Class File
#>
class File < IO
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
      return APR::File.unlock(self.fileno)
    end

    apr_flags = []
    if (locking_constant & File::LOCK_EX) > 0
      apr_flags << APR::File::APR_FLOCK_EXCLUSIVE
    end
    if (locking_constant & File::LOCK_SH) > 0
      apr_flags << APR::File::APR_FLOCK_SHARED
    end
    if (locking_constant & File::LOCK_NB) > 0
      apr_flags << APR::File::APR_FLOCK_NONBLOCK
    end

    apr_lock_type = apr_flags.inject(0) { |acc, cur| (acc | cur) }
    APR::File.lock(self.fileno, apr_lock_type)
  end
end
