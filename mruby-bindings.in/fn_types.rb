# ## apr_status_t apr_allocator_create(apr_allocator_t ** allocator)
# # Param: allocator (apr_allocator_t **)
# CTypes.set_fn_param_type('apr_allocator_create', 'allocator', CTypes['???'])

# ## apr_status_t apr_app_initialize(int * argc, const char *const ** argv, const char *const ** env)
# # Param: argc (int *)
# CTypes.set_fn_param_type('apr_app_initialize', 'argc', CTypes['???'])
# # Param: argv (const char *const **)
# CTypes.set_fn_param_type('apr_app_initialize', 'argv', CTypes['???'])
# # Param: env (const char *const **)
# CTypes.set_fn_param_type('apr_app_initialize', 'env', CTypes['???'])

# ## void * apr_array_pop(apr_array_header_t * arr)
# # Return value (void *)
# CTypes.set_fn_return_type('apr_array_pop', CTypes['???'])

# ## char * apr_array_pstrcat(apr_pool_t * p, const apr_array_header_t * arr, const char sep)
# # Return value (char *)
# CTypes.set_fn_return_type('apr_array_pstrcat', CTypes['???'])

# ## void * apr_array_push(apr_array_header_t * arr)
# # Return value (void *)
# CTypes.set_fn_return_type('apr_array_push', CTypes['???'])

# ## apr_int64_t apr_atoi64(const char * buf)
# # Return value (apr_int64_t)
# CTypes.set_fn_return_type('apr_atoi64', CTypes['???'])

# ## apr_uint32_t apr_atomic_add32(volatile apr_uint32_t * mem, apr_uint32_t val)
# # Param: mem (volatile apr_uint32_t *)
# CTypes.set_fn_param_type('apr_atomic_add32', 'mem', CTypes['???'])

# ## apr_uint32_t apr_atomic_cas32(volatile apr_uint32_t * mem, apr_uint32_t with, apr_uint32_t cmp)
# # Param: mem (volatile apr_uint32_t *)
# CTypes.set_fn_param_type('apr_atomic_cas32', 'mem', CTypes['???'])

# ## void * apr_atomic_casptr(volatile void ** mem, void * with, const void * cmp)
# # Return value (void *)
# CTypes.set_fn_return_type('apr_atomic_casptr', CTypes['???'])
# # Param: mem (volatile void **)
# CTypes.set_fn_param_type('apr_atomic_casptr', 'mem', CTypes['???'])
# # Param: with (void *)
# CTypes.set_fn_param_type('apr_atomic_casptr', 'with', CTypes['???'])
# # Param: cmp (const void *)
# CTypes.set_fn_param_type('apr_atomic_casptr', 'cmp', CTypes['???'])

# ## int apr_atomic_dec32(volatile apr_uint32_t * mem)
# # Param: mem (volatile apr_uint32_t *)
# CTypes.set_fn_param_type('apr_atomic_dec32', 'mem', CTypes['???'])

# ## apr_uint32_t apr_atomic_inc32(volatile apr_uint32_t * mem)
# # Param: mem (volatile apr_uint32_t *)
# CTypes.set_fn_param_type('apr_atomic_inc32', 'mem', CTypes['???'])

# ## apr_uint32_t apr_atomic_read32(volatile apr_uint32_t * mem)
# # Param: mem (volatile apr_uint32_t *)
# CTypes.set_fn_param_type('apr_atomic_read32', 'mem', CTypes['???'])

# ## void apr_atomic_set32(volatile apr_uint32_t * mem, apr_uint32_t val)
# # Param: mem (volatile apr_uint32_t *)
# CTypes.set_fn_param_type('apr_atomic_set32', 'mem', CTypes['???'])

# ## void apr_atomic_sub32(volatile apr_uint32_t * mem, apr_uint32_t val)
# # Param: mem (volatile apr_uint32_t *)
# CTypes.set_fn_param_type('apr_atomic_sub32', 'mem', CTypes['???'])

# ## apr_uint32_t apr_atomic_xchg32(volatile apr_uint32_t * mem, apr_uint32_t val)
# # Param: mem (volatile apr_uint32_t *)
# CTypes.set_fn_param_type('apr_atomic_xchg32', 'mem', CTypes['???'])

# ## void * apr_atomic_xchgptr(volatile void ** mem, void * with)
# # Return value (void *)
# CTypes.set_fn_return_type('apr_atomic_xchgptr', CTypes['???'])
# # Param: mem (volatile void **)
# CTypes.set_fn_param_type('apr_atomic_xchgptr', 'mem', CTypes['???'])
# # Param: with (void *)
# CTypes.set_fn_param_type('apr_atomic_xchgptr', 'with', CTypes['???'])

# ## int apr_base64_decode(char * plain_dst, const char * coded_src)
# # Param: plain_dst (char *)
# CTypes.set_fn_param_type('apr_base64_decode', 'plain_dst', CTypes['???'])

# ## int apr_base64_decode_binary(unsigned char * plain_dst, const char * coded_src)
# # Param: plain_dst (unsigned char *)
# CTypes.set_fn_param_type('apr_base64_decode_binary', 'plain_dst', CTypes['???'])

# ## int apr_base64_encode(char * coded_dst, const char * plain_src, int len_plain_src)
# # Param: coded_dst (char *)
# CTypes.set_fn_param_type('apr_base64_encode', 'coded_dst', CTypes['???'])

# ## int apr_base64_encode_binary(char * coded_dst, const unsigned char * plain_src, int len_plain_src)
# # Param: coded_dst (char *)
# CTypes.set_fn_param_type('apr_base64_encode_binary', 'coded_dst', CTypes['???'])
# # Param: plain_src (const unsigned char *)
# CTypes.set_fn_param_type('apr_base64_encode_binary', 'plain_src', CTypes['???'])

# ## apr_status_t apr_bcrypt_encode(const char * pw, unsigned int count, const unsigned char * salt, apr_size_t salt_len, char * out, apr_size_t out_len)
# # Param: salt (const unsigned char *)
# CTypes.set_fn_param_type('apr_bcrypt_encode', 'salt', CTypes['???'])
# # Param: out (char *)
# CTypes.set_fn_param_type('apr_bcrypt_encode', 'out', CTypes['???'])

# ## apr_status_t apr_brigade_cleanup(void * data)
# # Param: data (void *)
# CTypes.set_fn_param_type('apr_brigade_cleanup', 'data', CTypes['???'])

# ## apr_status_t apr_brigade_flatten(apr_bucket_brigade * bb, char * c, apr_size_t * len)
# # Param: c (char *)
# CTypes.set_fn_param_type('apr_brigade_flatten', 'c', CTypes['???'])
# # Param: len (apr_size_t *)
# CTypes.set_fn_param_type('apr_brigade_flatten', 'len', CTypes['???'])

# ## apr_bucket * apr_brigade_insert_file(apr_bucket_brigade * bb, apr_file_t * f, apr_off_t start, apr_off_t len, apr_pool_t * p)
# # Param: start (apr_off_t)
# CTypes.set_fn_param_type('apr_brigade_insert_file', 'start', CTypes['???'])
# # Param: len (apr_off_t)
# CTypes.set_fn_param_type('apr_brigade_insert_file', 'len', CTypes['???'])

# ## apr_status_t apr_brigade_length(apr_bucket_brigade * bb, int read_all, apr_off_t * length)
# # Param: length (apr_off_t *)
# CTypes.set_fn_param_type('apr_brigade_length', 'length', CTypes['???'])

# ## apr_status_t apr_brigade_partition(apr_bucket_brigade * b, apr_off_t point, apr_bucket ** after_point)
# # Param: point (apr_off_t)
# CTypes.set_fn_param_type('apr_brigade_partition', 'point', CTypes['???'])
# # Param: after_point (apr_bucket **)
# CTypes.set_fn_param_type('apr_brigade_partition', 'after_point', CTypes['???'])

# ## apr_status_t apr_brigade_pflatten(apr_bucket_brigade * bb, char ** c, apr_size_t * len, apr_pool_t * pool)
# # Param: c (char **)
# CTypes.set_fn_param_type('apr_brigade_pflatten', 'c', CTypes['???'])
# # Param: len (apr_size_t *)
# CTypes.set_fn_param_type('apr_brigade_pflatten', 'len', CTypes['???'])

# ## apr_status_t apr_brigade_printf(apr_bucket_brigade * b, apr_brigade_flush flush, void * ctx, const char * fmt)
# # Param: flush (apr_brigade_flush)
# CTypes.set_fn_param_type('apr_brigade_printf', 'flush', CTypes['???'])
# # Param: ctx (void *)
# CTypes.set_fn_param_type('apr_brigade_printf', 'ctx', CTypes['???'])

# ## apr_status_t apr_brigade_putc(apr_bucket_brigade * b, apr_brigade_flush flush, void * ctx, const char c)
# # Param: flush (apr_brigade_flush)
# CTypes.set_fn_param_type('apr_brigade_putc', 'flush', CTypes['???'])
# # Param: ctx (void *)
# CTypes.set_fn_param_type('apr_brigade_putc', 'ctx', CTypes['???'])

# ## apr_status_t apr_brigade_puts(apr_bucket_brigade * bb, apr_brigade_flush flush, void * ctx, const char * str)
# # Param: flush (apr_brigade_flush)
# CTypes.set_fn_param_type('apr_brigade_puts', 'flush', CTypes['???'])
# # Param: ctx (void *)
# CTypes.set_fn_param_type('apr_brigade_puts', 'ctx', CTypes['???'])

# ## apr_status_t apr_brigade_putstrs(apr_bucket_brigade * b, apr_brigade_flush flush, void * ctx)
# # Param: flush (apr_brigade_flush)
# CTypes.set_fn_param_type('apr_brigade_putstrs', 'flush', CTypes['???'])
# # Param: ctx (void *)
# CTypes.set_fn_param_type('apr_brigade_putstrs', 'ctx', CTypes['???'])

# ## apr_status_t apr_brigade_split_line(apr_bucket_brigade * bbOut, apr_bucket_brigade * bbIn, apr_read_type_e block, apr_off_t maxbytes)
# # Param: maxbytes (apr_off_t)
# CTypes.set_fn_param_type('apr_brigade_split_line', 'maxbytes', CTypes['???'])

# ## apr_status_t apr_brigade_to_iovec(apr_bucket_brigade * b, struct iovec * vec, int * nvec)
# # Param: vec (struct iovec *)
# CTypes.set_fn_param_type('apr_brigade_to_iovec', 'vec', CTypes['???'])
# # Param: nvec (int *)
# CTypes.set_fn_param_type('apr_brigade_to_iovec', 'nvec', CTypes['???'])

# ## apr_status_t apr_brigade_vprintf(apr_bucket_brigade * b, apr_brigade_flush flush, void * ctx, const char * fmt, va_list va)
# # Param: flush (apr_brigade_flush)
# CTypes.set_fn_param_type('apr_brigade_vprintf', 'flush', CTypes['???'])
# # Param: ctx (void *)
# CTypes.set_fn_param_type('apr_brigade_vprintf', 'ctx', CTypes['???'])
# # Param: va (va_list)
# CTypes.set_fn_param_type('apr_brigade_vprintf', 'va', CTypes['???'])

# ## apr_status_t apr_brigade_vputstrs(apr_bucket_brigade * b, apr_brigade_flush flush, void * ctx, va_list va)
# # Param: flush (apr_brigade_flush)
# CTypes.set_fn_param_type('apr_brigade_vputstrs', 'flush', CTypes['???'])
# # Param: ctx (void *)
# CTypes.set_fn_param_type('apr_brigade_vputstrs', 'ctx', CTypes['???'])
# # Param: va (va_list)
# CTypes.set_fn_param_type('apr_brigade_vputstrs', 'va', CTypes['???'])

# ## apr_status_t apr_brigade_write(apr_bucket_brigade * b, apr_brigade_flush flush, void * ctx, const char * str, apr_size_t nbyte)
# # Param: flush (apr_brigade_flush)
# CTypes.set_fn_param_type('apr_brigade_write', 'flush', CTypes['???'])
# # Param: ctx (void *)
# CTypes.set_fn_param_type('apr_brigade_write', 'ctx', CTypes['???'])

# ## apr_status_t apr_brigade_writev(apr_bucket_brigade * b, apr_brigade_flush flush, void * ctx, const struct iovec * vec, apr_size_t nvec)
# # Param: flush (apr_brigade_flush)
# CTypes.set_fn_param_type('apr_brigade_writev', 'flush', CTypes['???'])
# # Param: ctx (void *)
# CTypes.set_fn_param_type('apr_brigade_writev', 'ctx', CTypes['???'])
# # Param: vec (const struct iovec *)
# CTypes.set_fn_param_type('apr_brigade_writev', 'vec', CTypes['???'])

# ## void * apr_bucket_alloc(apr_size_t size, apr_bucket_alloc_t * list)
# # Return value (void *)
# CTypes.set_fn_return_type('apr_bucket_alloc', CTypes['???'])

# ## apr_status_t apr_bucket_copy_notimpl(apr_bucket * e, apr_bucket ** c)
# # Param: c (apr_bucket **)
# CTypes.set_fn_param_type('apr_bucket_copy_notimpl', 'c', CTypes['???'])

# ## void apr_bucket_destroy_noop(void * data)
# # Param: data (void *)
# CTypes.set_fn_param_type('apr_bucket_destroy_noop', 'data', CTypes['???'])

# ## apr_bucket * apr_bucket_file_create(apr_file_t * fd, apr_off_t offset, apr_size_t len, apr_pool_t * p, apr_bucket_alloc_t * list)
# # Param: offset (apr_off_t)
# CTypes.set_fn_param_type('apr_bucket_file_create', 'offset', CTypes['???'])

# ## apr_bucket * apr_bucket_file_make(apr_bucket * b, apr_file_t * fd, apr_off_t offset, apr_size_t len, apr_pool_t * p)
# # Param: offset (apr_off_t)
# CTypes.set_fn_param_type('apr_bucket_file_make', 'offset', CTypes['???'])

# ## void apr_bucket_free(void * block)
# # Param: block (void *)
# CTypes.set_fn_param_type('apr_bucket_free', 'block', CTypes['???'])

# ## apr_bucket * apr_bucket_heap_create(const char * buf, apr_size_t nbyte, void (*)(void *) free_func, apr_bucket_alloc_t * list)
# # Param: free_func (void (*)(void *))
# CTypes.set_fn_param_type('apr_bucket_heap_create', 'free_func', CTypes['???'])

# ## apr_bucket * apr_bucket_heap_make(apr_bucket * b, const char * buf, apr_size_t nbyte, void (*)(void *) free_func)
# # Param: free_func (void (*)(void *))
# CTypes.set_fn_param_type('apr_bucket_heap_make', 'free_func', CTypes['???'])

