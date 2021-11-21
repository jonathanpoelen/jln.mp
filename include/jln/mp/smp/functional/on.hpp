#pragma once

#include <jln/mp/smp/contract.hpp>
#include <jln/mp/functional/on.hpp>
#include <jln/mp/functional/monadic.hpp>

/// \cond
namespace jln::mp::detail
{
  struct _smp_on;
}
/// \endcond

namespace jln::mp::smp
{
  template <class... Fs>
  using on = typename mp::conditional_c<sizeof...(Fs) == 0>
    ::template f<
      na,
      rotate<number<-1>, detail::_smp_on>>
    ::template f<subcontract<Fs>...>;
}


/// \cond
namespace jln::mp::detail
{
  template<template<class> class sfinae, class... Fs>
  struct _sfinae<sfinae, on<Fs...>>
  {
    using type = smp::on<sfinae<Fs>...>;
  };

  struct _smp_on
  {
    template<class C, class... Fs>
    using f = contract<mp::on<Fs..., monadic_xs<C>>>;
  };
}
/// \endcond
