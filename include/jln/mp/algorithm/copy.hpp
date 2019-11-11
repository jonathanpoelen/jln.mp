#pragma once

#include "copy_if.hpp"
#include "../utility/same_as.hpp"

namespace jln::mp
{
  template<class T, class C = listify>
  using copy = copy_if<same_as<T>, C>;
}