# ## apr_bucket * apr_bucket_mmap_create(apr_mmap_t * mm, apr_off_t start, apr_size_t length, apr_bucket_alloc_t * list)
# # Param: start (apr_off_t)
# CTypes.set_fn_param_type('apr_bucket_mmap_create', 'start', CTypes['???'])

# ## apr_bucket * apr_bucket_mmap_make(apr_bucket * b, apr_mmap_t * mm, apr_off_t start, apr_size_t length)
# # Param: start (apr_off_t)
# CTypes.set_fn_param_type('apr_bucket_mmap_make', 'start', CTypes['???'])

# ## apr_status_t apr_bucket_shared_copy(apr_bucket * a, apr_bucket ** b)
# # Param: b (apr_bucket **)
# CTypes.set_fn_param_type('apr_bucket_shared_copy', 'b', CTypes['???'])

# ## int apr_bucket_shared_destroy(void * data)
# # Param: data (void *)
# CTypes.set_fn_param_type('apr_bucket_shared_destroy', 'data', CTypes['???'])

# ## apr_bucket * apr_bucket_shared_make(apr_bucket * b, void * data, apr_off_t start, apr_size_t length)
# # Param: data (void *)
# CTypes.set_fn_param_type('apr_bucket_shared_make', 'data', CTypes['???'])
# # Param: start (apr_off_t)
# CTypes.set_fn_param_type('apr_bucket_shared_make', 'start', CTypes['???'])

# ## apr_status_t apr_bucket_simple_copy(apr_bucket * a, apr_bucket ** b)
# # Param: b (apr_bucket **)
# CTypes.set_fn_param_type('apr_bucket_simple_copy', 'b', CTypes['???'])

# ## char * apr_collapse_spaces(char * dest, const char * src)
# # Return value (char *)
# CTypes.set_fn_return_type('apr_collapse_spaces', CTypes['???'])
# # Param: dest (char *)
# CTypes.set_fn_param_type('apr_collapse_spaces', 'dest', CTypes['???'])

# ## char * apr_cpystrn(char * dst, const char * src, apr_size_t dst_size)
# # Return value (char *)
# CTypes.set_fn_return_type('apr_cpystrn', CTypes['???'])
# # Param: dst (char *)
# CTypes.set_fn_param_type('apr_cpystrn', 'dst', CTypes['???'])

# ## apr_status_t apr_ctime(char * date_str, apr_time_t t)
# # Param: date_str (char *)
# CTypes.set_fn_param_type('apr_ctime', 'date_str', CTypes['???'])
# # Param: t (apr_time_t)
# CTypes.set_fn_param_type('apr_ctime', 't', CTypes['???'])

# ## apr_time_t apr_date_parse_http(const char * date)
# # Return value (apr_time_t)
# CTypes.set_fn_return_type('apr_date_parse_http', CTypes['???'])

# ## apr_time_t apr_date_parse_rfc(const char * date)
# # Return value (apr_time_t)
# CTypes.set_fn_return_type('apr_date_parse_rfc', CTypes['???'])

# ## apr_status_t apr_dbd_datum_get(const apr_dbd_driver_t * driver, apr_dbd_row_t * row, int col, apr_dbd_type_e type, void * data)
# # Param: data (void *)
# CTypes.set_fn_param_type('apr_dbd_datum_get', 'data', CTypes['???'])

# ## apr_status_t apr_dbd_get_driver(apr_pool_t * pool, const char * name, const apr_dbd_driver_t ** driver)
# # Param: driver (const apr_dbd_driver_t **)
# CTypes.set_fn_param_type('apr_dbd_get_driver', 'driver', CTypes['???'])

# ## int apr_dbd_get_row(const apr_dbd_driver_t * driver, apr_pool_t * pool, apr_dbd_results_t * res, apr_dbd_row_t ** row, int rownum)
# # Param: row (apr_dbd_row_t **)
# CTypes.set_fn_param_type('apr_dbd_get_row', 'row', CTypes['???'])

# ## void * apr_dbd_native_handle(const apr_dbd_driver_t * driver, apr_dbd_t * handle)
# # Return value (void *)
# CTypes.set_fn_return_type('apr_dbd_native_handle', CTypes['???'])

# ## apr_status_t apr_dbd_open(const apr_dbd_driver_t * driver, apr_pool_t * pool, const char * params, apr_dbd_t ** handle)
# # Param: handle (apr_dbd_t **)
# CTypes.set_fn_param_type('apr_dbd_open', 'handle', CTypes['???'])

# ## apr_status_t apr_dbd_open_ex(const apr_dbd_driver_t * driver, apr_pool_t * pool, const char * params, apr_dbd_t ** handle, const char ** error)
# # Param: handle (apr_dbd_t **)
# CTypes.set_fn_param_type('apr_dbd_open_ex', 'handle', CTypes['???'])
# # Param: error (const char **)
# CTypes.set_fn_param_type('apr_dbd_open_ex', 'error', CTypes['???'])

# ## int apr_dbd_pbquery(const apr_dbd_driver_t * driver, apr_pool_t * pool, apr_dbd_t * handle, int * nrows, apr_dbd_prepared_t * statement, const void ** args)
# # Param: nrows (int *)
# CTypes.set_fn_param_type('apr_dbd_pbquery', 'nrows', CTypes['???'])
# # Param: args (const void **)
# CTypes.set_fn_param_type('apr_dbd_pbquery', 'args', CTypes['???'])

# ## int apr_dbd_pbselect(const apr_dbd_driver_t * driver, apr_pool_t * pool, apr_dbd_t * handle, apr_dbd_results_t ** res, apr_dbd_prepared_t * statement, int random, const void ** args)
# # Param: res (apr_dbd_results_t **)
# CTypes.set_fn_param_type('apr_dbd_pbselect', 'res', CTypes['???'])
# # Param: args (const void **)
# CTypes.set_fn_param_type('apr_dbd_pbselect', 'args', CTypes['???'])

# ## int apr_dbd_pquery(const apr_dbd_driver_t * driver, apr_pool_t * pool, apr_dbd_t * handle, int * nrows, apr_dbd_prepared_t * statement, int nargs, const char ** args)
# # Param: nrows (int *)
# CTypes.set_fn_param_type('apr_dbd_pquery', 'nrows', CTypes['???'])
# # Param: args (const char **)
# CTypes.set_fn_param_type('apr_dbd_pquery', 'args', CTypes['???'])

# ## int apr_dbd_prepare(const apr_dbd_driver_t * driver, apr_pool_t * pool, apr_dbd_t * handle, const char * query, const char * label, apr_dbd_prepared_t ** statement)
# # Param: statement (apr_dbd_prepared_t **)
# CTypes.set_fn_param_type('apr_dbd_prepare', 'statement', CTypes['???'])

# ## int apr_dbd_pselect(const apr_dbd_driver_t * driver, apr_pool_t * pool, apr_dbd_t * handle, apr_dbd_results_t ** res, apr_dbd_prepared_t * statement, int random, int nargs, const char ** args)
# # Param: res (apr_dbd_results_t **)
# CTypes.set_fn_param_type('apr_dbd_pselect', 'res', CTypes['???'])
# # Param: args (const char **)
# CTypes.set_fn_param_type('apr_dbd_pselect', 'args', CTypes['???'])

# ## int apr_dbd_pvbquery(const apr_dbd_driver_t * driver, apr_pool_t * pool, apr_dbd_t * handle, int * nrows, apr_dbd_prepared_t * statement)
# # Param: nrows (int *)
# CTypes.set_fn_param_type('apr_dbd_pvbquery', 'nrows', CTypes['???'])

# ## int apr_dbd_pvbselect(const apr_dbd_driver_t * driver, apr_pool_t * pool, apr_dbd_t * handle, apr_dbd_results_t ** res, apr_dbd_prepared_t * statement, int random)
# # Param: res (apr_dbd_results_t **)
# CTypes.set_fn_param_type('apr_dbd_pvbselect', 'res', CTypes['???'])

# ## int apr_dbd_pvquery(const apr_dbd_driver_t * driver, apr_pool_t * pool, apr_dbd_t * handle, int * nrows, apr_dbd_prepared_t * statement)
# # Param: nrows (int *)
# CTypes.set_fn_param_type('apr_dbd_pvquery', 'nrows', CTypes['???'])

# ## int apr_dbd_pvselect(const apr_dbd_driver_t * driver, apr_pool_t * pool, apr_dbd_t * handle, apr_dbd_results_t ** res, apr_dbd_prepared_t * statement, int random)
# # Param: res (apr_dbd_results_t **)
# CTypes.set_fn_param_type('apr_dbd_pvselect', 'res', CTypes['???'])

# ## int apr_dbd_query(const apr_dbd_driver_t * driver, apr_dbd_t * handle, int * nrows, const char * statement)
# # Param: nrows (int *)
# CTypes.set_fn_param_type('apr_dbd_query', 'nrows', CTypes['???'])

# ## int apr_dbd_select(const apr_dbd_driver_t * driver, apr_pool_t * pool, apr_dbd_t * handle, apr_dbd_results_t ** res, const char * statement, int random)
# # Param: res (apr_dbd_results_t **)
# CTypes.set_fn_param_type('apr_dbd_select', 'res', CTypes['???'])

# ## int apr_dbd_transaction_start(const apr_dbd_driver_t * driver, apr_pool_t * pool, apr_dbd_t * handle, apr_dbd_transaction_t ** trans)
# # Param: trans (apr_dbd_transaction_t **)
# CTypes.set_fn_param_type('apr_dbd_transaction_start', 'trans', CTypes['???'])

# ## void apr_dbm_get_usednames(apr_pool_t * pool, const char * pathname, const char ** used1, const char ** used2)
# # Param: used1 (const char **)
# CTypes.set_fn_param_type('apr_dbm_get_usednames', 'used1', CTypes['???'])
# # Param: used2 (const char **)
# CTypes.set_fn_param_type('apr_dbm_get_usednames', 'used2', CTypes['???'])

# ## apr_status_t apr_dbm_get_usednames_ex(apr_pool_t * pool, const char * type, const char * pathname, const char ** used1, const char ** used2)
# # Param: used1 (const char **)
# CTypes.set_fn_param_type('apr_dbm_get_usednames_ex', 'used1', CTypes['???'])
# # Param: used2 (const char **)
# CTypes.set_fn_param_type('apr_dbm_get_usednames_ex', 'used2', CTypes['???'])

# ## char * apr_dbm_geterror(apr_dbm_t * dbm, int * errcode, char * errbuf, apr_size_t errbufsize)
# # Return value (char *)
# CTypes.set_fn_return_type('apr_dbm_geterror', CTypes['???'])
# # Param: errcode (int *)
# CTypes.set_fn_param_type('apr_dbm_geterror', 'errcode', CTypes['???'])
# # Param: errbuf (char *)
# CTypes.set_fn_param_type('apr_dbm_geterror', 'errbuf', CTypes['???'])

# ## apr_status_t apr_dbm_open(apr_dbm_t ** dbm, const char * name, apr_int32_t mode, apr_fileperms_t perm, apr_pool_t * cntxt)
# # Param: dbm (apr_dbm_t **)
# CTypes.set_fn_param_type('apr_dbm_open', 'dbm', CTypes['???'])

# ## apr_status_t apr_dbm_open_ex(apr_dbm_t ** dbm, const char * type, const char * name, apr_int32_t mode, apr_fileperms_t perm, apr_pool_t * cntxt)
# # Param: dbm (apr_dbm_t **)
# CTypes.set_fn_param_type('apr_dbm_open_ex', 'dbm', CTypes['???'])

# ## apr_status_t apr_dir_open(apr_dir_t ** new_dir, const char * dirname, apr_pool_t * pool)
# # Param: new_dir (apr_dir_t **)
# CTypes.set_fn_param_type('apr_dir_open', 'new_dir', CTypes['???'])

# ## const char * apr_dso_error(apr_dso_handle_t * dso, char * buf, apr_size_t bufsize)
# # Param: buf (char *)
# CTypes.set_fn_param_type('apr_dso_error', 'buf', CTypes['???'])

# ## apr_status_t apr_dso_load(apr_dso_handle_t ** res_handle, const char * path, apr_pool_t * ctx)
# # Param: res_handle (apr_dso_handle_t **)
# CTypes.set_fn_param_type('apr_dso_load', 'res_handle', CTypes['???'])

# ## apr_status_t apr_dso_sym(apr_dso_handle_sym_t * ressym, apr_dso_handle_t * handle, const char * symname)
# # Param: ressym (apr_dso_handle_sym_t *)
# CTypes.set_fn_param_type('apr_dso_sym', 'ressym', CTypes['???'])

# ## void apr_dynamic_fn_register(const char * szName, apr_opt_fn_t * pfn)
# # Param: pfn (apr_opt_fn_t *)
# CTypes.set_fn_param_type('apr_dynamic_fn_register', 'pfn', CTypes['???'])

# ## apr_opt_fn_t * apr_dynamic_fn_retrieve(const char * szName)
# # Return value (apr_opt_fn_t *)
# CTypes.set_fn_return_type('apr_dynamic_fn_retrieve', CTypes['???'])

# ## apr_status_t apr_env_get(char ** value, const char * envvar, apr_pool_t * pool)
# # Param: value (char **)
# CTypes.set_fn_param_type('apr_env_get', 'value', CTypes['???'])

# ## apr_status_t apr_file_buffer_set(apr_file_t * thefile, char * buffer, apr_size_t bufsize)
# # Param: buffer (char *)
# CTypes.set_fn_param_type('apr_file_buffer_set', 'buffer', CTypes['???'])

# ## apr_status_t apr_file_data_get(void ** data, const char * key, apr_file_t * file)
# # Param: data (void **)
# CTypes.set_fn_param_type('apr_file_data_get', 'data', CTypes['???'])

# ## apr_status_t apr_file_data_set(apr_file_t * file, void * data, const char * key, apr_status_t (*)(void *) cleanup)
# # Param: data (void *)
# CTypes.set_fn_param_type('apr_file_data_set', 'data', CTypes['???'])
# # Param: cleanup (apr_status_t (*)(void *))
# CTypes.set_fn_param_type('apr_file_data_set', 'cleanup', CTypes['???'])

# ## apr_status_t apr_file_dup(apr_file_t ** new_file, apr_file_t * old_file, apr_pool_t * p)
# # Param: new_file (apr_file_t **)
# CTypes.set_fn_param_type('apr_file_dup', 'new_file', CTypes['???'])

# ## apr_status_t apr_file_getc(char * ch, apr_file_t * thefile)
# # Param: ch (char *)
# CTypes.set_fn_param_type('apr_file_getc', 'ch', CTypes['???'])

