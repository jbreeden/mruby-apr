struct RClass* errno_module = mrb_define_module_under(mrb, APR_module(mrb), "Errno");
#ifdef E2BIG
  mrb_define_const(mrb, errno_module, "E2BIG", mrb_fixnum_value(E2BIG));
#endif
#ifdef EACCES
  mrb_define_const(mrb, errno_module, "EACCES", mrb_fixnum_value(EACCES));
#endif
#ifdef EADDRINUSE
  mrb_define_const(mrb, errno_module, "EADDRINUSE", mrb_fixnum_value(EADDRINUSE));
#endif
#ifdef EADDRNOTAVAIL
  mrb_define_const(mrb, errno_module, "EADDRNOTAVAIL", mrb_fixnum_value(EADDRNOTAVAIL));
#endif
#ifdef EAFNOSUPPORT
  mrb_define_const(mrb, errno_module, "EAFNOSUPPORT", mrb_fixnum_value(EAFNOSUPPORT));
#endif
#ifdef EAGAIN
  mrb_define_const(mrb, errno_module, "EAGAIN", mrb_fixnum_value(EAGAIN));
#endif
#ifdef EALREADY
  mrb_define_const(mrb, errno_module, "EALREADY", mrb_fixnum_value(EALREADY));
#endif
#ifdef EAUTH
  mrb_define_const(mrb, errno_module, "EAUTH", mrb_fixnum_value(EAUTH));
#endif
#ifdef EBADARCH
  mrb_define_const(mrb, errno_module, "EBADARCH", mrb_fixnum_value(EBADARCH));
#endif
#ifdef EBADEXEC
  mrb_define_const(mrb, errno_module, "EBADEXEC", mrb_fixnum_value(EBADEXEC));
#endif
#ifdef EBADF
  mrb_define_const(mrb, errno_module, "EBADF", mrb_fixnum_value(EBADF));
#endif
#ifdef EBADMACHO
  mrb_define_const(mrb, errno_module, "EBADMACHO", mrb_fixnum_value(EBADMACHO));
#endif
#ifdef EBADMSG
  mrb_define_const(mrb, errno_module, "EBADMSG", mrb_fixnum_value(EBADMSG));
#endif
#ifdef EBADRPC
  mrb_define_const(mrb, errno_module, "EBADRPC", mrb_fixnum_value(EBADRPC));
#endif
#ifdef EBUSY
  mrb_define_const(mrb, errno_module, "EBUSY", mrb_fixnum_value(EBUSY));
#endif
#ifdef ECANCELED
  mrb_define_const(mrb, errno_module, "ECANCELED", mrb_fixnum_value(ECANCELED));
#endif
#ifdef ECHILD
  mrb_define_const(mrb, errno_module, "ECHILD", mrb_fixnum_value(ECHILD));
#endif
#ifdef ECONNABORTED
  mrb_define_const(mrb, errno_module, "ECONNABORTED", mrb_fixnum_value(ECONNABORTED));
#endif
#ifdef ECONNREFUSED
  mrb_define_const(mrb, errno_module, "ECONNREFUSED", mrb_fixnum_value(ECONNREFUSED));
#endif
#ifdef ECONNRESET
  mrb_define_const(mrb, errno_module, "ECONNRESET", mrb_fixnum_value(ECONNRESET));
#endif
#ifdef EDEADLK
  mrb_define_const(mrb, errno_module, "EDEADLK", mrb_fixnum_value(EDEADLK));
#endif
#ifdef EDESTADDRREQ
  mrb_define_const(mrb, errno_module, "EDESTADDRREQ", mrb_fixnum_value(EDESTADDRREQ));
#endif
#ifdef EDEVERR
  mrb_define_const(mrb, errno_module, "EDEVERR", mrb_fixnum_value(EDEVERR));
#endif
#ifdef EDOM
  mrb_define_const(mrb, errno_module, "EDOM", mrb_fixnum_value(EDOM));
#endif
#ifdef EDQUOT
  mrb_define_const(mrb, errno_module, "EDQUOT", mrb_fixnum_value(EDQUOT));
#endif
#ifdef EEXIST
  mrb_define_const(mrb, errno_module, "EEXIST", mrb_fixnum_value(EEXIST));
#endif
#ifdef EFAULT
  mrb_define_const(mrb, errno_module, "EFAULT", mrb_fixnum_value(EFAULT));
