require 'mruby_bindings'

namespace :bindings do
  desc 'Extract type information from C files'
  task :scrape do
    File.delete('declarations.json') if File.exists?('declarations.json')
    
    inc = `apr-1-config --includedir`.strip
    headers = %W[
      #{inc}/apr.h
      #{inc}/apr_env.h
      #{inc}/apr_errno.h
      #{inc}/apr_file_info.h
      #{inc}/apr_file_io.h
      #{inc}/apr_fnmatch.h
      #{inc}/apr_general.h
      #{inc}/apr_global_mutex.h
      #{inc}/apr_network_io.h
      #{inc}/apr_pools.h
      #{inc}/apr_proc_mutex.h
      #{inc}/apr_signal.h
      #{inc}/apr_strings.h
      #{inc}/apr_time.h
      #{inc}/apr_want.h
    ]
    
    if headers.length == 0
      $stderr.puts 'No headers defined. Please update rakelib/mruby-bindings.rake'
      exit 1
    end
    
    headers.each do |header|
      sh "clang2json #{header} >> declarations.json"
    end
  end
  
  desc 'Inspect all declarations in an interactive Pry shell (require pry gem)'
  task :pry do
    require 'pry'
    MRubyBindings.read_declarations("declarations.json") do |lib|
      binding.pry
    end
  end

  desc 'Generate bindings'
  task :generate do
    cmd = ['mrbind generate']
    cmd << '-input declarations.json'
    cmd << '-module APR'
    cmd << '-gem mruby-apr'
    cmd << '-load mruby-bindings.in/ctypes.rb' if File.exists?('mruby-bindings.in/ctypes.rb')
    cmd << '-load mruby-bindings.in/fn_types.rb' if File.exists?('mruby-bindings.in/fn_types.rb')
    cmd << '-load mruby-bindings.in/macro_types.rb' if File.exists?('mruby-bindings.in/macro_types.rb')
    cmd << '-includes mruby-bindings.in/includes.h' if File.exists?('mruby-bindings.in/includes.h')
    cmd << '-output bindings'
    cmd << '-force'
    sh cmd.join(' ')
  end
  
  desc "Merge generated code into mrbgem"
  task :merge do
    sh "mrbind merge -from bindings -to ."
  end
  
  namespace :merge do
    desc "Merge generated code from src folder"
    task :src do
      sh "mrbind merge -from bindings -to . src"
    end
    
    desc "Merge generated code from include folder"
    task :include do
      sh "mrbind merge -from bindings -to . include"
    end
    
    desc "Merge generated code from mrblib folder"
    task :mrblib do
      sh "mrbind merge -from bindings -to . mrblib"
    end
  end
  
  desc 'Regenerate functions & classes headers'
  task :'enable-functions' do
    sh 'mrbind enable-functions -m APR -g mruby-apr -o .'
  end
  
  task :fn_count do
    sh "cat include/mruby_APR_functions.h | egrep 'TRUE|FALSE' | wc -l"
  end

  task :bound_fns do
    sh "cat include/mruby_APR_functions.h | egrep 'TRUE'"
  end

  task :bound_fn_count do
    sh "cat include/mruby_APR_functions.h | egrep 'TRUE' | wc -l"
  end

  task :unbound_fns do
    sh "cat include/mruby_APR_functions.h | egrep 'FALSE'"
  end

  task :unbound_fn_count do
    sh "cat include/mruby_APR_functions.h | egrep 'FALSE' | wc -l"
  end
end
