class APR::SharedPool
  def initialize
    err, @pool = APR.apr_pool_create(nil)
    APR.raise_apr_errno(err)
    @members = []
    @destroyed = false
  end

  def pool
    @pool
  end

  def join(new_member)
    if @destroyed
      raise StandardError.new("Cannot join this pool, it has already been emptied and destroyed.")
    end
    unless @members.include?(new_member)
      @members.unshift(new_member)
    end
  end

  def leave(existing_member)
    unless @members.include?(existing_member)
      raise ArgumentError.new("#{existing_member} is not a member of this shared pool")
    end
    @members.delete(existing_member)
    if @members.empty?
      APR.apr_pool_destroy(@pool)
    end
    @destroyed = true
  end
end
