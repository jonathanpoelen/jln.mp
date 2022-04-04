#include "test/is_invocable.hpp"
#include "test/is_same.hpp"
#include "test/test_case.hpp"
#include "test/numbers.hpp"

#include "jln/mp/smp/functional/random.hpp"

#ifdef __cpp_generic_lambdas
#if __cpp_generic_lambdas >= 201707L

TEST_SUITE_BEGIN()

TEST()
{
  using namespace jln::mp;
  using namespace ut::ints;

  ut::not_same<emp::random<>, emp::random<>>();

  using rd1 = random<>;
  #ifdef __clang__
  ut::not_same<rd1::f<int>, rd1::f<int>>();
  #else
  ut::same<rd1::f<int>, rd1::f<int>>();
  #endif
  ut::not_same<rd1::f<void>, rd1::f<int>>();

  ut::not_same<random<>::f<int>, random<>::f<int>>();
  ut::not_same<random<>::f<void>, random<>::f<int>>();
}

TEST_SUITE_END()

#endif
#endif
