#include "test/test_case.hpp"

#include "jln/mp/functional/is_invovable.hpp"

namespace
{
  struct A;
  struct B { template<class> using f = int; };
  struct C { template<int> using f = int; };
  struct D { template<class x> using f = typename x::type; };
  struct E { template<class x> static constexpr int f = x::value; };
  struct F { template<class...> using f = int; };
  struct G { template<class...> static constexpr int f = 1; };
  struct H { template<int...> using f = int; };
  struct I { template<int...> static constexpr int f = 1; };

  struct t { using type = int; };
  struct v { static constexpr int value = 1; };

  template<template<class...> class func, class a, class b, class c, class d, class e, class f, class g, class h, class i>
  void is_invoke_empty(a, b, c, d, e, f, g, h, i)
  {
    a{} = typename func<A>::template f<>{};
    b{} = typename func<B>::template f<>{};
    c{} = typename func<C>::template f<>{};
    d{} = typename func<D>::template f<>{};
    e{} = typename func<E>::template f<>{};
    f{} = typename func<F>::template f<>{};
    g{} = typename func<G>::template f<>{};
    h{} = typename func<H>::template f<>{};
    i{} = typename func<I>::template f<>{};
  }

  template<template<class...> class func, class a, class b, class c, class d, class e, class f, class g, class h, class i>
  void is_invoke_int(a, b, c, d, e, f, g, h, i)
  {
    a{} = typename func<A>::template f<int>{};
    b{} = typename func<B>::template f<int>{};
    c{} = typename func<C>::template f<int>{};
    d{} = typename func<D>::template f<int>{};
    e{} = typename func<E>::template f<int>{};
    f{} = typename func<F>::template f<int>{};
    g{} = typename func<G>::template f<int>{};
    h{} = typename func<H>::template f<int>{};
    i{} = typename func<I>::template f<int>{};
  }

  template<template<class...> class func, class a, class b, class c, class d, class e, class f, class g, class h, class i>
  void is_invoke_t(a, b, c, d, e, f, g, h, i)
  {
    a{} = typename func<A>::template f<t>{};
    b{} = typename func<B>::template f<t>{};
    c{} = typename func<C>::template f<t>{};
    d{} = typename func<D>::template f<t>{};
    e{} = typename func<E>::template f<t>{};
    f{} = typename func<F>::template f<t>{};
    g{} = typename func<G>::template f<t>{};
    h{} = typename func<H>::template f<t>{};
    i{} = typename func<I>::template f<t>{};
  }

  template<template<class...> class func, class a, class b, class c, class d, class e, class f, class g, class h, class i>
  void is_invoke_v(a, b, c, d, e, f, g, h, i)
  {
    a{} = typename func<A>::template f<v>{};
    b{} = typename func<B>::template f<v>{};
    c{} = typename func<C>::template f<v>{};
    d{} = typename func<D>::template f<v>{};
    e{} = typename func<E>::template f<v>{};
    f{} = typename func<F>::template f<v>{};
    g{} = typename func<G>::template f<v>{};
    h{} = typename func<H>::template f<v>{};
    i{} = typename func<I>::template f<v>{};
  }

  template<template<class...> class func, class a, class b, class c, class d, class e, class f, class g, class h, class i>
  void is_invoke_1(a, b, c, d, e, f, g, h, i)
  {
    a{} = typename func<A>::template f<1>{};
    b{} = typename func<B>::template f<1>{};
    c{} = typename func<C>::template f<1>{};
    d{} = typename func<D>::template f<1>{};
    e{} = typename func<E>::template f<1>{};
    f{} = typename func<F>::template f<1>{};
    g{} = typename func<G>::template f<1>{};
    h{} = typename func<H>::template f<1>{};
    i{} = typename func<I>::template f<1>{};
  }

  TEST()
  {
    using namespace jln::mp;

    auto y = true_{};
    auto n = false_{};

    //                            A  B  C  D  E  F  G  H  I
    is_invoke_empty<is_invocable>(n, n, n, n, n, y, n, y, n);
    is_invoke_int<  is_invocable>(n, y, n, n, n, y, n, n, n);
    is_invoke_t<    is_invocable>(n, y, n, y, n, y, n, n, n);
    is_invoke_v<    is_invocable>(n, y, n, n, n, y, n, n, n);
  }
}
