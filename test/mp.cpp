// SPDX-FileCopyrightText: 2024 Jonathan Poelen <jonathan.poelen@gmail.com>
// SPDX-License-Identifier: MIT
#include "src/algorithm/accumulate.cpp"
#include "src/algorithm/after.cpp"
#include "src/algorithm/all_of.cpp"
#include "src/algorithm/anticirculant_matrix.cpp"
#include "src/algorithm/any_of.cpp"
#include "src/algorithm/arrange.cpp"
#include "src/algorithm/batched.cpp"
#include "src/algorithm/before.cpp"
#include "src/algorithm/before_after.cpp"
#include "src/algorithm/circulant_matrix.cpp"
#include "src/algorithm/collapse.cpp"
#include "src/algorithm/combine.cpp"
#include "src/algorithm/compare_with.cpp"
#include "src/algorithm/compress.cpp"
#include "src/algorithm/conjunction.cpp"
#include "src/algorithm/contains.cpp"
#include "src/algorithm/copy.cpp"
#include "src/algorithm/copy_unique.cpp"
#include "src/algorithm/count.cpp"
#include "src/algorithm/counter.cpp"
#include "src/algorithm/disjunction.cpp"
#include "src/algorithm/drop_until.cpp"
#include "src/algorithm/drop_until_xs.cpp"
#include "src/algorithm/drop_while.cpp"
#include "src/algorithm/drop_while_xs.cpp"
#include "src/algorithm/ends_with.cpp"
#include "src/algorithm/find.cpp"
#include "src/algorithm/find_last.cpp"
#include "src/algorithm/flatten.cpp"
#include "src/algorithm/fold.cpp"
#include "src/algorithm/fold_right.cpp"
#include "src/algorithm/fold_tree.cpp"
#include "src/algorithm/fold_xs.cpp"
#include "src/algorithm/group.cpp"
#include "src/algorithm/index.cpp"
#include "src/algorithm/intersperse.cpp"
#include "src/algorithm/iota.cpp"
#include "src/algorithm/is_disjoint.cpp"
#include "src/algorithm/is_sorted.cpp"
#include "src/algorithm/is_subset.cpp"
#include "src/algorithm/is_unique.cpp"
#include "src/algorithm/lexicographical_compare.cpp"
#include "src/algorithm/lower_bound.cpp"
#include "src/algorithm/make_int_sequence.cpp"
#include "src/algorithm/matrix_longest.cpp"
#include "src/algorithm/matrix_shortest.cpp"
#include "src/algorithm/merge.cpp"
#include "src/algorithm/mismatch.cpp"
#include "src/algorithm/mismatch_index.cpp"
#include "src/algorithm/none_of.cpp"
#include "src/algorithm/pairwise.cpp"
#include "src/algorithm/pairwise_fold.cpp"
#include "src/algorithm/partition.cpp"
#include "src/algorithm/permutations.cpp"
#include "src/algorithm/powerset.cpp"
#include "src/algorithm/prefix.cpp"
#include "src/algorithm/product.cpp"
#include "src/algorithm/regroup.cpp"
#include "src/algorithm/remove.cpp"
#include "src/algorithm/remove_adjacent.cpp"
#include "src/algorithm/remove_prefix.cpp"
#include "src/algorithm/remove_suffix.cpp"
#include "src/algorithm/remove_unique.cpp"
#include "src/algorithm/repeat.cpp"
#include "src/algorithm/replace.cpp"
#include "src/algorithm/reverse.cpp"
#include "src/algorithm/reverse_fold.cpp"
#include "src/algorithm/reverse_fold_right.cpp"
#include "src/algorithm/rotate.cpp"
#include "src/algorithm/same.cpp"
#include "src/algorithm/scan.cpp"
#include "src/algorithm/scan_right.cpp"
#include "src/algorithm/search.cpp"
#include "src/algorithm/similar.cpp"
#include "src/algorithm/skip_until.cpp"
#include "src/algorithm/skip_until_xs.cpp"
#include "src/algorithm/skip_while.cpp"
#include "src/algorithm/skip_while_xs.cpp"
#include "src/algorithm/sort.cpp"
#include "src/algorithm/split.cpp"
#include "src/algorithm/split_after.cpp"
#include "src/algorithm/split_at.cpp"
#include "src/algorithm/split_before.cpp"
#include "src/algorithm/split_from.cpp"
#include "src/algorithm/split_keep_separator.cpp"
#include "src/algorithm/split_once.cpp"
#include "src/algorithm/starts_with.cpp"
#include "src/algorithm/suffix.cpp"
#include "src/algorithm/take_until.cpp"
#include "src/algorithm/take_until_xs.cpp"
#include "src/algorithm/take_while.cpp"
#include "src/algorithm/take_while_xs.cpp"
#include "src/algorithm/transform.cpp"
#include "src/algorithm/transform_first.cpp"
#include "src/algorithm/transform_second.cpp"
#include "src/algorithm/transform_third.cpp"
#include "src/algorithm/unfold.cpp"
#include "src/algorithm/unique.cpp"
#include "src/algorithm/upper_bound.cpp"
#include "src/algorithm/zip.cpp"
#include "src/algorithm/zip_longest.cpp"
#include "src/assume.cpp"
#include "src/functional/apply_or_identity.cpp"
#include "src/functional/bind_back.cpp"
#include "src/functional/bind_front.cpp"
#include "src/functional/capture_back.cpp"
#include "src/functional/capture_front.cpp"
#include "src/functional/cascade.cpp"
#include "src/functional/compose.cpp"
#include "src/functional/each.cpp"
#include "src/functional/eval.cpp"
#include "src/functional/fix.cpp"
#include "src/functional/flip.cpp"
#include "src/functional/identity.cpp"
#include "src/functional/if.cpp"
#include "src/functional/invoke_twice.cpp"
#include "src/functional/lift.cpp"
#include "src/functional/make_id.cpp"
#include "src/functional/memoize.cpp"
#include "src/functional/not_fn.cpp"
#include "src/functional/partial.cpp"
#include "src/functional/partial_each.cpp"
#include "src/functional/partial_tee.cpp"
#include "src/functional/partial_xs.cpp"
#include "src/functional/random.cpp"
#include "src/functional/recursively.cpp"
#include "src/functional/tee.cpp"
#include "src/functional/try.cpp"
#include "src/functional/until.cpp"
#include "src/functional/until_last.cpp"
#include "src/functional/while.cpp"
#include "src/list/append.cpp"
#include "src/list/as_list.cpp"
#include "src/list/at.cpp"
#include "src/list/back.cpp"
#include "src/list/clear.cpp"
#include "src/list/drop_back.cpp"
#include "src/list/drop_front.cpp"
#include "src/list/enumerate.cpp"
#include "src/list/erase.cpp"
#include "src/list/front.cpp"
#include "src/list/indices.cpp"
#include "src/list/insert.cpp"
#include "src/list/insert_sequence.cpp"
#include "src/list/is_empty.cpp"
#include "src/list/is_list.cpp"
#include "src/list/is_not_empty.cpp"
#include "src/list/is_size_of.cpp"
#include "src/list/join.cpp"
#include "src/list/list.cpp"
#include "src/list/lookup.cpp"
#include "src/list/offset.cpp"
#include "src/list/pop_back.cpp"
#include "src/list/pop_front.cpp"
#include "src/list/prepend.cpp"
#include "src/list/push_back.cpp"
#include "src/list/push_front.cpp"
#include "src/list/range.cpp"
#include "src/list/size.cpp"
#include "src/list/slice.cpp"
#include "src/list/sliding.cpp"
#include "src/list/swap_index.cpp"
#include "src/list/take_back.cpp"
#include "src/list/take_front.cpp"
#include "src/list/wrap_in_list.cpp"
#include "src/map/is_map.cpp"
#include "src/map/map_contains.cpp"
#include "src/map/map_erase.cpp"
#include "src/map/map_find.cpp"
#include "src/map/map_insert.cpp"
#include "src/map/map_keys.cpp"
#include "src/map/map_replace.cpp"
#include "src/map/map_update.cpp"
#include "src/number/as_bool.cpp"
#include "src/number/as_number.cpp"
#include "src/number/is_number.cpp"
#include "src/number/math.cpp"
#include "src/number/numbers.cpp"
#include "src/number/operators.cpp"
#include "src/number/to_bool.cpp"
#include "src/set/set_contains.cpp"
#include "src/set/set_difference.cpp"
#include "src/set/set_find.cpp"
#include "src/set/set_intersection.cpp"
#include "src/set/set_push_back.cpp"
#include "src/set/set_push_back_elements.cpp"
#include "src/set/set_push_front.cpp"
#include "src/set/set_push_front_elements.cpp"
#include "src/set/set_union.cpp"
#include "src/utility/alignof.cpp"
#include "src/utility/always.cpp"
#include "src/utility/conditional.cpp"
#include "src/utility/has_type.cpp"
#include "src/utility/has_value_type.cpp"
#include "src/utility/is.cpp"
#include "src/utility/is_not.cpp"
#include "src/utility/is_specialization_of.cpp"
#include "src/utility/iterate.cpp"
#include "src/utility/rewrap_unpack.cpp"
#include "src/utility/sizeof.cpp"
#include "src/utility/stl_traits.cpp"
#include "src/utility/type.cpp"
#include "src/utility/unpack.cpp"
#include "src/utility/value_type.cpp"
#include "src/utility/wrapper.cpp"
#include "src/value/as_val.cpp"
#include "src/value/has_value.cpp"
#include "src/value/is_val.cpp"
#include "src/value/operators.cpp"
#include "src/value/values.cpp"
