#pragma once

#include <jln/mp/list/listify.hpp>
#include <jln/mp/utility/unpack.hpp>
#include <jln/mp/functional/call.hpp>

namespace jln::mp
{
  /// \ingroup functional

  /// Invokes a \function with its two first arguments reversed.
  /// \treturn \sequence
  template<class C = listify>
  struct flip
  {
    template<class x0, class x1, class... xs>
    using f = JLN_MP_DCALL_XS(xs, C, x1, x0, xs...);
  };

  namespace emp
  {
    template<class L, class C = mp::listify>
    using flip = unpack<L, mp::flip<C>>;
  }
}
