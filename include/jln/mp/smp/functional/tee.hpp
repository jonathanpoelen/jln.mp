#pragma once

#include <jln/mp/smp/contract.hpp>
#include <jln/mp/functional/tee.hpp>

/// \cond
namespace jln::mp::detail
{
  struct _smp_tee;
}
/// \endcond

namespace jln::mp::smp
{
  template <class... Fs>
  using tee = contract<typename mp::rotate<
      mp::number<-1>,
      detail::_smp_tee
    >::template f<subcontract<Fs>...>>;
}


#include <jln/mp/functional/monadic.hpp>

/// \cond
namespace jln::mp::detail
{
  template<template<class> class sfinae, class... Fs>
  struct _sfinae<sfinae, tee<Fs...>>
  {
    using type = smp::tee<sfinae<Fs>...>;
  };

  struct _smp_tee
  {
    template<class C, class... Fs>
    using f = _tee<monadic_xs<C>, Fs...>;
  };
}
/// \endcond