# ## apr_status_t apr_file_gets(char * str, int len, apr_file_t * thefile)
# # Param: str (char *)
# CTypes.set_fn_param_type('apr_file_gets', 'str', CTypes['???'])

# ## apr_status_t apr_file_mktemp(apr_file_t ** fp, char * templ, apr_int32_t flags, apr_pool_t * p)
# # Param: fp (apr_file_t **)
# CTypes.set_fn_param_type('apr_file_mktemp', 'fp', CTypes['???'])
# # Param: templ (char *)
# CTypes.set_fn_param_type('apr_file_mktemp', 'templ', CTypes['???'])

# ## apr_status_t apr_file_mtime_set(const char * fname, apr_time_t mtime, apr_pool_t * pool)
# # Param: mtime (apr_time_t)
# CTypes.set_fn_param_type('apr_file_mtime_set', 'mtime', CTypes['???'])

# ## apr_status_t apr_file_name_get(const char ** new_path, apr_file_t * thefile)
# # Param: new_path (const char **)
# CTypes.set_fn_param_type('apr_file_name_get', 'new_path', CTypes['???'])

# ## apr_status_t apr_file_open(apr_file_t ** newf, const char * fname, apr_int32_t flag, apr_fileperms_t perm, apr_pool_t * pool)
# # Param: newf (apr_file_t **)
# CTypes.set_fn_param_type('apr_file_open', 'newf', CTypes['???'])

# ## apr_status_t apr_file_open_flags_stderr(apr_file_t ** thefile, apr_int32_t flags, apr_pool_t * pool)
# # Param: thefile (apr_file_t **)
# CTypes.set_fn_param_type('apr_file_open_flags_stderr', 'thefile', CTypes['???'])

# ## apr_status_t apr_file_open_flags_stdin(apr_file_t ** thefile, apr_int32_t flags, apr_pool_t * pool)
# # Param: thefile (apr_file_t **)
# CTypes.set_fn_param_type('apr_file_open_flags_stdin', 'thefile', CTypes['???'])

# ## apr_status_t apr_file_open_flags_stdout(apr_file_t ** thefile, apr_int32_t flags, apr_pool_t * pool)
# # Param: thefile (apr_file_t **)
# CTypes.set_fn_param_type('apr_file_open_flags_stdout', 'thefile', CTypes['???'])

# ## apr_status_t apr_file_open_stderr(apr_file_t ** thefile, apr_pool_t * pool)
# # Param: thefile (apr_file_t **)
# CTypes.set_fn_param_type('apr_file_open_stderr', 'thefile', CTypes['???'])

# ## apr_status_t apr_file_open_stdin(apr_file_t ** thefile, apr_pool_t * pool)
# # Param: thefile (apr_file_t **)
# CTypes.set_fn_param_type('apr_file_open_stdin', 'thefile', CTypes['???'])

# ## apr_status_t apr_file_open_stdout(apr_file_t ** thefile, apr_pool_t * pool)
# # Param: thefile (apr_file_t **)
# CTypes.set_fn_param_type('apr_file_open_stdout', 'thefile', CTypes['???'])

# ## apr_status_t apr_file_pipe_create(apr_file_t ** in, apr_file_t ** out, apr_pool_t * pool)
# # Param: in (apr_file_t **)
# CTypes.set_fn_param_type('apr_file_pipe_create', 'in', CTypes['???'])
# # Param: out (apr_file_t **)
# CTypes.set_fn_param_type('apr_file_pipe_create', 'out', CTypes['???'])

# ## apr_status_t apr_file_pipe_create_ex(apr_file_t ** in, apr_file_t ** out, apr_int32_t blocking, apr_pool_t * pool)
# # Param: in (apr_file_t **)
# CTypes.set_fn_param_type('apr_file_pipe_create_ex', 'in', CTypes['???'])
# # Param: out (apr_file_t **)
# CTypes.set_fn_param_type('apr_file_pipe_create_ex', 'out', CTypes['???'])

# ## apr_status_t apr_file_pipe_timeout_get(apr_file_t * thepipe, apr_interval_time_t * timeout)
# # Param: timeout (apr_interval_time_t *)
# CTypes.set_fn_param_type('apr_file_pipe_timeout_get', 'timeout', CTypes['???'])

# ## apr_status_t apr_file_pipe_timeout_set(apr_file_t * thepipe, apr_interval_time_t timeout)
# # Param: timeout (apr_interval_time_t)
# CTypes.set_fn_param_type('apr_file_pipe_timeout_set', 'timeout', CTypes['???'])

# ## apr_status_t apr_file_read(apr_file_t * thefile, void * buf, apr_size_t * nbytes)
# # Param: buf (void *)
# CTypes.set_fn_param_type('apr_file_read', 'buf', CTypes['???'])
# # Param: nbytes (apr_size_t *)
# CTypes.set_fn_param_type('apr_file_read', 'nbytes', CTypes['???'])

# ## apr_status_t apr_file_read_full(apr_file_t * thefile, void * buf, apr_size_t nbytes, apr_size_t * bytes_read)
# # Param: buf (void *)
# CTypes.set_fn_param_type('apr_file_read_full', 'buf', CTypes['???'])
# # Param: bytes_read (apr_size_t *)
# CTypes.set_fn_param_type('apr_file_read_full', 'bytes_read', CTypes['???'])

# ## apr_status_t apr_file_seek(apr_file_t * thefile, apr_seek_where_t where, apr_off_t * offset)
# # Param: offset (apr_off_t *)
# CTypes.set_fn_param_type('apr_file_seek', 'offset', CTypes['???'])

# ## apr_status_t apr_file_setaside(apr_file_t ** new_file, apr_file_t * old_file, apr_pool_t * p)
# # Param: new_file (apr_file_t **)
# CTypes.set_fn_param_type('apr_file_setaside', 'new_file', CTypes['???'])

# ## apr_status_t apr_file_trunc(apr_file_t * fp, apr_off_t offset)
# # Param: offset (apr_off_t)
# CTypes.set_fn_param_type('apr_file_trunc', 'offset', CTypes['???'])

# ## apr_status_t apr_file_write(apr_file_t * thefile, const void * buf, apr_size_t * nbytes)
# # Param: buf (const void *)
# CTypes.set_fn_param_type('apr_file_write', 'buf', CTypes['???'])
# # Param: nbytes (apr_size_t *)
# CTypes.set_fn_param_type('apr_file_write', 'nbytes', CTypes['???'])

# ## apr_status_t apr_file_write_full(apr_file_t * thefile, const void * buf, apr_size_t nbytes, apr_size_t * bytes_written)
# # Param: buf (const void *)
# CTypes.set_fn_param_type('apr_file_write_full', 'buf', CTypes['???'])
# # Param: bytes_written (apr_size_t *)
# CTypes.set_fn_param_type('apr_file_write_full', 'bytes_written', CTypes['???'])

# ## apr_status_t apr_file_writev(apr_file_t * thefile, const struct iovec * vec, apr_size_t nvec, apr_size_t * nbytes)
# # Param: vec (const struct iovec *)
# CTypes.set_fn_param_type('apr_file_writev', 'vec', CTypes['???'])
# # Param: nbytes (apr_size_t *)
# CTypes.set_fn_param_type('apr_file_writev', 'nbytes', CTypes['???'])

# ## apr_status_t apr_file_writev_full(apr_file_t * thefile, const struct iovec * vec, apr_size_t nvec, apr_size_t * nbytes)
# # Param: vec (const struct iovec *)
# CTypes.set_fn_param_type('apr_file_writev_full', 'vec', CTypes['???'])
# # Param: nbytes (apr_size_t *)
# CTypes.set_fn_param_type('apr_file_writev_full', 'nbytes', CTypes['???'])

# ## apr_status_t apr_filepath_encoding(int * style, apr_pool_t * p)
# # Param: style (int *)
# CTypes.set_fn_param_type('apr_filepath_encoding', 'style', CTypes['???'])

# ## apr_status_t apr_filepath_get(char ** path, apr_int32_t flags, apr_pool_t * p)
# # Param: path (char **)
# CTypes.set_fn_param_type('apr_filepath_get', 'path', CTypes['???'])

# ## apr_status_t apr_filepath_list_merge(char ** liststr, apr_array_header_t * pathelts, apr_pool_t * p)
# # Param: liststr (char **)
# CTypes.set_fn_param_type('apr_filepath_list_merge', 'liststr', CTypes['???'])

# ## apr_status_t apr_filepath_list_split(apr_array_header_t ** pathelts, const char * liststr, apr_pool_t * p)
# # Param: pathelts (apr_array_header_t **)
# CTypes.set_fn_param_type('apr_filepath_list_split', 'pathelts', CTypes['???'])

# ## apr_status_t apr_filepath_merge(char ** newpath, const char * rootpath, const char * addpath, apr_int32_t flags, apr_pool_t * p)
# # Param: newpath (char **)
# CTypes.set_fn_param_type('apr_filepath_merge', 'newpath', CTypes['???'])

# ## apr_status_t apr_filepath_root(const char ** rootpath, const char ** filepath, apr_int32_t flags, apr_pool_t * p)
# # Param: rootpath (const char **)
# CTypes.set_fn_param_type('apr_filepath_root', 'rootpath', CTypes['???'])
# # Param: filepath (const char **)
# CTypes.set_fn_param_type('apr_filepath_root', 'filepath', CTypes['???'])

# ## apr_status_t apr_generate_random_bytes(unsigned char * buf, apr_size_t length)
# # Param: buf (unsigned char *)
# CTypes.set_fn_param_type('apr_generate_random_bytes', 'buf', CTypes['???'])

# ## apr_status_t apr_gethostname(char * buf, int len, apr_pool_t * cont)
# # Param: buf (char *)
# CTypes.set_fn_param_type('apr_gethostname', 'buf', CTypes['???'])

# ## apr_status_t apr_getnameinfo(char ** hostname, apr_sockaddr_t * sa, apr_int32_t flags)
# # Param: hostname (char **)
# CTypes.set_fn_param_type('apr_getnameinfo', 'hostname', CTypes['???'])

# ## apr_status_t apr_getopt(apr_getopt_t * os, const char * opts, char * option_ch, const char ** option_arg)
# # Param: option_ch (char *)
# CTypes.set_fn_param_type('apr_getopt', 'option_ch', CTypes['???'])
# # Param: option_arg (const char **)
# CTypes.set_fn_param_type('apr_getopt', 'option_arg', CTypes['???'])

# ## apr_status_t apr_getopt_init(apr_getopt_t ** os, apr_pool_t * cont, int argc, const char *const * argv)
# # Param: os (apr_getopt_t **)
# CTypes.set_fn_param_type('apr_getopt_init', 'os', CTypes['???'])
# # Param: argv (const char *const *)
# CTypes.set_fn_param_type('apr_getopt_init', 'argv', CTypes['???'])

# ## apr_status_t apr_getopt_long(apr_getopt_t * os, const apr_getopt_option_t * opts, int * option_ch, const char ** option_arg)
# # Param: option_ch (int *)
# CTypes.set_fn_param_type('apr_getopt_long', 'option_ch', CTypes['???'])
# # Param: option_arg (const char **)
# CTypes.set_fn_param_type('apr_getopt_long', 'option_arg', CTypes['???'])

# ## apr_status_t apr_gid_get(apr_gid_t * groupid, const char * groupname, apr_pool_t * p)
# # Param: groupid (apr_gid_t *)
# CTypes.set_fn_param_type('apr_gid_get', 'groupid', CTypes['???'])

# ## apr_status_t apr_gid_name_get(char ** groupname, apr_gid_t groupid, apr_pool_t * p)
# # Param: groupname (char **)
# CTypes.set_fn_param_type('apr_gid_name_get', 'groupname', CTypes['???'])
# # Param: groupid (apr_gid_t)
# CTypes.set_fn_param_type('apr_gid_name_get', 'groupid', CTypes['???'])

# ## apr_status_t apr_global_mutex_child_init(apr_global_mutex_t ** mutex, const char * fname, apr_pool_t * pool)
# # Param: mutex (apr_global_mutex_t **)
# CTypes.set_fn_param_type('apr_global_mutex_child_init', 'mutex', CTypes['???'])

# ## apr_status_t apr_global_mutex_create(apr_global_mutex_t ** mutex, const char * fname, apr_lockmech_e mech, apr_pool_t * pool)
# # Param: mutex (apr_global_mutex_t **)
# CTypes.set_fn_param_type('apr_global_mutex_create', 'mutex', CTypes['???'])

# ## int apr_hash_do(apr_hash_do_callback_fn_t * comp, void * rec, const apr_hash_t * ht)
# # Param: comp (apr_hash_do_callback_fn_t *)
# CTypes.set_fn_param_type('apr_hash_do', 'comp', CTypes['???'])
# # Param: rec (void *)
# CTypes.set_fn_param_type('apr_hash_do', 'rec', CTypes['???'])

# ## void * apr_hash_get(apr_hash_t * ht, const void * key, apr_ssize_t klen)
# # Return value (void *)
# CTypes.set_fn_return_type('apr_hash_get', CTypes['???'])
# # Param: key (const void *)
# CTypes.set_fn_param_type('apr_hash_get', 'key', CTypes['???'])
# # Param: klen (apr_ssize_t)
# CTypes.set_fn_param_type('apr_hash_get', 'klen', CTypes['???'])

# ## apr_hash_t * apr_hash_make_custom(apr_pool_t * pool, apr_hashfunc_t hash_func)
# # Param: hash_func (apr_hashfunc_t)
# CTypes.set_fn_param_type('apr_hash_make_custom', 'hash_func', CTypes['???'])

# ## apr_hash_t * apr_hash_merge(apr_pool_t * p, const apr_hash_t * h1, const apr_hash_t * h2, void *(*)(apr_pool_t *, const void *, apr_ssize_t, const void *, const void *, const void *) merger, const void * data)
# # Param: merger (void *(*)(apr_pool_t *, const void *, apr_ssize_t, const void *, const void *, const void *))
# CTypes.set_fn_param_type('apr_hash_merge', 'merger', CTypes['???'])
# # Param: data (const void *)
# CTypes.set_fn_param_type('apr_hash_merge', 'data', CTypes['???'])

# ## void apr_hash_set(apr_hash_t * ht, const void * key, apr_ssize_t klen, const void * val)
# # Param: key (const void *)
# CTypes.set_fn_param_type('apr_hash_set', 'key', CTypes['???'])
# # Param: klen (apr_ssize_t)
# CTypes.set_fn_param_type('apr_hash_set', 'klen', CTypes['???'])
# # Param: val (const void *)
# CTypes.set_fn_param_type('apr_hash_set', 'val', CTypes['???'])

