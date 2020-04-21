#pragma once

#include "front.hpp"
#include "../algorithm/rotate.hpp"

namespace jln::mp
{
  /// \ingroup list

  /// Retrieves the last element of a sequence.
  /// \return \value
  template<class C = identity>
  using back = rotate<number<-1>, front<C>>;

  namespace emp
  {
    template<class L, class C = mp::identity>
    using back = unpack<L, mp::back<C>>;
  }
}
