#pragma once

#include <jln/mp/algorithm/lower_bound.hpp>

namespace jln::mp
{
  /// \ingroup search

  /// Finds first element that is greater that \c x.
  /// Invokes \c TC with all the elements since the one found at the end.
  /// If no element is found, \c FC is used.
  /// \pre \c is_sorted<Cmp>::f<xs...>
  /// \treturn \sequence
  template<class x, class Cmp = less<>, class TC = listify, class FC = TC>
  using upper_bound = lower_bound<x, flip<tee<Cmp, not_<>>>, TC, FC>;

  template<int_ x, class Cmp = less<>, class TC = listify, class FC = TC>
  using upper_bound_c = upper_bound<number<x>, Cmp, TC, FC>;

  template<class x, class TC = listify, class FC = TC>
  using upper_bound_than = upper_bound<x, less<>, TC, FC>;

  template<int_ x, class TC = listify, class FC = TC>
  using upper_bound_than_c = upper_bound<number<x>, less<>, TC, FC>;

  namespace emp
  {
    template<class L, class x, class Cmp = mp::less<>, class TC = mp::listify, class FC = TC>
    using upper_bound = unpack<L, mp::upper_bound<x, Cmp, TC, FC>>;

    template<class L, int_ x, class Cmp = mp::less<>, class TC = mp::listify, class FC = TC>
    using upper_bound_c = unpack<L, mp::upper_bound<mp::number<x>, Cmp, TC, FC>>;

    template<class L, class x, class TC = mp::listify, class FC = TC>
    using upper_bound_than = unpack<L, mp::upper_bound<x, mp::less<>, TC, FC>>;

    template<class L, int_ x, class TC = mp::listify, class FC = TC>
    using upper_bound_than_c = unpack<L, mp::upper_bound<mp::number<x>, mp::less<>, TC, FC>>;
  }
}
