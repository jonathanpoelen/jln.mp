// SPDX-FileCopyrightText: 2023 Jonathan Poelen <jonathan.poelen@gmail.com>
// SPDX-License-Identifier: MIT
#include "test.hpp"
#include "test/values.hpp"
#include "test/numbers.hpp"

#include "jln/mp/smp/value/as_val.hpp"

TEST_SUITE_BEGIN()

TEST()
{
  using namespace jln::mp;
  using namespace ut::ints;

  ut::same<v2, emp::as_val<_2>>();

  test_unary_pack<as_val>();

  test_context<as_val<>, smp::as_val<>>()
    .test<v1, _1>()
    .test<v1, v1>()
    .not_invocable<>()
    .not_invocable<list<>>()
    .not_invocable<_0, _1>()
    ;

  ut::not_invocable<smp::as_val<bad_function>, _1>();
}

TEST_SUITE_END()
