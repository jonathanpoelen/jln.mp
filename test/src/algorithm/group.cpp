#include "test.hpp"
#include "test/numbers.hpp"

#include "jln/mp/smp/algorithm/group.hpp"
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

  test_pack2<group_if, same_as<int>>();
  test_pack2<group_if, void>();

  ut::same<list<list<_0>, list<_1, _1>, list<_2, _2, _2>>,
    emp::group<emp::numbers<0, 1, 1, 2, 2, 2>>>();
  ut::same<list<list<_0, _0>, list<_1, _1>, list<_2, _2, _2>>,
    emp::group<emp::numbers<0, 0, 1, 1, 2, 2, 2>>>();

  using odd = push_front<number<1>, bit_and<>>;
  using cmp = transform<odd, equal<>>;
  using scmp = detail::sfinae<cmp>;

  test_context<group_if<cmp>, smp::group_if<scmp>>()
    .test<list<>>()
    .test<list<seq_0_0_0>, _0, _0, _0>()
    .test<list<list<_0, _0>, list<_1, _3>, seq_2>,
      _0, _0, _1, _3, _2>()
    .test<list<list<bad_number>>, bad_number>()
    .not_invocable<bad_number, bad_number>()
    ;

  test_context<group_if<always<na>>, smp::group_if<smp::always<na>>>()
    .test<list<>>()
    .test<list<seq_0>, _0>()
    .not_invocable<_0, _0>()
    ;

  test_context<group<>, smp::group<>, 0>()
    .test<list<>>()
    .test<list<seq_0_0_0, list<_1, _1>, seq_0, seq_2>,
      _0, _0, _0, _1, _1, _0, _2>()
    .test<list<seq_1_1_1>, _1, _1, _1>()
    .test<list<seq_0, seq_1, seq_3>, _0, _1, _3>()
    ;

  ut::not_invocable<smp::group<bad_function>>();
  ut::not_invocable<smp::group<bad_function>, _1, _1, _1, _2>();
  ut::not_invocable<smp::group_if<cmp, bad_function>>();
  ut::not_invocable<smp::group_if<cmp, bad_function>, _1, _1, _1>();
  ut::not_invocable<smp::group_if<bad_function, bad_function>>();
  ut::not_invocable<smp::group_if<bad_function, bad_function>, _1, _1, _1>();
}

TEST_SUITE_END()

