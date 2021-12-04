#include "test.hpp"
#include "test/numbers.hpp"

#include "jln/mp/smp/utility/always.hpp"
#include "jln/mp/smp/list/pop_back.hpp"

TEST_SUITE_BEGIN()

TEST()
{
  using namespace jln::mp;
  using namespace ut::ints;

  test_pack2<pop_back>();

  test_context<pop_back<>, smp::pop_back<>>()
    .test<list<>, _1>()
    .test<seq_1, _1, _2>()
    .test<seq_1_2, _1, _2, _3>()
    .not_invocable<>()
    ;

  ut::not_invocable<smp::pop_back<smp::always<na>>>();
  ut::not_invocable<smp::pop_back<bad_function>>();
}

TEST_SUITE_END()
