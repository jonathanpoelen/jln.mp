#include "test.hpp"
#include "test/numbers.hpp"

#include "jln/mp/smp/algorithm/split_by.hpp"
#include "jln/mp/smp/algorithm/index.hpp"
#include "jln/mp/smp/utility/always.hpp"
#include "jln/mp/smp/list/size.hpp"

TEST_SUITE_BEGIN()

TEST()
{
  using namespace jln::mp;
  using namespace ut::ints;

  test_pack3<split_by, index_of<_3>>();

  test_context<split_by<identity>, smp::split_by<smp::identity>>()
    .test<list<list<>, seq_0>, _0>()
    .test<list<seq_1, list<>>, _1>()
    .not_invocable<>()
    .not_invocable<void>()
    .not_invocable<_0, _1>()
    .not_invocable<_2>()
    ;

  test_context<
    split_by<index_if<is<_3>>>,
    smp::split_by<smp::index_if<smp::is<_3>>>
  >()
    .test<list<list<>, list<>>>()
    .test<list<seq_1_2, list<>>, _1, _2>()
    .test<list<seq_1_2, list<_3>>, _1, _2, _3>()
    ;

  ut::not_invocable<smp::split_by<smp::always<void>>, _1>();
  ut::not_invocable<smp::split_by<bad_function>, _1, _1, _1>();
  ut::not_invocable<smp::split_by2<smp::identity, bad_function>, _1>();
}

TEST_SUITE_END()

