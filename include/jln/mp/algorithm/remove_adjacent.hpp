#pragma once

#include "../algorithm/remove_adjacent_if.hpp"
#include "../algorithm/same.hpp"

namespace jln::mp
{
  template<class C = listify>
  using remove_adjacent = remove_adjacent_if<same<>, C>;
}
