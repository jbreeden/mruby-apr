MRuby::Build.new do |conf|
  # load specific toolchain settings

  # Gets set by the VS command prompts.
  if ENV['VisualStudioVersion'] || ENV['VSINSTALLDIR']
    toolchain :visualcpp
  else
    toolchain :gcc
  end

  conf.gembox 'full-core'

  conf.cc.flags << '-DMRB_INT64'

  # Include this gem from source
  conf.gem File.dirname(__FILE__)
end
