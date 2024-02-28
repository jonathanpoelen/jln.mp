// SPDX-FileCopyrightText: 2024 Jonathan Poelen <jonathan.poelen@gmail.com>
// SPDX-License-Identifier: MIT
#include "test.hpp"
#include "test/numbers.hpp"

#include "jln/mp/smp/algorithm/remove_suffix.hpp"
#include "jln/mp/smp/list/size.hpp"

TEST_SUITE_BEGIN()

TEST()
{
  using namespace jln::mp;
  using namespace ut::ints;

  using l0 = list<>;
  using l1 = list<_1>;
  using l2 = list<_1, _2>;

  test_unary_pack<remove_suffix, l0>();

  test_context<remove_suffix<l0>, smp::remove_suffix<l0>>()
    .test<l0>()
    .test<seq_0, _0>()
    ;

  test_context<remove_suffix<l1>, smp::remove_suffix<l1>>()
    .test<l0>()
    .test<seq_0, _0>()
    .test<l0, _1>()
    .test<seq_2, _2>()
    .test<seq_0, _0, _1>()
    .test<seq_1_2, _1, _2>()
    ;

  test_context<remove_suffix<l2>, smp::remove_suffix<l2>>()
    .test<l0>()
    .test<seq_0, _0>()
    .test<seq_0_1, _0, _1>()
    .test<seq_0, _0, _1, _2>()
    .test<seq_0_1_2_3, _0, _1, _2, _3>()
    .test<l0, _1, _2>()
    .test<seq_1_2_3, _1, _2, _3>()
    ;

  test_context<remove_suffix<l2, listify, size<>>, smp::remove_suffix<l2, smp::listify, smp::size<>>>()
    .test<_0>()
    .test<_1, _0>()
    .test<_2, _0, _1>()
    .test<seq_0, _0, _1, _2>()
    .test<_4, _0, _1, _2, _3>()
    .test<l0, _1, _2>()
    .test<_3, _1, _2, _3>()
    ;

  test_context<remove_suffix<int>, smp::remove_suffix<int>>()
    .not_invocable<>()
    .not_invocable<int>()
    ;

  ut::not_invocable<smp::remove_suffix<int>>();

  ut::invocable<smp::remove_suffix<l0, listify, bad_function>>();
  ut::not_invocable<smp::remove_suffix<l0, bad_function, listify>>();
  ut::invocable<smp::remove_suffix<l0, listify, bad_function>, _1>();
  ut::not_invocable<smp::remove_suffix<l0, bad_function, listify>, _1>();

  ut::not_invocable<smp::remove_suffix<l1, listify, bad_function>>();
  ut::invocable<smp::remove_suffix<l1, bad_function, listify>>();
  ut::invocable<smp::remove_suffix<l1, listify, bad_function>, _1>();
  ut::not_invocable<smp::remove_suffix<l1, bad_function, listify>, _1>();
}

TEST_SUITE_END()
