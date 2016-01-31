load 'fixture.rb'

TestFixture.new('APR API: Processes') do
  err, @pool = APR.pool_create(nil)

  describe 'APR.proc_create(command: String, argv: Array<String>, env: Array<String>, proc_attr: Procattr, pool: Pool): [errno: Fixnum, proc: Proc]' do
    it 'Can run a shell command and redirect output to a file' do
      err, proc_attr = APR.procattr_create @pool
      assert(err == 0)

      # WORKAROUND:
      #   Encountering lots of problems when using APR_SHELLCMD directly.
      #   It attempts to quote arguments in ways that appear unneeded.
      #   Additionally, the quoting is often wrong.
      #   So, using APR_PROGRAM_PATH, we can construct the shell command ourselves
      #   to get around this limitation.
      err = APR.procattr_cmdtype_set proc_attr, APR::Cmdtype::APR_PROGRAM_PATH
      assert(err == 0)

      err, file = APR.file_open "sandbox/echo_out.txt",
        APR::APR_FOPEN_CREATE | APR::APR_FOPEN_WRITE | APR::APR_FOPEN_TRUNCATE,
        APR::APR_FPROT_OS_DEFAULT,
        @pool
      assert(err == 0)

      err = APR.procattr_child_out_set proc_attr, file, nil
      assert(err == 0)

      argv = nil
      if APR::OS == 'Windows'
        argv = ["cmd.exe", '/C', "ruby -e \"puts 'some string'\""]
      else
        argv = ["sh", '-c', "ruby -e \"puts 'some string'\""]
      end

      err, process = APR.proc_create argv[0], argv, nil, proc_attr, @pool
      assert(err == 0)

      err, exitcode, exitwhy = APR.proc_wait process, APR::WaitHow::APR_WAIT

      APR.file_close(file)

      err, file = APR.file_open "sandbox/echo_out.txt", APR::APR_FOPEN_READ, 0, @pool
      assert(err == 0)

      err, str = APR.file_read file, 100
      assert(err == 0)
      # strip newline from echo before compare
      assert (str.strip == "some string")
      APR.file_close(file)
    end

    it 'Can run a shell command and pipe output to parent via APR.file_pipe_create' do
      err, proc_attr = APR.procattr_create @pool
      assert(err == 0)

      err = APR.procattr_cmdtype_set proc_attr, APR::Cmdtype::APR_SHELLCMD_ENV
      assert(err == 0)

      err, readEnd, writeEnd = APR.file_pipe_create @pool

      # Passing pipe ends:                            child,    parent
      err = APR.procattr_child_out_set proc_attr, writeEnd, readEnd
      assert(err == 0)

      err, argv = APR.tokenize_to_argv "echo this string of args", @pool
      assert(argv.length == 5)
      assert(err == 0)

      err, process = APR.proc_create "echo", argv, nil, proc_attr, @pool
      assert(err == 0)

      rr, str = APR.file_read readEnd, 100
      assert(err == 0)
      # strip newline from echo before compare
      assert (str.strip == "this string of args")

      APR.file_close(readEnd)

      err, exitcode, exitwhy = APR.proc_wait process, APR::WaitHow::APR_WAIT
    end
  end

  describe "APR.procattr_io_set(procattr: Procattr, in: Fixnum, out: Fixnum, err: Fixnum): errno: Fixnum" do
    it 'Can automatically create pipes between the parent and child processes (for std in, out, & err)' do
      err, proc_attr = APR.procattr_create @pool
      assert(err == 0)

      err = APR.procattr_cmdtype_set proc_attr, APR::Cmdtype::APR_SHELLCMD_ENV
      assert(err == 0)

      #                                  in                out                  err
      APR.procattr_io_set proc_attr, APR::APR_NO_PIPE, APR::APR_FULL_BLOCK, APR::APR_NO_PIPE

      err, argv = APR.tokenize_to_argv "echo this string of args", @pool
      assert(argv.length == 5)
      assert(err == 0)

      err, process = APR.proc_create "echo", argv, nil, proc_attr, @pool
      assert(err == 0)

      err, str = APR.file_read process.out, 100
      assert(err == 0)
      # strip newline from echo before compare
      assert (str.strip == "this string of args")

      APR.file_close(process.out)

      err, exitcode, exitwhy = APR.proc_wait process, APR::WaitHow::APR_WAIT
    end
  end

end
