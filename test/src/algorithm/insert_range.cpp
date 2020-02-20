#include "test.hpp"
#include "test/numbers.hpp"

#include "jln/mp/smp/algorithm/insert_range.hpp"

TEST_SUITE_BEGIN()

TEST()
{
  using namespace jln::mp;
  using namespace ut::ints;

  test_pack2<insert_range, _1, list<_2, _3>>();
  test_pack2<insert_range, void, list<_2, _3>>();
  test_pack2<insert_range, void, void>();

  ut::same<emp::numbers<0, 3, 1, 2>,
    emp::insert_range_c<seq_0_1_2, 1, list<_3>>>();

  test_context<insert_range_c<2, list<_6, _7>>, smp::insert_range_c<2, list<_6, _7>>>()
    .test<list<_0, _1, _6, _7, _2, _3>, _0, _1, _2, _3>()
    .test<list<_0, _1, _6, _7>, _0, _1>()
    .not_invocable<_0>()
    .not_invocable<>()
    ;
}

TEST_SUITE_END()
