// SPDX-FileCopyrightText: 2023 Jonathan Poelen <jonathan.poelen@gmail.com>
// SPDX-License-Identifier: MIT
#pragma once

#include <jln/mp/number/number.hpp>
#include <jln/mp/utility/unpack.hpp>
#include <jln/mp/functional/call.hpp>

namespace jln::mp
{
  /// \ingroup functional

  /// Invoking \c F with its first parameters bound to args.
  /// \semantics
  ///   \code
  ///   capture_front<a, b>::f<F, c, d> == F<a, b, c, d>
  ///   \endcode
  /// \treturn \sequence
  /// \see capture_back, bind_front, bind_back
  template<class... BoundArgs>
  struct capture_front
  {
    template<class F, class... xs>
    using f = JLN_MP_CALL_TRACE(F, BoundArgs..., xs...);
  };

  template<int_... BoundArgs>
  using capture_front_c = capture_front<number<BoundArgs>...>;

#if JLN_MP_ENABLE_TPL_AUTO
  template<auto... BoundArgs>
  struct capture_front_v
  {
    template<class F, class... xs>
    using f = typename F::template f<BoundArgs..., xs...>;
  };
#endif

  namespace emp
  {
    template<class L, class... BoundArgs>
    using capture_front = typename detail::_unpack<mp::capture_front<BoundArgs...>, L>::type;

    template<class L, int_... BoundArgs>
    using capture_front_c = typename detail::_unpack<mp::capture_front_c<BoundArgs...>, L>::type;

#if JLN_MP_ENABLE_TPL_AUTO
    template<class L, auto... BoundArgs>
    using capture_front_v = typename detail::_unpack<mp::capture_front_v<BoundArgs...>, L>::type;
#endif
  }
}