# ## void apr_hash_this(apr_hash_index_t * hi, const void ** key, apr_ssize_t * klen, void ** val)
# # Param: key (const void **)
# CTypes.set_fn_param_type('apr_hash_this', 'key', CTypes['???'])
# # Param: klen (apr_ssize_t *)
# CTypes.set_fn_param_type('apr_hash_this', 'klen', CTypes['???'])
# # Param: val (void **)
# CTypes.set_fn_param_type('apr_hash_this', 'val', CTypes['???'])

# ## unsigned int apr_hashfunc_default(const char * key, apr_ssize_t * klen)
# # Param: klen (apr_ssize_t *)
# CTypes.set_fn_param_type('apr_hashfunc_default', 'klen', CTypes['???'])

# ## void apr_hook_debug_show(const char * szName, const char *const * aszPre, const char *const * aszSucc)
# # Param: aszPre (const char *const *)
# CTypes.set_fn_param_type('apr_hook_debug_show', 'aszPre', CTypes['???'])
# # Param: aszSucc (const char *const *)
# CTypes.set_fn_param_type('apr_hook_debug_show', 'aszSucc', CTypes['???'])

# ## void apr_hook_sort_register(const char * szHookName, apr_array_header_t ** aHooks)
# # Param: aHooks (apr_array_header_t **)
# CTypes.set_fn_param_type('apr_hook_sort_register', 'aHooks', CTypes['???'])

# ## apr_status_t apr_ipsubnet_create(apr_ipsubnet_t ** ipsub, const char * ipstr, const char * mask_or_numbits, apr_pool_t * p)
# # Param: ipsub (apr_ipsubnet_t **)
# CTypes.set_fn_param_type('apr_ipsubnet_create', 'ipsub', CTypes['???'])

# ## char * apr_itoa(apr_pool_t * p, int n)
# # Return value (char *)
# CTypes.set_fn_return_type('apr_itoa', CTypes['???'])

# ## int apr_ldap_get_option(apr_pool_t * pool, LDAP * ldap, int option, void * outvalue, apr_ldap_err_t ** result_err)
# # Param: ldap (LDAP *)
# CTypes.set_fn_param_type('apr_ldap_get_option', 'ldap', CTypes['???'])
# # Param: outvalue (void *)
# CTypes.set_fn_param_type('apr_ldap_get_option', 'outvalue', CTypes['???'])
# # Param: result_err (apr_ldap_err_t **)
# CTypes.set_fn_param_type('apr_ldap_get_option', 'result_err', CTypes['???'])

# ## int apr_ldap_info(apr_pool_t * pool, apr_ldap_err_t ** result_err)
# # Param: result_err (apr_ldap_err_t **)
# CTypes.set_fn_param_type('apr_ldap_info', 'result_err', CTypes['???'])

# ## int apr_ldap_init(apr_pool_t * pool, LDAP ** ldap, const char * hostname, int portno, int secure, apr_ldap_err_t ** result_err)
# # Param: ldap (LDAP **)
# CTypes.set_fn_param_type('apr_ldap_init', 'ldap', CTypes['???'])
# # Param: result_err (apr_ldap_err_t **)
# CTypes.set_fn_param_type('apr_ldap_init', 'result_err', CTypes['???'])

# ## int apr_ldap_set_option(apr_pool_t * pool, LDAP * ldap, int option, const void * invalue, apr_ldap_err_t ** result_err)
# # Param: ldap (LDAP *)
# CTypes.set_fn_param_type('apr_ldap_set_option', 'ldap', CTypes['???'])
# # Param: invalue (const void *)
# CTypes.set_fn_param_type('apr_ldap_set_option', 'invalue', CTypes['???'])
# # Param: result_err (apr_ldap_err_t **)
# CTypes.set_fn_param_type('apr_ldap_set_option', 'result_err', CTypes['???'])

# ## int apr_ldap_ssl_init(apr_pool_t * pool, const char * cert_auth_file, int cert_file_type, apr_ldap_err_t ** result_err)
# # Param: result_err (apr_ldap_err_t **)
# CTypes.set_fn_param_type('apr_ldap_ssl_init', 'result_err', CTypes['???'])

# ## char * apr_ltoa(apr_pool_t * p, long n)
# # Return value (char *)
# CTypes.set_fn_return_type('apr_ltoa', CTypes['???'])

# ## apr_status_t apr_match_glob(const char * pattern, apr_array_header_t ** result, apr_pool_t * p)
# # Param: result (apr_array_header_t **)
# CTypes.set_fn_param_type('apr_match_glob', 'result', CTypes['???'])

# ## apr_status_t apr_md4(unsigned char [16] digest, const unsigned char * input, apr_size_t inputLen)
# # Param: digest (unsigned char [16])
# CTypes.set_fn_param_type('apr_md4', 'digest', CTypes['???'])
# # Param: input (const unsigned char *)
# CTypes.set_fn_param_type('apr_md4', 'input', CTypes['???'])

# ## apr_status_t apr_md4_final(unsigned char [16] digest, apr_md4_ctx_t * context)
# # Param: digest (unsigned char [16])
# CTypes.set_fn_param_type('apr_md4_final', 'digest', CTypes['???'])

# ## apr_status_t apr_md4_update(apr_md4_ctx_t * context, const unsigned char * input, apr_size_t inputLen)
# # Param: input (const unsigned char *)
# CTypes.set_fn_param_type('apr_md4_update', 'input', CTypes['???'])

# ## apr_status_t apr_md5(unsigned char [16] digest, const void * input, apr_size_t inputLen)
# # Param: digest (unsigned char [16])
# CTypes.set_fn_param_type('apr_md5', 'digest', CTypes['???'])
# # Param: input (const void *)
# CTypes.set_fn_param_type('apr_md5', 'input', CTypes['???'])

# ## apr_status_t apr_md5_encode(const char * password, const char * salt, char * result, apr_size_t nbytes)
# # Param: result (char *)
# CTypes.set_fn_param_type('apr_md5_encode', 'result', CTypes['???'])

# ## apr_status_t apr_md5_final(unsigned char [16] digest, apr_md5_ctx_t * context)
# # Param: digest (unsigned char [16])
# CTypes.set_fn_param_type('apr_md5_final', 'digest', CTypes['???'])

# ## apr_status_t apr_md5_update(apr_md5_ctx_t * context, const void * input, apr_size_t inputLen)
# # Param: input (const void *)
# CTypes.set_fn_param_type('apr_md5_update', 'input', CTypes['???'])

# ## apr_status_t apr_memcache_add(apr_memcache_t * mc, const char * key, char * baton, const apr_size_t data_size, apr_uint32_t timeout, apr_uint16_t flags)
# # Param: baton (char *)
# CTypes.set_fn_param_type('apr_memcache_add', 'baton', CTypes['???'])
# # Param: data_size (const apr_size_t)
# CTypes.set_fn_param_type('apr_memcache_add', 'data_size', CTypes['???'])

# ## void apr_memcache_add_multget_key(apr_pool_t * data_pool, const char * key, apr_hash_t ** values)
# # Param: values (apr_hash_t **)
# CTypes.set_fn_param_type('apr_memcache_add_multget_key', 'values', CTypes['???'])

# ## apr_status_t apr_memcache_create(apr_pool_t * p, apr_uint16_t max_servers, apr_uint32_t flags, apr_memcache_t ** mc)
# # Param: mc (apr_memcache_t **)
# CTypes.set_fn_param_type('apr_memcache_create', 'mc', CTypes['???'])

# ## apr_status_t apr_memcache_decr(apr_memcache_t * mc, const char * key, apr_int32_t n, apr_uint32_t * new_value)
# # Param: new_value (apr_uint32_t *)
# CTypes.set_fn_param_type('apr_memcache_decr', 'new_value', CTypes['???'])

# ## apr_memcache_server_t * apr_memcache_find_server_hash(apr_memcache_t * mc, const apr_uint32_t hash)
# # Param: hash (const apr_uint32_t)
# CTypes.set_fn_param_type('apr_memcache_find_server_hash', 'hash', CTypes['???'])

# ## apr_memcache_server_t * apr_memcache_find_server_hash_default(void * baton, apr_memcache_t * mc, const apr_uint32_t hash)
# # Param: baton (void *)
# CTypes.set_fn_param_type('apr_memcache_find_server_hash_default', 'baton', CTypes['???'])
# # Param: hash (const apr_uint32_t)
# CTypes.set_fn_param_type('apr_memcache_find_server_hash_default', 'hash', CTypes['???'])

# ## apr_status_t apr_memcache_getp(apr_memcache_t * mc, apr_pool_t * p, const char * key, char ** baton, apr_size_t * len, apr_uint16_t * flags)
# # Param: baton (char **)
# CTypes.set_fn_param_type('apr_memcache_getp', 'baton', CTypes['???'])
# # Param: len (apr_size_t *)
# CTypes.set_fn_param_type('apr_memcache_getp', 'len', CTypes['???'])
# # Param: flags (apr_uint16_t *)
# CTypes.set_fn_param_type('apr_memcache_getp', 'flags', CTypes['???'])

# ## apr_uint32_t apr_memcache_hash(apr_memcache_t * mc, const char * data, const apr_size_t data_len)
# # Param: data_len (const apr_size_t)
# CTypes.set_fn_param_type('apr_memcache_hash', 'data_len', CTypes['???'])

# ## apr_uint32_t apr_memcache_hash_crc32(void * baton, const char * data, const apr_size_t data_len)
# # Param: baton (void *)
# CTypes.set_fn_param_type('apr_memcache_hash_crc32', 'baton', CTypes['???'])
# # Param: data_len (const apr_size_t)
# CTypes.set_fn_param_type('apr_memcache_hash_crc32', 'data_len', CTypes['???'])

# ## apr_uint32_t apr_memcache_hash_default(void * baton, const char * data, const apr_size_t data_len)
# # Param: baton (void *)
# CTypes.set_fn_param_type('apr_memcache_hash_default', 'baton', CTypes['???'])
# # Param: data_len (const apr_size_t)
# CTypes.set_fn_param_type('apr_memcache_hash_default', 'data_len', CTypes['???'])

# ## apr_status_t apr_memcache_incr(apr_memcache_t * mc, const char * key, apr_int32_t n, apr_uint32_t * nv)
# # Param: nv (apr_uint32_t *)
# CTypes.set_fn_param_type('apr_memcache_incr', 'nv', CTypes['???'])

# ## apr_status_t apr_memcache_replace(apr_memcache_t * mc, const char * key, char * baton, const apr_size_t data_size, apr_uint32_t timeout, apr_uint16_t flags)
# # Param: baton (char *)
# CTypes.set_fn_param_type('apr_memcache_replace', 'baton', CTypes['???'])
# # Param: data_size (const apr_size_t)
# CTypes.set_fn_param_type('apr_memcache_replace', 'data_size', CTypes['???'])

# ## apr_status_t apr_memcache_server_create(apr_pool_t * p, const char * host, apr_port_t port, apr_uint32_t min, apr_uint32_t smax, apr_uint32_t max, apr_uint32_t ttl, apr_memcache_server_t ** ns)
# # Param: ns (apr_memcache_server_t **)
# CTypes.set_fn_param_type('apr_memcache_server_create', 'ns', CTypes['???'])

# ## apr_status_t apr_memcache_set(apr_memcache_t * mc, const char * key, char * baton, const apr_size_t data_size, apr_uint32_t timeout, apr_uint16_t flags)
# # Param: baton (char *)
# CTypes.set_fn_param_type('apr_memcache_set', 'baton', CTypes['???'])
# # Param: data_size (const apr_size_t)
# CTypes.set_fn_param_type('apr_memcache_set', 'data_size', CTypes['???'])

# ## apr_status_t apr_memcache_stats(apr_memcache_server_t * ms, apr_pool_t * p, apr_memcache_stats_t ** stats)
# # Param: stats (apr_memcache_stats_t **)
# CTypes.set_fn_param_type('apr_memcache_stats', 'stats', CTypes['???'])

# ## apr_status_t apr_memcache_version(apr_memcache_server_t * ms, apr_pool_t * p, char ** baton)
# # Param: baton (char **)
# CTypes.set_fn_param_type('apr_memcache_version', 'baton', CTypes['???'])

# ## apr_status_t apr_mmap_create(apr_mmap_t ** newmmap, apr_file_t * file, apr_off_t offset, apr_size_t size, apr_int32_t flag, apr_pool_t * cntxt)
# # Param: newmmap (apr_mmap_t **)
# CTypes.set_fn_param_type('apr_mmap_create', 'newmmap', CTypes['???'])
# # Param: offset (apr_off_t)
# CTypes.set_fn_param_type('apr_mmap_create', 'offset', CTypes['???'])

# ## apr_status_t apr_mmap_dup(apr_mmap_t ** new_mmap, apr_mmap_t * old_mmap, apr_pool_t * p)
# # Param: new_mmap (apr_mmap_t **)
# CTypes.set_fn_param_type('apr_mmap_dup', 'new_mmap', CTypes['???'])

# ## apr_status_t apr_mmap_offset(void ** addr, apr_mmap_t * mm, apr_off_t offset)
# # Param: addr (void **)
# CTypes.set_fn_param_type('apr_mmap_offset', 'addr', CTypes['???'])
# # Param: offset (apr_off_t)
# CTypes.set_fn_param_type('apr_mmap_offset', 'offset', CTypes['???'])

# ## char * apr_off_t_toa(apr_pool_t * p, apr_off_t n)
# # Return value (char *)
# CTypes.set_fn_return_type('apr_off_t_toa', CTypes['???'])
# # Param: n (apr_off_t)
# CTypes.set_fn_param_type('apr_off_t_toa', 'n', CTypes['???'])

# ## apr_status_t apr_os_dir_get(apr_os_dir_t ** thedir, apr_dir_t * dir)
# # Param: thedir (apr_os_dir_t **)
# CTypes.set_fn_param_type('apr_os_dir_get', 'thedir', CTypes['???'])

# ## apr_status_t apr_os_dir_put(apr_dir_t ** dir, apr_os_dir_t * thedir, apr_pool_t * cont)
# # Param: dir (apr_dir_t **)
# CTypes.set_fn_param_type('apr_os_dir_put', 'dir', CTypes['???'])
# # Param: thedir (apr_os_dir_t *)
# CTypes.set_fn_param_type('apr_os_dir_put', 'thedir', CTypes['???'])

# ## apr_status_t apr_os_dso_handle_get(apr_os_dso_handle_t * dso, apr_dso_handle_t * aprdso)
# # Param: dso (apr_os_dso_handle_t *)
# CTypes.set_fn_param_type('apr_os_dso_handle_get', 'dso', CTypes['???'])

