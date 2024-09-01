// SPDX-FileCopyrightText: 2023 Jonathan Poelen <jonathan.poelen@gmail.com>
// SPDX-License-Identifier: MIT
#include "test.hpp"
#include "test/numbers.hpp"

#include "jln/mp/smp/algorithm/reverse_fold.hpp"
#include "jln/mp/smp/list/pop_front.hpp"
#include "jln/mp/smp/number/operators.hpp"

TEST_SUITE_BEGIN()

TEST()
{
  using namespace jln::mp;
  using namespace ut::ints;

  ut::same<list<list<list<_3, _2>, _1>, _0>,
    emp::reverse_fold<seq_0_1_2, _3, listify>>();

  ut::same<list<>, emp::reverse_fold_or_else<list<>, listify>>();
  ut::same<list<list<list<_3, _2>, _1>, _0>,
    emp::reverse_fold_or_else<seq_0_1_2_3, listify, listify>>();

  test_binary_pack<reverse_fold>();
  test_unary_pack<reverse_fold, listify>();
  test_binary_pack<reverse_fold_or_else, listify>();
  test_unary_pack<reverse_fold_or_else, listify>();

  test_context<reverse_fold<listify>, smp::reverse_fold<smp::listify>>()
    .test<_0, _0>()
    .test<list<_0, _1>, _0, _1>()
    .test<list<list<list<_0, _3>, _2>, _1>, _0, _1, _2, _3>()
    .test<list<list<list<list<list<_0, _5>, _4>, _3>, _2>, _1>,
      _0, _1, _2, _3, _4, _5>()
    .not_invocable<>()
    ;

  test_context<
    reverse_fold<pop_front<identity>>,
    smp::reverse_fold<smp::pop_front<smp::identity>>
  >()
    .test<_0, _0>()
    .test<_1, _0, _1>()
    .test<_1, _0, _1, _2, _3>()
    .not_invocable<>()
    .not_invocable<na>()
    .not_invocable<_0, na>()
    .not_invocable<_0, _1, na>()
    ;

  test_context<
    reverse_fold_or_else<listify, listify>,
    smp::reverse_fold_or_else<smp::listify, smp::listify>
  >()
    .test<list<>>()
    .test<_0, _0>()
    .test<seq_1_0, _0, _1>()
    .test<list<list<list<_3, _2>, _1>, _0>, _0, _1, _2, _3>()
    .test<list<list<list<list<list<_5, _4>, _3>, _2>, _1>, _0>,
      _0, _1, _2, _3, _4, _5>()
    ;

  ut::not_invocable<smp::reverse_fold<smp::always<na>>, _1, _1, _1>();
  ut::not_invocable<smp::reverse_fold<listify, bad_function>, _1>();
  ut::not_invocable<smp::reverse_fold<listify, bad_function>, _1, _1, _1>();
  ut::not_invocable<smp::reverse_fold<bad_function, bad_function>, _1>();
  ut::not_invocable<smp::reverse_fold<bad_function, bad_function>, _1, _1, _1>();
  ut::not_invocable<smp::reverse_fold<bad_function, bad_function>, _1, _1, _1, _1, _1>();
  ut::not_invocable<smp::reverse_fold<smp::add<>>, _1, _1, _1, _1, _1, void>();
  ut::not_invocable<smp::reverse_fold<smp::add<>>, void, _1, _1, _1, _1, _1>();
  ut::not_invocable<smp::reverse_fold<smp::add<>>,
    _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, void>();
  ut::not_invocable<smp::reverse_fold<smp::add<>>,
    void, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1>();

  ut::not_invocable<smp::reverse_fold_or_else<smp::always<na>, smp::listify>, _1, _1, _1>();
  ut::not_invocable<smp::reverse_fold_or_else<smp::listify, smp::always<na>>>();
}

TEST_SUITE_END()
