#pragma once

#include "../assume.hpp"
#include "../../functional/partial.hpp"

namespace jln::mp::detail
{
  template<int>
  struct _smp_partial_select;
}

namespace jln::mp::smp
{
  template <class... Fs>
  using partial = typename detail::_smp_partial_select<detail::min(5, sizeof...(Fs))>
    ::template f<Fs...>;
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

  template<>
  struct _smp_partial_select<1>
  {
    template<class C>
    using f = contract<subcontract<C>>;
  };

  template<>
  struct _smp_partial_select<2>
  {
    template<class F, class C>
    using f = test_contract<
      size<>,
      partial<assume_unary<F>, monadic_xs<subcontract<C>>>
    >;
  };

  template<>
  struct _smp_partial_select<3>
  {
    template<class F0, class F1, class C>
    using f = test_contract<
      size<greater_equal_than_c<2>>,
      partial<
        assume_unary<F0>,
        assume_unary<F1>,
        monadic_xs<subcontract<C>>
      >
    >;
  };

  template<>
  struct _smp_partial_select<4>
  {
    template<class F0, class F1, class F2, class C>
    using f = test_contract<
      size<greater_equal_than_c<3>>,
      partial<
        assume_unary<F0>,
        assume_unary<F1>,
        assume_unary<F2>,
        monadic_xs<subcontract<C>>
      >
    >;
  };

  struct _smp_partial
  {
    template<class C, class... Fs>
    using f = test_contract<
      size<greater_equal_than_c<sizeof...(Fs)>>,
      _partial<monadic_xs<subcontract<C>>, assume_unary<Fs>...>
    >;
  };

  template<>
  struct _smp_partial_select<5>
  : mp::rotate<mp::number<-1>, _smp_partial>
  {};
}
