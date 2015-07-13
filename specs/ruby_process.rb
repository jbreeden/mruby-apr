TestFixture.new('Ruby API: Process') do
  file_for_writing = "#{$GEM_DIR}/sandbox/file_for_writing.txt"

  describe 'Process::spawn' do
    it 'Spawns a shell command if given a string' do
      pid = Process.spawn 'ruby -e "exit 1"'
      Process.wait(pid)
      assert($?.exitstatus == 1)
    end

    it 'Spawns a program, with no shell, if given argv as multiple args' do
      # This will fail, since without the shell "ruby" should be specified as the full path "/usr/bin/ruby"

      assert_raises(SystemCallError) do
        pid = Process.spawn 'ruby', '-e', '"exit 0"'
        Process.wait(pid)
        assert($?.exitstatus != 0)
      end

      ## TODO: Need to test on Mac again. This throws SystemCall error on Windows, and that seems right
      # pid = Process.spawn 'ruby', '-e', '"exit 0"'
      # Process.wait(pid)
      # assert($?.exitstatus != 0)
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
      Process.wait(pid)
      out_file.close
      read = nil
      File.open(file_for_writing) do |f|
        read = f.read
      end
      assert(read.strip == "my message")
    end

    it 'No longer needs hack for https://bz.apache.org/bugzilla/show_bug.cgi?id=58123' do
      # This pending test is just to track a todo in the source.
      # A workaround has been implemented for a bug in APR.
      # A patch has been submitted. Once fixed, need to search
      # for the URL in the source and remove the workaround.
      pending
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
