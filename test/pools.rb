$stdin.gets

pools = (0..1000).map { err, pool = APR.apr_pool_create(nil); pool }

$stdin.gets

pools = nil

$stdin.gets

GC.start

$stdin.gets
