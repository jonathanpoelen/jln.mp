// SPDX-FileCopyrightText: 2024 Jonathan Poelen <jonathan.poelen@gmail.com>
// SPDX-License-Identifier: MIT
#pragma once

#include <jln/mp/smp/algorithm/accumulate.hpp>
#include <jln/mp/smp/algorithm/after.hpp>
#include <jln/mp/smp/algorithm/all_of.hpp>
#include <jln/mp/smp/algorithm/anticirculant_matrix.hpp>
#include <jln/mp/smp/algorithm/any_of.hpp>
#include <jln/mp/smp/algorithm/arrange.hpp>
#include <jln/mp/smp/algorithm/batched.hpp>
#include <jln/mp/smp/algorithm/before.hpp>
#include <jln/mp/smp/algorithm/before_after.hpp>
#include <jln/mp/smp/algorithm/circulant_matrix.hpp>
#include <jln/mp/smp/algorithm/collapse.hpp>
#include <jln/mp/smp/algorithm/combine.hpp>
#include <jln/mp/smp/algorithm/compress.hpp>
#include <jln/mp/smp/algorithm/conjunction.hpp>
#include <jln/mp/smp/algorithm/contains.hpp>
#include <jln/mp/smp/algorithm/copy.hpp>
#include <jln/mp/smp/algorithm/copy_unique.hpp>
#include <jln/mp/smp/algorithm/count.hpp>
#include <jln/mp/smp/algorithm/counter.hpp>
#include <jln/mp/smp/algorithm/disjunction.hpp>
#include <jln/mp/smp/algorithm/drop_until.hpp>
#include <jln/mp/smp/algorithm/drop_until_xs.hpp>
#include <jln/mp/smp/algorithm/drop_while.hpp>
#include <jln/mp/smp/algorithm/drop_while_xs.hpp>
#include <jln/mp/smp/algorithm/ends_with.hpp>
#include <jln/mp/smp/algorithm/find.hpp>
#include <jln/mp/smp/algorithm/find_last.hpp>
#include <jln/mp/smp/algorithm/flatten.hpp>
#include <jln/mp/smp/algorithm/fold.hpp>
#include <jln/mp/smp/algorithm/fold_right.hpp>
#include <jln/mp/smp/algorithm/fold_tree.hpp>
#include <jln/mp/smp/algorithm/fold_xs.hpp>
#include <jln/mp/smp/algorithm/group.hpp>
#include <jln/mp/smp/algorithm/index.hpp>
#include <jln/mp/smp/algorithm/intersperse.hpp>
#include <jln/mp/smp/algorithm/iota.hpp>
#include <jln/mp/smp/algorithm/is_disjoint.hpp>
#include <jln/mp/smp/algorithm/is_sorted.hpp>
#include <jln/mp/smp/algorithm/is_subset.hpp>
#include <jln/mp/smp/algorithm/is_unique.hpp>
#include <jln/mp/smp/algorithm/lexicographical_compare.hpp>
#include <jln/mp/smp/algorithm/lower_bound.hpp>
#include <jln/mp/smp/algorithm/make_int_sequence.hpp>
#include <jln/mp/smp/algorithm/matrix_longest.hpp>
#include <jln/mp/smp/algorithm/matrix_shortest.hpp>
#include <jln/mp/smp/algorithm/max_element.hpp>
#include <jln/mp/smp/algorithm/merge.hpp>
#include <jln/mp/smp/algorithm/min_element.hpp>
#include <jln/mp/smp/algorithm/mismatch.hpp>
#include <jln/mp/smp/algorithm/mismatch_index.hpp>
#include <jln/mp/smp/algorithm/none_of.hpp>
#include <jln/mp/smp/algorithm/pairwise.hpp>
#include <jln/mp/smp/algorithm/pairwise_fold.hpp>
#include <jln/mp/smp/algorithm/partition.hpp>
#include <jln/mp/smp/algorithm/permutations.hpp>
#include <jln/mp/smp/algorithm/powerset.hpp>
#include <jln/mp/smp/algorithm/prefix.hpp>
#include <jln/mp/smp/algorithm/product.hpp>
#include <jln/mp/smp/algorithm/regroup.hpp>
#include <jln/mp/smp/algorithm/remove.hpp>
#include <jln/mp/smp/algorithm/remove_adjacent.hpp>
#include <jln/mp/smp/algorithm/remove_prefix.hpp>
#include <jln/mp/smp/algorithm/remove_suffix.hpp>
#include <jln/mp/smp/algorithm/remove_unique.hpp>
#include <jln/mp/smp/algorithm/repeat.hpp>
#include <jln/mp/smp/algorithm/repeat_index.hpp>
#include <jln/mp/smp/algorithm/replace.hpp>
#include <jln/mp/smp/algorithm/reverse.hpp>
#include <jln/mp/smp/algorithm/reverse_fold.hpp>
#include <jln/mp/smp/algorithm/reverse_fold_right.hpp>
#include <jln/mp/smp/algorithm/rotate.hpp>
#include <jln/mp/smp/algorithm/same.hpp>
#include <jln/mp/smp/algorithm/scan.hpp>
#include <jln/mp/smp/algorithm/scan_right.hpp>
#include <jln/mp/smp/algorithm/search.hpp>
#include <jln/mp/smp/algorithm/similar.hpp>
#include <jln/mp/smp/algorithm/skip_until.hpp>
#include <jln/mp/smp/algorithm/skip_until_xs.hpp>
#include <jln/mp/smp/algorithm/skip_while.hpp>
#include <jln/mp/smp/algorithm/skip_while_xs.hpp>
#include <jln/mp/smp/algorithm/sort.hpp>
#include <jln/mp/smp/algorithm/split.hpp>
#include <jln/mp/smp/algorithm/split_after.hpp>
#include <jln/mp/smp/algorithm/split_at.hpp>
#include <jln/mp/smp/algorithm/split_before.hpp>
#include <jln/mp/smp/algorithm/split_from.hpp>
#include <jln/mp/smp/algorithm/split_keep_separator.hpp>
#include <jln/mp/smp/algorithm/split_once.hpp>
#include <jln/mp/smp/algorithm/starts_with.hpp>
#include <jln/mp/smp/algorithm/suffix.hpp>
#include <jln/mp/smp/algorithm/take_until.hpp>
#include <jln/mp/smp/algorithm/take_until_xs.hpp>
#include <jln/mp/smp/algorithm/take_while.hpp>
#include <jln/mp/smp/algorithm/take_while_xs.hpp>
#include <jln/mp/smp/algorithm/transform.hpp>
#include <jln/mp/smp/algorithm/transform_at.hpp>
#include <jln/mp/smp/algorithm/transform_first.hpp>
#include <jln/mp/smp/algorithm/transform_second.hpp>
#include <jln/mp/smp/algorithm/transform_third.hpp>
#include <jln/mp/smp/algorithm/unfold.hpp>
#include <jln/mp/smp/algorithm/unique.hpp>
#include <jln/mp/smp/algorithm/upper_bound.hpp>
#include <jln/mp/smp/algorithm/zip.hpp>
#include <jln/mp/smp/algorithm/zip_longest.hpp>
