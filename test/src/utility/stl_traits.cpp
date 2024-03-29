// SPDX-FileCopyrightText: 2023 Jonathan Poelen <jonathan.poelen@gmail.com>
// SPDX-License-Identifier: MIT
#include "test.hpp"

#include "jln/mp/smp/utility/stl_traits.hpp"

TEST_SUITE_BEGIN()

TEST()
{
  using namespace jln::mp;

  test_unary_pack<traits::is_same>();

  test_context<traits::is_same<>, smp::traits::is_same<>>()
    .test<std::true_type, int, int>()
    .test<std::false_type, int, void>()
    .not_invocable<>()
    .not_invocable<int>()
    .not_invocable<int, int, int>()
    ;

  ut::not_invocable<smp::traits::is_same<bad_function>>();
  ut::not_invocable<smp::traits::is_same<bad_function>, int>();
  ut::not_invocable<smp::traits::is_same<bad_function>, int, int, int>();
}

TEST_SUITE_END()
