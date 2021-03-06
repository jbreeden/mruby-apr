load 'fixture.rb'

# Note:
# I know, it's evil, but these tests are very much order dependent.

APR::Spec.new('APR API: File IO') do

  test_txt = "#{$sandbox}/test.txt"
  two_line_file = "#{$sandbox}/two_line_file.txt"

  err, @pool = APR.pool_create(nil)
  @ug_rw = 0x660 # Probably going to be "umasked" to 640

  @str_with_null = "BeforeNull\x00AfterNull"

  def check_errno(errno)
    unless assert(errno == 0)
      raise APR.strerror(errno)
    end
  end

  describe 'APR.file_open(name: String, mode: Fixnum, permissions: Fixnum, pool: Pool): [errno: Fixnum, file: File]' do
    it 'Can open a file for writing' do
      err, file = APR.file_open test_txt,
        APR::APR_FOPEN_CREATE | APR::APR_FOPEN_WRITE | APR::APR_FOPEN_TRUNCATE, @ug_rw, @pool
      check_errno(err)
      assert (file.kind_of?(APR::File))
      APR.file_close(file)
      APR.pool_clear(@pool)
    end

    it 'Can open a file for reading' do
      err, file = APR.file_open test_txt, APR::APR_FOPEN_READ, 0, @pool
      check_errno(err)
      assert (file.kind_of?(APR::File))
      APR.file_close(file)
      APR.pool_clear(@pool)
    end
  end

  describe 'APR.file_puts(buf: String, file: File)' do
    it 'Can write to an open, writable, file' do
      err, file = APR.file_open test_txt,
        APR::APR_FOPEN_CREATE | APR::APR_FOPEN_WRITE | APR::APR_FOPEN_TRUNCATE, @ug_rw, @pool
      check_errno(err)
      assert (file.kind_of?(APR::File))

      err = APR.file_puts('This is a test', file)
      check_errno(err)

      APR.file_close(file)
      APR.pool_clear(@pool)
    end
  end

  describe 'APR.file_gets(at_most_n_bytes: Fixnum, file: File): [errno: Fixnum, str: String]' do
    it 'Reads length (1st param) characters and returns the string' do
      err, file = APR.file_open test_txt, APR::APR_FOPEN_READ, 0, @pool
      check_errno(err)
      assert (file.kind_of?(APR::File))

      err, str = APR.file_gets('This is a test'.length, file)
      check_errno(err)
      assert (str == 'This is a test')

      APR.file_close(file)
      APR.pool_clear(@pool)
    end

    it 'Reads as many characters as possible when length is beyond EOF' do
      err, file = APR.file_open test_txt, APR::APR_FOPEN_READ, 0, @pool
      check_errno(err)
      assert (file.kind_of?(APR::File))

      err, str = APR.file_gets('This is a test'.length * 10, file)
      assert (err == 0 && str == 'This is a test')

      APR.file_close(file)
      APR.pool_clear(@pool)
    end
  end

  describe 'APR.file_write(file: File, buffer: String, num_bytes: Fixnum): [errno: Fixnum, bytes_written: Fixnum]' do
    it 'Can write strings with nulls to a file' do
      err, file = APR.file_open(test_txt,
        APR::APR_FOPEN_CREATE | APR::APR_FOPEN_WRITE | APR::APR_FOPEN_TRUNCATE, @ug_rw, @pool)
      check_errno(err)
      assert (file.kind_of?(APR::File))

      buf = @str_with_null
      length = @str_with_null.length
      err, bytes_written = APR.file_write(file, buf, length)

      check_errno(err)
      assert (bytes_written == length)

      APR.file_close(file)
      APR.pool_clear(@pool)
    end
  end

  describe 'APR.file_read(file: File, Fixnum: num_bytes): [errno: Fixnum, str: String]' do
    it 'Can read strings with nulls from a file' do
      err, file = APR.file_open(test_txt, APR::APR_FOPEN_READ, 0, @pool)
      check_errno(err)
      assert (file.kind_of?(APR::File))

      err, str = APR.file_read(file, 100)
      check_errno(err)
      assert (str.length == @str_with_null.length)

      APR.file_close(file)
      APR.pool_clear(@pool)
    end

    it 'Returns EOF on first attempt to read past EOF' do
      err, file = APR.file_open(test_txt, APR::APR_FOPEN_READ, 0, @pool)
      check_errno(err)
      assert (file.kind_of?(APR::File))

      err, str = APR.file_read(file, 100)
      check_errno(err)
      assert (str.length == @str_with_null.length)

      err, str = APR.file_read(file, 100)
      assert(err == APR::APR_EOF)

      APR.file_close(file)
      APR.pool_clear(@pool)
    end
  end

  describe 'APR.file_close(file: File): errno: Fixnum' do
    it 'Closes an File' do
      # No explicit tests yet, this is just here for the output.
    end
  end

  describe 'APR.file_seek(thefile: File, where: Fixnum, offset: Fixnum): [errno: Fixnum, resulting_offset: Fixnum]' do
    it 'Can seek back from the end of the file' do
      err, file = APR.file_open(test_txt, APR::APR_FOPEN_READ, 0, @pool)
      check_errno(err)
      assert (file.kind_of?(APR::File))

      err, offset = APR.file_seek(file, APR::APR_END, -4);
      check_errno(err)
      assert (offset == 16)

      err, str = APR.file_read(file, 10)
      check_errno(err)
      assert (str == 'Null')

      err = APR.file_close(file)
      check_errno(err)
      APR.pool_clear(@pool)
    end
  end

  describe 'APR.file_copy(from_path: String, to_path: String, perms: int, pool: Poolype): errno: Fixnum' do
    it 'Copies files by name' do
      err = APR.file_copy("#{$sandbox}/test.txt", "#{$sandbox}/test_copy.txt", @ug_rw, @pool)
      check_errno(err)

      err, file = APR.file_open("#{$sandbox}/test_copy.txt", APR::APR_FOPEN_READ, 0, @pool)
      check_errno(err)

      APR.file_close(file)
      APR.pool_clear(@pool)
    end
  end

  describe 'APR.file_rename(from_path: String, to_path: String, pool: Poolype): errno: Fixnum' do
    it 'Renames a file' do
      err = APR.file_rename("#{$sandbox}/test_copy.txt", "#{$sandbox}/test_renamed.txt", @pool)
      check_errno(err)

      err, file = APR.file_open("#{$sandbox}/test_renamed.txt", APR::APR_FOPEN_READ, 0, @pool)
      check_errno(err)

      APR.file_close(file)
      APR.pool_clear(@pool)
    end
  end

  describe 'APR.file_remove(from_path: String, to_path: String, perms: int, pool: Poolype): errno: Fixnum' do
    it 'Removes a file' do
      err = APR.file_remove("#{$sandbox}/test_renamed.txt", @pool)
      check_errno(err)

      err, file = APR.file_open("#{$sandbox}/test_renamed.txt", APR::APR_FOPEN_READ, 0, @pool)
      assert (err != 0)
      APR.pool_clear(@pool)
    end
  end

  describe 'APR.file_lock(file: File, lock_type: Fixnum): errno: Fixnum' do
    it 'Locks a file (either flock or iocntl based, depending on platform)' do
      # Only manual testing until process functions are available, this is just here for the output.
    end
  end

  describe 'APR.file_unlock(file: File): errno: Fixnum' do
    it 'Unlocks a file (either flock or iocntl based, depending on platform)' do
      # Only manual testing until process functions are available, this is just here for the output.
    end
  end

  describe 'APR.file_attrs_set(fname: String, attrs: Fixnum, attr_mask: Fixnum, pool: Pool): errno: Fixnum' do
    it 'Sets attributes on a file' do
      # Only manual testing until process functions are available, this is just here for the output.
    end
  end

  describe 'APR.file_info_get(wanted: Fixnum, file: File)' do
    it 'Gets the finfo (fstat - like structure) for an open file' do
      APR.with_pool do |pool|
        err, f = APR.file_open(two_line_file, APR::APR_FOPEN_READ, APR::APR_OS_DEFAULT, pool)
        APR.raise_apr_errno(err)
        err, finfo = APR.file_info_get(APR::APR_FINFO_DEFAULT, f)
        APR.raise_apr_errno(err, ignore: APR::APR_INCOMPLETE)
        assert finfo.class == APR::Finfo
      end
    end
  end

  describe 'APR.stat(file_name: String, wanted: Fixnum, pool: Pool)' do
    it 'Gets the finfo (fstat - like structure) for a file by name' do
      APR.with_pool do |pool|
        err, finfo = APR.stat(two_line_file, APR::APR_FINFO_DEFAULT, pool)
        APR.raise_apr_errno(err, ignore: APR::APR_INCOMPLETE)
        assert finfo.class == APR::Finfo
      end
    end
  end

end