# ## apr_status_t apr_os_dso_handle_put(apr_dso_handle_t ** dso, apr_os_dso_handle_t thedso, apr_pool_t * pool)
# # Param: dso (apr_dso_handle_t **)
# CTypes.set_fn_param_type('apr_os_dso_handle_put', 'dso', CTypes['???'])
# # Param: thedso (apr_os_dso_handle_t)
# CTypes.set_fn_param_type('apr_os_dso_handle_put', 'thedso', CTypes['???'])

# ## apr_status_t apr_os_exp_time_get(apr_os_exp_time_t ** ostime, apr_time_exp_t * aprtime)
# # Param: ostime (apr_os_exp_time_t **)
# CTypes.set_fn_param_type('apr_os_exp_time_get', 'ostime', CTypes['???'])

# ## apr_status_t apr_os_exp_time_put(apr_time_exp_t * aprtime, apr_os_exp_time_t ** ostime, apr_pool_t * cont)
# # Param: ostime (apr_os_exp_time_t **)
# CTypes.set_fn_param_type('apr_os_exp_time_put', 'ostime', CTypes['???'])

# ## apr_status_t apr_os_file_get(apr_os_file_t * thefile, apr_file_t * file)
# # Param: thefile (apr_os_file_t *)
# CTypes.set_fn_param_type('apr_os_file_get', 'thefile', CTypes['???'])

# ## apr_status_t apr_os_file_put(apr_file_t ** file, apr_os_file_t * thefile, apr_int32_t flags, apr_pool_t * cont)
# # Param: file (apr_file_t **)
# CTypes.set_fn_param_type('apr_os_file_put', 'file', CTypes['???'])
# # Param: thefile (apr_os_file_t *)
# CTypes.set_fn_param_type('apr_os_file_put', 'thefile', CTypes['???'])

# ## apr_status_t apr_os_imp_time_get(apr_os_imp_time_t ** ostime, apr_time_t * aprtime)
# # Param: ostime (apr_os_imp_time_t **)
# CTypes.set_fn_param_type('apr_os_imp_time_get', 'ostime', CTypes['???'])
# # Param: aprtime (apr_time_t *)
# CTypes.set_fn_param_type('apr_os_imp_time_get', 'aprtime', CTypes['???'])

# ## apr_status_t apr_os_imp_time_put(apr_time_t * aprtime, apr_os_imp_time_t ** ostime, apr_pool_t * cont)
# # Param: aprtime (apr_time_t *)
# CTypes.set_fn_param_type('apr_os_imp_time_put', 'aprtime', CTypes['???'])
# # Param: ostime (apr_os_imp_time_t **)
# CTypes.set_fn_param_type('apr_os_imp_time_put', 'ostime', CTypes['???'])

# ## apr_status_t apr_os_pipe_put(apr_file_t ** file, apr_os_file_t * thefile, apr_pool_t * cont)
# # Param: file (apr_file_t **)
# CTypes.set_fn_param_type('apr_os_pipe_put', 'file', CTypes['???'])
# # Param: thefile (apr_os_file_t *)
# CTypes.set_fn_param_type('apr_os_pipe_put', 'thefile', CTypes['???'])

# ## apr_status_t apr_os_pipe_put_ex(apr_file_t ** file, apr_os_file_t * thefile, int register_cleanup, apr_pool_t * cont)
# # Param: file (apr_file_t **)
# CTypes.set_fn_param_type('apr_os_pipe_put_ex', 'file', CTypes['???'])
# # Param: thefile (apr_os_file_t *)
# CTypes.set_fn_param_type('apr_os_pipe_put_ex', 'thefile', CTypes['???'])

# ## apr_status_t apr_os_proc_mutex_put(apr_proc_mutex_t ** pmutex, apr_os_proc_mutex_t * ospmutex, apr_pool_t * cont)
# # Param: pmutex (apr_proc_mutex_t **)
# CTypes.set_fn_param_type('apr_os_proc_mutex_put', 'pmutex', CTypes['???'])

# ## apr_status_t apr_os_shm_get(apr_os_shm_t * osshm, apr_shm_t * shm)
# # Param: osshm (apr_os_shm_t *)
# CTypes.set_fn_param_type('apr_os_shm_get', 'osshm', CTypes['???'])

# ## apr_status_t apr_os_shm_put(apr_shm_t ** shm, apr_os_shm_t * osshm, apr_pool_t * cont)
# # Param: shm (apr_shm_t **)
# CTypes.set_fn_param_type('apr_os_shm_put', 'shm', CTypes['???'])
# # Param: osshm (apr_os_shm_t *)
# CTypes.set_fn_param_type('apr_os_shm_put', 'osshm', CTypes['???'])

# ## apr_status_t apr_os_sock_get(apr_os_sock_t * thesock, apr_socket_t * sock)
# # Param: thesock (apr_os_sock_t *)
# CTypes.set_fn_param_type('apr_os_sock_get', 'thesock', CTypes['???'])

# ## apr_status_t apr_os_sock_make(apr_socket_t ** apr_sock, apr_os_sock_info_t * os_sock_info, apr_pool_t * cont)
# # Param: apr_sock (apr_socket_t **)
# CTypes.set_fn_param_type('apr_os_sock_make', 'apr_sock', CTypes['???'])

# ## apr_status_t apr_os_sock_put(apr_socket_t ** sock, apr_os_sock_t * thesock, apr_pool_t * cont)
# # Param: sock (apr_socket_t **)
# CTypes.set_fn_param_type('apr_os_sock_put', 'sock', CTypes['???'])
# # Param: thesock (apr_os_sock_t *)
# CTypes.set_fn_param_type('apr_os_sock_put', 'thesock', CTypes['???'])

# ## apr_os_thread_t apr_os_thread_current()
# # Return value (apr_os_thread_t)
# CTypes.set_fn_return_type('apr_os_thread_current', CTypes['???'])

# ## int apr_os_thread_equal(apr_os_thread_t tid1, apr_os_thread_t tid2)
# # Param: tid1 (apr_os_thread_t)
# CTypes.set_fn_param_type('apr_os_thread_equal', 'tid1', CTypes['???'])
# # Param: tid2 (apr_os_thread_t)
# CTypes.set_fn_param_type('apr_os_thread_equal', 'tid2', CTypes['???'])

# ## apr_status_t apr_os_thread_get(apr_os_thread_t ** thethd, apr_thread_t * thd)
# # Param: thethd (apr_os_thread_t **)
# CTypes.set_fn_param_type('apr_os_thread_get', 'thethd', CTypes['???'])

# ## apr_status_t apr_os_thread_put(apr_thread_t ** thd, apr_os_thread_t * thethd, apr_pool_t * cont)
# # Param: thd (apr_thread_t **)
# CTypes.set_fn_param_type('apr_os_thread_put', 'thd', CTypes['???'])
# # Param: thethd (apr_os_thread_t *)
# CTypes.set_fn_param_type('apr_os_thread_put', 'thethd', CTypes['???'])

# ## apr_status_t apr_os_threadkey_get(apr_os_threadkey_t * thekey, apr_threadkey_t * key)
# # Param: thekey (apr_os_threadkey_t *)
# CTypes.set_fn_param_type('apr_os_threadkey_get', 'thekey', CTypes['???'])

# ## apr_status_t apr_os_threadkey_put(apr_threadkey_t ** key, apr_os_threadkey_t * thekey, apr_pool_t * cont)
# # Param: key (apr_threadkey_t **)
# CTypes.set_fn_param_type('apr_os_threadkey_put', 'key', CTypes['???'])
# # Param: thekey (apr_os_threadkey_t *)
# CTypes.set_fn_param_type('apr_os_threadkey_put', 'thekey', CTypes['???'])

# ## apr_status_t apr_os_uuid_get(unsigned char * uuid_data)
# # Param: uuid_data (unsigned char *)
# CTypes.set_fn_param_type('apr_os_uuid_get', 'uuid_data', CTypes['???'])

# ## void * apr_palloc(apr_pool_t * p, apr_size_t size)
# # Return value (void *)
# CTypes.set_fn_return_type('apr_palloc', CTypes['???'])

# ## void * apr_palloc_debug(apr_pool_t * p, apr_size_t size, const char * file_line)
# # Return value (void *)
# CTypes.set_fn_return_type('apr_palloc_debug', CTypes['???'])

# ## apr_status_t apr_parse_addr_port(char ** addr, char ** scope_id, apr_port_t * port, const char * str, apr_pool_t * p)
# # Param: addr (char **)
# CTypes.set_fn_param_type('apr_parse_addr_port', 'addr', CTypes['???'])
# # Param: scope_id (char **)
# CTypes.set_fn_param_type('apr_parse_addr_port', 'scope_id', CTypes['???'])
# # Param: port (apr_port_t *)
# CTypes.set_fn_param_type('apr_parse_addr_port', 'port', CTypes['???'])

# ## apr_status_t apr_password_get(const char * prompt, char * pwbuf, apr_size_t * bufsize)
# # Param: pwbuf (char *)
# CTypes.set_fn_param_type('apr_password_get', 'pwbuf', CTypes['???'])
# # Param: bufsize (apr_size_t *)
# CTypes.set_fn_param_type('apr_password_get', 'bufsize', CTypes['???'])

# ## void * apr_pcalloc_debug(apr_pool_t * p, apr_size_t size, const char * file_line)
# # Return value (void *)
# CTypes.set_fn_return_type('apr_pcalloc_debug', CTypes['???'])

# ## void * apr_pmemdup(apr_pool_t * p, const void * m, apr_size_t n)
# # Return value (void *)
# CTypes.set_fn_return_type('apr_pmemdup', CTypes['???'])
# # Param: m (const void *)
# CTypes.set_fn_param_type('apr_pmemdup', 'm', CTypes['???'])

# ## apr_status_t apr_poll(apr_pollfd_t * aprset, apr_int32_t numsock, apr_int32_t * nsds, apr_interval_time_t timeout)
# # Param: nsds (apr_int32_t *)
# CTypes.set_fn_param_type('apr_poll', 'nsds', CTypes['???'])
# # Param: timeout (apr_interval_time_t)
# CTypes.set_fn_param_type('apr_poll', 'timeout', CTypes['???'])

# ## apr_status_t apr_pollcb_create(apr_pollcb_t ** pollcb, apr_uint32_t size, apr_pool_t * p, apr_uint32_t flags)
# # Param: pollcb (apr_pollcb_t **)
# CTypes.set_fn_param_type('apr_pollcb_create', 'pollcb', CTypes['???'])

# ## apr_status_t apr_pollcb_create_ex(apr_pollcb_t ** pollcb, apr_uint32_t size, apr_pool_t * p, apr_uint32_t flags, apr_pollset_method_e method)
# # Param: pollcb (apr_pollcb_t **)
# CTypes.set_fn_param_type('apr_pollcb_create_ex', 'pollcb', CTypes['???'])

# ## apr_status_t apr_pollcb_poll(apr_pollcb_t * pollcb, apr_interval_time_t timeout, apr_pollcb_cb_t func, void * baton)
# # Param: timeout (apr_interval_time_t)
# CTypes.set_fn_param_type('apr_pollcb_poll', 'timeout', CTypes['???'])
# # Param: func (apr_pollcb_cb_t)
# CTypes.set_fn_param_type('apr_pollcb_poll', 'func', CTypes['???'])
# # Param: baton (void *)
# CTypes.set_fn_param_type('apr_pollcb_poll', 'baton', CTypes['???'])

# ## apr_status_t apr_pollset_create(apr_pollset_t ** pollset, apr_uint32_t size, apr_pool_t * p, apr_uint32_t flags)
# # Param: pollset (apr_pollset_t **)
# CTypes.set_fn_param_type('apr_pollset_create', 'pollset', CTypes['???'])

# ## apr_status_t apr_pollset_create_ex(apr_pollset_t ** pollset, apr_uint32_t size, apr_pool_t * p, apr_uint32_t flags, apr_pollset_method_e method)
# # Param: pollset (apr_pollset_t **)
# CTypes.set_fn_param_type('apr_pollset_create_ex', 'pollset', CTypes['???'])

# ## apr_status_t apr_pollset_poll(apr_pollset_t * pollset, apr_interval_time_t timeout, apr_int32_t * num, const apr_pollfd_t ** descriptors)
# # Param: timeout (apr_interval_time_t)
# CTypes.set_fn_param_type('apr_pollset_poll', 'timeout', CTypes['???'])
# # Param: num (apr_int32_t *)
# CTypes.set_fn_param_type('apr_pollset_poll', 'num', CTypes['???'])
# # Param: descriptors (const apr_pollfd_t **)
# CTypes.set_fn_param_type('apr_pollset_poll', 'descriptors', CTypes['???'])

# ## apr_abortfunc_t apr_pool_abort_get(apr_pool_t * pool)
# # Return value (apr_abortfunc_t)
# CTypes.set_fn_return_type('apr_pool_abort_get', CTypes['???'])

# ## void apr_pool_abort_set(apr_abortfunc_t abortfunc, apr_pool_t * pool)
# # Param: abortfunc (apr_abortfunc_t)
# CTypes.set_fn_param_type('apr_pool_abort_set', 'abortfunc', CTypes['???'])

# ## void apr_pool_child_cleanup_set(apr_pool_t * p, const void * data, apr_status_t (*)(void *) plain_cleanup, apr_status_t (*)(void *) child_cleanup)
# # Param: data (const void *)
# CTypes.set_fn_param_type('apr_pool_child_cleanup_set', 'data', CTypes['???'])
# # Param: plain_cleanup (apr_status_t (*)(void *))
# CTypes.set_fn_param_type('apr_pool_child_cleanup_set', 'plain_cleanup', CTypes['???'])
# # Param: child_cleanup (apr_status_t (*)(void *))
# CTypes.set_fn_param_type('apr_pool_child_cleanup_set', 'child_cleanup', CTypes['???'])

# ## void apr_pool_cleanup_kill(apr_pool_t * p, const void * data, apr_status_t (*)(void *) cleanup)
# # Param: data (const void *)
# CTypes.set_fn_param_type('apr_pool_cleanup_kill', 'data', CTypes['???'])
# # Param: cleanup (apr_status_t (*)(void *))
# CTypes.set_fn_param_type('apr_pool_cleanup_kill', 'cleanup', CTypes['???'])

# ## apr_status_t apr_pool_cleanup_null(void * data)
# # Param: data (void *)
# CTypes.set_fn_param_type('apr_pool_cleanup_null', 'data', CTypes['???'])

