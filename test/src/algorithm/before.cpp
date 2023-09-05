// SPDX-FileCopyrightText: 2023 Jonathan Poelen <jonathan.poelen@gmail.com>
// SPDX-License-Identifier: MIT
#include "test.hpp"
#include "test/numbers.hpp"

#include "jln/mp/smp/algorithm/before.hpp"
#include "jln/mp/smp/utility/always.hpp"
#include "jln/mp/smp/list/size.hpp"

TEST_SUITE_BEGIN()

TEST()
{
  using namespace jln::mp;
  using namespace ut::ints;

  using l0 = list<>;
  using l1 = list<_1>;
  using l2 = list<_1, _2>;

  test_mulary_pack<before, l0>();
  test_mulary_pack<before, l1>();
  test_mulary_pack<before, l2>();
  test_mulary_pack<before, l0, listify>();
  test_mulary_pack<before, l1, listify>();
  test_mulary_pack<before, l2, listify>();

  test_context<
    before<l0, listify, always<void>>,
    smp::before<l0, smp::listify, smp::always<void>>
  >()
    .test<list<>>()
    .test<list<>, _0>()
    ;

  test_context<
    before<l1, listify, always<void>>,
    smp::before<l1, smp::listify, smp::always<void>>
  >()
    .test<void>()
    .test<void, _0>()
    .test<list<>, _1>()
    .test<seq_0, _0, _1>()
    .test<list<>, _1, _2>()
    .test<seq_0, _0, _1, _2>()
    .test<seq_0, _0, _1, _2, _3>()
    ;

  test_context<
    before<l2, listify, always<void>>,
    smp::before<l2, smp::listify, smp::always<void>>
  >()
    .test<void>()
    .test<void, _0>()
    .test<void, _0, _1>()
    .test<seq_0, _0, _1, _2>()
    .test<seq_0, _0, _1, _2, _3>()
    .test<seq_0, _0, _1, _2, _3, _2>()
    ;

  test_context<
    before<l1, listify, size<>>,
    smp::before<l1, smp::listify, smp::size<>>
  >()
    .test<_0>()
    .test<_1, _0>()
    .test<list<>, _1>()
    .test<seq_0, _0, _1>()
    .test<seq_0_0, _0, _0, _1>()
    ;

  test_context<before<int>, smp::before<int>>()
    .not_invocable<>()
    .not_invocable<int>()
    ;

  ut::not_invocable<smp::before<int>>();
  ut::not_invocable<smp::before<l0, bad_function>>();
}

TEST_SUITE_END()
