#include "test.hpp"

#include "jln/mp/smp/number/as_number.hpp"

#include <type_traits>


TEST_SUITE_BEGIN()

TEST()
{
  using namespace jln::mp;

  using a = number<0>;
  using b = std::integral_constant<int, 1>;
  using c = std::integral_constant<unsigned long long, ~0ull>;

  ut::same<a, emp::as_number<a>>();
  ut::same<number<1>, emp::as_number<b>>();

  test_unary_pack<as_number>();

  test_context<as_number<>, smp::as_number<>>()
    .test<a, a>()
    .test<number<1>, b>()
    .not_invocable<void>()
    .not_invocable<c>() // narrowing conversion
    ;

  ut::not_invocable<smp::as_number<bad_function>>();
  ut::not_invocable<smp::as_number<bad_function>, true_>();
}

TEST_SUITE_END()
