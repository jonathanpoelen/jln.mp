#pragma once

#include "../utility/same_as.hpp"
#include "replace_if.hpp"

namespace jln::mp
{
  template<class T, class U, class C = listify>
  using replace = replace_if<same_as<T>, U, C>;

  namespace emp
  {
    template<class L, class T, class U, class C = mp::listify>
    using replace = eager<L, mp::replace<T, U, C>>;
  }
}
