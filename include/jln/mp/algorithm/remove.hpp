#pragma once

#include "remove_if.hpp"
#include "../utility/same_as.hpp"

namespace jln::mp
{
  template<class T, class C = listify>
  using remove = remove_if<same_as<T>, C>;

  namespace emp
  {
    template<class L, class T, class C = mp::listify>
    using remove = eager<L, mp::remove<T, C>>;
  }
}
