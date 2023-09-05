// SPDX-FileCopyrightText: 2023 Jonathan Poelen <jonathan.poelen@gmail.com>
// SPDX-License-Identifier: MIT
#include "test.hpp"
#include "test/numbers.hpp"

#include "jln/mp/smp/algorithm/fold_tree.hpp"
#include "jln/mp/smp/list/pop_front.hpp"
#include "jln/mp/smp/number/operators.hpp"

TEST_SUITE_BEGIN()

TEST()
{
  using namespace jln::mp;
  using namespace ut::ints;

  ut::same<list<>, emp::fold_tree<list<>, listify, listify>>();
  ut::same<list<list<_0, _1>, _2>, emp::fold_tree<seq_0_1_2, listify>>();

  test_binary_pack<fold_tree>();
  test_mulary_pack<fold_tree, listify>();
  test_binary_pack<fold_balanced_tree>();
  test_mulary_pack<fold_balanced_tree, listify>();

  test_context<fold_tree<listify>, smp::fold_tree<smp::listify>>()
    .test<_0, _0>()
    .test<list<_0, _1>, _0, _1>()
    .test<list<list<_0, _1>, _2>, _0, _1, _2>()
    .test<list<list<_0, _1>, list<_2, _3>>, _0, _1, _2, _3>()
    .test<list<list<list<_0, _1>, list<_2, _3>>, _4>, _0, _1, _2, _3, _4>()
    .test<list<list<list<_0, _1>, list<_2, _3>>, list<_4, _5>>,
        _0, _1, _2, _3, _4, _5>()
    .test<list<list<list<_0, _1>, list<_2, _3>>, list<list<_4, _5>, _6>>,
        _0, _1, _2, _3, _4, _5, _6>()
    .test<list<list<list<_0, _1>, list<_2, _3>>, list<list<_4, _5>, list<_6, _7>>>,
        _0, _1, _2, _3, _4, _5, _6, _7>()
    .test<list<list<list<list<_0, _1>, list<_2, _3>>, list<list<_4, _5>, list<_6, _7>>>, _8>,
        _0, _1, _2, _3, _4, _5, _6, _7, _8>()
    .not_invocable<>()
    ;

  test_context<fold_balanced_tree<listify>, smp::fold_balanced_tree<smp::listify>>()
    .test<_0, _0>()
    .test<list<_0, _1>, _0, _1>()
    .test<list<list<_0, _1>, _2>, _0, _1, _2>()
    .test<list<list<_0, _1>, list<_2, _3>>, _0, _1, _2, _3>()
    .test<list<list<list<_0, _1>, _2>, list<_3, _4>>, _0, _1, _2, _3, _4>()
    .test<list<list<list<_0, _1>, _2>, list<list<_3, _4>, _5>>,
        _0, _1, _2, _3, _4, _5>()
    .test<list<list<list<_0, _1>, list<_2, _3>>, list<list<_4, _5>, _6>>,
        _0, _1, _2, _3, _4, _5, _6>()
    .test<list<list<list<_0, _1>, list<_2, _3>>, list<list<_4, _5>, list<_6, _7>>>,
        _0, _1, _2, _3, _4, _5, _6, _7>()
    .test<list<list<list<list<_0, _1>, _2>, list<_3, _4>>, list<list<_5, _6>, list<_7, _8>>>,
        _0, _1, _2, _3, _4, _5, _6, _7, _8>()
    .test<list<list<list<list<_0, _1>, _2>, list<_3, _4>>, list<list<list<_5, _6>, _7>, list<_8, _9>>>,
        _0, _1, _2, _3, _4, _5, _6, _7, _8, _9>()
    .not_invocable<>()
    ;

  ut::not_invocable<smp::fold_tree<smp::always<na>>, _1, _1, _1>();
  ut::not_invocable<smp::fold_tree<listify, bad_function>, _1>();
  ut::not_invocable<smp::fold_tree<bad_function>, _1, _2>();
  ut::not_invocable<smp::fold_tree<add<>>, _1, _2, void>();

  ut::not_invocable<smp::fold_balanced_tree<listify, bad_function>, _1>();
  ut::not_invocable<smp::fold_balanced_tree<bad_function>, _1, _2>();
  ut::not_invocable<smp::fold_balanced_tree<add<>>, _1, _2, void>();
}

TEST_SUITE_END()
