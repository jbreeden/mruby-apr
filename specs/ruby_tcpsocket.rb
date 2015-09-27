load 'fixture.rb'

begin
  Object.const_get(:MRUBY_VERSION)
rescue
  # Running on MRI
  require 'socket'
end

TestFixture.new('Ruby API: BasicSocket, TCPSocket, & TCPServer') do
  describe "TCPSocket::new(remote_host, remote_port, local_host=nil, local_port=nil)" do
    it "Creates a connected TCP socket when given remote host & port" do
      s = TCPSocket.new("www.google.com", 80)
      s.write("GET http://www.google.com/ HTTP/1.1\nConnection: close\n\n")
      msg = s.read
      assert (msg =~ /200 OK/)
    end
  end

  describe "BasicSocket#write(str)" do
    # Tested by TCPSocket::new
    it "Writes the given str to the socket"
  end

  describe "BasicSocket#read(len=nil)" do
    # Tested by TCPSocket::new
    it "Reads from the socket until EOF (when the socket is closed)"

    it "Reads at most len bytes if len is provided" do
      s = TCPSocket.new("www.google.com", 80)
      s.write("GET http://www.google.com/ HTTP/1.1\n\n")
      msg = s.read(100)
      assert (msg =~ /200 OK/ && msg.length == 100)
    end

    it "Returns the empty string after EOF has been encountered, if length is not provided" do
      s = TCPSocket.new("www.google.com", 80)
      s.write("GET http://www.google.com/ HTTP/1.1\nConnection: close\n\n")
      s.read # Read all input
      second_response = s.read # Should be nothing left
      assert (second_response == '')
    end

    it "Returns nil after EOF has been encountered, if length is provided" do
      s = TCPSocket.new("www.google.com", 80)
      s.write("GET http://www.google.com/ HTTP/1.1\nConnection: close\n\n")
      s.read # Read all input
      second_response = s.read(10) # Should be nothing left
      assert (second_response == nil)
    end
  end

  describe "BasicSocket#close_read" do
    # Tested by TCPSocket::new
    it "Closes a socket for reading" do
      exc = nil
      begin
        s = TCPSocket.new("www.google.com", 80)
        s.write("GET http://www.google.com/ HTTP/1.1\n\n")
        s.close_read
        puts s.read(100)
      rescue Exception => e
        exc = e
      end

      assert (exc.class == IOError)
    end
  end

  describe "BasicSocket#close_write" do
    # Tested by TCPSocket::new
    it "Closes a socket for writing" do
      exc = nil
      begin
        s = TCPSocket.new("www.google.com", 80)
        s.close_write
        s.write("GET http://www.google.com/ HTTP/1.1\n\n")
      rescue Exception => e
        exc = e
      end

      assert (exc.class == IOError)
    end
  end

  describe "BasicSocket#close" do
    # Tested by TCPSocket::new
    it "Closes a socket for reading & writing" do
      exc = nil
      s = TCPSocket.new("www.google.com", 80)
      s.close

      begin
        s.write("GET http://www.google.com/ HTTP/1.1\n\n")
      rescue Exception => e
        exc = e
      end
      assert (exc.class == IOError)

      begin
        s.read
      rescue Exception => e
        exc = e
      end
      assert (exc.class == IOError)
    end
  end

  describe "TCPServer::new([hostname], port)" do
    it "Creates a new TCPServer on the given port" do
      server = TCPServer.new('localhost', 9999)
      server.listen(1)

      client = TCPSocket.new('localhost', 9999)
      client.write('client to server')
      client.close

      server_client_handle = server.accept
      result = server_client_handle.read
      assert (result == 'client to server')
    end
  end
end
