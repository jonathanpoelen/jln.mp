#pragma once

#include "number.hpp"
#include "../list/listify.hpp"
#include "../functional/call.hpp"

namespace jln::mp
{
  /// \ingroup number

  template<class C = listify>
  struct numbers
  {
    template<int_... ns>
    using f = call<C, number<ns>...>;
  };

  /// \cond
  template<>
  struct numbers<listify>
  {
    template<int_... ns>
    using f = list<number<ns>...>;
  };
  /// \endcond

  namespace emp
  {
    template<int_... vs>
    using numbers = list<number<vs>...>;
  }
}
