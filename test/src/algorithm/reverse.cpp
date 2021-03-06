#include "test.hpp"
#include "test/numbers.hpp"

#include "jln/mp/smp/algorithm/reverse.hpp"

TEST_SUITE_BEGIN()

TEST()
{
  using namespace jln::mp;
  using namespace ut::ints;

  ut::same<seq_2_1_0, emp::reverse<seq_0_1_2>>();

  test_pack2<reverse>();

  test_context<reverse<>, smp::reverse<>>()
    .test<list<>>()
    .test<seq_0_0_0, _0, _0, _0>()
    .test<emp::numbers<6, 5, 4, 3, 2, 1, 0>,
      _0, _1, _2, _3, _4, _5, _6>()
    .test<emp::numbers<7, 6, 5, 4, 3, 2, 1, 0>,
      _0, _1, _2, _3, _4, _5, _6, _7>()
    .test<emp::numbers<8, 7, 6, 5, 4, 3, 2, 1, 0>,
      _0, _1, _2, _3, _4, _5, _6, _7, _8>()
    ;

  ut::not_invocable<smp::reverse<bad_function>, _1, _1, _1>();
}

TEST_SUITE_END()
