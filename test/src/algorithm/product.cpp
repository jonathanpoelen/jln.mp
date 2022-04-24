#include "test.hpp"
#include "test/numbers.hpp"

#include "jln/mp/smp/utility/always.hpp"
#include "jln/mp/smp/algorithm/product.hpp"

TEST_SUITE_BEGIN()

TEST()
{
  using namespace jln::mp;
  using namespace ut::ints;

  test_mulary_pack<product>();

  ut::same<list<>, emp::product<list<>>>();
  ut::same<list<seq_0, seq_1>, emp::product<list<list<_0, _1>>>>();

  test_context<product<>, smp::product<>>()
    .test<list<>>()
    .test<list<>, list<>>()
    .test<list<seq_0>, seq_0>()
    .test<list<seq_0, seq_1>, list<_0, _1>>()
    .test<list<>, list<>, list<_0, _1>>()
    .test<list<>, list<_0, _1>, list<>>()
    .test<list<
        list<_0, _2>, list<_0, _3>,
        list<_1, _2>, list<_1, _3>>,
      list<_0, _1>, list<_2, _3>>()
    .test<list<
        list<_0, _2>, list<_0, _3>, list<_0, _4>,
        list<_1, _2>, list<_1, _3>, list<_1, _4>>,
      list<_0, _1>, list<_2, _3, _4>>()
    .test<list<
        list<_0, _3>, list<_0, _4>,
        list<_1, _3>, list<_1, _4>,
        list<_2, _3>, list<_2, _4>>,
      list<_0, _1, _2>, list<_3, _4>>()
    .test<list<>,
      list<_0, _1, _2>, list<_3, _4>, list<>>()
    .test<list<>,
      list<>, list<_0, _1, _2>, list<_3, _4>>()
    .test<list<>,
      list<_0, _1, _2>, list<>, list<_3, _4>>()
    .test<list<>,
      list<_0, _1, _2>, list<_3, _4>, list<>, list<_5>>()
    .test<list<
        list<_0, _3, _5>, list<_0, _4, _5>,
        list<_1, _3, _5>, list<_1, _4, _5>,
        list<_2, _3, _5>, list<_2, _4, _5>>,
      list<_0, _1, _2>, list<_3, _4>, list<_5>>()
    .test<list<
        list<_0, _3, _5>, list<_0, _3, _6>,
        list<_0, _4, _5>, list<_0, _4, _6>,
        list<_1, _3, _5>, list<_1, _3, _6>,
        list<_1, _4, _5>, list<_1, _4, _6>,
        list<_2, _3, _5>, list<_2, _3, _6>,
        list<_2, _4, _5>, list<_2, _4, _6>>,
      list<_0, _1, _2>, list<_3, _4>, list<_5, _6>>()
    .not_invocable<int>()
    ;

  ut::not_invocable<smp::product<smp::always<na>>>();
  ut::not_invocable<smp::product<bad_function>>();
  ut::not_invocable<smp::product<bad_function>, seq_0>();
  ut::not_invocable<smp::product<bad_function>, seq_0_1, seq_0_1>();
}

TEST_SUITE_END()
