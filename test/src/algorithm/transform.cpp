#include "test.hpp"
#include "test/numbers.hpp"

#include "jln/mp/smp/algorithm/transform.hpp"
#include "jln/mp/smp/number/operators.hpp"

TEST_SUITE_BEGIN()

template<class x, class y>
using to = mp::list<x, y, void>;

TEST()
{
  using namespace jln::mp;
  using namespace ut::ints;

  test_unary_pack<transform>();
  test_mulary_pack<transform, inc<>>();

  ut::same<seq_1_2_3, emp::transform<seq_0_1_2, inc<>>>();
  ut::same<list<_0, _1, void>, emp::transform<seq_0_1, identity, lift<to>>>();

  test_context<transform<inc<>>, smp::transform<smp::inc<>>>()
    .test<list<>>()
    .test<seq_1_2_3, _0, _1, _2>()
    .not_invocable<list<>>()
    ;

  ut::not_invocable<smp::transform<smp::always<na>>, _1>();
  ut::not_invocable<smp::transform<bad_function>, _1>();
  ut::not_invocable<smp::transform<identity, bad_function>, _1>();
  ut::not_invocable<smp::transform<bad_function, bad_function>, _1>();
}

TEST_SUITE_END()
