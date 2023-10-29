// SPDX-FileCopyrightText: 2023 Jonathan Poelen <jonathan.poelen@gmail.com>
// SPDX-License-Identifier: MIT
#include "test.hpp"
#include "test/numbers.hpp"

#include "jln/mp/smp/algorithm/copy_unique.hpp"
#include "jln/mp/smp/functional/each.hpp"
#include "jln/mp/smp/functional/lift.hpp"
#include "jln/mp/smp/utility/always.hpp"
#include "jln/mp/smp/utility/unpack.hpp"
#include "jln/mp/smp/list/at.hpp"

TEST_SUITE_BEGIN()

TEST()
{
  using namespace jln::mp;
  using namespace ut::ints;

  test_binary_pack<copy_unique_if>();
  test_mulary_pack<copy_unique_if, listify>();

  ut::same<emp::numbers<1, 3>, emp::copy_unique<emp::numbers<0, 1, 0, 2, 2, 3>>>();

  test_context<copy_unique<>, smp::copy_unique<>>()
    .test<list<>>()
    .test<list<_0>, _0>()
    .test<list<>, _0, _0>()
    .test<list<_0, _1>, _0, _1>()
    .test<list<_0, _1, _2>, _0, _1, _2>()
    .test<list<>, _0, _0, _0, _0, _0>()
    .test<list<_1, _3>,
      _0, _0, _1, _0, _2, _2, _2, _0, _0, _3>()
#if !JLN_MP_CUDA
    .test<list<int, int&&, int const, int const&, int const&&>,
      int, int&, int&&, int const, int const&, int const&&, int&>()
#endif
    ;

  test_context<copy_unique_if<>, smp::copy_unique_if<>>()
    .test<list<>>()
    .test<list<_0>, _0>()
    .test<list<>, _0, _0>()
    .test<list<_0, _1>, _0, _1>()
    .test<list<_0, _1, _2>, _0, _1, _2>()
    .test<list<>, _0, _0, _0, _0, _0>()
    .test<list<_1, _3>,
      _0, _0, _1, _0, _2, _2, _2, _0, _0, _3>()
#if !JLN_MP_CUDA
    .test<list<int, int&&, int const, int const&, int const&&>,
      int, int&, int&&, int const, int const&, int const&&, int&>()
#endif
    ;

  using first = unpack<at0<>>;
  using smp_first = smp::unpack<smp::at0<>>;
  test_context<
    copy_unique_if<each<first, first, lift<std::is_same>>>,
    smp::copy_unique_if<smp::each<smp_first, smp_first, smp::lift<std::is_same>>>,
    0 /* unpack<front<>> / unpack<at0<>> is optimized */
  >()
    .test<list<>>()
    .test<list<_0>, _0>()
    .test<list<>, seq_0_0, seq_0_1>()
    .test<list<seq_1_0>, seq_0_0, seq_0_1, seq_1_0>()
    .test<list<seq_1_0>,
      seq_0_0, seq_0_1, seq_1_0, seq_2_0, seq_0_2, seq_2_0>()
    .not_invocable<_0, _0>()
    ;

  ut::not_invocable<smp::copy_unique<bad_function>, _1, _1, _1, _1>();
  ut::not_invocable<smp::copy_unique_if<smp::always<na>>, _1, _1, _1, _1>();
  ut::not_invocable<smp::copy_unique_if<always<void>>, _1, _1, _1, _1>();
  ut::not_invocable<smp::copy_unique_if<bad_function>, _1, _1, _1, _1>();
  ut::not_invocable<smp::copy_unique_if<lift<std::is_same>, bad_function>, _1, _1, _1, _1>();
}

TEST_SUITE_END()
