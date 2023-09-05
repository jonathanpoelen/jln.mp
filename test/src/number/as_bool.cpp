// SPDX-FileCopyrightText: 2023 Jonathan Poelen <jonathan.poelen@gmail.com>
// SPDX-License-Identifier: MIT
#include "test.hpp"

#include "jln/mp/smp/number/as_bool.hpp"
#include "jln/mp/smp/number/operators.hpp"

#include <type_traits>


TEST_SUITE_BEGIN()

TEST()
{
  using namespace jln::mp;

  using a = number<0>;
  using b = std::integral_constant<int, 1>;
  using c = std::integral_constant<unsigned long long, ~0ull>;

  ut::same<a, emp::as_bool<a>>();
  ut::same<number<1>, emp::as_bool<b>>();

  test_unary_pack<as_bool>();

  test_context<as_bool<>, smp::as_bool<>>()
    .test<a, a>()
    .test<number<1>, b>()
    .not_invocable<number<1>, number<3>>() // narrowing conversion
    .not_invocable<void>()
    .not_invocable<c>() // narrowing conversion
    .not_invocable<>()
    ;

  test_context<as_bool<not_<>>, smp::as_bool<smp::not_<>>>()
    .test<number<1>, a>()
    .test<number<0>, b>()
    .not_invocable<number<1>, number<3>>() // narrowing conversion
    .not_invocable<void>()
    .not_invocable<c>() // narrowing conversion
    .not_invocable<>()
    ;

  ut::not_invocable<smp::as_bool<bad_function>>();
  ut::not_invocable<smp::as_bool<bad_function>, true_>();
  ut::not_invocable<smp::as_bool<smp::not_<bad_function>>, true_>();
}

TEST_SUITE_END()
