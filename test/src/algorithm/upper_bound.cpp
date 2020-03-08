#include "test.hpp"
#include "test/numbers.hpp"

#include "jln/mp/smp/algorithm/upper_bound.hpp"
#include "jln/mp/smp/number/operators.hpp"
#include "jln/mp/algorithm/iota.hpp"

TEST_SUITE_BEGIN()

template<class... xs>
struct other_list
{
  static_assert(sizeof...(xs) == 0);
};

template<int less_than, int count>
static void test_upper_bound()
{
  using namespace jln::mp;
  using namespace ut::ints;

  using f = iota<upper_bound_of_c<
    less_than,
    cfe<list>,
    cfe<other_list>
  >>;

  int const size = (less_than + 1 < count) ? count - (less_than + 1) : 0;
  using to_list = emp::conditional_c<
    size != 0,
    cfe<list>,
    cfe<other_list>
  >;
  using result = emp::iota_c<less_than+1, size, 1, to_list>;

  ut::invoke_r<result, f, _0, number<count>>();
  // TODO test with [count*less_than] elements
}

template<int less_than>
static void test_upper_bounds()
{
  test_upper_bound<less_than, 0>();
  test_upper_bound<less_than, 1>();
  test_upper_bound<less_than, 2>();
  test_upper_bound<less_than, 3>();
  test_upper_bound<less_than, 4>();
  test_upper_bound<less_than, 5>();
  test_upper_bound<less_than, 7>();
  test_upper_bound<less_than, 8>();
  test_upper_bound<less_than, 9>();
  test_upper_bound<less_than, 15>();
  test_upper_bound<less_than, 16>();
  test_upper_bound<less_than, 17>();
  test_upper_bound<less_than, 31>();
  test_upper_bound<less_than, 32>();
  test_upper_bound<less_than, 33>();
  test_upper_bound<less_than, 63>();
  test_upper_bound<less_than, 64>();
  test_upper_bound<less_than, 65>();
  test_upper_bound<less_than, 127>();
  test_upper_bound<less_than, 128>();
  test_upper_bound<less_than, 129>();
  test_upper_bound<less_than, 255>();
  test_upper_bound<less_than, 256>();
  test_upper_bound<less_than, 257>();
  test_upper_bound<less_than, 511>();
  test_upper_bound<less_than, 512>();
  test_upper_bound<less_than, 513>();
}

TEST()
{
  using namespace jln::mp;
  using namespace ut::ints;

  test_pack2<upper_bound>();

  ut::same<list<_3>, emp::upper_bound_of_c<seq_0_1_2_3, 2>>();

  test_upper_bounds<0>();
  test_upper_bounds<1>();
  test_upper_bounds<2>();
  test_upper_bounds<3>();
  test_upper_bounds<4>();
  test_upper_bounds<5>();
  test_upper_bounds<7>();
  test_upper_bounds<8>();
  test_upper_bounds<9>();
  test_upper_bounds<15>();
  test_upper_bounds<16>();
  test_upper_bounds<17>();
  test_upper_bounds<31>();
  test_upper_bounds<32>();
  test_upper_bounds<33>();
  test_upper_bounds<255>();
  test_upper_bounds<256>();
  test_upper_bounds<257>();
  test_upper_bounds<511>();
  test_upper_bounds<512>();
  test_upper_bounds<513>();

  test_context<upper_bound_of_c<2>, smp::upper_bound_of_c<2>, 0>()
    .test<list<>>()
    .test<list<>, _0>()
    .test<list<>, _1>()
    .test<list<>, _0, _1>()
    .test<list<>, _0, _1, _2>()
    .test<list<>, _2, _2, _2, _2, _2>()
    .test<list<_3, _3, _3, _3, _3>, _3, _3, _3, _3, _3>()
    .test<list<_3, _3>, _1, _1, _1, _2, _2, _3, _3>()
    .not_invocable<void>()
    ;

  test_context<upper_bound_of_c<2, identity, always<void>>, void, 0>()
    .test<void>()
    .test<void, _0>()
    .test<_3, _0, _1, _2, _3>()
    .not_invocable<_3, _4>()
    .not_invocable<_1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _3, _4>()
    ;

  ut::not_invocable<smp::upper_bound<void, always<void>>, _1>();
  ut::not_invocable<smp::upper_bound<void, bad_function>, _1>();
  ut::not_invocable<smp::upper_bound<void, bad_function, bad_function>, _1>();
  ut::not_invocable<smp::upper_bound<void, bad_function, bad_function, bad_function>, _1>();
  ut::not_invocable<smp::upper_bound_of<_1, bad_function, bad_function>, _1>();
  ut::not_invocable<smp::upper_bound_of<bad_contract, bad_function, bad_function>, _1>();

  ut::not_invocable<smp::upper_bound<void, bad_function>, _1, _1, _1>();
  ut::not_invocable<smp::upper_bound<void, bad_function, bad_function>, _1, _1, _1>();
  ut::not_invocable<smp::upper_bound<void, bad_function, bad_function, bad_function>, _1, _1, _1>();
  ut::not_invocable<smp::upper_bound_of<_1, bad_function, bad_function>, _1, _1, _1>();
  ut::not_invocable<smp::upper_bound_of<bad_contract, bad_function, bad_function>, _1, _1, _1>();
}

TEST_SUITE_END()
