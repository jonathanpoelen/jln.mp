// SPDX-FileCopyrightText: 2023 Jonathan Poelen <jonathan.poelen@gmail.com>
// SPDX-License-Identifier: MIT
#include "test.hpp"
#include "test/numbers.hpp"

#include "jln/mp/smp/utility/always.hpp"
#include "jln/mp/smp/list/slice.hpp"

TEST_SUITE_BEGIN()

TEST()
{
  using namespace jln::mp;
  using namespace ut::ints;

  test_mulary_pack<strided_slice, _1, _2, _1>();

  ut::same<emp::numbers<3, 4, 5, 6>, emp::strided_slice_c<
    seq_0_1_2_3_4_5_6_7_8_9, 3, 4>>();
  ut::same<emp::numbers<0, 2, 4>, emp::strided_slice_c<
    seq_0_1_2_3_4_5_6_7_8_9, 0, 3, 2>>();

  // invalid step
  test_context<strided_slice_c<2, 3, 0>, smp::strided_slice_c<2, 3, 0>>()
    .not_invocable<_0, _1, _2, _3, _4, _5, _6>()
    .not_invocable<_0, _1, _2, _3, _4, _5>()
    .not_invocable<_0, _1, _2, _3, _4>()
    .not_invocable<_0, _1, _2, _3>()
    .not_invocable<_0, _1, _2>()
    .not_invocable<_0, _1>()
    .not_invocable<_0>()
    .not_invocable<>()
    ;


  // start >= 0 ; count = 0 ; step = 1
  //@{

  test_context<strided_slice_c<0, 0>, smp::strided_slice_c<0, 0>>()
    .test<list<>, _0, _1, _2, _3>()
    .test<list<>, _0, _1, _2>()
    .test<list<>, _0, _1>()
    .test<list<>, _0>()
    .test<list<>>()
    ;

  test_context<strided_slice_c<1, 0>, smp::strided_slice_c<1, 0>>()
    .test<list<>, _0, _1, _2, _3>()
    .test<list<>, _0, _1, _2>()
    .test<list<>, _0, _1>()
    .test<list<>, _0>()
    .test<list<>>()
    ;

  test_context<strided_slice_c<2, 0>, smp::strided_slice_c<2, 0>>()
    .test<list<>, _0, _1, _2, _3>()
    .test<list<>, _0, _1, _2>()
    .test<list<>, _0, _1>()
    .test<list<>, _0>()
    .test<list<>>()
    ;

  test_context<strided_slice_c<3, 0>, smp::strided_slice_c<3, 0>>()
    .test<list<>, _0, _1, _2, _3>()
    .test<list<>, _0, _1, _2>()
    .test<list<>, _0, _1>()
    .test<list<>, _0>()
    .test<list<>>()
    ;

  //@}

  // start >= 0 ; count = 3 ; step = 1
  //@{

  test_context<strided_slice_c<0, 3>, smp::strided_slice_c<0, 3>>()
    .test<list<_0, _1, _2>, _0, _1, _2, _3, _4, _5>()
    .test<list<_0, _1, _2>, _0, _1, _2, _3, _4>()
    .test<list<_0, _1, _2>, _0, _1, _2, _3>()
    .test<list<_0, _1, _2>, _0, _1, _2>()
    .test<list<_0, _1>, _0, _1>()
    .test<list<_0>, _0>()
    .test<list<>>()
    ;

  test_context<strided_slice_c<1, 3>, smp::strided_slice_c<1, 3>>()
    .test<list<_1, _2, _3>, _0, _1, _2, _3, _4, _5>()
    .test<list<_1, _2, _3>, _0, _1, _2, _3, _4>()
    .test<list<_1, _2, _3>, _0, _1, _2, _3>()
    .test<list<_1, _2>, _0, _1, _2>()
    .test<list<_1>, _0, _1>()
    .test<list<>, _0>()
    .test<list<>>()
    ;

  test_context<strided_slice_c<2, 3>, smp::strided_slice_c<2, 3>>()
    .test<list<_2, _3, _4>, _0, _1, _2, _3, _4, _5>()
    .test<list<_2, _3, _4>, _0, _1, _2, _3, _4>()
    .test<list<_2, _3>, _0, _1, _2, _3>()
    .test<list<_2>, _0, _1, _2>()
    .test<list<>, _0, _1>()
    .test<list<>, _0>()
    .test<list<>>()
    ;

  test_context<strided_slice_c<3, 3>, smp::strided_slice_c<3, 3>>()
    .test<list<_3, _4, _5>, _0, _1, _2, _3, _4, _5>()
    .test<list<_3, _4>, _0, _1, _2, _3, _4>()
    .test<list<_3>, _0, _1, _2, _3>()
    .test<list<>, _0, _1, _2>()
    .test<list<>, _0, _1>()
    .test<list<>, _0>()
    .test<list<>>()
    ;

  test_context<strided_slice_c<4, 3>, smp::strided_slice_c<4, 3>>()
    .test<list<_4, _5>, _0, _1, _2, _3, _4, _5>()
    .test<list<_4>, _0, _1, _2, _3, _4>()
    .test<list<>, _0, _1, _2, _3>()
    .test<list<>, _0, _1, _2>()
    .test<list<>, _0, _1>()
    .test<list<>, _0>()
    .test<list<>>()
    ;

  //@}

  // start < 0 ; count = 0 ; step = 1
  //@{

  test_context<strided_slice_c<-1, 0>, smp::strided_slice_c<-1, 0>>()
    .test<list<>, _0, _1, _2, _3>()
    .test<list<>, _0, _1, _2>()
    .test<list<>, _0, _1>()
    .test<list<>, _0>()
    .test<list<>>()
    ;

  test_context<strided_slice_c<-2, 0>, smp::strided_slice_c<-2, 0>>()
    .test<list<>, _0, _1, _2, _3>()
    .test<list<>, _0, _1, _2>()
    .test<list<>, _0, _1>()
    .test<list<>, _0>()
    .test<list<>>()
    ;

  test_context<strided_slice_c<-3, 0>, smp::strided_slice_c<-3, 0>>()
    .test<list<>, _0, _1, _2, _3>()
    .test<list<>, _0, _1, _2>()
    .test<list<>, _0, _1>()
    .test<list<>, _0>()
    .test<list<>>()
    ;

  test_context<strided_slice_c<-4, 0>, smp::strided_slice_c<-4, 0>>()
    .test<list<>, _0, _1, _2, _3>()
    .test<list<>, _0, _1, _2>()
    .test<list<>, _0, _1>()
    .test<list<>, _0>()
    .test<list<>>()
    ;

  //@}

  // start < 0 ; count = 3 ; step = 1
  //@{

  test_context<strided_slice_c<-1, 3>, smp::strided_slice_c<-1, 3>>()
    .test<list<_5>, _0, _1, _2, _3, _4, _5>()
    .test<list<_4>, _0, _1, _2, _3, _4>()
    .test<list<_3>, _0, _1, _2, _3>()
    .test<list<_2>, _0, _1, _2>()
    .test<list<_1>, _0, _1>()
    .test<list<_0>, _0>()
    .test<list<>>()
    ;

  test_context<strided_slice_c<-2, 3>, smp::strided_slice_c<-2, 3>>()
    .test<list<_4, _5>, _0, _1, _2, _3, _4, _5>()
    .test<list<_3, _4>, _0, _1, _2, _3, _4>()
    .test<list<_2, _3>, _0, _1, _2, _3>()
    .test<list<_1, _2>, _0, _1, _2>()
    .test<list<_0, _1>, _0, _1>()
    .test<list<_0>, _0>()
    .test<list<>>()
    ;

  test_context<strided_slice_c<-3, 3>, smp::strided_slice_c<-3, 3>>()
    .test<list<_3, _4, _5>, _0, _1, _2, _3, _4, _5>()
    .test<list<_2, _3, _4>, _0, _1, _2, _3, _4>()
    .test<list<_1, _2, _3>, _0, _1, _2, _3>()
    .test<list<_0, _1, _2>, _0, _1, _2>()
    .test<list<_0, _1>, _0, _1>()
    .test<list<_0>, _0>()
    .test<list<>>()
    ;

  test_context<strided_slice_c<-4, 3>, smp::strided_slice_c<-4, 3>>()
    .test<list<_2, _3, _4>, _0, _1, _2, _3, _4, _5>()
    .test<list<_1, _2, _3>, _0, _1, _2, _3, _4>()
    .test<list<_0, _1, _2>, _0, _1, _2, _3>()
    .test<list<_0, _1>, _0, _1, _2>()
    .test<list<_0>, _0, _1>()
    .test<list<>, _0>()
    .test<list<>>()
    ;

  //@}

  // start >= 0 ; count = 0 ; step = 2
  //@{

  test_context<strided_slice_c<0, 0, 2>, smp::strided_slice_c<0, 0, 2>>()
    .test<list<>, _0, _1, _2, _3>()
    .test<list<>, _0, _1, _2>()
    .test<list<>, _0, _1>()
    .test<list<>, _0>()
    .test<list<>>()
    ;

  test_context<strided_slice_c<1, 0, 2>, smp::strided_slice_c<1, 0, 2>>()
    .test<list<>, _0, _1, _2, _3>()
    .test<list<>, _0, _1, _2>()
    .test<list<>, _0, _1>()
    .test<list<>, _0>()
    .test<list<>>()
    ;

  test_context<strided_slice_c<2, 0, 2>, smp::strided_slice_c<2, 0, 2>>()
    .test<list<>, _0, _1, _2, _3, _4>()
    .test<list<>, _0, _1, _2, _3>()
    .test<list<>, _0, _1, _2>()
    .test<list<>, _0, _1>()
    .test<list<>, _0>()
    .test<list<>>()
    ;

  test_context<strided_slice_c<3, 0, 2>, smp::strided_slice_c<3, 0, 2>>()
    .test<list<>, _0, _1, _2, _3>()
    .test<list<>, _0, _1, _2>()
    .test<list<>, _0, _1>()
    .test<list<>, _0>()
    .test<list<>>()
    ;

  //@}

  // start >= 0 ; count = 3 ; step = 2
  //@{

  test_context<strided_slice_c<0, 3, 2>, smp::strided_slice_c<0, 3, 2>>()
    .test<list<_0, _2, _4>, _0, _1, _2, _3, _4, _5>()
    .test<list<_0, _2, _4>, _0, _1, _2, _3, _4>()
    .test<list<_0, _2>, _0, _1, _2, _3>()
    .test<list<_0, _2>, _0, _1, _2>()
    .test<list<_0>, _0, _1>()
    .test<list<_0>, _0>()
    .test<list<>>()
    ;

  test_context<strided_slice_c<1, 3, 2>, smp::strided_slice_c<1, 3, 2>>()
    .test<list<_1, _3, _5>, _0, _1, _2, _3, _4, _5>()
    .test<list<_1, _3>, _0, _1, _2, _3, _4>()
    .test<list<_1, _3>, _0, _1, _2, _3>()
    .test<list<_1>, _0, _1, _2>()
    .test<list<_1>, _0, _1>()
    .test<list<>, _0>()
    .test<list<>>()
    ;

  test_context<strided_slice_c<2, 3, 2>, smp::strided_slice_c<2, 3, 2>>()
    .test<list<_2, _4, _6>, _0, _1, _2, _3, _4, _5, _6>()
    .test<list<_2, _4>, _0, _1, _2, _3, _4, _5>()
    .test<list<_2, _4>, _0, _1, _2, _3, _4>()
    .test<list<_2>, _0, _1, _2, _3>()
    .test<list<_2>, _0, _1, _2>()
    .test<list<>, _0, _1>()
    .test<list<>, _0>()
    .test<list<>>()
    ;

  test_context<strided_slice_c<3, 3, 2>, smp::strided_slice_c<3, 3, 2>>()
    .test<list<_3, _5>, _0, _1, _2, _3, _4, _5>()
    .test<list<_3>, _0, _1, _2, _3, _4>()
    .test<list<_3>, _0, _1, _2, _3>()
    .test<list<>, _0, _1, _2>()
    .test<list<>, _0, _1>()
    .test<list<>, _0>()
    .test<list<>>()
    ;

  test_context<strided_slice_c<4, 3, 2>, smp::strided_slice_c<4, 3, 2>>()
    .test<list<_4>, _0, _1, _2, _3, _4, _5>()
    .test<list<_4>, _0, _1, _2, _3, _4>()
    .test<list<>, _0, _1, _2, _3>()
    .test<list<>, _0, _1, _2>()
    .test<list<>, _0, _1>()
    .test<list<>, _0>()
    .test<list<>>()
    ;

  //@}

  // start < 0 ; count = 0 ; step = 2
  //@{

  test_context<strided_slice_c<-1, 0, 2>, smp::strided_slice_c<-1, 0, 2>>()
    .test<list<>, _0, _1, _2, _3>()
    .test<list<>, _0, _1, _2>()
    .test<list<>, _0, _1>()
    .test<list<>, _0>()
    .test<list<>>()
    ;

  test_context<strided_slice_c<-2, 0, 2>, smp::strided_slice_c<-2, 0, 2>>()
    .test<list<>, _0, _1, _2, _3>()
    .test<list<>, _0, _1, _2>()
    .test<list<>, _0, _1>()
    .test<list<>, _0>()
    .test<list<>>()
    ;

  test_context<strided_slice_c<-3, 0, 2>, smp::strided_slice_c<-3, 0, 2>>()
    .test<list<>, _0, _1, _2, _3>()
    .test<list<>, _0, _1, _2>()
    .test<list<>, _0, _1>()
    .test<list<>, _0>()
    .test<list<>>()
    ;

  //@}

  // start < 0 ; count = 3 ; step = 2
  //@{

  test_context<strided_slice_c<-1, 3, 2>, smp::strided_slice_c<-1, 3, 2>>()
    .test<list<_5>, _0, _1, _2, _3, _4, _5>()
    .test<list<_4>, _0, _1, _2, _3, _4>()
    .test<list<_3>, _0, _1, _2, _3>()
    .test<list<_2>, _0, _1, _2>()
    .test<list<_1>, _0, _1>()
    .test<list<_0>, _0>()
    .test<list<>>()
    ;

  test_context<strided_slice_c<-2, 3, 2>, smp::strided_slice_c<-2, 3, 2>>()
    .test<list<_4>, _0, _1, _2, _3, _4, _5>()
    .test<list<_3>, _0, _1, _2, _3, _4>()
    .test<list<_2>, _0, _1, _2, _3>()
    .test<list<_1>, _0, _1, _2>()
    .test<list<_0>, _0, _1>()
    .test<list<>, _0>()
    .test<list<>>()
    ;

  test_context<strided_slice_c<-3, 3, 2>, smp::strided_slice_c<-3, 3, 2>>()
    .test<list<_3, _5>, _0, _1, _2, _3, _4, _5>()
    .test<list<_2, _4>, _0, _1, _2, _3, _4>()
    .test<list<_1, _3>, _0, _1, _2, _3>()
    .test<list<_0, _2>, _0, _1, _2>()
    .test<list<_1>, _0, _1>()
    .test<list<_0>, _0>()
    .test<list<>>()
    ;

  test_context<strided_slice_c<-4, 3, 2>, smp::strided_slice_c<-4, 3, 2>>()
    .test<list<_2, _4>, _0, _1, _2, _3, _4, _5>()
    .test<list<_1, _3>, _0, _1, _2, _3, _4>()
    .test<list<_0, _2>, _0, _1, _2, _3>()
    .test<list<_1>, _0, _1, _2>()
    .test<list<_0>, _0, _1>()
    .test<list<>, _0>()
    .test<list<>>()
    ;

  //@}


  test_context<strided_slice_c<2, 10, 2>, smp::strided_slice_c<2, 10, 2>>()
    .test<list<_2, _4, _6, _8, _10, _12, _14, _16, _18, _20>,
      _0, _1, _2, _3, _4, _5, _6, _7, _8, _9,_10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21>()
    .test<list<_2, _4, _6, _8, _10, _12, _14, _16, _18, _20>,
      _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20>()
    .test<list<_2, _4, _6, _8, _10, _12, _14, _16, _18>,
      _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19>()
    ;

  test_context<strided_slice_c<0, 2, 5>, smp::strided_slice_c<0, 2, 5>>()
    .test<list<_0, _5>, _0, _1, _2, _3, _4, _5>()
    .test<list<_0, _5>, _0, _1, _2, _3, _4, _5, _6>()
    .test<list<_0>, _0, _1, _2, _3, _4>()
    ;

  ut::same<list<>, smp::strided_slice_c<2, 0, 0>::f<_0, _1, _2, _3, _4, _5>>();
  ut::not_invocable<smp::strided_slice_c<2, 3, 0>, _0, _1, _2, _3, _4, _5>();

  ut::not_invocable<smp::strided_slice<_2, _3, _2, bad_function>,
    _1, _1, _1, _1, _1, _1, _1, _1, _1>();
  ut::not_invocable<smp::strided_slice<smp::always<na>, _3, _2>,
    _1, _1, _1, _1, _1, _1, _1>();
  ut::not_invocable<smp::strided_slice<bad_number, _3, _2, bad_function>,
    _1, _1, _1, _1, _1, _1, _1>();
  ut::not_invocable<smp::strided_slice<_2, bad_number, _2, bad_function>,
    _1, _1, _1, _1, _1, _1, _1>();
  ut::not_invocable<smp::strided_slice<_2, _3, bad_number, bad_function>,
    _1, _1, _1, _1, _1, _1, _1>();
  ut::not_invocable<smp::strided_slice<bad_number, _3, _2>, _1, _1, _1, _1, _1, _1, _1>();
  ut::not_invocable<smp::strided_slice<_2, bad_number, _2>, _1, _1, _1, _1, _1, _1, _1>();
  ut::not_invocable<smp::strided_slice<_2, _3, bad_number>, _1, _1, _1, _1, _1, _1, _1>();
}

TEST_SUITE_END()

