require 'fileutils'

eval(File.read("./MDDOC.rb"))

files.each do |file|
  name = File.basename(file)
  d_start = doc_start(name)
  d_prefix = doc_prefix(name)
  d_end = doc_end(name)

  unless d_start
    puts "Skipping #{file}. No doc_start defined."
    next
  end
  unless d_prefix
    puts "Skipping #{file}. No doc_prefix defined."
    next
  end
  unless d_end
    puts "Skipping #{file}. No doc_end defined."
    next
  end

  doc_file = "./doc/#{File.dirname(file)}/#{File.basename(file).sub(Regexp.new("\\" + File.extname(file) + "$"), ".md")}"
  puts "Documenting #{file} in #{doc_file}"

  in_doc = false
  reg_start = Regexp.new("^\s*#{d_start}\s*$")
  reg_prefix = Regexp.new("^\s*#{d_prefix}\s{0,1}")
  reg_end = Regexp.new("^\s*#{d_end}\s*$")

  doc_dir = "./doc/#{File.dirname(file)}"
  unless Dir.exists?(doc_dir)
    FileUtils.mkdir_p doc_dir
  end

  File.open(doc_file, "w") do |out|
    File.read(file).each_line do |line|

      if !in_doc && reg_start =~ line
        in_doc = true
        next
      end

      if in_doc && !(reg_end =~ line)
        out.puts(line.sub(reg_prefix, ''))
        next
      end

      if in_doc && reg_end =~ line
        in_doc = false
        out.puts # write a blank line
        next
      end

    end
  end

  f = File.open(doc_file, "r")
  doc_file_size = f.size
  f.close
  if doc_file_size == 0
    puts "Deleting #{doc_file} (it was empty)"
    File.delete doc_file
  end
end
