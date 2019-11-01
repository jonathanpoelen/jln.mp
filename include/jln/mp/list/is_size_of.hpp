#pragma once

#include "size.hpp"
#include "../utility/same_as.hpp"
#include "../number/operators.hpp"

namespace jln::mp
{
  template<class N, class C = identity>
  using is_size_of = size<same_as<N, C>>;

  template<int_ n, class C = identity>
  using is_size_of_c = size<same_as<number<n>, C>>;

  template<class C = identity>
  using is_size_of_1 = is_size_of<number<1>, C>;

  template<class C = identity>
  using is_size_of_2 = is_size_of<number<2>, C>;

  template<class N, class C = identity>
  using is_size_larger_than = size<greater_than<N, C>>;

  template<int_ n, class C = identity>
  using is_size_larger_than_c = size<greater_than<number<n>, C>>;

  namespace emp
  {
    template<class L, class N, class C = mp::identity>
    using is_size_of = eager<L, mp::is_size_of<N, C>>;

    template<class L, int_ n, class C = mp::identity>
    using is_size_of_c = eager<L, mp::is_size_of_c<n, C>>;

    template<class L, class C = mp::identity>
    using is_size_of_1 = eager<L, is_size_of_1<C>>;

    template<class L, class C = mp::identity>
    using is_size_of_2 = eager<L, is_size_of_2<C>>;

    template<class L, class N, class C = mp::identity>
    using is_size_larger_than = eager<L, is_size_larger_than<N, C>>;

    template<class L, int_ n, class C = mp::identity>
    using is_size_larger_than_c = eager<L, is_size_larger_than_c<n, C>>;
  }
}
