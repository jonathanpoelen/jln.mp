// SPDX-FileCopyrightText: 2023 Jonathan Poelen <jonathan.poelen@gmail.com>
// SPDX-License-Identifier: MIT
#include "test.hpp"
#include "test/numbers.hpp"

#include "jln/mp/smp/number/math.hpp"
#include "jln/mp/smp/number/numbers.hpp"
#include "jln/mp/smp/utility/unpack.hpp"

TEST_SUITE_BEGIN()

TEST()
{
  using namespace jln::mp;
  using namespace ut::ints;

  using e = list<>;

  ut::same<_1, emp::min<_1, _2>>();
  ut::same<_2, emp::max<_1, _2>>();
  ut::same<_1, emp::abs<_1>>();
  ut::same<_1, emp::abs_c<-1>>();
  ut::same<_2, emp::clamp_c<2, 0, 3>>();
  ut::same<_3, emp::clamp_c<5, 0, 3>>();
  ut::same<_0, emp::clamp_c<-5, 0, 3>>();
  ut::same<_0, emp::pow_c<0, 1>>();
  ut::same<_0, emp::pow_c<0, 2>>();
  ut::same<_0, emp::pow_c<0, 3>>();
  ut::same<_1, emp::pow_c<1, 0>>();
  ut::same<_1, emp::pow_c<1, 1>>();
  ut::same<_1, emp::pow_c<1, 2>>();
  ut::same<_1, emp::pow_c<1, 3>>();
  ut::same<_1, emp::pow_c<2, 0>>();
  ut::same<_2, emp::pow_c<2, 1>>();
  ut::same<_4, emp::pow_c<2, 2>>();
  ut::same<_8, emp::pow_c<2, 3>>();
  ut::same<number<2*2*2*2*2*2*2*2>, emp::pow_c<2, 8>>();

  test_unary_pack<pow>();
  test_unary_pack<min>();
  test_binary_pack<abs>();
  test_unary_pack<abs, less<>>();

  test_context<min<>, smp::min<>>()
    .test<_1, _1, _2>()
    .not_invocable<>()
    .not_invocable<_1>()
    .not_invocable<_1, _2, _3>()
    .not_invocable<e>()
    ;

  test_context<max<>, smp::max<>>()
    .test<_2, _1, _2>()
    .not_invocable<>()
    .not_invocable<_1>()
    .not_invocable<_1, _2, _3>()
    .not_invocable<e>()
    ;

  test_context<clamp_c<-2, 5>, smp::clamp_c<-2, 5>>()
    .test<_1, _1>()
    .test<_4, _4>()
    .test<_5, _5>()
    .test<_5, _6>()
    .test<number<-1>, number<-1>>()
    .test<number<-2>, number<-2>>()
    .test<number<-2>, number<-3>>()
    .not_invocable<>()
    .not_invocable<_1, _2>()
    .not_invocable<bad_number>()
    ;

  test_context<abs<>, smp::abs<>, 0>()
    .test<_1, _1>()
    .test<_1, number<(-1)>>()
    .not_invocable<>()
    .not_invocable<_1, _2>()
    .not_invocable<bad_number>()
    ;

  test_context<pow<>, smp::pow<>>()
    .test<_1, _0, _0>()
    .test<_0, _0, _1>()
    .test<_1, _1, _1>()
    .test<_8, _2, _3>()
    .not_invocable<_0>()
    .not_invocable<_0, _0, _1>()
    .not_invocable<_1, _0, _0>()
    .not_invocable<bad_number, _1>()
    .not_invocable<_0, bad_number>()
    .not_invocable<_0, bad_number, bad_number>()
    ;

  ut::not_invocable<smp::pow<bad_function>>();
  ut::not_invocable<smp::pow<bad_function>, _1, _1>();
}

TEST_SUITE_END()
