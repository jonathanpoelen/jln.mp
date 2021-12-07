#include "test.hpp"
#include "test/numbers.hpp"

#include "jln/mp/smp/list/insert.hpp"

TEST_SUITE_BEGIN()

TEST()
{
  using namespace jln::mp;
  using namespace ut::ints;

  test_pack2<insert, _1, void>();

  ut::same<emp::numbers<0, 3, 1, 2>,
    emp::insert_c<seq_0_1_2, 1, _3>>();

  test_context<insert_c<2, _6>, smp::insert_c<2, _6>, 0>()
    .test<list<_0, _1, _6, _2, _3>, _0, _1, _2, _3>()
    .test<list<_0, _1, _6>, _0, _1>()
    .not_invocable<_0>()
    .not_invocable<>()
    ;

  test_context<insert_c<2, seq_0_1>, smp::insert_c<2, seq_0_1>, 0>()
    .test<list<_0, _1, seq_0_1, _2, _3>, _0, _1, _2, _3>()
    .test<list<_0, _1, seq_0_1>, _0, _1>()
    .not_invocable<_0>()
    .not_invocable<>()
    ;

  ut::not_invocable<smp::insert<smp::always<na>, _2>, _1, _1, _1, _1>();
  ut::not_invocable<smp::insert<_2, void, bad_function>, _1, _1, _1, _1>();
  ut::not_invocable<smp::insert<bad_number, int>, _1, _1, _1>();
}

TEST_SUITE_END()
