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
      ::template f<C, list<xs, x>...>::type;
  };

  namespace emp
  {
    template<class L, class x, class C = mp::listify>
    using suffix = unpack<L, mp::suffix<x, C>>;
  }
}
