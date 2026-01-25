// SPDX-FileCopyrightText: 2025 Jonathan Poelen <jonathan.poelen@gmail.com>
// SPDX-License-Identifier: MIT
#include "test.hpp"
#include "test/numbers.hpp"

#include "jln/mp/smp/algorithm/unique_by.hpp"
#include "jln/mp/smp/number/operators.hpp"

TEST_SUITE_BEGIN()

TEST()
{
  using namespace jln::mp;
  using namespace ut::ints;

  test_mulary_pack<unique_by, add0<>>();
  test_mulary_pack<unique_by_kv>();

  ut::same<
    list<seq_0_1, seq_1_1, seq_2_1>,
    emp::unique_by<
      list<seq_0_1, seq_1_0, seq_1_1, seq_2_0, seq_2_1, seq_3_0>,
      unpack<add0<>>
    >
  >();

  ut::same<
    list<_1, _0, _0, _5>,
    emp::unique_by_kv<
      list<
        unique_by_kv_entry<_0, _1>,
        unique_by_kv_entry<_1, _0>,
        unique_by_kv_entry<_1, _1>,
        unique_by_kv_entry<_2, _0>,
        unique_by_kv_entry<_2, _1>,
        unique_by_kv_entry<_3, _5>
      >
    >
  >();

  test_context<unique_by<unpack<add0<>>>, smp::unique_by<smp::unpack<smp::add0<>>>>()
    .not_invocable<list<int>>()
    .not_invocable<_0>()
// bug 5818596
#if !JLN_MP_WORKAROUND(JLN_MP_CUDA, <= 1301)
    .test<list<>>()
    .test<list<seq_0_0>, seq_0_0>()
    .test<list<seq_0_0>, seq_0_0, seq_0_0>()
    .test<list<seq_0_0, seq_0_1>, seq_0_0, seq_0_1>()
    .test<list<seq_0_0, seq_0_1, seq_2_2>, seq_0_0, seq_0_1, seq_2_2>()
    .test<
        list<
          seq_0_0, seq_0_1, seq_0_2, seq_0_3,
          seq_1_3,
          seq_2_3,
          seq_3_3
        >,
        seq_0_0, seq_0_1, seq_0_2, seq_0_3,
        seq_1_0, seq_1_1, seq_1_2, seq_1_3,
        seq_2_0, seq_2_1, seq_2_2, seq_2_3,
        seq_3_0, seq_3_1, seq_3_2, seq_3_3
      >()
#endif
    ;

  test_context<unique_by_kv<>, smp::unique_by_kv<>>()
    .not_invocable<list<>>()
    .not_invocable<seq_0>()
    .not_invocable<_0>()
    .test<list<>>()
    .test<list<_1, _3>,
      unique_by_kv_entry<_0, _1>,
      unique_by_kv_entry<_0, _2>,
      unique_by_kv_entry<_1, _3>,
      unique_by_kv_entry<_1, _4>
    >()
  ;

  ut::not_invocable<smp::unique_by<bad_function>, _1, _1, _1, _1>();
// bug 5818596
#if !JLN_MP_WORKAROUND(JLN_MP_CUDA, <= 1301)
  ut::not_invocable<smp::unique_by<smp::always<na>>, _1, _1, _1, _1>();
#endif
  ut::not_invocable<smp::unique_by<always<void>, bad_function>, _1, _1, _1, _1>();
}

TEST_SUITE_END()
