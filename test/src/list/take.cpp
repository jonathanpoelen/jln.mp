#include "test.hpp"
#include "test/numbers.hpp"

#include "jln/mp/smp/list/take.hpp"

TEST_SUITE_BEGIN()

TEST()
{
  using namespace jln::mp;
  using namespace ut::ints;

  test_pack<take, _0>()
    .test_variadic()
    .test_binary()
    .test_unary()
  ;

  test_pack<take>()
    .test_variadic()
    .test_binary()
    .test_unary()
  ;

  ut::same<seq_0_1, emp::take_c<list<_0, _1, _2, _3>, 2>>();

  test_context<take_c<2>, smp::take_c<2>>()
    .test<seq_0_1, _0, _1>()
    .test<seq_0_1, _0, _1, _2>()
    .test<seq_0_1, _0, _1, _2, _3>()
    .not_invocable<_0>()
    ;
}

TEST_SUITE_END()
