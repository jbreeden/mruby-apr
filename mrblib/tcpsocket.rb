class TCPSocket < IPSocket
  def initialize(remote_host, remote_port, local_host=nil, local_port=nil)
    super()

    # Wrapper semantics, for internal use only
    if (remote_host.class == APR::Socket)
      @apr_socket = remote_host
      @pool = remote_port
      err, @apr_remote_addrinfo = APR::apr_socket_addr_get(APR::Interface::APR_REMOTE, @apr_socket)
      APR::raise_apr_errno(err)
      err, @remote_host = APR::apr_sockaddr_ip_get(@apr_remote_addrinfo)
      APR::raise_apr_errno(err)
      return
    end

    err, @pool = APR::apr_pool_create(nil)
    APR.raise_apr_errno(err)

    @remote_host = remote_host
    @remote_port = remote_port
    @local_host = local_host
    @local_port = local_port

    err, @apr_remote_addrinfo = APR.apr_sockaddr_info_get(remote_host, APR::APR_INET, remote_port, 0, @pool)
    APR.raise_apr_errno(err)

    if local_host && local_port
      err, @apr_local_addrinfo = APR.apr_sockaddr_info_get(local_host, APR::APR_INET, local_port, 0, @pool)
    end

    err, @apr_socket = APR.apr_socket_create(APR::APR_INET, APR::SOCK_STREAM, APR::APR_PROTO_TCP, @pool)
    APR.raise_apr_errno(err)

    err = APR.apr_socket_connect(@apr_socket, @apr_remote_addrinfo)
    APR.raise_apr_errno(err)

    if @apr_local_addrinfo
      err = APR.apr_socket_bind(@apr_socket, @apr_local_addrinfo)
      APR.raise_apr_errno(err)
    end
  end
end
