#include "test.hpp"
#include "test/numbers.hpp"

#include "jln/mp/smp/algorithm/unique_justseen.hpp"
#include "jln/mp/smp/list/push_front.hpp"
#include "jln/mp/smp/number/operators.hpp"
#include "jln/mp/smp/algorithm/transform.hpp"
#include "jln/mp/smp/utility/unpack.hpp"

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

  test_binary_pack<unique_justseen_by>();
  test_mulary_pack<unique_justseen_by, is<int>>();

  ut::same<list<_0, _1, _2>,
    emp::unique_justseen<emp::numbers<0, 1, 1, 2, 2, 2>>>();
  ut::same<list<_0, _1, _2, _0, _2>,
    emp::unique_justseen<emp::numbers<0, 1, 1, 2, 0, 2>>>();

  using odd = push_front<number<1>, bit_and<>>;
  using cmp = transform<odd, equal<>>;
  using scmp = detail::sfinae<cmp>;

  test_context<unique_justseen_by<cmp>, smp::unique_justseen_by<scmp>>()
    .test<list<>>()
    .test<list<_0>, _0, _0, _0>()
    .test<list<_0, _1, _2>, _0, _0, _1, _3, _2>()
    .test<list<bad_number>, bad_number>()
    .not_invocable<bad_number, bad_number>()
    ;

  test_context<unique_justseen_by<always<na>>, smp::unique_justseen_by<smp::always<na>>>()
    .test<list<>>()
    .test<list<_0>, _0>()
    .not_invocable<_0, _0>()
    ;

  test_context<unique_justseen<>, smp::unique_justseen<>>()
    .test<list<>>()
    .test<list<_0, _1, _0, _2>, _0, _0, _0, _1, _1, _0, _2>()
    .test<list<_1>, _1, _1, _1>()
    .test<list<_0, _1, _3>, _0, _1, _3>()
    ;

  ut::not_invocable<smp::unique_justseen<bad_function>>();
  ut::not_invocable<smp::unique_justseen<bad_function>, _1, _1, _1, _2>();
  ut::not_invocable<smp::unique_justseen_by<smp::always<na>>, _1, _1>();
  ut::not_invocable<smp::unique_justseen_by<always<void>>, _1, _1>();
  ut::not_invocable<smp::unique_justseen_by<cmp, bad_function>>();
  ut::not_invocable<smp::unique_justseen_by<cmp, bad_function>, _1, _1, _1>();
  ut::not_invocable<smp::unique_justseen_by<bad_function, bad_function>>();
  ut::not_invocable<smp::unique_justseen_by<bad_function, bad_function>, _1, _1, _1>();
}

TEST_SUITE_END()

