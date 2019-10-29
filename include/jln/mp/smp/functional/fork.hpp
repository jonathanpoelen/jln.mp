#pragma once

#include "../../functional/fork.hpp"
#include "../../functional/monadic.hpp"

namespace jln::mp::detail
{
  template<class C, class... Fs>
  using _smp_fork = mp::fork<Fs..., monadic_xs<C>>;
}

namespace jln::mp::smp
{
  template <class... Fs>
  using fork = valid_contract<typename mp::rotate<
    mp::number<sizeof...(Fs)-1>,
    mp::cfe<detail::_smp_fork>
  >::template f<subcontract<Fs>...>>;
}

namespace jln::mp::detail
{
  template<template<class> class sfinae, class... Fs>
  struct _sfinae<sfinae, fork<Fs...>>
  {
    using type = smp::fork<sfinae<Fs>...>;
  };
}
