#pragma once

#include "../contract.hpp"
#include "../../functional/fork.hpp"

namespace jln::mp::detail
{
  struct _smp_fork;
}

namespace jln::mp::smp
{
  template <class... Fs>
  using fork = contract<typename mp::rotate<
      mp::number<-1>,
      detail::_smp_fork
    >::template f<subcontract<Fs>...>>;
}


#include "../../functional/monadic.hpp"

namespace jln::mp::detail
{
  template<template<class> class sfinae, class... Fs>
  struct _sfinae<sfinae, fork<Fs...>>
  {
    using type = smp::fork<sfinae<Fs>...>;
  };

  struct _smp_fork
  {
    template<class C, class... Fs>
    using f = _fork<monadic_xs<C>, Fs...>;
  };
}
