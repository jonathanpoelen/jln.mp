#include "test.hpp"
#include "test/numbers.hpp"

#include "jln/mp/smp/list/push_front.hpp"

TEST_SUITE_BEGIN()

TEST()
{
  using namespace jln::mp;
  using namespace TU::ints;

  test_pack<push_front, _1>()
    .test_binary()
    .test_unary()
  ;

  test_context<push_front<_1>, smp::push_front<_1>>()
    .test<seq_1>()
    .test<seq_1_2, _2>()
    .test<seq_1_2_3, _2, _3>()
    ;
}

TEST_SUITE_END()
