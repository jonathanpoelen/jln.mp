#pragma once

#include "../list/list.hpp"
#include "../list/push_front.hpp"
#include "../utility/unpack.hpp"

namespace jln::mp
{
  /// \ingroup list

  /// Inserts elements at the end of \c L list.
  /// \return \sequence
  template<class L, class C = listify>
  using append = push_front<L, unpack_append<C>>;

  namespace emp
  {
    template<class L, class... xs>
    using append = unpack_append<L, listify, xs...>;
  }
}
