#include "test.hpp"
#include "test/numbers.hpp"

#include "jln/mp/smp/algorithm/reverse.hpp"

TEST_SUITE_BEGIN()

TEST()
{
  using namespace jln::mp;
  using namespace ut::ints;

  ut::same<seq_2_1_0, emp::reverse<seq_0_1_2>>();

  test_mulary_pack<reverse>();

  test_context<reverse<>, smp::reverse<>>()
    .test<list<>>()
    .test<seq_0_0_0, _0, _0, _0>()
    .test<emp::numbers<6, 5, 4, 3, 2, 1, 0>,
      _0, _1, _2, _3, _4, _5, _6>()
    .test<emp::numbers<7, 6, 5, 4, 3, 2, 1, 0>,
      _0, _1, _2, _3, _4, _5, _6, _7>()
    .test<emp::numbers<8, 7, 6, 5, 4, 3, 2, 1, 0>,
      _0, _1, _2, _3, _4, _5, _6, _7, _8>()
    .test<emp::numbers<20, 19, 18, 17, 16, 15, 14,
      13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0>,
      _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10,
      _11, _12, _13, _14, _15, _16, _17, _18, _19, _20>()
    ;

  ut::not_invocable<smp::reverse<bad_function>, _1, _1, _1>();
}

TEST_SUITE_END()
