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
t_algorithm_after = executable('after', 'test/src/algorithm/after.cpp', dependencies: test_dep)
t_algorithm_all_of = executable('all_of', 'test/src/algorithm/all_of.cpp', dependencies: test_dep)
t_algorithm_any_of = executable('any_of', 'test/src/algorithm/any_of.cpp', dependencies: test_dep)
t_algorithm_cartesian = executable('cartesian', 'test/src/algorithm/cartesian.cpp', dependencies: test_dep)
t_algorithm_combine = executable('combine', 'test/src/algorithm/combine.cpp', dependencies: test_dep)
t_algorithm_compare_with = executable('compare_with', 'test/src/algorithm/compare_with.cpp', dependencies: test_dep)
t_algorithm_contains = executable('contains', 'test/src/algorithm/contains.cpp', dependencies: test_dep)
t_algorithm_copy = executable('copy', 'test/src/algorithm/copy.cpp', dependencies: test_dep)
t_algorithm_count = executable('count', 'test/src/algorithm/count.cpp', dependencies: test_dep)
t_algorithm_drop_while = executable('drop_while', 'test/src/algorithm/drop_while.cpp', dependencies: test_dep)
t_algorithm_ends_with = executable('ends_with', 'test/src/algorithm/ends_with.cpp', dependencies: test_dep)
t_algorithm_find = executable('find', 'test/src/algorithm/find.cpp', dependencies: test_dep)
t_algorithm_find_last = executable('find_last', 'test/src/algorithm/find_last.cpp', dependencies: test_dep)
t_algorithm_flatten = executable('flatten', 'test/src/algorithm/flatten.cpp', dependencies: test_dep)
t_algorithm_fold_left = executable('fold_left', 'test/src/algorithm/fold_left.cpp', dependencies: test_dep)
t_algorithm_fold_right = executable('fold_right', 'test/src/algorithm/fold_right.cpp', dependencies: test_dep)
t_algorithm_fold_tree = executable('fold_tree', 'test/src/algorithm/fold_tree.cpp', dependencies: test_dep)
t_algorithm_group = executable('group', 'test/src/algorithm/group.cpp', dependencies: test_dep)
t_algorithm_group_n = executable('group_n', 'test/src/algorithm/group_n.cpp', dependencies: test_dep)
t_algorithm_index = executable('index', 'test/src/algorithm/index.cpp', dependencies: test_dep)
t_algorithm_indices = executable('indices', 'test/src/algorithm/indices.cpp', dependencies: test_dep)
t_algorithm_intersperse = executable('intersperse', 'test/src/algorithm/intersperse.cpp', dependencies: test_dep)
t_algorithm_iota = executable('iota', 'test/src/algorithm/iota.cpp', dependencies: test_dep)
t_algorithm_is_disjoint = executable('is_disjoint', 'test/src/algorithm/is_disjoint.cpp', dependencies: test_dep)
t_algorithm_is_sorted = executable('is_sorted', 'test/src/algorithm/is_sorted.cpp', dependencies: test_dep)
t_algorithm_is_subset = executable('is_subset', 'test/src/algorithm/is_subset.cpp', dependencies: test_dep)
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
t_algorithm_prefix = executable('prefix', 'test/src/algorithm/prefix.cpp', dependencies: test_dep)
t_algorithm_remove = executable('remove', 'test/src/algorithm/remove.cpp', dependencies: test_dep)
t_algorithm_repeat = executable('repeat', 'test/src/algorithm/repeat.cpp', dependencies: test_dep)
t_algorithm_replace = executable('replace', 'test/src/algorithm/replace.cpp', dependencies: test_dep)
t_algorithm_reverse = executable('reverse', 'test/src/algorithm/reverse.cpp', dependencies: test_dep)
t_algorithm_reverse_fold = executable('reverse_fold', 'test/src/algorithm/reverse_fold.cpp', dependencies: test_dep)
t_algorithm_rotate = executable('rotate', 'test/src/algorithm/rotate.cpp', dependencies: test_dep)
t_algorithm_same = executable('same', 'test/src/algorithm/same.cpp', dependencies: test_dep)
t_algorithm_scan_left = executable('scan_left', 'test/src/algorithm/scan_left.cpp', dependencies: test_dep)
t_algorithm_scan_right = executable('scan_right', 'test/src/algorithm/scan_right.cpp', dependencies: test_dep)
t_algorithm_search = executable('search', 'test/src/algorithm/search.cpp', dependencies: test_dep)
t_algorithm_sort = executable('sort', 'test/src/algorithm/sort.cpp', dependencies: test_dep)
t_algorithm_split = executable('split', 'test/src/algorithm/split.cpp', dependencies: test_dep)
t_algorithm_split_after = executable('split_after', 'test/src/algorithm/split_after.cpp', dependencies: test_dep)
t_algorithm_split_at = executable('split_at', 'test/src/algorithm/split_at.cpp', dependencies: test_dep)
t_algorithm_split_before = executable('split_before', 'test/src/algorithm/split_before.cpp', dependencies: test_dep)
t_algorithm_split_by = executable('split_by', 'test/src/algorithm/split_by.cpp', dependencies: test_dep)
t_algorithm_starts_with = executable('starts_with', 'test/src/algorithm/starts_with.cpp', dependencies: test_dep)
t_algorithm_suffix = executable('suffix', 'test/src/algorithm/suffix.cpp', dependencies: test_dep)
t_algorithm_take_while = executable('take_while', 'test/src/algorithm/take_while.cpp', dependencies: test_dep)
t_algorithm_transform = executable('transform', 'test/src/algorithm/transform.cpp', dependencies: test_dep)
t_algorithm_unique = executable('unique', 'test/src/algorithm/unique.cpp', dependencies: test_dep)
t_algorithm_upper_bound = executable('upper_bound', 'test/src/algorithm/upper_bound.cpp', dependencies: test_dep)
t_algorithm_zip = executable('zip', 'test/src/algorithm/zip.cpp', dependencies: test_dep)
alias_target('mp.algorithm', t_algorithm_accumulate, t_algorithm_adjacent_difference, t_algorithm_adjacent_remove, t_algorithm_after, t_algorithm_all_of, t_algorithm_any_of, t_algorithm_cartesian, t_algorithm_combine, t_algorithm_compare_with, t_algorithm_contains, t_algorithm_copy, t_algorithm_count, t_algorithm_drop_while, t_algorithm_ends_with, t_algorithm_find, t_algorithm_find_last, t_algorithm_flatten, t_algorithm_fold_left, t_algorithm_fold_right, t_algorithm_fold_tree, t_algorithm_group, t_algorithm_group_n, t_algorithm_index, t_algorithm_indices, t_algorithm_intersperse, t_algorithm_iota, t_algorithm_is_disjoint, t_algorithm_is_sorted, t_algorithm_is_subset, t_algorithm_is_unique, t_algorithm_lexicographical_compare, t_algorithm_lower_bound, t_algorithm_make_int_sequence, t_algorithm_matrix_shortest, t_algorithm_merge, t_algorithm_mismatch, t_algorithm_mismatch_index, t_algorithm_none_of, t_algorithm_partition, t_algorithm_permutations, t_algorithm_powerset, t_algorithm_prefix, t_algorithm_remove, t_algorithm_repeat, t_algorithm_replace, t_algorithm_reverse, t_algorithm_reverse_fold, t_algorithm_rotate, t_algorithm_same, t_algorithm_scan_left, t_algorithm_scan_right, t_algorithm_search, t_algorithm_sort, t_algorithm_split, t_algorithm_split_after, t_algorithm_split_at, t_algorithm_split_before, t_algorithm_split_by, t_algorithm_starts_with, t_algorithm_suffix, t_algorithm_take_while, t_algorithm_transform, t_algorithm_unique, t_algorithm_upper_bound, t_algorithm_zip)
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
t_functional_not_fn = executable('not_fn', 'test/src/functional/not_fn.cpp', dependencies: test_dep)
t_functional_on = executable('on', 'test/src/functional/on.cpp', dependencies: test_dep)
t_functional_partial = executable('partial', 'test/src/functional/partial.cpp', dependencies: test_dep)
t_functional_recursively = executable('recursively', 'test/src/functional/recursively.cpp', dependencies: test_dep)
t_functional_tee = executable('tee', 'test/src/functional/tee.cpp', dependencies: test_dep)
t_functional_try = executable('try', 'test/src/functional/try.cpp', dependencies: test_dep)
t_functional_while = executable('while', 'test/src/functional/while.cpp', dependencies: test_dep)
alias_target('mp.functional', t_functional_bind, t_functional_capture, t_functional_cascade, t_functional_compose, t_functional_each, t_functional_eval, t_functional_fix, t_functional_flip, t_functional_identity, t_functional_if, t_functional_invoke_twice, t_functional_is_invocable, t_functional_lift, t_functional_not_fn, t_functional_on, t_functional_partial, t_functional_recursively, t_functional_tee, t_functional_try, t_functional_while)
t_list_append = executable('append', 'test/src/list/append.cpp', dependencies: test_dep)
t_list_as_list = executable('as_list', 'test/src/list/as_list.cpp', dependencies: test_dep)
t_list_at = executable('at', 'test/src/list/at.cpp', dependencies: test_dep)
t_list_back = executable('back', 'test/src/list/back.cpp', dependencies: test_dep)
t_list_clear = executable('clear', 'test/src/list/clear.cpp', dependencies: test_dep)
t_list_drop_back = executable('drop_back', 'test/src/list/drop_back.cpp', dependencies: test_dep)
t_list_drop_front = executable('drop_front', 'test/src/list/drop_front.cpp', dependencies: test_dep)
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
t_list_take_back = executable('take_back', 'test/src/list/take_back.cpp', dependencies: test_dep)
t_list_take_front = executable('take_front', 'test/src/list/take_front.cpp', dependencies: test_dep)
t_list_wrap_in_list = executable('wrap_in_list', 'test/src/list/wrap_in_list.cpp', dependencies: test_dep)
alias_target('mp.list', t_list_append, t_list_as_list, t_list_at, t_list_back, t_list_clear, t_list_drop_back, t_list_drop_front, t_list_erase, t_list_front, t_list_insert, t_list_insert_range, t_list_is_empty, t_list_is_list, t_list_is_size_of, t_list_join, t_list_list, t_list_offset, t_list_pop_back, t_list_pop_front, t_list_prepend, t_list_push_back, t_list_push_front, t_list_range, t_list_size, t_list_slice, t_list_sliding, t_list_swap_index, t_list_take_back, t_list_take_front, t_list_wrap_in_list)
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
t_utility_has_value_type = executable('has_value_type', 'test/src/utility/has_value_type.cpp', dependencies: test_dep)
t_utility_is = executable('is', 'test/src/utility/is.cpp', dependencies: test_dep)
t_utility_is_not = executable('is_not', 'test/src/utility/is_not.cpp', dependencies: test_dep)
t_utility_is_specialization_of = executable('is_specialization_of', 'test/src/utility/is_specialization_of.cpp', dependencies: test_dep)
t_utility_iterate = executable('iterate', 'test/src/utility/iterate.cpp', dependencies: test_dep)
t_utility_sizeof = executable('sizeof', 'test/src/utility/sizeof.cpp', dependencies: test_dep)
t_utility_stl_traits = executable('stl_traits', 'test/src/utility/stl_traits.cpp', dependencies: test_dep)
t_utility_type = executable('type', 'test/src/utility/type.cpp', dependencies: test_dep)
t_utility_unpack = executable('unpack', 'test/src/utility/unpack.cpp', dependencies: test_dep)
t_utility_value_type = executable('value_type', 'test/src/utility/value_type.cpp', dependencies: test_dep)
alias_target('mp.utility', t_utility_alignof, t_utility_always, t_utility_conditional, t_utility_has_type, t_utility_has_value_type, t_utility_is, t_utility_is_not, t_utility_is_specialization_of, t_utility_iterate, t_utility_sizeof, t_utility_stl_traits, t_utility_type, t_utility_unpack, t_utility_value_type)
t_value_as_val = executable('as_val', 'test/src/value/as_val.cpp', dependencies: test_dep)
t_value_has_value = executable('has_value', 'test/src/value/has_value.cpp', dependencies: test_dep)
t_value_is_val = executable('is_val', 'test/src/value/is_val.cpp', dependencies: test_dep)
t_value_operators = executable('operators_', 'test/src/value/operators.cpp', dependencies: test_dep)
t_value_values = executable('values', 'test/src/value/values.cpp', dependencies: test_dep)
alias_target('mp.value', t_value_as_val, t_value_has_value, t_value_is_val, t_value_operators, t_value_values)
alias_target('mp', t_algorithm_accumulate, t_algorithm_adjacent_difference, t_algorithm_adjacent_remove, t_algorithm_after, t_algorithm_all_of, t_algorithm_any_of, t_algorithm_cartesian, t_algorithm_combine, t_algorithm_compare_with, t_algorithm_contains, t_algorithm_copy, t_algorithm_count, t_algorithm_drop_while, t_algorithm_ends_with, t_algorithm_find, t_algorithm_find_last, t_algorithm_flatten, t_algorithm_fold_left, t_algorithm_fold_right, t_algorithm_fold_tree, t_algorithm_group, t_algorithm_group_n, t_algorithm_index, t_algorithm_indices, t_algorithm_intersperse, t_algorithm_iota, t_algorithm_is_disjoint, t_algorithm_is_sorted, t_algorithm_is_subset, t_algorithm_is_unique, t_algorithm_lexicographical_compare, t_algorithm_lower_bound, t_algorithm_make_int_sequence, t_algorithm_matrix_shortest, t_algorithm_merge, t_algorithm_mismatch, t_algorithm_mismatch_index, t_algorithm_none_of, t_algorithm_partition, t_algorithm_permutations, t_algorithm_powerset, t_algorithm_prefix, t_algorithm_remove, t_algorithm_repeat, t_algorithm_replace, t_algorithm_reverse, t_algorithm_reverse_fold, t_algorithm_rotate, t_algorithm_same, t_algorithm_scan_left, t_algorithm_scan_right, t_algorithm_search, t_algorithm_sort, t_algorithm_split, t_algorithm_split_after, t_algorithm_split_at, t_algorithm_split_before, t_algorithm_split_by, t_algorithm_starts_with, t_algorithm_suffix, t_algorithm_take_while, t_algorithm_transform, t_algorithm_unique, t_algorithm_upper_bound, t_algorithm_zip, t_assume, t_functional_bind, t_functional_capture, t_functional_cascade, t_functional_compose, t_functional_each, t_functional_eval, t_functional_fix, t_functional_flip, t_functional_identity, t_functional_if, t_functional_invoke_twice, t_functional_is_invocable, t_functional_lift, t_functional_not_fn, t_functional_on, t_functional_partial, t_functional_recursively, t_functional_tee, t_functional_try, t_functional_while, t_list_append, t_list_as_list, t_list_at, t_list_back, t_list_clear, t_list_drop_back, t_list_drop_front, t_list_erase, t_list_front, t_list_insert, t_list_insert_range, t_list_is_empty, t_list_is_list, t_list_is_size_of, t_list_join, t_list_list, t_list_offset, t_list_pop_back, t_list_pop_front, t_list_prepend, t_list_push_back, t_list_push_front, t_list_range, t_list_size, t_list_slice, t_list_sliding, t_list_swap_index, t_list_take_back, t_list_take_front, t_list_wrap_in_list, t_number_as_bool, t_number_as_number, t_number_is_number, t_number_math, t_number_numbers, t_number_operators, t_number_to_bool, t_utility_alignof, t_utility_always, t_utility_conditional, t_utility_has_type, t_utility_has_value_type, t_utility_is, t_utility_is_not, t_utility_is_specialization_of, t_utility_iterate, t_utility_sizeof, t_utility_stl_traits, t_utility_type, t_utility_unpack, t_utility_value_type, t_value_as_val, t_value_has_value, t_value_is_val, t_value_operators, t_value_values)
executable('check_inc', [
  'test/autogen/algorithm@accumulate.cpp',
  'test/autogen/algorithm@adjacent_difference.cpp',
  'test/autogen/algorithm@adjacent_remove.cpp',
  'test/autogen/algorithm@after.cpp',
  'test/autogen/algorithm@all_of.cpp',
  'test/autogen/algorithm@any_of.cpp',
  'test/autogen/algorithm@cartesian.cpp',
  'test/autogen/algorithm@combine.cpp',
  'test/autogen/algorithm@compare_with.cpp',
  'test/autogen/algorithm@contains.cpp',
  'test/autogen/algorithm@copy.cpp',
  'test/autogen/algorithm@count.cpp',
  'test/autogen/algorithm@drop_while.cpp',
  'test/autogen/algorithm@ends_with.cpp',
  'test/autogen/algorithm@find.cpp',
  'test/autogen/algorithm@find_last.cpp',
  'test/autogen/algorithm@flatten.cpp',
  'test/autogen/algorithm@fold_left.cpp',
  'test/autogen/algorithm@fold_right.cpp',
  'test/autogen/algorithm@fold_tree.cpp',
  'test/autogen/algorithm@group.cpp',
  'test/autogen/algorithm@group_n.cpp',
  'test/autogen/algorithm@index.cpp',
  'test/autogen/algorithm@indices.cpp',
  'test/autogen/algorithm@intersperse.cpp',
  'test/autogen/algorithm@iota.cpp',
  'test/autogen/algorithm@is_disjoint.cpp',
  'test/autogen/algorithm@is_sorted.cpp',
  'test/autogen/algorithm@is_subset.cpp',
  'test/autogen/algorithm@is_unique.cpp',
  'test/autogen/algorithm@lexicographical_compare.cpp',
  'test/autogen/algorithm@lower_bound.cpp',
  'test/autogen/algorithm@make_int_sequence.cpp',
  'test/autogen/algorithm@matrix_shortest.cpp',
  'test/autogen/algorithm@merge.cpp',
  'test/autogen/algorithm@mismatch.cpp',
  'test/autogen/algorithm@mismatch_index.cpp',
  'test/autogen/algorithm@none_of.cpp',
  'test/autogen/algorithm@partition.cpp',
  'test/autogen/algorithm@permutations.cpp',
  'test/autogen/algorithm@powerset.cpp',
  'test/autogen/algorithm@prefix.cpp',
  'test/autogen/algorithm@remove.cpp',
  'test/autogen/algorithm@repeat.cpp',
  'test/autogen/algorithm@replace.cpp',
  'test/autogen/algorithm@reverse.cpp',
  'test/autogen/algorithm@reverse_fold.cpp',
  'test/autogen/algorithm@rotate.cpp',
  'test/autogen/algorithm@same.cpp',
  'test/autogen/algorithm@scan_left.cpp',
  'test/autogen/algorithm@scan_right.cpp',
  'test/autogen/algorithm@search.cpp',
  'test/autogen/algorithm@sort.cpp',
  'test/autogen/algorithm@split.cpp',
  'test/autogen/algorithm@split_after.cpp',
  'test/autogen/algorithm@split_at.cpp',
  'test/autogen/algorithm@split_before.cpp',
  'test/autogen/algorithm@split_by.cpp',
  'test/autogen/algorithm@starts_with.cpp',
  'test/autogen/algorithm@suffix.cpp',
  'test/autogen/algorithm@take_while.cpp',
  'test/autogen/algorithm@transform.cpp',
  'test/autogen/algorithm@unique.cpp',
  'test/autogen/algorithm@upper_bound.cpp',
  'test/autogen/algorithm@zip.cpp',
  'test/autogen/detail@type_identity.cpp',
  'test/autogen/detail@enumerate.cpp',
  'test/autogen/error.cpp',
  'test/autogen/functional@bind.cpp',
  'test/autogen/functional@call.cpp',
  'test/autogen/functional@capture.cpp',
  'test/autogen/functional@cascade.cpp',
  'test/autogen/functional@compose.cpp',
  'test/autogen/functional@each.cpp',
  'test/autogen/functional@eval.cpp',
  'test/autogen/functional@fix.cpp',
  'test/autogen/functional@flip.cpp',
  'test/autogen/functional@identity.cpp',
  'test/autogen/functional@if.cpp',
  'test/autogen/functional@invoke_twice.cpp',
  'test/autogen/functional@is_invocable.cpp',
  'test/autogen/functional@lift.cpp',
  'test/autogen/functional@monadic.cpp',
  'test/autogen/functional@not_fn.cpp',
  'test/autogen/functional@on.cpp',
  'test/autogen/functional@partial.cpp',
  'test/autogen/functional@recursively.cpp',
  'test/autogen/functional@tee.cpp',
  'test/autogen/functional@try.cpp',
  'test/autogen/functional@while.cpp',
  'test/autogen/list@append.cpp',
  'test/autogen/list@as_list.cpp',
  'test/autogen/list@at.cpp',
  'test/autogen/list@back.cpp',
  'test/autogen/list@clear.cpp',
  'test/autogen/list@drop_back.cpp',
  'test/autogen/list@drop_front.cpp',
  'test/autogen/list@erase.cpp',
  'test/autogen/list@front.cpp',
  'test/autogen/list@insert.cpp',
  'test/autogen/list@insert_range.cpp',
  'test/autogen/list@is_empty.cpp',
  'test/autogen/list@is_list.cpp',
  'test/autogen/list@is_size_of.cpp',
  'test/autogen/list@join.cpp',
  'test/autogen/list@list.cpp',
  'test/autogen/list@listify.cpp',
  'test/autogen/list@offset.cpp',
  'test/autogen/list@pop_back.cpp',
  'test/autogen/list@pop_front.cpp',
  'test/autogen/list@prepend.cpp',
  'test/autogen/list@push_back.cpp',
  'test/autogen/list@push_front.cpp',
  'test/autogen/list@range.cpp',
  'test/autogen/list@size.cpp',
  'test/autogen/list@slice.cpp',
  'test/autogen/list@sliding.cpp',
  'test/autogen/list@swap_index.cpp',
  'test/autogen/list@take_back.cpp',
  'test/autogen/list@take_front.cpp',
  'test/autogen/list@wrap_in_list.cpp',
  'test/autogen/number@as_bool.cpp',
  'test/autogen/number@as_number.cpp',
  'test/autogen/number@is_number.cpp',
  'test/autogen/number@math.cpp',
  'test/autogen/number@number.cpp',
  'test/autogen/number@numbers.cpp',
  'test/autogen/number@operators.cpp',
  'test/autogen/number@to_bool.cpp',
  'test/autogen/utility@alignof.cpp',
  'test/autogen/utility@always.cpp',
  'test/autogen/utility@conditional.cpp',
  'test/autogen/utility@has_type.cpp',
  'test/autogen/utility@has_value_type.cpp',
  'test/autogen/utility@is.cpp',
  'test/autogen/utility@is_not.cpp',
  'test/autogen/utility@is_specialization_of.cpp',
  'test/autogen/utility@iterate.cpp',
  'test/autogen/utility@sizeof.cpp',
  'test/autogen/utility@stl_traits.cpp',
  'test/autogen/utility@type.cpp',
  'test/autogen/utility@unpack.cpp',
  'test/autogen/utility@value_type.cpp',
  'test/autogen/value@as_val.cpp',
  'test/autogen/value@has_value.cpp',
  'test/autogen/value@is_val.cpp',
  'test/autogen/value@operators.cpp',
  'test/autogen/value@val.cpp',
  'test/autogen/value@values.cpp',
  'test/autogen/smp@algorithm@accumulate.cpp',
  'test/autogen/smp@algorithm@adjacent_difference.cpp',
  'test/autogen/smp@algorithm@adjacent_remove.cpp',
  'test/autogen/smp@algorithm@after.cpp',
  'test/autogen/smp@algorithm@all_of.cpp',
  'test/autogen/smp@algorithm@any_of.cpp',
  'test/autogen/smp@algorithm@cartesian.cpp',
  'test/autogen/smp@algorithm@combine.cpp',
  'test/autogen/smp@algorithm@compare_with.cpp',
  'test/autogen/smp@algorithm@contains.cpp',
  'test/autogen/smp@algorithm@copy.cpp',
  'test/autogen/smp@algorithm@count.cpp',
  'test/autogen/smp@algorithm@drop_while.cpp',
  'test/autogen/smp@algorithm@ends_with.cpp',
  'test/autogen/smp@algorithm@find.cpp',
  'test/autogen/smp@algorithm@find_last.cpp',
  'test/autogen/smp@algorithm@flatten.cpp',
  'test/autogen/smp@algorithm@fold_left.cpp',
  'test/autogen/smp@algorithm@fold_right.cpp',
  'test/autogen/smp@algorithm@fold_tree.cpp',
  'test/autogen/smp@algorithm@group.cpp',
  'test/autogen/smp@algorithm@group_n.cpp',
  'test/autogen/smp@algorithm@index.cpp',
  'test/autogen/smp@algorithm@indices.cpp',
  'test/autogen/smp@algorithm@intersperse.cpp',
  'test/autogen/smp@algorithm@iota.cpp',
  'test/autogen/smp@algorithm@is_disjoint.cpp',
  'test/autogen/smp@algorithm@is_sorted.cpp',
  'test/autogen/smp@algorithm@is_subset.cpp',
  'test/autogen/smp@algorithm@is_unique.cpp',
  'test/autogen/smp@algorithm@lexicographical_compare.cpp',
  'test/autogen/smp@algorithm@lower_bound.cpp',
  'test/autogen/smp@algorithm@make_int_sequence.cpp',
  'test/autogen/smp@algorithm@matrix_shortest.cpp',
  'test/autogen/smp@algorithm@merge.cpp',
  'test/autogen/smp@algorithm@mismatch.cpp',
  'test/autogen/smp@algorithm@mismatch_index.cpp',
  'test/autogen/smp@algorithm@none_of.cpp',
  'test/autogen/smp@algorithm@partition.cpp',
  'test/autogen/smp@algorithm@permutations.cpp',
  'test/autogen/smp@algorithm@powerset.cpp',
  'test/autogen/smp@algorithm@prefix.cpp',
  'test/autogen/smp@algorithm@remove.cpp',
  'test/autogen/smp@algorithm@repeat.cpp',
  'test/autogen/smp@algorithm@replace.cpp',
  'test/autogen/smp@algorithm@reverse.cpp',
  'test/autogen/smp@algorithm@reverse_fold.cpp',
  'test/autogen/smp@algorithm@rotate.cpp',
  'test/autogen/smp@algorithm@same.cpp',
  'test/autogen/smp@algorithm@scan_left.cpp',
  'test/autogen/smp@algorithm@scan_right.cpp',
  'test/autogen/smp@algorithm@search.cpp',
  'test/autogen/smp@algorithm@sort.cpp',
  'test/autogen/smp@algorithm@split.cpp',
  'test/autogen/smp@algorithm@split_after.cpp',
  'test/autogen/smp@algorithm@split_at.cpp',
  'test/autogen/smp@algorithm@split_before.cpp',
  'test/autogen/smp@algorithm@split_by.cpp',
  'test/autogen/smp@algorithm@starts_with.cpp',
  'test/autogen/smp@algorithm@suffix.cpp',
  'test/autogen/smp@algorithm@take_while.cpp',
  'test/autogen/smp@algorithm@transform.cpp',
  'test/autogen/smp@algorithm@unique.cpp',
  'test/autogen/smp@algorithm@upper_bound.cpp',
  'test/autogen/smp@algorithm@zip.cpp',
  'test/autogen/smp@assume.cpp',
  'test/autogen/smp@concepts.cpp',
  'test/autogen/smp@contract.cpp',
  'test/autogen/smp@functional@bind.cpp',
  'test/autogen/smp@functional@capture.cpp',
  'test/autogen/smp@functional@cascade.cpp',
  'test/autogen/smp@functional@compose.cpp',
  'test/autogen/smp@functional@each.cpp',
  'test/autogen/smp@functional@eval.cpp',
  'test/autogen/smp@functional@fix.cpp',
  'test/autogen/smp@functional@flip.cpp',
  'test/autogen/smp@functional@identity.cpp',
  'test/autogen/smp@functional@if.cpp',
  'test/autogen/smp@functional@invoke_twice.cpp',
  'test/autogen/smp@functional@is_invocable.cpp',
  'test/autogen/smp@functional@lift.cpp',
  'test/autogen/smp@functional@not_fn.cpp',
  'test/autogen/smp@functional@on.cpp',
  'test/autogen/smp@functional@partial.cpp',
  'test/autogen/smp@functional@recursively.cpp',
  'test/autogen/smp@functional@sfinaefwd.cpp',
  'test/autogen/smp@functional@tee.cpp',
  'test/autogen/smp@functional@while.cpp',
  'test/autogen/smp@list@append.cpp',
  'test/autogen/smp@list@as_list.cpp',
  'test/autogen/smp@list@at.cpp',
  'test/autogen/smp@list@back.cpp',
  'test/autogen/smp@list@clear.cpp',
  'test/autogen/smp@list@drop_back.cpp',
  'test/autogen/smp@list@drop_front.cpp',
  'test/autogen/smp@list@erase.cpp',
  'test/autogen/smp@list@front.cpp',
  'test/autogen/smp@list@insert.cpp',
  'test/autogen/smp@list@insert_range.cpp',
  'test/autogen/smp@list@is_empty.cpp',
  'test/autogen/smp@list@is_list.cpp',
  'test/autogen/smp@list@is_size_of.cpp',
  'test/autogen/smp@list@join.cpp',
  'test/autogen/smp@list@listify.cpp',
  'test/autogen/smp@list@offset.cpp',
  'test/autogen/smp@list@pop_back.cpp',
  'test/autogen/smp@list@pop_front.cpp',
  'test/autogen/smp@list@prepend.cpp',
  'test/autogen/smp@list@push_back.cpp',
  'test/autogen/smp@list@push_front.cpp',
  'test/autogen/smp@list@range.cpp',
  'test/autogen/smp@list@size.cpp',
  'test/autogen/smp@list@slice.cpp',
  'test/autogen/smp@list@sliding.cpp',
  'test/autogen/smp@list@swap_index.cpp',
  'test/autogen/smp@list@take_back.cpp',
  'test/autogen/smp@list@take_front.cpp',
  'test/autogen/smp@list@wrap_in_list.cpp',
  'test/autogen/smp@number@as_bool.cpp',
  'test/autogen/smp@number@as_number.cpp',
  'test/autogen/smp@number@is_number.cpp',
  'test/autogen/smp@number@math.cpp',
  'test/autogen/smp@number@numbers.cpp',
  'test/autogen/smp@number@operators.cpp',
  'test/autogen/smp@number@to_bool.cpp',
  'test/autogen/smp@sfinae.cpp',
  'test/autogen/smp@utility@alignof.cpp',
  'test/autogen/smp@utility@always.cpp',
  'test/autogen/smp@utility@conditional.cpp',
  'test/autogen/smp@utility@has_type.cpp',
  'test/autogen/smp@utility@has_value_type.cpp',
  'test/autogen/smp@utility@is.cpp',
  'test/autogen/smp@utility@is_not.cpp',
  'test/autogen/smp@utility@is_specialization_of.cpp',
  'test/autogen/smp@utility@iterate.cpp',
  'test/autogen/smp@utility@sizeof.cpp',
  'test/autogen/smp@utility@stl_traits.cpp',
  'test/autogen/smp@utility@type.cpp',
  'test/autogen/smp@utility@unpack.cpp',
  'test/autogen/smp@utility@value_type.cpp',
  'test/autogen/smp@value@as_val.cpp',
  'test/autogen/smp@value@has_value.cpp',
  'test/autogen/smp@value@is_val.cpp',
  'test/autogen/smp@value@operators.cpp',
  'test/autogen/smp@value@values.cpp',
  'test/autogen/main.cpp'
], dependencies: test_dep)
# stop tests
