// SPDX-FileCopyrightText: 2023 Jonathan Poelen <jonathan.poelen@gmail.com>
// SPDX-License-Identifier: MIT
#include "test.hpp"

#include "jln/mp/smp/algorithm/same.hpp"
#include "jln/mp/smp/number/not.hpp"

TEST_SUITE_BEGIN()

TEST()
{
  using namespace jln::mp;

  ut::same<true_, emp::same<list<int, int, int>>>();
  ut::same<false_, emp::same<list<int, int, void>>>();

  ut::same<true_, number<emp::same_v<list<int, int, int>>>>();
  ut::same<false_, number<emp::same_v<list<int, int, void>>>>();

  ut::same<true_, number<emp::same_xs_v<int, int, int>>>();
  ut::same<false_, number<emp::same_xs_v<int, int, void>>>();

  test_unary_pack<same>();

  test_context<same<>, smp::same<>>()
    .test<true_>()
    .test<true_, int>()
    .test<true_, int, int>()
    .test<true_, int, int, int>()
    .test<false_, int, void>()
    .test<false_, int, int, void>()
    ;

  test_context<same<not_<>>, smp::same<smp::not_<>>>()
    .test<false_>()
    .test<false_, int>()
    .test<false_, int, int>()
    .test<false_, int, int, int>()
    .test<true_, int, void>()
    .test<true_, int, int, void>()
    ;

  ut::not_invocable<smp::same<bad_function>>();
  ut::not_invocable<smp::same<bad_function>, void>();
  ut::not_invocable<smp::same<bad_function>, void, void>();
  ut::not_invocable<smp::same<bad_function>, void, void, void>();
}

TEST_SUITE_END()
