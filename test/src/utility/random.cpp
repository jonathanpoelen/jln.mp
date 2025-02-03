// SPDX-FileCopyrightText: 2023 Jonathan Poelen <jonathan.poelen@gmail.com>
// SPDX-License-Identifier: MIT
#include "test/is_invocable.hpp"
#include "test/is_same.hpp"
#include "test/test_case.hpp"
#include "test/numbers.hpp"

#include "jln/mp/smp/utility/random.hpp"

#ifdef __cpp_generic_lambdas
// nvcc bug: types may not be defined in template arguments for emp::random_v<> ???
#if __cpp_generic_lambdas >= 201707L && !JLN_MP_WORKAROUND(JLN_MP_CUDA, <= 1208)

TEST_SUITE_BEGIN()

TEST()
{
  using namespace jln::mp;
  using namespace ut::ints;

  (void)random<identity>();
  (void)random<listify>();

  constexpr auto r1 = emp::random_v<>;
  constexpr auto r2 = emp::random_v<>;
  using R1 = emp::random<>;
  using R2 = emp::random<>;

  static_assert(r1 != r2);
  ut::not_same<R1, R2>();

  using rd1 = random<>;
  ut::same<rd1::f<int>, rd1::f<int>>();
  ut::not_same<rd1::f<void>, rd1::f<int>>();

  ut::not_same<random<>::f<int>, random<>::f<int>>();
  ut::not_same<random<>::f<void>, random<>::f<int>>();

  class tag1;
  class tag2;

  constexpr auto r1t1 = emp::random_v<tag1>;
  constexpr auto r1t2 = emp::random_v<tag2>;
  constexpr auto r2t1 = emp::random_v<tag1>;
  constexpr auto r2t2 = emp::random_v<tag2>;
  using R1T1 = emp::random<tag1>;
  using R1T2 = emp::random<tag2>;

  static_assert(r1t1 == r1t2);
  static_assert(r2t1 == r2t2);
  static_assert(r1t1 != r2t1);
  static_assert(r1t2 != r2t2);
  ut::same<R1T1, R1T2>();

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
