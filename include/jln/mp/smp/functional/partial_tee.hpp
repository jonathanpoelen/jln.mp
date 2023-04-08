#pragma once

#include <jln/mp/smp/contract.hpp>
#include <jln/mp/functional/partial_tee.hpp>

/// \cond
namespace jln::mp::detail
{
  struct _smp_partial_tee;
}
/// \endcond

namespace jln::mp::smp
{
  template <class... Fs>
  using partial_tee = typename mp::conditional_c<sizeof...(Fs) == 0>
    ::template f<
      na,
      rotate_c<-1, detail::_smp_partial_tee>>
    ::template f<subcontract<Fs>...>;
}

#include <jln/mp/functional/monadic.hpp>
#include <jln/mp/number/operators.hpp>
#include <jln/mp/list/size.hpp>

/// \cond
namespace jln::mp::detail
{
  template<template<class> class sfinae, class... Fs>
  struct _sfinae<sfinae, partial_tee<Fs...>>
  {
    using type = smp::partial_tee<sfinae<Fs>...>;
  };

  struct _smp_partial_tee
  {
    template<class C, class... Fs>
    using f = test_contract<
      size<greater_equal_than_c<sizeof...(Fs)>>,
      partial_tee<Fs..., monadic_xs<C>>
    >;
  };
}
/// \endcond
