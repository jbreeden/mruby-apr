load 'fixture.rb'

begin
  Object.const_get(:MRUBY_VERSION)
rescue
  # Running on MRI
  require 'socket'
end

TestFixture.new('Ruby API: UDPSocket') do
  describe "UDPSocket::read(length=nil)" do
    it "Reads at most length bytes from a bound UDPSocket" do
      server = UDPSocket.new()
      server.bind('localhost', 9999)

      msg = 'client to server'
      io = IO.popen("ruby", 'w')
      io.write(<<-EOS)
        require 'socket'
        client = UDPSocket.new()
        client.connect('localhost', 9999)
        client.write('#{msg}')
        client.close
      EOS
      io.close

      result = server.read(msg.length)
      assert (result == msg)
      server.close
    end

    it "Reads consecutive packets as a stream" do
      server = UDPSocket.new()
      server.bind('localhost', 9999)

      io = IO.popen("ruby", 'w')
      io.write(<<-EOS)
        require 'socket'

        client = UDPSocket.new()
        client.connect('localhost', 9999)
        client.write('one')
        client.close

        client2 = UDPSocket.new()
        client2.connect('localhost', 9999)
        client2.write('two')
        client2.close
      EOS
      io.close

      result = server.read(6)
      assert (result == 'onetwo')
      server.close
    end
  end

  describe "UDPSocket::recv(maxlen)" do
    it "Reads at most maxlen bytes from a bound UDPSocket" do
      server = UDPSocket.new()
      server.bind('localhost', 9999)

      msg = 'client to server'
      io = IO.popen("ruby", 'w')
      io.write(<<-EOS)
        require 'socket'
        client = UDPSocket.new()
        client.connect('localhost', 9999)
        client.write('#{msg}')
        client.close
      EOS
      io.close

      result = server.recv(msg.length)
      assert (result == msg)
      server.close
    end
  end

  describe "UDPSocket::recvfrom(maxlen)" do
    it "Reads from a bound UDPSocket, returning the sender's address" do
      server = UDPSocket.new()
      server.bind('localhost', 9999)

      msg = 'client to server'
      io = IO.popen("ruby", 'w')
      io.write(<<-EOS)
        require 'socket'
        client = UDPSocket.new()
        client.connect('localhost', 9999)
        client.write('#{msg}')
        client.close
      EOS
      io.close

      received, addrinfo = server.recvfrom(msg.length)
      assert (received == msg)
      assert (addrinfo[0] == 'AF_INET')
      assert (addrinfo[2] == 'localhost')
      server.close
    end
  end

  describe "UDPSocket::write(str)" do
    it "Writes the given string to a connected UDPSocket" do
      msg = 'client to server'
      io = IO.popen("ruby", 'w')
      io.write(<<-EOS)
        require 'socket'
        client = UDPSocket.new()
        client.bind('localhost', 9999)
        client.connect('localhost', 9998)
        client.write client.read(#{msg.length}).reverse
        client.close
      EOS
      io.close_write

      `sleep 1`

      server = UDPSocket.new()
      server.bind('localhost', 9998)
      server.connect('localhost', 9999)
      server.write(msg)
      assert (server.read(msg.length).reverse == msg)
    end
  end
end
