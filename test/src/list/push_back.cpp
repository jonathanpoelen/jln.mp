#include "test.hpp"
#include "test/numbers.hpp"

#include "jln/mp/smp/list/push_back.hpp"

TEST_SUITE_BEGIN()

TEST()
{
  using namespace jln::mp;
  using namespace ut::ints;

  test_pack<push_back, _2>()
    .test_binary()
    .test_unary()
  ;

  test_context<push_back<_2>, smp::push_back<_2>>()
    .test<seq_2>()
    .test<seq_1_2, _1>()
    .test<seq_0_1_2, _0, _1>()
    ;
}

TEST_SUITE_END()
