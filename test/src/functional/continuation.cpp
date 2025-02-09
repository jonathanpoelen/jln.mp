// SPDX-FileCopyrightText: 2023 Jonathan Poelen <jonathan.poelen@gmail.com>
// SPDX-License-Identifier: MIT
#include "test.hpp"
#include "test/numbers.hpp"

#include "jln/mp/smp/functional/continuation.hpp"
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

  (void)cfe<ut::unary::f>();
  (void)cfe<ut::binary::f>();
  (void)cfe<ut::listify::f>();

  (void)cfl<ut::unary::f>();
  (void)cfl<ut::binary::f>();
  (void)cfl<ut::listify::f>();

  (void)cfe_v<unary_i::f>();
  (void)cfe_v<binary_i::f>();
  (void)cfe_v<mulary_i::f>();

  (void)cfl_v<unary_i::f>();
  (void)cfl_v<binary_i::f>();
  (void)cfl_v<mulary_i::f>();

  (void)cfe_v_c<unary_i::f>();
  (void)cfe_v_c<binary_i::f>();
  (void)cfe_v_c<mulary_i::f>();

  (void)cfl_v_c<unary_i::f>();
  (void)cfl_v_c<binary_i::f>();
  (void)cfl_v_c<mulary_i::f>();

  test_context<cfe<foo>, smp::cfe<foo>>()
    .test<x, x>()
    .not_invocable<x, x>()
    ;

  test_context<cfl<bar>, smp::cfl<bar>>()
    .test<x, x>()
    .not_invocable<x, x>()
    ;

  test_context<cfe<bar>, smp::cfe<bar>>()
    .test<bar<x>, x>()
    ;

  test_context<cfl<foo>, smp::cfl<foo>>()
    .not_invocable<x>()
    ;

  test_context<cfe<violation::f>, smp::cfe<violation::f>>()
    .not_invocable<x>()
    ;

  test_context<cfl<violation::f>, smp::cfl<violation::f>>()
    .not_invocable<x>()
    ;

  ut::not_invocable<smp::cfe<foo, bad_function>>();
  ut::not_invocable<smp::cfl<bar, bad_function>>();
  ut::not_invocable<smp::cfe<bar, bad_function>>();

  constexpr int_t a1 = 1;
  constexpr int_t a2 = 2;

  test_context<cfe_v<mulary_i::f>, void>()
    .test<mulary_i::f<>>()
    .test<mulary_i::f<a1>, _1>()
    .test<mulary_i::f<a1, a2>, _1, _2>()
    ;

  test_context<cfl_v<mulary_i::f>, void>()
    .test<mulary_i::f<>::type>()
    .test<mulary_i::f<a1>::type, _1>()
    .test<mulary_i::f<a1, a2>::type, _1, _2>()
    ;

  ut::same<mulary_i::f<>, cfe_v_c<mulary_i::f>::f<>>();
  ut::same<mulary_i::f<a1>, cfe_v_c<mulary_i::f>::f<a1>>();
  ut::same<mulary_i::f<a1, a2>, cfe_v_c<mulary_i::f>::f<a1, a2>>();

  ut::same<mulary_i::f<>::type, cfl_v_c<mulary_i::f>::f<>>();
  ut::same<mulary_i::f<a1>::type, cfl_v_c<mulary_i::f>::f<a1>>();
  ut::same<mulary_i::f<a1, a2>::type, cfl_v_c<mulary_i::f>::f<a1, a2>>();
}

TEST_SUITE_END()
