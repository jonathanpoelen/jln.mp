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

#if JLN_MP_FEATURE_CONCEPTS
template<class n>
  requires(std::is_void_v<n>)
struct void_k_element {};
#endif

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
#if JLN_MP_FEATURE_CONCEPTS
  ut::not_invocable<smp::map_element_key_update<listify>, void_k_element<void>>();
#endif
}

template<class>
struct one_element {};

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
  ut::not_invocable<smp::map_element_value_update<listify>, one_element<_0>>();
}

TEST_SUITE_END()

// map_key_update
TEST()
{
  using namespace jln::mp;
  using namespace ut::ints;

  test_mulary_pack<map_key_update, _0>();

  ut::same<list<seq_0, list<seq_1_0, _0>>, emp::map_key_update<list<seq_0, seq_1_0>, _1, listify>>();
  ut::same<list<seq_0, seq_1_0>, emp::map_key_update<list<seq_0, seq_1_0>, _2, listify>>();

  test_context<map_key_update<_2, listify>, smp::map_key_update<_2, smp::listify>>()
    .test<list<>>()
    .test<list<seq_0>, seq_0>()
    .test<list<seq_0, list<seq_2_0, _0>>, seq_0, seq_2_0>()
    .not_invocable<void>()
    .not_invocable<list<>>()
    .not_invocable<seq_0, seq_0>()
    ;

  ut::not_invocable<smp::map_key_update<seq_0, bad_function>, _0>();
  ut::not_invocable<smp::map_key_update<seq_0, smp::listify, bad_function>, seq_0>();
}

// map_value_update
TEST()
{
  using namespace jln::mp;
  using namespace ut::ints;

  test_mulary_pack<map_value_update, _0>();

  ut::same<list<seq_0, list<_1, seq_1_0>>, emp::map_value_update<list<seq_0, seq_1_0>, _1, listify>>();
  ut::same<list<seq_0, seq_1_0>, emp::map_value_update<list<seq_0, seq_1_0>, _2, listify>>();

  test_context<map_value_update<_2, listify>, smp::map_value_update<_2, smp::listify>>()
    .test<list<>>()
    .test<list<seq_0>, seq_0>()
    .test<list<seq_0, list<_2, seq_2_0>>, seq_0, seq_2_0>()
    .not_invocable<void>()
    .not_invocable<list<>>()
    .not_invocable<seq_0, seq_0>()
    ;

  ut::not_invocable<smp::map_value_update<seq_0, bad_function>, _0>();
  ut::not_invocable<smp::map_value_update<seq_0, smp::listify, bad_function>, seq_0>();
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

// map_value_update_or_insert
TEST()
{
  using namespace jln::mp;
  using namespace ut::ints;

  test_mulary_pack<map_value_update_or_insert, seq_0_0>();

  test_context<
    map_value_update_or_insert<seq_2_0, listify>,
    smp::map_value_update_or_insert<seq_2_0, smp::listify>
  >()
    .test<list<seq_2_0>>()
    .test<list<seq_0, seq_2_0>, seq_0>()
    .test<list<seq_0, list<_2, seq_2>>, seq_0, seq_2>()
    .test<list<seq_0, list<_2, seq_2_1>>, seq_0, seq_2_1>()
    .not_invocable<void>()
    .not_invocable<list<>>()
    .not_invocable<seq_0, seq_0>()
    ;

  ut::not_invocable<smp::map_value_update_or_insert<seq_0, bad_function>, _0>();
  ut::not_invocable<smp::map_value_update_or_insert<seq_0, smp::listify, bad_function>, seq_0>();
}