#endif
#ifdef EFBIG
  mrb_define_const(mrb, errno_module, "EFBIG", mrb_fixnum_value(EFBIG));
#endif
#ifdef EFTYPE
  mrb_define_const(mrb, errno_module, "EFTYPE", mrb_fixnum_value(EFTYPE));
#endif
#ifdef EHOSTDOWN
  mrb_define_const(mrb, errno_module, "EHOSTDOWN", mrb_fixnum_value(EHOSTDOWN));
#endif
#ifdef EHOSTUNREACH
  mrb_define_const(mrb, errno_module, "EHOSTUNREACH", mrb_fixnum_value(EHOSTUNREACH));
#endif
#ifdef EIDRM
  mrb_define_const(mrb, errno_module, "EIDRM", mrb_fixnum_value(EIDRM));
#endif
#ifdef EILSEQ
  mrb_define_const(mrb, errno_module, "EILSEQ", mrb_fixnum_value(EILSEQ));
#endif
#ifdef EINPROGRESS
  mrb_define_const(mrb, errno_module, "EINPROGRESS", mrb_fixnum_value(EINPROGRESS));
#endif
#ifdef EINTR
  mrb_define_const(mrb, errno_module, "EINTR", mrb_fixnum_value(EINTR));
#endif
#ifdef EINVAL
  mrb_define_const(mrb, errno_module, "EINVAL", mrb_fixnum_value(EINVAL));
#endif
#ifdef EIO
  mrb_define_const(mrb, errno_module, "EIO", mrb_fixnum_value(EIO));
#endif
#ifdef EISCONN
  mrb_define_const(mrb, errno_module, "EISCONN", mrb_fixnum_value(EISCONN));
#endif
#ifdef EISDIR
  mrb_define_const(mrb, errno_module, "EISDIR", mrb_fixnum_value(EISDIR));
#endif
#ifdef ELAST
  mrb_define_const(mrb, errno_module, "ELAST", mrb_fixnum_value(ELAST));
#endif
#ifdef ELOOP
  mrb_define_const(mrb, errno_module, "ELOOP", mrb_fixnum_value(ELOOP));
#endif
#ifdef EMFILE
  mrb_define_const(mrb, errno_module, "EMFILE", mrb_fixnum_value(EMFILE));
#endif
#ifdef EMLINK
  mrb_define_const(mrb, errno_module, "EMLINK", mrb_fixnum_value(EMLINK));
#endif
#ifdef EMSGSIZE
  mrb_define_const(mrb, errno_module, "EMSGSIZE", mrb_fixnum_value(EMSGSIZE));
#endif
#ifdef EMULTIHOP
  mrb_define_const(mrb, errno_module, "EMULTIHOP", mrb_fixnum_value(EMULTIHOP));
#endif
#ifdef ENAMETOOLONG
  mrb_define_const(mrb, errno_module, "ENAMETOOLONG", mrb_fixnum_value(ENAMETOOLONG));
#endif
#ifdef ENEEDAUTH
  mrb_define_const(mrb, errno_module, "ENEEDAUTH", mrb_fixnum_value(ENEEDAUTH));
#endif
#ifdef ENETDOWN
  mrb_define_const(mrb, errno_module, "ENETDOWN", mrb_fixnum_value(ENETDOWN));
#endif
#ifdef ENETRESET
  mrb_define_const(mrb, errno_module, "ENETRESET", mrb_fixnum_value(ENETRESET));
#endif
#ifdef ENETUNREACH
  mrb_define_const(mrb, errno_module, "ENETUNREACH", mrb_fixnum_value(ENETUNREACH));
#endif
#ifdef ENFILE
  mrb_define_const(mrb, errno_module, "ENFILE", mrb_fixnum_value(ENFILE));
#endif
#ifdef ENOATTR
  mrb_define_const(mrb, errno_module, "ENOATTR", mrb_fixnum_value(ENOATTR));
#endif
#ifdef ENOBUFS
  mrb_define_const(mrb, errno_module, "ENOBUFS", mrb_fixnum_value(ENOBUFS));
#endif
#ifdef ENODATA
  mrb_define_const(mrb, errno_module, "ENODATA", mrb_fixnum_value(ENODATA));
#endif
#ifdef ENODEV
  mrb_define_const(mrb, errno_module, "ENODEV", mrb_fixnum_value(ENODEV));
