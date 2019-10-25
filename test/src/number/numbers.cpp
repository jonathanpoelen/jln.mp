#include "test.hpp"

#include "jln/mp/number/numbers.hpp"

TEST_SUITE_BEGIN()

TEST()
{
  using namespace jln::mp;

  using a = emp::numbers<>;
  using b = emp::numbers<0>;
  using c = emp::numbers<0, 1>;

  a() = list<>();
  b() = list<number<0>>();
  c() = list<number<0>, number<1>>();
}

TEST_SUITE_END()
