#pragma once

#include <jln/mp/functional/identity.hpp>

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
    using f = typename C::template f<x>;
  };

  template<class x>
  struct always<x, identity>
  {
    template<class... xs>
    using f = x;
  };
}
