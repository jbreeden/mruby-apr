# This file holds utilities for backporting code to mruby.
# The main goal is to make the smallest modifications to the
# source, and to keep as much code as possible. This should
# make future modifications easier, as the changes should be
# straightforward to follow, and mostly mechanical.
#
# For example, the `def_with_kwargs` class macro provides a
# way to tranform a method definition using keyword arguments
# to mruby-compatible syntax by modifying _only_ the method
# signature line.
#
# The `on_mruby?` predicate allows `#ifdef` style design-time
# (when classes are being loaded) mechanism for deciding how to
# implement a feature. Leaving the existing code in place, rather
# than modifying it for MRuby directly, eases the task of inspecting
# the code to verify the port is correct.
#
# Once a module has been ported, and is functioning correctly
# (ideally with good test coverage), these patches may be removed
# in the process of optimizing an mruby-specific implementation of
# the module. This should be done last in order to minimze the
# introduction of new bugs before the mruby port is even running
# and testable. From there, it's red-green-refactor.

class Object
  def on_mruby?
    Object.const_defined?(:MRUBY_VERSION)
  end
end

class Module
  def def_with_kwargs(name, kwargs, &implementation)
    self.define_method(name) do |*args, &block|
      overrides = {}
      overrides = args.pop if args.last.kind_of?(Hash)
      
      kwargs.keys.each { |k| args.push(overrides[k] || kwargs[k]) }
      
      unless self.respond_to?("#{name}_implementation".to_sym)
        if self.class == Class
          self.class.define_method("#{name}_implementation", &implementation)
        else
          (class << self; self; end).define_method("#{name}_implementation", &implementation)
        end
      end
      
      self.send("#{name}_implementation", *args, &block)
    end
  end
end
