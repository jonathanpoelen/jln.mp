// SPDX-FileCopyrightText: 2023 Jonathan Poelen <jonathan.poelen@gmail.com>
// SPDX-License-Identifier: MIT
#pragma once

#include <jln/mp/number/number.hpp>
#include <jln/mp/utility/unpack.hpp>
#include <jln/mp/functional/call.hpp>

namespace jln::mp
{
  /// \ingroup functional

  /// Invoking \c F with its last parameters bound to bound to args.
  /// \semantics
  ///   \code
  ///   bind_back<F, c, d>::f<a, b> == F<a, b, c, d>
  ///   \endcode
  /// \treturn \sequence
  /// \see bind_front, capture_back, capture_front
  template<class F, class... BoundArgs>
  struct bind_back
  {
    template<class... xs>
    using f = JLN_MP_DCALL_TRACE_XS(xs, F, xs..., BoundArgs...);
  };

  template<class F, int_... BoundArgs>
  using bind_back_c = bind_back<F, number<BoundArgs>...>;

#if JLN_MP_ENABLE_TPL_AUTO
  template<class F, auto... BoundArgs>
  struct bind_back_v
  {
    template<class... xs>
    using f = typename JLN_MP_CALLER_XS(xs, F)::template f<xs..., BoundArgs...>;
  };
#endif

  namespace emp
  {
    template<class L, class F, class... BoundArgs>
    using bind_back = typename detail::_unpack_append<F, L, BoundArgs...>::type;

    template<class L, class F, int_... BoundArgs>
    using bind_back_c = typename detail::_unpack_append<F, L, number<BoundArgs>...>::type;

#if JLN_MP_ENABLE_TPL_AUTO
    template<class L, class F, auto... BoundArgs>
    using bind_back_v = typename detail::_unpack<mp::bind_back_v<F, BoundArgs...>, L>::type;
#endif
  }
} // namespace jln::mp
