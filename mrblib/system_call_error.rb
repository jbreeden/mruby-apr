class SystemCallError < StandardError
  def initialize(msg, errno = nil)
    super(msg)
    @errno = errno
  end

  def errno
    @errno
  end
end

# A mock Errno module, mostly for API compatability until
# real Errno support is added.
module Errno
  def self.const_missing(const)
    errClass = Class.new(SystemCallError)
    errClass.class_eval do
      class << self
        attr_reader :name
      end
      @name = const.to_s
      def initialize(msg)
        super("#{self.class.name} msg")
      end
    end
    Errno.const_set(const, errClass)
    errClass
  end
end
