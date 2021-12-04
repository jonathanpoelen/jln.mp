#include "test.hpp"
#include "test/numbers.hpp"

#include "jln/mp/smp/functional/not_fn.hpp"

TEST_SUITE_BEGIN()

struct xxx
{
  template<class...>
  using f = jln::mp::true_;
};

TEST()
{
  using namespace jln::mp;
  using namespace ut::ints;

  ut::same<false_, emp::not_of<identity, true_>>();
  ut::same<true_, emp::not_of<identity, false_>>();

  ut::same<false_, emp::not_fn<seq_1, identity>>();
  ut::same<true_, emp::not_fn<seq_0, identity>>();

  test_pack3<not_fn, identity>();

  test_context<not_fn<identity>, smp::not_fn<smp::identity>, 0>()
    .test<_1, _0>()
    .test<_0, _1>()
    .not_invocable<_1, _1>()
    .not_invocable<void>()
    .not_invocable<>()
    ;

  using x_not = not_<>;
  using x_not_xxx = not_<xxx>;
  using x_not_not = not_<not_<>>;
  using x_not_not_xxx = not_<not_<xxx>>;
  using x_is = is<int>;
  using x_is_not = is<int, not_<>>;
  using x_same = same<>;
  using x_same_not = same<not_<>>;
  using x_lift = lift<std::is_same>;
  using x_lift_not = lift<std::is_same, not_<>>;
  using x_lift_not_not = lift<std::is_same, not_<not_<>>>;
  using x_tee_not = tee<is<int>, not_<>>;
  using x_tee2_not = tee<x_tee_not, not_<>>;
  using x_tee3_not = tee<x_tee2_not, not_<>>;
  using x_tee_xxx_not = tee<xxx, not_<>>;
  using x_tee_xxx_not_not = tee<xxx, not_<not_<>>>;
  using x_tee_xxx2_not = tee<x_tee_xxx_not, not_<>>;
  using x_tee_xxx3_not = tee<x_tee_xxx2_not, not_<>>;

  ut::invoke_r<x_not, lift<not_fn>, identity>();
  ut::invoke_r<x_not_not, lift<not_fn>, x_not>();
  ut::invoke_r<tee<x_not_xxx, not_<>>, lift<not_fn>, x_not_xxx>();
  ut::invoke_r<x_not, lift<not_fn>, x_not_not>();
  ut::invoke_r<tee<x_not_not_xxx, not_<>>, lift<not_fn>, x_not_not_xxx>();
  ut::invoke_r<x_is_not, lift<not_fn>, x_is>();
  ut::invoke_r<x_is, lift<not_fn>, x_is_not>();
  ut::invoke_r<x_same_not, lift<not_fn>, x_same>();
  ut::invoke_r<x_same, lift<not_fn>, x_same_not>();
  ut::invoke_r<x_lift_not, lift<not_fn>, x_lift>();
  ut::invoke_r<x_lift_not_not, lift<not_fn>, x_lift_not>();
  ut::invoke_r<x_is, lift<not_fn>, x_tee_not>();
  ut::invoke_r<x_is_not, lift<not_fn>, x_tee2_not>();
  ut::invoke_r<x_is, lift<not_fn>, x_tee3_not>();
  ut::invoke_r<x_tee_xxx_not_not, lift<not_fn>, x_tee_xxx_not>();
  ut::invoke_r<x_tee_xxx_not, lift<not_fn>, x_tee_xxx2_not>();
  ut::invoke_r<x_tee_xxx_not_not, lift<not_fn>, x_tee_xxx3_not>();

  ut::not_invocable<smp::not_fn<smp::always<na>>, _1>();
  ut::not_invocable<smp::not_fn<bad_function>, _1>();
  ut::not_invocable<smp::not_fn<always<void>>, _1>();
  ut::not_invocable<smp::not_fn<identity, bad_function>>();
}

TEST_SUITE_END()
