#pragma once

#include "unpack.hpp"

namespace jln::mp
{
  // TODO emp::unpack
  template<class L, class C>
  using eager = typename mp::unpack<C>::template f<L>;
}
