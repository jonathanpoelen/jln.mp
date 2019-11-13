#include "test.hpp"
#include "test/numbers.hpp"

#include "jln/mp/smp/algorithm/group.hpp"

TEST_SUITE_BEGIN()

TEST()
{
  using namespace jln::mp;
  using namespace ut::ints;

  test_pack<group_if, same_as<int>>()
    .test_binary()
    .test_unary()
    ;

  ut::same<list<list<_0>, list<_1, _1>, list<_2, _2, _2>>,
    emp::group<emp::numbers<0, 1, 1, 2, 2, 2>>>();
  ut::same<list<list<_0, _0>, list<_1, _1>, list<_2, _2, _2>>,
    emp::group<emp::numbers<0, 0, 1, 1, 2, 2, 2>>>();

  // test_context<group_if<odd>, smp::group_if<odd>, 0>()
  //   .test<_0>()
  //   .test<_0, _0, _0, _0>()
  //   .test<_3, _1, _1, _1>()
  //   .test<_2, _0, _1, _2, _3>()
  //   ;
  //
  // test_context<group_if<always<na>>, smp::group_if<smp::always<na>>, 0>()
  //   .test<_0>()
  //   .not_invocable<_0>()
  //   ;
  //
  // test_context<group<_1>, smp::group<_1>, 0>()
  //   .test<_0>()
  //   .test<_0, _0, _0, _0>()
  //   .test<_3, _1, _1, _1>()
  //   .test<_1, _0, _1, _3>()
  //   .test<_2, _0, _1, _3, _1>()
  //   ;
}

TEST_SUITE_END()

