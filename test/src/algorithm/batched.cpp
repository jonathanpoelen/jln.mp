// SPDX-FileCopyrightText: 2023 Jonathan Poelen <jonathan.poelen@gmail.com>
// SPDX-License-Identifier: MIT
#include "test.hpp"
#include "test/numbers.hpp"

#include "jln/mp/smp/algorithm/batched.hpp"
#include "jln/mp/smp/utility/always.hpp"
#include "jln/mp/smp/number/operators.hpp"

TEST_SUITE_BEGIN()

TEST()
{
  using namespace jln::mp;
  using namespace ut::ints;

  test_mulary_pack<batched, _2>();
  test_mulary_pack<batched_with, _2, listify>();

  ut::same<list<list<_0, _2, _3>, list<_4, _5, _6>, list<_7>>,
    emp::batched<emp::numbers<0, 2, 3, 4, 5, 6, 7>, _3>>();
  ut::same<list<list<_0, _2, _3>, list<_4, _5, _6>>,
    emp::batched<emp::numbers<0, 2, 3, 4, 5, 6>, _3>>();

  test_context<batched<_3>, smp::batched<_3>>()
    .test<list<>>()
    .test<list<seq_0_1>, _0, _1>()
    .test<list<seq_0_1_2>, _0, _1, _2>()
    .test<list<seq_0_1_2, seq_3>, _0, _1, _2, _3>()
    .test<list<seq_0_1_2, list<_3, _4>>, _0, _1, _2, _3, _4>()
    .test<list<seq_0_1_2, list<_3, _4, _5>>, _0, _1, _2, _3, _4, _5>()
    .test<list<seq_0_1_2, list<_3, _4, _5>, list<_6>>, _0, _1, _2, _3, _4, _5, _6>()
    .test<list<seq_0_1_2, list<_3, _4, _5>, list<_6, _7>>, _0, _1, _2, _3, _4, _5, _6, _7>()
    .test<list<list<bad_number>>, bad_number>()
    ;

  test_context<batched_with<_3, add<>>, smp::batched_with<_3, smp::add<>>>()
    .test<list<>>()
    .test<list<_1>, _0, _1>()
    .test<list<_3>, _0, _1, _2>()
    .test<list<_3, _3>, _0, _1, _2, _3>()
    .test<list<_3, _7>, _0, _1, _2, _3, _4>()
    .test<list<_3, _12>, _0, _1, _2, _3, _4, _5>()
    .test<list<_3, _12, _6>, _0, _1, _2, _3, _4, _5, _6>()
    .test<list<_3, _12, _13>, _0, _1, _2, _3, _4, _5, _6, _7>()
    .not_invocable<bad_number>()
    .not_invocable<bad_number, bad_number, bad_number, bad_number>()
    ;

  test_context<batched<_0>, smp::batched<_0>>()
    .test<list<>>()
    .test<list<>, _0, _1>()
    ;

  test_context<batched_c<2, ut::binary>, smp::batched_c<2, try_contract<ut::binary>>, -1>()
    .not_invocable<>()
    .not_invocable<_0>()
    .not_invocable<_0, _1>()
    .test<list<seq_0_1, seq_2>, _0, _1, _2>()
    .test<list<seq_0_1, seq_2_3>, _0, _1, _2, _3>()
    .not_invocable<_0, _1, _2, _3, _4>()
    .not_invocable<_0, _1, _2, _3, _4, _5>()
    ;

  test_context<batched_c<-1>, smp::batched_c<-1>>()
    .test<list<>>()
    ;

  ut::not_invocable<smp::batched<_3, bad_function>>();
  ut::not_invocable<smp::batched<_3, bad_function>, _1>();
  ut::not_invocable<smp::batched<_3, bad_function>, _1, _1, _1>();
  ut::not_invocable<smp::batched<_3, bad_function>, _1, _1, _1, _1, _1, _1, _1, _1>();
  ut::not_invocable<smp::batched<smp::always<na>>>();
  ut::not_invocable<smp::batched<bad_number, bad_function>>();
  ut::not_invocable<smp::batched<bad_number, bad_function>, _1>();
  ut::not_invocable<smp::batched<bad_number, bad_function>, _1, _1, _1>();
  ut::not_invocable<smp::batched<bad_number, bad_function>, _1, _1, _1, _1, _1, _1, _1, _1>();
}

TEST_SUITE_END()

