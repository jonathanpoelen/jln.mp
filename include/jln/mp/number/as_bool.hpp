#pragma once

#include "../functional/identity.hpp"
#include "../functional/call.hpp"
#include "number.hpp"

namespace jln::mp
{
  /// \ingroup number

  /// Narrowing convertion from \value to \boolean.
  /// \return \boolean
  template<class C = identity>
  struct as_bool
  {
    template<class x>
    using f = call<C, number<bool{x::value}>>;
  };

  namespace emp
  {
    template<class x>
    using as_bool = number<bool{x::value}>;
  }
}
