// SPDX-FileCopyrightText: 2023 Jonathan Poelen <jonathan.poelen@gmail.com>
// SPDX-License-Identifier: MIT
#include "test.hpp"

#include "jln/mp/smp/utility/always.hpp"
#include "jln/mp/smp/functional/flip.hpp"

TEST_SUITE_BEGIN()

TEST()
{
  using namespace jln::mp;

  test_mulary_pack<flip>();

  ut::same<list<char, int, void>, emp::flip<list<int, char, void>>>();

  test_context<flip<>, smp::flip<>>()
    .test<list<int, char>, char, int>()
    .test<list<int, char, void>, char, int, void>()
    .not_invocable<>()
    .not_invocable<int>()
    ;

  ut::not_invocable<smp::flip<smp::always<na>>, void, int>();
  ut::not_invocable<smp::flip<bad_function>, void, int>();
}

TEST_SUITE_END()
