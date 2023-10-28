// SPDX-FileCopyrightText: 2023 Jonathan Poelen <jonathan.poelen@gmail.com>
// SPDX-License-Identifier: MIT
#include "test.hpp"

#include "jln/mp/smp/list/as_list.hpp"

TEST_SUITE_BEGIN()

template<class, class, class>
struct fake_list;

template<class...>
struct other_list;

TEST()
{
  using namespace jln::mp;

  test_unary_pack<as_list>();

  using l1 = list<int, char, void>;
  using l2 = fake_list<int, char, void>;
  using l3 = other_list<int, char, void>;

  ut::same<l1, emp::as_list<l1>>();
  ut::same<l1, emp::as_list<l2>>();
  ut::same<l1, emp::as_list<l3>>();

  class bad;

  test_context<as_list<>, smp::as_list<>>()
    .test<l1, l1>()
    .test<l1, l2>()
    .test<l1, l3>()
    .not_invocable<>()
    .not_invocable<bad>()
    .not_invocable<l1, l1>()
    ;

  ut::not_invocable<smp::as_list<bad_function>>();
  ut::not_invocable<smp::as_list<bad_function>, list<>>();
}

TEST_SUITE_END()
