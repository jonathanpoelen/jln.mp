// SPDX-FileCopyrightText: 2023 Jonathan Poelen <jonathan.poelen@gmail.com>
// SPDX-License-Identifier: MIT
#include "test.hpp"
#include "test/numbers.hpp"

#include "jln/mp/smp/map/map_find.hpp"
#include "jln/mp/list/at.hpp"
#include "jln/mp/list/pop_front.hpp"

TEST_SUITE_BEGIN()

TEST()
{
  using namespace jln::mp;
  using namespace ut::ints;

  test_unary_pack<map_find>();
  test_mulary_pack<map_find, identity>();
  test_mulary_pack<map_find, identity, listify>();

  ut::same<seq_1_0, emp::map_find<list<seq_0, seq_1_0>, _1>>();
  ut::same<na, emp::map_find<list<seq_0, seq_1_0>, _2>>();
  ut::same<list<seq_0, seq_1_0>, emp::map_find<list<seq_0, seq_1_0>, _2, identity, listify>>();
  ut::same<list<seq_1_0>, emp::map_find<list<seq_0, seq_1_0>, _1, listify>>();

  // check specializations
  // identity, always<T>
  ut::same<seq_0, map_find<_0, identity, always<na>>::f<seq_0, seq_1_0>>();
  ut::same<na, map_find<_2, identity, always<na>>::f<seq_0, seq_1_0>>();
  // listify, always<T>
  ut::same<list<seq_0>, map_find<_0, listify, always<na>>::f<seq_0, seq_1_0>>();
  ut::same<na, map_find<_2, listify, always<na>>::f<seq_0, seq_1_0>>();
  // always<T>, always<U>
  ut::same<int, map_find<_0, always<int>, always<na>>::f<seq_0, seq_1_0>>();
  ut::same<na, map_find<_2, always<int>, always<na>>::f<seq_0, seq_1_0>>();
  // always<T, C1>, always<U, C2>
  ut::same<list<int>, map_find<_0, always<int, listify>, always<na>>::f<seq_0, seq_1_0>>();
  ut::same<na, map_find<_2, always<int, listify>, always<na>>::f<seq_0, seq_1_0>>();
  // unpack<pop_front<>>, always<T>
  ut::same<list<>, map_find<_0, unpack<pop_front<>>, always<na>>::f<seq_0, seq_1_0>>();
  ut::same<na, map_find<_2, unpack<pop_front<>>, always<na>>::f<seq_0, seq_1_0>>();
  // unpack<pop_front<C1>>, always<T, C2>
  ut::same<list<>, map_find<_0, unpack<pop_front<>>, always<na, listify>>::f<seq_0, seq_1_0>>();
  ut::same<list<na>, map_find<_2, unpack<pop_front<>>, always<na, listify>>::f<seq_0, seq_1_0>>();
  // unpack<at1<>>, always<T>
  ut::same<_2, map_find<_1, unpack<at1<>>, always<na>>::f<seq_0, seq_1_2>>();
  ut::same<na, map_find<_2, unpack<at1<>>, always<na>>::f<seq_0, seq_1_0>>();
  // unpack<at1<C1>>, always<T, C2>
  ut::same<list<_2>, map_find<_1, unpack<at1<listify>>, always<na>>::f<seq_0, seq_1_2>>();
  ut::same<na, map_find<_2, unpack<at1<listify>>, always<na>>::f<seq_0, seq_1_0>>();
  // unpack<C>, always<T, C2>
  ut::same<seq_0, map_find<_0, unpack<listify>, always<na>>::f<seq_0, seq_1>>();
  ut::same<seq_1, map_find<_1, unpack<listify>, always<na>>::f<seq_0, seq_1>>();
  ut::same<seq_1_2, map_find<_1, unpack<listify>, always<na>>::f<seq_0, seq_1_2>>();
  ut::same<na, map_find<_2, unpack<listify>, always<na>>::f<seq_0, seq_1_0>>();


  using Void = always<void>;
  using sVoid = smp::always<void>;

  using mp1 = map_find<_2, identity, Void>;
  ut::same<mp1, map_find_or_else<_2, Void>>();
  ut::same<mp1, map_find_or<_2, void>>();

  using smp1 = smp::map_find<_2, smp::identity, sVoid>;
  ut::same<smp1, smp::map_find_or_else<_2, sVoid>>();
  ut::same<smp1, smp::map_find_or<_2, void>>();

  test_context<map_find<_0, identity, Void>, smp::map_find<_0, smp::identity, sVoid>>()
    .test<void>()
    .test<seq_0, seq_0>()
    .test<seq_0, seq_1, seq_0>()
    .test<void, seq_1>()
    .test<seq_0_1, seq_0_1>()
    .test<seq_0_1, seq_1, seq_0_1>()
    .not_invocable<void>()
    .not_invocable<list<>>()
    .not_invocable<seq_0, seq_0>()
    ;

  test_context<map_find<_2, identity, Void>, smp::map_find<_2, smp::identity, sVoid>>()
    .test<void>()
    .test<void, seq_0>()
    .test<void, seq_0, seq_1>()
    .test<seq_2, seq_0, seq_1, seq_2>()
    .test<seq_2, seq_0, seq_1, seq_2, seq_3>()
    .test<void, seq_0, seq_1, seq_3>()
    .not_invocable<void>()
    .not_invocable<list<>>()
    .not_invocable<seq_0, seq_0>()
    ;

  ut::not_invocable<smp::map_find<_0, bad_function, sVoid>, seq_0>();
  ut::not_invocable<smp::map_find<_0, identity, bad_function>>();
}

TEST_SUITE_END()
