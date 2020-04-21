#pragma once

#include "../functional/call.hpp"

namespace jln::mp
{
  /// \ingroup functional

  /// Invoke a function computing the fixed point of a function.
  /// \return \value
  /// \see recurse
  /// \see recurse_fix
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
