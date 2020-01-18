#include "test.hpp"
#include "test/numbers.hpp"

#include "jln/mp/algorithm/sort.hpp"
#include "jln/mp/smp/number/operators.hpp"

TEST_SUITE_BEGIN()

template<long... ints>
using rints = jln::mp::detail::rlist<jln::mp::number<ints>...>;

TEST()
{
  using namespace jln::mp;
  using namespace ut::ints;
  using jln::mp::detail::rlist;

  ut::same<list<>, call<sort<>>>();

  ut::same<seq_0, call<sort<>, _0>>();

  ut::same<seq_0_1, call<sort<>, _0, _1>>();
  ut::same<seq_0_1, call<sort<>, _1, _0>>();

  ut::same<rints<0, 1, 2>, call<sort<>, _0, _1, _2>>();
  ut::same<rints<0, 1, 2>, call<sort<>, _1, _0, _2>>();
  ut::same<rints<0, 1, 2>, call<sort<>, _0, _2, _1>>();
  ut::same<rints<0, 1, 2>, call<sort<>, _1, _2, _0>>();
  ut::same<rints<0, 1, 2>, call<sort<>, _2, _0, _1>>();
  ut::same<rints<0, 1, 2>, call<sort<>, _2, _1, _0>>();

  ut::same<rlist<rints<0, 1>, _2, rints<3>>, call<sort<>, _0, _1, _2, _3>>();
  ut::same<rlist<rints<0, 1>, _2, rints<3>>, call<sort<>, _0, _2, _1, _3>>();
  ut::same<rlist<rints<0, 1>, _2, rints<3>>, call<sort<>, _1, _0, _2, _3>>();
  ut::same<rlist<rints<0, 1>, _2, rints<3>>, call<sort<>, _1, _2, _0, _3>>();
  ut::same<rlist<rints<0, 1>, _2, rints<3>>, call<sort<>, _2, _0, _1, _3>>();
  ut::same<rlist<rints<0, 1>, _2, rints<3>>, call<sort<>, _2, _1, _0, _3>>();
  ut::same<rlist<rints<0, 1>, _2, rints<3>>, call<sort<>, _0, _1, _3, _2>>();
  ut::same<rlist<rints<0, 1>, _2, rints<3>>, call<sort<>, _0, _2, _3, _1>>();
  ut::same<rlist<rints<0, 1>, _2, rints<3>>, call<sort<>, _1, _0, _3, _2>>();
  ut::same<rlist<rints<0, 1>, _2, rints<3>>, call<sort<>, _1, _2, _3, _0>>();
  ut::same<rlist<rints<0, 1>, _2, rints<3>>, call<sort<>, _2, _0, _3, _1>>();
  ut::same<rlist<rints<0, 1>, _2, rints<3>>, call<sort<>, _2, _1, _3, _0>>();
  ut::same<rlist<rints<0, 1>, _2, rints<3>>, call<sort<>, _0, _3, _1, _2>>();
  ut::same<rlist<rints<0, 1>, _2, rints<3>>, call<sort<>, _0, _3, _2, _1>>();
  ut::same<rlist<rints<0, 1>, _2, rints<3>>, call<sort<>, _1, _3, _0, _2>>();
  ut::same<rlist<rints<0, 1>, _2, rints<3>>, call<sort<>, _1, _3, _2, _0>>();
  ut::same<rlist<rints<0, 1>, _2, rints<3>>, call<sort<>, _2, _3, _0, _1>>();
  ut::same<rlist<rints<0, 1>, _2, rints<3>>, call<sort<>, _2, _3, _1, _0>>();
  ut::same<rlist<rints<0, 1>, _2, rints<3>>, call<sort<>, _3, _0, _1, _2>>();
  ut::same<rlist<rints<0, 1>, _2, rints<3>>, call<sort<>, _3, _0, _2, _1>>();
  ut::same<rlist<rints<0, 1>, _2, rints<3>>, call<sort<>, _3, _1, _0, _2>>();
  ut::same<rlist<rints<0, 1>, _2, rints<3>>, call<sort<>, _3, _1, _2, _0>>();
  ut::same<rlist<rints<0, 1>, _2, rints<3>>, call<sort<>, _3, _2, _0, _1>>();
  ut::same<rlist<rints<0, 1>, _2, rints<3>>, call<sort<>, _3, _2, _1, _0>>();

  ut::same<rlist<rints<0, 1>, _2, rints<3, 4>>, call<sort<>, _0, _1, _2, _3, _4>>();
  ut::same<rlist<rints<0, 1>, _2, rints<3, 4>>, call<sort<>, _0, _2, _1, _3, _4>>();
  ut::same<rlist<rints<0, 1>, _2, rints<3, 4>>, call<sort<>, _1, _0, _2, _3, _4>>();
  ut::same<rlist<rints<0, 1>, _2, rints<3, 4>>, call<sort<>, _1, _2, _0, _3, _4>>();
  ut::same<rlist<rints<0, 1>, _2, rints<3, 4>>, call<sort<>, _2, _0, _1, _3, _4>>();
  ut::same<rlist<rints<0, 1>, _2, rints<3, 4>>, call<sort<>, _2, _1, _0, _3, _4>>();
  ut::same<rlist<rints<0, 1>, _2, rints<3, 4>>, call<sort<>, _0, _1, _3, _2, _4>>();
  ut::same<rlist<rints<0, 1>, _2, rints<3, 4>>, call<sort<>, _0, _2, _3, _1, _4>>();
  ut::same<rlist<rints<0, 1>, _2, rints<3, 4>>, call<sort<>, _1, _0, _3, _2, _4>>();
  ut::same<rlist<rints<0, 1>, _2, rints<3, 4>>, call<sort<>, _1, _2, _3, _0, _4>>();
  ut::same<rlist<rints<0, 1>, _2, rints<3, 4>>, call<sort<>, _2, _0, _3, _1, _4>>();
  ut::same<rlist<rints<0, 1>, _2, rints<3, 4>>, call<sort<>, _2, _1, _3, _0, _4>>();
  ut::same<rlist<rints<0, 1>, _2, rints<3, 4>>, call<sort<>, _0, _3, _1, _2, _4>>();
  ut::same<rlist<rints<0, 1>, _2, rints<3, 4>>, call<sort<>, _0, _3, _2, _1, _4>>();
  ut::same<rlist<rints<0, 1>, _2, rints<3, 4>>, call<sort<>, _1, _3, _0, _2, _4>>();
  ut::same<rlist<rints<0, 1>, _2, rints<3, 4>>, call<sort<>, _1, _3, _2, _0, _4>>();
  ut::same<rlist<rints<0, 1>, _2, rints<3, 4>>, call<sort<>, _2, _3, _0, _1, _4>>();
  ut::same<rlist<rints<0, 1>, _2, rints<3, 4>>, call<sort<>, _2, _3, _1, _0, _4>>();
  ut::same<rlist<rints<0, 1>, _2, rints<3, 4>>, call<sort<>, _3, _0, _1, _2, _4>>();
  ut::same<rlist<rints<0, 1>, _2, rints<3, 4>>, call<sort<>, _3, _0, _2, _1, _4>>();
  ut::same<rlist<rints<0, 1>, _2, rints<3, 4>>, call<sort<>, _3, _1, _0, _2, _4>>();
  ut::same<rlist<rints<0, 1>, _2, rints<3, 4>>, call<sort<>, _3, _1, _2, _0, _4>>();
  ut::same<rlist<rints<0, 1>, _2, rints<3, 4>>, call<sort<>, _3, _2, _0, _1, _4>>();
  ut::same<rlist<rints<0, 1>, _2, rints<3, 4>>, call<sort<>, _3, _2, _1, _0, _4>>();
  ut::same<rlist<rints<0, 1>, _2, rints<3, 4>>, call<sort<>, _0, _1, _2, _4, _3>>();
  ut::same<rlist<rints<0, 1>, _2, rints<3, 4>>, call<sort<>, _0, _2, _1, _4, _3>>();
  ut::same<rlist<rints<0, 1>, _2, rints<3, 4>>, call<sort<>, _1, _0, _2, _4, _3>>();
  ut::same<rlist<rints<0, 1>, _2, rints<3, 4>>, call<sort<>, _1, _2, _0, _4, _3>>();
  ut::same<rlist<rints<0, 1>, _2, rints<3, 4>>, call<sort<>, _2, _0, _1, _4, _3>>();
  ut::same<rlist<rints<0, 1>, _2, rints<3, 4>>, call<sort<>, _2, _1, _0, _4, _3>>();
  ut::same<rlist<rints<0, 1>, _2, rints<3, 4>>, call<sort<>, _0, _1, _3, _4, _2>>();
  ut::same<rlist<rints<0, 1>, _2, rints<3, 4>>, call<sort<>, _0, _2, _3, _4, _1>>();
  ut::same<rlist<rints<0, 1>, _2, rints<3, 4>>, call<sort<>, _1, _0, _3, _4, _2>>();
  ut::same<rlist<rints<0, 1>, _2, rints<3, 4>>, call<sort<>, _1, _2, _3, _4, _0>>();
  ut::same<rlist<rints<0, 1>, _2, rints<3, 4>>, call<sort<>, _2, _0, _3, _4, _1>>();
  ut::same<rlist<rints<0, 1>, _2, rints<3, 4>>, call<sort<>, _2, _1, _3, _4, _0>>();
  ut::same<rlist<rints<0, 1>, _2, rints<3, 4>>, call<sort<>, _0, _3, _1, _4, _2>>();
  ut::same<rlist<rints<0, 1>, _2, rints<3, 4>>, call<sort<>, _0, _3, _2, _4, _1>>();
  ut::same<rlist<rints<0, 1>, _2, rints<3, 4>>, call<sort<>, _1, _3, _0, _4, _2>>();
  ut::same<rlist<rints<0, 1>, _2, rints<3, 4>>, call<sort<>, _1, _3, _2, _4, _0>>();
  ut::same<rlist<rints<0, 1>, _2, rints<3, 4>>, call<sort<>, _2, _3, _0, _4, _1>>();
  ut::same<rlist<rints<0, 1>, _2, rints<3, 4>>, call<sort<>, _2, _3, _1, _4, _0>>();
  ut::same<rlist<rints<0, 1>, _2, rints<3, 4>>, call<sort<>, _3, _0, _1, _4, _2>>();
  ut::same<rlist<rints<0, 1>, _2, rints<3, 4>>, call<sort<>, _3, _0, _2, _4, _1>>();
  ut::same<rlist<rints<0, 1>, _2, rints<3, 4>>, call<sort<>, _3, _1, _0, _4, _2>>();
  ut::same<rlist<rints<0, 1>, _2, rints<3, 4>>, call<sort<>, _3, _1, _2, _4, _0>>();
  ut::same<rlist<rints<0, 1>, _2, rints<3, 4>>, call<sort<>, _3, _2, _0, _4, _1>>();
  ut::same<rlist<rints<0, 1>, _2, rints<3, 4>>, call<sort<>, _3, _2, _1, _4, _0>>();
  ut::same<rlist<rints<0, 1>, _2, rints<3, 4>>, call<sort<>, _0, _1, _4, _2, _3>>();
  ut::same<rlist<rints<0, 1>, _2, rints<3, 4>>, call<sort<>, _0, _2, _4, _1, _3>>();
  ut::same<rlist<rints<0, 1>, _2, rints<3, 4>>, call<sort<>, _1, _0, _4, _2, _3>>();
  ut::same<rlist<rints<0, 1>, _2, rints<3, 4>>, call<sort<>, _1, _2, _4, _0, _3>>();
  ut::same<rlist<rints<0, 1>, _2, rints<3, 4>>, call<sort<>, _2, _0, _4, _1, _3>>();
  ut::same<rlist<rints<0, 1>, _2, rints<3, 4>>, call<sort<>, _2, _1, _4, _0, _3>>();
  ut::same<rlist<rints<0, 1>, _2, rints<3, 4>>, call<sort<>, _0, _1, _4, _3, _2>>();
  ut::same<rlist<rints<0, 1>, _2, rints<3, 4>>, call<sort<>, _0, _2, _4, _3, _1>>();
  ut::same<rlist<rints<0, 1>, _2, rints<3, 4>>, call<sort<>, _1, _0, _4, _3, _2>>();
  ut::same<rlist<rints<0, 1>, _2, rints<3, 4>>, call<sort<>, _1, _2, _4, _3, _0>>();
  ut::same<rlist<rints<0, 1>, _2, rints<3, 4>>, call<sort<>, _2, _0, _4, _3, _1>>();
  ut::same<rlist<rints<0, 1>, _2, rints<3, 4>>, call<sort<>, _2, _1, _4, _3, _0>>();
  ut::same<rlist<rints<0, 1>, _2, rints<3, 4>>, call<sort<>, _0, _3, _4, _1, _2>>();
  ut::same<rlist<rints<0, 1>, _2, rints<3, 4>>, call<sort<>, _0, _3, _4, _2, _1>>();
  ut::same<rlist<rints<0, 1>, _2, rints<3, 4>>, call<sort<>, _1, _3, _4, _0, _2>>();
  ut::same<rlist<rints<0, 1>, _2, rints<3, 4>>, call<sort<>, _1, _3, _4, _2, _0>>();
  ut::same<rlist<rints<0, 1>, _2, rints<3, 4>>, call<sort<>, _2, _3, _4, _0, _1>>();
  ut::same<rlist<rints<0, 1>, _2, rints<3, 4>>, call<sort<>, _2, _3, _4, _1, _0>>();
  ut::same<rlist<rints<0, 1>, _2, rints<3, 4>>, call<sort<>, _3, _0, _4, _1, _2>>();
  ut::same<rlist<rints<0, 1>, _2, rints<3, 4>>, call<sort<>, _3, _0, _4, _2, _1>>();
  ut::same<rlist<rints<0, 1>, _2, rints<3, 4>>, call<sort<>, _3, _1, _4, _0, _2>>();
  ut::same<rlist<rints<0, 1>, _2, rints<3, 4>>, call<sort<>, _3, _1, _4, _2, _0>>();
  ut::same<rlist<rints<0, 1>, _2, rints<3, 4>>, call<sort<>, _3, _2, _4, _0, _1>>();
  ut::same<rlist<rints<0, 1>, _2, rints<3, 4>>, call<sort<>, _3, _2, _4, _1, _0>>();
  ut::same<rlist<rints<0, 1>, _2, rints<3, 4>>, call<sort<>, _0, _4, _1, _2, _3>>();
  ut::same<rlist<rints<0, 1>, _2, rints<3, 4>>, call<sort<>, _0, _4, _2, _1, _3>>();
  ut::same<rlist<rints<0, 1>, _2, rints<3, 4>>, call<sort<>, _1, _4, _0, _2, _3>>();
  ut::same<rlist<rints<0, 1>, _2, rints<3, 4>>, call<sort<>, _1, _4, _2, _0, _3>>();
  ut::same<rlist<rints<0, 1>, _2, rints<3, 4>>, call<sort<>, _2, _4, _0, _1, _3>>();
  ut::same<rlist<rints<0, 1>, _2, rints<3, 4>>, call<sort<>, _2, _4, _1, _0, _3>>();
  ut::same<rlist<rints<0, 1>, _2, rints<3, 4>>, call<sort<>, _0, _4, _1, _3, _2>>();
  ut::same<rlist<rints<0, 1>, _2, rints<3, 4>>, call<sort<>, _0, _4, _2, _3, _1>>();
  ut::same<rlist<rints<0, 1>, _2, rints<3, 4>>, call<sort<>, _1, _4, _0, _3, _2>>();
  ut::same<rlist<rints<0, 1>, _2, rints<3, 4>>, call<sort<>, _1, _4, _2, _3, _0>>();
  ut::same<rlist<rints<0, 1>, _2, rints<3, 4>>, call<sort<>, _2, _4, _0, _3, _1>>();
  ut::same<rlist<rints<0, 1>, _2, rints<3, 4>>, call<sort<>, _2, _4, _1, _3, _0>>();
  ut::same<rlist<rints<0, 1>, _2, rints<3, 4>>, call<sort<>, _0, _4, _3, _1, _2>>();
  ut::same<rlist<rints<0, 1>, _2, rints<3, 4>>, call<sort<>, _0, _4, _3, _2, _1>>();
  ut::same<rlist<rints<0, 1>, _2, rints<3, 4>>, call<sort<>, _1, _4, _3, _0, _2>>();
  ut::same<rlist<rints<0, 1>, _2, rints<3, 4>>, call<sort<>, _1, _4, _3, _2, _0>>();
  ut::same<rlist<rints<0, 1>, _2, rints<3, 4>>, call<sort<>, _2, _4, _3, _0, _1>>();
  ut::same<rlist<rints<0, 1>, _2, rints<3, 4>>, call<sort<>, _2, _4, _3, _1, _0>>();
  ut::same<rlist<rints<0, 1>, _2, rints<3, 4>>, call<sort<>, _3, _4, _0, _1, _2>>();
  ut::same<rlist<rints<0, 1>, _2, rints<3, 4>>, call<sort<>, _3, _4, _0, _2, _1>>();
  ut::same<rlist<rints<0, 1>, _2, rints<3, 4>>, call<sort<>, _3, _4, _1, _0, _2>>();
  ut::same<rlist<rints<0, 1>, _2, rints<3, 4>>, call<sort<>, _3, _4, _1, _2, _0>>();
  ut::same<rlist<rints<0, 1>, _2, rints<3, 4>>, call<sort<>, _3, _4, _2, _0, _1>>();
  ut::same<rlist<rints<0, 1>, _2, rints<3, 4>>, call<sort<>, _3, _4, _2, _1, _0>>();
  ut::same<rlist<rints<0, 1>, _2, rints<3, 4>>, call<sort<>, _0, _4, _1, _2, _3>>();
  ut::same<rlist<rints<0, 1>, _2, rints<3, 4>>, call<sort<>, _0, _4, _2, _1, _3>>();
  ut::same<rlist<rints<0, 1>, _2, rints<3, 4>>, call<sort<>, _1, _4, _0, _2, _3>>();
  ut::same<rlist<rints<0, 1>, _2, rints<3, 4>>, call<sort<>, _1, _4, _2, _0, _3>>();
  ut::same<rlist<rints<0, 1>, _2, rints<3, 4>>, call<sort<>, _2, _4, _0, _1, _3>>();
  ut::same<rlist<rints<0, 1>, _2, rints<3, 4>>, call<sort<>, _2, _4, _1, _0, _3>>();
  ut::same<rlist<rints<0, 1>, _2, rints<3, 4>>, call<sort<>, _0, _4, _1, _3, _2>>();
  ut::same<rlist<rints<0, 1>, _2, rints<3, 4>>, call<sort<>, _0, _4, _2, _3, _1>>();
  ut::same<rlist<rints<0, 1>, _2, rints<3, 4>>, call<sort<>, _1, _4, _0, _3, _2>>();
  ut::same<rlist<rints<0, 1>, _2, rints<3, 4>>, call<sort<>, _1, _4, _2, _3, _0>>();
  ut::same<rlist<rints<0, 1>, _2, rints<3, 4>>, call<sort<>, _2, _4, _0, _3, _1>>();
  ut::same<rlist<rints<0, 1>, _2, rints<3, 4>>, call<sort<>, _2, _4, _1, _3, _0>>();
  ut::same<rlist<rints<0, 1>, _2, rints<3, 4>>, call<sort<>, _0, _4, _3, _1, _2>>();
  ut::same<rlist<rints<0, 1>, _2, rints<3, 4>>, call<sort<>, _0, _4, _3, _2, _1>>();
  ut::same<rlist<rints<0, 1>, _2, rints<3, 4>>, call<sort<>, _1, _4, _3, _0, _2>>();
  ut::same<rlist<rints<0, 1>, _2, rints<3, 4>>, call<sort<>, _1, _4, _3, _2, _0>>();
  ut::same<rlist<rints<0, 1>, _2, rints<3, 4>>, call<sort<>, _2, _4, _3, _0, _1>>();
  ut::same<rlist<rints<0, 1>, _2, rints<3, 4>>, call<sort<>, _2, _4, _3, _1, _0>>();
  ut::same<rlist<rints<0, 1>, _2, rints<3, 4>>, call<sort<>, _3, _4, _0, _1, _2>>();
  ut::same<rlist<rints<0, 1>, _2, rints<3, 4>>, call<sort<>, _3, _4, _0, _2, _1>>();
  ut::same<rlist<rints<0, 1>, _2, rints<3, 4>>, call<sort<>, _3, _4, _1, _0, _2>>();
  ut::same<rlist<rints<0, 1>, _2, rints<3, 4>>, call<sort<>, _3, _4, _1, _2, _0>>();
  ut::same<rlist<rints<0, 1>, _2, rints<3, 4>>, call<sort<>, _3, _4, _2, _0, _1>>();
  ut::same<rlist<rints<0, 1>, _2, rints<3, 4>>, call<sort<>, _3, _4, _2, _1, _0>>();
  ut::same<rlist<rints<0, 1>, _2, rints<3, 4>>, call<sort<>, _4, _0, _1, _2, _3>>();
  ut::same<rlist<rints<0, 1>, _2, rints<3, 4>>, call<sort<>, _4, _0, _2, _1, _3>>();
  ut::same<rlist<rints<0, 1>, _2, rints<3, 4>>, call<sort<>, _4, _1, _0, _2, _3>>();
  ut::same<rlist<rints<0, 1>, _2, rints<3, 4>>, call<sort<>, _4, _1, _2, _0, _3>>();
  ut::same<rlist<rints<0, 1>, _2, rints<3, 4>>, call<sort<>, _4, _2, _0, _1, _3>>();
  ut::same<rlist<rints<0, 1>, _2, rints<3, 4>>, call<sort<>, _4, _2, _1, _0, _3>>();
  ut::same<rlist<rints<0, 1>, _2, rints<3, 4>>, call<sort<>, _4, _0, _1, _3, _2>>();
  ut::same<rlist<rints<0, 1>, _2, rints<3, 4>>, call<sort<>, _4, _0, _2, _3, _1>>();
  ut::same<rlist<rints<0, 1>, _2, rints<3, 4>>, call<sort<>, _4, _1, _0, _3, _2>>();
  ut::same<rlist<rints<0, 1>, _2, rints<3, 4>>, call<sort<>, _4, _1, _2, _3, _0>>();
  ut::same<rlist<rints<0, 1>, _2, rints<3, 4>>, call<sort<>, _4, _2, _0, _3, _1>>();
  ut::same<rlist<rints<0, 1>, _2, rints<3, 4>>, call<sort<>, _4, _2, _1, _3, _0>>();
  ut::same<rlist<rints<0, 1>, _2, rints<3, 4>>, call<sort<>, _4, _0, _3, _1, _2>>();
  ut::same<rlist<rints<0, 1>, _2, rints<3, 4>>, call<sort<>, _4, _0, _3, _2, _1>>();
  ut::same<rlist<rints<0, 1>, _2, rints<3, 4>>, call<sort<>, _4, _1, _3, _0, _2>>();
  ut::same<rlist<rints<0, 1>, _2, rints<3, 4>>, call<sort<>, _4, _1, _3, _2, _0>>();
  ut::same<rlist<rints<0, 1>, _2, rints<3, 4>>, call<sort<>, _4, _2, _3, _0, _1>>();
  ut::same<rlist<rints<0, 1>, _2, rints<3, 4>>, call<sort<>, _4, _2, _3, _1, _0>>();
  ut::same<rlist<rints<0, 1>, _2, rints<3, 4>>, call<sort<>, _4, _3, _0, _1, _2>>();
  ut::same<rlist<rints<0, 1>, _2, rints<3, 4>>, call<sort<>, _4, _3, _0, _2, _1>>();
  ut::same<rlist<rints<0, 1>, _2, rints<3, 4>>, call<sort<>, _4, _3, _1, _0, _2>>();
  ut::same<rlist<rints<0, 1>, _2, rints<3, 4>>, call<sort<>, _4, _3, _1, _2, _0>>();
  ut::same<rlist<rints<0, 1>, _2, rints<3, 4>>, call<sort<>, _4, _3, _2, _0, _1>>();
  ut::same<rlist<rints<0, 1>, _2, rints<3, 4>>, call<sort<>, _4, _3, _2, _1, _0>>();


  // test_pack<sort, listify>()
  //   .test_unary()
  //   ;
  //
  // ut::same<_1, emp::sort<seq_0_1_2_3_4_5_6_7_8_9>>();
  //
  // test_context<sort<>, smp::sort<>>()
  //   .test<_1>()
  //   .test<_1, _0>()
  //   .test<_1, _0, _0>()
  //   .test<_1, _0, _1>()
  //   .test<_0, _1, _0>()
  //   .test<_1, _0, _1, _2>()
  //   .test<_0, _1, _0, _2>()
  //   .test<_0, _0, _2, _1>()
  //   .test<_1, _0, _1, _2, _3, _4>()
  //   .test<_0, _0, _1, _2, _4, _3>()
  //   .test<_1, bad_number>()
  //   .not_invocable<bad_number, bad_number>()
  //   .not_invocable<bad_number, bad_number, bad_number>()
  //   ;
  //
  // test_context<smp::sort<na>, void>()
  //   .test<_1>()
  //   .not_invocable<_1, _2>()
  //   ;

}

TEST_SUITE_END()
