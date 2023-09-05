// SPDX-FileCopyrightText: 2023 Jonathan Poelen <jonathan.poelen@gmail.com>
// SPDX-License-Identifier: MIT
#include "test.hpp"
#include "test/numbers.hpp"

#include "jln/mp/smp/utility/always.hpp"
#include "jln/mp/smp/list/erase.hpp"

TEST_SUITE_BEGIN()

TEST()
{
  using namespace jln::mp;
  using namespace ut::ints;

  test_mulary_pack<erase, _0, _1>();

  ut::same<emp::numbers<0, 2>, emp::erase_c<seq_0_1_2, 1>>();

  test_context<erase_c<0, 0>, smp::erase_c<0, 0>>()
    .test<list<_0, _1, _2, _3, _4, _5, _6>, _0, _1, _2, _3, _4, _5, _6>()
    .test<list<_0>, _0>()
    .test<list<>>()
    ;

  test_context<erase_c<0, 1>, smp::erase_c<0, 1>>()
    .test<list<_1, _2, _3, _4, _5, _6>, _0, _1, _2, _3, _4, _5, _6>()
    .test<list<_1, _2, _3>, _0, _1, _2, _3>()
    .test<list<_1>, _0, _1>()
    .test<list<>, _0>()
    .test<list<>>()
    ;

  test_context<erase_c<2, 1>, smp::erase_c<2, 1>>()
    .test<list<_0, _1, _3, _4, _5>, _0, _1, _2, _3, _4, _5>()
    .test<list<_0, _1, _3, _4>, _0, _1, _2, _3, _4>()
    .test<list<_0, _1, _3>, _0, _1, _2, _3>()
    .test<list<_0, _1>, _0, _1, _2>()
    .test<list<_0, _1>, _0, _1>()
    .test<list<_0>, _0>()
    .test<list<>>()
    ;

  test_context<erase_c<2, 3>, smp::erase_c<2, 3>>()
    .test<list<_0, _1, _5, _6>, _0, _1, _2, _3, _4, _5, _6>()
    .test<list<_0, _1, _5>, _0, _1, _2, _3, _4, _5>()
    .test<list<_0, _1>, _0, _1, _2, _3, _4>()
    .test<list<_0, _1>, _0, _1, _2, _3>()
    .test<list<_0, _1>, _0, _1, _2>()
    .test<list<_0, _1>, _0, _1>()
    .test<list<_0>, _0>()
    .test<list<>>()
    ;

  test_context<erase_c<-1, 1>, smp::erase_c<-1, 1>>()
    .test<list<_0, _1, _2, _3>, _0, _1, _2, _3, _4>()
    .test<list<_0, _1, _2>, _0, _1, _2, _3>()
    .test<list<_0, _1>, _0, _1, _2>()
    .test<list<_0>, _0, _1>()
    .test<list<>, _0>()
    .test<list<>>()
    ;

  test_context<erase_c<-2, 1>, smp::erase_c<-2, 1>>()
    .test<list<_0, _1, _2, _4>, _0, _1, _2, _3, _4>()
    .test<list<_0, _1, _3>, _0, _1, _2, _3>()
    .test<list<_0, _2>, _0, _1, _2>()
    .test<list<_1>, _0, _1>()
    .test<list<_0>, _0>()
    .test<list<>>()
    ;

  test_context<erase_c<-3, 2>, smp::erase_c<-3, 2>>()
    .test<list<_0, _1, _2, _3, _6>, _0, _1, _2, _3, _4, _5, _6>()
    .test<list<_0, _1, _2, _5>, _0, _1, _2, _3, _4, _5>()
    .test<list<_0, _1, _4>, _0, _1, _2, _3, _4>()
    .test<list<_0, _3>, _0, _1, _2, _3>()
    .test<list<_2>, _0, _1, _2>()
    .test<list<_1>, _0, _1>()
    .test<list<_0>, _0>()
    .test<list<>>()
    ;

  test_context<erase_c<-2, 2>, smp::erase_c<-2, 2>>()
    .test<list<_0, _1, _2, _3, _4>, _0, _1, _2, _3, _4, _5, _6>()
    .test<list<_0, _1, _2, _3>, _0, _1, _2, _3, _4, _5>()
    .test<list<_0, _1, _2>, _0, _1, _2, _3, _4>()
    .test<list<_0, _1>, _0, _1, _2, _3>()
    .test<list<_0>, _0, _1, _2>()
    .test<list<>, _0, _1>()
    .test<list<>, _0>()
    .test<list<>>()
    ;

  test_context<erase_c<-2, 3>, smp::erase_c<-2, 3>>()
    .test<list<_0, _1, _2, _3, _4>, _0, _1, _2, _3, _4, _5, _6>()
    .test<list<_0, _1, _2, _3>, _0, _1, _2, _3, _4, _5>()
    .test<list<_0, _1, _2>, _0, _1, _2, _3, _4>()
    .test<list<_0, _1>, _0, _1, _2, _3>()
    .test<list<_0>, _0, _1, _2>()
    .test<list<>, _0, _1>()
    .test<list<>, _0>()
    .test<list<>>()
    ;

  ut::not_invocable<smp::erase<_1, smp::always<na>>, _1, _1, _1, _1, _1>();
  ut::not_invocable<smp::erase<_1, _3, bad_function>, _1, _1, _1, _1, _1>();
  ut::not_invocable<smp::erase<bad_number, bad_number, bad_function>, _1, _1, _1, _1, _1>();
}

TEST_SUITE_END()
