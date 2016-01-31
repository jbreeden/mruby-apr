load 'fixture.rb'

TestFixture.new('APR API: Directories') do
  err, @pool = APR.pool_create(nil)
  @a_rwx = 0x070707

  def check_errno(errno)
    unless assert(errno == 0)
      raise "ERRNO(#{errno}) #{APR.strerror(errno)}"
    end
  end

  describe 'APR.dir_open(path: String, pool: Pool): [errno: Fixnum, dir: Dir]' do
    it 'Gets file information for each entry in the directory' do
      err, dir = APR.dir_open '.', @pool
      check_errno(err)
      APR.dir_close dir
    end
  end

  describe 'APR.dir_read(finfo: Finfo, wanted: Fixnum, dir: Dir): errno: Fixnum' do
    it 'Gets file information for each entry in the directory' do
      err, dir = APR.dir_open '.', @pool
      check_errno(err)

      time_pattern = "*[0-9][0-9]:[0-9][0-9]:[0-9][0-9]*"

      err, finfo = APR.dir_read 0, dir

      found_cwd = false
      found_parnet = false
      while err == 0 || err == APR::APR_INCOMPLETE
        # Just checking the access, modification, and creation times, since these should be available
        assert(0 == APR.fnmatch(time_pattern, APR.ctime(finfo.atime)[1], 0))
        assert(0 == APR.fnmatch(time_pattern, APR.ctime(finfo.mtime)[1], 0))
        assert(0 == APR.fnmatch(time_pattern, APR.ctime(finfo.ctime)[1], 0))
        found_cwd ||= (finfo.name == '.')
        found_parent ||= (finfo.name == '..')

        err, finfo = APR.dir_read 0, dir
      end
      assert (found_parent && found_cwd)
      APR.dir_close dir
    end
  end

  describe 'APR.dir_make(path: String, permissions: Fixnum, pool: Pool): errno: Fixnum' do
    it 'Creates a directory' do
      err = APR.dir_make 'sandbox/test_create_dir', @a_rwx, @pool
      check_errno(err)
      err, dir = APR.dir_open('sandbox/test_create_dir', @pool)
      check_errno(err)
    end
  end

  describe 'APR.dir_make_recursive(path: String, permissions: Fixnum, pool: Poolype): errno: Fixnum' do
    it 'Creates a directory and any required parent directories' do
      err = APR.dir_make_recursive 'sandbox/test_create_dir/some/nested/dir', @a_rwx, @pool
      check_errno(err)
      err, dir = APR.dir_open('sandbox/test_create_dir/some/nested/dir', @pool)
      check_errno(err)
      APR.dir_close(dir)
    end
  end

  describe 'APR.dir_remove(path: String, pool: Poolype): errno: Fixnum' do
    it 'Deletes a directory' do
      err = APR.dir_remove 'sandbox/test_create_dir/some/nested/dir', @pool
      check_errno(err)
      err = APR.dir_remove 'sandbox/test_create_dir/some/nested', @pool
      check_errno(err)
      err = APR.dir_remove 'sandbox/test_create_dir/some/', @pool
      check_errno(err)
      err = APR.dir_remove 'sandbox/test_create_dir', @pool
    end
  end

end
