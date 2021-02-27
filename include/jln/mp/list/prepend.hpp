#pragma once

#include <jln/mp/list/listify.hpp>
#include <jln/mp/list/push_front.hpp>
#include <jln/mp/utility/unpack.hpp>

namespace jln::mp
{
  /// \ingroup list

  /// Inserts elements at the start of \c L list.
  /// \treturn \sequence
  template<class L, class C = listify>
  using prepend = push_front<L, unpack<C>>;

  namespace emp
  {
    template<class L, class... xs>
    using prepend = unpack<L, listify, xs...>;
  }
}
