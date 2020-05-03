#include "test.hpp"
#include "test/numbers.hpp"

#include "jln/mp/smp/list/is_size_of.hpp"

TEST_SUITE_BEGIN()

TEST()
{
  using namespace jln::mp;
  using namespace ut::ints;

  ut::same<_0, emp::is_size_of_c<seq_0_1_2, 2>>();
  ut::same<_1, emp::is_size_of_c<seq_0_1_2, 3>>();

  test_context<is_size_of<_1>, smp::is_size_of<_1>>()
    .test<_0>()
    .test<_1, int>()
    .test<_0, int, void>()
    ;

  ut::not_invocable<smp::is_size_of<_1, bad_function>>();
  ut::not_invocable<smp::is_size_of<_1, bad_function>, _1>();
  ut::not_invocable<smp::is_size_of<bad_number>, _1>();
  ut::not_invocable<smp::is_size_of<bad_number, bad_function>, _1>();
}

TEST_SUITE_END()
