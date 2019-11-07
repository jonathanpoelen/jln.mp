#include "test.hpp"
#include "test/numbers.hpp"

#include "jln/mp/smp/list/pop_front.hpp"

TEST_SUITE_BEGIN()

TEST()
{
  using namespace jln::mp;
  using namespace ut::ints;

  test_pack<pop_front>()
    .test_unary()
  ;

  test_context<pop_front<>, smp::pop_front<>>()
    .test<list<>, _0>()
    .test<seq_1_2, _0, _1, _2>()
    .not_invocable<>()
    ;
}

TEST_SUITE_END()
