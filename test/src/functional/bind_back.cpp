// SPDX-FileCopyrightText: 2023 Jonathan Poelen <jonathan.poelen@gmail.com>
// SPDX-License-Identifier: MIT
#include "test.hpp"
#include "test/numbers.hpp"

#include "jln/mp/smp/functional/bind_back.hpp"
#include "jln/mp/smp/number/numbers.hpp"
#include "jln/mp/smp/list/pop_back.hpp"
#include "jln/mp/smp/list/listify.hpp"

TEST_SUITE_BEGIN()

#if JLN_MP_ENABLE_TPL_PARAM_AUTO
struct foo
{
  template<class, int>
  struct f
  {};
};
#endif

TEST()
{
  using namespace jln::mp;
  using namespace ut::ints;

  test_mulary_pack<bind_back>();

  ut::same<list<char, long, int>, emp::bind_back<list<char, long>, listify, int>>();
  ut::same<list<char, long, int, void>, emp::bind_back<list<char, long>, listify, int, void>>();

  ut::same<bind_back<listify, _1>, bind_back_c<listify, 1>>();

  test_context<
    bind_back<pop_back<>>,
    smp::bind_back<smp::pop_back<>>
  >()
    .test<list<>, void>()
    .test<list<void>, void, char>()
    .not_invocable<>()
    ;

  test_context<
    bind_back<pop_back<>, int>,
    smp::bind_back<smp::pop_back<>, int>
  >()
    .test<list<>>()
    .test<list<void>, void>()
    .test<list<void, char>, void, char>()
    ;

  test_context<
    bind_back<pop_back<>, int, long>,
    smp::bind_back<smp::pop_back<>, int, long>
  >()
    .test<list<int>>()
    .test<list<void, int>, void>()
    .test<list<void, char, int>, void, char>()
    ;

#if JLN_MP_ENABLE_TPL_PARAM_AUTO
  test_context<bind_back_v<foo, 3>, void>()
    .test<foo::f<_1, 3>, _1>()
    ;
#endif

  ut::not_invocable<smp::bind_back<smp::pop_back<>>>();
  ut::not_invocable<smp::bind_back<bad_contract>>();
  ut::not_invocable<smp::bind_back<bad_contract>, void>();
}

TEST_SUITE_END()
