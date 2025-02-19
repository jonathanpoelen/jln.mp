// SPDX-FileCopyrightText: 2023 Jonathan Poelen <jonathan.poelen@gmail.com>
// SPDX-License-Identifier: MIT
#pragma once

namespace jln::mp
{
  /// \cond
  namespace detail
  {
    template<class S>
    struct wrapper;
  }
  /// \endcond

  /// \ingroup utility

  namespace emp
  {
    /// converts a \typelist to a \c cfe<S>
    template<class L>
    using wrapper = typename detail::wrapper<L>::type;

    template<class L, class... xs>
    using rewrap = typename wrapper<L>::template f<xs...>;
  }
}

#include <jln/mp/functional/continuation.hpp>

/// \cond
namespace jln::mp::detail
{
  template<template<class...> class S, class... xs>
  struct wrapper<S<xs...>>
  {
    using type = cfe<S>;
  };
}
/// \endcond
