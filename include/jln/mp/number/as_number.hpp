#pragma once

#include <jln/mp/functional/identity.hpp>
#include <jln/mp/detail/call_trace.hpp>
#include <jln/mp/functional/call.hpp>
#include <jln/mp/number/number.hpp>

namespace jln::mp
{
  /// \ingroup number

  /// Narrowing convertion from \value to \number.
  /// \treturn \number
  template<class C = identity>
  struct as_number
  {
    template<class x>
    using f = JLN_MP_CALL_TRACE(C, number<int_{x::value}>);
  };

  namespace emp
  {
    template<class x>
    using as_number = number<int_{x::value}>;
  }
}
