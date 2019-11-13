#include "test.hpp"
#include "test/numbers.hpp"

#include "jln/mp/smp/algorithm/fold_right.hpp"
#include "jln/mp/smp/list/at.hpp"
#include "jln/mp/smp/list/list.hpp"

TEST_SUITE_BEGIN()

TEST()
{
  using namespace jln::mp;
  using namespace ut::ints;

  using rlist_1_2_0 = list<_1, list<_2, _0>>;

  ut::same<rlist_1_2_0, emp::fold_right<seq_0_1_2, listify>>();

  test_pack<fold_right>().test_binary();
  test_pack<fold_right, listify>().test_unary();

  test_context<fold_right<listify>, smp::fold_right<smp::listify>>()
    .test<_0, _0>()
    .test<list<_1, _0>, _0, _1>()
    .test<list<_1, list<_2, list<_3, _0>>>, _0, _1, _2, _3>()
    .test<list<_1, list<_2, list<_3, list<_4, list<_5, _0>>>>>,
      _0, _1, _2, _3, _4, _5>()
    .not_invocable<>()
    ;

  test_context<
    fold_right<at1<identity>>,
    smp::fold_right<smp::at1<smp::identity>>
  >()
    .test<_0, _0>()
    .test<_0, _0, _1>()
    .test<_0, _0, _1, _2, _3>()
    .not_invocable<>()
    .not_invocable<na>()
    .not_invocable<_0, na>()
    .not_invocable<_0, _1, na>()
    ;
}

TEST_SUITE_END()