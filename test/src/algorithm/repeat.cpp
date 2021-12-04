#include "test.hpp"
#include "test/numbers.hpp"

#include "jln/mp/smp/utility/always.hpp"
#include "jln/mp/smp/algorithm/repeat.hpp"

TEST_SUITE_BEGIN()

TEST()
{
  using namespace jln::mp;
  using namespace ut::ints;

  test_pack2<repeat, _1>();
  test_pack2<repeat>();

  ut::same<seq_1_1_1, emp::repeat_c<seq_1, 3>>();

  test_context<repeat_c<3>, smp::repeat_c<3>>()
    .test<list<>>()
    .test<seq_1_1_1, _1>()
    .test<emp::numbers<1, 2, 1, 2, 1, 2>, _1, _2>()
    ;

  ut::not_invocable<smp::repeat<smp::always<na>>>();
  ut::not_invocable<smp::repeat<_2, bad_function>>();
  ut::not_invocable<smp::repeat<_2, bad_function>, _1>();
  ut::not_invocable<smp::repeat<_2, bad_function>, _1, _1, _1>();
  ut::not_invocable<smp::repeat<bad_number, bad_function>>();
  ut::not_invocable<smp::repeat<bad_number, bad_function>, _1>();
  ut::not_invocable<smp::repeat<bad_number, bad_function>, _1, _1, _1>();
}

TEST_SUITE_END()
