#include "test.hpp"
#include "test/numbers.hpp"

#include "jln/mp/smp/algorithm/insert.hpp"

TEST_SUITE_BEGIN()

TEST()
{
  using namespace jln::mp;
  using namespace ut::ints;

  test_pack<insert, _1>()
    .test_variadic_not_na()
    .test_binary_not_na()
    .test_unary_not_na()
    ;

  ut::same<emp::numbers<0, 3, 1, 2>, emp::insert_c<
    seq_0_1_2, 1, list<_3>>>();

  test_context<
    insert_c<2, emp::numbers<6, 7>>,
    smp::insert_c<2, emp::numbers<6, 7>>,
    0
  >()
    .test<list<_0, _1, _6, _7, _2, _3>, _0, _1, _2, _3>()
    .test<list<_0, _1, _6, _7>, _0, _1>()
    .not_invocable<_0>()
    .not_invocable<>()
    ;
}

TEST_SUITE_END()