# ## void apr_pool_cleanup_register(apr_pool_t * p, const void * data, apr_status_t (*)(void *) plain_cleanup, apr_status_t (*)(void *) child_cleanup)
# # Param: data (const void *)
# CTypes.set_fn_param_type('apr_pool_cleanup_register', 'data', CTypes['???'])
# # Param: plain_cleanup (apr_status_t (*)(void *))
# CTypes.set_fn_param_type('apr_pool_cleanup_register', 'plain_cleanup', CTypes['???'])
# # Param: child_cleanup (apr_status_t (*)(void *))
# CTypes.set_fn_param_type('apr_pool_cleanup_register', 'child_cleanup', CTypes['???'])

# ## apr_status_t apr_pool_cleanup_run(apr_pool_t * p, void * data, apr_status_t (*)(void *) cleanup)
# # Param: data (void *)
# CTypes.set_fn_param_type('apr_pool_cleanup_run', 'data', CTypes['???'])
# # Param: cleanup (apr_status_t (*)(void *))
# CTypes.set_fn_param_type('apr_pool_cleanup_run', 'cleanup', CTypes['???'])

# ## apr_status_t apr_pool_create_core_ex(apr_pool_t ** newpool, apr_abortfunc_t abort_fn, apr_allocator_t * allocator)
# # Param: newpool (apr_pool_t **)
# CTypes.set_fn_param_type('apr_pool_create_core_ex', 'newpool', CTypes['???'])
# # Param: abort_fn (apr_abortfunc_t)
# CTypes.set_fn_param_type('apr_pool_create_core_ex', 'abort_fn', CTypes['???'])

# ## apr_status_t apr_pool_create_core_ex_debug(apr_pool_t ** newpool, apr_abortfunc_t abort_fn, apr_allocator_t * allocator, const char * file_line)
# # Param: newpool (apr_pool_t **)
# CTypes.set_fn_param_type('apr_pool_create_core_ex_debug', 'newpool', CTypes['???'])
# # Param: abort_fn (apr_abortfunc_t)
# CTypes.set_fn_param_type('apr_pool_create_core_ex_debug', 'abort_fn', CTypes['???'])

# ## apr_status_t apr_pool_create_ex(apr_pool_t ** newpool, apr_pool_t * parent, apr_abortfunc_t abort_fn, apr_allocator_t * allocator)
# # Param: newpool (apr_pool_t **)
# CTypes.set_fn_param_type('apr_pool_create_ex', 'newpool', CTypes['???'])
# # Param: abort_fn (apr_abortfunc_t)
# CTypes.set_fn_param_type('apr_pool_create_ex', 'abort_fn', CTypes['???'])

# ## apr_status_t apr_pool_create_ex_debug(apr_pool_t ** newpool, apr_pool_t * parent, apr_abortfunc_t abort_fn, apr_allocator_t * allocator, const char * file_line)
# # Param: newpool (apr_pool_t **)
# CTypes.set_fn_param_type('apr_pool_create_ex_debug', 'newpool', CTypes['???'])
# # Param: abort_fn (apr_abortfunc_t)
# CTypes.set_fn_param_type('apr_pool_create_ex_debug', 'abort_fn', CTypes['???'])

# ## apr_status_t apr_pool_create_unmanaged_ex(apr_pool_t ** newpool, apr_abortfunc_t abort_fn, apr_allocator_t * allocator)
# # Param: newpool (apr_pool_t **)
# CTypes.set_fn_param_type('apr_pool_create_unmanaged_ex', 'newpool', CTypes['???'])
# # Param: abort_fn (apr_abortfunc_t)
# CTypes.set_fn_param_type('apr_pool_create_unmanaged_ex', 'abort_fn', CTypes['???'])

# ## apr_status_t apr_pool_create_unmanaged_ex_debug(apr_pool_t ** newpool, apr_abortfunc_t abort_fn, apr_allocator_t * allocator, const char * file_line)
# # Param: newpool (apr_pool_t **)
# CTypes.set_fn_param_type('apr_pool_create_unmanaged_ex_debug', 'newpool', CTypes['???'])
# # Param: abort_fn (apr_abortfunc_t)
# CTypes.set_fn_param_type('apr_pool_create_unmanaged_ex_debug', 'abort_fn', CTypes['???'])

# ## void apr_pool_pre_cleanup_register(apr_pool_t * p, const void * data, apr_status_t (*)(void *) plain_cleanup)
# # Param: data (const void *)
# CTypes.set_fn_param_type('apr_pool_pre_cleanup_register', 'data', CTypes['???'])
# # Param: plain_cleanup (apr_status_t (*)(void *))
# CTypes.set_fn_param_type('apr_pool_pre_cleanup_register', 'plain_cleanup', CTypes['???'])

# ## apr_status_t apr_pool_userdata_get(void ** data, const char * key, apr_pool_t * pool)
# # Param: data (void **)
# CTypes.set_fn_param_type('apr_pool_userdata_get', 'data', CTypes['???'])

# ## apr_status_t apr_pool_userdata_set(const void * data, const char * key, apr_status_t (*)(void *) cleanup, apr_pool_t * pool)
# # Param: data (const void *)
# CTypes.set_fn_param_type('apr_pool_userdata_set', 'data', CTypes['???'])
# # Param: cleanup (apr_status_t (*)(void *))
# CTypes.set_fn_param_type('apr_pool_userdata_set', 'cleanup', CTypes['???'])

# ## apr_status_t apr_pool_userdata_setn(const void * data, const char * key, apr_status_t (*)(void *) cleanup, apr_pool_t * pool)
# # Param: data (const void *)
# CTypes.set_fn_param_type('apr_pool_userdata_setn', 'data', CTypes['???'])
# # Param: cleanup (apr_status_t (*)(void *))
# CTypes.set_fn_param_type('apr_pool_userdata_setn', 'cleanup', CTypes['???'])

# ## apr_status_t apr_proc_create(apr_proc_t * new_proc, const char * progname, const char *const * args, const char *const * env, apr_procattr_t * attr, apr_pool_t * pool)
# # Param: args (const char *const *)
# CTypes.set_fn_param_type('apr_proc_create', 'args', CTypes['???'])
# # Param: env (const char *const *)
# CTypes.set_fn_param_type('apr_proc_create', 'env', CTypes['???'])

# ## apr_status_t apr_proc_mutex_child_init(apr_proc_mutex_t ** mutex, const char * fname, apr_pool_t * pool)
# # Param: mutex (apr_proc_mutex_t **)
# CTypes.set_fn_param_type('apr_proc_mutex_child_init', 'mutex', CTypes['???'])

# ## apr_status_t apr_proc_mutex_cleanup(void * mutex)
# # Param: mutex (void *)
# CTypes.set_fn_param_type('apr_proc_mutex_cleanup', 'mutex', CTypes['???'])

# ## apr_status_t apr_proc_mutex_create(apr_proc_mutex_t ** mutex, const char * fname, apr_lockmech_e mech, apr_pool_t * pool)
# # Param: mutex (apr_proc_mutex_t **)
# CTypes.set_fn_param_type('apr_proc_mutex_create', 'mutex', CTypes['???'])

# ## void apr_proc_other_child_register(apr_proc_t * proc, void (*)(int, void *, int) maintenance, void * data, apr_file_t * write_fd, apr_pool_t * p)
# # Param: maintenance (void (*)(int, void *, int))
# CTypes.set_fn_param_type('apr_proc_other_child_register', 'maintenance', CTypes['???'])
# # Param: data (void *)
# CTypes.set_fn_param_type('apr_proc_other_child_register', 'data', CTypes['???'])

# ## void apr_proc_other_child_unregister(void * data)
# # Param: data (void *)
# CTypes.set_fn_param_type('apr_proc_other_child_unregister', 'data', CTypes['???'])

# ## apr_status_t apr_proc_wait(apr_proc_t * proc, int * exitcode, apr_exit_why_e * exitwhy, apr_wait_how_e waithow)
# # Param: exitcode (int *)
# CTypes.set_fn_param_type('apr_proc_wait', 'exitcode', CTypes['???'])
# # Param: exitwhy (apr_exit_why_e *)
# CTypes.set_fn_param_type('apr_proc_wait', 'exitwhy', CTypes['???'])

# ## apr_status_t apr_proc_wait_all_procs(apr_proc_t * proc, int * exitcode, apr_exit_why_e * exitwhy, apr_wait_how_e waithow, apr_pool_t * p)
# # Param: exitcode (int *)
# CTypes.set_fn_param_type('apr_proc_wait_all_procs', 'exitcode', CTypes['???'])
# # Param: exitwhy (apr_exit_why_e *)
# CTypes.set_fn_param_type('apr_proc_wait_all_procs', 'exitwhy', CTypes['???'])

# ## apr_status_t apr_procattr_child_errfn_set(apr_procattr_t * attr, apr_child_errfn_t * errfn)
# # Param: errfn (apr_child_errfn_t *)
# CTypes.set_fn_param_type('apr_procattr_child_errfn_set', 'errfn', CTypes['???'])

# ## apr_status_t apr_procattr_create(apr_procattr_t ** new_attr, apr_pool_t * cont)
# # Param: new_attr (apr_procattr_t **)
# CTypes.set_fn_param_type('apr_procattr_create', 'new_attr', CTypes['???'])

# ## apr_status_t apr_procattr_limit_set(apr_procattr_t * attr, apr_int32_t what, struct rlimit * limit)
# # Param: limit (struct rlimit *)
# CTypes.set_fn_param_type('apr_procattr_limit_set', 'limit', CTypes['???'])

# ## char * apr_psprintf(apr_pool_t * p, const char * fmt)
# # Return value (char *)
# CTypes.set_fn_return_type('apr_psprintf', CTypes['???'])

# ## char * apr_pstrcat(apr_pool_t * p)
# # Return value (char *)
# CTypes.set_fn_return_type('apr_pstrcat', CTypes['???'])

# ## char * apr_pstrcatv(apr_pool_t * p, const struct iovec * vec, apr_size_t nvec, apr_size_t * nbytes)
# # Return value (char *)
# CTypes.set_fn_return_type('apr_pstrcatv', CTypes['???'])
# # Param: vec (const struct iovec *)
# CTypes.set_fn_param_type('apr_pstrcatv', 'vec', CTypes['???'])
# # Param: nbytes (apr_size_t *)
# CTypes.set_fn_param_type('apr_pstrcatv', 'nbytes', CTypes['???'])

# ## char * apr_pstrdup(apr_pool_t * p, const char * s)
# # Return value (char *)
# CTypes.set_fn_return_type('apr_pstrdup', CTypes['???'])

# ## char * apr_pstrmemdup(apr_pool_t * p, const char * s, apr_size_t n)
# # Return value (char *)
# CTypes.set_fn_return_type('apr_pstrmemdup', CTypes['???'])

# ## char * apr_pstrndup(apr_pool_t * p, const char * s, apr_size_t n)
# # Return value (char *)
# CTypes.set_fn_return_type('apr_pstrndup', CTypes['???'])

# ## char * apr_pvsprintf(apr_pool_t * p, const char * fmt, int ap)
# # Return value (char *)
# CTypes.set_fn_return_type('apr_pvsprintf', CTypes['???'])

# ## apr_status_t apr_queue_create(apr_queue_t ** queue, unsigned int queue_capacity, apr_pool_t * a)
# # Param: queue (apr_queue_t **)
# CTypes.set_fn_param_type('apr_queue_create', 'queue', CTypes['???'])

# ## apr_status_t apr_queue_pop(apr_queue_t * queue, void ** data)
# # Param: data (void **)
# CTypes.set_fn_param_type('apr_queue_pop', 'data', CTypes['???'])

# ## apr_status_t apr_queue_push(apr_queue_t * queue, void * data)
# # Param: data (void *)
# CTypes.set_fn_param_type('apr_queue_push', 'data', CTypes['???'])

# ## apr_status_t apr_queue_trypop(apr_queue_t * queue, void ** data)
# # Param: data (void **)
# CTypes.set_fn_param_type('apr_queue_trypop', 'data', CTypes['???'])

# ## apr_status_t apr_queue_trypush(apr_queue_t * queue, void * data)
# # Param: data (void *)
# CTypes.set_fn_param_type('apr_queue_trypush', 'data', CTypes['???'])

# ## void apr_random_add_entropy(apr_random_t * g, const void * entropy_, apr_size_t bytes)
# # Param: entropy_ (const void *)
# CTypes.set_fn_param_type('apr_random_add_entropy', 'entropy_', CTypes['???'])

# ## apr_status_t apr_random_insecure_bytes(apr_random_t * g, void * random, apr_size_t bytes)
# # Param: random (void *)
# CTypes.set_fn_param_type('apr_random_insecure_bytes', 'random', CTypes['???'])

# ## apr_status_t apr_random_secure_bytes(apr_random_t * g, void * random, apr_size_t bytes)
# # Param: random (void *)
# CTypes.set_fn_param_type('apr_random_secure_bytes', 'random', CTypes['???'])

# ## apr_status_t apr_reslist_acquire(apr_reslist_t * reslist, void ** resource)
# # Param: resource (void **)
# CTypes.set_fn_param_type('apr_reslist_acquire', 'resource', CTypes['???'])

# ## apr_status_t apr_reslist_create(apr_reslist_t ** reslist, int min, int smax, int hmax, apr_interval_time_t ttl, apr_reslist_constructor con, apr_reslist_destructor de, void * params, apr_pool_t * pool)
# # Param: reslist (apr_reslist_t **)
# CTypes.set_fn_param_type('apr_reslist_create', 'reslist', CTypes['???'])
# # Param: ttl (apr_interval_time_t)
# CTypes.set_fn_param_type('apr_reslist_create', 'ttl', CTypes['???'])
# # Param: con (apr_reslist_constructor)
# CTypes.set_fn_param_type('apr_reslist_create', 'con', CTypes['???'])
# # Param: de (apr_reslist_destructor)
# CTypes.set_fn_param_type('apr_reslist_create', 'de', CTypes['???'])
# # Param: params (void *)
# CTypes.set_fn_param_type('apr_reslist_create', 'params', CTypes['???'])

# ## apr_status_t apr_reslist_invalidate(apr_reslist_t * reslist, void * resource)
# # Param: resource (void *)
# CTypes.set_fn_param_type('apr_reslist_invalidate', 'resource', CTypes['???'])

# ## apr_status_t apr_reslist_release(apr_reslist_t * reslist, void * resource)
# # Param: resource (void *)
# CTypes.set_fn_param_type('apr_reslist_release', 'resource', CTypes['???'])

# ## void apr_reslist_timeout_set(apr_reslist_t * reslist, apr_interval_time_t timeout)
# # Param: timeout (apr_interval_time_t)
# CTypes.set_fn_param_type('apr_reslist_timeout_set', 'timeout', CTypes['???'])

# ## apr_status_t apr_rfc822_date(char * date_str, apr_time_t t)
# # Param: date_str (char *)
# CTypes.set_fn_param_type('apr_rfc822_date', 'date_str', CTypes['???'])
# # Param: t (apr_time_t)
# CTypes.set_fn_param_type('apr_rfc822_date', 't', CTypes['???'])

