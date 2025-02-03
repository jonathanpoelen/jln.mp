// SPDX-FileCopyrightText: 2025 Jonathan Poelen <jonathan.poelen@gmail.com>
// SPDX-License-Identifier: MIT
#include "test/test_context.hpp"
#include "test/is_invocable.hpp"
#include "test/is_same.hpp"
#include "test/test_case.hpp"
#include "test/numbers.hpp"

#include "jln/mp/smp/utility/make_id.hpp"

#if JLN_MP_ENABLE_FRIEND_INJECTION && !JLN_MP_WORKAROUND(JLN_MP_GCC, < 1200)

TEST_SUITE_BEGIN()

TEST()
{
  using namespace jln::mp;
  using namespace ut::ints;

  test_unary_pack<make_id>();

  using emp::id_of_v;
  using emp::id_of;

  constexpr auto t1 = id_of_v<int>;
  constexpr auto t2 = id_of_v<double>;
  constexpr auto t3 = id_of_v<int, int>;

  JLN_MP_DIAGNOSTIC_PUSH()
  JLN_MP_DIAGNOSTIC_GCC_ONLY_IGNORE("-Wtautological-compare")
  static_assert(t1 == t1);
  static_assert(t1 != t2);
  static_assert(t3 != t1);
  static_assert(t3 == t3);
  static_assert(t3 != t2);
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
