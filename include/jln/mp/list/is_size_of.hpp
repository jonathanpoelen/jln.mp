#pragma once

#include "size.hpp"
#include "../utility/same_as.hpp"
#include "../number/operators.hpp"

namespace jln::mp
{
  template<class N, class C = identity>
  using is_size_of = size<same_as<N, C>>;

  template<class C = identity>
  using is_size_of_1 = is_size_of<number<1>, C>;

  template<class C = identity>
  using is_size_of_2 = is_size_of<number<2>, C>;

  template<class N, class C = identity>
  using is_size_larger_than = size<greater_than<N, C>>;
}
