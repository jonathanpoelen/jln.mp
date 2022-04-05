#include "test.hpp"
#include "test/numbers.hpp"

#include "jln/mp/smp/functional/bind_back.hpp"
#include "jln/mp/smp/number/numbers.hpp"
#include "jln/mp/smp/list/pop_back.hpp"
#include "jln/mp/smp/list/listify.hpp"

TEST_SUITE_BEGIN()

TEST()
{
  using namespace jln::mp;
  using namespace ut::ints;

  test_pack2<bind_back>();

  ut::same<list<char, long, int, void>, emp::bind_back<list<char, long>, listify, int, void>>();

  test_context<
    bind_back<pop_back<>, int, long>,
    smp::bind_back<smp::pop_back<>, int, long>
  >()
    .test<list<int>>()
    .test<list<void, char, int>, void, char>()
    ;

  test_context<
    bind_back_v<numbers<>, _3>,
    smp::bind_back_v<smp::numbers<>, _3>,
    -1
  >()
    .test<seq_3>()
    .test<seq_1_3, _1>()
    .not_invocable<int>()
    ;

  test_context<
    bind_back_v_c<numbers<>, 3>,
    smp::bind_back_v_c<smp::numbers<>, 3>,
    -1
  >()
    .test<seq_3>()
    .test<seq_1_3, _1>()
    .not_invocable<int>()
    ;

  ut::not_invocable<smp::bind_back<smp::pop_back<>>>();
}

TEST_SUITE_END()
