#include "test.hpp"
#include "test/numbers.hpp"

#include "jln/mp/smp/list/offset.hpp"

TEST_SUITE_BEGIN()

TEST()
{
  using namespace jln::mp;
  using namespace ut::ints;

  ut::same<_2, emp::offset<list<int, int, int>, _5>>();
  ut::same<number<-1>, emp::offset<list<int, int, int>, _2>>();

  test_pack<offset, _2>()
    .test_unary()
    ;

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
}

TEST_SUITE_END()
