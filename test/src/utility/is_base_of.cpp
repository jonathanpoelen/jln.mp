// SPDX-FileCopyrightText: 2024 Jonathan Poelen <jonathan.poelen@gmail.com>
// SPDX-License-Identifier: MIT
#include "test.hpp"
#include "test/numbers.hpp"

#include "jln/mp/smp/utility/is_base_of.hpp"

TEST_SUITE_BEGIN()

struct A {};
struct B {};
struct C : A {};

TEST()
{
  using namespace jln::mp;
  using namespace ut::ints;

  test_unary_pack<is_base_of, void>();

  ut::same<_0, emp::is_base_of<void, int>>();
  ut::same<_1, emp::is_base_of<A, A>>();
  ut::same<_0, emp::is_base_of<A, B>>();
  ut::same<_1, emp::is_base_of<A, C>>();
  ut::same<_0, emp::is_base_of<C, A>>();

  test_context<is_base_of<C>, smp::is_base_of<C>>()
    .test<_1, A>()
    .test<_0, B>()
    .test<_1, C>()
    .test<_0, int>()
    .test<_0, void>()
    .not_invocable<>()
    .not_invocable<int, int>()
    ;

  ut::not_invocable<smp::is_base_of<C, bad_function>, A>();
}

TEST_SUITE_END()
