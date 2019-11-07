#include "test.hpp"
#include "test/numbers.hpp"

#include "jln/mp/smp/algorithm/make_int_sequence.hpp"
#include "jln/mp/smp/number/numbers.hpp"
#include "jln/mp/smp/list/size.hpp"

TEST_SUITE_BEGIN()

TEST()
{
  using namespace jln::mp;
  using namespace ut::ints;

  ut::same<emp::make_int_sequence<_0>, list<>>();
  ut::same<emp::make_int_sequence<_1>, seq_0>();
  ut::same<emp::make_int_sequence<_2>, seq_0_1>();
  ut::same<emp::make_int_sequence<_3>, seq_0_1_2>();

  test_pack<make_int_sequence>()
    .test_unary<>()
    .test_binary<>()
  ;

  test_context<make_int_sequence<>, smp::make_int_sequence<>>()
    .test<list<>, _0>()
    .test<seq_0, _1>()
    .test<seq_0_1, _2>()
    .test<seq_0_1_2_3, _4>()
    .not_invocable<_0, _0>()
    .not_invocable<list<>>()
    .not_invocable<bad_number>()
    .not_invocable<class X>()
    ;

  test_context<
    make_int_sequence<size<make_int_sequence<>>>,
    smp::make_int_sequence<smp::size<smp::make_int_sequence<>>>
  >()
    .test<list<>, _0>()
    .test<seq_0, _1>()
    .test<seq_0_1, _2>()
    .test<seq_0_1_2_3, _4>()
    .not_invocable<_0, _0>()
    .not_invocable<list<>>()
    .not_invocable<bad_number>()
    .not_invocable<class X>()
    ;
}

TEST_SUITE_END()
