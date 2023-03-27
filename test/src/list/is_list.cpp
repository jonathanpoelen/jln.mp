#include "test.hpp"
#include "test/numbers.hpp"

#include "jln/mp/smp/list/is_list.hpp"

TEST_SUITE_BEGIN()

TEST()
{
  using namespace jln::mp;
  using namespace ut::ints;
  namespace z = optimizer;
  namespace t = optimizer::types;

  test_context<lift<z::optimize>, void>()
    .test<t::uncallable::f<>, is_list<>, t::uncallable>()
    .test<t::uncallable::f<>, is_list<>, z::seq<int, int>>()
    .test<z::optimized_result_t<_0, always<_0>>, is_list<>, int>()
    .test<z::optimized_result_t<_1, always<_1>>, is_list<>, list<>>()
    .test<z::optimized_result_t<_1, always<_1>>, is_list<>, z::list_t<t::number>>()
    .test<z::optimized_result_t<t::boolean, is_list<>>, is_list<>, t::any>()
    .test<z::optimized_result_t<z::union_<t::uncallable, t::boolean>, is_list<>>,
      is_list<>, z::pack<t::any>>()
    .test<z::optimized_result_t<z::union_<t::uncallable, _0>, always<_0>>,
      is_list<>, z::pack<int>>()
    ;

  test_unary_pack<is_list>();

  ut::same<_0, emp::is_list<_0>>();
  ut::same<_1, emp::is_list<list<>>>();

  test_context<is_list<>, smp::is_list<>>()
    .test<_0, _1>()
    .test<_1, list<>>()
    .not_invocable<_0, _0>()
    ;

  ut::not_invocable<smp::is_list<bad_function>>();
  ut::not_invocable<smp::is_list<bad_function>, list<>>();
}

TEST_SUITE_END()
