// SPDX-FileCopyrightText: 2023 Jonathan Poelen <jonathan.poelen@gmail.com>
// SPDX-License-Identifier: MIT
#pragma once

#include <jln/mp/functional/if.hpp>

namespace jln::mp
{
  /// \ingroup functional

  /// Returns \c TC::f<x> if \c Pred::f<x>, otherwise returns \c x.
  /// \treturn \value
  template<class Pred, class TC>
  using apply_or_identity = if_<Pred, TC, identity>;

  namespace emp
  {
    template<class Pred, class TC, class x>
    using apply_or_identity = typename mp::if_<Pred, TC, mp::identity>::template f<x>;
  }
}
