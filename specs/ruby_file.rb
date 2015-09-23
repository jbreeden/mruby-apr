load 'fixture.rb'

TestFixture.new('Ruby API: File') do
  sandbox_dir = "#{$GEM_DIR}/sandbox"
  empty_file = "#{$GEM_DIR}/sandbox/empty_file.txt"
  two_line_file = "#{$GEM_DIR}/sandbox/two_line_file.txt"
  file_for_writing = "#{$GEM_DIR}/sandbox/file_for_writing.txt"

  describe 'File::open(filename, mode="r" [, &block])' do
    it 'Returns an open File object, if filename exists' do
      f = File.open(two_line_file)
      assert(f.class == File)
      assert(!f.closed?)
    end

    it 'Raises a SystemCallError if filename does not exist' do
      assert_raises(SystemCallError) do
        File.open('this_path_doesnt_exist')
      end
    end

    it 'If given a block, it is passed the File, and the File is automatically closed when the block terminates' do
      file = nil
      File.open(two_line_file) do |f|
        file = f
        break
      end
      assert(file.closed?)
    end
  end

  describe 'File::absolute_path' do
    it 'Is implemented' do
      pending
    end
  end

  describe 'File::atime' do
    it 'Is implemented' do
      pending
    end
  end

  describe 'File::basename' do
    it 'Is implemented' do
      pending
    end
  end

  ## Not really cross platform. May implement later
  # describe 'File::chmod' do
  #   it 'Is implemented' do
  #     pending
  #   end
  # end
  #
  # describe 'File::chown' do
  #   it 'Is implemented' do
  #     pending
  #   end
  # end

  describe 'File::copy_stream' do
    it 'Is implemented' do
      pending
    end
  end

  describe 'File::ctime' do
    it 'Is implemented' do
      pending
    end
  end

  describe 'File::delete(path[, path]...)' do
    it 'Deletes the file named by the path argument' do
      name = 'sandbox/create_and_delete.txt'
      f = File.open(name, 'w')
      f.close
      assert File.exists?(name)
      File.delete(name)
      assert !File.exists?(name)
    end

    it 'Accepts multiple path parameters and deletes them all' do
      name1 = 'sandbox/create_and_delete1.txt'
      name2 = 'sandbox/create_and_delete2.txt'
      names = [name1, name2]
      names.each do |name|
        f = File.open(name, 'w')
        f.close
        assert File.exists?(name)
      end

      File.delete(*names)

      names.each do |name|
        assert !File.exists?(name)
      end
    end

    it 'Raises a system call error if the file does not exist' do
      assert_raises(SystemCallError) do
        File.delete('sandbox/does_not.exist')
      end
    end
  end

  describe 'File::directory?' do
    it 'Is implemented' do
      pending
    end
  end

  describe 'File::dirname' do
    it 'Is implemented' do
      pending
    end
  end

  describe 'File::exist? | exists?' do
    it 'Returns true if the file exists' do
      assert File.exists?(two_line_file)
      assert File.exist?(two_line_file)
    end

    it 'Returns true if the file exists, even if it\'s a directory' do
      assert File.exists?('.')
      assert File.exist?('.')
    end

    it 'Returns false if the file does not exist' do
      assert !File.exists?('does_not_exist.txt')
      assert !File.exist?('neither_does_this.txt')
    end
  end

  describe 'File::expand_path' do
    it 'Is implemented' do
      pending
    end
  end

  describe 'File::extname' do
    it 'Is implemented' do
      assert(File.extname("test.rb")       == ".rb")
      assert(File.extname("a/b/d/test.rb") == ".rb")
      assert(File.extname("test")          == "")
      assert(File.extname(".profile")      == "")
      assert(File.extname("a\\b\\c\\test.rb") == ".rb")
      assert(File.extname("a\\b\\c.\\test") == "")
      assert(File.extname("a\\b\\c.d\\test") == "")
      assert(File.extname("a\\b\\c.d\\.test") == "")
    end
  end

  describe 'File::file?' do
    it 'Returns true if the given path is a normal file' do
      assert File.file?(empty_file)
      assert !File.file?(sandbox_dir)
    end
  end

  describe 'File::fnmatch' do
    it 'Is implemented' do
      pending
    end
  end

  describe 'File::fnmatch?' do
    it 'Is implemented' do
      pending
    end
  end

  describe 'File::link' do
    it 'Is implemented' do
      pending
    end
  end

  describe 'File::lstat' do
    it 'Is implemented' do
      pending
    end
  end

  describe 'File::mtime' do
    it 'Is implemented' do
      pending
    end
  end

  describe 'File#print(obj, ...)' do
    it "Writes the given objects to the File" do
      File.open(file_for_writing, 'w') do |f|
        f.print('my message')
      end
      result = nil
      File.open(file_for_writing) do |f|
        result = f.read.strip
      end
      assert result.strip == 'my message'
    end

    it "If the output field separator ($,) is nil, nothing is inserted between each object." do
      File.open(file_for_writing, 'w') do |f|
        f.print('my', 'message')
      end
      result = nil
      File.open(file_for_writing) do |f|
        result = f.read.strip
      end
      assert result.strip == 'mymessage'
    end

    it "If the output field separator ($,) is not nil, it will be inserted between each object." do
      original_field_sep = $,
      $, = "\t"
      File.open(file_for_writing, 'w') do |f|
        f.print('my', 'message')
      end
      result = nil
      File.open(file_for_writing) do |f|
        result = f.read.strip
      end
      assert result.strip == "my\tmessage"
      $, = original_field_sep
    end

    it "If the output record separator ($\) is not nil, it will be appended to the output." do
      original_out_record_sep = $\
      $\ = "EOF"
      File.open(file_for_writing, 'w') do |f|
        f.print('my message')
      end
      result = nil
      File.open(file_for_writing) do |f|
        result = f.read.strip
      end
      assert result.strip == "my messageEOF"
      $\ = original_out_record_sep
    end

    it 'Objects that aren’t strings will be converted by calling their to_s method' do
      o = Object.new
      class << o
        def to_s
          'to_s result'
        end
      end
      File.open(file_for_writing, 'w') do |f|
        f.print(o, o)
      end
      result = nil
      File.open(file_for_writing) do |f|
        result = f.read.strip
      end
      assert result.strip == 'to_s resultto_s result'
    end
  end

  describe 'File#<<(obj)' do
    it "Writes obj to ios. obj will be converted to a string using to_s." do
      o = Object.new
      class << o
        def to_s
          'to_s result'
        end
      end
      File.open(file_for_writing, 'w') do |f|
        f << o
      end
      result = nil
      File.open(file_for_writing) do |f|
        result = f.read.strip
      end
      assert result == 'to_s result'
    end
  end

  describe 'File#puts(obj, ...)' do
    it "Writes the given objects to the File, appending the output record separator ($\\) between each item" do
      orig_out_sep = $\
      orig_in_sep = $/
      File.open(file_for_writing, 'w') do |f|
        f.puts 'test'
        $\ = 'END'
        f.puts 'test2'
      end
      read = []
      File.open(file_for_writing, 'r') do |f|
        read.push f.gets
        $/ = 'END'
        read.push f.gets
      end
      $\ = orig_out_sep
      $/ = orig_in_sep
      assert(read[0] == "test\n" && read[1] == "test2END")
    end

    it 'Raises an IOError if the file is not open for writing' do
      assert_raises(IOError) do
        File.open(file_for_writing) do |f|
          f.puts 'test'
        end
      end
    end

    it 'Appends to the file if opened with mode="a"' do
      File.open(file_for_writing, 'w') do |f|
        f.puts 'one line'
        f.puts 'two lines'
      end
      File.open(file_for_writing, 'a') do |f|
        f.puts 'three lines'
      end
      line_count = 0
      File.open(file_for_writing) do |f|
        until f.gets.nil?
          line_count += 1
        end
      end
      assert(line_count == 3)
    end

    it 'Does not append a record separator after any args that already end with a record separator sequence' do
      line = "line with newline \n"
      File.open(file_for_writing, 'w') do |f|
        f.puts line
      end
      read = nil
      File.open(file_for_writing) do |f|
        orig_in_sep = $/
        # Change the input sep so we don't accidentally stop reading
        # before an erroneous double newline, breaking the test
        $/ = "\t"
        read = f.gets(100)
        $/ = orig_in_sep
      end
      assert(read == line)
    end

    it 'If called with any array arguments, flattens the arrays and writes each element on a new line' do
      File.open(file_for_writing ,'w') do |f|
        f.puts [1, 2, [3, 4, [5, 6], 7], 8, [9, 10]], 11, 12, [13, [14, 15]]
      end
      line_count = 0
      File.open(file_for_writing) do |f|
        until f.gets.nil?
          line_count += 1
        end
      end
      assert(line_count == 15)
    end

    it 'If called without arguments, outputs a single record separator' do
      File.open(file_for_writing ,'w') do |f|
        f.puts
      end
      read = nil
      File.open(file_for_writing) do |f|
        orig_in_sep = $/
        $/ = "DNE"
        read = f.gets(100)
        $/ = orig_in_sep
      end
      assert(read == "\n")
    end
  end

  describe 'File#gets | gets(sep=$/) | gets(limit) | gets(sep, limit)' do
    it 'Reads until sep when called as `gets(sep=$/)` (the separator is included in the result)' do
      read = nil
      File.open(two_line_file) do |f|
        read = f.gets
      end
      assert(read.strip == "This file has two lines.")
    end

    it 'Returns "" if limit is 0' do
      read = nil
      File.open(two_line_file) do |f|
        read = f.gets(0)
      end
      assert(read == "")
    end

    it 'Reads at most `limit` bytes when called as `gets(limit)`' do
      read = nil
      File.open(two_line_file) do |f|
        read = f.gets(4)
      end
      assert(read == "This")
    end

    it 'Reads at most `limit` bytes when called as `gets(sep, limit)`' do
      read = nil
      File.open(two_line_file) do |f|
        read = f.gets("\n", 4)
      end
      assert(read == "This")
    end

    it 'Raises an IOError if the stream isn\'t open for reading' do
      assert_raises(IOError) do
        File.open(two_line_file, 'a') do |f|
          read = f.gets
        end
      end
    end

    it 'Returns nil if called at end of file' do
      File.open(two_line_file) do |f|
        assert(f.gets != nil)
        assert(f.gets != nil)
        assert(f.gets.nil?)
      end
    end
  end

  describe 'File#read' do
    it 'Reads length bytes from the file' do
      read = nil
      File.open(two_line_file) do |f|
        read = f.read(4)
      end
      assert(read == 'This')
    end

    it 'If length is omitted or is nil, it reads until EOF' do
      read = nil
      File.open(two_line_file) do |f|
        read = f.read
      end
      # Temporary hack for windows until a pending test for test mode is implemented
      assert(read == "This file has two lines.\nThis is the second line.\n" ||
        read == "This file has two lines.\r\nThis is the second line.\r\n")
    end

    it 'If length is provided, nil means it met EOF at beginning' do
      read = "definitely not nil yet"
      File.open(empty_file) do |f|
        read = f.read(10)
      end
      assert(read == nil)
    end

    it 'If length is provided, 1 to length-1 bytes string means it met EOF after reading the result' do
      read = nil
      File.open(two_line_file) do |f|
        read = f.read(1000)
      end
      assert(read.length < 1000)
    end

    it 'If length is provided, the length bytes string means it doesn’t meet EOF' do
      read = nil
      File.open(two_line_file) do |f|
        read = f.read(10)
      end
      assert(read.length == 10)
    end

    it 'If length is zero, it returns ""' do
      read = nil
      File.open(two_line_file) do |f|
        read = f.read(0)
      end
      assert(read == "")
    end

    it 'At end of file, it returns "" if length omitted or nil' do
      got_empty_str = false
      File.open(two_line_file) do |f|
        loop {
          read = f.read(nil)
          if read == ""
            got_empty_str = true
            break
          end
        }
      end
      assert(got_empty_str)
    end

    it 'Raises an IOError if the file isn\'t open for reading' do
      assert_raises(IOError) do
        File.open(two_line_file, 'a') do |f|
          f.read
        end
      end
    end
  end

  describe 'File#write' do
    it 'Writes the given string to the file' do
      File.open(file_for_writing, 'w') do |f|
        f.write('my message')
      end
      read = nil
      File.open(file_for_writing) do |f|
        read = f.read
      end
      assert (read == 'my message')
    end

    it 'If the argument is not a string, it will be converted to a string using to_s' do
      o = Object.new
      class << o
        def to_s
          "to_s result"
        end
      end

      File.open(file_for_writing, 'w') do |f|
        f.write(o)
      end
      read = nil
      File.open(file_for_writing) do |f|
        read = f.read
      end
      assert (read == 'to_s result')
    end

    it 'Returns the number of bytes written' do
      bytes_written = 0
      File.open(file_for_writing, 'w') do |f|
        bytes_written = f.write('1234')
      end
      assert(bytes_written == 4)
    end

    it 'Raises an IOError if the file isn\'t open for writing' do
      assert_raises(IOError) do
        File.open(two_line_file) do |f|
          f.write('my message')
        end
      end
    end
  end

  describe 'File#each(&block)' do
    it 'Executes the given block for each line in the file, passing in the line' do
      lines = []
      File.open(two_line_file) do |f|
        f.each do |l|
          lines.push l
        end
      end
      assert (lines[0].strip == "This file has two lines." && lines[1].strip == "This is the second line.")
    end

    it 'Returns an Enumerator if no block is given' do
      f = File.open(two_line_file)
      result = f.each
      assert(result.class == Enumerator)
      assert(result.next.strip == "This file has two lines.")
      assert(result.next.strip == "This is the second line.")
    end
  end

  describe 'File#each_line(&block)' do
    it 'Is an alias for each' do
      lines = []
      File.open(two_line_file) do |f|
        f.each do |l|
          lines.push l
        end
      end
      assert (lines[0].strip == "This file has two lines." && lines[1].strip == "This is the second line.")
    end
  end

  describe 'File#each_byte(&block)' do
    it 'Executes the given block for each character in the file' do
      bytes = []
      File.open(two_line_file) do |f|
        f.eof?
        f.each_byte do |b|
          bytes.push b
        end
      end
      assert(bytes[0] == 'T'.ord)
      assert(bytes[1] == 'h'.ord)
      # ... you get the idea
    end

    it 'Returns an Enumerator if no block is given' do
      f = nil
      begin
        f = File.open(two_line_file)
        result = f.each_byte
        assert(result.class == Enumerator)
        assert(result.next == "T".ord)
        assert(result.next == "h".ord)
      ensure
        f.close unless f.nil?
      end
    end
  end

  describe 'File#eof | eof?' do
    it 'Returns true if EOF has been hit, or else false' do
      f = nil
      begin
        f = File.open(two_line_file)
        assert(f.eof? == false)
        f.read
        assert(f.eof? == true)
      ensure
        f.close unless f.nil?
      end
    end

    it 'Returns true for an empty file, even if no reads have been performed yet' do
      f = nil
      begin
        f = File.open(empty_file)
        assert(f.eof? == true)
      ensure
        f.close unless f.nil?
      end
    end
  end

  describe 'File#getbyte' do
    it 'Returns the next character, or nil if at EOF' do
      first_byte = nil
      last_byte = 'not nil yet'
      File.open(two_line_file) do |f|
        first_byte = f.getbyte
        f.read # read full
        last_byte = f.getbyte
      end
      assert(first_byte == 'T'.ord && last_byte == nil)
    end
  end

  describe 'File#getc' do
    it 'Returns the next character, or nil if at EOF' do
      first_byte = nil
      last_byte = 'not nil yet'
      File.open(two_line_file) do |f|
        first_byte = f.getc
        f.read # read full
        last_byte = f.getc
      end
      assert(first_byte == 'T' && last_byte == nil)
    end
  end

  describe 'File#ungetbyte' do
    it 'Pushes back bytes onto a file buffer ' do
      read = []
      File.open(empty_file) do |f|
        # ungets in reverse order like CRuby.
        # Unlike CRuby implementation (but like the CRuby documentation)
        # only the last character will be read back
        f.ungetbyte 'abcde'
        # TODO: Why does read fail here on Windows, but not getc? `read.push f.read`
        read.push f.getc
        f.ungetbyte 65 # 'A'
        read.push f.getc
      end
      assert(read[0] == 'a' && read[1] == 'A')
    end
  end

  describe 'File#ungetc' do
    it 'Pushes back bytes onto a file buffer ' do
      read = []
      File.open(empty_file) do |f|
        # ungets in reverse order like CRuby.
        # Unlike CRuby implementation (but like the CRuby documentation)
        # only the last character will be read back
        f.ungetbyte 'abcde'
        read.push f.getc
        f.ungetbyte 65 # 'A'
        read.push f.getc
      end
      assert(read[0] == 'a' && read[1] == 'A')
    end
  end

  describe 'File#seek(amount, whence=IO::SEEK_SET)' do
    it 'Seeks `amount` bytes from the beginning of the file when given `whenc=IO::SEEK_SET` (the default)' do
      result = nil
      File.open(two_line_file) do |f|
        f.seek(5)
        result = f.read(4)
      end
      assert result == 'file'
    end

    it 'Seeks `amount` bytes from the end of the file when given `whenc=IO::SEEK_END`' do
      result = nil
      File.open(two_line_file) do |f|
        f.seek(-7, IO::SEEK_END)
        result = f.read.strip
      end
      assert result == 'line.'
    end

    it 'Seeks `amount` bytes from the current position of the file when given `whenc=IO::SEEK_CUR`' do
      result = nil
      File.open(two_line_file) do |f|
        f.read(5)
        f.seek(5, IO::SEEK_CUR)
        result = f.read(3)
      end
      assert result == 'has'
    end
  end
end
