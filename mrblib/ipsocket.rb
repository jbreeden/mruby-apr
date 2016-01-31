class IPSocket < BasicSocket
  def recvfrom(maxlen)
    err, addr, msg = APR.socket_recvfrom(@apr_socket, 0, maxlen)
    APR.raise_apr_errno(err, ignore: APR::APR_EOF)
    err, ip = APR.sockaddr_ip_get(addr)
    APR.raise_apr_errno(err)
    err, hostname = APR.getnameinfo(addr)
    APR.raise_apr_errno(err)
    [msg, [BasicSocket::Util.address_family_to_s(addr.family), addr.port, hostname, ip]]
  end
end
