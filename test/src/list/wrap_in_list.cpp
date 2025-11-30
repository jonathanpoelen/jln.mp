// SPDX-FileCopyrightText: 2023 Jonathan Poelen <jonathan.poelen@gmail.com>
// SPDX-License-Identifier: MIT
#include "test.hpp"

#include "jln/mp/smp/list/wrap_in_list.hpp"
#include "jln/mp/smp/functional/continuation.hpp"
#include "jln/mp/smp/utility/always.hpp"
#include "jln/mp/smp/utility/is_not.hpp"

#include <type_traits>

TEST_SUITE_BEGIN()

TEST()
{
  using namespace jln::mp;

  using pred1 = is<int>;
  using smp_pred1 = smp::is<int>;
  using pred2 = cfe<std::is_same>;
  using smp_pred2 = smp::cfe<std::is_same>;

  ut::same<list<int>, emp::wrap_in_list_if<pred1, int>>();
  ut::same<list<>, emp::wrap_in_list_if<pred1, char>>();
  ut::same<list<int>, emp::wrap_in_list_if<pred2, int, int>>();
  ut::same<list<>, emp::wrap_in_list_if<pred2, int, char>>();

  ut::same<list<>, emp::wrap_in_list_if_not<pred1, int>>();
  ut::same<list<char>, emp::wrap_in_list_if_not<pred1, char>>();
  ut::same<list<>, emp::wrap_in_list_if_not<pred2, int, int>>();
  ut::same<list<int>, emp::wrap_in_list_if_not<pred2, int, char>>();

  ut::same<list<>, emp::wrap_in_list_if<is<int, not_<>>, int>>();
  ut::same<list<>, emp::wrap_in_list_if<cfe<std::is_same, not_<>>, int, int>>();
  ut::same<list<>, emp::wrap_in_list_if<tee<is<int>, not_<>>, int>>();
  ut::same<list<>, emp::wrap_in_list_if<tee<cfe<std::is_same>, not_<>>, int, int>>();
  ut::same<list<int>, emp::wrap_in_list_if_not<is<int, not_<>>, int>>();
  ut::same<list<int>, emp::wrap_in_list_if_not<cfe<std::is_same, not_<>>, int, int>>();
  ut::same<list<int>, emp::wrap_in_list_if_not<tee<is<int>, not_<>>, int>>();
  ut::same<list<int>, emp::wrap_in_list_if_not<tee<cfe<std::is_same>, not_<>>, int, int>>();

  test_context<wrap_in_list_if<pred1>, smp::wrap_in_list_if<smp_pred1>>()
    .test<list<int>, int>()
    .test<list<>, char>()
    .not_invocable<>()
    .not_invocable<int, int>()
    ;

  test_context<wrap_in_list_if<pred2>, smp::wrap_in_list_if<smp_pred2>>()
    .test<list<int>, int, int>()
    .test<list<>, int, char>()
    .not_invocable<>()
    .not_invocable<int>()
    .not_invocable<int, int, int>()
    ;

  test_context<
    wrap_in_list_if<mp::always<number<2>>>,
    smp::wrap_in_list_if<smp::always<number<2>>>
  >()
    .test<list<int>, int>()
    .test<list<int>, int, char>()
    .not_invocable<>()
    ;

  test_context<wrap_in_list_if_not<pred1>, smp::wrap_in_list_if_not<smp_pred1>>()
    .test<list<>, int>()
    .test<list<char>, char>()
    .not_invocable<>()
    .not_invocable<int, int>()
    ;

  test_context<wrap_in_list_if_not<pred2>, smp::wrap_in_list_if_not<smp_pred2>>()
    .test<list<>, int, int>()
    .test<list<int>, int, char>()
    .not_invocable<>()
    .not_invocable<int>()
    .not_invocable<int, int, int>()
    ;

  test_context<
    wrap_in_list_if_not<mp::always<number<2>>>,
    smp::wrap_in_list_if_not<smp::always<number<2>>>
  >()
    .test<list<>, int>()
    .test<list<>, int, char>()
    .not_invocable<>()
    ;

  ut::not_invocable<smp::wrap_in_list_if<smp::always<na>>, int>();
  ut::not_invocable<smp::wrap_in_list_if<bad_function>>();
  ut::not_invocable<smp::wrap_in_list_if<bad_function>, int, int>();
  ut::not_invocable<smp::wrap_in_list_if<always<void>>, int, int>();
  ut::not_invocable<smp::wrap_in_list_if_not<smp::always<na>>>();
  ut::not_invocable<smp::wrap_in_list_if_not<bad_function>>();
  ut::not_invocable<smp::wrap_in_list_if_not<bad_function>, int, int>();
  ut::not_invocable<smp::wrap_in_list_if_not<always<void>>, int, int>();
}

TEST_SUITE_END()
