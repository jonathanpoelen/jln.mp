// SPDX-FileCopyrightText: 2023 Jonathan Poelen <jonathan.poelen@gmail.com>
// SPDX-License-Identifier: MIT
#include "test.hpp"
#include "test/numbers.hpp"

#include "jln/mp/smp/utility/always.hpp"
#include "jln/mp/smp/list/take_front.hpp"

TEST_SUITE_BEGIN()

TEST()
{
  using namespace jln::mp;
  using namespace ut::ints;

  test_mulary_pack<take_front, _1>();
  test_mulary_pack<take_front_max, _1>();

  ut::same<seq_0_1, emp::take_front_c<list<_0, _1, _2, _3>, 2>>();

  test_context<take_front_c<0>, smp::take_front_c<0>>()
    .test<list<>>()
    .test<list<>, _0>()
    .test<list<>, _0, _1>()
    ;

  test_context<take_front_c<2>, smp::take_front_c<2>>()
    .test<seq_0_1, _0, _1>()
    .test<seq_0_1, _0, _1, _2>()
    .test<seq_0_1, _0, _1, _2, _3>()
    .not_invocable<_0>()
    ;

  test_context<take_front_c<8>, smp::take_front_c<8>>()
    .test<list<JLN_MP_XS_8(JLN_MP_NIL, JLN_MP_NIL, JLN_MP_COMMA)>,
          JLN_MP_XS_8(JLN_MP_NIL, JLN_MP_NIL, JLN_MP_COMMA)>()
    .test<list<JLN_MP_XS_8(JLN_MP_NIL, JLN_MP_NIL, JLN_MP_COMMA)>,
          JLN_MP_XS_8(JLN_MP_NIL, JLN_MP_NIL, JLN_MP_COMMA), _0, _0>()
    .not_invocable<_0>()
    .not_invocable<JLN_MP_XS_7(JLN_MP_NIL, JLN_MP_NIL, JLN_MP_COMMA)>()
    ;

  test_context<take_front_max_c<2>, smp::take_front_max_c<2>>()
    .test<list<>>()
    .test<seq_0, _0>()
    .test<seq_0_1, _0, _1>()
    .test<seq_0_1, _0, _1, _2>()
    ;

  ut::not_invocable<smp::take_front<smp::always<na>>>();
  ut::not_invocable<smp::take_front<_1, bad_function>>();
  ut::not_invocable<smp::take_front<_1, bad_function>, _1, _1, _1>();
  ut::not_invocable<smp::take_front_max<_1, bad_function>>();
  ut::not_invocable<smp::take_front_max<_1, bad_function>, _1, _1, _1>();
}

TEST_SUITE_END()
