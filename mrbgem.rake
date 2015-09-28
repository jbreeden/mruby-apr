# TODO:
# Most of the configuration here should be done on the gem spec,
# not on the global conf object.

require 'pp'

$APR_GEM_DIR = File.dirname(__FILE__)
$APR_HOME = ENV['APR_HOME'] || "#{$APR_GEM_DIR}/../../apr_source/apr-1.5.2/build"

def configure_mruby_apr_win(spec)
  # apr.h is generated specially for each platform when building APR
  # I'm putting these generated headers into "#{$APR_GEM_DIR}/include/apr/PLATFORM"
  # (In this case, PLATFORM == win)
  spec.cc.include_paths << "#{$APR_HOME}"
  spec.cxx.include_paths << "#{$APR_HOME}"

  # Pre-built libraries are held under "#{$APR_GEM_DIR}/lib/PLATFORM"
  spec.linker.library_paths << "#{$APR_HOME}/x64/Release"

  spec.linker.libraries << "apr-1"
  spec.linker.libraries << "Rpcrt4"
  spec.linker.libraries << "Ws2_32"
  spec.linker.libraries << "Advapi32"
  spec.linker.libraries << "Shell32"
  spec.linker.libraries << "Mswsock"
end

def configure_mruby_apr_lin(spec)
  unless Dir.exists? '/usr/local/apr'
    puts 'Expected to find APR installed in /usr/local.'
    puts 'To install APR, download the source and run `configure && make && sudo make install`'
    raise 'APR not installed'
  end
  apr_include_dir = `/usr/local/apr/bin/apr-1-config --includes`.sub('-I', '').strip
  spec.cc.include_paths << apr_include_dir
  spec.cxx.include_paths << apr_include_dir
  spec.linker.library_paths << '/usr/local/apr/lib'
  spec.linker.libraries = spec.linker.libraries.concat `/usr/local/apr/bin/apr-1-config --libs`.
    split(' ').
    map { |flag|
      flag.gsub(/^-l/, '').strip
    }
  spec.linker.flags_before_libraries << '/usr/local/apr/lib/libapr-1.a'
end

def configure_mruby_apr(spec)
  # Common include path (all platforms)
  spec.cc.include_paths << "#{$APR_GEM_DIR}/include/apr"
  spec.cxx.include_paths << "#{$APR_GEM_DIR}/include/apr"

  # This gem is only setup to build with the static apr lib.
  # To use the static lib, you need to declare this preprocessor macro.
  spec.cc.defines << "APR_DECLARE_STATIC"
  spec.cxx.defines << "APR_DECLARE_STATIC"

  if ENV['OS'] =~ /windows/i
    configure_mruby_apr_win(spec)
  else
    configure_mruby_apr_lin(spec)
  end
end

MRuby::Gem::Specification.new('mruby-apr') do |spec|
  spec.license = 'Apache Version 2'
  spec.author  = 'Jared Breeden'
  spec.summary = 'Bindings to the APR libraries'
  spec.add_dependency('mruby-regexp-pcre', ">= 0.0.0", github: "iij/mruby-regexp-pcre")

  spec.rbfiles = [
    "io.rb",
    "file.rb",
    "basic_socket.rb",
    "ipsocket.rb",
    "tcpsocket.rb",
    "tcpserver.rb",
    "udpsocket.rb",
    "socket_error.rb"
  ].map { |name| "#{$APR_GEM_DIR}/mrblib/#{name}" }
    .concat(Dir["#{$APR_GEM_DIR}/mrblib/**/*.rb"])
    .map { |f| File.expand_path(f) }
    .uniq

  # Need the gem init file to be compiled last, so push it on the end of the file list
  gem_init_rb = File.expand_path("#{spec.dir}/mrblib/mrb_apr_gem_init.rb")
  spec.rbfiles.delete(gem_init_rb)
  spec.rbfiles.push(gem_init_rb)

  configure_mruby_apr(spec)

  unless /windows/i =~ ENV['OS']
    spec.cc.flags << [ '-std=c11' ]
    spec.cxx.flags << [ '-std=c++11' ]
  end
end
