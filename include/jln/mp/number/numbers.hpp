#pragma once

#include "number.hpp"
#include "../list/list.hpp"
#include "../functional/call.hpp"

namespace jln::mp
{
  template<class C = listify>
  struct numbers
  {
    template<int_... ns>
    using f = call<C, number<ns>...>;
  };

  template<>
  struct numbers<listify>
  {
    template<int_... ns>
    using f = list<number<ns>...>;
  };

  namespace emp
  {
    template<int_... vs>
    using numbers = list<number<vs>...>;
  }
}
