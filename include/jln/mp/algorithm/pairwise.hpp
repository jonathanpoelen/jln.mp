// SPDX-FileCopyrightText: 2023 Jonathan Poelen <jonathan.poelen@gmail.com>
// SPDX-License-Identifier: MIT
#pragma once

#include <jln/mp/algorithm/rotate.hpp>


namespace jln::mp
{
  /// \cond
  namespace detail
  {
    template<class>
    struct pairwise_impl;
  }
  /// \endcond

  /// \ingroup group

  /// Returns successive overlapping pairs.
  /// \post If `sizeof...(xs) <= 1`, then the result sequence is empty
  /// \post If `sizeof...(xs) > 1`, then the number of 2-tuples is `sizeof...(xs) - 1`
  /// \semantics
  ///   \code
  ///   pairwise<>::f<a, b, c, d>
  ///   == list<
  ///     list<a, b>,
  ///     list<b, c>,
  ///     list<c, d>
  ///   >
  ///   \endcode
  /// \treturn \sequence of \list
  /// \see sliding, batched
  template<class F = listify, class C = listify>
  struct pairwise_with
  {
    template<class... xs>
    using f = typename detail::pairwise_impl<
      typename detail::rotate_impl<sizeof...(xs) ? sizeof...(xs) - 1 : 0>
      ::template f<sizeof...(xs) ? sizeof...(xs) - 1 : 0, list, xs...>
    >
      ::template f<JLN_MP_TRACE_F(C)::template f, JLN_MP_TRACE_F(F)::template f, xs...>;
  };

  template<class C = listify>
  using pairwise = pairwise_with<listify, C>;

  namespace emp
  {
    template<class L, class F = mp::listify, class C = mp::listify>
    using pairwise_with = typename detail::_unpack<mp::pairwise_with<F, C>, L>::type;

    template<class L, class C = mp::listify>
    using pairwise = typename detail::_unpack<mp::pairwise<C>, L>::type;
  }

/// \cond
#if ! JLN_MP_OPTIMIZED_ALIAS && ! JLN_MP_DEBUG
  template<class F, template<class...> class C>
  struct pairwise_with<F, lift<C>>
  {
    template<class... xs>
    using f = typename detail::pairwise_impl<
      typename detail::rotate_impl<sizeof...(xs) ? sizeof...(xs) - 1 : 0>
      ::template f<sizeof...(xs) ? sizeof...(xs) - 1 : 0, list, xs...>
    >
      ::template f<C, JLN_MP_TRACE_F(F)::template f, xs...>;
  };

  template<template<class...> class F, class C>
  struct pairwise_with<lift<F>, C>
  {
    template<class... xs>
    using f = typename detail::pairwise_impl<
      typename detail::rotate_impl<sizeof...(xs) ? sizeof...(xs) - 1 : 0>
      ::template f<sizeof...(xs) ? sizeof...(xs) - 1 : 0, list, xs...>
    >
      ::template f<JLN_MP_TRACE_F(C)::template f, F, xs...>;
  };

  template<template<class...> class F, template<class...> class C>
  struct pairwise_with<lift<F>, lift<C>>
  {
    template<class... xs>
    using f = typename detail::pairwise_impl<
      typename detail::rotate_impl<sizeof...(xs) ? sizeof...(xs) - 1 : 0>
      ::template f<sizeof...(xs) ? sizeof...(xs) - 1 : 0, list, xs...>
    >
      ::template f<C, F, xs...>;
  };
#endif
/// \endcond
}

namespace jln::mp::detail
{
  template<class>
  struct pairwise_impl;

  template<class x, class... xs>
  struct pairwise_impl<list<x, xs...>>
  {
    template<template<class...> class C, template<class...> class F, class y, class... ys>
    using f = C<F<xs, ys>...>;
  };

  template<class x>
  struct pairwise_impl<list<x>>
  {
    template<template<class...> class C, template<class...> class F, class...>
    using f = C<>;
  };

  template<>
  struct pairwise_impl<list<>>
  {
    template<template<class...> class C, template<class...> class F>
    using f = C<>;
  };
}
