// SPDX-FileCopyrightText: 2023 Jonathan Poelen <jonathan.poelen@gmail.com>
// SPDX-License-Identifier: MIT
#pragma once

#include <jln/mp/algorithm/drop_until_xs.hpp>
#include <jln/mp/algorithm/starts_with.hpp>

namespace jln::mp
{
  /// \ingroup search

  /// Find the \sequence after a sub-\sequence.
  /// Calls \c TC with all the elements after the sub-\sequence found.
  /// If no element is found, \c FC is used with the whole \sequence.
  /// \treturn \sequence
  /// \see search, search_before
  template<class Seq, class TC = listify, class FC = clear<TC>>
  struct after
  {};

  template<class... Ts, class TC, class FC>
  struct after<list<Ts...>, TC, FC>
  : partial_drop_until_extended_by_n_xs_c<-int_(sizeof...(Ts)),
                                          sizeof...(Ts),
                                          starts_with<list<Ts...>>,
                                          TC, FC>
  {};

  namespace emp
  {
    template<class L, class Seq, class TC = mp::listify, class FC = mp::clear<TC>>
    using after = unpack<L, mp::after<Seq, TC, FC>>;
  }

  /// \cond
  template<class T, class TC, class FC>
  struct after<list<T>, TC, FC>
  : drop_until_extended_by_n_c<1, is<T>, TC, FC>
  {};

  template<class TC, class FC>
  struct after<list<>, TC, FC>
  : detail::call_trace_xs<TC>
  {};
  /// \endcond
}
