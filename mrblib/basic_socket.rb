class BasicSocket < IO

  # BasicSocket Subclass Contract
  # -----------------------------

  # A subclass of BasicSocket must provide the following instance variables:
  # - @apr_socket: An APR::Socket instance

  def initialize
    # Sockets always open in duplex mode.
    # When the client calls `close`, `close_read`, or `close_write`
    # these values will be overwritten.
    @can_read = true
    @can_write = true
  end

  # IO Subclass Contract Implementation
  # -----------------------------------

  def assert_can_read
    raise IOError.new("Not open for reading") unless @can_read
  end

  def assert_can_write
    raise IOError.new("Not open for writing") unless @can_write
  end

  def read(length=nil)
    assert_can_read

    msg = ""

    if length
      err, msg = APR::apr_socket_recv(@apr_socket, length)
      APR::raise_apr_errno(err, ignore: APR::APR_EOF)
    else
      err = nil
      msg = ""
      while err != APR::APR_EOF
        err, part = APR::apr_socket_recv(@apr_socket, 100)
        APR::raise_apr_errno(err, ignore: APR::APR_EOF)
        msg += part
      end
    end

    if length.nil?
      # should be "" if nothing was read (EOF hit)
      msg
    elsif length == 0
      # Per ruby documents, return "" on length == 0
      ""
    else
      # length was provided non-zero, so return nil if nothing read
      msg == "" ? nil : msg
    end
  end

  def write(str)
    assert_can_write

    # Todo: check for socket connection
    str = str.to_s unless str.class == String
    err, bytes_sent = APR::apr_socket_send(@apr_socket, str, str.length)
    APR.raise_apr_errno(err)
    bytes_sent
  end

  def eof?
    err, at_eof = APR::apr_socket_atreadeof(@apr_socket)
    APR.raise_apr_errno(err)
    at_eof
  end

  # Semi-Private Utility Methods
  # -----------------------

  module Util
    def self.to_apr_address_family(af)
      case af
      when Socket::AF_INET, :INET, :AF_INET, 'INET', 'AF_INET'
        APR::APR_INET
      when Socket::AF_INET6, :INET6, :AF_INET6, 'INET6', 'AF_INET6'
        APR::APR_INET6
      else
        raise SocketError("Unrecognized socket type: #{af}")
      end
    end

    def self.to_apr_socket_type(st)
      case st
      when :STREAM, :SOCK_STREAM, 'STREAM', 'SOCK_STREAM'
        APR::SOCK_STREAM
      when :DGRAM, :SOCK_DGRAM, 'DGRAM', 'SOCK_DGRAM'
        APR::SOCK_DGRAM
      when :RAW, :SOCK_RAW, 'RAW', 'SOCK_RAW'
        APR::SOCK_RAW
      when :SEQPACKET, :SOCK_SEQPACKET, 'SEQPACKET', 'SOCK_SEQPACKET'
        APR::SOCK_SEQPACKET
      when :RDM, :SOCK_RDM, 'RDM', 'SOCK_RDM'
        APR::SOCK_RDM
      else
        raise SocketError("Unrecognized socket type: #{st}")
      end
    end

    def self.address_family_to_s(af)
      case af
      when Socket::AF_APPLETALK
        'AF_APPLETALK'
      when Socket::AF_CCITT
        'AF_CCITT'
      when Socket::AF_CHAOS
        'AF_CHAOS'
      when Socket::AF_CNT
        'AF_CNT'
      when Socket::AF_COIP
        'AF_COIP'
      when Socket::AF_DATAKIT
        'AF_DATAKIT'
      when Socket::AF_DLI
        'AF_DLI'
      when Socket::AF_E164
        'AF_E164'
      when Socket::AF_ECMA
        'AF_ECMA'
      when Socket::AF_HYLINK
        'AF_HYLINK'
      when Socket::AF_IMPLINK
        'AF_IMPLINK'
      when Socket::AF_INET
        'AF_INET'
      when Socket::AF_INET6
        'AF_INET6'
      when Socket::AF_IPX
        'AF_IPX'
      when Socket::AF_ISDN
        'AF_ISDN'
      when Socket::AF_ISO
        'AF_ISO'
      when Socket::AF_LAT
        'AF_LAT'
      when Socket::AF_LINK
        'AF_LINK'
      when Socket::AF_LOCAL
        'AF_LOCAL'
      when Socket::AF_MAX
        'AF_MAX'
      when Socket::AF_NATM
        'AF_NATM'
      when Socket::AF_NDRV
        'AF_NDRV'
      when Socket::AF_NETBIOS
        'AF_NETBIOS'
      when Socket::AF_NS
        'AF_NS'
      when Socket::AF_OSI
        'AF_OSI'
      when Socket::AF_PPP
        'AF_PPP'
      when Socket::AF_PUP
        'AF_PUP'
      when Socket::AF_ROUTE
        'AF_ROUTE'
      when Socket::AF_SIP
        'AF_SIP'
      when Socket::AF_SNA
        'AF_SNA'
      when Socket::AF_SYSTEM
        'AF_SYSTEM'
      when Socket::AF_UNIX
        'AF_UNIX'
      when Socket::AF_UNSPEC
        'AF_UNSPEC'
      else
        raise ArgumentError.new("Unrecognized APR address family constant")
      end
    end
  end

  # Instance Methods
  # ----------------

  def close
    @can_read = false
    @can_write = false
    err = APR::apr_socket_close(@apr_socket)
    APR.raise_apr_errno(err)
  end

  def close_read
    @can_read = false
    err = APR::apr_socket_shutdown(@apr_socket, APR::ShutdownHow::APR_SHUTDOWN_READ)
    APR.raise_apr_errno(err)
  end

  def close_write
    @can_write = false
    err = APR::apr_socket_shutdown(@apr_socket, APR::ShutdownHow::APR_SHUTDOWN_WRITE)
    APR.raise_apr_errno(err)
  end

  # def connect_address
  #
  # end
  #
  # def do_not_reverse_lookup
  #
  # end
  #
  # def do_not_reverse_lookup=
  #
  # end
  #
  # def getpeereid
  #
  # end
  #
  # def getpeername
  #
  # end
  #
  # def getsockname
  #
  # end
  #
  # def getsockopt
  #
  # end
  #
  # def local_address
  #
  # end

  def recv(maxlen)
    err, msg = APR.apr_socket_recv(@apr_socket, maxlen)
    APR.raise_apr_errno(err, ignore: APR::APR_EOF)
    msg
  end

  # def recv_nonblock
  #
  # end
  #
  # def recvmsg
  #
  # end
  #
  # def recvmsg_nonblock
  #
  # end
  #
  # def remote_address
  #
  # end

  def send(msg)
    assert_can_write

    msg = msg.to_s unless msg.class == String
    err, bytes_sent = APR::apr_socket_send(@apr_socket, msg, msg.length)
    APR.raise_apr_errno(err)
    bytes_sent
  end

  # def sendmsg
  #
  # end
  #
  # def sendmsg_nonblock
  #
  # end
  #
  # def setsockopt
  #
  # end

  def shutdown(how = Socket::SHUT_RDWR)
    case how
    when Socket::SHUT_RDWR, :RDWR, :SHUT_RDWR, 'RDWR', 'SHUT_RDWR'
      close_read
      close_write
    when Socket::SHUT_RD, :RD, :SHUT_RD, 'RD', 'SHUT_RD'
      close_read
    when Socket::SHUT_WR, :WR, :SHUT_WR, 'WR', 'SHUT_WR'
      close_write
    else
      raise SocketError.new("Unrecognized `how` parameter to BasicSocket#shutdown: #{how}")
    end
  end
end
