project('jln.mp', 'cpp', default_options : ['cpp_std=c++17'])

if get_option('mp_debug')
  add_global_arguments('-DJLN_MP_ENABLE_DEBUG=1', language : 'cpp')
endif

jln_default_flags = {}
sys = build_machine.system()

# quick compilation
if not ['darwin', 'windows'].contains(sys)
  jln_default_flags = {
    'debug': 'off',
    'whole_program': 'strip_all',
  }

  comp = meson.get_compiler('cpp').get_id()
  if ['clang', 'gcc', 'intel'].contains(comp)
    meson.add_postconf_script('./tools/optimize_ninja.sh')
  endif
endif

subdir('meson_jln_flags')
add_global_arguments(jln_cpp_flags, language:'cpp')
add_global_link_arguments(jln_link_flags, language:'cpp')

if get_option('standalone')
  executable('standalone_test',
             ['test/standalone_mp.cpp', 'test/standalone_smp.cpp'],
             dependencies: declare_dependency(
               include_directories: include_directories('standalone/include')))
endif

test_dep = declare_dependency(include_directories: include_directories('test/include', 'include'))

executable('mp_test', 'test/mp.cpp', dependencies: test_dep)

# start tests
t_algorithm_accumulate = executable('accumulate', 'test/src/algorithm/accumulate.cpp', dependencies: test_dep)
t_algorithm_adjacent_difference = executable('adjacent_difference', 'test/src/algorithm/adjacent_difference.cpp', dependencies: test_dep)
t_algorithm_adjacent_remove = executable('adjacent_remove', 'test/src/algorithm/adjacent_remove.cpp', dependencies: test_dep)
t_algorithm_all_of = executable('all_of', 'test/src/algorithm/all_of.cpp', dependencies: test_dep)
t_algorithm_any_of = executable('any_of', 'test/src/algorithm/any_of.cpp', dependencies: test_dep)
t_algorithm_cartesian = executable('cartesian', 'test/src/algorithm/cartesian.cpp', dependencies: test_dep)
t_algorithm_combine = executable('combine', 'test/src/algorithm/combine.cpp', dependencies: test_dep)
t_algorithm_compare_with = executable('compare_with', 'test/src/algorithm/compare_with.cpp', dependencies: test_dep)
t_algorithm_contains = executable('contains', 'test/src/algorithm/contains.cpp', dependencies: test_dep)
t_algorithm_copy = executable('copy', 'test/src/algorithm/copy.cpp', dependencies: test_dep)
t_algorithm_count = executable('count', 'test/src/algorithm/count.cpp', dependencies: test_dep)
t_algorithm_find = executable('find', 'test/src/algorithm/find.cpp', dependencies: test_dep)
t_algorithm_flatten = executable('flatten', 'test/src/algorithm/flatten.cpp', dependencies: test_dep)
t_algorithm_fold_left = executable('fold_left', 'test/src/algorithm/fold_left.cpp', dependencies: test_dep)
t_algorithm_fold_right = executable('fold_right', 'test/src/algorithm/fold_right.cpp', dependencies: test_dep)
t_algorithm_group = executable('group', 'test/src/algorithm/group.cpp', dependencies: test_dep)
t_algorithm_group_n = executable('group_n', 'test/src/algorithm/group_n.cpp', dependencies: test_dep)
t_algorithm_index = executable('index', 'test/src/algorithm/index.cpp', dependencies: test_dep)
t_algorithm_indices = executable('indices', 'test/src/algorithm/indices.cpp', dependencies: test_dep)
t_algorithm_intersperse = executable('intersperse', 'test/src/algorithm/intersperse.cpp', dependencies: test_dep)
t_algorithm_iota = executable('iota', 'test/src/algorithm/iota.cpp', dependencies: test_dep)
t_algorithm_is_sorted = executable('is_sorted', 'test/src/algorithm/is_sorted.cpp', dependencies: test_dep)
t_algorithm_is_unique = executable('is_unique', 'test/src/algorithm/is_unique.cpp', dependencies: test_dep)
t_algorithm_lexicographical_compare = executable('lexicographical_compare', 'test/src/algorithm/lexicographical_compare.cpp', dependencies: test_dep)
t_algorithm_lower_bound = executable('lower_bound', 'test/src/algorithm/lower_bound.cpp', dependencies: test_dep)
t_algorithm_make_int_sequence = executable('make_int_sequence', 'test/src/algorithm/make_int_sequence.cpp', dependencies: test_dep)
t_algorithm_matrix_shortest = executable('matrix_shortest', 'test/src/algorithm/matrix_shortest.cpp', dependencies: test_dep)
t_algorithm_merge = executable('merge', 'test/src/algorithm/merge.cpp', dependencies: test_dep)
t_algorithm_mismatch = executable('mismatch', 'test/src/algorithm/mismatch.cpp', dependencies: test_dep)
t_algorithm_mismatch_index = executable('mismatch_index', 'test/src/algorithm/mismatch_index.cpp', dependencies: test_dep)
t_algorithm_none_of = executable('none_of', 'test/src/algorithm/none_of.cpp', dependencies: test_dep)
t_algorithm_partition = executable('partition', 'test/src/algorithm/partition.cpp', dependencies: test_dep)
t_algorithm_permutations = executable('permutations', 'test/src/algorithm/permutations.cpp', dependencies: test_dep)
t_algorithm_powerset = executable('powerset', 'test/src/algorithm/powerset.cpp', dependencies: test_dep)
t_algorithm_remove = executable('remove', 'test/src/algorithm/remove.cpp', dependencies: test_dep)
t_algorithm_repeat = executable('repeat', 'test/src/algorithm/repeat.cpp', dependencies: test_dep)
t_algorithm_replace = executable('replace', 'test/src/algorithm/replace.cpp', dependencies: test_dep)
t_algorithm_reverse = executable('reverse', 'test/src/algorithm/reverse.cpp', dependencies: test_dep)
t_algorithm_rotate = executable('rotate', 'test/src/algorithm/rotate.cpp', dependencies: test_dep)
t_algorithm_same = executable('same', 'test/src/algorithm/same.cpp', dependencies: test_dep)
t_algorithm_sort = executable('sort', 'test/src/algorithm/sort.cpp', dependencies: test_dep)
t_algorithm_split = executable('split', 'test/src/algorithm/split.cpp', dependencies: test_dep)
t_algorithm_split_after = executable('split_after', 'test/src/algorithm/split_after.cpp', dependencies: test_dep)
t_algorithm_split_at = executable('split_at', 'test/src/algorithm/split_at.cpp', dependencies: test_dep)
t_algorithm_split_before = executable('split_before', 'test/src/algorithm/split_before.cpp', dependencies: test_dep)
t_algorithm_take_while = executable('take_while', 'test/src/algorithm/take_while.cpp', dependencies: test_dep)
t_algorithm_transform = executable('transform', 'test/src/algorithm/transform.cpp', dependencies: test_dep)
t_algorithm_unique = executable('unique', 'test/src/algorithm/unique.cpp', dependencies: test_dep)
t_algorithm_upper_bound = executable('upper_bound', 'test/src/algorithm/upper_bound.cpp', dependencies: test_dep)
t_algorithm_zip = executable('zip', 'test/src/algorithm/zip.cpp', dependencies: test_dep)
alias_target('mp.algorithm', t_algorithm_accumulate, t_algorithm_adjacent_difference, t_algorithm_adjacent_remove, t_algorithm_all_of, t_algorithm_any_of, t_algorithm_cartesian, t_algorithm_combine, t_algorithm_compare_with, t_algorithm_contains, t_algorithm_copy, t_algorithm_count, t_algorithm_find, t_algorithm_flatten, t_algorithm_fold_left, t_algorithm_fold_right, t_algorithm_group, t_algorithm_group_n, t_algorithm_index, t_algorithm_indices, t_algorithm_intersperse, t_algorithm_iota, t_algorithm_is_sorted, t_algorithm_is_unique, t_algorithm_lexicographical_compare, t_algorithm_lower_bound, t_algorithm_make_int_sequence, t_algorithm_matrix_shortest, t_algorithm_merge, t_algorithm_mismatch, t_algorithm_mismatch_index, t_algorithm_none_of, t_algorithm_partition, t_algorithm_permutations, t_algorithm_powerset, t_algorithm_remove, t_algorithm_repeat, t_algorithm_replace, t_algorithm_reverse, t_algorithm_rotate, t_algorithm_same, t_algorithm_sort, t_algorithm_split, t_algorithm_split_after, t_algorithm_split_at, t_algorithm_split_before, t_algorithm_take_while, t_algorithm_transform, t_algorithm_unique, t_algorithm_upper_bound, t_algorithm_zip)
t_assume = executable('assume', 'test/src/assume.cpp', dependencies: test_dep)
t_functional_bind = executable('bind', 'test/src/functional/bind.cpp', dependencies: test_dep)
t_functional_capture = executable('capture', 'test/src/functional/capture.cpp', dependencies: test_dep)
t_functional_cascade = executable('cascade', 'test/src/functional/cascade.cpp', dependencies: test_dep)
t_functional_compose = executable('compose', 'test/src/functional/compose.cpp', dependencies: test_dep)
t_functional_each = executable('each', 'test/src/functional/each.cpp', dependencies: test_dep)
t_functional_eval = executable('eval', 'test/src/functional/eval.cpp', dependencies: test_dep)
t_functional_fix = executable('fix', 'test/src/functional/fix.cpp', dependencies: test_dep)
t_functional_flip = executable('flip', 'test/src/functional/flip.cpp', dependencies: test_dep)
t_functional_identity = executable('identity', 'test/src/functional/identity.cpp', dependencies: test_dep)
t_functional_if = executable('if', 'test/src/functional/if.cpp', dependencies: test_dep)
t_functional_invoke_twice = executable('invoke_twice', 'test/src/functional/invoke_twice.cpp', dependencies: test_dep)
t_functional_is_invocable = executable('is_invocable', 'test/src/functional/is_invocable.cpp', dependencies: test_dep)
t_functional_lift = executable('lift', 'test/src/functional/lift.cpp', dependencies: test_dep)
t_functional_on = executable('on', 'test/src/functional/on.cpp', dependencies: test_dep)
t_functional_partial = executable('partial', 'test/src/functional/partial.cpp', dependencies: test_dep)
t_functional_recurse = executable('recurse', 'test/src/functional/recurse.cpp', dependencies: test_dep)
t_functional_tee = executable('tee', 'test/src/functional/tee.cpp', dependencies: test_dep)
t_functional_try = executable('try', 'test/src/functional/try.cpp', dependencies: test_dep)
alias_target('mp.functional', t_functional_bind, t_functional_capture, t_functional_cascade, t_functional_compose, t_functional_each, t_functional_eval, t_functional_fix, t_functional_flip, t_functional_identity, t_functional_if, t_functional_invoke_twice, t_functional_is_invocable, t_functional_lift, t_functional_on, t_functional_partial, t_functional_recurse, t_functional_tee, t_functional_try)
t_list_append = executable('append', 'test/src/list/append.cpp', dependencies: test_dep)
t_list_as_list = executable('as_list', 'test/src/list/as_list.cpp', dependencies: test_dep)
t_list_at = executable('at', 'test/src/list/at.cpp', dependencies: test_dep)
t_list_back = executable('back', 'test/src/list/back.cpp', dependencies: test_dep)
t_list_drop = executable('drop', 'test/src/list/drop.cpp', dependencies: test_dep)
t_list_erase = executable('erase', 'test/src/list/erase.cpp', dependencies: test_dep)
t_list_front = executable('front', 'test/src/list/front.cpp', dependencies: test_dep)
t_list_insert = executable('insert', 'test/src/list/insert.cpp', dependencies: test_dep)
t_list_insert_range = executable('insert_range', 'test/src/list/insert_range.cpp', dependencies: test_dep)
t_list_is_empty = executable('is_empty', 'test/src/list/is_empty.cpp', dependencies: test_dep)
t_list_is_list = executable('is_list', 'test/src/list/is_list.cpp', dependencies: test_dep)
t_list_is_size_of = executable('is_size_of', 'test/src/list/is_size_of.cpp', dependencies: test_dep)
t_list_join = executable('join', 'test/src/list/join.cpp', dependencies: test_dep)
t_list_list = executable('list', 'test/src/list/list.cpp', dependencies: test_dep)
t_list_offset = executable('offset', 'test/src/list/offset.cpp', dependencies: test_dep)
t_list_pop_back = executable('pop_back', 'test/src/list/pop_back.cpp', dependencies: test_dep)
t_list_pop_front = executable('pop_front', 'test/src/list/pop_front.cpp', dependencies: test_dep)
t_list_prepend = executable('prepend', 'test/src/list/prepend.cpp', dependencies: test_dep)
t_list_push_back = executable('push_back', 'test/src/list/push_back.cpp', dependencies: test_dep)
t_list_push_front = executable('push_front', 'test/src/list/push_front.cpp', dependencies: test_dep)
t_list_range = executable('range', 'test/src/list/range.cpp', dependencies: test_dep)
t_list_size = executable('size', 'test/src/list/size.cpp', dependencies: test_dep)
t_list_slice = executable('slice', 'test/src/list/slice.cpp', dependencies: test_dep)
t_list_sliding = executable('sliding', 'test/src/list/sliding.cpp', dependencies: test_dep)
t_list_swap_index = executable('swap_index', 'test/src/list/swap_index.cpp', dependencies: test_dep)
t_list_take = executable('take', 'test/src/list/take.cpp', dependencies: test_dep)
t_list_wrap_in_list = executable('wrap_in_list', 'test/src/list/wrap_in_list.cpp', dependencies: test_dep)
alias_target('mp.list', t_list_append, t_list_as_list, t_list_at, t_list_back, t_list_drop, t_list_erase, t_list_front, t_list_insert, t_list_insert_range, t_list_is_empty, t_list_is_list, t_list_is_size_of, t_list_join, t_list_list, t_list_offset, t_list_pop_back, t_list_pop_front, t_list_prepend, t_list_push_back, t_list_push_front, t_list_range, t_list_size, t_list_slice, t_list_sliding, t_list_swap_index, t_list_take, t_list_wrap_in_list)
t_number_as_bool = executable('as_bool', 'test/src/number/as_bool.cpp', dependencies: test_dep)
t_number_as_number = executable('as_number', 'test/src/number/as_number.cpp', dependencies: test_dep)
t_number_is_number = executable('is_number', 'test/src/number/is_number.cpp', dependencies: test_dep)
t_number_math = executable('math', 'test/src/number/math.cpp', dependencies: test_dep)
t_number_numbers = executable('numbers', 'test/src/number/numbers.cpp', dependencies: test_dep)
t_number_operators = executable('operators', 'test/src/number/operators.cpp', dependencies: test_dep)
t_number_to_bool = executable('to_bool', 'test/src/number/to_bool.cpp', dependencies: test_dep)
alias_target('mp.number', t_number_as_bool, t_number_as_number, t_number_is_number, t_number_math, t_number_numbers, t_number_operators, t_number_to_bool)
t_utility_alignof = executable('alignof', 'test/src/utility/alignof.cpp', dependencies: test_dep)
t_utility_always = executable('always', 'test/src/utility/always.cpp', dependencies: test_dep)
t_utility_conditional = executable('conditional', 'test/src/utility/conditional.cpp', dependencies: test_dep)
t_utility_has_type = executable('has_type', 'test/src/utility/has_type.cpp', dependencies: test_dep)
t_utility_is_instance_of = executable('is_instance_of', 'test/src/utility/is_instance_of.cpp', dependencies: test_dep)
t_utility_same_as = executable('same_as', 'test/src/utility/same_as.cpp', dependencies: test_dep)
t_utility_sizeof = executable('sizeof', 'test/src/utility/sizeof.cpp', dependencies: test_dep)
t_utility_stl_traits = executable('stl_traits', 'test/src/utility/stl_traits.cpp', dependencies: test_dep)
t_utility_unpack = executable('unpack', 'test/src/utility/unpack.cpp', dependencies: test_dep)
alias_target('mp.utility', t_utility_alignof, t_utility_always, t_utility_conditional, t_utility_has_type, t_utility_is_instance_of, t_utility_same_as, t_utility_sizeof, t_utility_stl_traits, t_utility_unpack)
t_value_as_val = executable('as_val', 'test/src/value/as_val.cpp', dependencies: test_dep)
t_value_has_value = executable('has_value', 'test/src/value/has_value.cpp', dependencies: test_dep)
t_value_is_val = executable('is_val', 'test/src/value/is_val.cpp', dependencies: test_dep)
t_value_operators = executable('operators_', 'test/src/value/operators.cpp', dependencies: test_dep)
t_value_values = executable('values', 'test/src/value/values.cpp', dependencies: test_dep)
alias_target('mp.value', t_value_as_val, t_value_has_value, t_value_is_val, t_value_operators, t_value_values)
alias_target('mp', t_algorithm_accumulate, t_algorithm_adjacent_difference, t_algorithm_adjacent_remove, t_algorithm_all_of, t_algorithm_any_of, t_algorithm_cartesian, t_algorithm_combine, t_algorithm_compare_with, t_algorithm_contains, t_algorithm_copy, t_algorithm_count, t_algorithm_find, t_algorithm_flatten, t_algorithm_fold_left, t_algorithm_fold_right, t_algorithm_group, t_algorithm_group_n, t_algorithm_index, t_algorithm_indices, t_algorithm_intersperse, t_algorithm_iota, t_algorithm_is_sorted, t_algorithm_is_unique, t_algorithm_lexicographical_compare, t_algorithm_lower_bound, t_algorithm_make_int_sequence, t_algorithm_matrix_shortest, t_algorithm_merge, t_algorithm_mismatch, t_algorithm_mismatch_index, t_algorithm_none_of, t_algorithm_partition, t_algorithm_permutations, t_algorithm_powerset, t_algorithm_remove, t_algorithm_repeat, t_algorithm_replace, t_algorithm_reverse, t_algorithm_rotate, t_algorithm_same, t_algorithm_sort, t_algorithm_split, t_algorithm_split_after, t_algorithm_split_at, t_algorithm_split_before, t_algorithm_take_while, t_algorithm_transform, t_algorithm_unique, t_algorithm_upper_bound, t_algorithm_zip, t_assume, t_functional_bind, t_functional_capture, t_functional_cascade, t_functional_compose, t_functional_each, t_functional_eval, t_functional_fix, t_functional_flip, t_functional_identity, t_functional_if, t_functional_invoke_twice, t_functional_is_invocable, t_functional_lift, t_functional_on, t_functional_partial, t_functional_recurse, t_functional_tee, t_functional_try, t_list_append, t_list_as_list, t_list_at, t_list_back, t_list_drop, t_list_erase, t_list_front, t_list_insert, t_list_insert_range, t_list_is_empty, t_list_is_list, t_list_is_size_of, t_list_join, t_list_list, t_list_offset, t_list_pop_back, t_list_pop_front, t_list_prepend, t_list_push_back, t_list_push_front, t_list_range, t_list_size, t_list_slice, t_list_sliding, t_list_swap_index, t_list_take, t_list_wrap_in_list, t_number_as_bool, t_number_as_number, t_number_is_number, t_number_math, t_number_numbers, t_number_operators, t_number_to_bool, t_utility_alignof, t_utility_always, t_utility_conditional, t_utility_has_type, t_utility_is_instance_of, t_utility_same_as, t_utility_sizeof, t_utility_stl_traits, t_utility_unpack, t_value_as_val, t_value_has_value, t_value_is_val, t_value_operators, t_value_values)
executable('check_inc', [
  'test/autogen/algorithm@accumulate.hpp.cpp',
  'test/autogen/algorithm@adjacent_difference.hpp.cpp',
  'test/autogen/algorithm@adjacent_remove.hpp.cpp',
  'test/autogen/algorithm@all_of.hpp.cpp',
  'test/autogen/algorithm@any_of.hpp.cpp',
  'test/autogen/algorithm@cartesian.hpp.cpp',
  'test/autogen/algorithm@combine.hpp.cpp',
  'test/autogen/algorithm@compare_with.hpp.cpp',
  'test/autogen/algorithm@contains.hpp.cpp',
  'test/autogen/algorithm@copy.hpp.cpp',
  'test/autogen/algorithm@count.hpp.cpp',
  'test/autogen/algorithm@find.hpp.cpp',
  'test/autogen/algorithm@flatten.hpp.cpp',
  'test/autogen/algorithm@fold_left.hpp.cpp',
  'test/autogen/algorithm@fold_right.hpp.cpp',
  'test/autogen/algorithm@group.hpp.cpp',
  'test/autogen/algorithm@group_n.hpp.cpp',
  'test/autogen/algorithm@index.hpp.cpp',
  'test/autogen/algorithm@indices.hpp.cpp',
  'test/autogen/algorithm@intersperse.hpp.cpp',
  'test/autogen/algorithm@iota.hpp.cpp',
  'test/autogen/algorithm@is_sorted.hpp.cpp',
  'test/autogen/algorithm@is_unique.hpp.cpp',
  'test/autogen/algorithm@lexicographical_compare.hpp.cpp',
  'test/autogen/algorithm@lower_bound.hpp.cpp',
  'test/autogen/algorithm@make_int_sequence.hpp.cpp',
  'test/autogen/algorithm@matrix_shortest.hpp.cpp',
  'test/autogen/algorithm@merge.hpp.cpp',
  'test/autogen/algorithm@mismatch.hpp.cpp',
  'test/autogen/algorithm@mismatch_index.hpp.cpp',
  'test/autogen/algorithm@none_of.hpp.cpp',
  'test/autogen/algorithm@partition.hpp.cpp',
  'test/autogen/algorithm@permutations.hpp.cpp',
  'test/autogen/algorithm@powerset.hpp.cpp',
  'test/autogen/algorithm@remove.hpp.cpp',
  'test/autogen/algorithm@repeat.hpp.cpp',
  'test/autogen/algorithm@replace.hpp.cpp',
  'test/autogen/algorithm@reverse.hpp.cpp',
  'test/autogen/algorithm@rotate.hpp.cpp',
  'test/autogen/algorithm@same.hpp.cpp',
  'test/autogen/algorithm@sort.hpp.cpp',
  'test/autogen/algorithm@split.hpp.cpp',
  'test/autogen/algorithm@split_after.hpp.cpp',
  'test/autogen/algorithm@split_at.hpp.cpp',
  'test/autogen/algorithm@split_before.hpp.cpp',
  'test/autogen/algorithm@take_while.hpp.cpp',
  'test/autogen/algorithm@transform.hpp.cpp',
  'test/autogen/algorithm@unique.hpp.cpp',
  'test/autogen/algorithm@upper_bound.hpp.cpp',
  'test/autogen/algorithm@zip.hpp.cpp',
  'test/autogen/config@config.hpp.cpp',
  'test/autogen/config@debug.hpp.cpp',
  'test/autogen/detail@enumerate.hpp.cpp',
  'test/autogen/detail@type_identity.hpp.cpp',
  'test/autogen/functional@bind.hpp.cpp',
  'test/autogen/functional@call.hpp.cpp',
  'test/autogen/functional@capture.hpp.cpp',
  'test/autogen/functional@cascade.hpp.cpp',
  'test/autogen/functional@compose.hpp.cpp',
  'test/autogen/functional@each.hpp.cpp',
  'test/autogen/functional@eval.hpp.cpp',
  'test/autogen/functional@fix.hpp.cpp',
  'test/autogen/functional@flip.hpp.cpp',
  'test/autogen/functional@identity.hpp.cpp',
  'test/autogen/functional@if.hpp.cpp',
  'test/autogen/functional@invoke_twice.hpp.cpp',
  'test/autogen/functional@is_invocable.hpp.cpp',
  'test/autogen/functional@lift.hpp.cpp',
  'test/autogen/functional@monadic.hpp.cpp',
  'test/autogen/functional@on.hpp.cpp',
  'test/autogen/functional@partial.hpp.cpp',
  'test/autogen/functional@recurse.hpp.cpp',
  'test/autogen/functional@tee.hpp.cpp',
  'test/autogen/functional@try.hpp.cpp',
  'test/autogen/list@append.hpp.cpp',
  'test/autogen/list@as_list.hpp.cpp',
  'test/autogen/list@at.hpp.cpp',
  'test/autogen/list@back.hpp.cpp',
  'test/autogen/list@drop.hpp.cpp',
  'test/autogen/list@erase.hpp.cpp',
  'test/autogen/list@front.hpp.cpp',
  'test/autogen/list@insert.hpp.cpp',
  'test/autogen/list@insert_range.hpp.cpp',
  'test/autogen/list@is_empty.hpp.cpp',
  'test/autogen/list@is_list.hpp.cpp',
  'test/autogen/list@is_size_of.hpp.cpp',
  'test/autogen/list@join.hpp.cpp',
  'test/autogen/list@list.hpp.cpp',
  'test/autogen/list@listify.hpp.cpp',
  'test/autogen/list@offset.hpp.cpp',
  'test/autogen/list@pop_back.hpp.cpp',
  'test/autogen/list@pop_front.hpp.cpp',
  'test/autogen/list@prepend.hpp.cpp',
  'test/autogen/list@push_back.hpp.cpp',
  'test/autogen/list@push_front.hpp.cpp',
  'test/autogen/list@range.hpp.cpp',
  'test/autogen/list@size.hpp.cpp',
  'test/autogen/list@slice.hpp.cpp',
  'test/autogen/list@sliding.hpp.cpp',
  'test/autogen/list@swap_index.hpp.cpp',
  'test/autogen/list@take.hpp.cpp',
  'test/autogen/list@wrap_in_list.hpp.cpp',
  'test/autogen/main.cpp',
  'test/autogen/number@as_bool.hpp.cpp',
  'test/autogen/number@as_number.hpp.cpp',
  'test/autogen/number@is_number.hpp.cpp',
  'test/autogen/number@math.hpp.cpp',
  'test/autogen/number@number.hpp.cpp',
  'test/autogen/number@numbers.hpp.cpp',
  'test/autogen/number@operators.hpp.cpp',
  'test/autogen/number@to_bool.hpp.cpp',
  'test/autogen/smp@algorithm@accumulate.hpp.cpp',
  'test/autogen/smp@algorithm@adjacent_difference.hpp.cpp',
  'test/autogen/smp@algorithm@adjacent_remove.hpp.cpp',
  'test/autogen/smp@algorithm@all_of.hpp.cpp',
  'test/autogen/smp@algorithm@any_of.hpp.cpp',
  'test/autogen/smp@algorithm@cartesian.hpp.cpp',
  'test/autogen/smp@algorithm@combine.hpp.cpp',
  'test/autogen/smp@algorithm@compare_with.hpp.cpp',
  'test/autogen/smp@algorithm@contains.hpp.cpp',
  'test/autogen/smp@algorithm@copy.hpp.cpp',
  'test/autogen/smp@algorithm@count.hpp.cpp',
  'test/autogen/smp@algorithm@find.hpp.cpp',
  'test/autogen/smp@algorithm@flatten.hpp.cpp',
  'test/autogen/smp@algorithm@fold_left.hpp.cpp',
  'test/autogen/smp@algorithm@fold_right.hpp.cpp',
  'test/autogen/smp@algorithm@group.hpp.cpp',
  'test/autogen/smp@algorithm@group_n.hpp.cpp',
  'test/autogen/smp@algorithm@index.hpp.cpp',
  'test/autogen/smp@algorithm@indices.hpp.cpp',
  'test/autogen/smp@algorithm@intersperse.hpp.cpp',
  'test/autogen/smp@algorithm@iota.hpp.cpp',
  'test/autogen/smp@algorithm@is_sorted.hpp.cpp',
  'test/autogen/smp@algorithm@is_unique.hpp.cpp',
  'test/autogen/smp@algorithm@lexicographical_compare.hpp.cpp',
  'test/autogen/smp@algorithm@lower_bound.hpp.cpp',
  'test/autogen/smp@algorithm@make_int_sequence.hpp.cpp',
  'test/autogen/smp@algorithm@matrix_shortest.hpp.cpp',
  'test/autogen/smp@algorithm@merge.hpp.cpp',
  'test/autogen/smp@algorithm@mismatch.hpp.cpp',
  'test/autogen/smp@algorithm@mismatch_index.hpp.cpp',
  'test/autogen/smp@algorithm@none_of.hpp.cpp',
  'test/autogen/smp@algorithm@partition.hpp.cpp',
  'test/autogen/smp@algorithm@permutations.hpp.cpp',
  'test/autogen/smp@algorithm@powerset.hpp.cpp',
  'test/autogen/smp@algorithm@remove.hpp.cpp',
  'test/autogen/smp@algorithm@repeat.hpp.cpp',
  'test/autogen/smp@algorithm@replace.hpp.cpp',
  'test/autogen/smp@algorithm@reverse.hpp.cpp',
  'test/autogen/smp@algorithm@rotate.hpp.cpp',
  'test/autogen/smp@algorithm@same.hpp.cpp',
  'test/autogen/smp@algorithm@sort.hpp.cpp',
  'test/autogen/smp@algorithm@split.hpp.cpp',
  'test/autogen/smp@algorithm@split_after.hpp.cpp',
  'test/autogen/smp@algorithm@split_at.hpp.cpp',
  'test/autogen/smp@algorithm@split_before.hpp.cpp',
  'test/autogen/smp@algorithm@take_while.hpp.cpp',
  'test/autogen/smp@algorithm@transform.hpp.cpp',
  'test/autogen/smp@algorithm@unique.hpp.cpp',
  'test/autogen/smp@algorithm@upper_bound.hpp.cpp',
  'test/autogen/smp@algorithm@zip.hpp.cpp',
  'test/autogen/smp@assume.hpp.cpp',
  'test/autogen/smp@concepts.hpp.cpp',
  'test/autogen/smp@contract.hpp.cpp',
  'test/autogen/smp@functional@bind.hpp.cpp',
  'test/autogen/smp@functional@capture.hpp.cpp',
  'test/autogen/smp@functional@cascade.hpp.cpp',
  'test/autogen/smp@functional@compose.hpp.cpp',
  'test/autogen/smp@functional@each.hpp.cpp',
  'test/autogen/smp@functional@eval.hpp.cpp',
  'test/autogen/smp@functional@fix.hpp.cpp',
  'test/autogen/smp@functional@flip.hpp.cpp',
  'test/autogen/smp@functional@identity.hpp.cpp',
  'test/autogen/smp@functional@if.hpp.cpp',
  'test/autogen/smp@functional@invoke_twice.hpp.cpp',
  'test/autogen/smp@functional@is_invocable.hpp.cpp',
  'test/autogen/smp@functional@lift.hpp.cpp',
  'test/autogen/smp@functional@on.hpp.cpp',
  'test/autogen/smp@functional@partial.hpp.cpp',
  'test/autogen/smp@functional@recurse.hpp.cpp',
  'test/autogen/smp@functional@sfinaefwd.hpp.cpp',
  'test/autogen/smp@functional@tee.hpp.cpp',
  'test/autogen/smp@list@append.hpp.cpp',
  'test/autogen/smp@list@as_list.hpp.cpp',
  'test/autogen/smp@list@at.hpp.cpp',
  'test/autogen/smp@list@back.hpp.cpp',
  'test/autogen/smp@list@drop.hpp.cpp',
  'test/autogen/smp@list@erase.hpp.cpp',
  'test/autogen/smp@list@front.hpp.cpp',
  'test/autogen/smp@list@insert.hpp.cpp',
  'test/autogen/smp@list@insert_range.hpp.cpp',
  'test/autogen/smp@list@is_empty.hpp.cpp',
  'test/autogen/smp@list@is_list.hpp.cpp',
  'test/autogen/smp@list@is_size_of.hpp.cpp',
  'test/autogen/smp@list@join.hpp.cpp',
  'test/autogen/smp@list@listify.hpp.cpp',
  'test/autogen/smp@list@offset.hpp.cpp',
  'test/autogen/smp@list@pop_back.hpp.cpp',
  'test/autogen/smp@list@pop_front.hpp.cpp',
  'test/autogen/smp@list@prepend.hpp.cpp',
  'test/autogen/smp@list@push_back.hpp.cpp',
  'test/autogen/smp@list@push_front.hpp.cpp',
  'test/autogen/smp@list@range.hpp.cpp',
  'test/autogen/smp@list@size.hpp.cpp',
  'test/autogen/smp@list@slice.hpp.cpp',
  'test/autogen/smp@list@sliding.hpp.cpp',
  'test/autogen/smp@list@swap_index.hpp.cpp',
  'test/autogen/smp@list@take.hpp.cpp',
  'test/autogen/smp@list@wrap_in_list.hpp.cpp',
  'test/autogen/smp@number@as_bool.hpp.cpp',
  'test/autogen/smp@number@as_number.hpp.cpp',
  'test/autogen/smp@number@is_number.hpp.cpp',
  'test/autogen/smp@number@math.hpp.cpp',
  'test/autogen/smp@number@numbers.hpp.cpp',
  'test/autogen/smp@number@operators.hpp.cpp',
  'test/autogen/smp@number@to_bool.hpp.cpp',
  'test/autogen/smp@sfinae.hpp.cpp',
  'test/autogen/smp@utility@alignof.hpp.cpp',
  'test/autogen/smp@utility@always.hpp.cpp',
  'test/autogen/smp@utility@conditional.hpp.cpp',
  'test/autogen/smp@utility@has_type.hpp.cpp',
  'test/autogen/smp@utility@is_instance_of.hpp.cpp',
  'test/autogen/smp@utility@same_as.hpp.cpp',
  'test/autogen/smp@utility@sizeof.hpp.cpp',
  'test/autogen/smp@utility@stl_traits.hpp.cpp',
  'test/autogen/smp@utility@unpack.hpp.cpp',
  'test/autogen/smp@value.hpp.cpp',
  'test/autogen/smp@value@as_val.hpp.cpp',
  'test/autogen/smp@value@has_value.hpp.cpp',
  'test/autogen/smp@value@is_val.hpp.cpp',
  'test/autogen/smp@value@operators.hpp.cpp',
  'test/autogen/smp@value@values.hpp.cpp',
  'test/autogen/utility@alignof.hpp.cpp',
  'test/autogen/utility@always.hpp.cpp',
  'test/autogen/utility@conditional.hpp.cpp',
  'test/autogen/utility@has_type.hpp.cpp',
  'test/autogen/utility@is_instance_of.hpp.cpp',
  'test/autogen/utility@same_as.hpp.cpp',
  'test/autogen/utility@sizeof.hpp.cpp',
  'test/autogen/utility@stl_traits.hpp.cpp',
  'test/autogen/utility@unpack.hpp.cpp',
  'test/autogen/value@as_val.hpp.cpp',
  'test/autogen/value@has_value.hpp.cpp',
  'test/autogen/value@is_val.hpp.cpp',
  'test/autogen/value@operators.hpp.cpp',
  'test/autogen/value@val.hpp.cpp',
  'test/autogen/value@values.hpp.cpp'
], dependencies: test_dep)
# stop tests
