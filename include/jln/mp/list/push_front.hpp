#pragma once

#include <jln/mp/list/list.hpp>
#include <jln/mp/utility/unpack.hpp>
#include <jln/mp/functional/call.hpp>

namespace jln::mp
{
  /// \ingroup list

  /// Appends \c x to the beginning of the sequence.
  /// \treturn \sequence
  template<class x, class C = listify>
  struct push_front
  {
    template<class... xs>
    using f = JLN_MP_DCALL_XS(xs, C, x, xs...);
  };

  namespace emp
  {
    template<class L, class T, class C = mp::listify>
    using push_front = unpack<L, mp::push_front<T, C>>;
  }
}

