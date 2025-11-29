// SPDX-FileCopyrightText: 2023 Jonathan Poelen <jonathan.poelen@gmail.com>
// SPDX-License-Identifier: MIT
#include "test.hpp"

#include "jln/mp/smp/algorithm/same.hpp"
#include "jln/mp/smp/number/not.hpp"

TEST_SUITE_BEGIN()

template<class T, class... Ts>
static inline constexpr bool test_all_same_as = JLN_MP_ALL_SAME_AS(T, Ts);

template<class T, class... Ts>
static inline constexpr bool test_any_same_as = JLN_MP_ANY_SAME_AS(T, Ts);

template<class T, class... Ts>
static inline constexpr bool test_none_same_as = JLN_MP_NONE_SAME_AS(T, Ts);

TEST()
{
  using namespace jln::mp;

  static_assert(test_all_same_as<int, int, int>);
  static_assert(!test_all_same_as<int, int, char>);
  static_assert(!test_all_same_as<int, char, char>);

  static_assert(!test_none_same_as<int, int, int>);
  static_assert(!test_none_same_as<int, int, char>);
  static_assert(test_none_same_as<int, char, char>);

  static_assert(test_any_same_as<int, int, int>);
  static_assert(test_any_same_as<int, int, char>);
  static_assert(!test_any_same_as<int, char, char>);

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
