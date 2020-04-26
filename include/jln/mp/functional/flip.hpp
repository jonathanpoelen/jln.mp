#pragma once

#include "../list/list.hpp"
#include "../utility/unpack.hpp"
#include "call.hpp"

namespace jln::mp
{
  /// \ingroup functional

  /// Invoke a \function with its two first arguments reversed.
  /// \treturn \sequence
  template<class C = listify>
  struct flip
  {
    template<class x0, class x1, class... xs>
    using f = call<C, x1, x0, xs...>;
  };

  namespace emp
  {
    template<class L, class C = mp::listify>
    using flip = unpack<L, mp::flip<C>>;
  }
}
