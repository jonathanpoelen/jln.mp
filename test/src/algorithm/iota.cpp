// SPDX-FileCopyrightText: 2023 Jonathan Poelen <jonathan.poelen@gmail.com>
// SPDX-License-Identifier: MIT
#include "test.hpp"
#include "test/numbers.hpp"

#include "jln/mp/smp/algorithm/iota.hpp"

TEST_SUITE_BEGIN()

struct one_arg
{
  template<jln::mp::int_t i>
  using f = jln::mp::number<i>;
};

TEST()
{
  using namespace jln::mp;
  using namespace ut::ints;

  ut::same<_0, emp::iota_v_c<0, 1, 1, one_arg>>();
  ut::same<_1, emp::iota_v_c<1, 1, 1, one_arg>>();

  ut::same<seq_0_1_2, emp::iota_c<0, 3>>();
  ut::same<seq_1_3_5, emp::iota_c<1, 3, 2>>();

  ut::same<seq_0_1_2, emp::iota_v_c<0, 3>>();
  ut::same<seq_1_3_5, emp::iota_v_c<1, 3, 2>>();

  ut::same<list<number<-1>, number< 0>, number< 1>>, emp::iota_v_c<-1, 3>>();
  ut::same<list<number<-1>, number<-2>, number<-3>>, emp::iota_v_c<-1, 3, -1>>();
  ut::same<list<number<-1>, number< 1>, number< 3>>, emp::iota_v_c<-1, 3,  2>>();
  ut::same<list<number<-1>, number<-3>, number<-5>>, emp::iota_v_c<-1, 3, -2>>();

  ut::same<list<number<-3>, number<-2>, number<-1>>, emp::iota_v_c<-1, -3>>();
  ut::same<list<number< 1>, number< 0>, number<-1>>, emp::iota_v_c<-1, -3, -1>>();
  ut::same<list<number<-5>, number<-3>, number<-1>>, emp::iota_v_c<-1, -3,  2>>();
  ut::same<list<number< 3>, number< 1>, number<-1>>, emp::iota_v_c<-1, -3, -2>>();

  test_mulary_pack<iota>();

  test_context<iota<>, smp::iota<>>()
    .test<list<>, _0, _0>()
    .test<list<>, _3, _0>()
    .test<seq_0_1_2, _0, _3>()
    .test<seq_0_0_0, _0, _3, _0>()
    .test<seq_1_1_1, _1, _3, _0>()
    .test<seq_1_2_3, _1, _3>()
    .test<seq_0_2_4, _0, _3, _2>()
    .test<seq_1_3_5, _1, _3, _2>()
    .not_invocable<_1>()
    .not_invocable<_1, _1, _1, _1>()
    ;

  ut::not_invocable<smp::iota<bad_function>>();
  ut::not_invocable<smp::iota<bad_function>, _1, _4>();
}

TEST_SUITE_END()
