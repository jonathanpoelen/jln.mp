#pragma once

#include "../../functional/contract.hpp"
#include "../../functional/each.hpp"

namespace jln::mp::detail
{
  struct _smp_each; 
}

namespace jln::mp::smp
{
  template <class... Fs>
  using each = try_contract<typename mp::rotate<
    mp::number<sizeof...(Fs)-1>,
    detail::_smp_each
  >::template f<subcontract<Fs>...>>;
}


#include "../../functional/monadic.hpp"

namespace jln::mp::detail
{
  template<template<class> class sfinae, class... Fs>
  struct _sfinae<sfinae, each<Fs...>>
  {
    using type = smp::each<sfinae<Fs>...>;
  };
  
  struct _smp_each 
  {
    template<class C, class... Fs>
    using f = _each<monadic_xs<C>, Fs...>;
  };
}
