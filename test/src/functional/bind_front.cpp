#include "test.hpp"
#include "test/numbers.hpp"

#include "jln/mp/smp/functional/bind_front.hpp"
#include "jln/mp/smp/number/numbers.hpp"
#include "jln/mp/smp/list/pop_front.hpp"
#include "jln/mp/smp/list/listify.hpp"

TEST_SUITE_BEGIN()

TEST()
{
  using namespace jln::mp;
  using namespace ut::ints;

  test_pack2<bind_front>();

  ut::same<list<int, void, char, long>, emp::bind_front<list<char, long>, listify, int, void>>();

  test_context<
    bind_front<pop_front<>, int, long>,
    smp::bind_front<smp::pop_front<>, int, long>
  >()
    .test<list<long>>()
    .test<list<long, void, char>, void, char>()
    ;

  test_context<
    bind_front_c<listify, 3>,
    smp::bind_front_c<smp::listify, 3>,
    -1
  >()
    .test<seq_3>()
    .test<seq_3_1, _1>()
    ;

  test_context<
    bind_front_v<listify, 3>,
    smp::bind_front_v<smp::listify, 3>,
    -1
  >()
    .test<list<val<3>>>()
    .test<list<val<3>, _1>, _1>()
    ;

  ut::not_invocable<smp::bind_front<smp::pop_front<>>>();
}

TEST_SUITE_END()
