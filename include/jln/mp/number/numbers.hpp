#pragma once

#include "number.hpp"
#include "../list/list.hpp"

namespace jln::mp
{
  template<class continuation = listify>
  struct numbers
  {
    template<int_... ns>
    using f = typename continuation::template f<number<ns>...>;
  };

  namespace eager
  {
    template<int_... vs>
    using numbers = list<number<vs>...>;
  }
}
