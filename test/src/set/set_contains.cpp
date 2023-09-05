// SPDX-FileCopyrightText: 2023 Jonathan Poelen <jonathan.poelen@gmail.com>
// SPDX-License-Identifier: MIT
#include "test.hpp"
#include "test/numbers.hpp"

#include "jln/mp/smp/set/set_contains.hpp"
#include "jln/mp/smp/utility/always.hpp"

TEST_SUITE_BEGIN()

// set_contains
TEST()
{
  using namespace jln::mp;
  using namespace ut::ints;

  test_unary_pack<set_contains, void>();

  ut::same<_1, emp::set_contains<seq_0_1, _0>>();
  ut::same<_0, emp::set_contains<seq_0_1, _2>>();

  test_context<set_contains<_2>, smp::set_contains<_2>>()
    .test<_0>()
    .test<_0, _0>()
    .test<_0, _0, _1>()
    .test<_1, _0, _1, _2>()
    .test<_1, _0, _1, _2, _3>()
    .not_invocable<_1, _1>()
    ;

  ut::not_invocable<smp::set_contains<void, smp::always<na>>>();
  ut::not_invocable<smp::set_contains<void, bad_function>>();
}

// set_all_contains
TEST()
{
  using namespace jln::mp;
  using namespace ut::ints;

  test_unary_pack<set_all_contains, void>();

  ut::same<_1, emp::set_all_contains<_0, seq_0_1>>();
  ut::same<_0, emp::set_all_contains<_2, seq_0_1>>();

  test_context<set_all_contains<_2>, smp::set_all_contains<_2>>()
    .test<_1>()
    .test<_0, seq_1>()
    .test<_1, seq_1_2_3>()
    .test<_1, seq_1_2, seq_2_3>()
    .test<_0, seq_1_2, seq_1, seq_2_3>()
    .not_invocable<_1>()
    ;

  ut::not_invocable<smp::set_all_contains<void, smp::always<na>>>();
  ut::not_invocable<smp::set_all_contains<void, bad_function>>();
}

// set_any_contains
TEST()
{
  using namespace jln::mp;
  using namespace ut::ints;

  test_unary_pack<set_any_contains, void>();

  ut::same<_1, emp::set_any_contains<_0, seq_0_1>>();
  ut::same<_0, emp::set_any_contains<_2, seq_0_1>>();

  test_context<set_any_contains<_2>, smp::set_any_contains<_2>>()
    .test<_0>()
    .test<_0, seq_1>()
    .test<_1, seq_1_2_3>()
    .test<_1, seq_1_2, seq_2_3>()
    .test<_1, seq_1_2, seq_1, seq_2_3>()
    .test<_0, seq_1_3, seq_1, seq_3>()
    .not_invocable<_1>()
    ;

  ut::not_invocable<smp::set_any_contains<void, smp::always<na>>>();
  ut::not_invocable<smp::set_any_contains<void, bad_function>>();
}

// set_none_contains
TEST()
{
  using namespace jln::mp;
  using namespace ut::ints;

  test_unary_pack<set_none_contains, void>();

  ut::same<_0, emp::set_none_contains<_0, seq_0_1>>();
  ut::same<_1, emp::set_none_contains<_2, seq_0_1>>();

  test_context<set_none_contains<_2>, smp::set_none_contains<_2>>()
    .test<_1>()
    .test<_1, seq_1>()
    .test<_0, seq_1_2_3>()
    .test<_0, seq_1_2, seq_2_3>()
    .test<_0, seq_1_2, seq_1, seq_2_3>()
    .test<_1, seq_1_3, seq_1, seq_0_3>()
    .not_invocable<_1>()
    ;

  ut::not_invocable<smp::set_none_contains<void, smp::always<na>>>();
  ut::not_invocable<smp::set_none_contains<void, bad_function>>();
}

TEST_SUITE_END()
