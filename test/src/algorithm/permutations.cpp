// SPDX-FileCopyrightText: 2023 Jonathan Poelen <jonathan.poelen@gmail.com>
// SPDX-License-Identifier: MIT
#include "test.hpp"
#include "test/numbers.hpp"

#include "jln/mp/smp/algorithm/permutations.hpp"
#include "jln/mp/smp/utility/always.hpp"
#include "jln/mp/smp/list/size.hpp"

TEST_SUITE_BEGIN()

TEST()
{
  using namespace jln::mp;
  using namespace ut::ints;

  test_mulary_pack<permutations>();

  ut::same<list<
    list<_0, _1, _2>, list<_0, _2, _1>,
    list<_1, _0, _2>, list<_1, _2, _0>,
    list<_2, _0, _1>, list<_2, _1, _0>
  >, emp::permutations<seq_0_1_2>>();

  test_context<permutations<size<>>, smp::permutations<smp::size<>>>()
    .test<_0>()
    .test<_1, void>()
    .test<_2, void, void>()
    .test<_6, void, void, void>()
    .test<_24, void, void, void, void>()
    .not_invocable<void, void, void, void, void, void, void, void>()
    ;

  ut::not_invocable<smp::permutations<smp::always<na>>>();
  ut::not_invocable<smp::permutations<bad_function>>();
  ut::not_invocable<smp::permutations<bad_function>, _1, _1, _1, _1>();
}

TEST_SUITE_END()