# ## void * apr_rmm_addr_get(apr_rmm_t * rmm, apr_rmm_off_t entity)
# # Return value (void *)
# CTypes.set_fn_return_type('apr_rmm_addr_get', CTypes['???'])

# ## apr_status_t apr_rmm_attach(apr_rmm_t ** rmm, apr_anylock_t * lock, void * membuf, apr_pool_t * cont)
# # Param: rmm (apr_rmm_t **)
# CTypes.set_fn_param_type('apr_rmm_attach', 'rmm', CTypes['???'])
# # Param: membuf (void *)
# CTypes.set_fn_param_type('apr_rmm_attach', 'membuf', CTypes['???'])

# ## apr_status_t apr_rmm_init(apr_rmm_t ** rmm, apr_anylock_t * lock, void * membuf, apr_size_t memsize, apr_pool_t * cont)
# # Param: rmm (apr_rmm_t **)
# CTypes.set_fn_param_type('apr_rmm_init', 'rmm', CTypes['???'])
# # Param: membuf (void *)
# CTypes.set_fn_param_type('apr_rmm_init', 'membuf', CTypes['???'])

# ## apr_rmm_off_t apr_rmm_offset_get(apr_rmm_t * rmm, void * entity)
# # Param: entity (void *)
# CTypes.set_fn_param_type('apr_rmm_offset_get', 'entity', CTypes['???'])

# ## apr_rmm_off_t apr_rmm_realloc(apr_rmm_t * rmm, void * entity, apr_size_t reqsize)
# # Param: entity (void *)
# CTypes.set_fn_param_type('apr_rmm_realloc', 'entity', CTypes['???'])

# ## apr_status_t apr_sdbm_open(apr_sdbm_t ** db, const char * name, apr_int32_t mode, apr_fileperms_t perms, apr_pool_t * p)
# # Param: db (apr_sdbm_t **)
# CTypes.set_fn_param_type('apr_sdbm_open', 'db', CTypes['???'])

# ## void apr_sha1_base64(const char * clear, int len, char * out)
# # Param: out (char *)
# CTypes.set_fn_param_type('apr_sha1_base64', 'out', CTypes['???'])

# ## void apr_sha1_final(unsigned char [20] digest, apr_sha1_ctx_t * context)
# # Param: digest (unsigned char [20])
# CTypes.set_fn_param_type('apr_sha1_final', 'digest', CTypes['???'])

# ## void apr_sha1_update_binary(apr_sha1_ctx_t * context, const unsigned char * input, unsigned int inputLen)
# # Param: input (const unsigned char *)
# CTypes.set_fn_param_type('apr_sha1_update_binary', 'input', CTypes['???'])

# ## apr_status_t apr_shm_attach(apr_shm_t ** m, const char * filename, apr_pool_t * pool)
# # Param: m (apr_shm_t **)
# CTypes.set_fn_param_type('apr_shm_attach', 'm', CTypes['???'])

# ## void * apr_shm_baseaddr_get(const apr_shm_t * m)
# # Return value (void *)
# CTypes.set_fn_return_type('apr_shm_baseaddr_get', CTypes['???'])

# ## apr_status_t apr_shm_create(apr_shm_t ** m, apr_size_t reqsize, const char * filename, apr_pool_t * pool)
# # Param: m (apr_shm_t **)
# CTypes.set_fn_param_type('apr_shm_create', 'm', CTypes['???'])

# ## apr_sigfunc_t * apr_signal(int signo, apr_sigfunc_t * func)
# # Return value (apr_sigfunc_t *)
# CTypes.set_fn_return_type('apr_signal', CTypes['???'])
# # Param: func (apr_sigfunc_t *)
# CTypes.set_fn_param_type('apr_signal', 'func', CTypes['???'])

# ## apr_status_t apr_signal_thread(int (*)(int) signal_handler)
# # Param: signal_handler (int (*)(int))
# CTypes.set_fn_param_type('apr_signal_thread', 'signal_handler', CTypes['???'])

# ## void apr_sleep(apr_interval_time_t t)
# # Param: t (apr_interval_time_t)
# CTypes.set_fn_param_type('apr_sleep', 't', CTypes['???'])

# ## int apr_snprintf(char * buf, apr_size_t len, const char * format)
# # Param: buf (char *)
# CTypes.set_fn_param_type('apr_snprintf', 'buf', CTypes['???'])

# ## apr_status_t apr_sockaddr_info_get(apr_sockaddr_t ** sa, const char * hostname, apr_int32_t family, apr_port_t port, apr_int32_t flags, apr_pool_t * p)
# # Param: sa (apr_sockaddr_t **)
# CTypes.set_fn_param_type('apr_sockaddr_info_get', 'sa', CTypes['???'])

# ## apr_status_t apr_sockaddr_ip_get(char ** addr, apr_sockaddr_t * sockaddr)
# # Param: addr (char **)
# CTypes.set_fn_param_type('apr_sockaddr_ip_get', 'addr', CTypes['???'])

# ## apr_status_t apr_sockaddr_ip_getbuf(char * buf, apr_size_t buflen, apr_sockaddr_t * sockaddr)
# # Param: buf (char *)
# CTypes.set_fn_param_type('apr_sockaddr_ip_getbuf', 'buf', CTypes['???'])

# ## apr_status_t apr_socket_accept(apr_socket_t ** new_sock, apr_socket_t * sock, apr_pool_t * connection_pool)
# # Param: new_sock (apr_socket_t **)
# CTypes.set_fn_param_type('apr_socket_accept', 'new_sock', CTypes['???'])

# ## apr_status_t apr_socket_addr_get(apr_sockaddr_t ** sa, apr_interface_e which, apr_socket_t * sock)
# # Param: sa (apr_sockaddr_t **)
# CTypes.set_fn_param_type('apr_socket_addr_get', 'sa', CTypes['???'])

# ## apr_status_t apr_socket_atmark(apr_socket_t * sock, int * atmark)
# # Param: atmark (int *)
# CTypes.set_fn_param_type('apr_socket_atmark', 'atmark', CTypes['???'])

# ## apr_status_t apr_socket_atreadeof(apr_socket_t * sock, int * atreadeof)
# # Param: atreadeof (int *)
# CTypes.set_fn_param_type('apr_socket_atreadeof', 'atreadeof', CTypes['???'])

# ## apr_status_t apr_socket_create(apr_socket_t ** new_sock, int family, int type, int protocol, apr_pool_t * cont)
# # Param: new_sock (apr_socket_t **)
# CTypes.set_fn_param_type('apr_socket_create', 'new_sock', CTypes['???'])

# ## apr_status_t apr_socket_data_get(void ** data, const char * key, apr_socket_t * sock)
# # Param: data (void **)
# CTypes.set_fn_param_type('apr_socket_data_get', 'data', CTypes['???'])

# ## apr_status_t apr_socket_data_set(apr_socket_t * sock, void * data, const char * key, apr_status_t (*)(void *) cleanup)
# # Param: data (void *)
# CTypes.set_fn_param_type('apr_socket_data_set', 'data', CTypes['???'])
# # Param: cleanup (apr_status_t (*)(void *))
# CTypes.set_fn_param_type('apr_socket_data_set', 'cleanup', CTypes['???'])

# ## apr_status_t apr_socket_opt_get(apr_socket_t * sock, apr_int32_t opt, apr_int32_t * on)
# # Param: on (apr_int32_t *)
# CTypes.set_fn_param_type('apr_socket_opt_get', 'on', CTypes['???'])

# ## apr_status_t apr_socket_protocol_get(apr_socket_t * sock, int * protocol)
# # Param: protocol (int *)
# CTypes.set_fn_param_type('apr_socket_protocol_get', 'protocol', CTypes['???'])

# ## apr_status_t apr_socket_recv(apr_socket_t * sock, char * buf, apr_size_t * len)
# # Param: buf (char *)
# CTypes.set_fn_param_type('apr_socket_recv', 'buf', CTypes['???'])
# # Param: len (apr_size_t *)
# CTypes.set_fn_param_type('apr_socket_recv', 'len', CTypes['???'])

# ## apr_status_t apr_socket_recvfrom(apr_sockaddr_t * from, apr_socket_t * sock, apr_int32_t flags, char * buf, apr_size_t * len)
# # Param: buf (char *)
# CTypes.set_fn_param_type('apr_socket_recvfrom', 'buf', CTypes['???'])
# # Param: len (apr_size_t *)
# CTypes.set_fn_param_type('apr_socket_recvfrom', 'len', CTypes['???'])

# ## apr_status_t apr_socket_send(apr_socket_t * sock, const char * buf, apr_size_t * len)
# # Param: len (apr_size_t *)
# CTypes.set_fn_param_type('apr_socket_send', 'len', CTypes['???'])

# ## apr_status_t apr_socket_sendfile(apr_socket_t * sock, apr_file_t * file, apr_hdtr_t * hdtr, apr_off_t * offset, apr_size_t * len, apr_int32_t flags)
# # Param: offset (apr_off_t *)
# CTypes.set_fn_param_type('apr_socket_sendfile', 'offset', CTypes['???'])
# # Param: len (apr_size_t *)
# CTypes.set_fn_param_type('apr_socket_sendfile', 'len', CTypes['???'])

# ## apr_status_t apr_socket_sendto(apr_socket_t * sock, apr_sockaddr_t * where, apr_int32_t flags, const char * buf, apr_size_t * len)
# # Param: len (apr_size_t *)
# CTypes.set_fn_param_type('apr_socket_sendto', 'len', CTypes['???'])

# ## apr_status_t apr_socket_sendv(apr_socket_t * sock, const struct iovec * vec, apr_int32_t nvec, apr_size_t * len)
# # Param: vec (const struct iovec *)
# CTypes.set_fn_param_type('apr_socket_sendv', 'vec', CTypes['???'])
# # Param: len (apr_size_t *)
# CTypes.set_fn_param_type('apr_socket_sendv', 'len', CTypes['???'])

# ## apr_status_t apr_socket_timeout_get(apr_socket_t * sock, apr_interval_time_t * t)
# # Param: t (apr_interval_time_t *)
# CTypes.set_fn_param_type('apr_socket_timeout_get', 't', CTypes['???'])

# ## apr_status_t apr_socket_timeout_set(apr_socket_t * sock, apr_interval_time_t t)
# # Param: t (apr_interval_time_t)
# CTypes.set_fn_param_type('apr_socket_timeout_set', 't', CTypes['???'])

# ## apr_status_t apr_socket_type_get(apr_socket_t * sock, int * type)
# # Param: type (int *)
# CTypes.set_fn_param_type('apr_socket_type_get', 'type', CTypes['???'])

# ## char * apr_strerror(apr_status_t statcode, char * buf, apr_size_t bufsize)
# # Return value (char *)
# CTypes.set_fn_return_type('apr_strerror', CTypes['???'])
# # Param: buf (char *)
# CTypes.set_fn_param_type('apr_strerror', 'buf', CTypes['???'])

# ## char * apr_strfsize(apr_off_t size, char * buf)
# # Return value (char *)
# CTypes.set_fn_return_type('apr_strfsize', CTypes['???'])
# # Param: size (apr_off_t)
# CTypes.set_fn_param_type('apr_strfsize', 'size', CTypes['???'])
# # Param: buf (char *)
# CTypes.set_fn_param_type('apr_strfsize', 'buf', CTypes['???'])

# ## apr_status_t apr_strftime(char * s, apr_size_t * retsize, apr_size_t max, const char * format, apr_time_exp_t * tm)
# # Param: s (char *)
# CTypes.set_fn_param_type('apr_strftime', 's', CTypes['???'])
# # Param: retsize (apr_size_t *)
# CTypes.set_fn_param_type('apr_strftime', 'retsize', CTypes['???'])

# ## apr_status_t apr_strtoff(apr_off_t * offset, const char * buf, char ** end, int base)
# # Param: offset (apr_off_t *)
# CTypes.set_fn_param_type('apr_strtoff', 'offset', CTypes['???'])
# # Param: end (char **)
# CTypes.set_fn_param_type('apr_strtoff', 'end', CTypes['???'])

# ## apr_int64_t apr_strtoi64(const char * buf, char ** end, int base)
# # Return value (apr_int64_t)
# CTypes.set_fn_return_type('apr_strtoi64', CTypes['???'])
# # Param: end (char **)
# CTypes.set_fn_param_type('apr_strtoi64', 'end', CTypes['???'])

# ## char * apr_strtok(char * str, const char * sep, char ** last)
# # Return value (char *)
# CTypes.set_fn_return_type('apr_strtok', CTypes['???'])
# # Param: str (char *)
# CTypes.set_fn_param_type('apr_strtok', 'str', CTypes['???'])
# # Param: last (char **)
# CTypes.set_fn_param_type('apr_strtok', 'last', CTypes['???'])

# ## int apr_table_do(apr_table_do_callback_fn_t * comp, void * rec, const apr_table_t * t)
# # Param: comp (apr_table_do_callback_fn_t *)
# CTypes.set_fn_param_type('apr_table_do', 'comp', CTypes['???'])
# # Param: rec (void *)
# CTypes.set_fn_param_type('apr_table_do', 'rec', CTypes['???'])

# ## int apr_table_vdo(apr_table_do_callback_fn_t * comp, void * rec, const apr_table_t * t, int vp)
# # Param: comp (apr_table_do_callback_fn_t *)
# CTypes.set_fn_param_type('apr_table_vdo', 'comp', CTypes['???'])
# # Param: rec (void *)
# CTypes.set_fn_param_type('apr_table_vdo', 'rec', CTypes['???'])

# ## apr_status_t apr_temp_dir_get(const char ** temp_dir, apr_pool_t * p)
# # Param: temp_dir (const char **)
# CTypes.set_fn_param_type('apr_temp_dir_get', 'temp_dir', CTypes['???'])

# ## apr_status_t apr_thread_cond_create(apr_thread_cond_t ** cond, apr_pool_t * pool)
# # Param: cond (apr_thread_cond_t **)
# CTypes.set_fn_param_type('apr_thread_cond_create', 'cond', CTypes['???'])

# ## apr_status_t apr_thread_cond_timedwait(apr_thread_cond_t * cond, apr_thread_mutex_t * mutex, apr_interval_time_t timeout)
# # Param: timeout (apr_interval_time_t)
# CTypes.set_fn_param_type('apr_thread_cond_timedwait', 'timeout', CTypes['???'])

