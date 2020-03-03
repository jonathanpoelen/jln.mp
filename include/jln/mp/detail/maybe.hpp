#pragma once

#include "../functional/contract.hpp"

namespace jln::mp::detail
{
  template<class x>
  struct maybe
  {
    using type = x;
  };

  template<>
  struct maybe<na>
  {};
}
