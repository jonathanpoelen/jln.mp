#pragma once

#include <jln/mp/algorithm/search.hpp>
#include <jln/mp/algorithm/starts_with.hpp>
#include <jln/mp/list/drop_front.hpp>

namespace jln::mp
{
  /// \ingroup search

  /// Find the \sequence after a sub-\sequence.
  /// Calls \c TC with all the elements after the sub-\sequence found.
  /// If no element is found, \c FC is used with the whole \sequence.
  /// \treturn \sequence
  template<class Seq, class TC = listify, class FC = clear<TC>>
  struct after;

  template<class... Ts, class TC, class FC>
  struct after<list<Ts...>, TC, FC>
  : search<starts_with<list<Ts...>>, drop_front_c<sizeof...(Ts), TC>, FC>
  {};

  namespace emp
  {
    template<class L, class Seq, class TC = mp::listify, class FC = mp::clear<TC>>
    using after = unpack<L, mp::after<Seq, TC, FC>>;
  }

  /// \cond
  template<class TC, class FC>
  struct after<list<>, TC, FC>
  {
    template<class... xs>
    using f = JLN_MP_DCALL(0 <= sizeof...(xs), TC, xs...);
  };
  /// \endcond
}
