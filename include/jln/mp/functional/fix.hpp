#pragma once

#include <jln/mp/functional/call.hpp>

namespace jln::mp
{
  /// \ingroup functional

  /// Invokes a function computing the fixed point of a function.
  /// \treturn \value
  /// \see recurse, recurse_fix
  template<class C>
  struct fix
  {
    template<class... xs>
    using f = call<C, fix<C>, xs...>;
  };

  namespace emp
  {
    template<class F, class... xs>
    using fix = typename fix<F>::template f<xs...>;
  }
}
