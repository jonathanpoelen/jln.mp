#include "test.hpp"
#include "test/numbers.hpp"

#include "jln/mp/smp/list/is_not_empty.hpp"

TEST_SUITE_BEGIN()

TEST()
{
  using namespace jln::mp;
  using namespace ut::ints;

  test_unary_pack<is_not_empty>();

  ut::same<_1, emp::is_not_empty<list<int, int, int>>>();
  ut::same<_0, emp::is_not_empty<list<>>>();

  test_context<is_not_empty<>, smp::is_not_empty<>>()
    .test<_0>()
    .test<_1, int>()
    ;

  // optimized alias :)
  ut::same<smp::is_not_empty<>, contract<size<is<number<0>, not_<>>>>>();

  ut::not_invocable<smp::is_not_empty<bad_function>>();
  ut::not_invocable<smp::is_not_empty<bad_function>, _1>();
}

TEST_SUITE_END()
