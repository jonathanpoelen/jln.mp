#include "test.hpp"
#include "test/numbers.hpp"

#include "jln/mp/smp/algorithm/group_n.hpp"
#include "jln/mp/smp/list/push_front.hpp"
#include "jln/mp/smp/number/operators.hpp"
#include "jln/mp/smp/algorithm/transform.hpp"

TEST_SUITE_BEGIN()

struct cmp
{
  template<class x, class y>
  using f = jln::mp::number<(x::value & 1) == (y::value & 1)>;
};

TEST()
{
  using namespace jln::mp;
  using namespace ut::ints;

  test_pack2<group_n, _2>();
  test_pack3<group_n>();

  ut::same<list<list<_0, _2, _3>, list<_4, _5, _6>, list<_7>>,
    emp::group_n<emp::numbers<0, 2, 3, 4, 5, 6, 7>, _3>>();
  ut::same<list<list<_0, _2, _3>, list<_4, _5, _6>>,
    emp::group_n<emp::numbers<0, 2, 3, 4, 5, 6>, _3>>();

  test_context<group_n<_3>, smp::group_n<_3>>()
    .test<list<>>()
    .test<list<seq_0_1>, _0, _1>()
    .test<list<seq_0_1_2>, _0, _1, _2>()
    .test<list<seq_0_1_2, seq_3>, _0, _1, _2, _3>()
    .test<list<list<bad_number>>, bad_number>()
    ;

  test_context<group_n<_0>, smp::group_n<_0>>()
    .test<list<>>()
    .test<list<>, _0, _1>()
    ;

  ut::not_invocable<smp::group_n<_3, bad_function>>();
  ut::not_invocable<smp::group_n<_3, bad_function>, _1>();
  ut::not_invocable<smp::group_n<_3, bad_function>, _1, _1, _1>();
  ut::not_invocable<smp::group_n<_3, bad_function>, _1, _1, _1, _1, _1, _1, _1, _1>();
  ut::not_invocable<smp::group_n<bad_number, bad_function>>();
  ut::not_invocable<smp::group_n<bad_number, bad_function>, _1>();
  ut::not_invocable<smp::group_n<bad_number, bad_function>, _1, _1, _1>();
  ut::not_invocable<smp::group_n<bad_number, bad_function>, _1, _1, _1, _1, _1, _1, _1, _1>();
}

TEST_SUITE_END()

