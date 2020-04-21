#pragma once

#include "../functional/identity.hpp"
#include "../functional/call.hpp"
#include "number.hpp"

namespace jln::mp
{
  /// \ingroup number

  /// Convert a \value to a \boolean.
  /// \return \boolean
  template<class C = identity>
  struct to_bool
  {
    template<class x>
    using f = call<C, number<bool(x::value)>>;
  };

  namespace emp
  {
    template<class x>
    using to_bool = number<bool(x::value)>;
  }
}
