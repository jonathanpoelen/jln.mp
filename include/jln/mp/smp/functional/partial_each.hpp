#pragma once

#include <jln/mp/smp/contract.hpp>
#include <jln/mp/functional/partial_each.hpp>

/// \cond
namespace jln::mp::detail
{
  struct _smp_partial_each;
}
/// \endcond

namespace jln::mp::smp
{
  template <class... Fs>
  using partial_each = typename mp::conditional_c<sizeof...(Fs) == 0>
    ::template f<
      na,
      rotate_c<-1, detail::_smp_partial_each>>
    ::template f<Fs...>;
}

#include <jln/mp/smp/assume.hpp>
#include <jln/mp/functional/monadic.hpp>
#include <jln/mp/number/operators.hpp>
#include <jln/mp/list/size.hpp>

/// \cond
namespace jln::mp::detail
{
  template<template<class> class sfinae, class... Fs>
  struct _sfinae<sfinae, partial_each<Fs...>>
  {
    using type = smp::partial_each<sfinae<Fs>...>;
  };

  struct _smp_partial_each
  {
    template<class C, class... Fs>
    using f = test_contract<
      size<greater_equal_than_c<sizeof...(Fs)>>,
      partial_each<assume_unary<Fs>..., monadic_xs<subcontract<C>>>
    >;
  };
}
/// \endcond
