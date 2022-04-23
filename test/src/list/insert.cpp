#include "test.hpp"
#include "test/numbers.hpp"

#include "jln/mp/smp/list/insert.hpp"

TEST_SUITE_BEGIN()

TEST()
{
  using namespace jln::mp;
  using namespace ut::ints;

  test_mulary_pack<insert, _1, void>();

  ut::same<emp::numbers<0, 3, 1, 2>,
    emp::insert_c<seq_0_1_2, 1, _3>>();

  test_context<insert_c<2, _6>, smp::insert_c<2, _6>>()
    .test<list<_0, _1, _6, _2, _3>, _0, _1, _2, _3>()
    .test<list<_0, _1, _6>, _0, _1>()
    .test<list<_0, _6>, _0>()
    .test<list<_6>>()
    ;

  test_context<insert_c<-2, _6>, smp::insert_c<-2, _6>>()
    .test<list<_0, _1, _6, _2, _3>, _0, _1, _2, _3>()
    .test<list<_6, _0, _1>, _0, _1>()
    .test<list<_6, _0>, _0>()
    .test<list<_6>>()
    ;

  ut::not_invocable<smp::insert<_2, void, bad_function>, _1, _1, _1, _1>();
  ut::not_invocable<smp::insert<bad_number, int>, _1, _1, _1>();
}

TEST_SUITE_END()
