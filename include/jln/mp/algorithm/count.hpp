#pragma once

#include "copy.hpp"
#include "../list/size.hpp"

namespace jln::mp
{
  template<class T, class C = listify>
  using count = copy<T, size<C>>;
}
