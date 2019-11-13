#include "test.hpp"

#include "jln/mp/smp/number/as_bool.hpp"

#include <type_traits>


TEST_SUITE_BEGIN()

TEST()
{
  using namespace jln::mp;

  using a = number<0>;
  using b = std::integral_constant<int, 1>;
  using c = std::integral_constant<unsigned long long, ~0ull>;

  ut::same<a, emp::as_bool<a>>();
  ut::same<number<1>, emp::as_bool<b>>();

  test_pack<as_bool>()
    .test_unary()
  ;

  test_context<as_bool<>, smp::as_bool<>>()
    .test<a, a>()
    .test<number<1>, b>()
    .test<number<1>, number<3>>()
    .not_invocable<void>()
    .not_invocable<c>() // narrowing conversion
    ;
}

TEST_SUITE_END()