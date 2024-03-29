// SPDX-FileCopyrightText: 2023 Jonathan Poelen <jonathan.poelen@gmail.com>
// SPDX-License-Identifier: MIT
#include "test.hpp"
#include "test/numbers.hpp"

#include "jln/mp/smp/utility/always.hpp"
#include "jln/mp/smp/algorithm/combine.hpp"

TEST_SUITE_BEGIN()

TEST()
{
  using namespace jln::mp;
  using namespace ut::ints;

  test_mulary_pack<combine>();

  ut::same<list<>, emp::combine<list<>>>();
  ut::same<list<
    list<_0, _0>, list<_0, _1>, list<_1, _0>, list<_1, _1>>,
    emp::combine<list<_0, _1>>>();

  test_context<combine<>, smp::combine<>>()
    .test<list<>>()
    .test<list<list<_0>>, _0>()
    .test<list<
      list<_0, _0>, list<_0, _1>,
      list<_1, _0>, list<_1, _1>>,
      _0, _1>()
    .test<list<
      list<_0, _0, _0>, list<_0, _0, _1>, list<_0, _0, _2>,
      list<_0, _1, _0>, list<_0, _1, _1>, list<_0, _1, _2>,
      list<_0, _2, _0>, list<_0, _2, _1>, list<_0, _2, _2>,
      list<_1, _0, _0>, list<_1, _0, _1>, list<_1, _0, _2>,
      list<_1, _1, _0>, list<_1, _1, _1>, list<_1, _1, _2>,
      list<_1, _2, _0>, list<_1, _2, _1>, list<_1, _2, _2>,
      list<_2, _0, _0>, list<_2, _0, _1>, list<_2, _0, _2>,
      list<_2, _1, _0>, list<_2, _1, _1>, list<_2, _1, _2>,
      list<_2, _2, _0>, list<_2, _2, _1>, list<_2, _2, _2>>,
      _0, _1, _2>()
    ;

  ut::not_invocable<smp::combine<smp::always<na>>>();
  ut::not_invocable<smp::combine<bad_function>>();
  ut::not_invocable<smp::combine<bad_function>, _1>();
  ut::not_invocable<smp::combine<bad_function>, _1, _1>();
}

TEST_SUITE_END()
