# cat src/mruby_APR.c | ruby -e 'puts $stdin.read.gsub(/\n{3,}/m, "\n\n")' > temp; mv temp src/mruby_APR.c

## 
## Use format specifier for ints
## 
# File.open('src/mruby_APR.c', 'r') do |f|
#   while l = f.gets
#     if (l =~ /mrb_mruby_curses_gem_init/)
#       puts l
#       break
#     elsif (l =~ /#if BIND/)
#       puts l
#       
#       ints = []
#       func = ''
#       loop {
#         l = f.gets
#         func << l
#         if int = l[/mrb_obj_is_kind_of\(mrb, ([^,]+), mrb->fixnum_class\)/, 1]
#           ints << int
#         end
#         break if l =~ /^#endif/
#       }
#       
#       # puts ints.inspect
#       match = func.match(/mrb_get_args\(mrb, "[^"]+"(.*)\);$/)
#       unless match
#         puts func
#         next
#       end
#       
#       params = match[1].gsub(',', '').gsub('&', '').strip.split(/\s/)
#       
#       ints.each do |int|
#         index = params.index(int)
#         func.gsub!(/mrb_value #{int};/, "mrb_int native_#{int};")
#         func.gsub!(/^\s+if \(!mrb_obj_is_kind_of\(mrb, #{int}, mrb->fixnum_class(.*?)^\s*}\n/m, "")
#         func.gsub!(/^.*mrb_fixnum\(#{int}\).*$/, '')
#         func.sub!(/mrb_get_args\(mrb, "(.{#{index}})o/, "mrb_get_args(mrb, \"\\1i")
#         func.sub!(/mrb_get_args(.*)&#{int}(,|\))/, "mrb_get_args\\1&native_#{int}\\2")
#       end
#       puts func
#     else
#       puts l
#     end
#   end
#   
#   # Pump out the remainder of the file, if any
#   while l = f.gets
#     puts l
#   end
# end

## 
## Use format specifier for strings
## 
# File.open('src/mruby_APR.c', 'r') do |f|
#   while l = f.gets
#     if (l =~ /mrb_mruby_curses_gem_init/)
#       puts l
#       break
#     elsif (l =~ /#if BIND/)
#       puts l
#       
#       strings = []
#       func = ''
#       loop {
#         l = f.gets
#         func << l
#         if str = l[/ = mrb_string_value_cstr\(mrb, &(\S*)\);/, 1]
#           strings << str
#         end
#         break if l =~ /^#endif/
#       }
#       
#       # puts strings.inspect
#       match = func.match(/mrb_get_args\(mrb, "[^"]+"(.*)\);$/)
#       unless match
#         puts func
#         next
#       end
#       
#       params = match[1].gsub(',', '').gsub('&', '').strip.split(/\s/)
#       
#       strings.each do |str|
#         index = params.index(str)
#         func.gsub!(/mrb_value #{str};/, "char * native_#{str};")
#         func.gsub!(/^\s+if \(!mrb_obj_is_kind_of\(mrb, #{str}, mrb->string_class(.*?)^\s*}\n/m, "")
#         func.gsub!(/^.*mrb_string_value_cstr\(mrb, &#{str}\).*$/, '')
#         func.sub!(/mrb_get_args\(mrb, "(.{#{index}})o/, "mrb_get_args(mrb, \"\\1z")
#         func.sub!(/mrb_get_args(.*)&#{str}(,|\))/, "mrb_get_args\\1&native_#{str}\\2")
#       end
#       puts func
#     else
#       puts l
#     end
#   end
#   
#   # Pump out the remainder of the file, if any
#   while l = f.gets
#     puts l
#   end
# end

# def tag_fns
#   File.open('src/mruby_APR.c') do |f|
#     stop = false
#     f.each_line do |l|
#       if !stop && fn = l[/#if BIND_(.*)_FUNCTION/, 1]
#         puts "/* MRUBY_BINDING: #{fn} */"
#         puts l
#       elsif !stop && l =~ /^\#endif$/
#         puts l
#         puts "/* MRUBY_BINDING_END */"
#       elsif !stop && l =~ /gem_init/
#         puts l
#         stop = true
#       else
#         puts l
#       end
#     end
#   end
# end
# tag_fns

def add_shas
  File.open('src/mruby_APR.c') do |f|
    f.each_line do |l|
      if l[/MRUBY_BINDING:/]
        puts l
        puts "/* sha: user_edited */"
      else
        puts l
      end
    end
  end
end
add_shas

# def trim_disabled_fns
#   disabled = Hash.new { |h, k| h[k] = false }
#   File.open('include/mruby_APR.h', 'r') do |f|
#     f.each_line do |line|
#       if (match = line[/#define\s*BIND_(.*)_FUNCTION\s*FALSE/, 1])
#         disabled[match] = true
#       end
#     end
#   end
#   
#   File.open('src/mruby_APR.c', 'r') do |f|
#     File.open('src/mruby_APR.c.trimmed', 'w') do |out|
#       line = f.gets
#       loop {
#         break if line.nil?
#         
#         if match = line[/MRUBY_BINDING: (\S+)/, 1]
#           if disabled[match]
#             line = f.gets until line =~ /MRUBY_BINDING_END/
#             line = f.gets
#             line = f.gets until line =~ /\S/
#             next
#           end
#         end
#         
#         # Important to keep #if's indented for this guy
#         if match = line[/^#if BIND_(\S+)_FUNCTION/, 1]
#           if disabled[match]
#             line = f.gets until line =~ /^#endif/
#             line = f.gets
#             line = f.gets until line =~ /\S/
#             next
#           end
#         end
#         
#         out.puts line
#         line = f.gets
#       }
#     end
#   end
#   
#   File.rename('src/mruby_APR.c.trimmed', 'src/mruby_APR.c')
# end
# trim_disabled_fns()
