# This should be run with CRuby for testing TCP server sockets

require 'socket'

client = TCPSocket.new 'localhost', 8889
client.print "socket data"
client.close
