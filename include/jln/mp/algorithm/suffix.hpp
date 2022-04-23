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
    using suffix = unpack<L, mp::suffix<x, C>>;
  }

  /// \cond
  template<class x>
  struct suffix<x, listify>
  {
    template<class... xs>
    using f = typename detail::_join_select<sizeof...(xs)>
      ::template f<list, list<xs, x>...>::type;
  };
  /// \endcond
}
