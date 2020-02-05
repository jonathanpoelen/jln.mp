#include "test.hpp"

#include "jln/mp/smp/functional/bind.hpp"

TEST_SUITE_BEGIN()

template<class x>
using foo = x;

template<class x>
struct bar
{
  using type = x;
};

class x {};

TEST()
{
  using namespace jln::mp;

  test_context<cfe<foo>, smp::cfe<foo>>()
    .test<x, x>()
    .not_invocable<x, x>()
    ;

  test_context<cfl<bar>, smp::cfl<bar>>()
    .test<x, x>()
    .not_invocable<x, x>()
    ;

  test_context<cfe<bar>, smp::cfe<bar>>()
    .test<bar<x>, x>()
    ;

  test_context<cfl<foo>, smp::cfl<foo>>()
    .not_invocable<x>()
    ;
}

TEST_SUITE_END()
