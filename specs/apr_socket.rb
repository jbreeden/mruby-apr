load 'fixture.rb'

TestFixture.new('APR API: Sockets') do
  err, @pool = APR.pool_create(nil)

  def run_server
    @server_pid = spawn "ruby ./helpers/tcp_server.rb"
    `sleep 1`
  end

  def wait_for_server
    Process.wait(@server_pid)
  end

  def run_client
    @client_pid = spawn "sleep 1 && ruby ./helpers/tcp_client.rb"
  end

  def wait_for_client
    Process.wait(@client_pid)
  end

  describe 'APR.socket_connect(socket: Socket, addr: Sockaddr)' do
    it 'Connects a client socket to a server' do
      run_server

      #                                            Host         Family         Port  Flags
      err, server_addr = APR.sockaddr_info_get "localhost", APR::APR_INET, 8888, 0, @pool
      APR.raise_apr_errno(err)

      err, client = APR.socket_create(APR::APR_INET, APR::SOCK_STREAM, APR::APR_PROTO_TCP, @pool)
      APR.raise_apr_errno(err)

      err = APR.socket_connect(client, server_addr)
      APR.raise_apr_errno(err)

      err, buf = APR.socket_recv(client, 100)
      APR.raise_apr_errno(err)

      assert (buf == 'socket data')
    end
  end

  describe 'APR.socket_atreadeof(socket: Socket)' do
    it 'Returns [APR::APR_SUCCESS, true] when the read buffer is empty and the socket has been closed by the peer' do
      run_server

      #                                            Host         Family         Port  Flags
      err, server_addr = APR.sockaddr_info_get "localhost", APR::APR_INET, 8888, 0, @pool
      APR.raise_apr_errno(err)

      err, client = APR.socket_create(APR::APR_INET, APR::SOCK_STREAM, APR::APR_PROTO_TCP, @pool)
      APR.raise_apr_errno(err)

      err = APR.socket_connect(client, server_addr)
      APR.raise_apr_errno(err)

      eof_check = APR.socket_atreadeof(client)
      assert (eof_check[0] == APR::APR_SUCCESS && eof_check[1] == false)
      err, buf = APR.socket_recv(client, 100)
      APR.raise_apr_errno(err)

      wait_for_server
      eof_check = APR.socket_atreadeof(client)
      assert (eof_check[0] == APR::APR_SUCCESS && eof_check[1] == true)
    end
  end

  describe 'APR.socket_send(socket, message, length)' do
    it 'Returns a APR::APR_EOF when the connection is closed' do
      err, server_addr = APR.sockaddr_info_get "www.google.com", APR::APR_INET, 80,   0,    @pool
      APR.raise_apr_errno(err)

      err, client = APR.socket_create(APR::APR_INET, APR::SOCK_STREAM, APR::APR_PROTO_TCP, @pool)
      APR.raise_apr_errno(err)

      err = APR.socket_connect(client, server_addr)
      APR.raise_apr_errno(err)

      msg = "GET http://www.google.com/ HTTP/1.1\nConnection: close\n\n"
      APR.socket_send(client, msg, msg.length)

      err = 0
      while err == 0
        err, buf = APR.socket_recv(client, 1000)
        APR.raise_apr_errno(err, ignore: APR::APR_EOF)
      end

      assert (err == APR::APR_EOF)
    end
  end

  describe 'APR.socket_bind(socket, addr)' do
    it 'Binds a server socket to an address' do
      #                                            Host         Family         Port  Flags
      err, server_addr = APR.sockaddr_info_get "localhost", APR::APR_INET, 8889, 0, @pool
      APR.raise_apr_errno(err)

      err, server = APR.socket_create(APR::APR_INET, APR::SOCK_STREAM, APR::APR_PROTO_TCP, @pool)
      APR.raise_apr_errno(err)

      err = APR.socket_bind(server, server_addr)
      APR.raise_apr_errno(err)

      run_client

      APR.socket_listen(server, 100)
      err, client = APR.socket_accept(server, @pool)
      APR.raise_apr_errno(err)

      err, msg = APR.socket_recv(client, 1000)
      APR.raise_apr_errno(err, ignore: APR::APR_EOF)

      assert (msg == 'socket data')
    end
  end
end
