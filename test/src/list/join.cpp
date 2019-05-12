#include "test.hpp"

#include "jln/mp/functional/call.hpp"
#include "jln/mp/list/join.hpp"

namespace
{
  TEST()
  {
    using namespace jln::mp;

    using a = list<int, float, double>;
    using b = list<char, unsigned>;
    using c = list<class X>;
    using flat_list = list<int, float, double, char, unsigned, class X>;
    eager::join<a, b, c>{} = flat_list{};
    eager::join<list<>, list<>, list<>>{} = list<>{};
    call<join<>, list<class X>, list<>>{} = list<class X>{};
    call<join<join<>>, list<a, b>, list<c>>{} = flat_list{};
    call<join<join<>>, list<list<class X>>, list<>>{} = list<class X>{};
    call<join<join<join<>>>, list<>>{} = list<>{};
    call<join<join<join<>>>, list<list<>>, list<>>{} = list<>{};

    call<smp::join<>, list<class X>, list<>>{} = list<class X>{};
    call<smp::join<smp::join<>>, list<a, b>, list<c>>{} = flat_list{};
    call<smp::join<smp::join<>>, list<list<class X>>, list<>>{} = list<class X>{};
    call<smp::join<smp::join<smp::join<>>>, list<>>{} = list<>{};
    call<smp::join<smp::join<smp::join<>>>, list<list<>>, list<>>{} = list<>{};

    IS_INVOCABLE(smp::join<>, list<class X>, list<>);
    not IS_INVOCABLE(smp::join<>, class X, list<>);
    not IS_INVOCABLE(smp::join<smp::join<>>, list<class X>, list<>);
                // call<smp::join<smp::join<>>, list<class X>, list<>>{} = 1;
         // always<call<smp::join<smp::join<>>, list<class X>, list<>>>{} = 1;
    // smp::join<smp::join<>>::f<list<list<class X>>, list<>>{} = 1;
    IS_INVOCABLE(smp::join<smp::join<>>, list<list<class X>>, list<>);
    not IS_INVOCABLE(smp::join<smp::join<smp::join<>>>, list<class X>, list<>);
    not IS_INVOCABLE(smp::join<smp::join<smp::join<>>>, list<list<class X>>, list<>);
    IS_INVOCABLE(smp::join<smp::join<smp::join<>>>, list<list<list<class X>>>, list<>);
  }
}
