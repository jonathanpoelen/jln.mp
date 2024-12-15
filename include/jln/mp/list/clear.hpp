// SPDX-FileCopyrightText: 2023 Jonathan Poelen <jonathan.poelen@gmail.com>
// SPDX-License-Identifier: MIT
#pragma once

#include <jln/mp/list/listify.hpp>
#include <jln/mp/utility/always.hpp>

namespace jln::mp
{
  /// \ingroup list

  /// Removes all elements from the \sequence.
  /// \treturn \value
  template<class C = listify>
  struct clear
  {
    template<class... xs>
    using f = typename JLN_MP_LAZY_PARAM(xs..., JLN_MP_TRACE_F(C))::template f<>;
  };

  /// \cond
  template<>
  struct clear<listify>
#if JLN_MP_FORCE_LAZY_ALIAS
    : always<list<>>
  {};
#else
  {
    template<class... xs>
    using f = list<xs...>;
  };
#endif
  /// \endcond
}
