// SPDX-FileCopyrightText: 2023 Jonathan Poelen <jonathan.poelen@gmail.com>
// SPDX-License-Identifier: MIT
#include "test.hpp"
#include "test/numbers.hpp"

#include "jln/mp/smp/algorithm/partition.hpp"
#include "jln/mp/smp/number/operators.hpp"
#include "jln/mp/smp/functional/bind_back.hpp"

TEST_SUITE_BEGIN()

TEST()
{
  using namespace jln::mp;
  using namespace ut::ints;

  test_binary_pack<partition>();
  test_mulary_pack<partition, listify>();

  using mod2 = push_back<_2, mod<>>;

  ut::same<list<
    emp::numbers<1, 3, 5, 7, 9>,
    emp::numbers<0, 2, 4, 6, 8>
  >, emp::partition<seq_0_1_2_3_4_5_6_7_8_9, mod2>>();

  test_context<partition<mod2>, smp::partition<detail::sfinae<mod2>>>()
    .test<list<list<>, list<>>>()
    .test<list<seq_1_1, seq_0>, _1, _0, _1>()
    .test<list<list<>, seq_0_0_0>, _0, _0, _0>()
    .test<list<seq_1_1_1, list<>>, _1, _1, _1>()
    .not_invocable<bad_number>()
    ;

  test_context<
    partition<bind_back<less<>, _1>>,
    smp::partition<smp::bind_back<smp::less<>, _1>>
  >()
    .test<list<list<>, list<>>>()
    .test<list<seq_0_0_0, list<>>, _0, _0, _0>()
    .test<list<list<>, seq_1_1_1>, _1, _1, _1>()
    .test<list<seq_0, seq_1_1>, _1, _0, _1>()
    .test<list<seq_0, seq_1_2>, _1, _0, _2>()
    .not_invocable<bad_number>()
    ;

  ut::not_invocable<smp::partition<smp::always<na>>, _1, _1, _1>();
  ut::not_invocable<smp::partition<mod2, bad_function>>();
  ut::not_invocable<smp::partition<mod2, bad_function>, _1, _1, _1, _1>();
  ut::not_invocable<smp::partition<always<void>>, _1>();
  ut::not_invocable<smp::partition<bad_function, bad_function>>();
  ut::not_invocable<smp::partition<bad_function, bad_function>, _1, _1, _1, _1>();
}

TEST_SUITE_END()
