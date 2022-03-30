#include "test.hpp"
#include "test/numbers.hpp"

#include "jln/mp/smp/functional/until.hpp"
#include "jln/mp/smp/functional/lift.hpp"
#include "jln/mp/smp/functional/if.hpp"
#include "jln/mp/smp/list/push_back.hpp"
#include "jln/mp/smp/list/is_size_of.hpp"
#include "jln/mp/smp/utility/is_not.hpp"
#include "jln/mp/smp/utility/stl_traits.hpp"

TEST_SUITE_BEGIN()

TEST()
{
  using namespace jln::mp;
  using namespace ut::ints;

  test_context<
    until<is<int****>, traits::add_pointer<>>,
    smp::until<smp::is<int****>, smp::traits::add_pointer<>>
  >()
    .test<int****, int>()
    .not_invocable<>()
    .not_invocable<int, int>()
  ;

  test_context<
    until_xs<is_size_of_c<5>, push_back<int, next_recursion>>,
    smp::until_xs<smp::is_size_of_c<5>, smp::push_back<int, smp::next_recursion>>
  >()
    .test<list<_1, int, int, int, int>, _1>()
    .test<list<_1, _2, _3, _4, _5>, _1, _2, _3, _4, _5>()
  ;

  ut::not_invocable<smp::until<smp::always<na>, smp::next_recursion>, _1, _1>();
  ut::not_invocable<smp::until<smp::always<_1>, smp::next_recursion>, _1, _1>();
  ut::not_invocable<smp::until<bad_function, smp::always<_0>>, _1>();
  ut::not_invocable<smp::until<smp::always<_0>, bad_function>, _1>();
}

TEST_SUITE_END()
