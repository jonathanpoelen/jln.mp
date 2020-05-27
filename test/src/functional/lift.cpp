#include "test.hpp"
#include "test/numbers.hpp"

#include "jln/mp/smp/functional/lift.hpp"
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

  (void)lift<ut::unary::f>();
  (void)lift<ut::binary::f>();
  (void)lift<ut::listify::f>();
  (void)lift<ut::variadic::f>();

  (void)lift_t<ut::unary::f>();
  (void)lift_t<ut::binary::f>();
  (void)lift_t<ut::listify::f>();
  (void)lift_t<ut::variadic::f>();

  test_context<lift<foo>, smp::lift<foo>>()
    .test<x, x>()
    .not_invocable<x, x>()
    ;

  test_context<lift_t<bar>, smp::lift_t<bar>>()
    .test<x, x>()
    .not_invocable<x, x>()
    ;

  test_context<lift<bar>, smp::lift<bar>>()
    .test<bar<x>, x>()
    ;

  test_context<lift_t<foo>, smp::lift_t<foo>>()
    .not_invocable<x>()
    ;

  test_context<lift<violation::f>, smp::lift<violation::f>>()
    .not_invocable<x>()
    ;

  test_context<lift_t<violation::f>, smp::lift_t<violation::f>>()
    .not_invocable<x>()
    ;

  ut::not_invocable<smp::lift<foo, bad_function>>();
  ut::not_invocable<smp::lift_t<bar, bad_function>>();
  ut::not_invocable<smp::lift<bar, bad_function>>();
}

TEST_SUITE_END()
