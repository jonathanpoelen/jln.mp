#pragma once

#include <jln/mp/number/number.hpp>
#include <jln/mp/functional/call.hpp>
#include <jln/mp/functional/identity.hpp>

namespace jln::mp
{
  /// \ingroup trait

  /// Wrapper for alignof keyword
  /// \treturn \number
  template<class C = identity>
  struct alignof_
  {
    template<class x>
    using f = JLN_MP_CALL_TRACE(C, number<alignof(x)>);
  };

  namespace emp
  {
    template<class x>
    using alignof_ = number<alignof(x)>;
  }
}
