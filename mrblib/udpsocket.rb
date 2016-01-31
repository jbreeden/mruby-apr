class UDPSocket < IPSocket
  def initialize(address_family = Socket::AF_INET, pool = nil)
    super()

    # Wrapper semantics, for internal use only
    if (address_family.class == APR::Socket)
      @apr_socket = address_family
      @pool = pool
      return
    end

    address_family = BasicSocket::Util.to_apr_address_family(address_family)

    err, @pool = APR.pool_create(nil)
    APR.raise_apr_errno(err)

    err, @apr_socket = APR.socket_create(address_family, APR::SOCK_DGRAM, APR::APR_PROTO_UDP, @pool)
    APR.raise_apr_errno(err)
  end

  # Base Class Overrides
  # --------------------

  def read(limit=nil)
    assert_can_read

    # Handle limit == 0 case up front. Now all calls
    # delegated to super `read` will return nil at EOF
    return "" if limit == 0

    # The default read for basic socket delegates to apr_socket_read,
    # which returns after a UDP packet is finished. In Ruby style, we should
    # instead treat consecutive UDP packets as a stream when `read` is called.
    result = nil
    bytes_read = 0
    loop {
      part = super(limit && limit - bytes_read)
      break if part.nil?
      result = result.to_s + part
      bytes_read += part.length
      break if bytes_read >= limit
    }

    result
  end

  # Instance Methods
  # ----------------

  def bind(host, port)
    err, @apr_local_addrinfo = APR.sockaddr_info_get(host, APR::APR_INET, port, 0, @pool)
    APR.raise_apr_errno(err)

    err = APR.socket_bind(@apr_socket, @apr_local_addrinfo)
    APR.raise_apr_errno(err)
  end

  def connect(host, port)
    err, @apr_remote_addrinfo = APR.sockaddr_info_get(host, APR::APR_INET, port, 0, @pool)
    APR.raise_apr_errno(err)

    err = APR.socket_connect(@apr_socket, @apr_remote_addrinfo)
    APR.raise_apr_errno(err)
  end
end
