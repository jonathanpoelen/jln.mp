#pragma once

#include "../assume.hpp"
#include "../../functional/each.hpp"

/// \cond
namespace jln::mp::detail
{
  template<int>
  struct _smp_each_select;
}
/// \endcond

namespace jln::mp::smp
{
  template <class... Fs>
  using each = typename detail::_smp_each_select<detail::min(5, sizeof...(Fs))>
    ::template f<Fs...>;
}


#include "../../functional/monadic.hpp"

/// \cond
namespace jln::mp::detail
{
  template<template<class> class sfinae, class... Fs>
  struct _sfinae<sfinae, each<Fs...>>
  {
    using type = smp::each<sfinae<Fs>...>;
  };

  template<>
  struct _smp_each_select<1>
  {
    template<class C>
    using f = test_contract<size<not_<>>, subcontract<C>>;
  };

  template<>
  struct _smp_each_select<2>
  {
    template<class F, class C>
    using f = test_contract<size<same_as<number<1>>>, each<
      assume_unary<F>, monadic_xs<assume_unary<C>>>>;
  };

  template<>
  struct _smp_each_select<3>
  {
    template<class F0, class F1, class C>
    using f = test_contract<size<same_as<number<2>>>, each<
      assume_unary<F0>,
      assume_unary<F1>,
      monadic_xs<assume_binary<C>>>>;
  };

  template<>
  struct _smp_each_select<4>
  {
    template<class F0, class F1, class F2, class C>
    using f = test_contract<size<same_as<number<3>>>, each<
      assume_unary<F0>,
      assume_unary<F1>,
      assume_unary<F2>,
      monadic_xs<subcontract<C>>>>;
  };

  struct _smp_each
  {
    template<class C, class... Fs>
    using f = test_contract<size<same_as<number<sizeof...(Fs)>>>,
      _each<monadic_xs<subcontract<C>>, assume_unary<Fs>...>>;
  };

  template<>
  struct _smp_each_select<5>
  : mp::rotate<mp::number<-1>, detail::_smp_each>
  {};
}
/// \endcond
