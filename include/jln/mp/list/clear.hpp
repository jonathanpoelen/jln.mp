#pragma once

#include <jln/mp/list/listify.hpp>

namespace jln::mp
{
  /// \ingroup list

  /// Removes all elements from the \sequence.
  /// \treturn \value
  template<class C = listify>
  struct clear
  {
    template<class... xs>
    using f = JLN_MP_DCALL(sizeof...(xs) >= 0, C);
  };

  /// \cond
  template<>
  struct clear<listify>
  {
    template<class... xs>
    using f = list<>;
  };
  /// \endcond
}
