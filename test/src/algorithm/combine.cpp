#include "test.hpp"
#include "test/numbers.hpp"

#include "jln/mp/smp/algorithm/combine.hpp"

TEST_SUITE_BEGIN()

TEST()
{
  using namespace jln::mp;
  using namespace ut::ints;

  test_pack<combine>()
    .test_variadic()
    .test_binary()
    .test_unary()
    ;

  ut::same<list<>, emp::combine<list<>>>();
  ut::same<list<
    list<_0, _0>, list<_0, _1>, list<_1, _0>, list<_1, _1>>,
    emp::combine<list<_0, _1>>>();

  test_context<combine<>, smp::combine<>>()
    .test<list<>>()
    .test<list<list<_0>>, _0>()
    .test<list<
      list<_0, _0>, list<_0, _1>,
      list<_1, _0>, list<_1, _1>>,
      _0, _1>()
    .test<list<
      list<_0, _0, _0>, list<_0, _0, _1>, list<_0, _0, _2>,
      list<_0, _1, _0>, list<_0, _1, _1>, list<_0, _1, _2>,
      list<_0, _2, _0>, list<_0, _2, _1>, list<_0, _2, _2>,
      list<_1, _0, _0>, list<_1, _0, _1>, list<_1, _0, _2>,
      list<_1, _1, _0>, list<_1, _1, _1>, list<_1, _1, _2>,
      list<_1, _2, _0>, list<_1, _2, _1>, list<_1, _2, _2>,
      list<_2, _0, _0>, list<_2, _0, _1>, list<_2, _0, _2>,
      list<_2, _1, _0>, list<_2, _1, _1>, list<_2, _1, _2>,
      list<_2, _2, _0>, list<_2, _2, _1>, list<_2, _2, _2>>,
      _0, _1, _2>()
    ;
}

TEST_SUITE_END()
