#include "test.hpp"
#include "test/numbers.hpp"

#include "jln/mp/smp/list/empty.hpp"

TEST_SUITE_BEGIN()

TEST()
{
  using namespace jln::mp;
  using namespace ut::ints;

  ut::same<_0, emp::empty<list<int, int, int>>>();
  ut::same<_1, emp::empty<list<>>>();

  test_context<empty<>, smp::empty<>>()
    .test<_1>()
    .test<_0, int>()
    ;
}

TEST_SUITE_END()
