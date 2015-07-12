# Using a shared pool means it will not be destroyed until all members have left.
# Each Pipe joins the pool on construction, and leaves when they're closed.
# The effect is that this pool exists until all stdstreams are closed.
# It may be desirable to never destroy this pool so that streams may be reponed.
# At the moment, this isn't a concern, but would be easy to fix if File/IO#reopen
# is implemented.
std_pool = APR::SharedPool.new
err, stdin = APR.apr_file_open_flags_stdin(APR::APR_FOPEN_READ, std_pool.pool)
$stdin = IO::Pipe.new(stdin, 'r', std_pool)
err, stdout = APR.apr_file_open_flags_stdout(APR::APR_FOPEN_WRITE, std_pool.pool)
$stdout = IO::Pipe.new(stdout, 'w', std_pool)
err, stderr = APR.apr_file_open_flags_stderr(APR::APR_FOPEN_WRITE, std_pool.pool)
$stderr = IO::Pipe.new(stderr, 'w', std_pool)

STDIN = $stdin
STDOUT = $stdout
STDERR = $stderr
