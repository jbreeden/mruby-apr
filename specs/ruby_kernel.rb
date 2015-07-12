TestFixture.new("Ruby API: Kernel") do
  describe 'Kernel::` (backquote)' do
    it 'Runs a command and returns it\'s standard output' do
      assert(`echo 1234`.strip == '1234')
    end
  end
end
