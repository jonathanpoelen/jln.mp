#include "test.hpp"
#include "test/numbers.hpp"

#include "jln/mp/smp/list/join.hpp"

TEST_SUITE_BEGIN()

TEST()
{
  using namespace jln::mp;
  using namespace TU::ints;

  class X;
  using a = list<_0, _1, _2>;
  using b = list<_3, _4>;
  using c = list<X>;
  using e = list<>;
  using flat_list = list<_0, _1, _2, _3, _4, X>;

  IS_SAME(flat_list, emp::join<a, b, c>);
  IS_SAME(e, emp::join<list<>, e, e>);

  test_context<join<>, smp::join<>>()
    .test<e>()
    .test<e, e, e>()
    .test<c, c, e>()
    .test<flat_list, a, b, c>()
    .not_invocable<X, e>()
    ;
  test_context<join<join<>>, smp::join<smp::join<>>>()
    .test<flat_list, list<a, b>, list<c>>()
    .test<c, list<c>, e>()
    .not_invocable<c, e>()
    ;

  test_context<join<join<join<>>>, smp::join<smp::join<smp::join<>>>>()
    .test<e, e>()
    .test<e, list<e>, e>()
    .test<c, list<list<c>>, e>()
    .not_invocable<c, e>()
    .not_invocable<list<c>, e>()
    ;
}

TEST_SUITE_END()
