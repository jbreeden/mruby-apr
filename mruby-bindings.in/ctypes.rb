# CTypes.define('Example') do
#   self.needs_unboxing = true
#   self.needs_boxing_cleanup = false
#   self.needs_unboxing_cleanup = false
#   self.needs_type_check = true
#   
#   self.recv_template = 'mrb_value %{value};'
#   self.format_specifier = 'o'
#   self.get_args_template = '&%{value}'
#   self.type_check_template = nil
#   self.invocation_arg_template = '%{value}'
#   self.field_swap_template = %{old} = %{new};
#   
#   self.unboxing_fn.invocation_template = '%{as} = TODO_mruby_unbox_Example(%{unbox});'
#   self.unboxing_fn.cleanup_template = 'free(%{value});'
#   
#   self.boxing_fn.invocation_template = '%{as} = TODO_mruby_box_Example(%{box});'
#   self.boxing_fn.cleanup_template = 'free(%{value});'
# end

## This block is called to determine the Ruby class name to use for a C type.
# CTypes.translate_type_names do |name|
#   MRubyBindings.type_name_to_rb_class(name)
# end

## This block is called to determine the Ruby method name to use for a C function.
# CTypes.translate_fn_names do |name|
#   name
# end

## This block is called to determine the Ruby constant name to use for a C enum value.
# CTypes.translate_enum_names do |name|
#   name
# end
