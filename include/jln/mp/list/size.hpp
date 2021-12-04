#pragma once

#include <jln/mp/number/number.hpp>
#include <jln/mp/utility/unpack.hpp>

namespace jln::mp
{
  /// \ingroup list

  /// Returns the number of elements in a \c xs.
  /// \treturn \number
  template<class C = identity>
  struct size
  {
    template<class... xs>
    using f = JLN_MP_CALL_TRACE(C, number<sizeof...(xs)>);
  };

  namespace emp
  {
    template<class L, class C = mp::identity>
    using size = unpack<L, mp::size<C>>;
  }
}
