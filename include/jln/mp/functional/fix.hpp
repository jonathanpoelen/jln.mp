#pragma once

#include <jln/mp/functional/call.hpp>

namespace jln::mp
{
  /// \ingroup functional

  /// Invokes a function computing the fixed point of a function.
  /// \treturn \value
  /// \see recursively
  template<class C>
  struct fix
  {
    template<class... xs>
    using f = JLN_MP_DCALL_TRACE_XS(xs, C, fix<C>, xs...);
  };

  namespace emp
  {
    template<class F, class... xs>
    using fix = typename fix<F>::template f<xs...>;
  }
}
