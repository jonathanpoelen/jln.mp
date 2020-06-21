#pragma once

#include "../contract.hpp"
#include "../../functional/on.hpp"
#include "../../functional/monadic.hpp"

/// \cond
namespace jln::mp::detail
{
  struct _smp_on
  {
    template<class C, class... Fs>
    using f = contract<mp::on<Fs..., monadic_xs<C>>>;
  };
}
/// \endcond

namespace jln::mp::smp
{
  template <class... Fs>
  using on = typename rotate<number<-1>, detail::_smp_on>::f<subcontract<Fs>...>;
}


/// \cond
namespace jln::mp::detail
{
  template<template<class> class sfinae, class... Fs>
  struct _sfinae<sfinae, on<Fs...>>
  {
    using type = smp::on<sfinae<Fs>...>;
  };
}
/// \endcond
