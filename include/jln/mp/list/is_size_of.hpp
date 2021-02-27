#pragma once

#include <jln/mp/list/size.hpp>
#include <jln/mp/utility/is.hpp>

namespace jln::mp
{
  /// \ingroup list

  template<class N, class C = identity>
  using is_size_of = size<is<N, C>>;

  template<int_ n, class C = identity>
  using is_size_of_c = size<is<number<n>, C>>;

  namespace emp
  {
    template<class L, class N, class C = mp::identity>
    using is_size_of = unpack<L, mp::is_size_of<N, C>>;

    template<class L, int_ n, class C = mp::identity>
    using is_size_of_c = unpack<L, mp::is_size_of_c<n, C>>;
  }
}
