#pragma once

#include <jln/mp/functional/identity.hpp>
#include <jln/mp/utility/unpack.hpp>

namespace jln::mp
{
  /// \ingroup list

  /// Retrieves the first element of a sequence.
  /// \treturn \value
  template<class C = identity>
  struct front
  {
    template<class x, class... xs>
    using f = JLN_MP_CALL_TRACE((C), x);
  };

  namespace emp
  {
    template<class L, class C = mp::identity>
    using front = unpack<L, front<C>>;
  }
}

namespace jln::mp
{
  /// \cond
  template<>
  struct front<identity>
  {
    template<class x, class...>
    using f = x;
  };
  /// \endcond
}
