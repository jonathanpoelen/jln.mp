#include "test.hpp"

#include "jln/mp/smp/functional/identity.hpp"

TEST_SUITE_BEGIN()

TEST()
{
  using namespace jln::mp;

  test_context<identity, smp::identity>()
    .test<int, int>()
    .not_invocable<>()
    .not_invocable<int, int>()
    ;
}

TEST_SUITE_END()