#endif
#ifdef ENOENT
  mrb_define_const(mrb, errno_module, "ENOENT", mrb_fixnum_value(ENOENT));
#endif
#ifdef ENOEXEC
  mrb_define_const(mrb, errno_module, "ENOEXEC", mrb_fixnum_value(ENOEXEC));
#endif
#ifdef ENOLCK
  mrb_define_const(mrb, errno_module, "ENOLCK", mrb_fixnum_value(ENOLCK));
#endif
#ifdef ENOLINK
  mrb_define_const(mrb, errno_module, "ENOLINK", mrb_fixnum_value(ENOLINK));
#endif
#ifdef ENOMEM
  mrb_define_const(mrb, errno_module, "ENOMEM", mrb_fixnum_value(ENOMEM));
#endif
#ifdef ENOMSG
  mrb_define_const(mrb, errno_module, "ENOMSG", mrb_fixnum_value(ENOMSG));
#endif
#ifdef ENOPOLICY
  mrb_define_const(mrb, errno_module, "ENOPOLICY", mrb_fixnum_value(ENOPOLICY));
#endif
#ifdef ENOPROTOOPT
  mrb_define_const(mrb, errno_module, "ENOPROTOOPT", mrb_fixnum_value(ENOPROTOOPT));
#endif
#ifdef ENOSPC
  mrb_define_const(mrb, errno_module, "ENOSPC", mrb_fixnum_value(ENOSPC));
#endif
#ifdef ENOSR
  mrb_define_const(mrb, errno_module, "ENOSR", mrb_fixnum_value(ENOSR));
#endif
#ifdef ENOSTR
  mrb_define_const(mrb, errno_module, "ENOSTR", mrb_fixnum_value(ENOSTR));
#endif
#ifdef ENOSYS
  mrb_define_const(mrb, errno_module, "ENOSYS", mrb_fixnum_value(ENOSYS));
#endif
#ifdef ENOTBLK
  mrb_define_const(mrb, errno_module, "ENOTBLK", mrb_fixnum_value(ENOTBLK));
#endif
#ifdef ENOTCONN
  mrb_define_const(mrb, errno_module, "ENOTCONN", mrb_fixnum_value(ENOTCONN));
#endif
#ifdef ENOTDIR
  mrb_define_const(mrb, errno_module, "ENOTDIR", mrb_fixnum_value(ENOTDIR));
#endif
#ifdef ENOTEMPTY
  mrb_define_const(mrb, errno_module, "ENOTEMPTY", mrb_fixnum_value(ENOTEMPTY));
#endif
#ifdef ENOTRECOVERABLE
  mrb_define_const(mrb, errno_module, "ENOTRECOVERABLE", mrb_fixnum_value(ENOTRECOVERABLE));
#endif
#ifdef ENOTSOCK
  mrb_define_const(mrb, errno_module, "ENOTSOCK", mrb_fixnum_value(ENOTSOCK));
#endif
#ifdef ENOTSUP
  mrb_define_const(mrb, errno_module, "ENOTSUP", mrb_fixnum_value(ENOTSUP));
#endif
#ifdef ENOTTY
  mrb_define_const(mrb, errno_module, "ENOTTY", mrb_fixnum_value(ENOTTY));
#endif
#ifdef ENXIO
  mrb_define_const(mrb, errno_module, "ENXIO", mrb_fixnum_value(ENXIO));
#endif
#ifdef EOPNOTSUPP
  mrb_define_const(mrb, errno_module, "EOPNOTSUPP", mrb_fixnum_value(EOPNOTSUPP));
#endif
#ifdef EOVERFLOW
  mrb_define_const(mrb, errno_module, "EOVERFLOW", mrb_fixnum_value(EOVERFLOW));
#endif
#ifdef EOWNERDEAD
  mrb_define_const(mrb, errno_module, "EOWNERDEAD", mrb_fixnum_value(EOWNERDEAD));
#endif
#ifdef EPERM
  mrb_define_const(mrb, errno_module, "EPERM", mrb_fixnum_value(EPERM));
#endif
#ifdef EPFNOSUPPORT
  mrb_define_const(mrb, errno_module, "EPFNOSUPPORT", mrb_fixnum_value(EPFNOSUPPORT));
#endif
#ifdef EPIPE
  mrb_define_const(mrb, errno_module, "EPIPE", mrb_fixnum_value(EPIPE));
