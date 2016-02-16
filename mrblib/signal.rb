# Only here to allow RubySpec to run (for now).
module Signal
  def self.trap(*args)
    $stderr.puts "WARNING: Signal handling is not supported. Registered callbacks will not be called."
  end
end
