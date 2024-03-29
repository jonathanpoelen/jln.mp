// SPDX-FileCopyrightText: 2023 Jonathan Poelen <jonathan.poelen@gmail.com>
// SPDX-License-Identifier: MIT
#include "test.hpp"
#include "test/numbers.hpp"

#include "jln/mp/smp/list/is_empty.hpp"

TEST_SUITE_BEGIN()

TEST()
{
  using namespace jln::mp;
  using namespace ut::ints;

  test_unary_pack<is_empty>();

  ut::same<_0, emp::is_empty<list<int, int, int>>>();
  ut::same<_1, emp::is_empty<list<>>>();

  test_context<is_empty<>, smp::is_empty<>>()
    .test<_1>()
    .test<_0, int>()
    ;

  // optimized alias :)
  ut::same<smp::is_empty<>, contract<size<not_<identity>>>>();

  ut::not_invocable<smp::is_empty<bad_function>>();
  ut::not_invocable<smp::is_empty<bad_function>, _1>();
}

TEST_SUITE_END()
