#include "test.hpp"
#include "test/numbers.hpp"

#include "jln/mp/smp/algorithm/disjunction.hpp"
#include "jln/mp/smp/utility/always.hpp"
#include "jln/mp/smp/list/listify.hpp"

TEST_SUITE_BEGIN()

TEST()
{
  using namespace jln::mp;
  using namespace ut::ints;

  ut::same<_1, emp::disjunction<seq_1_1>>();
  ut::same<_1, emp::disjunction<seq_1_0>>();
  ut::same<_0, emp::disjunction<seq_0_0>>();

  test_unary_pack<disjunction>();

  test_context<disjunction<>, smp::disjunction<>>()
    .test<_0>()
    .test<_1, _1>()
    .test<_1, _1, list<>>()
    .test<_1, _1, _1>()
    .test<_1, _1, _1, _1>()
    .test<_1, _0, _1, _1, _1, _1>()
    .test<_1, _1, _1, _1, _1, _0>()
    .test<_0, _0, _0, _0>()
    .test<_2, _2>()
    .not_invocable<list<>>()
    .not_invocable<_0, list<>>()
    ;

  test_context<disjunction<listify>, smp::disjunction<smp::listify>>()
    .test<seq_0>()
    .test<seq_1, _1>()
    .test<seq_1, _1, list<>>()
    .test<seq_1, _1, _1>()
    .test<seq_1, _1, _1, _1>()
    .test<seq_1, _0, _1, _1, _1, _1>()
    .test<seq_1, _1, _1, _1, _1, _0>()
    .test<seq_0, _0, _0, _0>()
    .test<seq_2, _2>()
    .not_invocable<list<>>()
    .not_invocable<_0, list<>>()
    ;

  ut::not_invocable<smp::disjunction<smp::always<na>>>();
  ut::not_invocable<smp::disjunction<bad_function>>();
  ut::not_invocable<smp::disjunction_with<smp::always<na>>, _1>();
  ut::not_invocable<smp::disjunction_with<bad_function>, _1>();
}

TEST_SUITE_END()
