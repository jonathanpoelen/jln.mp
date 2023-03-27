#include "test.hpp"
#include "test/numbers.hpp"

#include "jln/mp/smp/utility/iterate.hpp"
#include "jln/mp/smp/number/operators.hpp"

TEST_SUITE_BEGIN()

TEST()
{
  using namespace jln::mp;
  using namespace ut::ints;
  namespace z = optimizer;
  namespace t = optimizer::types;

  test_context<lift<z::optimize>, void>()
    .test<t::uncallable::f<>, iterate_c<1, listify>, t::uncallable>()
    .test<t::uncallable::f<>, iterate_c<1, listify>, z::seq<int, int>>()
    .test<z::optimized_result_t<int, always<int>>, iterate_c<0, listify>, int>()
    .test<z::optimized_result_t<list<int>, always<list<int>>>, iterate_c<1, listify>, int>()
    .test<z::optimized_result_t<t::any, iterate_c<2, listify>>, iterate_c<2, listify>, int>()
    ;

  test_unary_pack<iterate, _0>();
  test_unary_pack<iterate, _0, inc<>>();

  test_context<iterate<_0, inc<>>, smp::iterate<_0, smp::inc<>>>()
    .test<_0, _0>()
    .test<_3, _3>()
    .not_invocable<>()
    .not_invocable<_0, _1>()
    ;

  test_context<iterate<_5, inc<>>, smp::iterate<_5, smp::inc<>>>()
    .test<_5, _0>()
    .test<_7, _2>()
    .not_invocable<>()
    .not_invocable<_0, _1>()
    ;

  test_context<iterate<_10, inc<>>, smp::iterate<_10, smp::inc<>>>()
    .test<_10, _0>()
    .not_invocable<>()
    .not_invocable<_0, _1>()
    ;

  ut::not_invocable<smp::iterate<_10, smp::inc<>, bad_function>, _1>();
  ut::not_invocable<smp::iterate<_1, smp::inc<>, bad_function>, _1>();
  ut::not_invocable<smp::iterate<_1, smp::inc<>>, void>();
  ut::not_invocable<smp::iterate<_10, bad_function>, _1>();
  ut::not_invocable<smp::iterate<_1, bad_function>, _1>();
  ut::not_invocable<smp::iterate<int, smp::inc<>>, _1>();
  ut::not_invocable<smp::iterate<int, smp::inc<>>, void>();
  ut::not_invocable<smp::iterate<int, bad_function>, _1>();
}

TEST_SUITE_END()
