#pragma once

#include "../functional/identity.hpp"
#include "../functional/call.hpp"
#include "number.hpp"

namespace jln::mp
{
  /// \ingroup number

  /// Narrowing convertion from \value to \number.
  /// \return \number
  template<class C = identity>
  struct as_number
  {
    template<class x>
    using f = call<C, number<int_{x::value}>>;
  };

  namespace emp
  {
    template<class x>
    using as_number = number<int_{x::value}>;
  }
}
