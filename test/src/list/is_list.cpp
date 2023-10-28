// SPDX-FileCopyrightText: 2023 Jonathan Poelen <jonathan.poelen@gmail.com>
// SPDX-License-Identifier: MIT
#include "test.hpp"
#include "test/numbers.hpp"

#include "jln/mp/smp/list/is_list.hpp"

TEST_SUITE_BEGIN()

TEST()
{
  using namespace jln::mp;
  using namespace ut::ints;

  test_unary_pack<is_list>();

  ut::same<_0, emp::is_list<_0>>();
  ut::same<_1, emp::is_list<list<>>>();

  test_context<is_list<>, smp::is_list<>>()
    .test<_0, _1>()
    .test<_1, list<>>()
    .not_invocable<_0, _0>()
    ;

  ut::not_invocable<smp::is_list<bad_function>>();
  ut::not_invocable<smp::is_list<bad_function>, list<>>();
}

TEST_SUITE_END()
