class UDPSocket < IPSocket
  def initialize(address_family = Socket::AF_INET, pool = nil)
    super()

    # Wrapper semantics, for internal use only
    if (address_family.class == APR::AprSocketT)
      @apr_socket = address_family
      @pool = pool
      return
    end

    address_family = BasicSocket::Util.to_apr_address_family(address_family)

    err, @pool = APR::apr_pool_create(nil)
    APR.raise_apr_errno(err)

    err, @apr_socket = APR.apr_socket_create(address_family, APR::SOCK_DGRAM, APR::APR_PROTO_UDP, @pool)
    APR.raise_apr_errno(err)
  end

  def bind(host, port)
    err, @apr_local_addrinfo = APR.apr_sockaddr_info_get(host, APR::APR_INET, port, 0, @pool)
    APR.raise_apr_errno(err)

    err = APR.apr_socket_bind(@apr_socket, @apr_local_addrinfo)
    APR.raise_apr_errno(err)
  end

  def connect(host, port)
    err, @apr_remote_addrinfo = APR.apr_sockaddr_info_get(host, APR::APR_INET, port, 0, @pool)
    APR.raise_apr_errno(err)

    err = APR.apr_socket_connect(@apr_socket, @apr_remote_addrinfo)
    APR.raise_apr_errno(err)
  end
end
