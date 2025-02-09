// SPDX-FileCopyrightText: 2023 Jonathan Poelen <jonathan.poelen@gmail.com>
// SPDX-License-Identifier: MIT
#include "test.hpp"
#include "test/numbers.hpp"

#include "jln/mp/smp/utility/always.hpp"
#include "jln/mp/smp/functional/invoke_twice.hpp"
#include "jln/mp/smp/functional/continuation.hpp"
#include "jln/mp/smp/list/pop_front.hpp"
#include "jln/mp/smp/list/front.hpp"
#include "jln/mp/smp/list/take_front.hpp"

TEST_SUITE_BEGIN()

TEST()
{
  using namespace jln::mp;
  using namespace ut::ints;

  test_mulary_pack<invoke_twice>();

  ut::same<list<void, int>, invoke_twice<front<cfe<take_front, cfe<pop_front>>>>
    ::template f<_2, void, int, char, long>>();

  test_context<
    invoke_twice<front<cfe<take_front, cfe<pop_front>>>>,
    smp::invoke_twice<smp::front<smp::cfe<smp::take_front, smp::cfe<smp::pop_front>>>>,
    -1
  >()
    .test<list<void, int>, _2, void, int, char, long>()
    .not_invocable<void, void, int, char, long>()
    .not_invocable<_5, void, int, char, long>()
    ;

  ut::not_invocable<smp::invoke_twice<smp::always<na>>>();
  ut::not_invocable<smp::invoke_twice<bad_function>>();
  ut::not_invocable<smp::invoke_twice<always<bad_function>>>();
}

TEST_SUITE_END()
