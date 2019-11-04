#include "test.hpp"
#include "test/numbers.hpp"

#include "jln/mp/smp/algorithm/indices.hpp"

TEST_SUITE_BEGIN()

TEST()
{
  using namespace jln::mp;
  using namespace TU::ints;

  IS_SAME(seq_0_1_2, emp::indices<seq_0_1_2>);
  IS_SAME(seq_0_1_2, emp::indices<seq_1_2_3>);

  test_pack<indices>()
    .test_binary()
    .test_unary()
  ;

  IS_INVOCABLE(smp::indices<>);
  IS_INVOCABLE(smp::indices<>, _1);

  // TODO smp::indices
  test_context<indices<>, void>()
    .test<list<>>()
    .test<seq_0_1_2, _0, _0, _0>()
    ;
}

TEST_SUITE_END()
