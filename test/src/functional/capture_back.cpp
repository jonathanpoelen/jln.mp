#include "test.hpp"
#include "test/numbers.hpp"

#include "jln/mp/smp/functional/capture_back.hpp"
#include "jln/mp/smp/functional/identity.hpp"
#include "jln/mp/smp/list/pop_front.hpp"
#include "jln/mp/number/numbers.hpp"

TEST_SUITE_BEGIN()

TEST()
{
  using namespace jln::mp;
  using namespace ut::ints;

  test_context<capture_back<int, char>, smp::capture_back<int, char>>()
    .test<list<char>, pop_front<>>()
    .test<list<>, pop_front<pop_front<>>>()
    .test<list<void, int, char>, listify, void>()
    .not_invocable<smp::identity>()
    .not_invocable<pop_front<pop_front<smp::pop_front<>>>>()
    ;

  test_context<capture_back_v<void>, smp::capture_back_v<void>>()
    .not_invocable<listify, int>()
    .not_invocable<listify, _2>()
    .not_invocable<listify>()
    ;

  test_context<capture_back_v<_1, _2>, smp::capture_back_v<_1, _2>>()
    .test<seq_1_2, numbers<>>()
    .test<emp::numbers<3, 1, 2>, numbers<>, _3>()
    .not_invocable<listify>()
    ;
}

TEST_SUITE_END()
