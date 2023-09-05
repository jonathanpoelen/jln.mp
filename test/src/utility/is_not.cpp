// SPDX-FileCopyrightText: 2023 Jonathan Poelen <jonathan.poelen@gmail.com>
// SPDX-License-Identifier: MIT
#include "test.hpp"
#include "test/numbers.hpp"

#include "jln/mp/smp/utility/is_not.hpp"

TEST_SUITE_BEGIN()

TEST()
{
  using namespace jln::mp;
  using namespace ut::ints;

  test_unary_pack<is_not, _1>();

  test_context<is_not<_1>, smp::is_not<_1>>()
    .test<_1, list<>>()
    .test<_0, _1>()
    .not_invocable<>()
    .not_invocable<_0, _1>()
    ;

  ut::not_invocable<smp::is_not<int, bad_function>>();
  ut::not_invocable<smp::is_not<int, bad_function>, int>();
}

TEST_SUITE_END()
