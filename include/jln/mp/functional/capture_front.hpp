// SPDX-FileCopyrightText: 2023 Jonathan Poelen <jonathan.poelen@gmail.com>
// SPDX-License-Identifier: MIT
#pragma once

#include <jln/mp/value/val.hpp>
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

#if __cplusplus >= 201703L
  template<JLN_MP_TPL_AUTO_OR_INT... BoundArgs>
  using capture_front_c = capture_front<val<BoundArgs>...>;
#else
  template<int_... BoundArgs>
  using capture_front_c = capture_front<typed_val<int_, BoundArgs>...>;
#endif

  template<JLN_MP_TPL_AUTO_OR_INT... BoundArgs>
  struct capture_front_v_c
  {
    template<class F, class... xs>
    using f = typename F::template f<BoundArgs..., xs::value...>;
  };

  template<class... BoundArgs>
  using capture_front_v = capture_front_v_c<BoundArgs::value...>;

  namespace emp
  {
    template<class L, class... BoundArgs>
    using capture_front = unpack<L, mp::capture_front<BoundArgs...>>;

    template<class L, class... BoundArgs>
    using capture_front_v = unpack<L, mp::capture_front_v<BoundArgs...>>;

    template<class L, JLN_MP_TPL_AUTO_OR_INT... BoundArgs>
    using capture_front_v_c = unpack<L, mp::capture_front_v_c<BoundArgs...>>;
  }
}
