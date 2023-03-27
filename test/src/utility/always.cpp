#include "test.hpp"
#include "test/numbers.hpp"

#include "jln/mp/smp/utility/always.hpp"
#include "jln/mp/smp/number/operators.hpp"

TEST_SUITE_BEGIN()

TEST()
{
  using namespace jln::mp;
  using namespace ut::ints;
  namespace z = optimizer;
  namespace tt = optimizer::types;

  test_context<lift<z::optimize>, void>()
    .test<tt::uncallable::f<>, always<int>, tt::uncallable>()
    .test<z::optimized_result_t<int, always<int>>, always<int>, void>()
    .test<z::optimized_result_t<int, always<int>>, always<int>, tt::number>()
    .test<z::optimized_result_t<int, always<int>>, always<int>, z::seq<int, int>>()
    .test<z::optimized_result_t<z::union_<tt::uncallable, int>, always<int>>,
      always<int>, z::union_<tt::uncallable, int>>()
    .test<z::optimized_result_t<char, always<char>>, always<int, always<char>>, void>()
    ;

  test_unary_pack<always, _1>();

  test_context<always<_1>, smp::always<_1>>()
    .test<_1>()
    .test<_1, list<>>()
    .test<_1, seq_0_0_0>()
    ;

  test_context<always<_1, equal<>>, smp::always<_1, smp::equal<>>>()
    .not_invocable<>()
    .not_invocable<_0>()
    ;

  ut::not_invocable<smp::always<int, bad_function>>();
}

TEST_SUITE_END()
