load 'fixture.rb'

begin
  Object.const_get(:MRUBY_VERSION)
rescue
  # Running on MRI
  require 'socket'
end

TestFixture.new('Ruby API: TCPSocket, & TCPServer') do
  describe "TCPSocket::new(remote_host, remote_port, local_host=nil, local_port=nil)" do
    it "Creates a connected TCP socket when given remote host & port" do
      s = TCPSocket.new("www.google.com", 80)
      s.write("GET http://www.google.com/ HTTP/1.1\nConnection: close\n\n")
      msg = s.read
      assert (msg =~ /200 OK/)
    end
  end

  describe "TCPSocket#write(str)" do
    # Tested by TCPSocket::new
    it "Writes the given str to the socket"
  end

  describe "TCPSocket#read(len=nil)" do
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

  describe "TCPSocket#close_read" do
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

  describe "TCPSocket#close_write" do
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

  describe "TCPSocket#close" do
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

  describe "TCPSocket#eof?" do
    it "Returns true if the socket has been closed by the peer" do
      s = TCPSocket.new("www.google.com", 80)
      s.write("GET http://www.google.com/ HTTP/1.1\nConnection: close\n\n")
      assert(!s.eof?)
      s.read
      assert(s.eof?)
    end
  end

  describe "TCPSocket#gets" do
    it "Read from the socket one line at a time" do
      s = TCPSocket.new("www.google.com", 80)
      s.write("GET http://www.google.com/ HTTP/1.1\nConnection: close\n\n")
      assert (s.gets =~ /200 OK\s+$/)
      hit_content_type = false
      while line = s.gets
        hit_content_type = true if line =~ /^Content-Type:/
      end
      assert(hit_content_type)
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
