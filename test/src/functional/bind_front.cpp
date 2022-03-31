#include "test.hpp"

#include "jln/mp/smp/functional/bind_front.hpp"
#include "jln/mp/smp/list/pop_front.hpp"
#include "jln/mp/smp/list/listify.hpp"

TEST_SUITE_BEGIN()

TEST()
{
  using namespace jln::mp;

  test_pack2<bind_front>();

  ut::same<list<int, void, char, long>, emp::bind_front<list<char, long>, listify, int, void>>();

  test_context<
    bind_front<pop_front<>, int, long>,
    smp::bind_front<smp::pop_front<>, int, long>
  >()
    .test<list<long>>()
    .test<list<long, void, char>, void, char>()
    ;

  ut::not_invocable<smp::bind_front<smp::pop_front<>>>();
}

TEST_SUITE_END()
