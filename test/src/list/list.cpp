#include "test.hpp"
#include "test/numbers.hpp"

#include "jln/mp/smp/list/listify.hpp"

TEST_SUITE_BEGIN()

TEST()
{
  using namespace jln::mp;
  using namespace ut::ints;

  test_context<listify, smp::listify>()
    .test<list<>>()
    .test<seq_0, _0>()
    .test<seq_1_2_3, _1, _2, _3>()
    ;
}

TEST_SUITE_END()
