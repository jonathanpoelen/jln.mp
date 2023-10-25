// SPDX-FileCopyrightText: 2023 Jonathan Poelen <jonathan.poelen@gmail.com>
// SPDX-License-Identifier: MIT
#include "test.hpp"
#include "test/numbers.hpp"

#include "jln/mp/smp/algorithm/split_once.hpp"
#include "jln/mp/smp/utility/always.hpp"
#include "jln/mp/smp/list/size.hpp"

TEST_SUITE_BEGIN()

TEST()
{
  using namespace jln::mp;
  using namespace ut::ints;

  test_mulary_pack<split_once_if>();
  test_mulary_pack<split_once_if, identity>();
  test_mulary_pack<split_once_if, identity, identity>();

  test_context<split_once_if<identity>, smp::split_once_if<smp::identity>>()
    .test<list<>>()
    .test<list<>, _0>()
    .test<list<list<>, list<>>, _1>()
    .test<list<seq_0, list<>>, _0, _1>()
    .test<list<list<>, seq_0>, _1, _0>()
    .test<list<seq_0, seq_0>, _0, _1, _0>()
    .not_invocable<void>()
    ;

  test_context<split_once<_2>, smp::split_once<_2>>()
    .test<list<>>()
    .test<list<>, void>()
    .test<list<>, _0>()
    .test<list<>, _0, _1>()
    .test<list<seq_0_1, list<>>, _0, _1, _2>()
    .test<list<seq_0_1, seq_3>, _0, _1, _2, _3>()
    ;

  ut::not_invocable<smp::split_once_if<smp::always<void>>, _1>();
  ut::not_invocable<smp::split_once_if<bad_function>, _1, _1, _1>();
  ut::not_invocable<smp::split_once_if<smp::identity, bad_function>, _1>();
}

TEST_SUITE_END()

