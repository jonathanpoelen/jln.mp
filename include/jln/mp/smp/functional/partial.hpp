#pragma once

#include "../../functional/contract.hpp"
#include "../../functional/partial.hpp"
#include "../../functional/monadic.hpp"
#include "../../number/operators.hpp"
#include "../../list/size.hpp"

namespace jln::mp::detail
{
  template<class C, class... Fs>
  using _smp_partial = contract<
    size<greater_equal_than_c<sizeof...(Fs)>>, 
    _partial<monadic_xs<C>, Fs...>>;
}

namespace jln::mp::smp
{
  template <class... Fs>
  using partial = typename mp::rotate<
    mp::number<-1>,
    mp::cfe<detail::_smp_partial>
  >::template f<subcontract<Fs>...>;
}

namespace jln::mp::detail
{
  template<template<class> class sfinae, class... Fs>
  struct _sfinae<sfinae, partial<Fs...>>
  {
    using type = smp::partial<sfinae<Fs>...>;
  };
}
