#include "test.hpp"
#include "test/numbers.hpp"

#include "jln/mp/smp/algorithm/erase.hpp"

TEST_SUITE_BEGIN()

TEST()
{
  using namespace jln::mp;
  using namespace ut::ints;

  test_pack<erase, _0, _1>()
    .test_variadic()
    .test_binary()
    .test_unary()
    ;

  ut::same<emp::numbers<0, 2>, emp::erase_c<seq_0_1_2, 1>>();

  test_context<erase_c<2, 3>, smp::erase_c<2, 3>>()
    .test<list<_0, _1, _5>, _0, _1, _2, _3, _4, _5>()
    .test<list<_0, _1>, _0, _1, _2, _3, _4>()
    .test<list<_0, _1>, _0, _1, _2, _3>()
    .test<list<_0, _1>, _0, _1>()
    .not_invocable<_0>()
    .not_invocable<>()
    ;

  test_context<erase_c<-1, 3>, smp::erase_c<-1, 3>>()
    .not_invocable<_0, _1, _2, _3, _4, _5>()
    ;
}

TEST_SUITE_END()
