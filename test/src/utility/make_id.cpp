// SPDX-FileCopyrightText: 2025 Jonathan Poelen <jonathan.poelen@gmail.com>
// SPDX-License-Identifier: MIT
#include "test/test_context.hpp"
#include "test/is_invocable.hpp"
#include "test/is_same.hpp"
#include "test/test_case.hpp"
#include "test/numbers.hpp"

#include "jln/mp/smp/utility/make_id.hpp"

#if JLN_MP_ENABLE_FRIEND_INJECTION

TEST_SUITE_BEGIN()

TEST()
{
  using namespace jln::mp;
  using namespace ut::ints;

  test_unary_pack<make_id>();

  using emp::id_of_v;
  using emp::id_of;

  JLN_MP_DIAGNOSTIC_PUSH()
  JLN_MP_DIAGNOSTIC_GCC_ONLY_IGNORE("-Wtautological-compare")
  static_assert(id_of_v<int> == id_of_v<int>);
  static_assert(id_of_v<int> != id_of_v<double>);
  static_assert(id_of_v<int, int> != id_of_v<int>);
  static_assert(id_of_v<int, int> == id_of_v<int, int>);
  static_assert(id_of_v<int, int> != id_of_v<double>);
  JLN_MP_DIAGNOSTIC_POP()

  test_context<make_id<>, smp::make_id<>>()
    .test<id_of<int>, int>()
    .test<id_of<list<>>, list<>>()
    .not_invocable<>()
    .not_invocable<int, int>()
    ;

  test_context<make_id<listify>, smp::make_id<listify>>()
    .test<list<id_of<int>>, int>()
    .test<list<id_of<list<>>>, list<>>()
    .not_invocable<>()
    .not_invocable<int, int>()
    ;

  ut::not_invocable<smp::make_id<bad_function>, int>();
}

TEST_SUITE_END()

#endif
