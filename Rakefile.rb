# Util Functions
# --------------

def each_test_file(&block)
  Dir['specs/*.rb'].reject { |f| File.basename(f) == 'fixture.rb' }.each(&block)
end

def test_file_name(test_file)
  File.basename(test_file).sub(/\.rb$/, '')
end

# Tasks
# -----

desc "Print the supported functions"
task "tell_functions" do
  File.open('include/mruby_APR.h', 'r') do |f|
    regex = /BIND_(.*)_FUNCTION TRUE/
    f.each_line do |l|
      puts l[regex, 1] if l =~ regex
    end
  end
end

namespace :test do

  each_test_file do |test_file|
    test = test_file_name(test_file)
    desc "Run the #{test} tests"
    task (test) do
      Dir.chdir 'specs' do
        system "mruby #{test_file.sub(/^specs\//, '')}"
      end
    end
  end

  desc "Run all of the tests"
  task :all do
    Dir.chdir 'specs' do
      Dir['*.rb'].reject { |f| File.basename(f) == 'specs/fixture.rb' }.sort.each do |f|
        system "mruby #{f}"
      end
    end
  end

end

desc "Generate method stubs for a ruby class"
task :gen_rb do
  c = eval(ENV['CLASS'])
  unless c.class == Class
    $stderr.puts "#{ENV['CLASS']} does not refer to a Ruby class"
  end
  c.singleton_methods(false).sort.each do |m|
    puts "def self.#{m}(*args)\n   raise NotImplementedError.new\nend\n\n"
  end
  c.public_instance_methods(false).sort.each do |m|
    puts "def #{m}(*args)\n   raise NotImplementedError.new\nend\n\n"
  end
end
