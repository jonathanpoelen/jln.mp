#include "test.hpp"
#include "test/numbers.hpp"

#include "jln/mp/smp/algorithm/take_while.hpp"
#include "jln/mp/smp/utility/same_as.hpp"

TEST_SUITE_BEGIN()

TEST()
{
  using namespace jln::mp;
  using namespace ut::ints;

  ut::same<seq_0_1, emp::take_while<list<_0, _1, _2, _3>, same_as<_2>>>();

  test_context<
    take_while<same_as<_2>>,
    smp::take_while<smp::same_as<_2>>,
    0
  >()
    .test<list<>, _0, _1>()
    .test<seq_2, _0, _1, _2>()
    .test<seq_2_3, _0, _1, _2, _3>()
    ;
}

TEST_SUITE_END()
