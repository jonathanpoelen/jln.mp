#include "test.hpp"

#include "jln/mp/smp/list/clear.hpp"

TEST_SUITE_BEGIN()

TEST()
{
  using namespace jln::mp;
  namespace z = optimizer;
  namespace t = optimizer::types;

  test_context<lift<z::optimize>, void>()
    .test<t::uncallable::f<>, clear<>, t::uncallable>()
    .test<z::optimized_result_t<list<>, always<list<>>>, clear<>, int>()
    .test<z::optimized_result_t<list<>, always<list<>>>, clear<>, int>()
    .test<z::optimized_result_t<list<>, always<list<>>>, clear<>, z::seq<int, int>>()
    .test<z::optimized_result_t<z::union_<t::uncallable, list<>>, always<list<>>>,
      clear<>, z::union_<t::uncallable, int>>()
    ;

  test_context<clear<>, smp::clear<>>()
    .test<list<>>()
    .test<list<>, void>()
    .test<list<>, void, void>()
    ;

  ut::not_invocable<smp::clear<bad_function>>();
  ut::not_invocable<smp::clear<bad_function>, void>();
}

TEST_SUITE_END()
