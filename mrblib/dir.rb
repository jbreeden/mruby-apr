class Dir
  # def initialize(path)
  #
  # end
  #
  # def self.open(path, &block)
  #
  # end

  def self.[](pattern)
    Util.glob(pwd, pattern)
  end
  class << self
    alias glob []
  end

  def self.chdir(path, &block)
    if block.nil?
      err = APR.apr_dir_chdir(path)
      APR.raise_apr_errno(err)
    else
      prev = pwd
      begin
        chdir path
        block[]
      ensure
        chdir prev
      end
    end
  end

  # def self.chroot
  #
  # end

  def self.delete(path)
    APR.with_pool do |pool|
      err = APR.apr_dir_remove(path, pool)
      APR.raise_apr_errno(err)
    end
  end
  class << self
    alias rmdir delete
    alias unlink rmdir
  end

  def self.entries(path)
    results = []
    APR.with_pool do |pool|
      err, dir = APR.apr_dir_open path, pool
      APR.raise_apr_errno(err)

      err, finfo = APR.apr_dir_read APR::APR_FINFO_DEFAULT, dir
      while err == 0 || err == APR::APR_INCOMPLETE
        results.push(finfo.name)
        err, finfo = APR.apr_dir_read APR::APR_FINFO_DEFAULT, dir
      end
    end
    results
  end

  def self.exists?(path)
    File.directory?(path)
  end
  class << self
    alias exist? exists?
  end

  def self.foreach(path, &block)
    files = entries(path)
    if block.nil?
      self.to_enum :foreach, path
    else
      files.each &block
    end
  end

  def self.getcwd
    # TODO May need to fix path on windows (Ruby always uses /)
    err, path = APR.apr_dir_getcwd
    APR.raise_apr_errno(err) # Why would this ever happen?
    path
  end
  class << self
    alias pwd getcwd
  end

  # def self.home
  #
  # end

  def self.mkdir(path)
    APR.with_pool do |pool|
      err = APR.apr_dir_make path, APR::APR_FPROT_OS_DEFAULT, pool
      APR.raise_apr_errno(err)
    end
  end

  module Util
    def self.glob(from, pattern, recursing = false)
      results = []
      dirs = [from]
      next_dirs = []
      prev_dirs = []
      parts = pattern.split('/')
      current_part = 0
      last_part = parts.length - 1
      recursed = false

      parts.each do |part|
        next if part == '' # double slash in pattern, treat it as one

        dirs.each do |dir|
          files = Dir.entries(dir)
          # '**' matches 0 or more directories, so inlcude '.'
          files = files.reject { |e| e == '.' } unless part == '.' || part == '**'
          files = files.reject { |e| e == '..' } unless part == '..'
          files.each do |entry|
            next if entry[0] == '.' && !(entry == '.' || entry == '..')
            relative_path = "#{dir}/#{entry}"
            if APR::APR_SUCCESS == APR.apr_fnmatch(part, entry, 0)
              if current_part == last_part
                results.push(relative_path)
              else
                if File.directory? relative_path
                  next_dirs.push(relative_path)
                end
              end
            end
          end
        end

        # Once we get here, the ** should have matched all directories
        # under all paths listed in `dirs`. Now we can recurse on them
        # all with the remainder of the glob. Afterwards, the glob matching
        # will be finished
        if part == '**' && current_part != last_part
          if current_part == 0
            prev_dirs = [from]
          end
          prev_dirs.each do |dir|
            subdirs(dir, recurse: true).each do |subdir|
              results.concat(
                Dir::Util.glob(subdir, parts[(current_part + 1)..last_part].join('/'), true)
              )
            end
          end
          recursed = true
        end

        break if recursed
        prev_dirs = dirs
        dirs = next_dirs
        next_dirs = []
        current_part += 1
      end
      if recursing
        results
      else
        results.uniq.map { |r|
          r.sub(from + '/', '')
        }
      end
    end

    def self.subdirs(path, opt = {})
      results = []
      Dir.entries(path).reject { |d| d[0] == '.' }.each do |entry|
        rel_path = "#{path}/#{entry}"
        if File.directory? rel_path
          results.push rel_path
          results = results.concat(subdirs(rel_path, opt)) if opt[:recurse]
        end
      end
      results.uniq
    end
  end
end
