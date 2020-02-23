#include "test.hpp"
#include "test/numbers.hpp"

#include "jln/mp/smp/list/is_empty.hpp"

TEST_SUITE_BEGIN()

TEST()
{
  using namespace jln::mp;
  using namespace ut::ints;

  ut::same<_0, emp::is_empty<list<int, int, int>>>();
  ut::same<_1, emp::is_empty<list<>>>();

  test_context<is_empty<>, smp::is_empty<>>()
    .test<_1>()
    .test<_0, int>()
    ;

  ut::not_invocable<smp::is_empty<bad_function>>();
  ut::not_invocable<smp::is_empty<bad_function>, _1>();
}

TEST_SUITE_END()
