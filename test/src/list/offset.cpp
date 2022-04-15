#include "test.hpp"
#include "test/numbers.hpp"

#include "jln/mp/smp/utility/always.hpp"
#include "jln/mp/smp/list/offset.hpp"

TEST_SUITE_BEGIN()

TEST()
{
  using namespace jln::mp;
  using namespace ut::ints;

  ut::same<_2, emp::offset<list<int, int, int>, _5>>();
  ut::same<number<-1>, emp::offset<list<int, int, int>, _2>>();

  test_unary_pack<offset, _2>();

  test_context<offset<_2>, smp::offset<_2>>()
    .test<_2>()
    .test<_1, int>()
    .test<_0, int, int>()
    .test<number<-1>, int, int, int>()
    .test<number<-2>, int, int, int, int>()
    ;

  test_context<smp::offset<bad_number>, void>()
    .not_invocable<>()
    ;

  ut::not_invocable<smp::offset<smp::always<na>>>();
  ut::not_invocable<smp::offset<_1, bad_function>>();
  ut::not_invocable<smp::offset<_1, bad_function>, _1, _1, _1>();
}

TEST_SUITE_END()
