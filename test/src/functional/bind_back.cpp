#include "test.hpp"

#include "jln/mp/smp/functional/bind_back.hpp"
#include "jln/mp/smp/list/pop_back.hpp"
#include "jln/mp/smp/list/listify.hpp"

TEST_SUITE_BEGIN()

TEST()
{
  using namespace jln::mp;

  test_pack2<bind_back>();

  ut::same<list<char, long, int, void>, emp::bind_back<list<char, long>, listify, int, void>>();

  test_context<
    bind_back<pop_back<>, int, long>,
    smp::bind_back<smp::pop_back<>, int, long>
  >()
    .test<list<int>>()
    .test<list<void, char, int>, void, char>()
    ;

  ut::not_invocable<smp::bind_back<smp::pop_back<>>>();
}

TEST_SUITE_END()
