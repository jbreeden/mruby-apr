module Process
  # No real privates in mruby, so use a sub module for some sort of hiding
  module Util

    # Some nasty details below involving proc creation on windows.
    # For more info, see:
    # - http://blogs.msdn.com/b/twistylittlepassagesallalike/archive/2011/04/23/everyone-quotes-arguments-the-wrong-way.aspx

    # Only for arguments that are (or will be, by apr) wrapped in double quotes
    def self.double_backslashes_preceding_quotes(arg)
      new_arg = ""
      preceding_quote = true # It's wrapped, so the trailing quotes are preceding a quote
      arg.reverse.each_char do |c|
        if preceding_quote
          if c == '\\'
            new_arg << '\\\\'
          else
            new_arg << c
            preceding_quote = false unless c == '"'
          end
        else
          new_arg << c
          preceding_quote = true if c == '"'
        end
      end
      new_arg.reverse
    end

    def self.quote_windows_argv(argv)
      new_argv = [argv[0]]
      if argv.length > 1
        argv[1..(argv.length - 1)].each do |arg|
          if arg.include? ' '
            # APR does it's own quoting if there's a space in the arg
            # (But it's extremely naive, and doesn't escape contained quotes, so we have to)
            escaped = double_backslashes_preceding_quotes(arg).gsub('"', '\"')
            new_argv.push escaped
          elsif arg.include? '"'
            # To escape a double quote on windows, you have to be in a double quote,
            # so we escape and wrap
            escaped = double_backslashes_preceding_quotes(arg).gsub('"', '\"')
            new_argv.push "\"#{escaped}\""
          else
            new_argv.push(arg)
          end
        end
      end
      new_argv
    end

    def self.parse_spawn_args(*command, pool)
      env = nil
      options = nil;

      if command.length == 0
        raise ArgumentError.new('Wrong number of arguments (0 for 1+)')
      end

      if command[0].class == Hash
        env = command.shift
      end

      if command.last.class == Hash
        options = command.pop
      end

      if command.length == 1 && command[0].class == String
        # WORKAROUND:
        #   Encountering lots of problems when using APR_SHELLCMD directly.
        #   It attempts to quote arguments in ways that appear unneeded.
        #   Additionally, the quoting is often wrong.
        #   So, using APR_PROGRAM_PATH, we can construct the shell command ourselves
        #   to get around this limitation.
        argv = nil
        if APR::OS == 'Windows'
          # User is aware of shell processing, so they'll escape any quotes themselves.
          # Note that this goes directly through CreateProcess, so any cmd significant
          # metacharacters are not interpreted until the child proc (ie there is no outter
          # cmd shell to worry about)
          argv = ["cmd.exe", '/C', command[0]]
        else
          argv = ["sh", '-c', command[0]]
        end

        { env: env, argv: argv, options: options, cmd_type: APR::AprCmdtypeE::APR_PROGRAM_PATH }
      elsif command[0].class == Array
        if command[0].length != 2
          raise ArgumentError.new('wrong first argument')
        end
        argv = [command[0][0], command[0][1]].concat(command[1..(command.length)])
        if APR::OS == 'Windows'
          argv = quote_windows_argv(argv)
        end
        { env: env, argv: argv, options: options, cmd_type: APR::AprCmdtypeE::APR_PROGRAM_PATH }
      else

        # Unix is simple... the args are passed in an actual vector, so just pass them along
        argv = command
        if APR::OS == 'Windows'
          # Windows is a horrible beast... only accepting a command line that is later processed
          # into an argv for the target program by CommandLineToArgvW (that is, if the program
          # doesn't use the command line directly). So we have to quote the args correctly
          # to allow the constructed command line string to be deconstructed back into the
          # original argument vector.
          # (Note that the construction of the commandline string is done with APR itself)
          argv = quote_windows_argv(command)
        end
        { env: env, argv: argv, options: options, cmd_type: APR::AprCmdtypeE::APR_PROGRAM_PATH }
      end
    end
  end

  def self.spawn(*command)
    # Going to mutate this, don't want to mess with client's copy
    command = command.dup

    APR.with_pool do |pool|
      err, proc_attr = APR.apr_procattr_create pool
      args = Util.parse_spawn_args(*command, pool)
      env = args[:env]
      argv = args[:argv]
      options = args[:options]
      cmd_type = args[:cmd_type]

      APR.apr_procattr_cmdtype_set proc_attr, cmd_type

      # TODO: Configure environment variables from env hash

      if options
        if options[:in]
          # Pass nil as the parent file, or else APR tries to create a new pipe
          # between the two files. If a pipe is required for the child process,
          # it will have been created by IO.pipe already by the client.
          err = APR.apr_procattr_child_in_set proc_attr, options[:in].native_file, nil
          APR.raise_apr_errno(err)
        end
        if options[:out]
          err = APR.apr_procattr_child_out_set proc_attr, options[:out].native_file, nil
          APR.raise_apr_errno(err)
        end
        if options[:err]
          err = APR.apr_procattr_child_err_set proc_attr, options[:err].native_file, nil
          APR.raise_apr_errno(err)
        end
      else
        APR.apr_procattr_io_set(proc_attr, APR::APR_NO_PIPE, APR::APR_NO_PIPE, APR::APR_NO_PIPE)
      end

      err, process = APR.apr_proc_create argv[0], argv, nil, proc_attr, pool
      APR.raise_apr_errno(err)

      process.pid
    end
  end

  def self.wait(pid)
    proc = APR.apr_proc_from_pid(pid)
    err, exit_code, exit_why = APR.apr_proc_wait(proc, APR::AprWaitHowE::APR_WAIT)
    APR.raise_apr_errno(err, ignore: [APR::APR_CHILD_NOTDONE, APR::APR_CHILD_DONE])
    $? = Process::Status.new(pid, exit_code, exit_why)
    return pid
  end
end
