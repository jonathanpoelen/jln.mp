#include "test.hpp"

#include "jln/mp/smp/number/to_bool.hpp"

#include <type_traits>


TEST_SUITE_BEGIN()

TEST()
{
  using namespace jln::mp;

  using a = std::integral_constant<int, 0>;
  using b = std::integral_constant<int, 1>;
  using c = std::integral_constant<unsigned long long, ~0ull>;

  ut::same<false_, emp::to_bool<a>>();
  ut::same<true_, emp::to_bool<b>>();

  test_pack<to_bool>().test_unary();
  test_pack3<to_bool>();

  test_context<to_bool<>, smp::to_bool<>>()
    .test<false_, number<0>>()
    .test<true_, number<1>>()
    .test<false_, a>()
    .test<true_, b>()
    .test<true_, c>()
    .test<true_, number<3>>()
    .not_invocable<>()
    .not_invocable<void>()
    ;

  ut::not_invocable<smp::to_bool<bad_function>>();
  ut::not_invocable<smp::to_bool<bad_function>, true_>();
}

TEST_SUITE_END()
