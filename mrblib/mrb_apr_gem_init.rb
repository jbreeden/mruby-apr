proc { # Creates a local scope (like IIFE in JavaScript)
  err, stdin_pool = APR.pool_create(nil)
  err, stdin = APR.file_open_flags_stdin(APR::APR_FOPEN_READ, stdin_pool)
  $stdin = File.new(stdin, "r", stdin_pool) if err == APR::APR_SUCCESS
  
  err, stdout_pool = APR.pool_create(nil)
  err, stdout = APR.file_open_flags_stdout(APR::APR_FOPEN_WRITE, stdout_pool)
  $stdout = File.new(stdout, "w", stdout_pool) if err == APR::APR_SUCCESS
  
  err, stderr_pool = APR.pool_create(nil)
  err, stderr = APR.file_open_flags_stderr(APR::APR_FOPEN_WRITE, stderr_pool)
  $stderr = File.new(stderr, "w", stderr_pool) if err == APR::APR_SUCCESS
}[]

STDIN = $stdin
STDOUT = $stdout
STDERR = $stderr

module Kernel
  def puts(*a); $stdout.puts(*a); end
  def print(*a); $stdout.print(*a); end
  def gets(*a); $stdin.gets(*a); end
end
