#pragma once

#include <jln/mp/functional/identity.hpp>
#include <jln/mp/functional/call.hpp>
#include <jln/mp/number/number.hpp>

namespace jln::mp
{
  /// \ingroup number

  /// Narrowing convertion from \value to \bool.
  /// \treturn \bool
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