#endif
#ifdef EPROCLIM
  mrb_define_const(mrb, errno_module, "EPROCLIM", mrb_fixnum_value(EPROCLIM));
#endif
#ifdef EPROCUNAVAIL
  mrb_define_const(mrb, errno_module, "EPROCUNAVAIL", mrb_fixnum_value(EPROCUNAVAIL));
#endif
#ifdef EPROGMISMATCH
  mrb_define_const(mrb, errno_module, "EPROGMISMATCH", mrb_fixnum_value(EPROGMISMATCH));
#endif
#ifdef EPROGUNAVAIL
  mrb_define_const(mrb, errno_module, "EPROGUNAVAIL", mrb_fixnum_value(EPROGUNAVAIL));
#endif
#ifdef EPROTO
  mrb_define_const(mrb, errno_module, "EPROTO", mrb_fixnum_value(EPROTO));
#endif
#ifdef EPROTONOSUPPORT
  mrb_define_const(mrb, errno_module, "EPROTONOSUPPORT", mrb_fixnum_value(EPROTONOSUPPORT));
#endif
#ifdef EPROTOTYPE
  mrb_define_const(mrb, errno_module, "EPROTOTYPE", mrb_fixnum_value(EPROTOTYPE));
#endif
#ifdef EPWROFF
  mrb_define_const(mrb, errno_module, "EPWROFF", mrb_fixnum_value(EPWROFF));
#endif
#ifdef EQFULL
  mrb_define_const(mrb, errno_module, "EQFULL", mrb_fixnum_value(EQFULL));
#endif
#ifdef ERANGE
  mrb_define_const(mrb, errno_module, "ERANGE", mrb_fixnum_value(ERANGE));
#endif
#ifdef EREMOTE
  mrb_define_const(mrb, errno_module, "EREMOTE", mrb_fixnum_value(EREMOTE));
#endif
#ifdef EROFS
  mrb_define_const(mrb, errno_module, "EROFS", mrb_fixnum_value(EROFS));
#endif
#ifdef ERPCMISMATCH
  mrb_define_const(mrb, errno_module, "ERPCMISMATCH", mrb_fixnum_value(ERPCMISMATCH));
#endif
#ifdef ESHLIBVERS
  mrb_define_const(mrb, errno_module, "ESHLIBVERS", mrb_fixnum_value(ESHLIBVERS));
#endif
#ifdef ESHUTDOWN
  mrb_define_const(mrb, errno_module, "ESHUTDOWN", mrb_fixnum_value(ESHUTDOWN));
#endif
#ifdef ESOCKTNOSUPPORT
  mrb_define_const(mrb, errno_module, "ESOCKTNOSUPPORT", mrb_fixnum_value(ESOCKTNOSUPPORT));
#endif
#ifdef ESPIPE
  mrb_define_const(mrb, errno_module, "ESPIPE", mrb_fixnum_value(ESPIPE));
#endif
#ifdef ESRCH
  mrb_define_const(mrb, errno_module, "ESRCH", mrb_fixnum_value(ESRCH));
#endif
#ifdef ESTALE
  mrb_define_const(mrb, errno_module, "ESTALE", mrb_fixnum_value(ESTALE));
#endif
#ifdef ETIME
  mrb_define_const(mrb, errno_module, "ETIME", mrb_fixnum_value(ETIME));
#endif
#ifdef ETIMEDOUT
  mrb_define_const(mrb, errno_module, "ETIMEDOUT", mrb_fixnum_value(ETIMEDOUT));
#endif
#ifdef ETOOMANYREFS
  mrb_define_const(mrb, errno_module, "ETOOMANYREFS", mrb_fixnum_value(ETOOMANYREFS));
#endif
#ifdef ETXTBSY
  mrb_define_const(mrb, errno_module, "ETXTBSY", mrb_fixnum_value(ETXTBSY));
#endif
#ifdef EUSERS
  mrb_define_const(mrb, errno_module, "EUSERS", mrb_fixnum_value(EUSERS));
#endif
#ifdef EWOULDBLOCK
  mrb_define_const(mrb, errno_module, "EWOULDBLOCK", mrb_fixnum_value(EWOULDBLOCK));
#endif
#ifdef EXDEV
  mrb_define_const(mrb, errno_module, "EXDEV", mrb_fixnum_value(EXDEV));
#endif
