#pragma once

#include <jln/mp/list/listify.hpp>

namespace jln::mp
{
  /// \ingroup list

  /// Removes all elements from the \sequence.
  /// \treturn \number
  template<class C = listify>
  struct clear
  {
    template<class... xs>
    using f = JLN_MP_DCALL(sizeof...(xs) >= 0, C);
  };
}
