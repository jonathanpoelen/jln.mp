#pragma once

#include "../functional/identity.hpp"
#include "../functional/call.hpp"
#include "val.hpp"

namespace jln::mp
{
  /// \ingroup value

  /// Converts \c x to \val.
  /// \pre \c emp::has_value<x> == \c true
  /// \treturn \bool
  template<class C = identity>
  struct as_val
  {
    template<class x>
#if __cplusplus >= 201703L
    using f = mp::call<C, val<x::value>>;
#else
    using f = mp::call<C, typed_value<decltype(x::value), x::value>>;
#endif
  };

  namespace emp
  {
    template<class x>
#if __cplusplus >= 201703L
    using f = val<x::value>;
#else
    using f = typed_value<decltype(x::value), x::value>;
#endif
  }
}
