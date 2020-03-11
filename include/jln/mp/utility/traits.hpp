#pragma once

#include "../functional/identity.hpp"
#include "../number/number.hpp"

#include <type_traits>

namespace jln::mp
{
  template<class C = identity>
  struct is_same
  {
    template<class x, class y>
    using f = number<std::is_same<x, y>::value>;
  };

  // TODO is_instance_of<list>
}
