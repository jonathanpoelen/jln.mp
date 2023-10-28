// SPDX-FileCopyrightText: 2023 Jonathan Poelen <jonathan.poelen@gmail.com>
// SPDX-License-Identifier: MIT
#include "test.hpp"
#include "test/numbers.hpp"

#include "jln/mp/smp/list/size.hpp"

TEST_SUITE_BEGIN()

TEST()
{
  using namespace jln::mp;
  using namespace ut::ints;

  test_unary_pack<size>();

  ut::same<_3, emp::size<list<int, int, int>>>();

  test_context<size<>, smp::size<>>()
    .test<_0>()
    .test<_1, int>()
    .test<_2, int, void>()
    .test<_3, int, void, char>()
    ;

  ut::same<smp::size<>, contract<mp::size<>>>();

  ut::not_invocable<smp::size<bad_function>>();
}

TEST_SUITE_END()
