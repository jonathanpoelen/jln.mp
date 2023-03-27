#include "test.hpp"
#include "test/numbers.hpp"

#include "jln/mp/smp/utility/conditional.hpp"

TEST_SUITE_BEGIN()

TEST()
{
  using namespace jln::mp;
  using namespace ut::ints;
  namespace z = optimizer;
  namespace tt = optimizer::types;

  test_context<lift<z::optimize>, void>()
    .test<tt::uncallable::f<>, conditional_c<true>, tt::uncallable>()
    .test<tt::uncallable::f<>, conditional_c<true>, void>()

    .test<z::optimized_result_t<int, always<int>>, conditional_c<true>, z::seq<int, void>>()
    .test<z::optimized_result_t<void, always<void>>, conditional_c<false>, z::seq<int, void>>()
    .test<z::optimized_result_t<z::union_<tt::uncallable, int>, always<int>>,
      conditional_c<true>, z::union_<tt::uncallable, z::seq<int, void>>>()
    .test<z::optimized_result_t<z::union_<tt::uncallable, void>, always<void>>,
      conditional_c<false>, z::union_<tt::uncallable, z::seq<int, void>>>()

    .test<z::optimized_result_t<tt::boolean, conditional_c<true>>,
      conditional_c<true>, z::seq<tt::boolean, tt::any>>()
    .test<z::optimized_result_t<tt::any, conditional_c<false>>,
      conditional_c<false>, z::seq<tt::boolean, tt::any>>()
    .test<z::optimized_result_t<z::union_<tt::uncallable, tt::boolean>, conditional_c<true>>,
      conditional_c<true>, z::union_<tt::uncallable, z::seq<tt::boolean, tt::any>>>()
    .test<z::optimized_result_t<z::union_<tt::uncallable, tt::any>, conditional_c<false>>,
      conditional_c<false>, z::union_<tt::uncallable, z::seq<tt::boolean, tt::any>>>()
    ;

  test_context<conditional_c<true>, smp::conditional_c<true>>()
    .test<_1, _1, _2>()
    .not_invocable<>()
    .not_invocable<_1>()
    .not_invocable<_1, _2, _3>()
    ;

  test_context<conditional_c<false>, smp::conditional_c<false>>()
    .test<_2, _1, _2>()
    .not_invocable<>()
    .not_invocable<_1>()
    .not_invocable<_1, _2, _3>()
    ;
}

TEST_SUITE_END()
