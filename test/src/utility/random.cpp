// SPDX-FileCopyrightText: 2023 Jonathan Poelen <jonathan.poelen@gmail.com>
// SPDX-License-Identifier: MIT
#include "test/is_invocable.hpp"
#include "test/is_same.hpp"
#include "test/test_case.hpp"
#include "test/numbers.hpp"

#include "jln/mp/smp/utility/random.hpp"

#ifdef __cpp_generic_lambdas
#if __cpp_generic_lambdas >= 201707L

TEST_SUITE_BEGIN()

TEST()
{
  using namespace jln::mp;
  using namespace ut::ints;

  (void)random<identity>();
  (void)random<listify>();

  static_assert(emp::random_v<> != emp::random_v<>);
  ut::not_same<emp::random<>, emp::random<>>();

  using rd1 = random<>;
  ut::same<rd1::f<int>, rd1::f<int>>();
  ut::not_same<rd1::f<void>, rd1::f<int>>();

  ut::not_same<random<>::f<int>, random<>::f<int>>();
  ut::not_same<random<>::f<void>, random<>::f<int>>();

  class tag1;
  class tag2;

  static_assert(emp::random_v<tag1> == emp::random_v<tag2>);
  static_assert(emp::random_v<tag1> == emp::random_v<tag2>);
  static_assert(emp::random_v<tag1> != emp::random_v<tag1>);
  static_assert(emp::random_v<tag2> != emp::random_v<tag2>);
  static_assert(emp::random_v<tag1> == emp::random_v<tag2>);
  ut::same<emp::random<tag1>, emp::random<tag2>>();

  using rdt1 = random_for<tag1>;
  using rdt2 = random_for<tag2>;

  ut::same<rdt1::f<int>, rdt2::f<int>>();
  ut::same<rdt1::f<void>, rdt2::f<void>>();
  ut::same<rdt1::f<char>, rdt1::f<char>>();
  ut::same<rdt2::f<char>, rdt2::f<char>>();
  ut::same<rdt1::f<int>, rdt1::f<int>>();
  ut::same<rdt2::f<int>, rdt2::f<int>>();
  ut::same<rdt1::f<float>, rdt2::f<float>>();
  ut::not_same<rdt1::f<void>, rdt1::f<int>>();
  ut::not_same<rdt2::f<void>, rdt2::f<int>>();
}

TEST_SUITE_END()

#endif
#endif
