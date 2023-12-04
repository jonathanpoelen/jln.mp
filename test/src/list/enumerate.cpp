// SPDX-FileCopyrightText: 2023 Jonathan Poelen <jonathan.poelen@gmail.com>
// SPDX-License-Identifier: MIT
#include "test.hpp"
#include "test/numbers.hpp"

#include "jln/mp/smp/functional/flip.hpp"
#include "jln/mp/smp/list/enumerate.hpp"
#include "jln/mp/smp/utility/always.hpp"

TEST_SUITE_BEGIN()

class A;
class B;
class C;

struct indexed_type
{
  template<int i, class T>
  struct f;
};

TEST()
{
  using namespace jln::mp;
  using namespace ut::ints;

  test_mulary_pack<enumerate>();
  test_mulary_pack<enumerate_with>();

  using IndexedList = list<indexed_type::f<0, A>, indexed_type::f<1, B>, indexed_type::f<2, C>>;

  ut::same<IndexedList, enumerate_v_with<indexed_type>::f<A, B, C>>();
  ut::same<IndexedList, emp::enumerate_v_with<list<A, B, C>, indexed_type>>();


  using Enumerated = list<list<_0, A>, list<_1, B>, list<_2, C>>;
  using Enumerated2 = list<list<_1, B>, list<_0, A>, list<_2, C>>;
  using FlippedEnumerated = list<list<A, _0>, list<B, _1>, list<C, _2>>;

  ut::same<Enumerated, emp::enumerate_with<list<A, B, C>>>();
  ut::same<Enumerated2, emp::enumerate<list<A, B, C>, mp::flip<>>>();
  ut::same<FlippedEnumerated, emp::enumerate_with<list<A, B, C>, mp::flip<>>>();
  ut::same<Enumerated2, emp::enumerate_with<list<A, B, C>, mp::listify, mp::flip<>>>();

  test_context<enumerate<>, smp::enumerate<>>()
    .test<Enumerated, A, B, C>()
  ;

  test_context<enumerate_with<flip<>>, smp::enumerate_with<smp::flip<>>>()
    .test<FlippedEnumerated, A, B, C>()
  ;

  ut::not_invocable<smp::enumerate<smp::always<na>>, _1, _1, _1>();
  ut::not_invocable<smp::enumerate<bad_function>, _1, _1, _1>();
  ut::not_invocable<smp::enumerate_with<smp::always<na>>, _1, _1, _1>();
}

TEST_SUITE_END()
