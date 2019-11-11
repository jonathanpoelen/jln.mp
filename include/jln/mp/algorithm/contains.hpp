#pragma once

#include "any_of.hpp"
#include "../utility/same_as.hpp"

namespace jln::mp
{
  template<class T, class C = identity>
  using contains = any_of<same_as<T>, C>;
}
