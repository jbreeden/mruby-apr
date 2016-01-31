#ifndef MRUBY_APR_FUNCTIONS_HEADER
#define MRUBY_APR_FUNCTIONS_HEADER

#define BIND_apr_app_initialize_FUNCTION FALSE
#define BIND_apr_atoi64_FUNCTION FALSE
#define BIND_apr_collapse_spaces_FUNCTION FALSE
#define BIND_apr_cpystrn_FUNCTION FALSE
#define BIND_apr_ctime_FUNCTION FALSE
#define BIND_apr_dir_close_FUNCTION TRUE
#define BIND_apr_dir_make_FUNCTION TRUE
#define BIND_apr_dir_make_recursive_FUNCTION TRUE
#define BIND_apr_dir_open_FUNCTION FALSE
#define BIND_apr_dir_read_FUNCTION TRUE
#define BIND_apr_dir_remove_FUNCTION TRUE
#define BIND_apr_dir_rewind_FUNCTION TRUE
#define BIND_apr_env_delete_FUNCTION TRUE
#define BIND_apr_env_get_FUNCTION FALSE
#define BIND_apr_env_set_FUNCTION TRUE
#define BIND_apr_file_append_FUNCTION TRUE
#define BIND_apr_file_attrs_set_FUNCTION TRUE
#define BIND_apr_file_buffer_set_FUNCTION FALSE
#define BIND_apr_file_buffer_size_get_FUNCTION TRUE
#define BIND_apr_file_close_FUNCTION TRUE
#define BIND_apr_file_copy_FUNCTION TRUE
#define BIND_apr_file_data_get_FUNCTION FALSE
#define BIND_apr_file_data_set_FUNCTION FALSE
#define BIND_apr_file_datasync_FUNCTION TRUE
#define BIND_apr_file_dup_FUNCTION FALSE
#define BIND_apr_file_dup2_FUNCTION TRUE
#define BIND_apr_file_eof_FUNCTION TRUE
#define BIND_apr_file_flags_get_FUNCTION TRUE
#define BIND_apr_file_flush_FUNCTION TRUE
#define BIND_apr_file_getc_FUNCTION FALSE
#define BIND_apr_file_gets_FUNCTION FALSE
#define BIND_apr_file_info_get_FUNCTION TRUE
#define BIND_apr_file_link_FUNCTION TRUE
#define BIND_apr_file_lock_FUNCTION TRUE
#define BIND_apr_file_mktemp_FUNCTION FALSE
#define BIND_apr_file_mtime_set_FUNCTION FALSE
#define BIND_apr_file_name_get_FUNCTION FALSE
#define BIND_apr_file_namedpipe_create_FUNCTION TRUE
#define BIND_apr_file_open_FUNCTION FALSE
#define BIND_apr_file_open_flags_stderr_FUNCTION FALSE
#define BIND_apr_file_open_flags_stdin_FUNCTION FALSE
#define BIND_apr_file_open_flags_stdout_FUNCTION FALSE
#define BIND_apr_file_open_stderr_FUNCTION FALSE
#define BIND_apr_file_open_stdin_FUNCTION FALSE
#define BIND_apr_file_open_stdout_FUNCTION FALSE
#define BIND_apr_file_perms_set_FUNCTION TRUE
#define BIND_apr_file_pipe_create_FUNCTION FALSE
#define BIND_apr_file_pipe_create_ex_FUNCTION FALSE
#define BIND_apr_file_pipe_timeout_get_FUNCTION FALSE
#define BIND_apr_file_pipe_timeout_set_FUNCTION FALSE
#define BIND_apr_file_printf_FUNCTION TRUE
#define BIND_apr_file_putc_FUNCTION TRUE
#define BIND_apr_file_puts_FUNCTION TRUE
#define BIND_apr_file_read_FUNCTION FALSE
#define BIND_apr_file_read_full_FUNCTION FALSE
#define BIND_apr_file_remove_FUNCTION TRUE
#define BIND_apr_file_rename_FUNCTION TRUE
#define BIND_apr_file_seek_FUNCTION FALSE
#define BIND_apr_file_setaside_FUNCTION FALSE
#define BIND_apr_file_sync_FUNCTION TRUE
#define BIND_apr_file_trunc_FUNCTION FALSE
#define BIND_apr_file_ungetc_FUNCTION TRUE
#define BIND_apr_file_unlock_FUNCTION TRUE
#define BIND_apr_file_write_FUNCTION FALSE
#define BIND_apr_file_write_full_FUNCTION FALSE
#define BIND_apr_file_writev_FUNCTION FALSE
#define BIND_apr_file_writev_full_FUNCTION FALSE
#define BIND_apr_filepath_encoding_FUNCTION FALSE
#define BIND_apr_filepath_get_FUNCTION FALSE
#define BIND_apr_filepath_list_merge_FUNCTION FALSE
#define BIND_apr_filepath_list_split_FUNCTION FALSE
#define BIND_apr_filepath_merge_FUNCTION FALSE
#define BIND_apr_filepath_root_FUNCTION FALSE
#define BIND_apr_filepath_set_FUNCTION TRUE
#define BIND_apr_fnmatch_FUNCTION TRUE
#define BIND_apr_fnmatch_test_FUNCTION TRUE
#define BIND_apr_generate_random_bytes_FUNCTION FALSE
#define BIND_apr_gethostname_FUNCTION FALSE
#define BIND_apr_getnameinfo_FUNCTION FALSE
#define BIND_apr_getservbyname_FUNCTION TRUE
#define BIND_apr_global_mutex_child_init_FUNCTION FALSE
#define BIND_apr_global_mutex_create_FUNCTION FALSE
#define BIND_apr_global_mutex_destroy_FUNCTION TRUE
#define BIND_apr_global_mutex_lock_FUNCTION TRUE
#define BIND_apr_global_mutex_lockfile_FUNCTION TRUE
#define BIND_apr_global_mutex_name_FUNCTION TRUE
#define BIND_apr_global_mutex_trylock_FUNCTION TRUE
#define BIND_apr_global_mutex_unlock_FUNCTION TRUE
#define BIND_apr_initialize_FUNCTION TRUE
#define BIND_apr_ipsubnet_create_FUNCTION FALSE
#define BIND_apr_ipsubnet_test_FUNCTION TRUE
#define BIND_apr_itoa_FUNCTION FALSE
#define BIND_apr_ltoa_FUNCTION FALSE
#define BIND_apr_match_glob_FUNCTION FALSE
#define BIND_apr_mcast_hops_FUNCTION TRUE
#define BIND_apr_mcast_interface_FUNCTION TRUE
#define BIND_apr_mcast_join_FUNCTION TRUE
#define BIND_apr_mcast_leave_FUNCTION TRUE
#define BIND_apr_mcast_loopback_FUNCTION TRUE
#define BIND_apr_off_t_toa_FUNCTION FALSE
#define BIND_apr_palloc_FUNCTION FALSE
#define BIND_apr_palloc_debug_FUNCTION FALSE
#define BIND_apr_parse_addr_port_FUNCTION FALSE
#define BIND_apr_pcalloc_debug_FUNCTION FALSE
#define BIND_apr_pmemdup_FUNCTION FALSE
#define BIND_apr_pool_abort_get_FUNCTION FALSE
#define BIND_apr_pool_abort_set_FUNCTION FALSE
#define BIND_apr_pool_allocator_get_FUNCTION FALSE
#define BIND_apr_pool_child_cleanup_set_FUNCTION FALSE
#define BIND_apr_pool_cleanup_for_exec_FUNCTION TRUE
#define BIND_apr_pool_cleanup_kill_FUNCTION FALSE
#define BIND_apr_pool_cleanup_null_FUNCTION FALSE
#define BIND_apr_pool_cleanup_register_FUNCTION FALSE
#define BIND_apr_pool_cleanup_run_FUNCTION FALSE
#define BIND_apr_pool_clear_FUNCTION TRUE
#define BIND_apr_pool_clear_debug_FUNCTION TRUE
#define BIND_apr_pool_create_core_ex_FUNCTION FALSE
#define BIND_apr_pool_create_core_ex_debug_FUNCTION FALSE
#define BIND_apr_pool_create_ex_FUNCTION FALSE
#define BIND_apr_pool_create_ex_debug_FUNCTION FALSE
#define BIND_apr_pool_create_unmanaged_ex_FUNCTION FALSE
#define BIND_apr_pool_create_unmanaged_ex_debug_FUNCTION FALSE
#define BIND_apr_pool_destroy_FUNCTION TRUE
#define BIND_apr_pool_destroy_debug_FUNCTION TRUE
#define BIND_apr_pool_initialize_FUNCTION TRUE
#define BIND_apr_pool_is_ancestor_FUNCTION TRUE
#define BIND_apr_pool_note_subprocess_FUNCTION TRUE
#define BIND_apr_pool_parent_get_FUNCTION TRUE
#define BIND_apr_pool_pre_cleanup_register_FUNCTION FALSE
#define BIND_apr_pool_tag_FUNCTION TRUE
#define BIND_apr_pool_terminate_FUNCTION TRUE
#define BIND_apr_pool_userdata_get_FUNCTION FALSE
#define BIND_apr_pool_userdata_set_FUNCTION FALSE
#define BIND_apr_pool_userdata_setn_FUNCTION FALSE
#define BIND_apr_proc_create_FUNCTION FALSE
#define BIND_apr_proc_detach_FUNCTION TRUE
#define BIND_apr_proc_fork_FUNCTION TRUE
#define BIND_apr_proc_kill_FUNCTION TRUE
#define BIND_apr_proc_mutex_child_init_FUNCTION FALSE
#define BIND_apr_proc_mutex_cleanup_FUNCTION FALSE
#define BIND_apr_proc_mutex_create_FUNCTION FALSE
#define BIND_apr_proc_mutex_defname_FUNCTION TRUE
#define BIND_apr_proc_mutex_destroy_FUNCTION TRUE
#define BIND_apr_proc_mutex_lock_FUNCTION TRUE
#define BIND_apr_proc_mutex_lockfile_FUNCTION TRUE
#define BIND_apr_proc_mutex_name_FUNCTION TRUE
#define BIND_apr_proc_mutex_trylock_FUNCTION TRUE
#define BIND_apr_proc_mutex_unlock_FUNCTION TRUE
#define BIND_apr_proc_other_child_alert_FUNCTION TRUE
#define BIND_apr_proc_other_child_refresh_FUNCTION TRUE
#define BIND_apr_proc_other_child_refresh_all_FUNCTION TRUE
#define BIND_apr_proc_other_child_register_FUNCTION FALSE
#define BIND_apr_proc_other_child_unregister_FUNCTION FALSE
#define BIND_apr_proc_wait_FUNCTION FALSE
#define BIND_apr_proc_wait_all_procs_FUNCTION FALSE
#define BIND_apr_procattr_addrspace_set_FUNCTION TRUE
#define BIND_apr_procattr_child_err_set_FUNCTION TRUE
#define BIND_apr_procattr_child_errfn_set_FUNCTION FALSE
#define BIND_apr_procattr_child_in_set_FUNCTION TRUE
#define BIND_apr_procattr_child_out_set_FUNCTION TRUE
#define BIND_apr_procattr_cmdtype_set_FUNCTION TRUE
#define BIND_apr_procattr_create_FUNCTION FALSE
#define BIND_apr_procattr_detach_set_FUNCTION TRUE
#define BIND_apr_procattr_dir_set_FUNCTION TRUE
#define BIND_apr_procattr_error_check_set_FUNCTION TRUE
#define BIND_apr_procattr_group_set_FUNCTION TRUE
#define BIND_apr_procattr_io_set_FUNCTION TRUE
#define BIND_apr_procattr_limit_set_FUNCTION FALSE
#define BIND_apr_procattr_user_set_FUNCTION TRUE
#define BIND_apr_psprintf_FUNCTION FALSE
#define BIND_apr_pstrcat_FUNCTION FALSE
#define BIND_apr_pstrcatv_FUNCTION FALSE
#define BIND_apr_pstrdup_FUNCTION FALSE
#define BIND_apr_pstrmemdup_FUNCTION FALSE
#define BIND_apr_pstrndup_FUNCTION FALSE
#define BIND_apr_pvsprintf_FUNCTION FALSE
#define BIND_apr_rfc822_date_FUNCTION FALSE
#define BIND_apr_setup_signal_thread_FUNCTION TRUE
#define BIND_apr_signal_FUNCTION FALSE
#define BIND_apr_signal_block_FUNCTION TRUE
#define BIND_apr_signal_description_get_FUNCTION TRUE
#define BIND_apr_signal_init_FUNCTION TRUE
#define BIND_apr_signal_thread_FUNCTION FALSE
#define BIND_apr_signal_unblock_FUNCTION TRUE
#define BIND_apr_sleep_FUNCTION FALSE
#define BIND_apr_snprintf_FUNCTION FALSE
#define BIND_apr_sockaddr_equal_FUNCTION TRUE
#define BIND_apr_sockaddr_info_get_FUNCTION FALSE
#define BIND_apr_sockaddr_ip_get_FUNCTION FALSE
#define BIND_apr_sockaddr_ip_getbuf_FUNCTION FALSE
#define BIND_apr_socket_accept_FUNCTION FALSE
#define BIND_apr_socket_addr_get_FUNCTION FALSE
#define BIND_apr_socket_atmark_FUNCTION FALSE
#define BIND_apr_socket_atreadeof_FUNCTION FALSE
#define BIND_apr_socket_bind_FUNCTION TRUE
#define BIND_apr_socket_close_FUNCTION TRUE
#define BIND_apr_socket_connect_FUNCTION TRUE
#define BIND_apr_socket_create_FUNCTION FALSE
#define BIND_apr_socket_data_get_FUNCTION FALSE
#define BIND_apr_socket_data_set_FUNCTION FALSE
#define BIND_apr_socket_listen_FUNCTION TRUE
#define BIND_apr_socket_opt_get_FUNCTION FALSE
#define BIND_apr_socket_opt_set_FUNCTION TRUE
#define BIND_apr_socket_protocol_get_FUNCTION FALSE
#define BIND_apr_socket_recv_FUNCTION FALSE
#define BIND_apr_socket_recvfrom_FUNCTION FALSE
#define BIND_apr_socket_send_FUNCTION FALSE
#define BIND_apr_socket_sendfile_FUNCTION FALSE
#define BIND_apr_socket_sendto_FUNCTION FALSE
#define BIND_apr_socket_sendv_FUNCTION FALSE
#define BIND_apr_socket_shutdown_FUNCTION TRUE
#define BIND_apr_socket_timeout_get_FUNCTION FALSE
#define BIND_apr_socket_timeout_set_FUNCTION FALSE
#define BIND_apr_socket_type_get_FUNCTION FALSE
#define BIND_apr_stat_FUNCTION TRUE
#define BIND_apr_strerror_FUNCTION FALSE
#define BIND_apr_strfsize_FUNCTION FALSE
#define BIND_apr_strftime_FUNCTION FALSE
#define BIND_apr_strnatcasecmp_FUNCTION TRUE
#define BIND_apr_strnatcmp_FUNCTION TRUE
#define BIND_apr_strtoff_FUNCTION FALSE
#define BIND_apr_strtoi64_FUNCTION FALSE
#define BIND_apr_strtok_FUNCTION FALSE
#define BIND_apr_temp_dir_get_FUNCTION FALSE
#define BIND_apr_terminate_FUNCTION TRUE
#define BIND_apr_terminate2_FUNCTION TRUE
#define BIND_apr_thread_create_FUNCTION FALSE
#define BIND_apr_thread_data_get_FUNCTION FALSE
#define BIND_apr_thread_data_set_FUNCTION FALSE
#define BIND_apr_thread_detach_FUNCTION TRUE
#define BIND_apr_thread_exit_FUNCTION TRUE
#define BIND_apr_thread_join_FUNCTION FALSE
#define BIND_apr_thread_once_FUNCTION FALSE
#define BIND_apr_thread_once_init_FUNCTION FALSE
#define BIND_apr_thread_yield_FUNCTION TRUE
#define BIND_apr_threadattr_create_FUNCTION FALSE
#define BIND_apr_threadattr_detach_get_FUNCTION TRUE
#define BIND_apr_threadattr_detach_set_FUNCTION TRUE
#define BIND_apr_threadattr_guardsize_set_FUNCTION TRUE
#define BIND_apr_threadattr_stacksize_set_FUNCTION TRUE
#define BIND_apr_threadkey_data_get_FUNCTION FALSE
#define BIND_apr_threadkey_data_set_FUNCTION FALSE
#define BIND_apr_threadkey_private_create_FUNCTION FALSE
#define BIND_apr_threadkey_private_delete_FUNCTION TRUE
#define BIND_apr_threadkey_private_get_FUNCTION FALSE
#define BIND_apr_threadkey_private_set_FUNCTION FALSE
#define BIND_apr_time_ansi_put_FUNCTION FALSE
#define BIND_apr_time_clock_hires_FUNCTION TRUE
#define BIND_apr_time_exp_get_FUNCTION FALSE
#define BIND_apr_time_exp_gmt_FUNCTION FALSE
#define BIND_apr_time_exp_gmt_get_FUNCTION FALSE
#define BIND_apr_time_exp_lt_FUNCTION FALSE
#define BIND_apr_time_exp_tz_FUNCTION FALSE
#define BIND_apr_time_now_FUNCTION FALSE
#define BIND_apr_tokenize_to_argv_FUNCTION FALSE
#define BIND_apr_vsnprintf_FUNCTION FALSE
#endif
