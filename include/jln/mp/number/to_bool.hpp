#pragma once

#include <jln/mp/functional/identity.hpp>
#include <jln/mp/functional/call.hpp>
#include <jln/mp/number/number.hpp>

namespace jln::mp
{
  /// \ingroup number

  /// Converts a \value to a \bool.
  /// \treturn \bool
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
