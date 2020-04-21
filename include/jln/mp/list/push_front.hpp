#pragma once

#include "list.hpp"
#include "../utility/unpack.hpp"
#include "../functional/call.hpp"

namespace jln::mp
{
  /// \ingroup list

  /// Appends \c x to the beginning of the sequence.
  /// \return \sequence
  template<class x, class C = listify>
  struct push_front
  {
    template<class... xs>
    using f = call<C, x, xs...>;
  };

  namespace emp
  {
    template<class L, class T, class C = mp::listify>
    using push_front = unpack<L, mp::push_front<T, C>>;
  }
}

