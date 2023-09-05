// SPDX-FileCopyrightText: 2023 Jonathan Poelen <jonathan.poelen@gmail.com>
// SPDX-License-Identifier: MIT
#include "test.hpp"
#include "test/numbers.hpp"

#include "jln/mp/smp/algorithm/scan_right.hpp"
#include "jln/mp/smp/list/pop_front.hpp"
#include "jln/mp/smp/number/operators.hpp"

TEST_SUITE_BEGIN()

TEST()
{
  using namespace jln::mp;
  using namespace ut::ints;

  ut::same<
    list<
      list<_0, list<_1, _2>>,
      list<_1, _2>,
      _2
    >,
    emp::scan_right<seq_0_1_2, listify>
  >();

  test_mulary_pack<scan_right>();
  test_mulary_pack<scan_right, listify>();

  test_context<scan_right<listify>, smp::scan_right<smp::listify>>()
    .test<list<>>()
    .test<list<_0>, _0>()
    .test<list<list<_0, _1>, _1>, _0, _1>()
    .test<list<list<_0, list<_1, _2>>, list<_1, _2>, _2>, _0, _1, _2>()
    .test<
      list<
        list<_0, list<_1, list<_2, _3>>>,
        list<_1, list<_2, _3>>,
        list<_2, _3>,
        _3
      >,
      _0, _1, _2, _3>()
    .test<
      list<
        list<_0, list<_1, list<_2, list<_3, list<_4, list<_5, list<_6, list<_7, list<_8, list<_9, _10>>>>>>>>>>,
        list<_1, list<_2, list<_3, list<_4, list<_5, list<_6, list<_7, list<_8, list<_9, _10>>>>>>>>>,
        list<_2, list<_3, list<_4, list<_5, list<_6, list<_7, list<_8, list<_9, _10>>>>>>>>,
        list<_3, list<_4, list<_5, list<_6, list<_7, list<_8, list<_9, _10>>>>>>>,
        list<_4, list<_5, list<_6, list<_7, list<_8, list<_9, _10>>>>>>,
        list<_5, list<_6, list<_7, list<_8, list<_9, _10>>>>>,
        list<_6, list<_7, list<_8, list<_9, _10>>>>,
        list<_7, list<_8, list<_9, _10>>>,
        list<_8, list<_9, _10>>,
        list<_9, _10>,
        _10
      >,
      _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10>()
    ;

  test_context<
    scan_right<pop_front<identity>>,
    smp::scan_right<smp::pop_front<smp::identity>>
  >()
    .test<list<>>()
    .test<seq_0, _0>()
    .test<seq_1_1, _0, _1>()
    .test<list<_3, _3, _3, _3>, _0, _1, _2, _3>()
    .not_invocable<na>()
    .not_invocable<_0, na>()
    .not_invocable<_0, _1, na>()
    ;

  ut::not_invocable<smp::scan_right<smp::always<na>>, _1, _1, _1>();
  ut::not_invocable<smp::scan_right<listify, bad_function>, _1>();
  ut::not_invocable<smp::scan_right<listify, bad_function>, _1, _1, _1>();
  ut::not_invocable<smp::scan_right<bad_function, bad_function>, _1>();
  ut::not_invocable<smp::scan_right<bad_function, bad_function>, _1, _1, _1>();
  ut::not_invocable<smp::scan_right<bad_function, bad_function>, _1, _1, _1, _1, _1>();
  ut::not_invocable<smp::scan_right<smp::add<>>, _1, _1, _1, _1, _1, void>();
  ut::not_invocable<smp::scan_right<smp::add<>>, void, _1, _1, _1, _1, _1>();
  ut::not_invocable<smp::scan_right<smp::add<>>,
    _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, void>();
  ut::not_invocable<smp::scan_right<smp::add<>>,
    void, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1>();
}

TEST_SUITE_END()
