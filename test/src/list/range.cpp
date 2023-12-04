// SPDX-FileCopyrightText: 2023 Jonathan Poelen <jonathan.poelen@gmail.com>
// SPDX-License-Identifier: MIT
#include "test.hpp"
#include "test/numbers.hpp"

#include "jln/mp/smp/list/range.hpp"
#include "jln/mp/smp/number/operators.hpp"

TEST_SUITE_BEGIN()

TEST()
{
  using namespace jln::mp;
  using namespace ut::ints;

  test_mulary_pack<range, _1, _2>();

  test_context<range_c<0, 3>, smp::range_c<0, 3>>()
    .test<list<_0, _1, _2>, _0, _1, _2, _3, _4, _5>()
    .test<list<_0, _1, _2>, _0, _1, _2, _3, _4>()
    .test<list<_0, _1, _2>, _0, _1, _2, _3>()
    .test<list<_0, _1, _2>, _0, _1, _2>()
    .test<list<_0, _1>, _0, _1>()
    .test<list<_0>, _0>()
    .test<list<>>()
    ;

  test_context<range_c<0, -1>, smp::range_c<0, -1>>()
    .test<list<_0, _1, _2, _3, _4>, _0, _1, _2, _3, _4, _5>()
    .test<list<_0, _1, _2, _3>, _0, _1, _2, _3, _4>()
    .test<list<_0, _1, _2>, _0, _1, _2, _3>()
    .test<list<_0, _1>, _0, _1, _2>()
    .test<list<_0>, _0, _1>()
    .test<list<>, _0>()
    .test<list<>>()
    ;

  test_context<range_c<2, 4>, smp::range_c<2, 4>>()
    .test<list<_2, _3>, _0, _1, _2, _3, _4, _5>()
    .test<list<_2, _3>, _0, _1, _2, _3, _4>()
    .test<list<_2, _3>, _0, _1, _2, _3>()
    .test<list<_2>, _0, _1, _2>()
    .test<list<>, _0, _1>()
    .test<list<>, _0>()
    .test<list<>>()
    ;

  test_context<range_c<4, 0>, smp::range_c<4, 0>>()
    .test<list<>, _0, _1, _2, _3, _4, _5>()
    .test<list<>, _0, _1, _2, _3, _4>()
    .test<list<>, _0, _1, _2, _3>()
    .test<list<>, _0, _1, _2>()
    .test<list<>, _0, _1>()
    .test<list<>, _0>()
    .test<list<>>()
    ;

  test_context<range_c<4, 2>, smp::range_c<4, 2>>()
    .test<list<>, _0, _1, _2, _3, _4, _5>()
    .test<list<>, _0, _1, _2, _3, _4>()
    .test<list<>, _0, _1, _2, _3>()
    .test<list<>, _0, _1, _2>()
    .test<list<>, _0, _1>()
    .test<list<>, _0>()
    .test<list<>>()
    ;

  test_context<range_c<2, -3>, smp::range_c<2, -3>>()
    .test<list<_2>, _0, _1, _2, _3, _4, _5>()
    .test<list<>, _0, _1, _2, _3, _4>()
    .test<list<>, _0, _1, _2, _3>()
    .test<list<>, _0, _1, _2>()
    .test<list<>, _0, _1>()
    .test<list<>, _0>()
    .test<list<>>()
    ;

  test_context<range_c<1, -1>, smp::range_c<1, -1>>()
    .test<list<_1, _2, _3, _4>, _0, _1, _2, _3, _4, _5>()
    .test<list<_1, _2, _3>, _0, _1, _2, _3, _4>()
    .test<list<_1, _2>, _0, _1, _2, _3>()
    .test<list<_1>, _0, _1, _2>()
    .test<list<>, _0, _1>()
    .test<list<>, _0>()
    .test<list<>>()
    ;

  test_context<range_c<-1, -1>, smp::range_c<-1, -1>>()
    .test<list<>, _0, _1, _2, _3, _4, _5>()
    .test<list<>, _0, _1, _2, _3, _4>()
    .test<list<>, _0, _1, _2, _3>()
    .test<list<>, _0, _1, _2>()
    .test<list<>, _0, _1>()
    .test<list<>, _0>()
    .test<list<>>()
    ;

  test_context<range_c<-2, 0>, smp::range_c<-2, 0>>()
    .test<list<>, _0, _1, _2, _3, _4, _5>()
    .test<list<>, _0, _1, _2, _3, _4>()
    .test<list<>, _0, _1, _2, _3>()
    .test<list<>, _0, _1, _2>()
    .test<list<>, _0, _1>()
    .test<list<>, _0>()
    .test<list<>>()
    ;

  test_context<range_c<-1, 3>, smp::range_c<-1, 3>>()
    .test<list<>, _0, _1, _2, _3, _4, _5>()
    .test<list<>, _0, _1, _2, _3, _4>()
    .test<list<>, _0, _1, _2, _3>()
    .test<list<_2>, _0, _1, _2>()
    .test<list<_1>, _0, _1>()
    .test<list<_0>, _0>()
    .test<list<>>()
    ;

  test_context<range_c<-2, 3>, smp::range_c<-2, 3>>()
    .test<list<>, _0, _1, _2, _3, _4, _5>()
    .test<list<>, _0, _1, _2, _3, _4>()
    .test<list<_2>, _0, _1, _2, _3>()
    .test<list<_1, _2>, _0, _1, _2>()
    .test<list<_0, _1>, _0, _1>()
    .test<list<_0>, _0>()
    .test<list<>>()
    ;

  test_context<range_c<-2, -4>, smp::range_c<-2, -4>>()
    .test<list<>, _0, _1, _2, _3, _4, _5>()
    .test<list<>, _0, _1, _2, _3, _4>()
    .test<list<>, _0, _1, _2, _3>()
    .test<list<>, _0, _1, _2>()
    .test<list<>, _0, _1>()
    .test<list<>, _0>()
    .test<list<>>()
    ;

  test_context<range_c<-4, -2>, smp::range_c<-4, -2>>()
    .test<list<_2, _3>, _0, _1, _2, _3, _4, _5>()
    .test<list<_1, _2>, _0, _1, _2, _3, _4>()
    .test<list<_0, _1>, _0, _1, _2, _3>()
    .test<list<_0>, _0, _1, _2>()
    .test<list<>, _0, _1>()
    .test<list<>, _0>()
    .test<list<>>()
    ;

  ut::not_invocable<smp::range<smp::always<na>, _2>, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1>();
  ut::not_invocable<smp::range<_0, _9, bad_function>, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1>();
  ut::not_invocable<smp::range<_2, _9, bad_function>, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1>();
  ut::not_invocable<smp::range<_0, number<-1>, bad_function>, _1, _1, _1, _1, _1, _1, _1, _1>();
  ut::not_invocable<smp::range<_1, number<-1>, bad_function>, _1, _1, _1, _1, _1, _1, _1, _1>();
  ut::not_invocable<smp::range<_1, number<-2>, bad_function>, _1, _1, _1, _1, _1, _1, _1, _1>();
  ut::not_invocable<smp::range<number<-1>, number<-1>, bad_function>, _1, _1, _1, _1, _1, _1>();
  ut::not_invocable<smp::range<number<-3>, _10, bad_function>, _1, _1, _1, _1, _1, _1, _1, _1>();
  ut::not_invocable<smp::range<number<3>, number<-3>, bad_function>, _1, _1, _1, _1, _1, _1>();
  ut::not_invocable<smp::range<number<-9>, number<-7>, bad_function>, _1, _1, _1, _1, _1, _1>();
  ut::not_invocable<smp::range<number<-10>, number<-2>, bad_function>, _1, _1, _1, _1, _1, _1>();
  ut::not_invocable<smp::range<number<-11>, number<-2>, bad_function>, _1, _1, _1, _1, _1, _1>();
  ut::not_invocable<smp::range<number<-22>, _0, bad_function>, _1, _1, _1, _1, _1, _1, _1, _1>();
  ut::not_invocable<smp::range<bad_number, bad_number, bad_function>, _1, _1, _1, _1, _1, _1>();
  ut::not_invocable<smp::range<_1, bad_number>, _1, _1, _1, _1, _1, _1>();
  ut::not_invocable<smp::range<bad_number, _2>, _1, _1, _1, _1, _1, _1>();
}

TEST_SUITE_END()
