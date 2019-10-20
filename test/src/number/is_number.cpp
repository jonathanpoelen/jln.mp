#include "test.hpp"

#include "jln/mp/number/is_number.hpp"

namespace
{
  TEST()
  {
    using namespace jln::mp;

    class x;
    using n = number<0>;

    true_() = emp::is_number<n>();
    false_() = emp::is_number<x>();

    test_context<is_number<>, smp::is_number<>>()
      .test<true_, n>()
      .test<false_, x>()
      .not_invocable<>()
      .not_invocable<x, x>()
      .not_invocable<n, n>()
      ;
  }
}
