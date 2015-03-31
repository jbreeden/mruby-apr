# Class File

## `#flock(locking_constant)`
Locks or unlocks a file according to locking_constant.
- Args
  + `locking_constant` Bitwise or of
    - `File::LOCK_EX` (Get an exclusive lock)
    - `File::LOCK_NB` (Do not block)
    - `File::LOCK_SH` (Get a shared lock)
    - `File::LOCK_UN` (Release any held locks)
- Returns false if File::LOCK_NB is specified and the operation would otherwise have blocked.

