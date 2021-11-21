#pragma once

#include <jln/mp/functional/identity.hpp>
#include <jln/mp/detail/call_trace.hpp>

namespace jln::mp
{
  /// \ingroup utility

  /// Always evaluate at an arbitrary value.
  /// \post result = x
  /// \treturn value
  template<class x, class C = identity>
  struct always
  {
    template<class... xs>
    using f = JLN_MP_CALL_TRACE((C), x);
  };

  template<class x>
  struct always<x, identity>
  {
    template<class... xs>
    using f = x;
  };
}
