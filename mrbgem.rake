$APR_GEM_DIR = File.dirname(__FILE__)
$APR_HOME = ENV['APR_HOME']

def configure_mruby_apr_win(spec)
  # TODO: This default is here because of this mrbgem's origins in rubium.
  #       Should update rubium's build_config to set ENV['APR_HOME'] instead.
  apr_home = ($APR_HOME && Dir.exists?($APR_HOME)) ? $APR_HOME : "#{$APR_GEM_DIR}/../../apr_source/apr-1.5.2/build"
  unless Dir.exists?(apr_home)
    $stderr.puts "On Windows, APR_HOME env variable should be set to libapr build directory."
    raise 'APR not found'
  end

  spec.cc.include_paths << apr_home
  spec.cxx.include_paths << apr_home

  # Pre-built libraries are held under "#{$APR_GEM_DIR}/lib/PLATFORM"
  spec.linker.library_paths << "#{apr_home}/x64/Release"

  spec.linker.libraries << "apr-1"
  spec.linker.libraries << "Rpcrt4"
  spec.linker.libraries << "Ws2_32"
  spec.linker.libraries << "Advapi32"
  spec.linker.libraries << "Shell32"
  spec.linker.libraries << "Mswsock"
end

def configure_mruby_apr_lin(spec)
  unless Dir.exists? '/usr/local/apr'
    $stderr.puts 'Expected to find APR installed in /usr/local.'
    $stderr.puts 'To install APR, download the source and run `configure && make && sudo make install`'
    raise 'APR not found'
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

  # Gather cflags from various locations and check for MRB_INT64
  # TODO: There should be a better way to communicate this requirement
  #       to the user.
  set_flags = spec.build.cc.flags.dup.concat((ENV['CFLAGS'] || '').split).flatten
  
  if !(/true/i =~ ENV['MRUBY_APR_IGNORE_INT_SIZE']) && set_flags.select { |f| f =~ /-D.*MRB_INT64/i }.empty?
    $stderr.puts <<-EOS
ERROR:
  mruby-apr requires 64 bit integers. 
  Please define the MRB_INT64 macro before building.
Options:
  1. Set `spec.cc.flags << '-DMRB_INT64'` in build_config.rb
  2. Invoke rake as `rake CLFAGS=-DMRB_INT64 ...` when building mruby
Workaround:
  If you think you're seeing this message in error, 
  set ENV['MRUBY_APR_IGNORE_INT_SIZE'] = 'true' to bypass
  this check (and consider submitting a bug report!)
EOS
  raise "MRuby-APR requires MRB_INT64 to be set"
  end

  spec.rbfiles = %w[
    mruby_backport_utils
    io
    file
    dir
    glob
    basic_socket
    ipsocket
    tcpsocket
    tcpserver
    udpsocket
    socket_error
    kernel
  ].map { |name| "#{$APR_GEM_DIR}/mrblib/#{name}.rb" }
    .concat(Dir["#{$APR_GEM_DIR}/mrblib/**/*.rb"])
    .map { |f| File.expand_path(f) }
    .uniq

  # Need the gem init file to be compiled last, so push it on the end of the file list
  gem_init_rb = File.expand_path("#{spec.dir}/mrblib/mrb_apr_gem_init.rb")
  spec.rbfiles.delete(gem_init_rb)
  spec.rbfiles.push(gem_init_rb)

  configure_mruby_apr(spec)
end
