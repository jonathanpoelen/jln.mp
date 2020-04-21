#pragma once

#include "../number/number.hpp"
#include "../utility/unpack.hpp"

namespace jln::mp
{
  /// \ingroup list

  /// Returns the number of elements in a \c xs.
  /// \return \number
  template<class C = identity>
  struct size
  {
    template<class... xs>
    using f = typename C::template f<number<sizeof...(xs)>>;
  };

  namespace emp
  {
    template<class L, class C = mp::identity>
    using size = unpack<L, mp::size<C>>;
  }
}
