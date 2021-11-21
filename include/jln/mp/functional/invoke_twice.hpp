#pragma once

#include <jln/mp/functional/call.hpp>
#include <jln/mp/detail/call_trace.hpp>

namespace jln::mp
{
  /// \ingroup functional

  /// Invokes twice.
  /// \treturn \value
  template<class F>
  struct invoke_twice
  {
    template<class... xs>
    using f = JLN_MP_CALL_TRACE((call<F, xs...>), xs...);
  };
}
