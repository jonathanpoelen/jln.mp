// SPDX-FileCopyrightText: 2024 Jonathan Poelen <jonathan.poelen@gmail.com>
// SPDX-License-Identifier: MIT
#include "test.hpp"
#include "test/numbers.hpp"

#include "jln/mp/smp/functional/compare_with.hpp"
#include "jln/mp/smp/algorithm/min_element.hpp"
#include "jln/mp/number/number.hpp"

TEST_SUITE_BEGIN()

TEST()
{
  using namespace jln::mp;
  using namespace ut::ints;

  test_unary_pack<min_element>();
  test_binary_pack<min_element_with>();

  test_unary_pack<last_min_element>();
  test_binary_pack<last_min_element_with>();

  ut::same<_0, emp::min_element<seq_0_1_0_2_0_3_0>>();
  ut::same<_1, emp::min_element<seq_3_2_1>>();
  ut::same<_1, emp::min_element_xs<_3, _2, _1>>();
  ut::same<_1, emp::min_element_c<3, 2, 1>>();
  static_assert(1 == emp::min_element_v<seq_3_2_1>);
  static_assert(1 == emp::min_element_xs_v<_3, _2, _1>);
  static_assert(1 == emp::min_element_c_v<3, 2, 1>);

  ut::same<_0, emp::last_min_element<seq_0_1_0_2_0_3_0>>();
  ut::same<_1, emp::last_min_element<seq_3_2_1>>();
  ut::same<_1, emp::last_min_element_xs<_3, _2, _1>>();
  ut::same<_1, emp::last_min_element_c<3, 2, 1>>();
  static_assert(1 == emp::last_min_element_v<seq_3_2_1>);
  static_assert(1 == emp::last_min_element_xs_v<_3, _2, _1>);
  static_assert(1 == emp::last_min_element_c_v<3, 2, 1>);

  test_context<min_element<>, smp::min_element<>>()
    .test<_0, _0, _1>()
    .test<_0, _1, _0>()
    .test<_1, _1, _2>()
    .test<_0, _1, _2, _0, _3>()
    .not_invocable<>()
    .not_invocable<_0, bad_number>()
    ;

  test_context<last_min_element<>, smp::last_min_element<>>()
    .test<_0, _0, _1>()
    .test<_0, _1, _0>()
    .test<_1, _1, _2>()
    .test<_0, _1, _2, _0, _3>()
    .not_invocable<>()
    .not_invocable<_0, bad_number>()
    ;

  using cmp = compare_with<push_back<_2, div<>>>;
  using smp_cmp = smp::compare_with<smp::push_back<_2, smp::div<>>>;

  test_context<min_element_with<cmp>, smp::min_element_with<smp_cmp>>()
    .test<_0, _0, _1>()
    .test<_1, _1, _0>()
    .test<_1, _1, _2>()
    .test<_1, _1, _2, _0, _3>()
    .not_invocable<>()
    .not_invocable<_0, bad_number>()
    ;

  test_context<last_min_element_with<cmp>, smp::last_min_element_with<smp_cmp>>()
    .test<_1, _0, _1>()
    .test<_0, _1, _0>()
    .test<_1, _1, _2>()
    .test<_0, _1, _2, _0, _3>()
    .not_invocable<>()
    .not_invocable<_0, bad_number>()
    ;

  ut::not_invocable<smp::min_element_with<bad_function>, _0, _1>();
  ut::not_invocable<smp::min_element<bad_function>, _0>();

  ut::not_invocable<smp::last_min_element_with<bad_function>, _0, _1>();
  ut::not_invocable<smp::last_min_element<bad_function>, _0>();
}

TEST_SUITE_END()
