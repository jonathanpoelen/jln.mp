// SPDX-FileCopyrightText: 2023 Jonathan Poelen <jonathan.poelen@gmail.com>
// SPDX-License-Identifier: MIT
#include "test.hpp"
#include "test/numbers.hpp"

#include "jln/mp/smp/functional/capture_back.hpp"
#include "jln/mp/smp/functional/identity.hpp"
#include "jln/mp/smp/list/pop_front.hpp"
#include "jln/mp/number/numbers.hpp"

TEST_SUITE_BEGIN()

struct foo
{
  template<class, int>
  struct f
  {};
};

TEST()
{
  using namespace jln::mp;
  using namespace ut::ints;

  test_mulary_pack<capture_back>();

  ut::same<capture_back<_1>, capture_back_c<1>>();

  test_context<capture_back<int, char>, smp::capture_back<int, char>>()
    .test<list<char>, pop_front<>>()
    .test<list<>, pop_front<pop_front<>>>()
    .test<list<void, int, char>, listify, void>()
    .not_invocable<void>()
    .not_invocable<smp::identity>()
    .not_invocable<pop_front<pop_front<smp::pop_front<>>>>()
    ;

  test_context<capture_back_v<1>, void>()
    .test<foo::f<_2, 1>, foo, _2>()
    ;
}

TEST_SUITE_END()
