// SPDX-FileCopyrightText: 2023 Jonathan Poelen <jonathan.poelen@gmail.com>
// SPDX-License-Identifier: MIT
#pragma once

#include <jln/mp/smp/contract.hpp>
#include <jln/mp/functional/partial.hpp>

/// \cond
namespace jln::mp::detail
{
  struct _smp_partial;
}
/// \endcond

namespace jln::mp::smp
{
  template<class... Fs>
  using partial = typename mp::conditional_c<sizeof...(Fs) == 0>
    ::template f<
      na,
      rotate_c<-1, detail::_smp_partial>>
    ::template f<subcontract<Fs>...>;
}

#include <jln/mp/functional/monadic.hpp>

/// \cond
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
    using f = contract<mp::partial<Fs..., monadic_xs<C>>>;
  };
}
/// \endcond
