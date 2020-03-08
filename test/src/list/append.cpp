#include "test.hpp"
#include "test/numbers.hpp"

#include "jln/mp/smp/list/append.hpp"
#include "jln/mp/smp/number/operators.hpp"

TEST_SUITE_BEGIN()

TEST()
{
  using namespace jln::mp;
  using namespace ut::ints;

  test_pack2<append, list<>>();

  ut::same<list<_0, _1, _2, _3, _4>, emp::append<seq_0_1_2, _3, _4>>();

  test_context<append<list<_9>>, smp::append<list<_9>>>()
    .test<list<_9>>()
    .test<list<_9, _0, _1, _2>, _0, _1, _2>()
    ;

  ut::not_invocable<smp::append<seq_0_0, bad_function>>();
  ut::not_invocable<smp::append<seq_0_0, bad_function>, _1>();
  ut::not_invocable<smp::append<bad_number, bad_function>>();
  ut::not_invocable<smp::append<bad_number, bad_function>, _1>();
}

TEST_SUITE_END()
