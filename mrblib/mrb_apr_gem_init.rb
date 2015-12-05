proc { # Creates a local scope (like IIFE in JavaScript)
  err, std_streams_pool = APR.apr_pool_create(nil)
  err, stdin = APR.apr_file_open_flags_stdin(APR::APR_FOPEN_READ, std_streams_pool)
  $stdin = File.new(stdin, "r", std_streams_pool) if err == APR::APR_SUCCESS
  err, stdout = APR.apr_file_open_flags_stdout(APR::APR_FOPEN_WRITE, std_streams_pool)
  $stdout = File.new(stdout, "w", std_streams_pool) if err == APR::APR_SUCCESS
  err, stderr = APR.apr_file_open_flags_stderr(APR::APR_FOPEN_WRITE, std_streams_pool)
  $stderr = File.new(stderr, "w", std_streams_pool) if err == APR::APR_SUCCESS
}[]

STDIN = $stdin
STDOUT = $stdout
STDERR = $stderr

# The default `puts` in mruby isn't quite like MRI, so lets replace it.
module Kernel
  def puts(*a); $stdout.puts(*a); end
end
