#pragma once

#include "../assume.hpp"
#include "../../functional/partial_eager.hpp"

namespace jln::mp::detail
{
  template<int>
  struct _smp_partial_eager_select;
}

namespace jln::mp::smp
{
  template <class... Fs>
  using partial_eager = typename detail::_smp_partial_eager_select<detail::min(5, sizeof...(Fs))>
    ::template f<Fs...>;
}


#include "../../functional/monadic.hpp"
#include "../../number/operators.hpp"
#include "../../list/size.hpp"

namespace jln::mp::detail
{
  template<template<class> class sfinae, class... Fs>
  struct _sfinae<sfinae, partial_eager<Fs...>>
  {
    using type = smp::partial_eager<sfinae<Fs>...>;
  };
  
  template<>
  struct _smp_partial_eager_select<1>
  {
    template<class C>
    using f = contract<subcontract<C>>;
  };
  
  template<>
  struct _smp_partial_eager_select<2>
  {
    template<class F, class C>
    using f = contract<
      partial_eager<subcontract<F>, monadic_xs<assume_unary<C>>>
    >;
  };
  
  template<>
  struct _smp_partial_eager_select<3>
  {
    template<class F0, class F1, class C>
    using f = test_contract<
      size<>,
      partial_eager<
        assume_unary<F0>, 
        subcontract<F1>, 
        monadic_xs<assume_binary<C>>
      >
    >;
  };
  
  template<>
  struct _smp_partial_eager_select<4>
  {
    template<class F0, class F1, class F2, class C>
    using f = test_contract<
      size<greater_equal_than_c<2>>,
      partial_eager<
        assume_unary<F0>, 
        assume_unary<F1>, 
        subcontract<F2>, 
        monadic_xs<subcontract<C>>
      >
    >;
  };
  
  struct _smp_partial_eager
  {
    template<class Flast, class C, class... Fs>
    using f = test_contract<
      size<greater_equal_than_c<sizeof...(Fs)>>,
      typename _partial_eager<
        subcontract<Flast>, 
        monadic_xs<subcontract<C>>, 
        assume_unary<Fs>...
      >::type
    >;
  };
  
  template<>
  struct _smp_partial_eager_select<5> 
  : mp::rotate<mp::number<-2>, _smp_partial_eager>
  {};
}
