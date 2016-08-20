# Features provided by mruby-apr that would normally need to be `require`d
# (This allows us to run some CRuby code without pulling out `require` calls,
#  we can simply return false for these requires.)
$BUILTIN_FEATURES = %w[
  find
  fileutils
  forwardable
  observer
  ostruct
  pathname
  pp
  rbconfig
  shellwords
  socket
  tmpdir
]

# Features that have been loaded by `require`
$LOADED_FEATURES = []

# Load path
$: = []
$LOAD_PATH = $:

# Input record separator
$/ = "\n"

# Output record separator
$\

# Output field separator
$, = nil

# This is a stub, just so that RubySpec doesn't throw up.
module RbConfig
  CONFIG = Hash.new do |h, k|
    if k == 'bindir'
      # TODO: WINDOWS SUPPORT?
      h['bindir'] = File.dirname(`which mruby`.strip)
    else
      raise "RbConfig[#{k} : #{k.class}]"
    end
  end
  
  CONFIG['EXEEXT'] = APR::OS == 'Windows' ? '.exe' : ''
  CONFIG['RUBY_INSTALL_NAME'] = 'mruby'
  CONFIG['host_os'] = APR::OS == 'Windows' ? 'mswin' : 'unix'
end

# This is a stub, just so that RubySpec doesn't throw up.
class SystemExit < StandardError
end
