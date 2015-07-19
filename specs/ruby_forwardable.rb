class TestForwardee
  def return_one
    1
  end

  def return_arg(arg)
    arg
  end

  def run_block(&block)
    block[]
  end
end

class TestForwarder
  extend Forwardable
  delegate [:return_one, :return_arg, :run_block] => :@forwardee

  def initialize
    @forwardee = TestForwardee.new
  end
end

TestFixture.new('Ruby API: Forwardable') do
  describe 'Forwardable#delegate' do
    it 'Creates delegate methods on classes' do
      f = TestForwarder.new
      assert f.return_one == 1
    end

    it 'Creates delegate methods on instances' do
      forwardee = Object.new
      class << forwardee
        def return_two
          2
        end
      end
      forwarder = Object.new
      forwarder.instance_variable_set(:@forwardee, forwardee)
      forwarder.extend Forwardable
      forwarder.delegate :return_two => :@forwardee
      assert forwarder.return_two == 2
    end

    it 'Passes arguments along' do
      f = TestForwarder.new
      assert f.return_arg('test') == 'test'
    end

    it 'Passes blocks along' do
      f = TestForwarder.new
      success = false
      f.run_block do
        success = true
      end
      assert success
    end
  end
end
