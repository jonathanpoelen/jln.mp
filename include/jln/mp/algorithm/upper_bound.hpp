#pragma once

#include "lower_bound.hpp"

namespace jln::mp
{
  template<class x, class Cmp = less<>, class C = listify, class NC = C>
  using upper_bound = lower_bound<x, flip<fork<Cmp, not_<>>>, C, NC>;

  template<int_ x, class Cmp = less<>, class C = listify, class NC = C>
  using upper_bound_c = upper_bound<number<x>, Cmp, C, NC>;

  template<class x, class C = listify, class NC = C>
  using upper_bound_of = upper_bound<x, less<>, C, NC>;

  template<int_ x, class C = listify, class NC = C>
  using upper_bound_of_c = upper_bound<number<x>, less<>, C, NC>;

  namespace emp
  {
    template<class L, class x, class Cmp = mp::less<>, class C = mp::listify, class NC = C>
    using upper_bound = unpack<L, mp::upper_bound<x, Cmp, C, NC>>;

    template<class L, int_ x, class Cmp = mp::less<>, class C = mp::listify, class NC = C>
    using upper_bound_c = unpack<L, mp::upper_bound<mp::number<x>, Cmp, C, NC>>;

    template<class L, class x, class C = mp::listify, class NC = C>
    using upper_bound_of = unpack<L, mp::upper_bound<x, mp::less<>, C, NC>>;

    template<class L, int_ x, class C = mp::listify, class NC = C>
    using upper_bound_of_c = unpack<L, mp::upper_bound<mp::number<x>, mp::less<>, C, NC>>;
  }
}
