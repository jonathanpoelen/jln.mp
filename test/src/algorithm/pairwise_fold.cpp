// SPDX-FileCopyrightText: 2023 Jonathan Poelen <jonathan.poelen@gmail.com>
// SPDX-License-Identifier: MIT
#include "test.hpp"
#include "test/numbers.hpp"

#include "jln/mp/smp/algorithm/pairwise_fold.hpp"
#include "jln/mp/smp/number/operators.hpp"
#include "jln/mp/smp/list/size.hpp"
#include "jln/mp/smp/number/operators.hpp"

TEST_SUITE_BEGIN()

TEST()
{
  using namespace jln::mp;
  using namespace ut::ints;

  test_mulary_pack<pairwise_fold, listify>();
  test_mulary_pack<pairwise_fold_and_transform_front, listify, listify>();

  ut::same<list<_0, seq_0_1, seq_1_2, seq_2_3>, emp::pairwise_fold<seq_0_1_2_3, listify>>();

  test_context<pairwise_fold<listify>, smp::pairwise_fold<smp::listify>>()
    .test<list<>>()
    .test<list<_0>, _0>()
    .test<list<_0, seq_0_1>, _0, _1>()
    ;

  test_context<
    pairwise_fold_and_transform_front<listify, listify>,
    smp::pairwise_fold_and_transform_front<smp::listify, smp::listify>
  >()
    .test<list<>>()
    .test<list<seq_0>, _0>()
    .test<list<seq_0, seq_0_1>, _0, _1>()
    ;

  test_context<pairwise_fold<mp::add<>>, smp::pairwise_fold<smp::add<>>>()
    .test<list<>>()
    .test<list<_0>, _0>()
    .test<list<_0, _1>, _0, _1>()
    .test<list<_0, _1, _3>, _0, _1, _2>()
    .not_invocable<_0, seq_0>()
    ;

  ut::not_invocable<smp::pairwise_fold<identity>, _1, _1>();
  ut::not_invocable<smp::pairwise_fold<bad_function>, _1, _1>();
  ut::not_invocable<smp::pairwise_fold<smp::listify, bad_function>, _1>();
  ut::not_invocable<smp::pairwise_fold_and_transform_front<smp::listify, bad_function>, _1>();
}

TEST_SUITE_END()
