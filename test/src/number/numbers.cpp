#include "test/test_case.hpp"
#include "test/is_same.hpp"

#include "jln/mp/smp/number/numbers.hpp"

TEST_SUITE_BEGIN()

TEST()
{
  using namespace jln::mp;

  using a = emp::numbers<>;
  using b = emp::numbers<0>;
  using c = emp::numbers<0, 1>;

  ut::same<a, list<>>();
  ut::same<b, list<number<0>>>();
  ut::same<c, list<number<0>, number<1>>>();
}

TEST_SUITE_END()
