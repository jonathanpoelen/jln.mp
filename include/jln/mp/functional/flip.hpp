// SPDX-FileCopyrightText: 2023 Jonathan Poelen <jonathan.poelen@gmail.com>
// SPDX-License-Identifier: MIT
#pragma once

#include <jln/mp/list/listify.hpp>
#include <jln/mp/utility/unpack.hpp>
#include <jln/mp/functional/call.hpp>

namespace jln::mp
{
  /// \ingroup functional

  /// Invokes a \function with its two first arguments reversed.
  /// \semantics
  ///   \code
  ///   C::f<xs[1], xs[0], ...xs[2:]>
  ///   \endcode
  /// \treturn \sequence
  template<class C = listify>
  struct flip
  {
    template<class x0, class x1, class... xs>
    using f = JLN_MP_DCALL_TRACE_XS(xs, C, x1, x0, xs...);
  };

  namespace emp
  {
    template<class L, class C = mp::listify>
    using flip = typename detail::_unpack<mp::flip<C>, L>::type;
  }

  /// \cond
  template<>
  struct flip<listify>
  {
    template<class x0, class x1, class... xs>
    using f = list<x1, x0, xs...>;
  };
  /// \endcond
}
