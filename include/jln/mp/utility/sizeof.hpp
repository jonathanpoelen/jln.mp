#pragma once

#include <jln/mp/number/number.hpp>
#include <jln/mp/functional/identity.hpp>
#include <jln/mp/detail/call_trace.hpp>

namespace jln::mp
{
  /// \ingroup trait

  /// Wrapper for sizeof keyword
  /// \treturn \number
  template<class C = identity>
  struct sizeof_
  {
    template<class x>
    using f = JLN_MP_CALL_TRACE(C, number<sizeof(x)>);
  };

  namespace emp
  {
    template<class x>
    using sizeof_ = number<sizeof(x)>;
  }
}
