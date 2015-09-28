load 'fixture.rb'

TestFixture.new('Ruby API: File::Stat') do
  empty_file = "#{$sandbox}/empty_file.txt"
  two_line_file = "#{$sandbox}/two_line_file.txt"
  file_for_writing = "#{$sandbox}/file_for_writing.txt"

  describe 'Stat#atime' do
    it 'Gives the access time of the file as a Time' do
      # Unfortunately have to sleep for a second to guarantee atime > "now"
      APR.apr_sleep 2000000 # micro seconds
      stat = File::Stat.new(empty_file)
      assert(stat.atime.class == Time)
    end
  end

  describe 'Stat#ctime' do
    it 'Gives the creation time of the file as a Time' do
      created_file = "#{$sandbox}/created_file.txt"
      now = Time.now
      # Unfortunately have to sleep for a second to guarantee ctime > "now"
      APR.apr_sleep 2000000 # micro seconds
      # File.delete(created_file) if File.exists?(created_file)
      File.open(created_file, 'w') do |f|
        f.puts "Created after #{now}"
      end
      stat = File::Stat.new(created_file)
      ctime = stat.ctime
      assert(ctime > now)
    end
  end

  describe 'Stat#mtime' do
    it 'Gives the last modified time of the file as a Time' do
      stat1 = File::Stat.new(file_for_writing)
      File.open(file_for_writing, 'w') do |f|
        f.puts "Modification"
      end
      stat2 = File::Stat.new(file_for_writing)
      assert(stat2.mtime > stat1.mtime)
    end
  end

  describe 'Stat#size' do
    it 'Gives the size of the file in bytes' do
      stat = File::Stat.new(two_line_file)
      # File hase 2 24-char lines, size depends on line endings
      assert(50 <= stat.size && stat.size <= 52)
    end
  end

  describe 'Stat#directory?' do
    it 'Returns true if the file is a directory' do
      stat = File::Stat.new($sandbox)
      assert(stat.directory?)
    end

    it 'Returns false for non-directory files' do
      stat = File::Stat.new(empty_file)
      assert(!stat.directory?)
    end
  end

  describe 'Stat#file?' do
    it 'Returns true if the file is a regular file' do
      stat = File::Stat.new(empty_file)
      assert(stat.file?)
    end

    it 'Returns false for non-regular files' do
      stat = File::Stat.new($sandbox)
      assert(!stat.file?)
    end
  end
end
