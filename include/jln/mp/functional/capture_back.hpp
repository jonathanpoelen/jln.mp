// SPDX-FileCopyrightText: 2023 Jonathan Poelen <jonathan.poelen@gmail.com>
// SPDX-License-Identifier: MIT
#pragma once

#include <jln/mp/number/number.hpp>
#include <jln/mp/utility/unpack.hpp>
#include <jln/mp/functional/call.hpp>

namespace jln::mp
{
  /// \ingroup functional

  /// Invoking \c F with its last parameters bound to args.
  /// \semantics
  ///   \code
  ///   capture_back<c, d>::f<F, a, b> == F<a, b, c, d>
  ///   \endcode
  /// \treturn \sequence
  /// \see capture_front, bind_back, bind_front
  template<class... BoundArgs>
  struct capture_back
  {
    template<class F, class... xs>
    using f = JLN_MP_CALL_TRACE(F, xs..., BoundArgs...);
  };

  template<int_... BoundArgs>
  using capture_back_c = capture_back<number<BoundArgs>...>;

#if JLN_MP_ENABLE_TPL_AUTO
  template<auto... BoundArgs>
  struct capture_back_v
  {
    template<class F, class... xs>
    using f = typename F::template f<xs..., BoundArgs...>;
  };
#endif

  namespace emp
  {
    template<class L, class... BoundArgs>
    using capture_back = unpack<L, mp::capture_back<BoundArgs...>>;

    template<class L, int_... BoundArgs>
    using capture_back_c = unpack<L, mp::capture_back_c<BoundArgs...>>;

#if JLN_MP_ENABLE_TPL_AUTO
    template<class L, auto... BoundArgs>
    using capture_back_v = unpack<L, mp::capture_back_v<BoundArgs...>>;
#endif
  }
}
