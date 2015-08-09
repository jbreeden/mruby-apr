ENV = Object.new

class << ENV
  def [](key)
    err, value = ::APR.apr_env_get(key, pool)
    if err != 0
      nil
    else
      value
    end
  end

  def []=(key, value)
    err = ::APR.apr_env_set(key, value, pool)
    ::APR.raise_apr_errno(err)
    value
  end

  def delete(key)
    value = self[key]
    ::APR.apr_env_delete(key, pool)
    value
  end

  def pool
    unless @pool
      err, env_pool = ::APR.apr_pool_create(nil)
      @pool = env_pool
    end
    @pool
  end
end
