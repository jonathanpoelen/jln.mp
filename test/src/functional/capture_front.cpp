// SPDX-FileCopyrightText: 2023 Jonathan Poelen <jonathan.poelen@gmail.com>
// SPDX-License-Identifier: MIT
#include "test.hpp"
#include "test/numbers.hpp"

#include "jln/mp/smp/functional/capture_front.hpp"
#include "jln/mp/smp/functional/identity.hpp"
#include "jln/mp/smp/list/pop_front.hpp"
#include "jln/mp/number/numbers.hpp"

TEST_SUITE_BEGIN()

struct foo
{
  template<int, class...>
  struct f
  {};
};

TEST()
{
  using namespace jln::mp;
  using namespace ut::ints;

  test_mulary_pack<capture_front>();

  ut::same<capture_front<_1>, capture_front_c<1>>();

  test_context<capture_front<int, char>, smp::capture_front<int, char>>()
    .test<list<char>, pop_front<>>()
    .test<list<>, pop_front<pop_front<>>>()
    .test<list<int, char, void>, listify, void>()
    .not_invocable<void>()
    .not_invocable<smp::identity>()
    .not_invocable<pop_front<pop_front<smp::pop_front<>>>>()
    ;

  test_context<capture_front_v<1>, void>()
    .test<foo::f<1, _2>, foo, _2>()
    ;
}

TEST_SUITE_END()
