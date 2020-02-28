#include "test.hpp"
#include "test/numbers.hpp"

#include "jln/mp/smp/functional/compose.hpp"
#include "jln/mp/smp/number/operators.hpp"

TEST_SUITE_BEGIN()

template<class x> using f = jln::mp::number<x::value*10>;
template<class x, class...> using g = jln::mp::number<x::value+1>;
template<class... xs> using h = jln::mp::number<sizeof...(xs)>;

TEST()
{
  using namespace jln::mp;
  using namespace ut::ints;

  ut::same<call<compose_f<h>, int>, h<int>>();
  ut::same<call<compose_f<h, g>, int>, g<h<int>>>();
  ut::same<call<compose_f<h, g, f>, int>, f<g<h<int>>>>();
  ut::same<call<compose_f<f, g, h>, _1>, h<g<f<_1>>>>();
  ut::same<call<compose_f<g, h, f>, _1>, f<h<g<_1>>>>();

  ut::same<smp::compose_f<h, g, f>, smp::cfe<h, smp::cfe<g, smp::cfe<f>>>>();

  test_context<smp::compose_f<h, g, f>, void>()
    .test<f<g<h<int>>>, int>()
  ;

  test_context<smp::compose_f<f, g, h>, void>()
    .test<h<g<f<_1>>>, _1>()
    .not_invocable<int>()
  ;

  test_context<smp::compose_f<identity::f, f>, void>()
    .test<f<_1>, _1>()
    .not_invocable<int>()
  ;

  test_context<
    compose<inc<>, inc<>, inc<>>,
    smp::compose<smp::inc<>, smp::inc<>, smp::inc<>>
  >()
    .test<_4, _1>()
    .not_invocable<int>()
  ;

  ut::not_invocable<smp::compose<bad_function, bad_function>>();
  ut::not_invocable<smp::compose<bad_function, bad_function, bad_function>>();
}

TEST_SUITE_END()
