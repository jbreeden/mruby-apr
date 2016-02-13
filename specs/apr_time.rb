load 'fixture.rb'

APR::Spec.new('APR API: Time') do
  err, @pool = APR.pool_create(nil)

  def check_errno(errno)
    unless assert(errno == 0)
      raise APR.strerror(errno)
    end
  end

  describe 'APR.time_now(pool: Pool): time: Time' do
    it 'Gets the current time' do
      time = APR.time_now 0
      err, time_s = APR.ctime(time)

      check_errno(err)
      assert(0 == APR.fnmatch("*[0-9][0-9]:[0-9][0-9]:[0-9][0-9]*", time_s, 0))
    end
  end

end
