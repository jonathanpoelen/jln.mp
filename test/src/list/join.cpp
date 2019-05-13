#include "test.hpp"

#include "jln/mp/functional/call.hpp"
#include "jln/mp/list/join.hpp"
#include "jln/mp/sfinae/sfinae.hpp"

namespace
{
  TEST()
  {
    using namespace jln::mp;

    auto test = [](auto a, auto sa, auto r, auto... args){
      IS_INVOCABLE_V(a, args...);
      IS_INVOCABLE_V(sa, args...);
      r = call<decltype(a), decltype(args)...>();
      r = call<decltype(sa), decltype(args)...>();
      // r = call<sfinae<decltype(a)>, decltype(args)...>();
      r = call<sfinae<decltype(sa)>, decltype(args)...>();
    };

    class X;
    using a = list<int, float, double>;
    using b = list<char, unsigned>;
    using c = list<X>;
    using e = list<>;
    using flat_list = list<int, float, double, char, unsigned, X>;
    eager::join<a, b, c>() = flat_list();
    eager::join<list<>, e, e>() = e();

    test(join<>(), smp::join<>(), e());
    test(join<>(), smp::join<>(), c(), c(), e());
    test(join<join<>>(), smp::join<smp::join<>>(), flat_list(), list<a, b>(), list<c>());
    test(join<join<>>(), smp::join<smp::join<>>(), c(), list<c>(), e());
    test(join<join<join<>>>(), smp::join<smp::join<smp::join<>>>(), e(), e());
    test(join<join<join<>>>(), smp::join<smp::join<smp::join<>>>(), e(), list<e>(), e());

    IS_INVOCABLE(smp::join<>, c, e);
    not IS_INVOCABLE(smp::join<>, X, e);
    not IS_INVOCABLE(smp::join<smp::join<>>, c, e);
                // call<smp::join<smp::join<>>, c, e>() = 1; BUG gcc
         // always<call<smp::join<smp::join<>>, c, e>>() = 1;
    // smp::join<smp::join<>>::f<list<c>, e>() = 1;
    IS_INVOCABLE(smp::join<smp::join<>>, list<c>, e);
    not IS_INVOCABLE(smp::join<smp::join<smp::join<>>>, c, e);
    not IS_INVOCABLE(smp::join<smp::join<smp::join<>>>, list<c>, e);
    IS_INVOCABLE(smp::join<smp::join<smp::join<>>>, list<list<c>>, e);
    not IS_INVOCABLE(sfinae<join<join<join<>>>>, list<c>, e);
    IS_INVOCABLE(sfinae<join<>>, list<list<c>>, e);
    // IS_INVOCABLE(sfinae<join<join<>>>, list<list<c>>, e);
    // IS_INVOCABLE(sfinae<join<join<join<>>>>, list<list<c>>, e);
  }
}
