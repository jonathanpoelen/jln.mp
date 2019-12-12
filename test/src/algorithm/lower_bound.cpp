#include "test.hpp"
#include "test/numbers.hpp"

#include "jln/mp/smp/algorithm/lower_bound.hpp"
#include "jln/mp/smp/number/operators.hpp"
#include "jln/mp/algorithm/iota.hpp"

TEST_SUITE_BEGIN()

template<class... xs>
struct other_list
{
  static_assert(sizeof...(xs) == 0);
};

template<int less_than, int count>
static void test_lower_bound()
{
  using namespace jln::mp;
  using namespace ut::ints;

  using f = iota<lower_bound<
    less_than_c<less_than>,
    cfe<list>,
    cfe<other_list>
  >>;

  int const size = (less_than < count) ? count - (less_than) : 0;
  using to_list = emp::conditional_c<
    size != 0,
    cfe<list>,
    cfe<other_list>
  >;
  using result = emp::iota_c<less_than, size, 1, to_list>;

  ut::invoke_r<result, f, _0, number<count>>();
  // TODO test with [count*less_than] elements
}

template<int less_than>
static void test_lower_bounds()
{
  test_lower_bound<less_than, 0>();
  test_lower_bound<less_than, 1>();
  test_lower_bound<less_than, 2>();
  test_lower_bound<less_than, 3>();
  test_lower_bound<less_than, 4>();
  test_lower_bound<less_than, 5>();
  test_lower_bound<less_than, 7>();
  test_lower_bound<less_than, 8>();
  test_lower_bound<less_than, 9>();
  test_lower_bound<less_than, 15>();
  test_lower_bound<less_than, 16>();
  test_lower_bound<less_than, 17>();
  test_lower_bound<less_than, 31>();
  test_lower_bound<less_than, 32>();
  test_lower_bound<less_than, 33>();
  test_lower_bound<less_than, 63>();
  test_lower_bound<less_than, 64>();
  test_lower_bound<less_than, 65>();
  test_lower_bound<less_than, 127>();
  test_lower_bound<less_than, 128>();
  test_lower_bound<less_than, 129>();
  test_lower_bound<less_than, 255>();
  test_lower_bound<less_than, 256>();
  test_lower_bound<less_than, 257>();
  test_lower_bound<less_than, 511>();
  test_lower_bound<less_than, 512>();
  test_lower_bound<less_than, 513>();
}

TEST()
{
  using namespace jln::mp;
  using namespace ut::ints;

  test_pack<lower_bound>()
    .test_binary()
    .test_unary()
  ;

  // using pred1 = less_than_c<2>;

  // ut::same<list<_3>, emp::lower_bound<seq_0_1_2_3, pred1>>();

  test_lower_bounds<0>();
  test_lower_bounds<1>();
  test_lower_bounds<2>();
  test_lower_bounds<3>();
  test_lower_bounds<4>();
  test_lower_bounds<5>();
  test_lower_bounds<7>();
  test_lower_bounds<8>();
  test_lower_bounds<9>();
  test_lower_bounds<15>();
  test_lower_bounds<16>();
  test_lower_bounds<17>();
  test_lower_bounds<31>();
  test_lower_bounds<32>();
  test_lower_bounds<33>();
  test_lower_bounds<255>();
  test_lower_bounds<256>();
  test_lower_bounds<257>();
  test_lower_bounds<511>();
  test_lower_bounds<512>();
  test_lower_bounds<513>();

  // ut::invoke_r<li_3st<_13>, iota<lower_bound<_12>>, _0, _14>();
  // ut::invoke_r<list<_20, _21>, iota<lower_bound<_20>>, _0, _22>();
  // ut::invoke_r<list<_60, _61>, iota<lower_bound<_60>>, _0, _62>();
  // ut::invoke_r<list<_70, _71>, iota<lower_bound<_70>>, _0, _72>();
  // ut::invoke_r<list<_130, _131>, iota<lower_bound<_130>>, _0, _132>();
  // ut::invoke_r<list<_260, _261>, iota<lower_bound<_260>>, _0, _262>();
  // ut::invoke_r<list<_320, _321>, iota<lower_bound<_320>>, _0, _322>();
  // ut::invoke_r<list<_520, _521>, iota<lower_bound<_520>>, _0, _522>();
  // ut::invoke_r<list<_555, _556>, iota<lower_bound<_555>>, _0, _557>();
  // ut::invoke_r<list<_580, _581>, iota<lower_bound<_580>>, _0, _582>();
  // ut::invoke_r<list<_780, _781>, iota<lower_bound<_780>>, _0, _782>();
  //
  // test_context<lower_bound_if<identity>, smp::lower_bound_if<smp::identity>>()
  //   .test<list<>>()
  //   .test<list<>, _0>()
  //   .test<seq_1, _1>()
  //   .test<seq_1, _0, _1>()
  //   .test<seq_1_2, _0, _0, _0, _0, _0, _0, _0, _0, _0, _0, _0, _0, _0, _0, _0, _0, _0, _0, _0, _0, _0, _0, _0, _0, _0, _0, _0, _0, _0, _0, _0, _0, _0, _0, _0, _0, _0, _0, _0, _0, _0, _0, _0, _0, _0, _0, _0, _0, _0, _0, _0, _0, _0, _0, _0, _0, _0, _0, _0, _0, _0, _0, _0, _0, _1, _2>()
  //   .test<seq_1_2, _0, _0, _0, _0, _0, _0, _0, _0, _0, _0, _0, _0, _0, _0, _0, _0, _0, _0, _0, _0, _0, _0, _0, _0, _0, _0, _0, _0, _0, _0, _0, _0, _0, _0, _0, _0, _0, _0, _0, _0, _0, _0, _0, _0, _0, _0, _0, _0, _0, _0, _0, _0, _0, _0, _0, _0, _0, _0, _0, _0, _0, _0, _0, _0, _0, _1, _2>()
  //   .not_invocable<void>()
  //   ;
  //
  // test_context<
  //   lower_bound<_3, listify, always<void>>,
  //   smp::lower_bound<_3, smp::listify, smp::always<void>>,
  //   0
  // >()
  //   .test<void>()
  //   .test<void, _0>()
  //   .test<void, _0, _1, _2>()
  //   .test<seq_3_2, _3, _2>()
  //   .test<seq_3_2, _0, _3, _2>()
  //   ;
}

TEST_SUITE_END()
