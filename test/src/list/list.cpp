#include "test.hpp"
#include "test/numbers.hpp"

#include "jln/mp/smp/list/list.hpp"

TEST_SUITE_BEGIN()

TEST()
{
  using namespace jln::mp;
  using namespace TU::ints;

  test_context<smp::listify, void>()
    .test<list<>>()
    .test<seq_0, _0>()
    .test<seq_1_2_3, _1, _2, _3>()
    ;
}

TEST_SUITE_END()
