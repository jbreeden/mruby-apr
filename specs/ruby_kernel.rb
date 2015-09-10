load 'fixture.rb'

TestFixture.new("Ruby API: Kernel") do
  describe 'Kernel::` (backquote)' do
    it 'Runs a command and returns it\'s standard output' do
      assert(`echo 1234`.strip == '1234')
    end

    it 'Sets $? based on the exit status of the child process' do
      `exit 1`
      assert($?.exitstatus == 1)
      `exit 2`
      assert($?.exitstatus == 2)
    end
  end
end
