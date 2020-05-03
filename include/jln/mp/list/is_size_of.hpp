#pragma once

#include "size.hpp"
#include "../utility/same_as.hpp"

namespace jln::mp
{
  /// \ingroup list

  template<class N, class C = identity>
  using is_size_of = size<same_as<N, C>>;

  template<int_ n, class C = identity>
  using is_size_of_c = size<same_as<number<n>, C>>;

  namespace emp
  {
    template<class L, class N, class C = mp::identity>
    using is_size_of = unpack<L, mp::is_size_of<N, C>>;

    template<class L, int_ n, class C = mp::identity>
    using is_size_of_c = unpack<L, mp::is_size_of_c<n, C>>;
  }
}
