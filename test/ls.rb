def ls(dir)
  result = []
  Dir.entries(dir).each do |e|
    next if e[0] == '.'
    result.push("#{dir}/#{e}")
    if File.directory?("#{dir}/#{e}")
      result = result.concat(ls("#{dir}/#{e}"))
    end
  end
  result
end

puts ls('.').length
