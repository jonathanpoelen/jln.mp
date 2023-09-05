// SPDX-FileCopyrightText: 2023 Jonathan Poelen <jonathan.poelen@gmail.com>
// SPDX-License-Identifier: MIT
#include "test.hpp"
#include "test/values.hpp"
#include "test/numbers.hpp"

#include "jln/mp/smp/value/is_val.hpp"

TEST_SUITE_BEGIN()

TEST()
{
  using namespace jln::mp;
  using namespace ut::ints;

  test_unary_pack<is_val>();

  test_context<is_val<>, smp::is_val<>>()
    .test<_0, list<>>()
    .test<_0, _0>()
    .test<_1, v0>()
    .not_invocable<>()
    .not_invocable<v0, v1>()
    .not_invocable<_0, _1>()
    ;

  ut::not_invocable<smp::is_val<bad_function>, _1>();
}

TEST_SUITE_END()
