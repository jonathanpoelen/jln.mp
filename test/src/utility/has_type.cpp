// SPDX-FileCopyrightText: 2023 Jonathan Poelen <jonathan.poelen@gmail.com>
// SPDX-License-Identifier: MIT
#include "test.hpp"
#include "test/numbers.hpp"

#include "jln/mp/smp/utility/has_type.hpp"

TEST_SUITE_BEGIN()

struct dummy
{
  using type = int;
};

TEST()
{
  using namespace jln::mp;
  using namespace ut::ints;

  test_unary_pack<has_type>();

  test_context<has_type<>, smp::has_type<>>()
    .test<_0, list<>>()
    .test<_1, dummy>()
    .not_invocable<>()
    .not_invocable<_0, _1>()
    ;

  ut::not_invocable<smp::has_type<bad_function>>();
  ut::not_invocable<smp::has_type<bad_function>, int>();
  ut::not_invocable<smp::has_type<bad_function>, dummy>();
}

TEST_SUITE_END()
