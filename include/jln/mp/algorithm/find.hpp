#pragma once

#include <jln/mp/algorithm/drop_until.hpp>
#include <jln/mp/utility/is.hpp>

namespace jln::mp
{
  /// \ingroup search

  /// Finds the first element that satisfy a \predicate.
  /// \pre \c Pred::f<x> must return a boolean, 1 or 0
  /// Calls \c TC with all the elements since the one found at the end.
  /// If no element is found, \c FC is used with the whole \sequence.
  /// \treturn \sequence
  /// \see find_if_not, find, find_last_if, find_last
  template<class Pred, class TC = listify, class FC = clear<TC>>
  using find_if = drop_until<Pred, TC, FC>;

  /// \see find_if, find, find_last_if, find_last
  template<class Pred, class TC = listify, class FC = clear<TC>>
  using find_if_not = drop_while<Pred, TC, FC>;

  /// \see find_if, find_if_not, find_last_if, find_last
  template<class T, class TC = listify, class FC = clear<TC>>
  using find = find_if<is<T>, TC, FC>;

  namespace emp
  {
    template<class L, class Pred, class TC = mp::listify, class FC = clear<TC>>
    using find_if = unpack<L, mp::find_if<Pred, TC, FC>>;

    template<class L, class Pred, class TC = mp::listify, class FC = clear<TC>>
    using find_if_not = unpack<L, mp::find_if_not<Pred, TC, FC>>;

    template<class L, class T, class TC = mp::listify, class FC = clear<TC>>
    using find = unpack<L, mp::find_if<mp::is<T>, TC, FC>>;
  }
}
