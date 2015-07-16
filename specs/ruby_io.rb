TestFixture.new('Ruby API: IO') do
  describe 'IO.pipe' do
    it 'Creates a pair of File objects to be used as the read & write ends of the pipe' do
      r, w = IO.pipe
      w.write('my message')
      w.close
      msg = r.read(10)
      r.close
      assert(msg == 'my message')
    end
  end

  describe 'IO.popen([env,] cmd, mode="r" [, opt])' do
    it 'Runs the specified command as a subprocess, returning an IO like object with a pid member' do
      pipe = IO.popen('exit 4')
      pipe.close
      assert($?.exitstatus == 4)
    end

    it 'Connects the returned IO-like object to child\'s stdin for mode "r"' do
      pipe = IO.popen('ruby -e "puts 123"', "r")
      msg = pipe.read(3)
      assert(msg == '123')
      pipe.close
    end

    it 'Connects the returned IO-like object to child\'s stdout for mode "w"' do
      pipe = IO.popen('ruby -e "gets; exit 2"', "w")
      pipe.puts('123')
      pipe.close
      assert($?.exitstatus == 2)
    end

    it 'Connects the returned IO-like object to child\'s stdin & stdout for mode "r+"' do
      pipe = IO.popen('ruby -e "l = gets; puts l"', "r+")
      pipe.puts('123')
      read = pipe.gets
      assert(read.strip == "123")
      pipe.close
    end

    it 'Sends EOF when the output pipe is closed' do
      pipe = IO.popen('ruby -e "data = STDIN.read; puts data"', "r+")
      pipe.write('123')
      pipe.close_write
      read = pipe.read
      assert(read.strip == "123")
      pipe.close
    end

    it 'Yeilds the IO like object instead of returning it if a block is provided' do
      pending
    end

    it 'Handles \\r\\n & \\n line endings in text mode' do
      pending
    end
  end

  describe 'IO.pipe' do
    it 'Both pipes are closed & freed after each is garbage collected' do
      # Right now you have to close them manually.
      # Going to have to track, on the C side, when each is GC'ed
      # Need to do the same for ordinary files
      pending
    end
  end
end
