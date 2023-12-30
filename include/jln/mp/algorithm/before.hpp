// SPDX-FileCopyrightText: 2023 Jonathan Poelen <jonathan.poelen@gmail.com>
// SPDX-License-Identifier: MIT
#pragma once

#include <jln/mp/algorithm/take_until_xs.hpp>
#include <jln/mp/algorithm/starts_with.hpp>

namespace jln::mp
{
  /// \ingroup search

  /// Find the \sequence before a sub-\sequence.
  /// Calls \c TC with all the elements before the sub-\sequence found.
  /// If no element is found, \c FC is used with the whole \sequence.
  /// \treturn \sequence
  /// \see search, search_before
  template<class Seq, class TC = listify, class FC = clear<TC>>
  struct before
  {};

  template<class... Ts, class TC, class FC>
  struct before<list<Ts...>, TC, FC>
  : partial_take_until_xs_c<-int_{sizeof...(Ts)},
                            starts_with<list<Ts...>>,
                            TC, FC>
  {
#ifdef JLN_MP_DOXYGENATING
    template<class... xs>
    using f;
#endif
  };

  namespace emp
  {
    template<class L, class Seq, class TC = mp::listify, class FC = mp::clear<TC>>
    using before = unpack<L, mp::before<Seq, TC, FC>>;
  }

  /// \cond
  template<class T, class TC, class FC>
  struct before<list<T>, TC, FC>
  : take_until<is<T>, TC, FC>
  {};

  template<class TC, class FC>
  struct before<list<>, TC, FC>
  : detail::call_trace_xs_0<TC>
  {};
  /// \endcond
}
