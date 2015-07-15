def via_cruby(cmd)
  puts "Spawn via CRuby:"
  File.open('sandbox/shell.rb', 'w') do |f|
    f.puts "system %q[#{cmd}]"
  end
  if APR::OS == 'Windows'
    pid = spawn "C:/Ruby22/bin/ruby.exe", 'sandbox/shell.rb'
  else
    pid = spawn "/usr/bin/ruby", 'sandbox/shell.rb'
  end
  Process.wait(pid)
rescue Exception => ex
  puts ex
end

def as_program(cmd)
  puts "Spawn as PROGRAM:"
  err, pool = APR.apr_pool_create(nil)
  err, proc_attr = APR.apr_procattr_create pool

  err = APR.apr_procattr_cmdtype_set proc_attr, APR::AprCmdtypeE::APR_PROGRAM_PATH

  argv = nil
  if APR::OS == 'Windows'
    argv = ["cmd.exe", '/C', cmd]
  else
    argv = ["/bin/sh", '-c', cmd]
  end
  err, process = APR.apr_proc_create argv[0], argv, nil, proc_attr, pool
  APR.raise_apr_errno(err)

  err, exitcode, exitwhy = APR.apr_proc_wait process, APR::AprWaitHowE::APR_WAIT
  exitcode == 0
rescue Exception => ex
  puts ex
end

def as_shellcmd_unified(cmd)
  puts "Spawn as SHELLCMD (unified):"
  err, pool = APR.apr_pool_create(nil)
  err, proc_attr = APR.apr_procattr_create pool

  err = APR.apr_procattr_cmdtype_set proc_attr, APR::AprCmdtypeE::APR_SHELLCMD_ENV
  err, argv = APR.apr_tokenize_to_argv cmd, pool

  #puts "Tokenized argv: #{argv}"

  unless APR::OS == "Windows"
    argv = argv.map { |a|
      if a.include?(' ') || a.include?("\t")
        "\"#{a}\""
      else
        a
      end
    }
  end

  puts "Quoted argv: #{argv}"

  err, process = APR.apr_proc_create argv[0], [cmd], nil, proc_attr, pool
  APR.raise_apr_errno(err)
  err, exitcode, exitwhy = APR.apr_proc_wait process, APR::AprWaitHowE::APR_WAIT
  exitcode == 0

rescue Exception => ex
  puts ex
end

def as_shellcmd_tokenized(cmd)
  puts "Spawn as SHELLCMD (Tokenized):"
  err, pool = APR.apr_pool_create(nil)
  err, proc_attr = APR.apr_procattr_create pool

  err = APR.apr_procattr_cmdtype_set proc_attr, APR::AprCmdtypeE::APR_SHELLCMD_ENV
  err, argv = APR.apr_tokenize_to_argv cmd, pool

  #puts "Tokenized argv: #{argv}"

  unless APR::OS == "Windows"
    argv = argv.map { |a|
      if a.include?(' ') || a.include?("\t")
        "\"#{a}\""
      else
        a
      end
    }
  end

  puts "Quoted argv: #{argv}"

  err, process = APR.apr_proc_create argv[0], argv, nil, proc_attr, pool
  APR.raise_apr_errno(err)
  err, exitcode, exitwhy = APR.apr_proc_wait process, APR::AprWaitHowE::APR_WAIT
  exitcode == 0
rescue Exception => ex
  puts ex
end

def shell(cmd)
  via_cruby(cmd)
  as_program(cmd)
  #as_shellcmd_unified(cmd)
  as_shellcmd_tokenized(cmd)
end

def test(cmd)
  puts cmd
  puts ('-' * cmd.length)
  puts
  shell(cmd)
  puts
end

# See: http://rxr.whitequark.org/mri/source/win32/win32.c#099

# Simple test
#test %q[echo 1]
# Reving up with quotes
test %q[ruby -e "puts(2)"]
# Nesting quotes, escaped from the shell
test %q[ruby -e "puts \"3\""]
# Testing for shell interpretation of the command line
test %q[ruby -r English -e "puts $INPUT_RECORD_SEPARATOR.length"]
# Single quote in double quotes
test %q[ruby -e "puts '3'.class"]
# Double quotes in single quotes
test %q[ruby -e 'puts "3".class']
