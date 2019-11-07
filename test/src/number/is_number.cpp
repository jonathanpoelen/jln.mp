#include "test.hpp"

#include "jln/mp/smp/number/is_number.hpp"

TEST_SUITE_BEGIN()

TEST()
{
  using namespace jln::mp;

  class x;
  using n = number<0>;

  ut::same<false_, emp::is_number<x>>();
  ut::same<true_, emp::is_number<n>>();

  test_pack<is_number>()
    .test_unary()
  ;

  test_context<is_number<>, smp::is_number<>>()
    .test<true_, n>()
    .test<false_, x>()
    .not_invocable<>()
    .not_invocable<x, x>()
    .not_invocable<n, n>()
    ;

  test_context<is_number<is_number<>>, smp::is_number<smp::is_number<>>>()
    .test<true_, n>()
    .test<true_, x>()
    .not_invocable<>()
    .not_invocable<x, x>()
    .not_invocable<n, n>()
    ;
}

TEST_SUITE_END()
