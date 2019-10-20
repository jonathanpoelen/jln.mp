#include "test.hpp"

#include "jln/mp/list/enumerate.hpp"
#include "jln/mp/number/numbers.hpp"
#include "jln/mp/list/size.hpp"

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

    using a = emp::numbers<>;
    using b = emp::numbers<0>;
    using c = emp::numbers<0, 1>;
    using d = emp::numbers<0, 1, 2>;
    using e = emp::numbers<0, 1, 2, 3>;

    emp::enumerate<_0>() = a();
    emp::enumerate<_1>() = b();
    emp::enumerate<_2>() = c();
    emp::enumerate<_3>() = d();
    emp::enumerate<_4>() = e();

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
