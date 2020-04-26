#pragma once

#include "list.hpp"
#include "../functional/call.hpp"
#include "../utility/unpack.hpp"

namespace jln::mp
{
  /// \ingroup list

  /// Appends \c x to the end of the sequence
  /// \treturn \sequence
  template<class x, class C = listify>
  struct push_back
  {
    template<class... xs>
    using f = call<C, xs..., x>;
  };

  namespace emp
  {
    template<class L, class T, class C = mp::listify>
    using push_back = unpack<L, mp::push_back<T, C>>;
  }
}
