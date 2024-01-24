// SPDX-FileCopyrightText: 2023 Jonathan Poelen <jonathan.poelen@gmail.com>
// SPDX-License-Identifier: MIT
#include "test.hpp"
#include "test/numbers.hpp"

#include "jln/mp/smp/set/set_find.hpp"

TEST_SUITE_BEGIN()

TEST()
{
  using namespace jln::mp;
  using namespace ut::ints;

  test_unary_pack<set_find>();
  test_mulary_pack<set_find, identity>();
  test_mulary_pack<set_find, identity, listify>();

  ut::same<_1, emp::set_find<seq_0_1, _1>>();
  ut::same<na, emp::set_find<seq_0_1, _2>>();
  ut::same<seq_1, emp::set_find<seq_0_1, _1, listify>>();
  ut::same<seq_0_1, emp::set_find<seq_0_1, _2, identity, listify>>();

  using Void = always<void>;
  using sVoid = smp::always<void>;

  using mp1 = set_find<_2, identity, Void>;
  ut::same<mp1, set_find_or_else<_2, Void>>();
  ut::same<mp1, set_find_or<_2, void>>();

  using smp1 = smp::set_find<_2, smp::identity, sVoid>;
  ut::same<smp1, smp::set_find_or_else<_2, sVoid>>();
  ut::same<smp1, smp::set_find_or<_2, void>>();

  test_context<set_find<_0, identity, Void>, smp::set_find<_0, smp::identity, sVoid>>()
    .test<void>()
    .test<void, _1>()
    .test<_0, _0>()
    .test<_0, _1, _0>()
    .test<_0, _0, _1>()
    .not_invocable<_0, _0>()
    .not_invocable<_1, _0, _1>()
    ;

  ut::not_invocable<smp::set_find<_0, bad_function, sVoid>, _0>();
  ut::not_invocable<smp::set_find<_0, identity, bad_function>>();
}

TEST_SUITE_END()
