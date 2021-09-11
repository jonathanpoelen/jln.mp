#include "test.hpp"
#include "test/numbers.hpp"

#include "jln/mp/smp/algorithm/counter.hpp"

TEST_SUITE_BEGIN()

TEST()
{
  using namespace jln::mp;
  using namespace ut::ints;

  test_pack2<counter>();

  ut::same<list<list<_2, int>, list<_1, char>, list<_2, short>>,
    emp::counter<list<int, char, int, short, short>>>();

  test_context<counter<>, smp::counter<>>()
    .test<list<>>()
    .test<list<list<_1, int>>, int>()
    .test<list<list<_2, int>>, int, int>()
    .test<list<list<_3, int>>, int, int, int>()
    .test<list<list<_1, int>, list<_1, char>>, int, char>()
    .test<list<list<_1, int>, list<_1, char>, list<_1, short>>, int, char, short>()
    .test<list<list<_2, int>, list<_1, char>, list<_2, short>, list<_1, float>>,
        int, char, short, int, short, float>()
    ;

  ut::not_invocable<smp::counter<bad_function>, _1, _1, _1, _1>();
}

TEST_SUITE_END()
