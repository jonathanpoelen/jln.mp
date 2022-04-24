#pragma once

#include <jln/mp/functional/identity.hpp>
#include <jln/mp/functional/call.hpp>

namespace jln::mp
{
  /// \ingroup trait

  /// Function for \c x::type.
  /// \treturn \value
  template<class C = identity>
  struct type_
  {
    template<class x>
    using f = JLN_MP_CALL_TRACE(C, typename x::type);
  };

  namespace emp
  {
    template<class x>
    using type_ = typename x::type;
  }

  /// \cond
  template<>
  struct type_<identity>
  {
    template<class x>
    using f = typename x::type;
  };
  /// \endcond
}
