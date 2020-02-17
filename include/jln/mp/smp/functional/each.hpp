#pragma once

#include "../../functional/each.hpp"
#include "../../functional/monadic.hpp"

namespace jln::mp::detail
{
  template<class C, class... Fs>
  using _smp_each = _each<monadic_xs<C>, Fs...>;
}

namespace jln::mp::smp
{
  template <class... Fs>
  using each = try_contract<typename mp::rotate<
    mp::number<sizeof...(Fs)-1>,
    mp::cfe<detail::_smp_each>
  >::template f<subcontract<Fs>...>>;
}

namespace jln::mp::detail
{
  template<template<class> class sfinae, class... Fs>
  struct _sfinae<sfinae, each<Fs...>>
  {
    using type = smp::each<sfinae<Fs>...>;
  };
}
