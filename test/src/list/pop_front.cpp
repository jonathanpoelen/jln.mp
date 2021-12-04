#include "test.hpp"
#include "test/numbers.hpp"

#include "jln/mp/smp/utility/always.hpp"
#include "jln/mp/smp/list/pop_front.hpp"

TEST_SUITE_BEGIN()

TEST()
{
  using namespace jln::mp;
  using namespace ut::ints;

  test_pack2<pop_front>();

  test_context<pop_front<>, smp::pop_front<>>()
    .test<list<>, _0>()
    .test<seq_1_2, _0, _1, _2>()
    .not_invocable<>()
    ;

  ut::not_invocable<smp::pop_front<smp::always<na>>>();
  ut::not_invocable<smp::pop_front<bad_function>>();
}

TEST_SUITE_END()
