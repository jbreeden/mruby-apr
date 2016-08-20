class SystemCallError < StandardError
  class << self
    alias _new new
  end
  
  def self.new(msg, errno)
    if (subclass = Errno.lookup(errno))
      subclass.new(msg)
    else
      self._new(msg, errno)
    end
  end
  
  def initialize(msg, errno)
    if self.class == ::SystemCallError
      super("Unkown Error (#{errno}) - #{msg}")
    else
      super("#{self.class.name} (#{errno}) - #{msg}")
    end
    @errno = errno
  end
  
  def inspect
    "#<#{self.class.name}>: #{message}"
  end

  def errno
    @errno
  end
end

module Errno
  @lookup = {}
  
  def self.define(name, errno)
    errClass = Class.new(SystemCallError)
    
    errClass.define_singleton_method(:new) do |*args|
      self._new(*args)
    end
    
    errClass.define_singleton_method(:name) do
      @name ||= name.to_s
    end
    
    errClass.define_method(:initialize) do |msg|
      super(msg, errno)
    end
    
    errClass.define_method(:inspect) do |msg|
      "#<#{self.class.name}>: #{self.message}"
    end
    
    Errno.const_set(name, errClass)
    @lookup[errno] = errClass
    errClass
  end
  
  def self.lookup(errno)
    @lookup[errno]
  end
  
  APR::Errno.constants(false).each do |const|
    ::Errno.define(const, APR::Errno.const_get(const))
  end
end
