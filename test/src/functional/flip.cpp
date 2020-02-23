#include "test.hpp"

#include "jln/mp/smp/functional/flip.hpp"

TEST_SUITE_BEGIN()

TEST()
{
  using namespace jln::mp;

  test_pack2<flip>();

  ut::same<list<char, int, void>, emp::flip<list<int, char, void>>>();

  test_context<flip<>, smp::flip<>>()
    .test<list<int, char>, char, int>()
    .test<list<int, char, void>, char, int, void>()
    .not_invocable<>()
    .not_invocable<int>()
    ;

  ut::not_invocable<smp::flip<bad_function>, void, int>();
}

TEST_SUITE_END()
