#include "test.hpp"
#include "test/numbers.hpp"

#include "jln/mp/smp/utility/is.hpp"

TEST_SUITE_BEGIN()

TEST()
{
  using namespace jln::mp;
  using namespace ut::ints;
  namespace z = optimizer;
  namespace t = optimizer::types;

  test_context<lift<z::optimize>, void>()
    .test<t::uncallable::f<>, is<int>, t::uncallable>()
    .test<t::uncallable::f<>, is<int>, z::seq<int, int>>()
    .test<z::optimized_result_t<_1, always<_1>>, is<int>, int>()
    .test<z::optimized_result_t<z::union_<t::uncallable, _1>, always<_1>>,
      is<int>, z::union_<t::uncallable, int>>()
    .test<z::optimized_result_t<_0, always<_0>>, is<int>, void>()
    .test<z::optimized_result_t<t::boolean, is<int>>, is<int>, t::number>()
    .test<z::optimized_result_t<t::basic_union<t::uncallable, t::boolean>, is<int>>,
      is<int>, t::basic_pack<int>>()
    .test<z::optimized_result_t<z::union_<t::uncallable, t::boolean>, is<int>>,
      is<int>, z::union_<int, z::seq<int, int>>>()
    ;

  test_unary_pack<is, _1>();

  test_context<is<_1>, smp::is<_1>>()
    .test<_0, list<>>()
    .test<_1, _1>()
    .not_invocable<>()
    .not_invocable<_0, _1>()
    ;

  ut::not_invocable<smp::is<int, bad_function>>();
  ut::not_invocable<smp::is<int, bad_function>, int>();
}

TEST_SUITE_END()
