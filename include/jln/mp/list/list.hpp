#pragma once

#include "../functional/bind.hpp"

namespace jln::mp
{
  template<class... vals>
  class list {};

  using listify = cfe<list>;
}
