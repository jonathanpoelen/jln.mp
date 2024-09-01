// SPDX-FileCopyrightText: 2023 Jonathan Poelen <jonathan.poelen@gmail.com>
// SPDX-License-Identifier: MIT
#include "test.hpp"
#include "test/numbers.hpp"

#include "jln/mp/smp/algorithm/reverse_fold_right.hpp"
#include "jln/mp/smp/list/pop_front.hpp"
#include "jln/mp/smp/number/operators.hpp"

TEST_SUITE_BEGIN()

TEST()
{
  using namespace jln::mp;
  using namespace ut::ints;

  ut::same<list<_2, list<_1, list<_0, _3>>>,
    emp::reverse_fold_right<seq_0_1_2, _3, listify>>();

  ut::same<list<>, emp::reverse_fold_right_or_else<list<>, listify>>();
  ut::same<list<_3, list<_2, list<_1, _0>>>,
    emp::reverse_fold_right_or_else<seq_0_1_2_3, listify>>();

  ut::same<list<_2, list<_1, _0>>,
    emp::reverse_reduce<seq_0_1_2, listify>>();

  test_binary_pack<reverse_fold_right>();
  test_unary_pack<reverse_fold_right, listify>();
  test_binary_pack<reverse_fold_right_or_else, listify>();
  test_unary_pack<reverse_fold_right_or_else, listify>();

  test_context<reverse_fold_right<listify>, smp::reverse_fold_right<smp::listify>>()
    .test<_0, _0>()
    .test<list<_1, _0>, _0, _1>()
    .test<list<_3, list<_2, list<_1, _0>>>, _0, _1, _2, _3>()
    .test<list<_5, list<_4, list<_3, list<_2, list<_1, _0>>>>>,
      _0, _1, _2, _3, _4, _5>()
    .test<list<_9, list<_8, list<_7, list<_6, list<_5,
          list<_4, list<_3, list<_2, list<_1, _0>>>>>>>>>,
      _0, _1, _2, _3, _4, _5, _6, _7, _8, _9>()
    .not_invocable<>()
    ;

  test_context<
    reverse_fold_right<pop_front<identity>>,
    smp::reverse_fold_right<smp::pop_front<smp::identity>>
  >()
    .test<_0, _0>()
    .test<_0, _0, _1>()
    .test<_0, _0, _1, _2, _3>()
    .not_invocable<>()
    .not_invocable<na>()
    .not_invocable<_0, na>()
    .not_invocable<_0, _1, na>()
    ;

  test_context<
    reverse_fold_right_or_else<listify, listify>,
    smp::reverse_fold_right_or_else<smp::listify, smp::listify>
  >()
    .test<list<>>()
    .test<_0, _0>()
    .test<list<_1, _0>, _0, _1>()
    .test<list<_3, list<_2, list<_1, _0>>>, _0, _1, _2, _3>()
    .test<list<_5, list<_4, list<_3, list<_2, list<_1, _0>>>>>,
      _0, _1, _2, _3, _4, _5>()
    .test<list<_9, list<_8, list<_7, list<_6, list<_5,
          list<_4, list<_3, list<_2, list<_1, _0>>>>>>>>>,
      _0, _1, _2, _3, _4, _5, _6, _7, _8, _9>()
    ;

  ut::not_invocable<smp::reverse_fold_right<smp::always<na>>, _1, _1, _1>();
  ut::not_invocable<smp::reverse_fold_right<listify, bad_function>, _1>();
  ut::not_invocable<smp::reverse_fold_right<listify, bad_function>, _1, _1, _1>();
  ut::not_invocable<smp::reverse_fold_right<bad_function, bad_function>, _1>();
  ut::not_invocable<smp::reverse_fold_right<bad_function, bad_function>, _1, _1, _1>();
  ut::not_invocable<smp::reverse_fold_right<bad_function, bad_function>, _1, _1, _1, _1, _1>();
  ut::not_invocable<smp::reverse_fold_right<smp::add<>>, _1, _1, _1, _1, _1, void>();
  ut::not_invocable<smp::reverse_fold_right<smp::add<>>, void, _1, _1, _1, _1, _1>();
  ut::not_invocable<smp::reverse_fold_right<smp::add<>>,
    _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, void>();
  ut::not_invocable<smp::reverse_fold_right<smp::add<>>,
    void, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1>();

  ut::not_invocable<smp::reverse_fold_right_or_else<smp::always<na>, smp::listify>, _1, _1, _1>();
  ut::not_invocable<smp::reverse_fold_right_or_else<smp::listify, smp::always<na>>>();
}

TEST_SUITE_END()
