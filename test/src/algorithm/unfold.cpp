#include "test.hpp"
#include "test/numbers.hpp"

#include "jln/mp/smp/algorithm/unfold.hpp"
#include "jln/mp/smp/number/operators.hpp"
#include "jln/mp/smp/functional/tee.hpp"
#include "jln/mp/smp/functional/if.hpp"
#include "jln/mp/smp/functional/lift.hpp"

TEST_SUITE_BEGIN()

TEST()
{
  using namespace jln::mp;
  using namespace ut::ints;

  using f = if_<
    less_than_c<5>,
    tee<identity, inc<>, lift<Some>>,
    None
  >;
  using make_seq_5 = unfold<f>;

  using smp_f = smp::if_<
    smp::less_than_c<5>,
    smp::tee<smp::identity, smp::inc<>, smp::lift<Some>>,
    smp::None
  >;
  using smp_make_seq_5 = smp::unfold<smp_f>;

  ut::same<list<_0, _1, _2, _3, _4>, emp::unfold<_0, f>>();

  test_pack2<unfold, mp::always<None>>();

  test_context<make_seq_5, smp_make_seq_5>()
    .test<list<_0, _1, _2, _3, _4>, _0>()
    .test<list<number<-1>, _0, _1, _2, _3, _4>, number<-1>>()
    .test<list<_3, _4>, _3>()
    .test<list<_4>, _4>()
    .test<list<>, _5>()
    .not_invocable<>()
    .not_invocable<list<>>()
    ;

  ut::not_invocable<smp::unfold<smp::always<na>>, _1, _1, _1>();
  ut::not_invocable<smp::unfold<smp_f, bad_function>, _1>();
  ut::not_invocable<smp::unfold<listify, bad_function>, _1, _1, _1>();
  ut::not_invocable<smp::unfold<listify, bad_function>, list<>>();
  ut::not_invocable<smp::unfold<listify>>();
  ut::not_invocable<smp::unfold<bad_function>, list<>>();
  ut::not_invocable<smp::unfold<bad_function>, _1>();
  ut::not_invocable<smp::unfold<bad_function>>();
}

TEST_SUITE_END()
