#include "mruby.h"
#include "mruby_apr.h"
#include "apr.h"
#include "apr_pools.h"
#include "apr_portable.h"
#include "apr_file_io.h"

#if defined(_WIN32) || defined(_WIN64)
// Need this to convert HANDLES to file descriptors
#include "io.h"
#endif

static
apr_file_t* fd_to_apr_file_t(int fd, apr_pool_t* pool) {
#if defined(_WIN32) || defined(_WIN64)
   apr_os_file_t os_file = (apr_os_file_t)_get_osfhandle(fd);
#else
   apr_os_file_t os_file = (apr_os_file_t)(fd);
#endif
   apr_file_t* apr_file;
   apr_os_file_put(&apr_file, &os_file, NULL, pool);
   return apr_file;
}

//<
// # Class APR::File
//>

//<
// ## `::lock(fd, lock_type)`
// Obtains a file lock on the file with file descriptor `fd`
// - Args
//   + `fd`: The integer file descriptor for the file to lock.
//     Note that you can obtain this from a `::File` (not `APR::File`) by `#fileno`
//   + `lock_type`: Bitwise OR of
//     - `APR::File::APR_FLOCK_EXCLUSIVE` (Gets an exclusive lock)
//     - `APR::File::APR_FLOCK_SHARED` (Gets a shared lock)
//     - `APR::File::APR_FLOCK_NONBLOCK` (Do not block. If the lock cannot be obtained immediately, return `false`)
// - Returns `true` if the lock was obtained, else `false`
// - Notes
//   + Don't combine `APR::File::APR_FLOCK_EXCLUSIVE` with `APR::File::APR_FLOCK_SHARED`.
//     The only combination that makes sense is one of those values with `APR::File::APR_FLOCK_NONBLOCK`
//   + The constant names (like `APR_FLOCK_EXCLUSIVE`) may seem a bit repetitive, but they provide a 1-to-1 mapping
//     to the C values from the APR library.
// - Ex:
// ```Ruby
// APR::File.lock(f.fileno, APR::File::APR_FLOCK_EXCLUSIVE)
// # Do your work...
// APR::File.unlock(f.fileno)
// ```
//>
mrb_value
mrb_apr_file_lock(mrb_state* mrb, mrb_value self) {
   mrb_int fd;
   mrb_int lock_type;
   mrb_get_args(mrb, "ii", &fd, &lock_type);

   apr_pool_t* pool;
   apr_pool_create(&pool, NULL);
   apr_file_t* apr_file = fd_to_apr_file_t(fd, pool);

   mrb_value result;
   if (APR_SUCCESS == apr_file_lock(apr_file, lock_type)) {
      SET_BOOL_VALUE(result, true);
   }
   else {
      SET_BOOL_VALUE(result, false);
   }

   apr_pool_destroy(pool);

   return result;
}

//<
// ## `::unlock(fd)`
// Release any held locks on the file with file descriptor `fd`
// - Args
//   + `fd`: The integer file descriptor for the file to lock.
//     Note that you can obtain this from a `::File` (not `APR::File`) by `#fileno`
// - Ex:
// ```Ruby
// f = File.open('text.txt', 'r')
// got_lock APR::File.lock(f.fileno, APR::File::APR_FLOCK_EXCLUSIVE | APR::File::APR_FLOCK_NONBLOCK)
// if got_lock
//    # Do your work...
// end
// APR::File.unlock(f.fileno)
// ```
//>
mrb_value
mrb_apr_file_unlock(mrb_state* mrb, mrb_value self) {
   mrb_int fd;
   mrb_get_args(mrb, "i", &fd);

   apr_pool_t* pool;
   apr_pool_create(&pool, NULL);
   apr_file_t* apr_file = fd_to_apr_file_t(fd, pool);

   mrb_value result;
   if (APR_SUCCESS == apr_file_unlock(apr_file)) {
      SET_BOOL_VALUE(result, true);
   }
   else {
      SET_BOOL_VALUE(result, false);
   }

   apr_pool_destroy(pool);

   return result;
}

void define_flock_constants(mrb_state* mrb, RClass* apr_file_class) {
   mrb_value exclusive;
   SET_INT_VALUE(exclusive, APR_FLOCK_EXCLUSIVE);
   mrb_define_const(mrb, apr_file_class, "APR_FLOCK_EXCLUSIVE", exclusive);

   mrb_value shared;
   SET_INT_VALUE(shared, APR_FLOCK_SHARED);
   mrb_define_const(mrb, apr_file_class, "APR_FLOCK_SHARED", shared);

   mrb_value nonblock;
   SET_INT_VALUE(nonblock, APR_FLOCK_NONBLOCK);
   mrb_define_const(mrb, apr_file_class, "APR_FLOCK_NONBLOCK", nonblock);
}

void mrb_mruby_apr_file_init(mrb_state* mrb, RClass* apr_module) {
   // File Methods
   RClass* apr_file_class = mrb_define_class_under(mrb, apr_module, "File", mrb->object_class);
   define_flock_constants(mrb, apr_file_class);
   mrb_define_class_method(mrb, apr_file_class, "lock", mrb_apr_file_lock, MRB_ARGS_REQ(2));
   mrb_define_class_method(mrb, apr_file_class, "unlock", mrb_apr_file_unlock, MRB_ARGS_REQ(1));
}
