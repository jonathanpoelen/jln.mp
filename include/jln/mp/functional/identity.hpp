#pragma once

namespace jln::mp
{
  struct identity
  {
    template<class x>
    using f = x;
  };

  namespace eager
  {
    template<class x>
    using identity = x;
  }
}
