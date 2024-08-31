// SPDX-FileCopyrightText: 2023 Jonathan Poelen <jonathan.poelen@gmail.com>
// SPDX-License-Identifier: MIT
#include "test.hpp"
#include "test/numbers.hpp"

#include "jln/mp/smp/functional/select.hpp"
#include "jln/mp/smp/number/operators.hpp"
#include "jln/mp/smp/list/listify.hpp"
#include "jln/mp/smp/list/front.hpp"
#include "jln/mp/number/number.hpp"

TEST_SUITE_BEGIN()

TEST()
{
  using namespace jln::mp;
  using namespace ut::ints;

  test_mulary_pack<select, _0>();
  test_mulary_pack<select, _0, identity>();
  test_mulary_pack<reverse_select, _0>();
  test_mulary_pack<reverse_select, _0, identity>();

  ut::same<_0, emp::select<less<>, _0, _1>>();
  ut::same<_0, emp::select<less<>, _1, _0>>();
  ut::same<_1, emp::select<less<>, _1, _2>>();

  ut::same<_1, emp::reverse_select<less<>, _0, _1>>();
  ut::same<_1, emp::reverse_select<less<>, _1, _0>>();
  ut::same<_2, emp::reverse_select<less<>, _1, _2>>();

  test_context<select<less<>>, smp::select<smp::less<>>>()
    .test<_0, _0, _1>()
    .test<_0, _1, _0>()
    .test<_1, _1, _2>()
    .not_invocable<>()
    .not_invocable<_1>()
    .not_invocable<_1, _2, _3>()
    .not_invocable<bad_number>()
    ;

  test_context<reverse_select<less<>>, smp::reverse_select<smp::less<>>>()
    .test<_1, _0, _1>()
    .test<_1, _1, _0>()
    .test<_2, _1, _2>()
    .not_invocable<>()
    .not_invocable<_1>()
    .not_invocable<_1, _2, _3>()
    .not_invocable<bad_number>()
    ;

  test_context<
    select<less<>, always<int>, listify>,
    smp::select<smp::less<>, smp::always<int>, smp::listify>
  >()
    .test<int, _0, _1>()
    .test<list<_0>, _1, _0>()
    .test<int, _1, _2>()
    .not_invocable<>()
    .not_invocable<_1>()
    .not_invocable<_1, _2, _3>()
    .not_invocable<bad_number>()
    ;

  test_context<
    reverse_select<less<>, always<int>, listify>,
    smp::reverse_select<smp::less<>, smp::always<int>, smp::listify>
  >()
    .test<int, _0, _1>()
    .test<list<_1>, _1, _0>()
    .test<int, _1, _2>()
    .not_invocable<>()
    .not_invocable<_1>()
    .not_invocable<_1, _2, _3>()
    .not_invocable<bad_number>()
    ;

  ut::not_invocable<smp::select<smp::less<bad_function>>>();
  ut::not_invocable<smp::select<smp::less<>, bad_function, identity>>();
  ut::not_invocable<smp::select<smp::less<>, identity, bad_function>>();
}

TEST_SUITE_END()
