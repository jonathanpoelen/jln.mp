#pragma once

#include "call.hpp"

namespace jln::mp
{
  /// \ingroup functional

  /// Invoke twice.
  /// \treturn \value
  template<class F>
  struct fork_front
  {
    template<class... xs>
    using f = typename call<F, xs...>::template f<xs...>;
  };
}
