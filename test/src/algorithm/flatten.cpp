// SPDX-FileCopyrightText: 2023 Jonathan Poelen <jonathan.poelen@gmail.com>
// SPDX-License-Identifier: MIT
#include "test.hpp"
#include "test/numbers.hpp"

#include "jln/mp/smp/algorithm/flatten.hpp"

TEST_SUITE_BEGIN()

template<class...>
struct other_list;

TEST()
{
  using namespace jln::mp;
  using namespace ut::ints;

  test_mulary_pack<flatten, lift<list>>();
  test_mulary_pack<flatten_once, lift<list>>();

  ut::same<seq_0_1_2_3, emp::flatten<
    list<_0, list<_1, list<_2>>, list<list<_3>>>>>();

  test_context<flatten<>, smp::flatten<>>()
    .test<seq_0_1_2_3, _0, _1, _2, _3>()
    .test<seq_0_1_2_3, _0, list<list<_1>, _2>, _3>()
    .test<list<_0, other_list<list<_1>>, _2, _3>,
      _0, list<other_list<list<_1>>, _2>, _3>()
    ;

  test_context<flatten<lift<other_list>>, smp::flatten<lift<other_list>>>()
    .test<seq_0_1_2_3, _0, _1, _2, _3>()
    .test<list<_0, list<list<_1>, _2>, _3>, _0, list<list<_1>, _2>, _3>()
    .test<list<_0, list<_1>, _1, list<_2>, _3>,
      _0, other_list<list<_1>, _1>, list<_2>, _3>()
    ;

  ut::not_invocable<smp::flatten<lift<list>, bad_function>, seq_0>();
  ut::not_invocable<smp::flatten<lift<list>, bad_function>, seq_0, seq_0_2>();
  ut::not_invocable<smp::flatten<bad_function, bad_function>, seq_0>();
  ut::not_invocable<smp::flatten<bad_function, bad_function>, seq_0, seq_0_0_0>();


  ut::same<list<_0, _1, list<_2>, list<_3>>, emp::flatten_once<
    list<_0, list<_1, list<_2>>, list<list<_3>>>>>();

  test_context<flatten_once<>, smp::flatten_once<>>()
    .test<seq_0_1_2_3, _0, _1, _2, _3>()
    .test<list<_0, list<_1>, _2, _3>, _0, list<list<_1>, _2>, _3>()
    .test<list<_0, other_list<list<_1>>, _2, _3>,
      _0, list<other_list<list<_1>>, _2>, _3>()
    ;

  test_context<flatten_once<lift<other_list>>, smp::flatten_once<lift<other_list>>>()
    .test<seq_0_1_2_3, _0, _1, _2, _3>()
    .test<list<_0, list<list<_1>, _2>, _3>, _0, list<list<_1>, _2>, _3>()
    .test<list<_0, list<_1>, _1, list<_2>, _3>,
      _0, other_list<list<_1>, _1>, list<_2>, _3>()
    ;

  ut::not_invocable<smp::flatten_once<lift<list>, bad_function>, seq_0>();
  ut::not_invocable<smp::flatten_once<lift<list>, bad_function>, seq_0, seq_0_2>();
  ut::not_invocable<smp::flatten_once<bad_function, bad_function>, seq_0>();
  ut::not_invocable<smp::flatten_once<bad_function, bad_function>, seq_0, seq_0_0_0>();
}

TEST_SUITE_END()
