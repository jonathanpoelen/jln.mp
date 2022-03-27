#pragma once

#include <jln/mp/algorithm/find.hpp>
#include <jln/mp/algorithm/search.hpp>
#include <jln/mp/algorithm/starts_with.hpp>
#include <jln/mp/list/drop_front.hpp>

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
  : partial_search_c<sizeof...(Ts) - 1,
                     starts_with<list<Ts...>>,
                     drop_front_c<sizeof...(Ts), TC>,
                     FC>
  {};

  namespace emp
  {
    template<class L, class Seq, class TC = mp::listify, class FC = mp::clear<TC>>
    using before = unpack<L, mp::before<Seq, TC, FC>>;
  }

  /// \cond
  template<class T, class TC, class FC>
  struct before<list<T>, TC, FC>
  : find<T, drop_front_c<1, TC>, FC>
  {};

  template<class TC, class FC>
  struct before<list<>, TC, FC>
  {
    template<class... xs>
    using f = JLN_MP_DCALL_TRACE_XS(xs, TC, xs...);
  };
  /// \endcond
}
