# mruby glob.rb  "/./a/{}b/c{}/d{e}f/{g,h,}/{,i,j}/{k/l}/[m/n]//o///p"
# Dir::GlobAST.new(ARGV[0]).each_segment { |segment| puts segment.map { |pattern| "/#{pattern}/(#{pattern.class})"}}
puts Dir[ARGV[0]]
