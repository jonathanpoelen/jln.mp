#include "test.hpp"
#include "test/numbers.hpp"

#include "jln/mp/smp/algorithm/anticirculant_matrix.hpp"
#include "jln/mp/smp/number/operators.hpp"

TEST_SUITE_BEGIN()

TEST()
{
  using namespace jln::mp;
  using namespace ut::ints;

  test_pack2<anticirculant_matrix>();
  test_pack3<anticirculant_matrix, listify>();

  test_context<anticirculant_matrix<>, smp::anticirculant_matrix<>>()
    .test<list<>>()
    .test<list<seq_0>, _0>()
    .test<list<seq_0_1, seq_1_0>, _0, _1>()
    .test<list<emp::numbers<0, 1, 2>,
               emp::numbers<1, 2, 0>,
               emp::numbers<2, 0, 1>>, _0, _1, _2>()
    .test<list<emp::numbers<0, 1, 2, 3>,
               emp::numbers<1, 2, 3, 0>,
               emp::numbers<2, 3, 0, 1>,
               emp::numbers<3, 0, 1, 2>>, _0, _1, _2, _3>()
    .test<list<emp::numbers<1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18>,
               emp::numbers<2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 1>,
               emp::numbers<3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 1, 2>,
               emp::numbers<4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 1, 2, 3>,
               emp::numbers<5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 1, 2, 3, 4>,
               emp::numbers<6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 1, 2, 3, 4, 5>,
               emp::numbers<7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 1, 2, 3, 4, 5, 6>,
               emp::numbers<8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 1, 2, 3, 4, 5, 6, 7>,
               emp::numbers<9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 1, 2, 3, 4, 5, 6, 7, 8>,
               emp::numbers<10, 11, 12, 13, 14, 15, 16, 17, 18, 1, 2, 3, 4, 5, 6, 7, 8, 9>,
               emp::numbers<11, 12, 13, 14, 15, 16, 17, 18, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10>,
               emp::numbers<12, 13, 14, 15, 16, 17, 18, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11>,
               emp::numbers<13, 14, 15, 16, 17, 18, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12>,
               emp::numbers<14, 15, 16, 17, 18, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13>,
               emp::numbers<15, 16, 17, 18, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14>,
               emp::numbers<16, 17, 18, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15>,
               emp::numbers<17, 18, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16>,
               emp::numbers<18, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17>
              >, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10,
                 _11, _12, _13, _14, _15, _16, _17, _18>()
    ;

  test_context<anticirculant_matrix_with<add<>>, smp::anticirculant_matrix_with<smp::add<>>>()
    .test<list<>>()
    .test<list<_0>, _0>()
    .test<list<_1, _1>, _0, _1>()
    .test<list<_3, _3, _3>, _0, _1, _2>()
    .test<list<_6, _6, _6, _6>, _0, _1, _2, _3>()
    .not_invocable<na>()
    ;

  ut::not_invocable<smp::anticirculant_matrix<bad_function>, _1>();
}

TEST_SUITE_END()
