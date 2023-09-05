// SPDX-FileCopyrightText: 2023 Jonathan Poelen <jonathan.poelen@gmail.com>
// SPDX-License-Identifier: MIT
#pragma once

#include <jln/mp/functional/until_last.hpp>
#include <jln/mp/algorithm/drop_until.hpp>
#include <jln/mp/algorithm/drop_while.hpp>

namespace jln::mp
{
  /// \ingroup search

  /// Finds the last element that satisfy a \predicate.
  /// Calls \c TC with all the elements since the last found at the end.
  /// If no element is found, \c FC is used with the whole \sequence.
  /// \treturn \sequence
  /// \see find_last_if_not, find_last, find
  template<class Pred, class TC = listify, class FC = clear<TC>>
  using find_last_if = until_last_t<drop_until, Pred, TC, FC>;

  /// \see find_last_if, find_last, find
  template<class Pred, class TC = listify, class FC = clear<TC>>
  using find_last_if_not = until_last_t<drop_while, Pred, TC, FC>;

  /// \see find_last_if, find_last_if_not, find_last, find
  template<class T, class TC = listify, class FC = clear<TC>>
  using find_last = find_last_if<is<T>, TC, FC>;

  namespace emp
  {
    template<class L, class Pred, class TC = mp::listify, class FC = clear<TC>>
    using find_last_if = unpack<L, mp::find_last_if<Pred, TC, FC>>;

    template<class L, class Pred, class TC = mp::listify, class FC = clear<TC>>
    using find_last_if_not = unpack<L, mp::find_last_if_not<Pred, TC, FC>>;

    template<class L, class T, class TC = mp::listify, class FC = clear<TC>>
    using find_last = unpack<L, mp::find_last_if<mp::is<T>, TC, FC>>;
  }
}
