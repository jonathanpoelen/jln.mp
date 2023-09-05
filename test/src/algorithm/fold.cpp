// SPDX-FileCopyrightText: 2023 Jonathan Poelen <jonathan.poelen@gmail.com>
// SPDX-License-Identifier: MIT
#include "test.hpp"
#include "test/numbers.hpp"

#include "jln/mp/smp/algorithm/fold.hpp"
#include "jln/mp/smp/list/pop_front.hpp"
#include "jln/mp/smp/number/operators.hpp"

TEST_SUITE_BEGIN()

TEST()
{
  using namespace jln::mp;
  using namespace ut::ints;

  ut::same<list<list<list<_0, _1>, _2>, _3>,
    emp::fold<seq_1_2_3, _0, listify>>();

  ut::same<list<list<_1, _2>, _3>,
    emp::reduce<seq_1_2_3, listify>>();

  test_binary_pack<fold>();
  test_unary_pack<fold, listify>();

  test_context<fold<listify>, smp::fold<smp::listify>>()
    .test<_0, _0>()
    .test<list<_0, _1>, _0, _1>()
    .test<list<list<list<_0, _1>, _2>, _3>, _0, _1, _2, _3>()
    .test<list<list<list<list<list<_0, _1>, _2>, _3>, _4>, _5>,
      _0, _1, _2, _3, _4, _5>()
    .not_invocable<>()
    ;

  test_context<
    fold<pop_front<identity>>,
    smp::fold<smp::pop_front<smp::identity>>
  >()
    .test<_0, _0>()
    .test<_1, _0, _1>()
    .test<_3, _0, _1, _2, _3>()
    .not_invocable<>()
    .not_invocable<na>()
    .not_invocable<_0, na>()
    .not_invocable<_0, _1, na>()
    ;

  ut::not_invocable<smp::fold<smp::always<na>>, _1, _1, _1>();
  ut::not_invocable<smp::fold<listify, bad_function>, _1>();
  ut::not_invocable<smp::fold<listify, bad_function>, _1, _1, _1>();
  ut::not_invocable<smp::fold<bad_function, bad_function>, _1>();
  ut::not_invocable<smp::fold<bad_function, bad_function>, _1, _1, _1>();
  ut::not_invocable<smp::fold<bad_function, bad_function>, _1, _1, _1, _1, _1>();
  ut::not_invocable<smp::fold<smp::add<>>, _1, _1, _1, _1, _1, void>();
  ut::not_invocable<smp::fold<smp::add<>>, void, _1, _1, _1, _1, _1>();
  ut::not_invocable<smp::fold<smp::add<>>,
    _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, void>();
  ut::not_invocable<smp::fold<smp::add<>>,
    void, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1>();
}

TEST_SUITE_END()
