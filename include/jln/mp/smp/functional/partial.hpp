#pragma once

#include "../../functional/contract.hpp"
#include "../../functional/partial.hpp"

namespace jln::mp::detail
{
  struct _smp_partial;
}

namespace jln::mp::smp
{
  template <class... Fs>
  using partial = typename mp::rotate<
    mp::number<-1>,
    detail::_smp_partial
  >::template f<Fs...>;
}


#include "../../functional/monadic.hpp"
#include "../../number/operators.hpp"
#include "../../list/size.hpp"

namespace jln::mp::detail
{
  template<template<class> class sfinae, class... Fs>
  struct _sfinae<sfinae, partial<Fs...>>
  {
    using type = smp::partial<sfinae<Fs>...>;
  };

  struct _smp_partial
  {
    template<class C, class... Fs>
    using f = test_contract<
      size<greater_equal_than_c<sizeof...(Fs)>>,
      _partial<monadic_xs<subcontract<C>>, assume_unary<Fs>...>>;
  };
}
