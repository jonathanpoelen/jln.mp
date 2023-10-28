// SPDX-FileCopyrightText: 2023 Jonathan Poelen <jonathan.poelen@gmail.com>
// SPDX-License-Identifier: MIT
#include "test.hpp"
#include "test/numbers.hpp"

#include "jln/mp/smp/list/join.hpp"

TEST_SUITE_BEGIN()

TEST()
{
  using namespace jln::mp;
  using namespace ut::ints;

  test_mulary_pack<join>();

  class X;
  using a = list<_0, _1, _2>;
  using b = list<_3, _4>;
  using c = list<X>;
  using e = list<>;
  using flat_list = list<_0, _1, _2, _3, _4, X>;

  ut::same<flat_list, emp::join<a, b, c>>();
  ut::same<e, emp::join<list<>, e, e>>();

  test_context<join<>, smp::join<>>()
    .test<e>()
    .test<e, e, e>()
    .test<c, c, e>()
    .test<flat_list, a, b, c>()
    .not_invocable<X, e>()
    ;
  test_context<join<join<>>, smp::join<smp::join<>>>()
    .test<flat_list, list<a, b>, list<c>>()
    .test<c, list<c>, e>()
    .not_invocable<c, e>()
    ;

  test_context<join<join<join<>>>, smp::join<smp::join<smp::join<>>>>()
    .test<e, e>()
    .test<e, list<e>, e>()
    .test<c, list<list<c>>, e>()
    .not_invocable<c, e>()
    .not_invocable<list<c>, e>()
    ;

  ut::not_invocable<smp::join<smp::always<na>>>();
  ut::not_invocable<smp::join<bad_function>>();
  ut::not_invocable<smp::join<bad_function>, seq_0_0, seq_0_0>();
}

TEST_SUITE_END()
