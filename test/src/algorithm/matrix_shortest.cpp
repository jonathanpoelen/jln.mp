// SPDX-FileCopyrightText: 2023 Jonathan Poelen <jonathan.poelen@gmail.com>
// SPDX-License-Identifier: MIT
#include "test.hpp"
#include "test/numbers.hpp"

#include "jln/mp/smp/algorithm/matrix_shortest.hpp"
#include "jln/mp/smp/utility/always.hpp"
#include "jln/mp/smp/list/is_list.hpp"
#include "jln/mp/smp/list/size.hpp"

TEST_SUITE_BEGIN()

TEST()
{
  using namespace jln::mp;
  using namespace ut::ints;

  ut::same<
    list<seq_0_0, seq_0_1, seq_3_2>,
    emp::left_matrix_shortest<list<seq_0_0_0, seq_0_1, seq_3_2_1>>
  >();

  test_mulary_pack<left_matrix_shortest_with>();
  test_mulary_pack<left_matrix_shortest_with, listify>();

  test_context<left_matrix_shortest<>, smp::left_matrix_shortest<>>()
    .test<list<>>()
    .test<list<list<>>, list<>>()
    .test<list<list<>, list<>>, list<>, list<>>()
    .test<list<list<>, list<>>, list<>, seq_0_0_0>()
    .test<list<seq_0>, seq_0>()
    .test<list<seq_0, seq_1>, seq_0, seq_1>()
    .test<list<seq_0_2, seq_1_3>, seq_0_2, seq_1_3>()
    .test<list<seq_0_0, seq_2_1, seq_1_1, seq_0_1>,
        seq_0_0_0, seq_2_1, seq_1_1_1, seq_0_1_0_2_0_3_0>()
    .not_invocable<int>()
    ;

  test_context<left_matrix_shortest_with<size<>>, smp::left_matrix_shortest_with<smp::size<>>>()
    .test<list<>>()
    .test<list<_0>, list<>>()
    .test<list<_0, _0>, list<>, list<>>()
    .test<list<_0, _0>, list<>, seq_0_0_0>()
    .test<list<_1>, seq_0>()
    .test<list<_1, _1>, seq_0, seq_1>()
    .test<list<_2, _2>, seq_0_2, seq_1_3>()
    .test<list<_2, _2, _2, _2>, seq_0_0_0, seq_2_1, seq_1_1_1, seq_0_1_0_2_0_3_0>()
    .not_invocable<int>()
    ;

  test_context<left_matrix_shortest<is_list<>>, smp::left_matrix_shortest<smp::is_list<>>>()
    .test<true_, list<>>()
    .not_invocable<>()
    .not_invocable<list<list<>, list<>>, list<>, list<>>()
    .not_invocable<int>()
    ;

  ut::not_invocable<smp::left_matrix_shortest<bad_function>>();
  ut::not_invocable<smp::left_matrix_shortest<bad_function>, seq_0_1, seq_0_1>();
  ut::not_invocable<smp::left_matrix_shortest<bad_function>, seq_0_1, seq_0_1_2_3>();
  ut::not_invocable<smp::left_matrix_shortest_with<smp::always<na>>, seq_0_1, seq_0_1>();
}

TEST()
{
  using namespace jln::mp;
  using namespace ut::ints;

  ut::same<
    list<seq_0_0, seq_0_1, seq_2_1>,
    emp::right_matrix_shortest<list<seq_0_0_0, seq_0_1, seq_3_2_1>>
  >();

  test_mulary_pack<right_matrix_shortest_with>();
  test_mulary_pack<right_matrix_shortest_with, listify>();

  test_context<right_matrix_shortest<>, smp::right_matrix_shortest<>>()
    .test<list<>>()
    .test<list<list<>>, list<>>()
    .test<list<list<>, list<>>, list<>, list<>>()
    .test<list<list<>, list<>>, list<>, seq_0_0_0>()
    .test<list<seq_0>, seq_0>()
    .test<list<seq_0, seq_1>, seq_0, seq_1>()
    .test<list<seq_0_2, seq_1_3>, seq_0_2, seq_1_3>()
    .test<list<seq_0_0, seq_2_1, seq_1_1, seq_3_0>,
        seq_0_0_0, seq_2_1, seq_1_1_1, seq_0_1_0_2_0_3_0>()
    .not_invocable<int>()
    ;

  test_context<right_matrix_shortest_with<size<>>, smp::right_matrix_shortest_with<smp::size<>>>()
    .test<list<>>()
    .test<list<_0>, list<>>()
    .test<list<_0, _0>, list<>, list<>>()
    .test<list<_0, _0>, list<>, seq_0_0_0>()
    .test<list<_1>, seq_0>()
    .test<list<_1, _1>, seq_0, seq_1>()
    .test<list<_2, _2>, seq_0_2, seq_1_3>()
    .test<list<_2, _2, _2, _2>, seq_0_0_0, seq_2_1, seq_1_1_1, seq_0_1_0_2_0_3_0>()
    .not_invocable<int>()
    ;

  test_context<right_matrix_shortest<is_list<>>, smp::right_matrix_shortest<smp::is_list<>>>()
    .test<true_, list<>>()
    .not_invocable<>()
    .not_invocable<list<list<>, list<>>, list<>, list<>>()
    .not_invocable<int>()
    ;

  ut::not_invocable<smp::right_matrix_shortest<bad_function>>();
  ut::not_invocable<smp::right_matrix_shortest<bad_function>, seq_0_1, seq_0_1>();
  ut::not_invocable<smp::right_matrix_shortest<bad_function>, seq_0_1, seq_0_1_2_3>();
  ut::not_invocable<smp::right_matrix_shortest_with<smp::always<na>>, seq_0_1, seq_0_1>();
}

TEST_SUITE_END()
