#pragma once

#include <jln/mp/list/front.hpp>
#include <jln/mp/algorithm/rotate.hpp>

namespace jln::mp
{
  /// \ingroup list

  /// Retrieves the last element of a sequence.
  /// \treturn \value
  template<class C = identity>
  using back = rotate<number<-1>, front<C>>;

  namespace emp
  {
    template<class L, class C = mp::identity>
    using back = unpack<L, mp::back<C>>;
  }
}
