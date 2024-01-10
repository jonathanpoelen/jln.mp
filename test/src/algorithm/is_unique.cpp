// SPDX-FileCopyrightText: 2023 Jonathan Poelen <jonathan.poelen@gmail.com>
// SPDX-License-Identifier: MIT
#include "test.hpp"
#include "test/numbers.hpp"

#include "jln/mp/smp/algorithm/is_unique.hpp"
#include "jln/mp/smp/functional/each.hpp"
#include "jln/mp/smp/functional/lift.hpp"
#include "jln/mp/smp/utility/unpack.hpp"
#include "jln/mp/smp/list/at.hpp"
#include "jln/mp/smp/number/operators.hpp"

TEST_SUITE_BEGIN()

TEST()
{
  using namespace jln::mp;
  using namespace ut::ints;

  test_binary_pack<is_unique_if>();
  test_unary_pack<is_unique_if, listify>();

  ut::same<_1, emp::is_unique<emp::numbers<0, 1, 2>>>();
  ut::same<_0, emp::is_unique<emp::numbers<0, 1, 0, 2, 2>>>();

  ut::same<_1, emp::is_unique_if<emp::numbers<0, 1, 2>, equal<>>>();
  ut::same<_0, emp::is_unique_if<emp::numbers<0, 1, 0, 2, 2>, equal<>>>();

  // optimized comparator
  ut::same<smp::is_unique_if<>, ut::sfinae<is_unique<>>>();


  test_context<is_unique<>, smp::is_unique<>>()
    .test<_1>()
    .test<_1, _0>()
    .test<_0, _0, _0>()
    .test<_1, _0, _1>()
    .test<_1, _0, _1, _2>()
    .test<_0, _0, _0, _0, _0, _0>()
    .test<_0, _0, _0, _1, _0, _2, _2, _2, _0, _0, _3>()
    .test<_1, int, int&, int&&, int const, int const&, int const&&>()
    .test<_0, int, int&, int&&, int const, int const&, int const&&, int&>()
    ;

  using first = unpack<at0<>>;
  using smp_first = smp::unpack<smp::at0<>>;
  test_context<
    is_unique_if<each<first, first, lift<std::is_same>>>,
    smp::is_unique_if<smp::each<smp_first, smp_first, smp::lift<std::is_same>>>,
    0 /* unpack<front<>> / unpack<at0<>> is optimized */
  >()
    .test<_1>()
    .test<_1, _0>()
    .test<_0, list<_0, _0>, list<_0, _1>>()
    .test<_1, list<_0, _0>, list<_1, _0>>()
    .test<_0, list<_0, _0>, list<_0, _1>, list<_1, _0>>()
    .not_invocable<_0, _0>()
    ;

  test_context<is_unique_if<equal<>>, smp::is_unique_if<smp::equal<>>>()
    .test<_1>()
    .test<_1, _1>()
    .test<_1, _1, _0>()
    .test<_0, _1, _0, _1>()
    .test<_0, _1, _1, _0, void>()
    .not_invocable<_1, _0, void>()
    ;

  ut::not_invocable<smp::is_unique<bad_function>>();
  ut::not_invocable<smp::is_unique_if<smp::always<na>>, _1, _1>();
  ut::not_invocable<smp::is_unique_if<always<void>>, _1, _1>();
  ut::not_invocable<smp::is_unique_if<always<void>, bad_function>>();
  ut::not_invocable<smp::is_unique_if<always<true_>, bad_function>>();
  ut::not_invocable<smp::is_unique_if<bad_function, bad_function>>();
  ut::not_invocable<smp::is_unique_if<bad_function, bad_function>, _1, _1, _1>();
}

TEST_SUITE_END()
