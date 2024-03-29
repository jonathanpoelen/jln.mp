// SPDX-FileCopyrightText: 2023 Jonathan Poelen <jonathan.poelen@gmail.com>
// SPDX-License-Identifier: MIT
#include "test.hpp"
#include "test/numbers.hpp"

#include "jln/mp/smp/map/map_update.hpp"

TEST_SUITE_BEGIN()

// map_update
TEST()
{
  using namespace jln::mp;
  using namespace ut::ints;

  test_mulary_pack<map_update, _0>();

  ut::same<list<seq_0, list<seq_1_0>>, emp::map_update<list<seq_0, seq_1_0>, _1, listify>>();
  ut::same<list<seq_0, seq_1_0>, emp::map_update<list<seq_0, seq_1_0>, _2, listify>>();

  test_context<map_update<_2, listify>, smp::map_update<_2, smp::listify>>()
    .test<list<>>()
    .test<list<seq_0>, seq_0>()
    .test<list<seq_0, list<seq_2_0>>, seq_0, seq_2_0>()
    .not_invocable<void>()
    .not_invocable<list<>>()
    .not_invocable<seq_0, seq_0>()
    ;

  ut::not_invocable<smp::map_update<seq_0, bad_function>, _0>();
  ut::not_invocable<smp::map_update<seq_0, smp::listify, bad_function>, seq_0>();
}

// map_element_key_update
TEST()
{
  using namespace jln::mp;
  using namespace ut::ints;

  ut::same<list<seq_0>, emp::map_element_key_update<seq_0, listify>>();

  test_context<map_element_key_update<listify>, smp::map_element_key_update<smp::listify>>()
    .test<list<seq_0>, seq_0>()
    .test<list<seq_0_1, _1>, seq_0_1>()
    .test<list<seq_0_1_2, _1, _2>, seq_0_1_2>()
    .not_invocable<>()
    .not_invocable<void>()
    .not_invocable<list<>>()
    .not_invocable<seq_0, seq_0>()
    ;

  ut::not_invocable<smp::map_element_key_update<bad_function>, seq_0>();
}

// map_element_value_update
TEST()
{
  using namespace jln::mp;
  using namespace ut::ints;

  ut::same<list<_0, seq_0>, emp::map_element_value_update<seq_0, listify>>();

  test_context<map_element_value_update<listify>, smp::map_element_value_update<smp::listify>>()
    .test<list<_0, seq_0>, seq_0>()
    .test<list<_0, seq_0_1>, seq_0_1>()
    .test<list<_0, seq_0_1_2>, seq_0_1_2>()
    .not_invocable<>()
    .not_invocable<void>()
    .not_invocable<list<>>()
    .not_invocable<seq_0, seq_0>()
    ;

  ut::not_invocable<smp::map_element_value_update<bad_function>, seq_0>();
}

TEST_SUITE_END()

// map_update_key
TEST()
{
  using namespace jln::mp;
  using namespace ut::ints;

  test_mulary_pack<map_update_key, _0>();

  ut::same<list<seq_0, list<seq_1_0, _0>>, emp::map_update_key<list<seq_0, seq_1_0>, _1, listify>>();
  ut::same<list<seq_0, seq_1_0>, emp::map_update_key<list<seq_0, seq_1_0>, _2, listify>>();

  test_context<map_update_key<_2, listify>, smp::map_update_key<_2, smp::listify>>()
    .test<list<>>()
    .test<list<seq_0>, seq_0>()
    .test<list<seq_0, list<seq_2_0, _0>>, seq_0, seq_2_0>()
    .not_invocable<void>()
    .not_invocable<list<>>()
    .not_invocable<seq_0, seq_0>()
    ;

  ut::not_invocable<smp::map_update_key<seq_0, bad_function>, _0>();
  ut::not_invocable<smp::map_update_key<seq_0, smp::listify, bad_function>, seq_0>();
}

// map_update_value
TEST()
{
  using namespace jln::mp;
  using namespace ut::ints;

  test_mulary_pack<map_update_value, _0>();

  ut::same<list<seq_0, list<_1, seq_1_0>>, emp::map_update_value<list<seq_0, seq_1_0>, _1, listify>>();
  ut::same<list<seq_0, seq_1_0>, emp::map_update_value<list<seq_0, seq_1_0>, _2, listify>>();

  test_context<map_update_value<_2, listify>, smp::map_update_value<_2, smp::listify>>()
    .test<list<>>()
    .test<list<seq_0>, seq_0>()
    .test<list<seq_0, list<_2, seq_2_0>>, seq_0, seq_2_0>()
    .not_invocable<void>()
    .not_invocable<list<>>()
    .not_invocable<seq_0, seq_0>()
    ;

  ut::not_invocable<smp::map_update_value<seq_0, bad_function>, _0>();
  ut::not_invocable<smp::map_update_value<seq_0, smp::listify, bad_function>, seq_0>();
}

// map_update_or_insert
TEST()
{
  using namespace jln::mp;
  using namespace ut::ints;

  test_mulary_pack<map_update_or_insert, seq_0_0>();

  ut::same<list<seq_0, list<seq_1_0>>, emp::map_update_or_insert<list<seq_0, seq_1_0>, seq_1, listify>>();
  ut::same<list<seq_0, seq_1_0, seq_2>, emp::map_update_or_insert<list<seq_0, seq_1_0>, seq_2, listify>>();

  test_context<
    map_update_or_insert<seq_2_0, listify>,
    smp::map_update_or_insert<seq_2_0, smp::listify>
  >()
    .test<list<seq_2_0>>()
    .test<list<seq_0, seq_2_0>, seq_0>()
    .test<list<seq_0, list<seq_2>>, seq_0, seq_2>()
    .not_invocable<void>()
    .not_invocable<list<>>()
    .not_invocable<seq_0, seq_0>()
    ;

  ut::not_invocable<smp::map_update_or_insert<seq_0, bad_function>, _0>();
  ut::not_invocable<smp::map_update_or_insert<seq_0, smp::listify, bad_function>, seq_0>();
}

// map_update_value_or_insert
TEST()
{
  using namespace jln::mp;
  using namespace ut::ints;

  test_mulary_pack<map_update_value_or_insert, seq_0_0>();

  test_context<
    map_update_value_or_insert<seq_2_0, listify>,
    smp::map_update_value_or_insert<seq_2_0, smp::listify>
  >()
    .test<list<seq_2_0>>()
    .test<list<seq_0, seq_2_0>, seq_0>()
    .test<list<seq_0, list<_2, seq_2>>, seq_0, seq_2>()
    .test<list<seq_0, list<_2, seq_2_1>>, seq_0, seq_2_1>()
    .not_invocable<void>()
    .not_invocable<list<>>()
    .not_invocable<seq_0, seq_0>()
    ;

  ut::not_invocable<smp::map_update_value_or_insert<seq_0, bad_function>, _0>();
  ut::not_invocable<smp::map_update_value_or_insert<seq_0, smp::listify, bad_function>, seq_0>();
}
