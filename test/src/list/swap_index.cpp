// SPDX-FileCopyrightText: 2023 Jonathan Poelen <jonathan.poelen@gmail.com>
// SPDX-License-Identifier: MIT
#include "test.hpp"
#include "test/numbers.hpp"

#include "jln/mp/smp/utility/always.hpp"
#include "jln/mp/smp/list/swap_index.hpp"

TEST_SUITE_BEGIN()

TEST()
{
  using namespace jln::mp;
  using namespace ut::ints;

  ut::same<list<_3, _1, _2, _0>, emp::swap_index_c<seq_0_1_2_3, 0, 3>>();

  test_mulary_pack<swap_index, _1, _2>();

  ut::same<swap_index_c<1, 2>, swap_index_c<2, 1>>();
  ut::same<smp::swap_index_c<1, 2>, smp::swap_index_c<2, 1>>();

  test_context<swap_index_c<1, 2>, smp::swap_index_c<1, 2>>()
    .test<list<_0, _2, _1>, _0, _1, _2>()
    .test<list<_0, _2, _1, _3>, _0, _1, _2, _3>()
    .not_invocable<>()
    .not_invocable<_1>()
    .not_invocable<_1, _2>()
    ;

  test_context<swap_index_c<1, 1>, smp::swap_index_c<1, 1>>()
    .test<list<_0, _1>, _0, _1>()
    .test<list<_0, _1, _2>, _0, _1, _2>()
    .not_invocable<>()
    .not_invocable<_1>()
    ;

  ut::not_invocable<smp::swap_index<_1, _2, bad_function>, _1, _1, _1, _1>();
  ut::not_invocable<smp::swap_index<smp::always<na>, smp::always<na>>, _1, _1, _1, _1>();
  ut::not_invocable<smp::swap_index<bad_number, bad_number, bad_function>, _1, _1, _1, _1>();
  ut::not_invocable<smp::swap_index<bad_function, bad_function, bad_function>, _1, _1, _1, _1>();
}

TEST_SUITE_END()
