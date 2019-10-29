#pragma once

#include "../functional/bind.hpp"

namespace jln::mp
{
  template<class... xs>
  class list {};

  using listify = cfe<list>;
} // namespace jln::mp
