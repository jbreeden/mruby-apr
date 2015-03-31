# Class APR::File

## `::lock(fd, lock_type)`
Obtains a file lock on the file with file descriptor `fd`
- Args
  + `fd`: The integer file descriptor for the file to lock.
    Note that you can obtain this from a `::File` (not `APR::File`) by `#fileno`
  + `lock_type`: Bitwise OR of
    - `APR::File::APR_FLOCK_EXCLUSIVE` (Gets an exclusive lock)
    - `APR::File::APR_FLOCK_SHARED` (Gets a shared lock)
    - `APR::File::APR_FLOCK_NONBLOCK` (Do not block. If the lock cannot be obtained immediately, return `false`)
- Returns `true` if the lock was obtained, else `false`
- Notes
  + Don't combine `APR::File::APR_FLOCK_EXCLUSIVE` with `APR::File::APR_FLOCK_SHARED`.
    The only combination that makes sense is one of those values with `APR::File::APR_FLOCK_NONBLOCK`
  + The constant names (like `APR_FLOCK_EXCLUSIVE`) may seem a bit repetitive, but they provide a 1-to-1 mapping
    to the C values from the APR library.
- Ex:
```Ruby
APR::File.lock(f.fileno, APR::File::APR_FLOCK_EXCLUSIVE)
# Do your work...
APR::File.unlock(f.fileno)
```

## `::unlock(fd)`
Release any held locks on the file with file descriptor `fd`
- Args
  + `fd`: The integer file descriptor for the file to lock.
    Note that you can obtain this from a `::File` (not `APR::File`) by `#fileno`
- Ex:
```Ruby
f = File.open('text.txt', 'r')
got_lock APR::File.lock(f.fileno, APR::File::APR_FLOCK_EXCLUSIVE | APR::File::APR_FLOCK_NONBLOCK)
if got_lock
   # Do your work...
end
APR::File.unlock(f.fileno)
```

