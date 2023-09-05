// SPDX-FileCopyrightText: 2023 Jonathan Poelen <jonathan.poelen@gmail.com>
// SPDX-License-Identifier: MIT
#pragma once

#include <jln/mp/algorithm/rotate.hpp>

namespace jln::mp
{
  /// \cond
  namespace detail
  {
    struct partial_tee_impl;
  }
  /// \endcond

  /// \ingroup functional

  /// Invokes multiple functions passing all parameters to each
  /// then calls \c C with the results and the rest of the parameters.
  /// \semantics
  ///   \code
  ///   partial_tee<F,G,C>::f<a> == /* error */
  ///   partial_tee<F,G,C>::f<a,b,c,d> == C::f<F::f<a,b,c,d>, G::f<a,b,c,d>, c, d>
  ///   \endcode
  /// \treturn \value
  /// \see partial_each, partial, each, tee
#ifdef JLN_MP_DOXYGENATING
  template<class... Fs, class C>
  struct partial_tee
  {
    template<class... xs>
    using f;
  };
#else
  template<class... Fs>
  struct partial_tee
  : detail::rotate_impl<sizeof...(Fs)-1>
  ::template f<sizeof...(Fs)-1, detail::partial_tee_impl, Fs...>
  {};
#endif
}

#include <jln/mp/functional/partial_xs.hpp>

/// \cond
namespace jln::mp::detail
{
  struct partial_tee_impl
  {
    template<class... Fs>
    using f = partial_xs_select<1, Fs...>;
  };
} // namespace jln::mp
/// \endcond
