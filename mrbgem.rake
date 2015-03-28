def configure_mruby_apr(conf)
  gem_dir = File.dirname(__FILE__)

  # Common include path (all platforms)
  conf.cc.include_paths << "#{gem_dir}/include/apr"
  conf.cxx.include_paths << "#{gem_dir}/include/apr"

  # This gem is only setup to build with the static apr lib.
  # To use the static lib, you need to declare this preprocessor macro.
  conf.cc.defines << "APR_DECLARE_STATIC"
  conf.cxx.defines << "APR_DECLARE_STATIC"

  if ENV['OS'] =~ /windows/i
    # apr.h is generated specially for each platform when building APR
    # I'm putting these generated headers into "#{gem_dir}/include/apr/PLATFORM"
    # (In this case, PLATFORM == win)
    conf.cc.include_paths << "#{gem_dir}/include/apr/win"
    conf.cxx.include_paths << "#{gem_dir}/include/apr/win"

    # Pre-built libraries are held under "#{gem_dir}/lib/PLATFORM"
    conf.linker.library_paths << "#{gem_dir}/lib/win"

    # I've appended the selected C runtime APR was built with onto the lib file name
    conf.linker.libraries << "apr-1_md"
    conf.linker.libraries << "Advapi32"
    conf.linker.libraries << "Shell32"
  else
    raise "No mruby-apr build settings configured for this platform"
  end
end

MRuby::Gem::Specification.new('mruby-apr') do |spec|
  spec.license = 'Apache Version 2'
  spec.author  = 'Jared Breeden'
  spec.summary = 'Bindings to the APR libraries'

  # TODO: Add dependency on mruby-regexp-pcre (or compatible)
  # TODO: Add dependency on mruby-errno
end
