#include "test.hpp"
#include "test/numbers.hpp"

#include "jln/mp/smp/algorithm/split_if.hpp"
#include "jln/mp/smp/number/operators.hpp"
#include "jln/mp/smp/list/push_back.hpp"

TEST_SUITE_BEGIN()

TEST()
{
  using namespace jln::mp;
  using namespace TU::ints;

  using e = list<>;
  using l_mod_3 = list<
    e,
    list<_1, _2>,
    list<_4, _5>,
    list<_7, _8>,
    e
  >;

  IS_SAME(l_mod_3, emp::split_if<seq_0_1_2_3_4_5_6_7_8_9,
    push_back<_3, mod<not_<>>>>);

  test_pack<split_if>().test_unary();
  test_pack<split_if, identity>().test_binary();

  test_context<split_if<not_<>>, smp::split_if<smp::not_<>>>()
    .test<list<>>()
    .test<list<seq_1>, _1>()
    .test<list<seq_1_1_1>, _1, _1, _1>()
    .test<list<e, e>, _0>()
    .test<list<e, e, e, e>, _0, _0, _0>()
    .test<list<list<_1>, list<_2>, list<_3>>, _1, _0, _2, _0, _3>()
    .test<list<list<_1, _2>, list<_3>>, _1, _2, _0, _3>()
    .test<list<e, list<_1, _2>, list<_3>>, _0, _1, _2, _0, _3>()
    .test<list<list<_1, _2>, list<_3>, e>, _1, _2, _0, _3, _0>()
    .not_invocable<bad_number>()
    ;
}

TEST_SUITE_END()
