// SPDX-FileCopyrightText: 2023 Jonathan Poelen <jonathan.poelen@gmail.com>
// SPDX-License-Identifier: MIT
#include "test.hpp"
#include "test/numbers.hpp"

#include "jln/mp/smp/algorithm/fold_right.hpp"
#include "jln/mp/smp/list/at.hpp"
#include "jln/mp/smp/list/listify.hpp"
#include "jln/mp/smp/number/operators.hpp"

TEST_SUITE_BEGIN()

TEST()
{
  using namespace jln::mp;
  using namespace ut::ints;

  ut::same<list<_0, list<_1, list<_2, _3>>>,
    emp::fold_right<seq_0_1_2, _3, listify>>();

  ut::same<_0, emp::fold_right_or_else<list<>, listify, size<>>>();
  ut::same<list<_0, list<_1, list<_2, _3>>>,
    emp::fold_right_or_else<seq_0_1_2_3, listify, size<>>>();

  test_binary_pack<fold_right>();
  test_unary_pack<fold_right, listify>();
  test_binary_pack<fold_right_or_else, listify>();
  test_unary_pack<fold_right_or_else, listify>();

  test_context<fold_right<listify>, smp::fold_right<smp::listify>>()
    .test<_0, _0>()
    .test<list<_1, _0>, _0, _1>()
    .test<list<_1, list<_2, list<_3, _0>>>, _0, _1, _2, _3>()
    .test<list<_1, list<_2, list<_3, list<_4, list<_5, _0>>>>>,
      _0, _1, _2, _3, _4, _5>()
    .not_invocable<>()
    ;

  test_context<
    fold_right<at1<identity>>,
    smp::fold_right<smp::at1<smp::identity>>
  >()
    .test<_0, _0>()
    .test<_0, _0, _1>()
    .test<_0, _0, _1, _2, _3>()
    .not_invocable<>()
    .not_invocable<na>()
    .not_invocable<_0, na>()
    .not_invocable<_0, _1, na>()
    ;

  test_context<fold_right_or_else<listify, listify>, smp::fold_right_or_else<smp::listify, smp::listify>>()
    .test<list<>>()
    .test<_0, _0>()
    .test<seq_0_1, _0, _1>()
    .test<list<_0, list<_1, list<_2, _3>>>, _0, _1, _2, _3>()
    .test<list<_0, list<_1, list<_2, list<_3, list<_4, _5>>>>>,
      _0, _1, _2, _3, _4, _5>()
    ;

  ut::not_invocable<smp::fold_right<smp::always<na>>, _1, _1, _1>();
  ut::not_invocable<smp::fold_right<listify, bad_function>, _1>();
  ut::not_invocable<smp::fold_right<listify, bad_function>, _1, _1, _1>();
  ut::not_invocable<smp::fold_right<bad_function, bad_function>, _1>();
  ut::not_invocable<smp::fold_right<bad_function, bad_function>, _1, _1, _1>();
  ut::not_invocable<smp::fold_right<smp::add<>>, _1, _1, _1, _1, _1, void>();
  ut::not_invocable<smp::fold_right<smp::add<>>, void, _1, _1, _1, _1, _1>();
  ut::not_invocable<smp::fold_right<smp::add<>>,
    _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, void>();
  ut::not_invocable<smp::fold_right<smp::add<>>,
    void, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1>();

  ut::not_invocable<smp::fold_right_or_else<smp::always<na>, smp::listify>, _1, _1, _1>();
  ut::not_invocable<smp::fold_right_or_else<smp::listify, smp::always<na>>>();
}

TEST_SUITE_END()
