// SPDX-FileCopyrightText: 2023 Jonathan Poelen <jonathan.poelen@gmail.com>
// SPDX-License-Identifier: MIT
#include "test.hpp"
#include "test/numbers.hpp"

#include "jln/mp/smp/algorithm/any_of.hpp"
#include "jln/mp/smp/number/operators.hpp"
#include "jln/mp/smp/number/to_bool.hpp"

TEST_SUITE_BEGIN()

TEST()
{
  using namespace jln::mp;
  using namespace ut::ints;

  ut::same<false_, emp::any_of<seq_0_0_0, to_bool<>>>();
  ut::same<true_, emp::any_of<seq_0_1_2, to_bool<>>>();
  ut::same<true_, emp::any_of<seq_1_2_3, to_bool<>>>();

  test_unary_pack<any_of>();
  test_unary_pack<any_of, to_bool<>>();

  test_context<any_of<to_bool<>>, smp::any_of<smp::to_bool<>>>()
    .test<false_>()
    .test<false_, _0, _0>()
    .test<true_, _0, _0, _1>()
    .test<true_, _0, _0, _1, void>()
    .test<true_, _3, _1>()
    .test<true_, _3, _1, void>()
    ;

  test_context<any_of<less_than_c<3>>, smp::any_of<smp::less_than_c<3>>>()
    .test<true_, _1, _0>()
    .test<true_, _1, _0, _3>()
    .test<true_, _1, _0, void>()
    .test<false_, _3, _3>()
    .not_invocable<list<>>()
    ;

  ut::not_invocable<smp::any_of<smp::always<na>>, _1>();
  ut::not_invocable<smp::any_of<bad_function>, _1>();
  ut::not_invocable<smp::any_of<always<void>>, _1>();
  ut::not_invocable<smp::any_of<always<true_>, bad_function>>();
  ut::not_invocable<smp::any_of<always<true_>, bad_function>, _1>();
  ut::not_invocable<smp::any_of<bad_function, bad_function>>();
  ut::not_invocable<smp::any_of<bad_function, bad_function>, _1>();
}

#if JLN_MP_FEATURE_CONCEPTS
TEST()
{
  using namespace jln::mp;
  using namespace ut::ints;

  static_assert(!emp::any_of_sfinae_truthy_xs_v<identity>);
  static_assert( emp::any_of_sfinae_truthy_xs_v<identity, _1, _1, _1>);
  static_assert( emp::any_of_sfinae_truthy_xs_v<identity, _1, _0, _1>);
  static_assert(!emp::any_of_sfinae_truthy_xs_v<identity, _0, _0, _0>);
  static_assert( emp::any_of_sfinae_truthy_xs_v<identity, _1, void, _1>);
  static_assert( emp::any_of_sfinae_truthy_xs_v<identity, _0, void, _1>);
  static_assert(!emp::any_of_sfinae_truthy_xs_v<identity, _0, void, _0>);

  static_assert(!emp::any_of_sfinae_falsy_xs_v<identity>);
  static_assert(!emp::any_of_sfinae_falsy_xs_v<identity, _1, _1, _1>);
  static_assert( emp::any_of_sfinae_falsy_xs_v<identity, _1, _0, _1>);
  static_assert( emp::any_of_sfinae_falsy_xs_v<identity, _0, _0, _0>);
  static_assert(!emp::any_of_sfinae_falsy_xs_v<identity, _1, void, _1>);
  static_assert( emp::any_of_sfinae_falsy_xs_v<identity, _0, void, _1>);
  static_assert( emp::any_of_sfinae_falsy_xs_v<identity, _0, void, _0>);

  static_assert(!emp::any_of_sfinae_truthy_v<list<>, identity>);
  static_assert( emp::any_of_sfinae_truthy_v<list<_1, _1, _1>, identity>);
  static_assert( emp::any_of_sfinae_truthy_v<list<_1, _0, _1>, identity>);
  static_assert(!emp::any_of_sfinae_truthy_v<list<_0, _0, _0>, identity>);
  static_assert( emp::any_of_sfinae_truthy_v<list<_1, void, _1>, identity>);
  static_assert( emp::any_of_sfinae_truthy_v<list<_0, void, _1>, identity>);
  static_assert(!emp::any_of_sfinae_truthy_v<list<_0, void, _0>, identity>);

  static_assert(!emp::any_of_sfinae_falsy_v<list<>, identity>);
  static_assert(!emp::any_of_sfinae_falsy_v<list<_1, _1, _1>, identity>);
  static_assert( emp::any_of_sfinae_falsy_v<list<_1, _0, _1>, identity>);
  static_assert( emp::any_of_sfinae_falsy_v<list<_0, _0, _0>, identity>);
  static_assert(!emp::any_of_sfinae_falsy_v<list<_1, void, _1>, identity>);
  static_assert( emp::any_of_sfinae_falsy_v<list<_0, void, _1>, identity>);
  static_assert( emp::any_of_sfinae_falsy_v<list<_0, void, _0>, identity>);

  test_unary_pack<any_of_sfinae_falsy>();
  test_unary_pack<any_of_sfinae_truthy>();
  test_unary_pack<any_of_sfinae_falsy, to_bool<>>();
  test_unary_pack<any_of_sfinae_truthy, to_bool<>>();

  test_context<any_of_sfinae_truthy<identity>, smp::any_of_sfinae_truthy<smp::identity>>()
    .test<false_>()
    .test<true_, _1, _1>()
    .test<true_, _1, _0>()
    .test<false_, _0, _0>()
    .test<false_, _0, void>()
    .test<true_, _1, void>()
    ;

  test_context<any_of_sfinae_falsy<identity>, smp::any_of_sfinae_falsy<smp::identity>>()
    .test<false_>()
    .test<false_, _1, _1>()
    .test<true_, _1, _0>()
    .test<true_, _0, _0>()
    .test<true_, _0, void>()
    .test<false_, _1, void>()
    ;
}
#endif

TEST_SUITE_END()
