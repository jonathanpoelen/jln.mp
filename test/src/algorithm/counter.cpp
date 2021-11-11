#include "test.hpp"
#include "test/numbers.hpp"

#include "jln/mp/smp/algorithm/counter.hpp"
#include "jln/mp/smp/functional/flip.hpp"

TEST_SUITE_BEGIN()

// counter
TEST()
{
  using namespace jln::mp;
  using namespace ut::ints;

  test_pack2<counter>();

  ut::same<list<list<int, _2>, list<char, _1>, list<short, _2>>,
    emp::counter<list<int, char, int, short, short>>>();

  test_context<counter<>, smp::counter<>>()
    .test<list<>>()
    .test<list<list<int, _1>>, int>()
    .test<list<list<int, _2>>, int, int>()
    .test<list<list<int, _3>>, int, int, int>()
    .test<list<list<int, _1>, list<char, _1>>, int, char>()
    .test<list<list<int, _1>, list<char, _1>, list<short, _1>>, int, char, short>()
    .test<list<list<int, _2>, list<char, _1>, list<short, _2>, list<float, _1>>,
        int, char, short, int, short, float>()
    ;

  ut::not_invocable<smp::counter<bad_function>, _1, _1, _1, _1>();
}

// counter_wrapped_with
TEST()
{
  using namespace jln::mp;
  using namespace ut::ints;

  test_pack2<counter_wrapped_with>();
  test_pack2<counter_wrapped_with, listify>();

  ut::same<list<list<_2, int>, list<_1, char>, list<_2, short>>,
    emp::counter_wrapped_with<list<int, char, int, short, short>, flip<>>>();

  test_context<counter_wrapped_with<flip<>>, smp::counter_wrapped_with<smp::flip<>>>()
    .test<list<>>()
    .test<list<list<_1, int>>, int>()
    .test<list<list<_2, int>>, int, int>()
    .test<list<list<_3, int>>, int, int, int>()
    .test<list<list<_1, int>, list<_1, char>>, int, char>()
    .test<list<list<_1, int>, list<_1, char>, list<_1, short>>, int, char, short>()
    .test<list<list<_2, int>, list<_1, char>, list<_2, short>, list<_1, float>>,
        int, char, short, int, short, float>()
    ;

  ut::not_invocable<smp::counter_wrapped_with<bad_function>, _1, _1, _1, _1>();
  ut::not_invocable<smp::counter_wrapped_with<listify, bad_function>, _1, _1, _1, _1>();
  ut::not_invocable<smp::counter_wrapped_with<bad_function, bad_function>, _1, _1, _1, _1>();
}

TEST_SUITE_END()
