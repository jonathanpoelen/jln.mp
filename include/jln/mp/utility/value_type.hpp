#pragma once

#include <jln/mp/functional/identity.hpp>

namespace jln::mp
{
  /// \ingroup trait

  /// Function for \c x::value_type.
  /// \treturn \value
  template<class C = identity>
  struct value_type
  {
    template<class x>
    using f = typename C::template f<typename x::value_type>;
  };

  template<>
  struct value_type<identity>
  {
    template<class x>
    using f = typename x::value_type;
  };

  namespace emp
  {
    template<class x>
    using value_type = typename x::value_type;
  }
}
