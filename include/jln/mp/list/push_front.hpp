// SPDX-FileCopyrightText: 2023 Jonathan Poelen <jonathan.poelen@gmail.com>
// SPDX-License-Identifier: MIT
#pragma once

#include <jln/mp/list/list.hpp>
#include <jln/mp/utility/unpack.hpp>
#include <jln/mp/functional/call.hpp>

namespace jln::mp
{
  /// \ingroup list

  /// Appends \c x to the beginning of the sequence.
  /// \treturn \sequence
  template<class x, class C = listify>
  struct push_front
  {
    template<class... xs>
    using f = JLN_MP_DCALL_TRACE_XS(xs, C, x, xs...);
  };

  namespace emp
  {
    template<class L, class T, class C = mp::listify>
    using push_front = typename detail::_unpack<mp::push_front<T, C>, L>::type;
  }

  /// \cond
  template<class x>
  struct push_front<x, listify>
  {
    template<class... xs>
    using f = list<x, xs...>;
  };
  /// \endcond
}

