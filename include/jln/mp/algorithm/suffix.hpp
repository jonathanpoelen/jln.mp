// SPDX-FileCopyrightText: 2023 Jonathan Poelen <jonathan.poelen@gmail.com>
// SPDX-License-Identifier: MIT
#pragma once

#include <jln/mp/list/listify.hpp>
#include <jln/mp/utility/unpack.hpp>
#include <jln/mp/list/join.hpp>

namespace jln::mp
{
  /// \ingroup algorithm

  /// Inserts a \value after each element of a \sequence.
  /// \treturn \list
  /// \see intersperse, prefix
  template<class x, class C = listify>
  struct suffix
  {
    template<class... xs>
    using f = typename detail::_join_select<sizeof...(xs)>
      ::template f<JLN_MP_TRACE_F(C)::template f, list<xs, x>...>::type;
  };

  namespace emp
  {
    template<class L, class x, class C = mp::listify>
    using suffix = typename detail::_unpack<mp::suffix<x, C>, L>::type;
  }
}

/// \cond
#if ! JLN_MP_OPTIMIZED_ALIAS && ! JLN_MP_ENABLE_DEBUG
namespace jln::mp
{
  template<class x, template<class...> class C>
  struct suffix<x, lift<C>>
  {
    template<class... xs>
    using f = typename detail::_join_select<sizeof...(xs)>
      ::template f<C, list<xs, x>...>::type;
  };
}
#endif
/// \endcond
