#include "test.hpp"
#include "test/numbers.hpp"

#include "jln/mp/smp/list/join.hpp"

TEST_SUITE_BEGIN()

TEST()
{
  using namespace jln::mp;
  using namespace ut::ints;
  namespace z = optimizer;
  namespace t = optimizer::types;

  test_context<lift<z::optimize>, void>()
    .test<t::uncallable::f<>, join<>, t::uncallable>()
    .test<t::uncallable::f<>, join<>, int>()
    .test<t::uncallable::f<>, join<>, z::seq<int, int>>()
    .test<z::optimized_result_t<list<>, always<list<>>>, join<>, list<>>()
    .test<z::optimized_result_t<z::union_<t::uncallable, list<>>, always<list<>>>,
      join<>, z::union_<t::uncallable, list<>>>()
    .test<z::optimized_result_t<z::list_t<t::number, int>, join<>>,
      join<>, z::seq<z::list_t<t::number>, list<int>>>()
    .test<z::optimized_result_t<t::basic_list<t::basic_pack<t::number>>, join<>>,
      join<>, t::basic_pack<z::list_t<t::number>>>()
    .test<z::optimized_result_t<t::basic_list<t::basic_pack<t::basic_seq<t::number, int>>>, join<>>,
      join<>, t::basic_pack<z::list_t<t::number, int>>>()
    ;

  test_mulary_pack<join>();

  class X;
  using a = list<_0, _1, _2>;
  using b = list<_3, _4>;
  using c = list<X>;
  using e = list<>;
  using flat_list = list<_0, _1, _2, _3, _4, X>;

  ut::same<flat_list, emp::join<a, b, c>>();
  ut::same<e, emp::join<list<>, e, e>>();

  test_context<join<>, smp::join<>>()
    .test<e>()
    .test<e, e, e>()
    .test<c, c, e>()
    .test<flat_list, a, b, c>()
    .not_invocable<X, e>()
    ;
  test_context<join<join<>>, smp::join<smp::join<>>>()
    .test<flat_list, list<a, b>, list<c>>()
    .test<c, list<c>, e>()
    .not_invocable<c, e>()
    ;

  test_context<join<join<join<>>>, smp::join<smp::join<smp::join<>>>>()
    .test<e, e>()
    .test<e, list<e>, e>()
    .test<c, list<list<c>>, e>()
    .not_invocable<c, e>()
    .not_invocable<list<c>, e>()
    ;

  ut::not_invocable<smp::join<smp::always<na>>>();
  ut::not_invocable<smp::join<bad_function>>();
  ut::not_invocable<smp::join<bad_function>, seq_0_0, seq_0_0>();
}

TEST_SUITE_END()
