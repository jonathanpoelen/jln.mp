// SPDX-FileCopyrightText: 2024 Jonathan Poelen <jonathan.poelen@gmail.com>
// SPDX-License-Identifier: MIT
#include "test.hpp"
#include "test/numbers.hpp"

#include "jln/mp/smp/algorithm/compare_with.hpp"
#include "jln/mp/smp/algorithm/max_element.hpp"
#include "jln/mp/number/number.hpp"

TEST_SUITE_BEGIN()

TEST()
{
  using namespace jln::mp;
  using namespace ut::ints;

  test_unary_pack<max_element>();
  test_binary_pack<max_element_with>();

  test_unary_pack<last_max_element>();
  test_binary_pack<last_max_element_with>();

  ut::same<_3, emp::max_element<seq_0_1_0_2_0_3_0>>();
  ut::same<_3, emp::max_element<seq_3_2_1>>();
  static_assert(emp::max_element_v<seq_3_2_1> == 3);

  ut::same<_3, emp::last_max_element<emp::numbers<3, 0, 1, 2, 3>>>();
  ut::same<_3, emp::last_max_element<seq_3_2_1>>();
  static_assert(emp::last_max_element_v<seq_3_2_1> == 3);

  test_context<max_element<>, smp::max_element<>>()
    .test<_1, _0, _1>()
    .test<_1, _1, _0>()
    .test<_2, _1, _2>()
    .test<_3, _1, _2, _0, _3>()
    .not_invocable<>()
    .not_invocable<_0, bad_number>()
    ;

  test_context<last_max_element<>, smp::last_max_element<>>()
    .test<_1, _0, _1>()
    .test<_1, _1, _0>()
    .test<_2, _1, _2>()
    .test<_3, _1, _2, _0, _3>()
    .not_invocable<>()
    .not_invocable<_0, bad_number>()
    ;

  using cmp = compare_with<push_back<_2, div<>>>;
  using smp_cmp = smp::compare_with<smp::push_back<_2, smp::div<>>>;

  test_context<max_element_with<cmp>, smp::max_element_with<smp_cmp>>()
    .test<_0, _0, _1>()
    .test<_1, _1, _0>()
    .test<_2, _1, _2>()
    .test<_2, _1, _2, _0, _3>()
    .not_invocable<>()
    .not_invocable<_0, bad_number>()
    ;

  test_context<last_max_element_with<cmp>, smp::last_max_element_with<smp_cmp>>()
    .test<_1, _0, _1>()
    .test<_0, _1, _0>()
    .test<_2, _1, _2>()
    .test<_3, _1, _2, _0, _3>()
    .not_invocable<>()
    .not_invocable<_0, bad_number>()
    ;

  ut::not_invocable<smp::max_element_with<bad_function>, _0, _1>();
  ut::not_invocable<smp::max_element<bad_function>, _0>();

  ut::not_invocable<smp::last_max_element_with<bad_function>, _0, _1>();
  ut::not_invocable<smp::last_max_element<bad_function>, _0>();
}

TEST_SUITE_END()
