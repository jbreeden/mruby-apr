class TCPServer < TCPSocket
  def initialize(hostname, port = nil)
    if port == nil
      port = hostname
      hostname = nil
    end

    err, @pool = APR::apr_pool_create(nil)
    APR.raise_apr_errno(err)

    @local_host = hostname
    @local_port = port

    err, @apr_local_addrinfo = APR.apr_sockaddr_info_get(hostname, APR::APR_INET, port, 0, @pool)
    APR.raise_apr_errno(err)
    err, @apr_socket = APR.apr_socket_create(APR::APR_INET, APR::SOCK_STREAM, APR::APR_PROTO_TCP, @pool)
    APR.raise_apr_errno(err)

    err = APR.apr_socket_bind(@apr_socket, @apr_local_addrinfo)
    APR.raise_apr_errno(err)
  end

  def accept
    err, client = APR::apr_socket_accept(@apr_socket, @pool)
    APR::raise_apr_errno(err)
    TCPSocket.new(client, @pool)
  end

  # def accept_nonblock
  # end

  def listen(backlog)
    err = APR::apr_socket_listen(@apr_socket, backlog)
    APR::raise_apr_errno(err)
  end

  # def sysaccept
  # end
end
