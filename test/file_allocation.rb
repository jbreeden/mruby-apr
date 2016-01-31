files = []
num_files = 200

puts "Open Files"
(1..num_files).each do |i|
  files.push(File.open("temp/file#{i}", 'w'))
end

sleep 2
