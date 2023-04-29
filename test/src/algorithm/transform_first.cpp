#include "test.hpp"
#include "test/numbers.hpp"

#include "jln/mp/smp/algorithm/transform_first.hpp"
#include "jln/mp/smp/number/operators.hpp"

TEST_SUITE_BEGIN()

template<class x, class y>
using to = mp::list<x, y, void>;

TEST()
{
  using namespace jln::mp;
  using namespace ut::ints;

  test_unary_pack<transform_first>();
  test_mulary_pack<transform_first, inc<>>();

  ut::same<list<_1, _1, _2>, emp::transform_first<seq_0_1_2, inc<>>>();
  ut::same<list<_1, _1, void>, emp::transform_first<seq_0_1, inc<>, lift<to>>>();

  test_context<transform_first<inc<>>, smp::transform_first<smp::inc<>>>()
    .test<seq_2, _1>()
    .test<list<_1, _1, _2>, _0, _1, _2>()
    .not_invocable<>()
    ;

  ut::not_invocable<smp::transform_first<smp::always<na>>, _1>();
  ut::not_invocable<smp::transform_first<bad_function>, _1>();
  ut::not_invocable<smp::transform_first<identity, bad_function>, _1>();
  ut::not_invocable<smp::transform_first<bad_function, bad_function>, _1>();
}

TEST_SUITE_END()
