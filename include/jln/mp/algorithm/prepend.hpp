#pragma once

#include "../list/list.hpp"
#include "../list/push_front.hpp"
#include "../utility/unpack_append.hpp"

namespace jln::mp
{
  template<class L, class C = listify>
  using prepend = push_front<L, unpack_append<C>>;
}
