// SPDX-FileCopyrightText: 2023 Jonathan Poelen <jonathan.poelen@gmail.com>
// SPDX-License-Identifier: MIT
#include "test.hpp"
#include "test/numbers.hpp"

#include "jln/mp/smp/functional/lift.hpp"
#include "jln/mp/smp/list/push_front.hpp"

TEST_SUITE_BEGIN()

template<class x>
using foo = x;

template<class x>
struct bar
{
  using type = x;
};

class x {};

using int_t = jln::mp::int_t;

struct unary_i { template<int_t> struct f { struct type; }; };
struct binary_i { template<int_t, int_t> struct f { struct type; }; };
struct mulary_i { template<int_t...> struct f { struct type; }; };

TEST()
{
  using namespace jln::mp;
  using namespace ut::ints;

  (void)lift<ut::unary::f>();
  (void)lift<ut::binary::f>();
  (void)lift<ut::listify::f>();

  (void)lift_t<ut::unary::f>();
  (void)lift_t<ut::binary::f>();
  (void)lift_t<ut::listify::f>();

  (void)lift_v<unary_i::f>();
  (void)lift_v<binary_i::f>();
  (void)lift_v<mulary_i::f>();

  (void)lift_v_t<unary_i::f>();
  (void)lift_v_t<binary_i::f>();
  (void)lift_v_t<mulary_i::f>();

  (void)lift_v_c<unary_i::f>();
  (void)lift_v_c<binary_i::f>();
  (void)lift_v_c<mulary_i::f>();

  (void)lift_v_c_t<unary_i::f>();
  (void)lift_v_c_t<binary_i::f>();
  (void)lift_v_c_t<mulary_i::f>();

  test_context<lift<foo>, smp::lift<foo>>()
    .test<x, x>()
    .not_invocable<x, x>()
    ;

  test_context<lift_t<bar>, smp::lift_t<bar>>()
    .test<x, x>()
    .not_invocable<x, x>()
    ;

  test_context<lift<bar>, smp::lift<bar>>()
    .test<bar<x>, x>()
    ;

  test_context<lift_t<foo>, smp::lift_t<foo>>()
    .not_invocable<x>()
    ;

  test_context<lift<violation::f>, smp::lift<violation::f>>()
    .not_invocable<x>()
    ;

  test_context<lift_t<violation::f>, smp::lift_t<violation::f>>()
    .not_invocable<x>()
    ;

  ut::not_invocable<smp::lift<foo, bad_function>>();
  ut::not_invocable<smp::lift_t<bar, bad_function>>();
  ut::not_invocable<smp::lift<bar, bad_function>>();

  constexpr int_t a1 = 1;
  constexpr int_t a2 = 2;

  test_context<lift_v<mulary_i::f>, void>()
    .test<mulary_i::f<>>()
    .test<mulary_i::f<a1>, _1>()
    .test<mulary_i::f<a1, a2>, _1, _2>()
    ;

  test_context<lift_v_t<mulary_i::f>, void>()
    .test<mulary_i::f<>::type>()
    .test<mulary_i::f<a1>::type, _1>()
    .test<mulary_i::f<a1, a2>::type, _1, _2>()
    ;

  ut::same<mulary_i::f<>, lift_v_c<mulary_i::f>::f<>>();
  ut::same<mulary_i::f<a1>, lift_v_c<mulary_i::f>::f<a1>>();
  ut::same<mulary_i::f<a1, a2>, lift_v_c<mulary_i::f>::f<a1, a2>>();

  ut::same<mulary_i::f<>::type, lift_v_c_t<mulary_i::f>::f<>>();
  ut::same<mulary_i::f<a1>::type, lift_v_c_t<mulary_i::f>::f<a1>>();
  ut::same<mulary_i::f<a1, a2>::type, lift_v_c_t<mulary_i::f>::f<a1, a2>>();
}

TEST_SUITE_END()
