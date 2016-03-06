class String
  unless instance_methods.include? :frozen?
    def frozen?
      false
    end
  end
end
