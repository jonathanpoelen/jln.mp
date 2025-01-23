// SPDX-FileCopyrightText: 2023 Jonathan Poelen <jonathan.poelen@gmail.com>
// SPDX-License-Identifier: MIT
#include "test.hpp"
#include "test/numbers.hpp"

#include "jln/mp/smp/functional/bind_front.hpp"
#include "jln/mp/smp/number/numbers.hpp"
#include "jln/mp/smp/list/pop_front.hpp"
#include "jln/mp/smp/list/listify.hpp"

TEST_SUITE_BEGIN()

#if JLN_MP_ENABLE_TPL_AUTO
struct foo
{
  template<int, class...>
  struct f
  {};
};
#endif

TEST()
{
  using namespace jln::mp;
  using namespace ut::ints;

  test_mulary_pack<bind_front>();

  ut::same<list<int, char, long>, emp::bind_front<list<char, long>, listify, int>>();
  ut::same<list<int, void, char, long>, emp::bind_front<list<char, long>, listify, int, void>>();

  ut::same<bind_front<listify, _1>, bind_front_c<listify, 1>>();

  test_context<
    bind_front<pop_front<>>,
    smp::bind_front<smp::pop_front<>>
  >()
    .test<list<>, void>()
    .test<list<char>, void, char>()
    .not_invocable<>()
    ;

  test_context<
    bind_front<pop_front<>, int>,
    smp::bind_front<smp::pop_front<>, int>
  >()
    .test<list<>>()
    .test<list<void>, void>()
    .test<list<void, char>, void, char>()
    ;

  test_context<
    bind_front<pop_front<>, int, long>,
    smp::bind_front<smp::pop_front<>, int, long>
  >()
    .test<list<long>>()
    .test<list<long, void>, void>()
    .test<list<long, void, char>, void, char>()
    ;

#if JLN_MP_ENABLE_TPL_AUTO
  test_context<bind_front_v<foo, 3>, void>()
    .test<foo::f<3>>()
    .test<foo::f<3, _1>, _1>()
    ;
#endif

  ut::not_invocable<smp::bind_front<smp::pop_front<>>>();
  ut::not_invocable<smp::bind_front<bad_contract>>();
  ut::not_invocable<smp::bind_front<bad_contract>, void>();
}

TEST_SUITE_END()
