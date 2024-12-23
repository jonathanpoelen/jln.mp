// SPDX-FileCopyrightText: 2023 Jonathan Poelen <jonathan.poelen@gmail.com>
// SPDX-License-Identifier: MIT
#include "test.hpp"
#include "test/numbers.hpp"

#include "jln/mp/smp/list/size.hpp"
#include "jln/mp/smp/algorithm/repeat_index.hpp"

TEST_SUITE_BEGIN()

TEST()
{
  using namespace jln::mp;
  using namespace ut::ints;

  test_mulary_pack<repeat_index>();

  ut::same<list<seq_0_0_0>, emp::repeat_index<seq_3>>();
  ut::same<list<_3>, emp::repeat_index_with<seq_3, mp::size<>>>();

  test_context<repeat_index<>, smp::repeat_index<>>()
    .test<list<>>()
    .test<list<seq_0>, _1>()
    .test<list<seq_0, seq_1_1>, _1, _2>()
    .test<list<seq_0, seq_1_1, seq_2_2>, _1, _2, _2>()
    .test<list<list<_0, _0, _0, _0, _0>, list<>, seq_2>, _5, _0, _1>()
    .not_invocable<void>()
    .not_invocable<number<-1>>()
    ;

  test_context<repeat_index_with<mp::size<>>, smp::repeat_index_with<smp::size<>>>()
    .test<list<>>()
    .test<list<_1>, _1>()
    .test<list<_1, _2>, _1, _2>()
    .test<list<_1, _2, _2>, _1, _2, _2>()
    .test<list<_5, _0, _1>, _5, _0, _1>()
    .not_invocable<void>()
    .not_invocable<number<-1>>()
    ;

  ut::invocable<smp::repeat_index_with<bad_function>>();
  ut::not_invocable<smp::repeat_index_with<bad_function>, _0>();
  ut::not_invocable<smp::repeat_index_with<listify, bad_function>>();
  ut::not_invocable<smp::repeat_index_with<listify, bad_function>, _0>();
}

TEST_SUITE_END()
