#pragma once

#include <jln/mp/detail/enumerate.hpp>
#include <jln/mp/algorithm/cartesian.hpp>
#include <jln/mp/algorithm/repeat.hpp>

namespace jln::mp
{
  /// \ingroup algorithm

  /// Computes all possible combinations (with repetition) from the elements in a \sequence.
  /// \treturn \sequence of \list
  template<class C = listify>
  struct combine
  {
    template<class... xs>
    using f = typename repeat_c<sizeof...(xs), cartesian<C>>
      ::template f<list<xs...>>;
  };

  namespace emp
  {
    template<class L, class C = mp::listify>
    using combine = unpack<L, mp::combine<C>>;
  }
}
