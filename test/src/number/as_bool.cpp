#include "test.hpp"

#include "jln/mp/smp/number/as_bool.hpp"

#include <type_traits>


TEST_SUITE_BEGIN()

TEST()
{
  using namespace jln::mp;

  using a = std::integral_constant<int, 0>;
  using b = std::integral_constant<int, 1>;
  using c = std::integral_constant<unsigned long long, ~0ull>;

  ut::same<false_, emp::as_bool<a>>();
  ut::same<true_, emp::as_bool<b>>();

  test_pack<as_bool>()
    .test_unary()
  ;

  test_context<as_bool<>, smp::as_bool<>>()
    .test<false_, number<0>>()
    .test<true_, number<1>>()
    .test<false_, a>()
    .test<true_, b>()
    .not_invocable<>()
    .not_invocable<void>()
    .not_invocable<c>() // narrowing conversion
    .not_invocable<number<3>>() // narrowing conversion
    ;
}

TEST_SUITE_END()
