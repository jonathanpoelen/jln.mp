#include "test.hpp"
#include "test/numbers.hpp"

#include "jln/mp/smp/algorithm/transform.hpp"
#include "jln/mp/smp/number/operators.hpp"

TEST_SUITE_BEGIN()

TEST()
{
  using namespace jln::mp;
  using namespace ut::ints;

  test_pack2<transform, inc<>>();
  test_pack2<transform, listify>();

  ut::same<seq_1_2_3, emp::transform<seq_0_1_2, inc<>>>();

  test_context<transform<inc<>>, smp::transform<smp::inc<>>>()
    .test<list<>>()
    .test<seq_1_2_3, _0, _1, _2>()
    .not_invocable<list<>>()
    ;

  ut::not_invocable<smp::transform<bad_function>, _1>();
  ut::not_invocable<smp::transform<identity, bad_function>, _1>();
  ut::not_invocable<smp::transform<bad_function, bad_function>, _1>();
}

TEST_SUITE_END()
