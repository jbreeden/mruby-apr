TestFixture.new('Ruby API: Process') do
  file_for_writing = "#{$GEM_DIR}/sandbox/file_for_writing.txt"

  describe 'Process::spawn' do
    it 'Spawns a shell command if given a string' do
      APR.with_pool do |pool|
        # If there was a shell involved, the command executed below would be
        # interpretted, and the environment variable expanded. So, if we
        # correctly bypass the shall, the variable name should be printed
        # instead of the variable's value.
        APR.apr_env_set("I_SHOULD_NOT_BE_PRINTED", "I should be printed", pool)

        cmd = nil
        if APR::OS != 'Windows'
          cmd = 'ruby -e "puts \"$I_SHOULD_NOT_BE_PRINTED\""'
        else
          cmd = 'ruby -e "puts \"%I_SHOULD_NOT_BE_PRINTED%\""'
        end

        r, w = IO.pipe
        pid = Process.spawn(*cmd, out: w)
        w.close

        assert(r.read.strip == 'I should be printed')
        r.close
      end
    end

    it 'Interprets shell command arguments correctly' do
      capture_out = proc do |cmd|
        r, w = IO.pipe
        pid = Process.spawn(*cmd, out: w)
        w.close
        result = r.read
        r.close
        result.strip
      end

      # Reving up with quotes
      assert '1' == capture_out[%q[ruby -e "puts(1)"]]
      # Single quote in double quotes
      assert 'String' == capture_out[%q[ruby -e "puts '2'.class"]]
      # Double quotes in single quotes
      assert 'String' == capture_out[%q[ruby -e 'puts "3".class']]
      # Nesting quotes, escaped from the shell (%q does not require escaping \)
      assert 'String' == capture_out[%q[ruby -e "puts \"4\".class"]]
      # Command combinations
      assert 'FAILED'  != capture_out[ %q[ ruby -e "exit 0" || ruby -e "puts 'FAILED'"  ]]
      assert 'SUCCESS' == capture_out[ %q[ ruby -e "exit 0" && ruby -e "puts 'SUCCESS'" ]]
      assert 'SUCCESS' == capture_out[ %q[ ruby -e "exit 1" || ruby -e "puts 'SUCCESS'" ]]
      assert 'FAILED'  != capture_out[ %q[ ruby -e "exit 1" && ruby -e "puts 'FAILED'"  ]]
    end

    it 'Spawns a program, with no shell, if given argv as multiple args' do
      APR.with_pool do |pool|
        # If there was a shell involved, the command executed below would be
        # interpretted, and the environment variable expanded. So, if we
        # correctly bypass the shall, the variable name should be printed
        # instead of the variable's value.
        APR.apr_env_set("I_SHOULD_BE_PRINTED", "I should not", pool)

        cmd = nil
        if APR::OS != 'Windows'
          cmd = ['ruby', '-e', 'puts "$I_SHOULD_BE_PRINTED"']
        else
          cmd = ['ruby', '-e', 'puts "%I_SHOULD_BE_PRINTED%"']
        end

        r, w = IO.pipe
        pid = Process.spawn(*cmd, out: w)
        w.close

        assert(r.read.include? 'I_SHOULD_BE_PRINTED')
      end
    end

    it 'Supports redirecting in, out, & err streams to/from a Pipe\'s created by IO.pipe' do
      r, w = IO.pipe
      Process.spawn('ruby -e "puts \'my message\'"', out: w)
      w.close # Close in parent so we can get EOF
      msg = r.read
      r.close # Close read when finished so resources are cleaned up
      # Stripping because windows might end with \r\n, and unix with \n.
      assert (msg.strip == "my message")
    end

    it 'Supports redirecting to ordinary file objects' do
      out_file = File.open(file_for_writing, 'w')
      pid = Process.spawn("echo my message", out: out_file)
      out_file.close
      Process.wait(pid)
      read = nil
      File.open(file_for_writing) do |f|
        read = f.read
      end
      assert(read.strip == "my message")
    end
  end

  describe 'Process::wait' do
    it 'Sets $? based on the exit status of the indicated process' do
      pending
    end

    it 'If called twice on the same PID, does the right thing... which is...?' do
      pending
    end
  end
end
