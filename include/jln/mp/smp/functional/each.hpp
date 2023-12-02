// SPDX-FileCopyrightText: 2023 Jonathan Poelen <jonathan.poelen@gmail.com>
// SPDX-License-Identifier: MIT
#pragma once

#include <jln/mp/smp/assume.hpp>
#include <jln/mp/functional/each.hpp>

/// \cond
namespace jln::mp::detail
{
  template<int>
  struct _smp_each_select;
}
/// \endcond

namespace jln::mp::smp
{
  template<class... Fs>
  using each = typename detail::_smp_each_select<sizeof...(Fs) < 4 ? sizeof...(Fs) : 4>
    ::template f<Fs...>;
}


#include <jln/mp/functional/monadic.hpp>

/// \cond
namespace jln::mp::detail
{
  template<template<class> class sfinae, class... Fs>
  struct _sfinae<sfinae, each<Fs...>>
  {
    using type = smp::each<sfinae<Fs>...>;
  };

  template<>
  struct _smp_each_select<0>
  {};

  template<>
  struct _smp_each_select<1>
  {
    template<class C>
    using f = test_contract<size<not_<>>, assume_numbers<C>>;
  };

  template<>
  struct _smp_each_select<2>
  {
    template<class F, class C>
    using f = test_contract<size<is<number<1>>>, _each<
      monadic_xs<assume_unary<C>>, assume_unary<F>>>;
  };

  template<>
  struct _smp_each_select<3>
  {
    template<class F0, class F1, class C>
    using f = test_contract<size<is<number<2>>>, _each<
      monadic_xs<assume_binary<C>>,
      assume_unary<F0>,
      assume_unary<F1>>>;
  };

  struct _smp_each
  {
    template<class C, class... Fs>
    using f = test_contract<size<is<number<sizeof...(Fs)>>>,
      _each<monadic_xs<subcontract<C>>, assume_unary<Fs>...>>;
  };

  template<>
  struct _smp_each_select<4>
  : mp::rotate_c<-1, detail::_smp_each>
  {};
}
/// \endcond
