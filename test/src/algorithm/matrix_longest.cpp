// SPDX-FileCopyrightText: 2023 Jonathan Poelen <jonathan.poelen@gmail.com>
// SPDX-License-Identifier: MIT
#include "test.hpp"
#include "test/numbers.hpp"

#include "jln/mp/smp/algorithm/matrix_longest.hpp"
#include "jln/mp/smp/utility/always.hpp"
#include "jln/mp/smp/list/is_list.hpp"
#include "jln/mp/smp/list/size.hpp"

TEST_SUITE_BEGIN()

TEST()
{
  using namespace jln::mp;
  using namespace ut::ints;

  ut::same<
    list<seq_0_0_0, list<void, _0, _1>, seq_3_2_1>,
    emp::left_matrix_longest<list<seq_0_0_0, seq_0_1, seq_3_2_1>, void>
  >();

  test_mulary_pack<left_matrix_longest_with>();
  test_mulary_pack<left_matrix_longest_with, listify>();

  test_context<left_matrix_longest<void>, smp::left_matrix_longest<void>>()
    .test<list<>>()
    .test<list<list<>>, list<>>()
    .test<list<list<>, list<>>, list<>, list<>>()
    .test<list<list<void, void, void>, seq_0_0_0>, list<>, seq_0_0_0>()
    .test<list<seq_0>, seq_0>()
    .test<list<seq_0, seq_1>, seq_0, seq_1>()
    .test<list<seq_0_2, seq_1_3>, seq_0_2, seq_1_3>()
    .test<list<list<void, void, void, void, _0, _0, _0>,
               list<void, void, void, void, void, _2, _1>,
               list<void, void, void, void, _1, _1, _1>,
               seq_0_1_0_2_0_3_0>,
        seq_0_0_0, seq_2_1, seq_1_1_1, seq_0_1_0_2_0_3_0>()
    .not_invocable<int>()
    ;

  test_context<left_matrix_longest_with<void, size<>>, smp::left_matrix_longest_with<void, smp::size<>>>()
    .test<list<>>()
    .test<list<_0>, list<>>()
    .test<list<_0, _0>, list<>, list<>>()
    .test<list<_3, _3>, list<>, seq_0_0_0>()
    .test<list<_1>, seq_0>()
    .test<list<_1, _1>, seq_0, seq_1>()
    .test<list<_2, _2>, seq_0_2, seq_1_3>()
    .test<list<_7, _7, _7, _7>, seq_0_0_0, seq_2_1, seq_1_1_1, seq_0_1_0_2_0_3_0>()
    .not_invocable<int>()
    ;

  test_context<left_matrix_longest<void, is_list<>>, smp::left_matrix_longest<void, smp::is_list<>>>()
    .test<true_, list<>>()
    .not_invocable<>()
    .not_invocable<list<list<>, list<>>, list<>, list<>>()
    .not_invocable<int>()
    ;

  ut::not_invocable<smp::left_matrix_longest<void, bad_function>>();
  ut::not_invocable<smp::left_matrix_longest<void, bad_function>>();
  ut::not_invocable<smp::left_matrix_longest<void, bad_function>, seq_0_1, seq_0_1>();
  ut::not_invocable<smp::left_matrix_longest<void, bad_function>, seq_0_1, seq_0_1_2_3>();
  ut::not_invocable<smp::left_matrix_longest_with<void, smp::always<na>>, seq_0_1, seq_0_1>();
}

TEST()
{
  using namespace jln::mp;
  using namespace ut::ints;

  ut::same<
    list<seq_0_0_0, list<_0, _1, void>, seq_3_2_1>,
    emp::right_matrix_longest<list<seq_0_0_0, seq_0_1, seq_3_2_1>, void>
  >();

  test_mulary_pack<right_matrix_longest_with>();
  test_mulary_pack<right_matrix_longest_with, listify>();

  test_context<right_matrix_longest<void>, smp::right_matrix_longest<void>>()
    .test<list<>>()
    .test<list<list<>>, list<>>()
    .test<list<list<>, list<>>, list<>, list<>>()
    .test<list<list<void, void, void>, seq_0_0_0>, list<>, seq_0_0_0>()
    .test<list<seq_0>, seq_0>()
    .test<list<seq_0, seq_1>, seq_0, seq_1>()
    .test<list<seq_0_2, seq_1_3>, seq_0_2, seq_1_3>()
    .test<list<list<_0, _0, _0, void, void, void, void>,
               list<_2, _1, void, void, void, void, void>,
               list<_1, _1, _1, void, void, void, void>,
               seq_0_1_0_2_0_3_0>,
        seq_0_0_0, seq_2_1, seq_1_1_1, seq_0_1_0_2_0_3_0>()
    .not_invocable<int>()
    ;

  test_context<right_matrix_longest_with<void, size<>>, smp::right_matrix_longest_with<void, smp::size<>>>()
    .test<list<>>()
    .test<list<_0>, list<>>()
    .test<list<_0, _0>, list<>, list<>>()
    .test<list<_3, _3>, list<>, seq_0_0_0>()
    .test<list<_1>, seq_0>()
    .test<list<_1, _1>, seq_0, seq_1>()
    .test<list<_2, _2>, seq_0_2, seq_1_3>()
    .test<list<_7, _7, _7, _7>, seq_0_0_0, seq_2_1, seq_1_1_1, seq_0_1_0_2_0_3_0>()
    .not_invocable<int>()
    ;

  test_context<right_matrix_longest<void, is_list<>>, smp::right_matrix_longest<void, smp::is_list<>>>()
    .test<true_, list<>>()
    .not_invocable<>()
    .not_invocable<list<list<>, list<>>, list<>, list<>>()
    .not_invocable<int>()
    ;

  ut::not_invocable<smp::right_matrix_longest<void, bad_function>>();
  ut::not_invocable<smp::right_matrix_longest<void, bad_function>>();
  ut::not_invocable<smp::right_matrix_longest<void, bad_function>, seq_0_1, seq_0_1>();
  ut::not_invocable<smp::right_matrix_longest<void, bad_function>, seq_0_1, seq_0_1_2_3>();
  ut::not_invocable<smp::right_matrix_longest_with<void, smp::always<na>>, seq_0_1, seq_0_1>();
}

TEST_SUITE_END()
