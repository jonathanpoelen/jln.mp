#pragma once

#include <jln/mp/functional/if.hpp>

namespace jln::mp
{
  /// \ingroup functional

  /// Return \p TC::f<x> if \p Pred::f<x>, otherwise returns \p x.
  /// \treturn \value
  template<class Pred, class TC>
  using apply_or_identity = if_<Pred, TC, identity>;

  namespace emp
  {
    template<class Pred, class TC, class x>
    using apply_or_identity = typename mp::if_<Pred, TC, mp::identity>::template f<x>;
  }
}
