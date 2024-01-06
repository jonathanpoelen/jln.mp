// SPDX-FileCopyrightText: 2023 Jonathan Poelen <jonathan.poelen@gmail.com>
// SPDX-License-Identifier: MIT
#include "test.hpp"
#include "test/numbers.hpp"

#include "jln/mp/smp/algorithm/split_after.hpp"
#include "jln/mp/smp/number/operators.hpp"
#include "jln/mp/smp/list/push_back.hpp"

TEST_SUITE_BEGIN()

TEST()
{
  using namespace jln::mp;
  using namespace ut::ints;

  using e = list<>;
  using l_mod_3 = list<
    list<_0>,
    list<_1, _2, _3>,
    list<_4, _5, _6>,
    list<_7, _8, _9>,
    list<>
  >;

  ut::same<l_mod_3, emp::split_after_if<seq_0_1_2_3_4_5_6_7_8_9,
    push_back<_3, mod<not_<>>>>>();
  ut::same<list<seq_0, seq_1_0, list<_2, _0>, list<_3, _0>, e>,
    emp::split_after<seq_0_1_0_2_0_3_0, _0>>();

  test_unary_pack<split_after_if>();
  test_mulary_pack<split_after_if, identity>();
  test_unary_pack<split_after_if_with>();
  test_mulary_pack<split_after_if_with, identity>();

  test_context<split_after_if<not_<>>, smp::split_after_if<smp::not_<>>>()
    .test<e>()
    .test<list<seq_1>, _1>()
    .test<list<seq_1_1_1>, _1, _1, _1>()
    .test<list<seq_0, e>, _0>()
    .test<list<seq_0, seq_0, seq_0, e>, _0, _0, _0>()
    .test<list<list<_1, _0>, list<_2, _0>, list<_3>>, _1, _0, _2, _0, _3>()
    .test<list<list<_1, _2, _0>, list<_3>>, _1, _2, _0, _3>()
    .test<list<seq_0, list<_1, _2, _0>, list<_3>>, _0, _1, _2, _0, _3>()
    .test<list<list<_1, _2, _0>, list<_3, _0>, e>, _1, _2, _0, _3, _0>()
    .not_invocable<bad_number>()
    ;

  test_context<split_after<_2>, smp::split_after<_2>>()
    .test<list<>>()
    .test<list<seq_1>, _1>()
    .test<list<seq_1_2, seq_3_2, seq_5>, _1, _2, _3, _2, _5>()
    ;

  test_context<split_after_with<_2, size<>>, smp::split_after_with<_2, smp::size<>>>()
    .test<list<>>()
    .test<list<_1>, _1>()
    .test<list<_2, _2, _1>, _1, _2, _3, _2, _5>()
    ;

  ut::same<list<>, smp::split_after_if_with<smp::is<int>, bad_function>::f<>>();
  ut::same<list<>, smp::split_after_if_with<bad_function, bad_function>::f<>>();

  ut::not_invocable<smp::split_after<void, bad_function>, _1, _1, _1>();
  ut::not_invocable<smp::split_after_if<bad_function>, _1, _1, _1>();
  ut::not_invocable<smp::split_after_if<always<void>, bad_function>, _1, _1, _1>();
  ut::not_invocable<smp::split_after_if<bad_function, bad_function>, _1, _1, _1>();
  ut::not_invocable<smp::split_after_if_with<bad_function>, _1, _1, _1>();
  ut::not_invocable<smp::split_after_if_with<smp::always<na>>, _1, _1, _1>();
  ut::not_invocable<smp::split_after_if_with<smp::is<int>, bad_function>, _1, _1, _1>();
  ut::not_invocable<smp::split_after_if_with<smp::is<int>, smp::always<na>>, _1, _1, _1>();
}

TEST_SUITE_END()
