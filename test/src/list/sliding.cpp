// SPDX-FileCopyrightText: 2023 Jonathan Poelen <jonathan.poelen@gmail.com>
// SPDX-License-Identifier: MIT
#include "test.hpp"
#include "test/numbers.hpp"

#include "jln/mp/smp/functional/lift.hpp"
#include "jln/mp/smp/number/operators.hpp"
#include "jln/mp/smp/utility/always.hpp"
#include "jln/mp/smp/list/sliding.hpp"

TEST_SUITE_BEGIN()

TEST()
{
  using namespace jln::mp;
  using namespace ut::ints;

  ut::same<list<>, emp::sliding<list<>, _3>>();
  ut::same<list<seq_0>, emp::sliding<seq_0, _3>>();
  ut::same<list<seq_0_1>, emp::sliding<seq_0_1, _3>>();
  ut::same<list<seq_0_1_2>, emp::sliding<seq_0_1_2, _3>>();
  ut::same<list<seq_0_1_2, seq_1_2_3>, emp::sliding<seq_0_1_2_3, _3>>();

  ut::same<list<>, emp::strided_sliding<list<>, _1, _2>>();
  ut::same<list<seq_0>, emp::strided_sliding<seq_0, _1, _2>>();
  ut::same<list<seq_0>, emp::strided_sliding<seq_0_1, _1, _2>>();
  ut::same<list<seq_0, seq_2>, emp::strided_sliding<seq_0_1_2, _1, _2>>();
  ut::same<list<seq_0, seq_2>, emp::strided_sliding<seq_0_1_2_3, _1, _2>>();

  ut::same<list<>, emp::strided_sliding<list<>, _2, _2>>();
  ut::same<list<seq_0>, emp::strided_sliding<seq_0, _2, _2>>();
  ut::same<list<seq_0_1>, emp::strided_sliding<seq_0_1, _2, _2>>();
  ut::same<list<seq_0_1, seq_2>, emp::strided_sliding<seq_0_1_2, _2, _2>>();
  ut::same<list<seq_0_1, seq_2_3>, emp::strided_sliding<seq_0_1_2_3, _2, _2>>();

  ut::same<list<>, emp::strided_sliding<list<>, _3, _2>>();
  ut::same<list<seq_0>, emp::strided_sliding<seq_0, _3, _2>>();
  ut::same<list<seq_0_1>, emp::strided_sliding<seq_0_1, _3, _2>>();
  ut::same<list<seq_0_1_2>, emp::strided_sliding<seq_0_1_2, _3, _2>>();
  ut::same<list<seq_0_1_2, seq_2_3>, emp::strided_sliding<seq_0_1_2_3, _3, _2>>();
  ut::same<list<seq_0_1_2, seq_2_3_4>, emp::strided_sliding<list<_0, _1, _2, _3, _4>, _3, _2>>();
  ut::same<list<seq_0_1_2, seq_2_3_4, list<_4, _5, _6>>, emp::strided_sliding<list<_0, _1, _2, _3, _4, _5, _6>, _3, _2>>();

  test_mulary_pack<strided_sliding, _2, _1>();

  ut::same<list<seq_0_1, seq_1_2>, emp::sliding<seq_0_1_2, _2>>();

  using listify2 = lift<list, listify>;
  using smp_listify2 = detail::sfinae<listify2>;

  test_context<sliding<_1>, smp::sliding<_1>>()
    .test<list<>>()
    .test<list<seq_0>, _0>()
    .test<list<seq_0, seq_1>, _0, _1>()
    .test<list<seq_0, seq_1, seq_2>, _0, _1, _2>()
    ;

  test_context<sliding_with<_1, listify2>, smp::sliding_with<_1, smp_listify2>>()
    .test<list<>>()
    .test<list<list<seq_0>>, _0>()
    .test<list<list<seq_0>, list<seq_1>>, _0, _1>()
    .test<list<list<seq_0>, list<seq_1>, list<seq_2>>, _0, _1, _2>()
    ;

  test_context<sliding<_2>, smp::sliding<_2>>()
    .test<list<>>()
    .test<list<seq_0>, _0>()
    .test<list<seq_0_1>, _0, _1>()
    .test<list<seq_0_1, seq_1_2>, _0, _1, _2>()
    .test<list<seq_0_1, seq_1_2, seq_2_3>, _0, _1, _2, _3>()
    ;

  test_context<sliding_with<_2, listify2>, smp::sliding_with<_2, smp_listify2>>()
    .test<list<>>()
    .test<list<list<seq_0>>, _0>()
    .test<list<list<seq_0_1>>, _0, _1>()
    .test<list<list<seq_0_1>, list<seq_1_2>>, _0, _1, _2>()
    .test<list<list<seq_0_1>, list<seq_1_2>, list<seq_2_3>>, _0, _1, _2, _3>()
    ;

  test_context<sliding<_3>, smp::sliding<_3>>()
    .test<list<>>()
    .test<list<seq_0>, _0>()
    .test<list<seq_0_1>, _0, _1>()
    .test<list<seq_0_1_2>, _0, _1, _2>()
    .test<list<seq_0_1_2, seq_1_2_3>, _0, _1, _2, _3>()
    .test<list<seq_0_1_2, seq_1_2_3, seq_2_3_4>, _0, _1, _2, _3, _4>()
    ;

  test_context<sliding_with<_3, listify2>, smp::sliding_with<_3, smp_listify2>>()
    .test<list<>>()
    .test<list<list<seq_0>>, _0>()
    .test<list<list<seq_0_1>>, _0, _1>()
    .test<list<list<seq_0_1_2>>, _0, _1, _2>()
    .test<list<list<seq_0_1_2>, list<seq_1_2_3>>, _0, _1, _2, _3>()
    .test<list<list<seq_0_1_2>, list<seq_1_2_3>, list<seq_2_3_4>>, _0, _1, _2, _3, _4>()
    ;

  test_context<sliding<_9>, smp::sliding<_9>>()
    .test<list<>>()
    .test<list<seq_0>, _0>()
    .test<list<seq_0_1>, _0, _1>()
    .test<list<seq_0_1_2>, _0, _1, _2>()
    .test<list<seq_0_1_2_3>, _0, _1, _2, _3>()
    .test<list<list<_0, _1, _2, _3, _4>>, _0, _1, _2, _3, _4>()
    .test<list<list<_0, _1, _2, _3, _4, _5, _6, _7>>, _0, _1, _2, _3, _4, _5, _6, _7>()
    .test<list<list<_0, _1, _2, _3, _4, _5, _6, _7, _8>>, _0, _1, _2, _3, _4, _5, _6, _7, _8>()
    .test<list<
        list<_0, _1, _2, _3, _4, _5, _6, _7, _8>,
        list<_1, _2, _3, _4, _5, _6, _7, _8, _9>
      >,
      _0, _1, _2, _3, _4, _5, _6, _7, _8, _9>()
    .test<list<
        list<_0, _1, _2, _3, _4, _5, _6, _7, _8>,
        list<_1, _2, _3, _4, _5, _6, _7, _8, _9>,
        list<_2, _3, _4, _5, _6, _7, _8, _9, _10>
      >,
      _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10>()
    ;

  test_context<sliding_with<_9, listify2>, smp::sliding_with<_9, smp_listify2>>()
    .test<list<>>()
    .test<list<list<seq_0>>, _0>()
    .test<list<list<seq_0_1>>, _0, _1>()
    .test<list<list<seq_0_1_2>>, _0, _1, _2>()
    .test<list<list<seq_0_1_2_3>>, _0, _1, _2, _3>()
    .test<list<list<list<_0, _1, _2, _3, _4>>>, _0, _1, _2, _3, _4>()
    .test<list<list<list<_0, _1, _2, _3, _4, _5, _6, _7>>>, _0, _1, _2, _3, _4, _5, _6, _7>()
    .test<list<list<list<_0, _1, _2, _3, _4, _5, _6, _7, _8>>>, _0, _1, _2, _3, _4, _5, _6, _7, _8>()
    .test<list<
        list<list<_0, _1, _2, _3, _4, _5, _6, _7, _8>>,
        list<list<_1, _2, _3, _4, _5, _6, _7, _8, _9>>
      >,
      _0, _1, _2, _3, _4, _5, _6, _7, _8, _9>()
    .test<list<
        list<list<_0, _1, _2, _3, _4, _5, _6, _7, _8>>,
        list<list<_1, _2, _3, _4, _5, _6, _7, _8, _9>>,
        list<list<_2, _3, _4, _5, _6, _7, _8, _9, _10>>
      >,
      _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10>()
    ;

  test_context<sliding<_10>, smp::sliding<_10>>()
    .test<list<>>()
    .test<list<seq_0>, _0>()
    .test<list<seq_0_1>, _0, _1>()
    .test<list<seq_0_1_2>, _0, _1, _2>()
    .test<list<seq_0_1_2_3>, _0, _1, _2, _3>()
    .test<list<list<_0, _1, _2, _3, _4>>, _0, _1, _2, _3, _4>()
    .test<list<list<_0, _1, _2, _3, _4, _5, _6, _7, _8>>, _0, _1, _2, _3, _4, _5, _6, _7, _8>()
    .test<list<list<_0, _1, _2, _3, _4, _5, _6, _7, _8, _9>>, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9>()
    .test<list<
        list<_0, _1, _2, _3, _4, _5, _6, _7, _8, _9>,
        list<_1, _2, _3, _4, _5, _6, _7, _8, _9, _10>
      >,
      _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10>()
    .test<list<
        list<_0, _1, _2, _3, _4, _5, _6, _7, _8, _9>,
        list<_1, _2, _3, _4, _5, _6, _7, _8, _9, _10>,
        list<_2, _3, _4, _5, _6, _7, _8, _9, _10, _11>
      >,
      _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11>()
    ;

  test_context<sliding_with<_10, listify2>, smp::sliding_with<_10, smp_listify2>>()
    .test<list<>>()
    .test<list<list<seq_0>>, _0>()
    .test<list<list<seq_0_1>>, _0, _1>()
    .test<list<list<seq_0_1_2>>, _0, _1, _2>()
    .test<list<list<seq_0_1_2_3>>, _0, _1, _2, _3>()
    .test<list<list<list<_0, _1, _2, _3, _4>>>, _0, _1, _2, _3, _4>()
    .test<list<list<list<_0, _1, _2, _3, _4, _5, _6, _7, _8>>>, _0, _1, _2, _3, _4, _5, _6, _7, _8>()
    .test<list<list<list<_0, _1, _2, _3, _4, _5, _6, _7, _8, _9>>>, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9>()
    .test<list<
        list<list<_0, _1, _2, _3, _4, _5, _6, _7, _8, _9>>,
        list<list<_1, _2, _3, _4, _5, _6, _7, _8, _9, _10>>
      >,
      _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10>()
    .test<list<
        list<list<_0, _1, _2, _3, _4, _5, _6, _7, _8, _9>>,
        list<list<_1, _2, _3, _4, _5, _6, _7, _8, _9, _10>>,
        list<list<_2, _3, _4, _5, _6, _7, _8, _9, _10, _11>>
      >,
      _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11>()
    ;

  test_context<strided_sliding<_1, _2>, smp::strided_sliding<_1, _2>>()
    .test<list<>>()
    .test<list<seq_0>, _0>()
    .test<list<seq_0>, _0, _1>()
    .test<list<seq_0, seq_2>, _0, _1, _2>()
    .test<list<seq_0, seq_2>, _0, _1, _2, _3>()
    ;

  test_context<strided_sliding_with<_1, _2, listify2>, smp::strided_sliding_with<_1, _2, smp_listify2>>()
    .test<list<>>()
    .test<list<list<seq_0>>, _0>()
    .test<list<list<seq_0>>, _0, _1>()
    .test<list<list<seq_0>, list<seq_2>>, _0, _1, _2>()
    .test<list<list<seq_0>, list<seq_2>>, _0, _1, _2, _3>()
    ;

  test_context<strided_sliding<_2, _2>, smp::strided_sliding<_2, _2>>()
    .test<list<>>()
    .test<list<seq_0>, _0>()
    .test<list<seq_0_1>, _0, _1>()
    .test<list<seq_0_1, seq_2>, _0, _1, _2>()
    .test<list<seq_0_1, seq_2_3>, _0, _1, _2, _3>()
    ;

  test_context<strided_sliding_with<_2, _2, listify2>, smp::strided_sliding_with<_2, _2, smp_listify2>>()
    .test<list<>>()
    .test<list<list<seq_0>>, _0>()
    .test<list<list<seq_0_1>>, _0, _1>()
    .test<list<list<seq_0_1>, list<seq_2>>, _0, _1, _2>()
    .test<list<list<seq_0_1>, list<seq_2_3>>, _0, _1, _2, _3>()
    ;

  test_context<strided_sliding<_3, _2>, smp::strided_sliding<_3, _2>>()
    .test<list<>>()
    .test<list<seq_0>, _0>()
    .test<list<seq_0_1>, _0, _1>()
    .test<list<seq_0_1_2>, _0, _1, _2>()
    .test<list<seq_0_1_2, seq_2_3>, _0, _1, _2, _3>()
    .test<list<seq_0_1_2, seq_2_3_4>, _0, _1, _2, _3, _4>()
    .test<list<seq_0_1_2, seq_2_3_4, list<_4, _5>>, _0, _1, _2, _3, _4, _5>()
    .test<list<seq_0_1_2, seq_2_3_4, list<_4, _5, _6>>, _0, _1, _2, _3, _4, _5, _6>()
    ;

  test_context<strided_sliding_with<_3, _2, listify2>, smp::strided_sliding_with<_3, _2, smp_listify2>>()
    .test<list<>>()
    .test<list<list<seq_0>>, _0>()
    .test<list<list<seq_0_1>>, _0, _1>()
    .test<list<list<seq_0_1_2>>, _0, _1, _2>()
    .test<list<list<seq_0_1_2>, list<seq_2_3>>, _0, _1, _2, _3>()
    .test<list<list<seq_0_1_2>, list<seq_2_3_4>>, _0, _1, _2, _3, _4>()
    .test<list<list<seq_0_1_2>, list<seq_2_3_4>, list<list<_4, _5>>>, _0, _1, _2, _3, _4, _5>()
    .test<list<list<seq_0_1_2>, list<seq_2_3_4>, list<list<_4, _5, _6>>>, _0, _1, _2, _3, _4, _5, _6>()
    ;

  test_context<strided_sliding<_5, _2>, smp::strided_sliding<_5, _2>>()
    .test<list<>>()
    .test<list<seq_0_1_2_3>, _0, _1, _2, _3>()
    .test<list<list<_0, _1, _2, _3, _4>, list<_2, _3, _4, _5>>, _0, _1, _2, _3, _4, _5>()
    .test<list<list<_0, _1, _2, _3, _4>, list<_2, _3, _4, _5, _6>>,
      _0, _1, _2, _3, _4, _5, _6>()
    .test<list<list<_0, _1, _2, _3, _4>, list<_2, _3, _4, _5, _6>, list<_4, _5, _6, _7>>,
      _0, _1, _2, _3, _4, _5, _6, _7>()
    ;

  test_context<strided_sliding_with<_5, _2, listify2>, smp::strided_sliding_with<_5, _2, smp_listify2>>()
    .test<list<>>()
    .test<list<list<seq_0_1_2_3>>, _0, _1, _2, _3>()
    .test<list<list<list<_0, _1, _2, _3, _4>>, list<list<_2, _3, _4, _5>>>, _0, _1, _2, _3, _4, _5>()
    .test<list<list<list<_0, _1, _2, _3, _4>>, list<list<_2, _3, _4, _5, _6>>>,
      _0, _1, _2, _3, _4, _5, _6>()
    .test<list<list<list<_0, _1, _2, _3, _4>>, list<list<_2, _3, _4, _5, _6>>, list<list<_4, _5, _6, _7>>>,
      _0, _1, _2, _3, _4, _5, _6, _7>()
    ;

  test_context<strided_sliding<_2, _5>, smp::strided_sliding<_2, _5>>()
    .test<list<>>()
    .test<list<seq_0_1>, _0, _1, _2, _3>()
    .test<list<seq_0_1>, _0, _1, _2, _3, _4>()
    .test<list<seq_0_1, list<_5>>, _0, _1, _2, _3, _4, _5>()
    .test<list<seq_0_1, list<_5, _6>>, _0, _1, _2, _3, _4, _5, _6>()
    .test<list<seq_0_1, list<_5, _6>>, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9>()
    .test<list<seq_0_1, list<_5, _6>, list<_10>>, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10>()
    ;

  test_context<strided_sliding_with<_2, _5, listify2>, smp::strided_sliding_with<_2, _5, smp_listify2>>()
    .test<list<>>()
    .test<list<list<seq_0_1>>, _0, _1, _2, _3>()
    .test<list<list<seq_0_1>>, _0, _1, _2, _3, _4>()
    .test<list<list<seq_0_1>, list<list<_5>>>, _0, _1, _2, _3, _4, _5>()
    .test<list<list<seq_0_1>, list<list<_5, _6>>>, _0, _1, _2, _3, _4, _5, _6>()
    .test<list<list<seq_0_1>, list<list<_5, _6>>>, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9>()
    .test<list<list<seq_0_1>, list<list<_5, _6>>, list<list<_10>>>, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10>()
    ;

  test_context<strided_sliding_with<_6, _3, listify2>, smp::strided_sliding_with<_6, _3, smp_listify2>>()
    .test<list<>>()
    .test<list<list<seq_0_1_2_3>>, _0, _1, _2, _3>()
    .test<list<list<list<_0, _1, _2, _3, _4, _5>>>, _0, _1, _2, _3, _4, _5>()
    .test<list<list<list<_0, _1, _2, _3, _4, _5>>, list<list<_3, _4, _5, _6>>>, _0, _1, _2, _3, _4, _5, _6>()
    .test<list<list<list<_0, _1, _2, _3, _4, _5>>, list<list<_3, _4, _5, _6, _7, _8>>>,
      _0, _1, _2, _3, _4, _5, _6, _7, _8>()
    .test<list<list<list<_0, _1, _2, _3, _4, _5>>, list<list<_3, _4, _5, _6, _7, _8>>, list<list<_6, _7, _8, _9>>>,
      _0, _1, _2, _3, _4, _5, _6, _7, _8, _9>()
    ;

  test_context<strided_sliding_c<0, -1>, smp::strided_sliding_c<0, -1>>()
    .test<list<>>()
    .test<list<>, _0>()
    ;

  test_context<strided_sliding_with_c<0, -1, listify2>, smp::strided_sliding_with_c<0, -1, smp_listify2>>()
    .test<list<>>()
    .test<list<>, _0>()
    ;

  test_context<strided_sliding_c<1, -1>, smp::strided_sliding_c<1, -1>>()
    .test<list<>>()
    .test<list<>, _0>()
    ;

  test_context<strided_sliding_with_c<1, -1, listify2>, smp::strided_sliding_with_c<1, -1, smp_listify2>>()
    .test<list<>>()
    .test<list<>, _0>()
    ;

  test_context<strided_sliding_c<-1, -1>, smp::strided_sliding_c<-1, -1>>()
    .test<list<>>()
    .test<list<>, _0>()
    ;

  test_context<strided_sliding_with_c<-1, -1, listify2>, smp::strided_sliding_with_c<-1, -1, smp_listify2>>()
    .test<list<>>()
    .test<list<>, _0>()
    ;

  test_context<strided_sliding_c<-1, 1>, smp::strided_sliding_c<-1, 1>>()
    .test<list<>>()
    .test<list<>, _0>()
    ;

  test_context<strided_sliding_with_c<-1, 1, listify2>, smp::strided_sliding_with_c<-1, 1, smp_listify2>>()
    .test<list<>>()
    .test<list<>, _0>()
    ;

  test_context<strided_sliding_c<-1, 2>, smp::strided_sliding_c<-1, 2>>()
    .test<list<>>()
    .test<list<>, _0>()
    ;

  test_context<strided_sliding_with_c<-1, 2, listify2>, smp::strided_sliding_with_c<-1, 2, smp_listify2>>()
    .test<list<>>()
    .test<list<>, _0>()
    ;


  ut::not_invocable<smp::strided_sliding_with_c<2, 1, bad_function>, _1, _2, _3>();
  ut::not_invocable<smp::strided_sliding_with_c<2, 1, smp::listify, bad_function>, _1, _2, _3>();

  ut::not_invocable<smp::strided_sliding_c<1, 1, and_<>>, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10>();
  ut::not_invocable<smp::strided_sliding_c<1, 2, and_<>>, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10>();
  ut::not_invocable<smp::strided_sliding_c<3, 1, and_<>>, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10>();
  ut::not_invocable<smp::strided_sliding_c<3, 2, and_<>>, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10>();
  ut::not_invocable<smp::strided_sliding_c<3, 3, and_<>>, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10>();
  ut::not_invocable<smp::strided_sliding_c<3, 4, and_<>>, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10,
    _11, _12, _13, _14, _15>();

  ut::not_invocable<smp::strided_sliding<_3, _1, bad_function>, _1, _1, _1, _1, _1, _1>();
  ut::not_invocable<smp::strided_sliding<_1, _2, bad_function>, _1, _1, _1, _1, _1, _1>();
  ut::not_invocable<smp::strided_sliding<_2, _2, bad_function>, _1, _1, _1, _1, _1, _1>();
  ut::not_invocable<smp::strided_sliding<_3, _2, bad_function>, _1, _1, _1, _1, _1, _1>();
  ut::not_invocable<smp::strided_sliding<_5, _2, bad_function>, _1, _1, _1, _1, _1, _1>();
  ut::not_invocable<smp::strided_sliding<_2, _5, bad_function>, _1, _1, _1, _1, _1, _1>();
  ut::not_invocable<smp::strided_sliding<smp::always<na>, _1>, _1, _1, _1, _1, _1, _1>();
  ut::not_invocable<smp::strided_sliding<_0, bad_number>, _1, _1, _1, _1>();
  ut::not_invocable<smp::strided_sliding<bad_number, _1>, _1, _1, _1, _1>();
  ut::not_invocable<smp::strided_sliding<_0, number<-1>, bad_function>, _1, _1, _1, _1>();
  ut::not_invocable<smp::strided_sliding<_1, number<-1>, bad_function>, _1, _1, _1, _1>();
  ut::not_invocable<smp::strided_sliding<bad_number, bad_number, bad_function>, _1, _1>();
  ut::not_invocable<smp::strided_sliding<smp::always<na>, smp::always<na>>, _1, _1>();
}

TEST_SUITE_END()