# ## apr_status_t apr_thread_create(apr_thread_t ** new_thread, apr_threadattr_t * attr, apr_thread_start_t func, void * data, apr_pool_t * cont)
# # Param: new_thread (apr_thread_t **)
# CTypes.set_fn_param_type('apr_thread_create', 'new_thread', CTypes['???'])
# # Param: func (apr_thread_start_t)
# CTypes.set_fn_param_type('apr_thread_create', 'func', CTypes['???'])
# # Param: data (void *)
# CTypes.set_fn_param_type('apr_thread_create', 'data', CTypes['???'])

# ## apr_status_t apr_thread_data_get(void ** data, const char * key, apr_thread_t * thread)
# # Param: data (void **)
# CTypes.set_fn_param_type('apr_thread_data_get', 'data', CTypes['???'])

# ## apr_status_t apr_thread_data_set(void * data, const char * key, apr_status_t (*)(void *) cleanup, apr_thread_t * thread)
# # Param: data (void *)
# CTypes.set_fn_param_type('apr_thread_data_set', 'data', CTypes['???'])
# # Param: cleanup (apr_status_t (*)(void *))
# CTypes.set_fn_param_type('apr_thread_data_set', 'cleanup', CTypes['???'])

# ## apr_status_t apr_thread_join(apr_status_t * retval, apr_thread_t * thd)
# # Param: retval (apr_status_t *)
# CTypes.set_fn_param_type('apr_thread_join', 'retval', CTypes['???'])

# ## apr_status_t apr_thread_mutex_create(apr_thread_mutex_t ** mutex, unsigned int flags, apr_pool_t * pool)
# # Param: mutex (apr_thread_mutex_t **)
# CTypes.set_fn_param_type('apr_thread_mutex_create', 'mutex', CTypes['???'])

# ## apr_status_t apr_thread_once(apr_thread_once_t * control, void (*)(void) func)
# # Param: func (void (*)(void))
# CTypes.set_fn_param_type('apr_thread_once', 'func', CTypes['???'])

# ## apr_status_t apr_thread_once_init(apr_thread_once_t ** control, apr_pool_t * p)
# # Param: control (apr_thread_once_t **)
# CTypes.set_fn_param_type('apr_thread_once_init', 'control', CTypes['???'])

# ## apr_status_t apr_thread_pool_create(apr_thread_pool_t ** me, apr_size_t init_threads, apr_size_t max_threads, apr_pool_t * pool)
# # Param: me (apr_thread_pool_t **)
# CTypes.set_fn_param_type('apr_thread_pool_create', 'me', CTypes['???'])

# ## apr_interval_time_t apr_thread_pool_idle_wait_get(apr_thread_pool_t * me)
# # Return value (apr_interval_time_t)
# CTypes.set_fn_return_type('apr_thread_pool_idle_wait_get', CTypes['???'])

# ## apr_interval_time_t apr_thread_pool_idle_wait_set(apr_thread_pool_t * me, apr_interval_time_t timeout)
# # Return value (apr_interval_time_t)
# CTypes.set_fn_return_type('apr_thread_pool_idle_wait_set', CTypes['???'])
# # Param: timeout (apr_interval_time_t)
# CTypes.set_fn_param_type('apr_thread_pool_idle_wait_set', 'timeout', CTypes['???'])

# ## apr_status_t apr_thread_pool_push(apr_thread_pool_t * me, apr_thread_start_t func, void * param, apr_byte_t priority, void * owner)
# # Param: func (apr_thread_start_t)
# CTypes.set_fn_param_type('apr_thread_pool_push', 'func', CTypes['???'])
# # Param: param (void *)
# CTypes.set_fn_param_type('apr_thread_pool_push', 'param', CTypes['???'])
# # Param: owner (void *)
# CTypes.set_fn_param_type('apr_thread_pool_push', 'owner', CTypes['???'])

# ## apr_status_t apr_thread_pool_schedule(apr_thread_pool_t * me, apr_thread_start_t func, void * param, apr_interval_time_t time, void * owner)
# # Param: func (apr_thread_start_t)
# CTypes.set_fn_param_type('apr_thread_pool_schedule', 'func', CTypes['???'])
# # Param: param (void *)
# CTypes.set_fn_param_type('apr_thread_pool_schedule', 'param', CTypes['???'])
# # Param: time (apr_interval_time_t)
# CTypes.set_fn_param_type('apr_thread_pool_schedule', 'time', CTypes['???'])
# # Param: owner (void *)
# CTypes.set_fn_param_type('apr_thread_pool_schedule', 'owner', CTypes['???'])

# ## apr_status_t apr_thread_pool_task_owner_get(apr_thread_t * thd, void ** owner)
# # Param: owner (void **)
# CTypes.set_fn_param_type('apr_thread_pool_task_owner_get', 'owner', CTypes['???'])

# ## apr_status_t apr_thread_pool_tasks_cancel(apr_thread_pool_t * me, void * owner)
# # Param: owner (void *)
# CTypes.set_fn_param_type('apr_thread_pool_tasks_cancel', 'owner', CTypes['???'])

# ## apr_status_t apr_thread_pool_top(apr_thread_pool_t * me, apr_thread_start_t func, void * param, apr_byte_t priority, void * owner)
# # Param: func (apr_thread_start_t)
# CTypes.set_fn_param_type('apr_thread_pool_top', 'func', CTypes['???'])
# # Param: param (void *)
# CTypes.set_fn_param_type('apr_thread_pool_top', 'param', CTypes['???'])
# # Param: owner (void *)
# CTypes.set_fn_param_type('apr_thread_pool_top', 'owner', CTypes['???'])

# ## apr_status_t apr_thread_rwlock_create(apr_thread_rwlock_t ** rwlock, apr_pool_t * pool)
# # Param: rwlock (apr_thread_rwlock_t **)
# CTypes.set_fn_param_type('apr_thread_rwlock_create', 'rwlock', CTypes['???'])

# ## apr_status_t apr_threadattr_create(apr_threadattr_t ** new_attr, apr_pool_t * cont)
# # Param: new_attr (apr_threadattr_t **)
# CTypes.set_fn_param_type('apr_threadattr_create', 'new_attr', CTypes['???'])

# ## apr_status_t apr_threadkey_data_get(void ** data, const char * key, apr_threadkey_t * threadkey)
# # Param: data (void **)
# CTypes.set_fn_param_type('apr_threadkey_data_get', 'data', CTypes['???'])

# ## apr_status_t apr_threadkey_data_set(void * data, const char * key, apr_status_t (*)(void *) cleanup, apr_threadkey_t * threadkey)
# # Param: data (void *)
# CTypes.set_fn_param_type('apr_threadkey_data_set', 'data', CTypes['???'])
# # Param: cleanup (apr_status_t (*)(void *))
# CTypes.set_fn_param_type('apr_threadkey_data_set', 'cleanup', CTypes['???'])

# ## apr_status_t apr_threadkey_private_create(apr_threadkey_t ** key, void (*)(void *) dest, apr_pool_t * cont)
# # Param: key (apr_threadkey_t **)
# CTypes.set_fn_param_type('apr_threadkey_private_create', 'key', CTypes['???'])
# # Param: dest (void (*)(void *))
# CTypes.set_fn_param_type('apr_threadkey_private_create', 'dest', CTypes['???'])

# ## apr_status_t apr_threadkey_private_get(void ** new_mem, apr_threadkey_t * key)
# # Param: new_mem (void **)
# CTypes.set_fn_param_type('apr_threadkey_private_get', 'new_mem', CTypes['???'])

# ## apr_status_t apr_threadkey_private_set(void * priv, apr_threadkey_t * key)
# # Param: priv (void *)
# CTypes.set_fn_param_type('apr_threadkey_private_set', 'priv', CTypes['???'])

# ## apr_status_t apr_time_ansi_put(apr_time_t * result, time_t input)
# # Param: result (apr_time_t *)
# CTypes.set_fn_param_type('apr_time_ansi_put', 'result', CTypes['???'])

# ## apr_status_t apr_time_exp_get(apr_time_t * result, apr_time_exp_t * input)
# # Param: result (apr_time_t *)
# CTypes.set_fn_param_type('apr_time_exp_get', 'result', CTypes['???'])

# ## apr_status_t apr_time_exp_gmt(apr_time_exp_t * result, apr_time_t input)
# # Param: input (apr_time_t)
# CTypes.set_fn_param_type('apr_time_exp_gmt', 'input', CTypes['???'])

# ## apr_status_t apr_time_exp_gmt_get(apr_time_t * result, apr_time_exp_t * input)
# # Param: result (apr_time_t *)
# CTypes.set_fn_param_type('apr_time_exp_gmt_get', 'result', CTypes['???'])

# ## apr_status_t apr_time_exp_lt(apr_time_exp_t * result, apr_time_t input)
# # Param: input (apr_time_t)
# CTypes.set_fn_param_type('apr_time_exp_lt', 'input', CTypes['???'])

# ## apr_status_t apr_time_exp_tz(apr_time_exp_t * result, apr_time_t input, apr_int32_t offs)
# # Param: input (apr_time_t)
# CTypes.set_fn_param_type('apr_time_exp_tz', 'input', CTypes['???'])

# ## apr_time_t apr_time_now()
# # Return value (apr_time_t)
# CTypes.set_fn_return_type('apr_time_now', CTypes['???'])

# ## apr_status_t apr_tokenize_to_argv(const char * arg_str, char *** argv_out, apr_pool_t * token_context)
# # Param: argv_out (char ***)
# CTypes.set_fn_param_type('apr_tokenize_to_argv', 'argv_out', CTypes['???'])

# ## apr_status_t apr_uid_current(apr_uid_t * userid, apr_gid_t * groupid, apr_pool_t * p)
# # Param: userid (apr_uid_t *)
# CTypes.set_fn_param_type('apr_uid_current', 'userid', CTypes['???'])
# # Param: groupid (apr_gid_t *)
# CTypes.set_fn_param_type('apr_uid_current', 'groupid', CTypes['???'])

# ## apr_status_t apr_uid_get(apr_uid_t * userid, apr_gid_t * groupid, const char * username, apr_pool_t * p)
# # Param: userid (apr_uid_t *)
# CTypes.set_fn_param_type('apr_uid_get', 'userid', CTypes['???'])
# # Param: groupid (apr_gid_t *)
# CTypes.set_fn_param_type('apr_uid_get', 'groupid', CTypes['???'])

# ## apr_status_t apr_uid_homepath_get(char ** dirname, const char * username, apr_pool_t * p)
# # Param: dirname (char **)
# CTypes.set_fn_param_type('apr_uid_homepath_get', 'dirname', CTypes['???'])

# ## apr_status_t apr_uid_name_get(char ** username, apr_uid_t userid, apr_pool_t * p)
# # Param: username (char **)
# CTypes.set_fn_param_type('apr_uid_name_get', 'username', CTypes['???'])
# # Param: userid (apr_uid_t)
# CTypes.set_fn_param_type('apr_uid_name_get', 'userid', CTypes['???'])

# ## char * apr_uri_unparse(apr_pool_t * p, const apr_uri_t * uptr, unsigned int flags)
# # Return value (char *)
# CTypes.set_fn_return_type('apr_uri_unparse', CTypes['???'])

# ## void apr_uuid_format(char * buffer, const apr_uuid_t * uuid)
# # Param: buffer (char *)
# CTypes.set_fn_param_type('apr_uuid_format', 'buffer', CTypes['???'])

# ## int apr_vformatter(int (*)(apr_vformatter_buff_t *) flush_func, apr_vformatter_buff_t * c, const char * fmt, int ap)
# # Param: flush_func (int (*)(apr_vformatter_buff_t *))
# CTypes.set_fn_param_type('apr_vformatter', 'flush_func', CTypes['???'])

# ## int apr_vsnprintf(char * buf, apr_size_t len, const char * format, int ap)
# # Param: buf (char *)
# CTypes.set_fn_param_type('apr_vsnprintf', 'buf', CTypes['???'])

# ## apr_status_t apr_xlate_conv_buffer(apr_xlate_t * convset, const char * inbuf, apr_size_t * inbytes_left, char * outbuf, apr_size_t * outbytes_left)
# # Param: inbytes_left (apr_size_t *)
# CTypes.set_fn_param_type('apr_xlate_conv_buffer', 'inbytes_left', CTypes['???'])
# # Param: outbuf (char *)
# CTypes.set_fn_param_type('apr_xlate_conv_buffer', 'outbuf', CTypes['???'])
# # Param: outbytes_left (apr_size_t *)
# CTypes.set_fn_param_type('apr_xlate_conv_buffer', 'outbytes_left', CTypes['???'])

# ## apr_status_t apr_xlate_open(apr_xlate_t ** convset, const char * topage, const char * frompage, apr_pool_t * pool)
# # Param: convset (apr_xlate_t **)
# CTypes.set_fn_param_type('apr_xlate_open', 'convset', CTypes['???'])

# ## apr_status_t apr_xlate_sb_get(apr_xlate_t * convset, int * onoff)
# # Param: onoff (int *)
# CTypes.set_fn_param_type('apr_xlate_sb_get', 'onoff', CTypes['???'])

# ## apr_status_t apr_xml_parse_file(apr_pool_t * p, apr_xml_parser ** parser, apr_xml_doc ** ppdoc, apr_file_t * xmlfd, apr_size_t buffer_length)
# # Param: parser (apr_xml_parser **)
# CTypes.set_fn_param_type('apr_xml_parse_file', 'parser', CTypes['???'])
# # Param: ppdoc (apr_xml_doc **)
# CTypes.set_fn_param_type('apr_xml_parse_file', 'ppdoc', CTypes['???'])

# ## apr_status_t apr_xml_parser_done(apr_xml_parser * parser, apr_xml_doc ** pdoc)
# # Param: pdoc (apr_xml_doc **)
# CTypes.set_fn_param_type('apr_xml_parser_done', 'pdoc', CTypes['???'])

# ## char * apr_xml_parser_geterror(apr_xml_parser * parser, char * errbuf, apr_size_t errbufsize)
# # Return value (char *)
# CTypes.set_fn_return_type('apr_xml_parser_geterror', CTypes['???'])
# # Param: errbuf (char *)
# CTypes.set_fn_param_type('apr_xml_parser_geterror', 'errbuf', CTypes['???'])

# ## void apr_xml_to_text(apr_pool_t * p, const apr_xml_elem * elem, int style, apr_array_header_t * namespaces, int * ns_map, const char ** pbuf, apr_size_t * psize)
# # Param: ns_map (int *)
# CTypes.set_fn_param_type('apr_xml_to_text', 'ns_map', CTypes['???'])
# # Param: pbuf (const char **)
# CTypes.set_fn_param_type('apr_xml_to_text', 'pbuf', CTypes['???'])
# # Param: psize (apr_size_t *)
# CTypes.set_fn_param_type('apr_xml_to_text', 'psize', CTypes['???'])

