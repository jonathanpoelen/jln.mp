#include "test.hpp"
#include "test/numbers.hpp"

#include "jln/mp/smp/algorithm/conjunction.hpp"
#include "jln/mp/smp/utility/always.hpp"
#include "jln/mp/smp/list/listify.hpp"

TEST_SUITE_BEGIN()

TEST()
{
  using namespace jln::mp;
  using namespace ut::ints;

  ut::same<_1, emp::conjunction<seq_1_1>>();
  ut::same<_0, emp::conjunction<seq_1_0>>();

  test_unary_pack<conjunction>();

  test_context<conjunction<>, smp::conjunction<>>()
    .test<_1>()
    .test<_1, _1>()
    .test<_1, _1, _1>()
    .test<_0, _0, _1, _1, _1, _1>()
    .test<_0, _1, _0, list<>, _1>()
    .test<_2, _1, _2>()
    .not_invocable<list<>>()
    .not_invocable<_1, _1, list<>>()
    ;

  test_context<conjunction<listify>, smp::conjunction<smp::listify>>()
    .test<seq_1>()
    .test<seq_1, _1>()
    .test<seq_1, _1, _1>()
    .test<seq_0, _0, _1, _1, _1, _1>()
    .test<seq_0, _1, _0, list<>, _1>()
    .test<seq_2, _1, _2>()
    .not_invocable<list<>>()
    .not_invocable<_1, _1, list<>>()
    ;

  ut::not_invocable<smp::conjunction<smp::always<na>>>();
  ut::not_invocable<smp::conjunction<bad_function>>();
  ut::not_invocable<smp::conjunction_with<smp::always<na>>, _1>();
  ut::not_invocable<smp::conjunction_with<bad_function>, _1>();
}

TEST_SUITE_END()
