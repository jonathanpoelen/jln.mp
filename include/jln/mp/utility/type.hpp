#pragma once

#include "../functional/identity.hpp"

namespace jln::mp
{
  /// \ingroup trait

  /// Function for \c x::type.
  /// \treturn \value
  template<class C = identity>
  struct type_
  {
    template<class x>
    using f = typename C::template f<typename x::type>;
  };

  template<>
  struct type_<identity>
  {
    template<class x>
    using f = typename x::type;
  };

  namespace emp
  {
    template<class x>
    using type_ = typename x::type;
  }
}
