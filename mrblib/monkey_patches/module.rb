class Module
  unless instance_methods.include? :name
    def name
      to_s
    end
  end
end
