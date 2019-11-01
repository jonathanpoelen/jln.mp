#include "test.hpp"

#include "jln/mp/smp/number/numbers.hpp"

TEST_SUITE_BEGIN()

TEST()
{
  using namespace jln::mp;

  using a = emp::numbers<>;
  using b = emp::numbers<0>;
  using c = emp::numbers<0, 1>;

  IS_SAME(a, list<>);
  IS_SAME(b, list<number<0>>);
  IS_SAME(c, list<number<0>, number<1>>);
}

TEST_SUITE_END()
