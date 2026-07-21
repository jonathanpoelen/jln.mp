// SPDX-FileCopyrightText: 2026 Jonathan Poelen <jonathan.poelen@gmail.com>
// SPDX-License-Identifier: MIT

#include "jln/mp/smp/functional/sfinae_truthy_falsy.hpp"

#if !JLN_MP_FEATURE_CONCEPTS

#include "test/test_case.hpp"

#else

#include "test.hpp"
#include "test/numbers.hpp"

TEST_SUITE_BEGIN()

TEST()
{
  using namespace jln::mp;
  using namespace ut::ints;

  static_assert(!sfinae_truthy_as<identity>);
  static_assert( sfinae_truthy_as<identity, _2>);
  static_assert( sfinae_truthy_as<identity, _1>);
  static_assert(!sfinae_truthy_as<identity, _0>);
  static_assert(!sfinae_truthy_as<identity, _1, _1>);
  static_assert(!sfinae_truthy_as<identity, void>);

  static_assert(!sfinae_falsy_as<identity>);
  static_assert(!sfinae_falsy_as<identity, _2>);
  static_assert(!sfinae_falsy_as<identity, _1>);
  static_assert( sfinae_falsy_as<identity, _0>);
  static_assert(!sfinae_falsy_as<identity, _1, _1>);
  static_assert(!sfinae_falsy_as<identity, void>);

  ut::same<_0, emp::is_sfinae_truthy<list<>, identity>>();
  ut::same<_1, emp::is_sfinae_truthy<list<_2>, identity>>();
  ut::same<_1, emp::is_sfinae_truthy<list<_1>, identity>>();
  ut::same<_0, emp::is_sfinae_truthy<list<_0>, identity>>();
  ut::same<_0, emp::is_sfinae_truthy<list<_1, _1>, identity>>();
  ut::same<_0, emp::is_sfinae_truthy<list<void>, identity>>();

  ut::same<_0, emp::is_sfinae_falsy<list<>, identity>>();
  ut::same<_0, emp::is_sfinae_falsy<list<_2>, identity>>();
  ut::same<_0, emp::is_sfinae_falsy<list<_1>, identity>>();
  ut::same<_1, emp::is_sfinae_falsy<list<_0>, identity>>();
  ut::same<_0, emp::is_sfinae_falsy<list<_1, _1>, identity>>();
  ut::same<_0, emp::is_sfinae_falsy<list<void>, identity>>();

  test_unary_pack<is_sfinae_falsy>();
  test_unary_pack<is_sfinae_truthy>();
  test_unary_pack<is_sfinae_falsy, to_bool<>>();
  test_unary_pack<is_sfinae_truthy, to_bool<>>();

  test_context<is_sfinae_truthy<identity>, smp::is_sfinae_truthy<smp::identity>>()
    .test<false_>()
    .test<true_, _2>()
    .test<true_, _1>()
    .test<false_, _0>()
    .test<false_, _1, _1>()
    .test<false_, void>()
    ;

  test_context<is_sfinae_falsy<identity>, smp::is_sfinae_falsy<smp::identity>>()
    .test<false_>()
    .test<false_, _2>()
    .test<false_, _1>()
    .test<true_, _0>()
    .test<false_, _1, _1>()
    .test<false_, void>()
    ;
}

TEST_SUITE_END()

#endif
