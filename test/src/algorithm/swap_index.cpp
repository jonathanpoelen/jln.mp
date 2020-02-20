#include "test.hpp"
#include "test/numbers.hpp"

#include "jln/mp/smp/algorithm/swap_index.hpp"

TEST_SUITE_BEGIN()

TEST()
{
  using namespace jln::mp;
  using namespace ut::ints;

  ut::same<list<_3, _1, _2, _0>, emp::swap_index_c<seq_0_1_2_3, 0, 3>>();

  test_pack2<swap_index, _1, _2>();
  test_pack3<swap_index, void, void>();

  ut::same<swap_index_c<1, 2>, swap_index_c<2, 1>>();
  ut::same<smp::swap_index_c<1, 2>, smp::swap_index_c<2, 1>>();

  test_context<swap_index_c<1, 2>, smp::swap_index_c<1, 2>>()
    .test<list<_0, _2, _1>, _0, _1, _2>()
    .test<list<_0, _2, _1, _3>, _0, _1, _2, _3>()
    .not_invocable<>()
    .not_invocable<_1>()
    .not_invocable<_1, _2>()
    ;

  test_context<swap_index_c<1, 1>, smp::swap_index_c<1, 1>>()
    .test<list<_0, _1>, _0, _1>()
    .test<list<_0, _1, _2>, _0, _1, _2>()
    .not_invocable<>()
    .not_invocable<_1>()
    ;
}

TEST_SUITE_END()
