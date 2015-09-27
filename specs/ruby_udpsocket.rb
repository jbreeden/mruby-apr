load 'fixture.rb'

begin
  Object.const_get(:MRUBY_VERSION)
rescue
  # Running on MRI
  require 'socket'
end

TestFixture.new('Ruby API: UDPSocket & UDPServer') do
  describe "UDPSocket::read(length=nil)" do
    it "Reads at most length bytes from a bound UDPSocket" do
      server = UDPSocket.new()
      server.bind('localhost', 9999)

      msg = 'client to server'
      io = IO.popen("ruby", 'w')
      io.write(<<-EOS)
        require 'socket'
        sleep 0.2
        client = UDPSocket.new()
        sent = client.send('#{msg}', 0, 'localhost', 9999)
        client.close
      EOS
      io.close

      result = server.read(msg.length)
      assert (result == msg)
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
        new_msg = client.read(#{msg.length}).reverse
        client.write new_msg
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
