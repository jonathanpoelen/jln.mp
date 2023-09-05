// SPDX-FileCopyrightText: 2023 Jonathan Poelen <jonathan.poelen@gmail.com>
// SPDX-License-Identifier: MIT
#include "test.hpp"
#include "test/numbers.hpp"

#include "jln/mp/smp/algorithm/powerset.hpp"
#include "jln/mp/smp/utility/always.hpp"

TEST_SUITE_BEGIN()

TEST()
{
  using namespace jln::mp;
  using namespace ut::ints;

  test_mulary_pack<powerset>();

  ut::same<list<>, emp::powerset<list<>>>();
  ut::same<list<list<>, list<_0>, list<_1>, list<_0, _1>>,
    emp::powerset<list<_0, _1>>>();

  test_context<powerset<>, smp::powerset<>>()
    .test<list<>>()
    .test<list<list<>, list<_0>>, _0>()
    .test<list<list<>, list<_0>, list<_1>, list<_0, _1>>, _0, _1>()
    .test<list<
      list<>, list<_0>, list<_1>, list<_0, _1>,
      list<_2>, list<_0, _2>, list<_1, _2>, list<_0, _1, _2>>,
      _0, _1, _2>()
    .test<list<
      list<>, list<_0>, list<_1>, list<_0, _1>,
      list<_2>, list<_0, _2>, list<_1, _2>, list<_0, _1, _2>,
      list<_3>, list<_0, _3>, list<_1, _3>, list<_0, _1, _3>,
      list<_2, _3>, list<_0, _2, _3>, list<_1, _2, _3>, list<_0, _1, _2, _3>>,
      _0, _1, _2, _3>()
    ;

  ut::not_invocable<smp::powerset<smp::always<na>>, _1, _1, _1>();
  ut::not_invocable<smp::powerset<bad_function>, _1, _1, _1>();
}

TEST_SUITE_END()
