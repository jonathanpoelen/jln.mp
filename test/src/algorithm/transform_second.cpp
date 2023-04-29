#include "test.hpp"
#include "test/numbers.hpp"

#include "jln/mp/smp/algorithm/transform_second.hpp"
#include "jln/mp/smp/number/operators.hpp"

TEST_SUITE_BEGIN()

template<class x, class y>
using to = mp::list<x, y, void>;

TEST()
{
  using namespace jln::mp;
  using namespace ut::ints;

  test_unary_pack<transform_second>();
  test_mulary_pack<transform_second, inc<>>();

  ut::same<list<_0, _2, _2>, emp::transform_second<seq_0_1_2, inc<>>>();
  ut::same<list<_0, _2, void>, emp::transform_second<seq_0_1, inc<>, lift<to>>>();

  test_context<transform_second<inc<>>, smp::transform_second<smp::inc<>>>()
    .test<list<_1, _4>, _1, _3>()
    .test<list<_0, _2, _2>, _0, _1, _2>()
    .not_invocable<>()
    .not_invocable<_1>()
    ;

  ut::not_invocable<smp::transform_second<smp::always<na>>, _1, _1>();
  ut::not_invocable<smp::transform_second<bad_function>, _1, _1>();
  ut::not_invocable<smp::transform_second<identity, bad_function>, _1, _1>();
  ut::not_invocable<smp::transform_second<bad_function, bad_function>, _1, _1>();
}

TEST_SUITE_END()
