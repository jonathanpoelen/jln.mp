// SPDX-FileCopyrightText: 2023 Jonathan Poelen <jonathan.poelen@gmail.com>
// SPDX-License-Identifier: MIT
#include "test.hpp"
#include "test/numbers.hpp"

#include "jln/mp/smp/algorithm/before_after.hpp"
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

  test_mulary_pack<before_after_with, l0>();
  test_mulary_pack<before_after_with, l1>();
  test_mulary_pack<before_after_with, l2>();
  test_mulary_pack<before_after_with, l0, listify>();
  test_mulary_pack<before_after_with, l1, listify>();
  test_mulary_pack<before_after_with, l2, listify>();
  test_binary_pack<before_after_with, l0, listify, listify>();
  test_binary_pack<before_after_with, l1, listify, listify>();
  test_binary_pack<before_after_with, l2, listify, listify>();
  test_binary_pack<before_after_with, l0, listify, listify, listify>();
  test_binary_pack<before_after_with, l1, listify, listify, listify>();
  test_binary_pack<before_after_with, l2, listify, listify, listify>();

  test_context<
    before_after<l0, listify, always<void>>,
    smp::before_after<l0, smp::listify, smp::always<void>>
  >()
    .test<list<list<>, list<>>>()
    .test<list<list<>, seq_0>, _0>()
    ;

  test_context<
    before_after<l1, listify, always<void>>,
    smp::before_after<l1, smp::listify, smp::always<void>>
  >()
    .test<void>()
    .test<void, _0>()
    .test<list<list<>, list<>>, _1>()
    .test<list<seq_0, list<>>, _0, _1>()
    .test<list<list<>, seq_2>, _1, _2>()
    .test<list<seq_0, seq_2>, _0, _1, _2>()
    ;

  test_context<
    before_after<l2, listify, always<void>>,
    smp::before_after<l2, smp::listify, smp::always<void>>
  >()
    .test<void>()
    .test<void, _0>()
    .test<void, _0, _1>()
    .test<list<seq_0, list<>>, _0, _1, _2>()
    .test<list<list<>, seq_3>, _1, _2, _3>()
    .test<list<seq_0, seq_3>, _0, _1, _2, _3>()
    ;

  test_context<
    before_after<l1, listify, size<>>,
    smp::before_after<l1, smp::listify, smp::size<>>
  >()
    .test<_1, _0>()
    ;

  test_context<before_after<int>, smp::before_after<int>>()
    .not_invocable<>()
    .not_invocable<int>()
    ;

  ut::not_invocable<smp::before_after<int>>();
  ut::not_invocable<smp::before_after<l0, bad_function>>();
}

TEST_SUITE_END()
