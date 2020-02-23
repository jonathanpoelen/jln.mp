#include "test.hpp"
#include "test/numbers.hpp"

#include "jln/mp/smp/functional/function.hpp"
#include "jln/mp/smp/list/push_front.hpp"

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

  (void)cfe<ut::unary::f>();
  (void)cfe<ut::binary::f>();
  (void)cfe<ut::listify::f>();
  (void)cfe<ut::variadic::f>();

  (void)cfl<ut::unary::f>();
  (void)cfl<ut::binary::f>();
  (void)cfl<ut::listify::f>();
  (void)cfl<ut::variadic::f>();

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

  test_context<cfe<violation::f>, smp::cfe<violation::f>>()
    .not_invocable<x>()
    ;

  test_context<cfl<violation::f>, smp::cfl<violation::f>>()
    .not_invocable<x>()
    ;

  ut::not_invocable<smp::cfe<foo, bad_function>>();
  ut::not_invocable<smp::cfl<bar, bad_function>>();
  ut::not_invocable<smp::cfe<bar, bad_function>>();
}

TEST_SUITE_END()
