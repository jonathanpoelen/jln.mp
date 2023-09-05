// SPDX-FileCopyrightText: 2023 Jonathan Poelen <jonathan.poelen@gmail.com>
// SPDX-License-Identifier: MIT
#include "test.hpp"
#include "test/numbers.hpp"

#include "jln/mp/smp/algorithm/unique.hpp"
#include "jln/mp/smp/functional/each.hpp"
#include "jln/mp/smp/utility/always.hpp"
#include "jln/mp/smp/list/at.hpp"

TEST_SUITE_BEGIN()

TEST()
{
  using namespace jln::mp;
  using namespace ut::ints;

  test_mulary_pack<unique>();
  test_mulary_pack<unique_if>();
  test_mulary_pack<unique_if, listify>();

  ut::same<seq_0_1_2, emp::unique<emp::numbers<0, 1, 0, 2, 2>>>();

  test_context<unique<>, smp::unique<>>()
    .test<list<>>()
    .test<seq_0, _0>()
    .test<seq_0, _0, _0>()
    .test<seq_0_1, _0, _1>()
    .test<seq_0_1_2, _0, _1, _2>()
    .test<seq_0, _0, _0, _0, _0, _0>()
    .test<seq_0_1_2_3, _0, _0, _1, _0, _2, _2, _2, _0, _0, _3>()
    .test<list<int, int&, int&&, int const, int const&, int const&&>,
      int, int&, int&&, int const, int const&, int const&&, int&>()
    ;

  test_context<unique_if<>, smp::unique_if<>>()
    .test<list<>>()
    .test<seq_0, _0>()
    .test<seq_0, _0, _0>()
    .test<seq_0_1, _0, _1>()
    .test<seq_0_1_2, _0, _1, _2>()
    .test<seq_0, _0, _0, _0, _0, _0>()
    .test<seq_0_1_2_3, _0, _0, _1, _0, _2, _2, _2, _0, _0, _3>()
    .test<list<int, int&, int&&, int const, int const&, int const&&>,
      int, int&, int&&, int const, int const&, int const&&, int&>()
    ;

  using first = unpack<at0<>>;
  using smp_first = smp::unpack<smp::at0<>>;
  test_context<
    unique_if<each<first, first, lift<std::is_same>>>,
    smp::unique_if<smp::each<smp_first, smp_first, smp::lift<std::is_same>>>,
    0 /* unpack<front<>> / unpack<at0<>> is optimized */
  >()
    .test<list<>>()
    .test<seq_0, _0>()
    .test<list<seq_0_0>, seq_0_0, seq_0_1>()
    .test<list<seq_0_0, seq_1_0>, seq_0_0, seq_0_1, seq_1_0>()
    .not_invocable<_0, _0>()
    ;

  ut::not_invocable<smp::unique<bad_function>, _1, _1, _1, _1>();
  ut::not_invocable<smp::unique_if<smp::always<na>>, _1, _1, _1, _1>();
  ut::not_invocable<smp::unique_if<always<void>>, _1, _1, _1, _1>();
  ut::not_invocable<smp::unique_if<bad_function>, _1, _1, _1, _1>();
  ut::not_invocable<smp::unique_if<lift<std::is_same>, bad_function>, _1, _1, _1, _1>();
}

TEST_SUITE_END()
