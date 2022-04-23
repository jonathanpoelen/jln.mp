#pragma once

#include <jln/mp/list/listify.hpp>
#include <jln/mp/utility/unpack.hpp>
#include <jln/mp/list/join.hpp>

namespace jln::mp
{
  /// \ingroup algorithm

  /// Inserts a \value before each element of a \sequence.
  /// \treturn \list
  /// \see intersperse, suffix
  template<class x, class C = listify>
  struct prefix
  {
    template<class... xs>
    using f = typename detail::_join_select<sizeof...(xs)>
      ::template f<JLN_MP_TRACE_F(C)::template f, list<x, xs>...>::type;
  };

  namespace emp
  {
    template<class L, class x, class C = mp::listify>
    using prefix = unpack<L, mp::prefix<x, C>>;
  }

  /// \cond
  template<class x>
  struct prefix<x, listify>
  {
    template<class... xs>
    using f = typename detail::_join_select<sizeof...(xs)>
      ::template f<list, list<x, xs>...>::type;
  };
  /// \endcond
}
