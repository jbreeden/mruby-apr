class APR::Process
  def self.with_ruby_semantics(*command)
    p = APR::Process.new

    if command.length == 0
      raise ArgumentError.new("No command specified")
    elsif command.length == 1 && command[0].class == String
      argv = command[0].shellsplit
      p.cmdtype_set :APR_SHELLCMD_ENV
    elsif command.length == 1
      argv = command[0].to_s.shellsplit
      p.cmdtype_set :APR_SHELLCMD_ENV
    else
      argv = command.map{ |arg| arg.to_s}
      p.cmdtype_set :APR_PROGRAM_PATH
    end
    
    [p, argv]
  end
end
