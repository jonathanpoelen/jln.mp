// SPDX-FileCopyrightText: 2023 Jonathan Poelen <jonathan.poelen@gmail.com>
// SPDX-License-Identifier: MIT
#include "test.hpp"
#include "test/numbers.hpp"

#include "jln/mp/smp/algorithm/is_subset.hpp"
#include "jln/mp/smp/number/operators.hpp"

TEST_SUITE_BEGIN()

TEST()
{
  using namespace jln::mp;
  using namespace ut::ints;

  test_binary_pack<is_subset_with>();
  test_unary_pack<is_subset_with, listify>();

  ut::same<_1, emp::is_subset<emp::numbers<0, 1, 2>, emp::numbers<0, 1>>>();
  ut::same<_0, emp::is_subset<emp::numbers<0, 1, 2>, emp::numbers<1, 2, 3>>>();

  test_context<is_subset<>, smp::is_subset<>>()
    .test<_1>()
    .test<_1, list<>>()
    .test<_1, list<_1>>()
    .test<_1, list<>, list<>>()
    .test<_1, list<>, list<>, list<>>()
    .test<_1, list<>, list<>, list<>, list<>>()
    .test<_0, list<>, seq_0>()
    .test<_0, list<>, seq_0, seq_0>()
    .test<_0, list<>, seq_0, seq_0, seq_0>()
    .test<_1, seq_0_1_2_3, list<_1>>()
    .test<_0, seq_0_1_2_3, list<_5>>()
    .test<_1, seq_0_1_2_3, list<_1>, list<_2>>()
    .test<_0, seq_0_1_2_3, list<_1>, list<_2, _4>>()
    .test<_1, seq_0_1_2_3, list<_1>, list<_2>, list<_3, _0>>()
    .test<_0, seq_0_1_2_3, list<_5>, list<_5>, list<_4, _8>>()
    .not_invocable<_0>()
    .not_invocable<list<>, _0>()
    .not_invocable<list<>, list<>, _0>()
    ;

  test_context<is_subset_with<equal<>>, smp::is_subset_with<smp::equal<>>>()
    .test<_1>()
    .test<_1, list<>>()
    .test<_1, list<_1>>()
    .test<_1, list<>, list<>>()
    .test<_1, list<>, list<>, list<>>()
    .test<_1, list<>, list<>, list<>, list<>>()
    .test<_0, list<>, seq_0>()
    .test<_0, list<>, seq_0, seq_0>()
    .test<_0, list<>, seq_0, seq_0, seq_0>()
    .test<_1, seq_0_1_2_3, list<_1>>()
    .test<_0, seq_0_1_2_3, list<_5>>()
    .test<_1, seq_0_1_2_3, list<_1>, list<_2>>()
    .test<_0, seq_0_1_2_3, list<_1>, list<_2, _4>>()
    .test<_1, seq_0_1_2_3, list<_1>, list<_2>, list<_3, _0>>()
    .test<_0, seq_0_1_2_3, list<_5>, list<_5>, list<_4, _8>>()
    .not_invocable<_0>()
    .not_invocable<list<>, _0>()
    .not_invocable<list<>, list<>, _0>()
    ;

  ut::not_invocable<smp::is_subset<bad_function>>();
  ut::not_invocable<smp::is_subset_with<smp::always<na>>, list<_1>, list<_0>>();
  ut::not_invocable<smp::is_subset_with<always<void>>, list<_1>, list<_0>>();
  ut::not_invocable<smp::is_subset_with<always<void>, bad_function>>();
  ut::not_invocable<smp::is_subset_with<always<true_>, bad_function>>();
  ut::not_invocable<smp::is_subset_with<bad_function, bad_function>>();
  ut::not_invocable<smp::is_subset_with<bad_function, bad_function>, _1, _1, _1>();
}

TEST_SUITE_END()
