APR.apr_initialize

proc { # Creates a local scope (like IIFE in JavsScript)
  err, std_streams_pool = APR.apr_pool_create(nil)
  err, $stdin = APR.apr_file_open_flags_stdin(APR::APR_FOPEN_READ, std_streams_pool)
  err, $stdout = APR.apr_file_open_flags_stdout(APR::APR_FOPEN_WRITE, std_streams_pool)
  err, $stderr = APR.apr_file_open_flags_stderr(APR::APR_FOPEN_WRITE, std_streams_pool)
}[]

STDIN = $stdin
STDOUT = $stdout
STDERR = $stderr
