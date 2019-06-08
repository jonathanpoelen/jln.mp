#include "test.hpp"

#include "jln/mp/list/enumerate.hpp"
#include "jln/mp/number/numbers.hpp"
#include "jln/mp/algorithm/size.hpp"

namespace
{
  TEST()
  {
    using namespace jln::mp;

    using _0 = number<0>;
    using _1 = number<1>;
    using _2 = number<2>;
    using _3 = number<3>;
    using _4 = number<4>;

    using a = eager::numbers<>;
    using b = eager::numbers<0>;
    using c = eager::numbers<0, 1>;
    using d = eager::numbers<0, 1, 2>;
    using e = eager::numbers<0, 1, 2, 3>;

    eager::enumerate<_0>() = a();
    eager::enumerate<_1>() = b();
    eager::enumerate<_2>() = c();
    eager::enumerate<_3>() = d();
    eager::enumerate<_4>() = e();

    test_context<enumerate<>, smp::enumerate<>>()
      .test<a, _0>()
      .test<b, _1>()
      .test<c, _2>()
      .test<d, _3>()
      .test<e, _4>()
      .not_invocable<e>()
      .not_invocable<class X>()
      ;
    test_context<enumerate<size<enumerate<>>>, smp::enumerate<smp::size<smp::enumerate<>>>>()
      .test<a, _0>()
      .test<b, _1>()
      .test<c, _2>()
      .test<d, _3>()
      .test<e, _4>()
      .not_invocable<e>()
      .not_invocable<class X>()
      ;
  }
}
