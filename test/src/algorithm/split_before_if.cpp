#include "test.hpp"
#include "test/numbers.hpp"

#include "jln/mp/smp/algorithm/split_before_if.hpp"
#include "jln/mp/smp/number/operators.hpp"
#include "jln/mp/smp/list/push_back.hpp"

TEST_SUITE_BEGIN()

TEST()
{
  using namespace jln::mp;
  using namespace ut::ints;

  using e = list<>;
  using l_mod_3 = list<
    e,
    list<_0, _1, _2>,
    list<_3, _4, _5>,
    list<_6, _7, _8>,
    list<_9>
  >;

  ut::same<l_mod_3, emp::split_before_if<seq_0_1_2_3_4_5_6_7_8_9,
    push_back<_3, mod<not_<>>>>>();

  test_pack<split_before_if>().test_unary();
  test_pack<split_before_if, identity>().test_binary();

  test_context<split_before_if<not_<>>, smp::split_before_if<smp::not_<>>>()
    .test<e>()
    .test<list<seq_1>, _1>()
    .test<list<seq_1_1_1>, _1, _1, _1>()
    .test<list<e, seq_0>, _0>()
    .test<list<e, seq_0, seq_0, seq_0>, _0, _0, _0>()
    .test<list<seq_1, list<_0, _2>, list<_0, _3>>, _1, _0, _2, _0, _3>()
    .test<list<seq_1_2, list<_0, _3>>, _1, _2, _0, _3>()
    .test<list<e, seq_0_1_2, list<_0, _3>>, _0, _1, _2, _0, _3>()
    .test<list<seq_1_2, list<_0, _3>, seq_0>, _1, _2, _0, _3, _0>()
    .not_invocable<bad_number>()
    ;
}

TEST_SUITE_END()
