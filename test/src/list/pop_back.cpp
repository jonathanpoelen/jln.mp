#include "test.hpp"
#include "test/numbers.hpp"

#include "jln/mp/smp/list/pop_back.hpp"

TEST_SUITE_BEGIN()

TEST()
{
  using namespace jln::mp;
  using namespace TU::ints;

  test_pack<pop_back>()
    .test_unary()
  ;

  test_context<pop_back<>, smp::pop_back<>>()
    .test<list<>, _1>()
    .test<seq_1, _1, _2>()
    .test<seq_1_2, _1, _2, _3>()
    .not_invocable<>()
    ;
}

TEST_SUITE_END()
