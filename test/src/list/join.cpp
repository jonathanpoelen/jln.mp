#include "test.hpp"

#include "jln/mp/functional/sfinae.hpp"
#include "jln/mp/functional/call.hpp"
#include "jln/mp/list/join.hpp"

namespace
{
  TEST()
  {
    using namespace jln::mp;

    class X;
    using a = list<int, float, double>;
    using b = list<char, unsigned>;
    using c = list<X>;
    using e = list<>;
    using flat_list = list<int, float, double, char, unsigned, X>;
    eager::join<a, b, c>() = flat_list();
    eager::join<list<>, e, e>() = e();

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
}
