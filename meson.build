project('jln.mp', 'cpp', default_options : ['cpp_std=c++17'])

if get_option('mp_debug')
  add_global_arguments('-DJLN_MP_ENABLE_DEBUG=1', language : 'cpp')
endif

jln_default_flags = {}
sys = build_machine.system()
# quick compilation
if sys != 'darwin' and sys != 'windows'
  jln_default_flags = {
    'debug': 'off',
    'whole_program': 'strip_all',
  }
endif

subdir('meson_jln_flags')
add_global_arguments(jln_cpp_flags, language:'cpp')
add_global_link_arguments(jln_link_flags, language:'cpp')

test_dep = declare_dependency(include_directories: include_directories('test/include', 'include'))

executable('mp_test', 'test/mp.cpp', dependencies: test_dep)

# start tests
t_0_0 = executable('is_instance_of', 'test/src/utility/is_instance_of.cpp', dependencies: test_dep, build_by_default: false)
t_0_1 = executable('conditional', 'test/src/utility/conditional.cpp', dependencies: test_dep, build_by_default: false)
t_0_2 = executable('always', 'test/src/utility/always.cpp', dependencies: test_dep, build_by_default: false)
t_0_3 = executable('same_as', 'test/src/utility/same_as.cpp', dependencies: test_dep, build_by_default: false)
t_0_4 = executable('unpack', 'test/src/utility/unpack.cpp', dependencies: test_dep, build_by_default: false)
t_0_5 = executable('has_type', 'test/src/utility/has_type.cpp', dependencies: test_dep, build_by_default: false)
alias_target('mp.utility', t_0_0, t_0_1, t_0_2, t_0_3, t_0_4, t_0_5)
t_1_0 = executable('iota', 'test/src/algorithm/iota.cpp', dependencies: test_dep, build_by_default: false)
t_1_1 = executable('take_while', 'test/src/algorithm/take_while.cpp', dependencies: test_dep, build_by_default: false)
t_1_2 = executable('fold_left', 'test/src/algorithm/fold_left.cpp', dependencies: test_dep, build_by_default: false)
t_1_3 = executable('indices', 'test/src/algorithm/indices.cpp', dependencies: test_dep, build_by_default: false)
t_1_4 = executable('lower_bound', 'test/src/algorithm/lower_bound.cpp', dependencies: test_dep, build_by_default: false)
t_1_5 = executable('contains', 'test/src/algorithm/contains.cpp', dependencies: test_dep, build_by_default: false)
t_1_6 = executable('reverse', 'test/src/algorithm/reverse.cpp', dependencies: test_dep, build_by_default: false)
t_1_7 = executable('flatten', 'test/src/algorithm/flatten.cpp', dependencies: test_dep, build_by_default: false)
t_1_8 = executable('index', 'test/src/algorithm/index.cpp', dependencies: test_dep, build_by_default: false)
t_1_9 = executable('sort', 'test/src/algorithm/sort.cpp', dependencies: test_dep, build_by_default: false)
t_1_10 = executable('accumulate', 'test/src/algorithm/accumulate.cpp', dependencies: test_dep, build_by_default: false)
t_1_11 = executable('partition', 'test/src/algorithm/partition.cpp', dependencies: test_dep, build_by_default: false)
t_1_12 = executable('unique', 'test/src/algorithm/unique.cpp', dependencies: test_dep, build_by_default: false)
t_1_13 = executable('is_unique', 'test/src/algorithm/is_unique.cpp', dependencies: test_dep, build_by_default: false)
t_1_14 = executable('is_sorted', 'test/src/algorithm/is_sorted.cpp', dependencies: test_dep, build_by_default: false)
t_1_15 = executable('permutations', 'test/src/algorithm/permutations.cpp', dependencies: test_dep, build_by_default: false)
t_1_16 = executable('same', 'test/src/algorithm/same.cpp', dependencies: test_dep, build_by_default: false)
t_1_17 = executable('all_of', 'test/src/algorithm/all_of.cpp', dependencies: test_dep, build_by_default: false)
t_1_18 = executable('cartesian', 'test/src/algorithm/cartesian.cpp', dependencies: test_dep, build_by_default: false)
t_1_19 = executable('replace', 'test/src/algorithm/replace.cpp', dependencies: test_dep, build_by_default: false)
t_1_20 = executable('group', 'test/src/algorithm/group.cpp', dependencies: test_dep, build_by_default: false)
t_1_21 = executable('make_int_sequence', 'test/src/algorithm/make_int_sequence.cpp', dependencies: test_dep, build_by_default: false)
t_1_22 = executable('split_after', 'test/src/algorithm/split_after.cpp', dependencies: test_dep, build_by_default: false)
t_1_23 = executable('none_of', 'test/src/algorithm/none_of.cpp', dependencies: test_dep, build_by_default: false)
t_1_24 = executable('combine', 'test/src/algorithm/combine.cpp', dependencies: test_dep, build_by_default: false)
t_1_25 = executable('split_before', 'test/src/algorithm/split_before.cpp', dependencies: test_dep, build_by_default: false)
t_1_26 = executable('find', 'test/src/algorithm/find.cpp', dependencies: test_dep, build_by_default: false)
t_1_27 = executable('any_of', 'test/src/algorithm/any_of.cpp', dependencies: test_dep, build_by_default: false)
t_1_28 = executable('zip', 'test/src/algorithm/zip.cpp', dependencies: test_dep, build_by_default: false)
t_1_29 = executable('upper_bound', 'test/src/algorithm/upper_bound.cpp', dependencies: test_dep, build_by_default: false)
t_1_30 = executable('merge', 'test/src/algorithm/merge.cpp', dependencies: test_dep, build_by_default: false)
t_1_31 = executable('fold_right', 'test/src/algorithm/fold_right.cpp', dependencies: test_dep, build_by_default: false)
t_1_32 = executable('repeat', 'test/src/algorithm/repeat.cpp', dependencies: test_dep, build_by_default: false)
t_1_33 = executable('split_at', 'test/src/algorithm/split_at.cpp', dependencies: test_dep, build_by_default: false)
t_1_34 = executable('remove_adjacent', 'test/src/algorithm/remove_adjacent.cpp', dependencies: test_dep, build_by_default: false)
t_1_35 = executable('count', 'test/src/algorithm/count.cpp', dependencies: test_dep, build_by_default: false)
t_1_36 = executable('split', 'test/src/algorithm/split.cpp', dependencies: test_dep, build_by_default: false)
t_1_37 = executable('powerset', 'test/src/algorithm/powerset.cpp', dependencies: test_dep, build_by_default: false)
t_1_38 = executable('matrix_shortest', 'test/src/algorithm/matrix_shortest.cpp', dependencies: test_dep, build_by_default: false)
t_1_39 = executable('remove', 'test/src/algorithm/remove.cpp', dependencies: test_dep, build_by_default: false)
t_1_40 = executable('group_n', 'test/src/algorithm/group_n.cpp', dependencies: test_dep, build_by_default: false)
t_1_41 = executable('copy', 'test/src/algorithm/copy.cpp', dependencies: test_dep, build_by_default: false)
t_1_42 = executable('intersperse', 'test/src/algorithm/intersperse.cpp', dependencies: test_dep, build_by_default: false)
t_1_43 = executable('transform', 'test/src/algorithm/transform.cpp', dependencies: test_dep, build_by_default: false)
t_1_44 = executable('rotate', 'test/src/algorithm/rotate.cpp', dependencies: test_dep, build_by_default: false)
alias_target('mp.algorithm', t_1_0, t_1_1, t_1_2, t_1_3, t_1_4, t_1_5, t_1_6, t_1_7, t_1_8, t_1_9, t_1_10, t_1_11, t_1_12, t_1_13, t_1_14, t_1_15, t_1_16, t_1_17, t_1_18, t_1_19, t_1_20, t_1_21, t_1_22, t_1_23, t_1_24, t_1_25, t_1_26, t_1_27, t_1_28, t_1_29, t_1_30, t_1_31, t_1_32, t_1_33, t_1_34, t_1_35, t_1_36, t_1_37, t_1_38, t_1_39, t_1_40, t_1_41, t_1_42, t_1_43, t_1_44)
t_2_0 = executable('partial_eager', 'test/src/functional/partial_eager.cpp', dependencies: test_dep, build_by_default: false)
t_2_1 = executable('capture', 'test/src/functional/capture.cpp', dependencies: test_dep, build_by_default: false)
t_2_2 = executable('function', 'test/src/functional/function.cpp', dependencies: test_dep, build_by_default: false)
t_2_3 = executable('each', 'test/src/functional/each.cpp', dependencies: test_dep, build_by_default: false)
t_2_4 = executable('fork_front', 'test/src/functional/fork_front.cpp', dependencies: test_dep, build_by_default: false)
t_2_5 = executable('recurse', 'test/src/functional/recurse.cpp', dependencies: test_dep, build_by_default: false)
t_2_6 = executable('fork', 'test/src/functional/fork.cpp', dependencies: test_dep, build_by_default: false)
t_2_7 = executable('partial', 'test/src/functional/partial.cpp', dependencies: test_dep, build_by_default: false)
t_2_8 = executable('eval', 'test/src/functional/eval.cpp', dependencies: test_dep, build_by_default: false)
t_2_9 = executable('is_invocable', 'test/src/functional/is_invocable.cpp', dependencies: test_dep, build_by_default: false)
t_2_10 = executable('cascade', 'test/src/functional/cascade.cpp', dependencies: test_dep, build_by_default: false)
t_2_11 = executable('fix', 'test/src/functional/fix.cpp', dependencies: test_dep, build_by_default: false)
t_2_12 = executable('flip', 'test/src/functional/flip.cpp', dependencies: test_dep, build_by_default: false)
t_2_13 = executable('bind', 'test/src/functional/bind.cpp', dependencies: test_dep, build_by_default: false)
t_2_14 = executable('if', 'test/src/functional/if.cpp', dependencies: test_dep, build_by_default: false)
t_2_15 = executable('identity', 'test/src/functional/identity.cpp', dependencies: test_dep, build_by_default: false)
t_2_16 = executable('compose', 'test/src/functional/compose.cpp', dependencies: test_dep, build_by_default: false)
alias_target('mp.functional', t_2_0, t_2_1, t_2_2, t_2_3, t_2_4, t_2_5, t_2_6, t_2_7, t_2_8, t_2_9, t_2_10, t_2_11, t_2_12, t_2_13, t_2_14, t_2_15, t_2_16)
t_3_0 = executable('operators', 'test/src/value/operators.cpp', dependencies: test_dep, build_by_default: false)
t_3_1 = executable('has_value', 'test/src/value/has_value.cpp', dependencies: test_dep, build_by_default: false)
t_3_2 = executable('is_val', 'test/src/value/is_val.cpp', dependencies: test_dep, build_by_default: false)
t_3_3 = executable('as_val', 'test/src/value/as_val.cpp', dependencies: test_dep, build_by_default: false)
t_3_4 = executable('values', 'test/src/value/values.cpp', dependencies: test_dep, build_by_default: false)
alias_target('mp.value', t_3_0, t_3_1, t_3_2, t_3_3, t_3_4)
t_4_0 = executable('operators_', 'test/src/number/operators.cpp', dependencies: test_dep, build_by_default: false)
t_4_1 = executable('as_number', 'test/src/number/as_number.cpp', dependencies: test_dep, build_by_default: false)
t_4_2 = executable('as_bool', 'test/src/number/as_bool.cpp', dependencies: test_dep, build_by_default: false)
t_4_3 = executable('numbers', 'test/src/number/numbers.cpp', dependencies: test_dep, build_by_default: false)
t_4_4 = executable('math', 'test/src/number/math.cpp', dependencies: test_dep, build_by_default: false)
t_4_5 = executable('to_bool', 'test/src/number/to_bool.cpp', dependencies: test_dep, build_by_default: false)
t_4_6 = executable('is_number', 'test/src/number/is_number.cpp', dependencies: test_dep, build_by_default: false)
alias_target('mp.number', t_4_0, t_4_1, t_4_2, t_4_3, t_4_4, t_4_5, t_4_6)
t_5_0 = executable('list_wrap_if', 'test/src/list/list_wrap_if.cpp', dependencies: test_dep, build_by_default: false)
t_5_1 = executable('push_front', 'test/src/list/push_front.cpp', dependencies: test_dep, build_by_default: false)
t_5_2 = executable('insert_range', 'test/src/list/insert_range.cpp', dependencies: test_dep, build_by_default: false)
t_5_3 = executable('swap_index', 'test/src/list/swap_index.cpp', dependencies: test_dep, build_by_default: false)
t_5_4 = executable('is_size_of', 'test/src/list/is_size_of.cpp', dependencies: test_dep, build_by_default: false)
t_5_5 = executable('size', 'test/src/list/size.cpp', dependencies: test_dep, build_by_default: false)
t_5_6 = executable('prepend', 'test/src/list/prepend.cpp', dependencies: test_dep, build_by_default: false)
t_5_7 = executable('list', 'test/src/list/list.cpp', dependencies: test_dep, build_by_default: false)
t_5_8 = executable('drop', 'test/src/list/drop.cpp', dependencies: test_dep, build_by_default: false)
t_5_9 = executable('sliding', 'test/src/list/sliding.cpp', dependencies: test_dep, build_by_default: false)
t_5_10 = executable('is_list', 'test/src/list/is_list.cpp', dependencies: test_dep, build_by_default: false)
t_5_11 = executable('erase', 'test/src/list/erase.cpp', dependencies: test_dep, build_by_default: false)
t_5_12 = executable('range', 'test/src/list/range.cpp', dependencies: test_dep, build_by_default: false)
t_5_13 = executable('offset', 'test/src/list/offset.cpp', dependencies: test_dep, build_by_default: false)
t_5_14 = executable('pop_front', 'test/src/list/pop_front.cpp', dependencies: test_dep, build_by_default: false)
t_5_15 = executable('push_back', 'test/src/list/push_back.cpp', dependencies: test_dep, build_by_default: false)
t_5_16 = executable('front', 'test/src/list/front.cpp', dependencies: test_dep, build_by_default: false)
t_5_17 = executable('join', 'test/src/list/join.cpp', dependencies: test_dep, build_by_default: false)
t_5_18 = executable('insert', 'test/src/list/insert.cpp', dependencies: test_dep, build_by_default: false)
t_5_19 = executable('take', 'test/src/list/take.cpp', dependencies: test_dep, build_by_default: false)
t_5_20 = executable('pop_back', 'test/src/list/pop_back.cpp', dependencies: test_dep, build_by_default: false)
t_5_21 = executable('at', 'test/src/list/at.cpp', dependencies: test_dep, build_by_default: false)
t_5_22 = executable('append', 'test/src/list/append.cpp', dependencies: test_dep, build_by_default: false)
t_5_23 = executable('back', 'test/src/list/back.cpp', dependencies: test_dep, build_by_default: false)
t_5_24 = executable('is_empty', 'test/src/list/is_empty.cpp', dependencies: test_dep, build_by_default: false)
t_5_25 = executable('as_list', 'test/src/list/as_list.cpp', dependencies: test_dep, build_by_default: false)
t_5_26 = executable('slice', 'test/src/list/slice.cpp', dependencies: test_dep, build_by_default: false)
alias_target('mp.list', t_5_0, t_5_1, t_5_2, t_5_3, t_5_4, t_5_5, t_5_6, t_5_7, t_5_8, t_5_9, t_5_10, t_5_11, t_5_12, t_5_13, t_5_14, t_5_15, t_5_16, t_5_17, t_5_18, t_5_19, t_5_20, t_5_21, t_5_22, t_5_23, t_5_24, t_5_25, t_5_26)
alias_target('mp', t_0_0, t_0_1, t_0_2, t_0_3, t_0_4, t_0_5, t_1_0, t_1_1, t_1_2, t_1_3, t_1_4, t_1_5, t_1_6, t_1_7, t_1_8, t_1_9, t_1_10, t_1_11, t_1_12, t_1_13, t_1_14, t_1_15, t_1_16, t_1_17, t_1_18, t_1_19, t_1_20, t_1_21, t_1_22, t_1_23, t_1_24, t_1_25, t_1_26, t_1_27, t_1_28, t_1_29, t_1_30, t_1_31, t_1_32, t_1_33, t_1_34, t_1_35, t_1_36, t_1_37, t_1_38, t_1_39, t_1_40, t_1_41, t_1_42, t_1_43, t_1_44, t_2_0, t_2_1, t_2_2, t_2_3, t_2_4, t_2_5, t_2_6, t_2_7, t_2_8, t_2_9, t_2_10, t_2_11, t_2_12, t_2_13, t_2_14, t_2_15, t_2_16, t_3_0, t_3_1, t_3_2, t_3_3, t_3_4, t_4_0, t_4_1, t_4_2, t_4_3, t_4_4, t_4_5, t_4_6, t_5_0, t_5_1, t_5_2, t_5_3, t_5_4, t_5_5, t_5_6, t_5_7, t_5_8, t_5_9, t_5_10, t_5_11, t_5_12, t_5_13, t_5_14, t_5_15, t_5_16, t_5_17, t_5_18, t_5_19, t_5_20, t_5_21, t_5_22, t_5_23, t_5_24, t_5_25, t_5_26)
executable('check_inc', [
  'test/autogen/smp@algorithm@matrix_shortest.hpp.cpp',
  'test/autogen/smp@value@is_val.hpp.cpp',
  'test/autogen/utility@is_instance_of.hpp.cpp',
  'test/autogen/functional@each.hpp.cpp',
  'test/autogen/smp@list@is_list.hpp.cpp',
  'test/autogen/algorithm@matrix_shortest.hpp.cpp',
  'test/autogen/smp@algorithm@contains.hpp.cpp',
  'test/autogen/list@slice.hpp.cpp',
  'test/autogen/detail@type_identity.hpp.cpp',
  'test/autogen/functional@identity.hpp.cpp',
  'test/autogen/algorithm@remove.hpp.cpp',
  'test/autogen/algorithm@iota.hpp.cpp',
  'test/autogen/smp@algorithm@count.hpp.cpp',
  'test/autogen/algorithm@index.hpp.cpp',
  'test/autogen/smp@number@math.hpp.cpp',
  'test/autogen/list@at.hpp.cpp',
  'test/autogen/smp@algorithm@replace.hpp.cpp',
  'test/autogen/value@val.hpp.cpp',
  'test/autogen/smp@list@pop_front.hpp.cpp',
  'test/autogen/smp@utility@has_type.hpp.cpp',
  'test/autogen/algorithm@split_at.hpp.cpp',
  'test/autogen/smp@list@erase.hpp.cpp',
  'test/autogen/algorithm@accumulate.hpp.cpp',
  'test/autogen/smp@algorithm@remove.hpp.cpp',
  'test/autogen/smp@list@is_size_of.hpp.cpp',
  'test/autogen/smp@list@list.hpp.cpp',
  'test/autogen/functional@monadic.hpp.cpp',
  'test/autogen/smp@utility@traits.hpp.cpp',
  'test/autogen/smp@functional@fork.hpp.cpp',
  'test/autogen/smp@number@numbers.hpp.cpp',
  'test/autogen/smp@algorithm@fold_left.hpp.cpp',
  'test/autogen/smp@list@at.hpp.cpp',
  'test/autogen/smp@functional@recurse.hpp.cpp',
  'test/autogen/smp@algorithm@split.hpp.cpp',
  'test/autogen/number@operators.hpp.cpp',
  'test/autogen/algorithm@group.hpp.cpp',
  'test/autogen/number@to_bool.hpp.cpp',
  'test/autogen/algorithm@indices.hpp.cpp',
  'test/autogen/smp@algorithm@flatten.hpp.cpp',
  'test/autogen/list@list.hpp.cpp',
  'test/autogen/functional@fork_front.hpp.cpp',
  'test/autogen/smp@list@push_front.hpp.cpp',
  'test/autogen/smp@algorithm@take_while.hpp.cpp',
  'test/autogen/smp@algorithm@combine.hpp.cpp',
  'test/autogen/smp@functional@partial_eager.hpp.cpp',
  'test/autogen/smp@algorithm@powerset.hpp.cpp',
  'test/autogen/algorithm@upper_bound.hpp.cpp',
  'test/autogen/functional@compose.hpp.cpp',
  'test/autogen/functional@partial.hpp.cpp',
  'test/autogen/smp@list@as_list.hpp.cpp',
  'test/autogen/functional@recurse.hpp.cpp',
  'test/autogen/config@debug.hpp.cpp',
  'test/autogen/algorithm@is_sorted.hpp.cpp',
  'test/autogen/smp@algorithm@find.hpp.cpp',
  'test/autogen/list@pop_back.hpp.cpp',
  'test/autogen/smp@functional@if.hpp.cpp',
  'test/autogen/algorithm@split_before.hpp.cpp',
  'test/autogen/algorithm@find.hpp.cpp',
  'test/autogen/smp@functional@function.hpp.cpp',
  'test/autogen/smp@algorithm@make_int_sequence.hpp.cpp',
  'test/autogen/smp@number@as_bool.hpp.cpp',
  'test/autogen/list@push_back.hpp.cpp',
  'test/autogen/smp@algorithm@all_of.hpp.cpp',
  'test/autogen/list@append.hpp.cpp',
  'test/autogen/algorithm@take_while.hpp.cpp',
  'test/autogen/value@has_value.hpp.cpp',
  'test/autogen/smp@algorithm@fold_right.hpp.cpp',
  'test/autogen/number@numbers.hpp.cpp',
  'test/autogen/algorithm@permutations.hpp.cpp',
  'test/autogen/number@is_number.hpp.cpp',
  'test/autogen/algorithm@any_of.hpp.cpp',
  'test/autogen/list@insert.hpp.cpp',
  'test/autogen/number@as_number.hpp.cpp',
  'test/autogen/algorithm@powerset.hpp.cpp',
  'test/autogen/smp@functional@eval.hpp.cpp',
  'test/autogen/smp@value@values.hpp.cpp',
  'test/autogen/functional@capture.hpp.cpp',
  'test/autogen/list@front.hpp.cpp',
  'test/autogen/algorithm@zip.hpp.cpp',
  'test/autogen/smp@contract.hpp.cpp',
  'test/autogen/algorithm@unique.hpp.cpp',
  'test/autogen/functional@flip.hpp.cpp',
  'test/autogen/list@pop_front.hpp.cpp',
  'test/autogen/config@enumerate.hpp.cpp',
  'test/autogen/algorithm@sort.hpp.cpp',
  'test/autogen/list@swap_index.hpp.cpp',
  'test/autogen/smp@functional@compose.hpp.cpp',
  'test/autogen/algorithm@replace.hpp.cpp',
  'test/autogen/value@as_val.hpp.cpp',
  'test/autogen/list@sliding.hpp.cpp',
  'test/autogen/functional@bind.hpp.cpp',
  'test/autogen/algorithm@fold_right.hpp.cpp',
  'test/autogen/smp@list@append.hpp.cpp',
  'test/autogen/algorithm@cartesian.hpp.cpp',
  'test/autogen/smp@algorithm@indices.hpp.cpp',
  'test/autogen/smp@algorithm@reverse.hpp.cpp',
  'test/autogen/utility@traits.hpp.cpp',
  'test/autogen/number@math.hpp.cpp',
  'test/autogen/list@offset.hpp.cpp',
  'test/autogen/value@is_val.hpp.cpp',
  'test/autogen/smp@algorithm@is_sorted.hpp.cpp',
  'test/autogen/smp@concepts.hpp.cpp',
  'test/autogen/smp@list@pop_back.hpp.cpp',
  'test/autogen/functional@cascade.hpp.cpp',
  'test/autogen/list@join.hpp.cpp',
  'test/autogen/smp@list@push_back.hpp.cpp',
  'test/autogen/smp@algorithm@group_n.hpp.cpp',
  'test/autogen/smp@algorithm@index.hpp.cpp',
  'test/autogen/smp@algorithm@any_of.hpp.cpp',
  'test/autogen/smp@list@slice.hpp.cpp',
  'test/autogen/smp@number@as_number.hpp.cpp',
  'test/autogen/functional@call.hpp.cpp',
  'test/autogen/list@as_list.hpp.cpp',
  'test/autogen/algorithm@merge.hpp.cpp',
  'test/autogen/algorithm@repeat.hpp.cpp',
  'test/autogen/list@list_wrap_if.hpp.cpp',
  'test/autogen/list@take.hpp.cpp',
  'test/autogen/smp@assume.hpp.cpp',
  'test/autogen/smp@algorithm@cartesian.hpp.cpp',
  'test/autogen/smp@utility@conditional.hpp.cpp',
  'test/autogen/list@range.hpp.cpp',
  'test/autogen/algorithm@contains.hpp.cpp',
  'test/autogen/smp@functional@sfinaefwd.hpp.cpp',
  'test/autogen/smp@list@swap_index.hpp.cpp',
  'test/autogen/algorithm@split_after.hpp.cpp',
  'test/autogen/smp@value@operators.hpp.cpp',
  'test/autogen/smp@functional@fork_front.hpp.cpp',
  'test/autogen/smp@list@front.hpp.cpp',
  'test/autogen/utility@unpack.hpp.cpp',
  'test/autogen/smp@algorithm@none_of.hpp.cpp',
  'test/autogen/value@values.hpp.cpp',
  'test/autogen/smp@algorithm@rotate.hpp.cpp',
  'test/autogen/smp@algorithm@repeat.hpp.cpp',
  'test/autogen/smp@algorithm@sort.hpp.cpp',
  'test/autogen/functional@if.hpp.cpp',
  'test/autogen/algorithm@flatten.hpp.cpp',
  'test/autogen/utility@always.hpp.cpp',
  'test/autogen/smp@algorithm@intersperse.hpp.cpp',
  'test/autogen/number@number.hpp.cpp',
  'test/autogen/smp@algorithm@lower_bound.hpp.cpp',
  'test/autogen/utility@has_type.hpp.cpp',
  'test/autogen/smp@functional@identity.hpp.cpp',
  'test/autogen/algorithm@same.hpp.cpp',
  'test/autogen/smp@value@as_val.hpp.cpp',
  'test/autogen/smp@functional@fix.hpp.cpp',
  'test/autogen/smp@algorithm@merge.hpp.cpp',
  'test/autogen/smp@list@range.hpp.cpp',
  'test/autogen/smp@utility@same_as.hpp.cpp',
  'test/autogen/list@is_list.hpp.cpp',
  'test/autogen/algorithm@reverse.hpp.cpp',
  'test/autogen/list@push_front.hpp.cpp',
  'test/autogen/smp@functional@is_invocable.hpp.cpp',
  'test/autogen/smp@algorithm@iota.hpp.cpp',
  'test/autogen/list@erase.hpp.cpp',
  'test/autogen/list@insert_range.hpp.cpp',
  'test/autogen/list@back.hpp.cpp',
  'test/autogen/algorithm@remove_adjacent.hpp.cpp',
  'test/autogen/smp@algorithm@copy.hpp.cpp',
  'test/autogen/smp@algorithm@upper_bound.hpp.cpp',
  'test/autogen/algorithm@transform.hpp.cpp',
  'test/autogen/smp@algorithm@zip.hpp.cpp',
  'test/autogen/algorithm@count.hpp.cpp',
  'test/autogen/smp@functional@bind.hpp.cpp',
  'test/autogen/smp@functional@each.hpp.cpp',
  'test/autogen/smp@list@drop.hpp.cpp',
  'test/autogen/algorithm@none_of.hpp.cpp',
  'test/autogen/algorithm@fold_left.hpp.cpp',
  'test/autogen/list@is_empty.hpp.cpp',
  'test/autogen/list@size.hpp.cpp',
  'test/autogen/algorithm@partition.hpp.cpp',
  'test/autogen/smp@algorithm@permutations.hpp.cpp',
  'test/autogen/functional@try_invoke.hpp.cpp',
  'test/autogen/algorithm@intersperse.hpp.cpp',
  'test/autogen/smp@value@has_value.hpp.cpp',
  'test/autogen/list@prepend.hpp.cpp',
  'test/autogen/algorithm@copy.hpp.cpp',
  'test/autogen/algorithm@lower_bound.hpp.cpp',
  'test/autogen/smp@list@prepend.hpp.cpp',
  'test/autogen/list@drop.hpp.cpp',
  'test/autogen/smp@utility@unpack.hpp.cpp',
  'test/autogen/main.cpp',
  'test/autogen/smp@algorithm@partition.hpp.cpp',
  'test/autogen/smp@list@back.hpp.cpp',
  'test/autogen/smp@algorithm@is_unique.hpp.cpp',
  'test/autogen/functional@function.hpp.cpp',
  'test/autogen/smp@list@is_empty.hpp.cpp',
  'test/autogen/smp@list@offset.hpp.cpp',
  'test/autogen/detail@first.hpp.cpp',
  'test/autogen/smp@functional@capture.hpp.cpp',
  'test/autogen/smp@list@list_wrap_if.hpp.cpp',
  'test/autogen/smp@algorithm@split_after.hpp.cpp',
  'test/autogen/number@as_bool.hpp.cpp',
  'test/autogen/smp@algorithm@split_before.hpp.cpp',
  'test/autogen/smp@functional@flip.hpp.cpp',
  'test/autogen/smp@algorithm@transform.hpp.cpp',
  'test/autogen/list@is_size_of.hpp.cpp',
  'test/autogen/functional@fork.hpp.cpp',
  'test/autogen/smp@list@sliding.hpp.cpp',
  'test/autogen/algorithm@make_int_sequence.hpp.cpp',
  'test/autogen/functional@eval.hpp.cpp',
  'test/autogen/smp@list@insert.hpp.cpp',
  'test/autogen/smp@functional@partial.hpp.cpp',
  'test/autogen/smp@number@to_bool.hpp.cpp',
  'test/autogen/functional@is_invocable.hpp.cpp',
  'test/autogen/smp@utility@always.hpp.cpp',
  'test/autogen/utility@same_as.hpp.cpp',
  'test/autogen/smp@algorithm@accumulate.hpp.cpp',
  'test/autogen/smp@algorithm@remove_adjacent.hpp.cpp',
  'test/autogen/functional@fix.hpp.cpp',
  'test/autogen/smp@algorithm@split_at.hpp.cpp',
  'test/autogen/smp@algorithm@same.hpp.cpp',
  'test/autogen/algorithm@is_unique.hpp.cpp',
  'test/autogen/algorithm@combine.hpp.cpp',
  'test/autogen/smp@list@join.hpp.cpp',
  'test/autogen/smp@number@operators.hpp.cpp',
  'test/autogen/smp@list@size.hpp.cpp',
  'test/autogen/algorithm@all_of.hpp.cpp',
  'test/autogen/smp@number@is_number.hpp.cpp',
  'test/autogen/smp@utility@is_instance_of.hpp.cpp',
  'test/autogen/smp@functional@cascade.hpp.cpp',
  'test/autogen/algorithm@group_n.hpp.cpp',
  'test/autogen/value@operators.hpp.cpp',
  'test/autogen/algorithm@rotate.hpp.cpp',
  'test/autogen/utility@conditional.hpp.cpp',
  'test/autogen/smp@algorithm@unique.hpp.cpp',
  'test/autogen/algorithm@split.hpp.cpp',
  'test/autogen/smp@list@take.hpp.cpp',
  'test/autogen/functional@partial_eager.hpp.cpp',
  'test/autogen/smp@list@insert_range.hpp.cpp',
  'test/autogen/smp@algorithm@group.hpp.cpp'
], dependencies: test_dep)
# stop tests
