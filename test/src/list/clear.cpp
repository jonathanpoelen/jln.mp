// SPDX-FileCopyrightText: 2023 Jonathan Poelen <jonathan.poelen@gmail.com>
// SPDX-License-Identifier: MIT
#include "test.hpp"

#include "jln/mp/smp/list/clear.hpp"

TEST_SUITE_BEGIN()

TEST()
{
  using namespace jln::mp;

  test_context<clear<>, smp::clear<>>()
    .test<list<>>()
    .test<list<>, void>()
    .test<list<>, void, void>()
    ;

  ut::not_invocable<smp::clear<bad_function>>();
  ut::not_invocable<smp::clear<bad_function>, void>();
}

TEST_SUITE_END()
