// SPDX-FileCopyrightText: 2023 Jonathan Poelen <jonathan.poelen@gmail.com>
// SPDX-License-Identifier: MIT
#include "test.hpp"
#include "test/numbers.hpp"

#include "jln/mp/smp/functional/memoize.hpp"
#include "jln/mp/smp/number/operators.hpp"
#include "jln/mp/smp/list/push_back.hpp"

TEST_SUITE_BEGIN()

TEST()
{
  using namespace jln::mp;
  using namespace ut::ints;

  test_mulary_pack<memoize>();

  test_context<
    memoize<identity>,
    smp::memoize<smp::identity>
  >()
    .test<int, int>()
    .not_invocable<>()
    .not_invocable<int, int>()
    ;

  test_context<
    push_back<_2, memoize<less<>>>,
    smp::push_back<_2, smp::memoize<smp::less<>>>
  >()
    .test<_1, _1>()
    .test<_0, _2>()
    .not_invocable<>()
    .not_invocable<int>()
    .not_invocable<_1, _1>()
    .not_invocable<int, int>()
    ;

  ut::not_invocable<smp::memoize<smp::always<na>>>();
  ut::not_invocable<smp::memoize<bad_function>>();
}

TEST_SUITE_END()
