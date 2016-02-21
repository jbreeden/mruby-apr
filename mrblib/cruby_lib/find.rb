module Find
  def find(*paths)
    ignore_error = false
    if [true, false].include?(paths.last)
      ignore_error =  paths.pop
    end
    
    block_given? or return enum_for(__method__, *paths, ignore_error)

    paths.map { |path|
      raise SystemCallError.new("No such file or directory #{d}") unless File.exist?(path)
      path.dup
    }.each do |path|
      path = path.to_path if path.respond_to? :to_path
      paths = [path]
      while file = paths.shift
        begin
          yield file.dup
          begin
            is_directory = File.directory?(file)
          rescue SystemCallError
            raise unless ignore_error
            next
          end
          if is_directory
            begin
              files = Dir.entries(file)
            rescue SystemCallError
              raise unless ignore_error
              next
            end
            files.sort!
            files.reverse_each {|f|
              next if f == "." or f == ".."
              f = File.join(file, f)
              paths.unshift f
            }
          end
        rescue Prune
          # Just Continue
        end
      end
    end
    nil
  end

  class Prune < StandardError; end
  def prune
    raise Prune.new
  end

  module_function :find
  module_function :prune
end
