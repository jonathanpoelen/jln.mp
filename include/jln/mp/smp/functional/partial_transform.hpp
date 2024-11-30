// SPDX-FileCopyrightText: 2024 Jonathan Poelen <jonathan.poelen@gmail.com>
// SPDX-License-Identifier: MIT
#pragma once

#include <jln/mp/smp/contract.hpp>
#include <jln/mp/functional/partial_transform.hpp>

/// \cond
namespace jln::mp::detail
{
  struct _smp_partial_transform;
  struct _smp_partial_transform0;
}
/// \endcond

namespace jln::mp::smp
{
  template<class... Fs>
  using partial_transform = typename mp::conditional_c<sizeof...(Fs) == 0>
    ::template f<
      mp::always<bad_contract>,
      rotate_c<-1, detail::_smp_partial_transform>>
    ::template f<Fs...>;

  template<class... Fs>
  using partial_transform0 = typename mp::conditional_c<sizeof...(Fs) == 0>
    ::template f<
      mp::always<bad_contract>,
      rotate_c<-1, detail::_smp_partial_transform0>>
    ::template f<Fs...>;
}

#include <jln/mp/functional/monadic.hpp>
#include <jln/mp/number/operators.hpp>
#include <jln/mp/list/size.hpp>

/// \cond
namespace jln::mp::detail
{
  template<template<class> class sfinae, class... Fs>
  struct _sfinae<sfinae, partial_transform<Fs...>>
  {
    using type = smp::partial_transform<sfinae<Fs>...>;
  };

  struct _smp_partial_transform
  {
    template<class C, class... Fs>
    using f = test_contract<
      size<greater_equal_than_c<sizeof...(Fs)>>,
      partial_transform<subcontract<Fs>..., monadic_xs<subcontract<C>>>
    >;
  };

  template<template<class> class sfinae, class... Fs>
  struct _sfinae<sfinae, partial_transform0<Fs...>>
  {
    using type = smp::partial_transform0<sfinae<Fs>...>;
  };

  struct _smp_partial_transform0
  {
    template<class C, class... Fs>
    using f = contract<mp::partial_transform0<subcontract<Fs>..., monadic_xs<subcontract<C>>>>;
  };
}
/// \endcond
