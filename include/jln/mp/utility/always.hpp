#pragma once

#include "../functional/identity.hpp"

namespace jln::mp
{
  /// \ingroup utility

  /// Always evaluate at an arbitrary value.
  /// \post result = x
  /// \return value
  template<class x, class C = identity>
  struct always
  {
    template<class... xs>
    using f = typename C::template f<x>;
  };
}
