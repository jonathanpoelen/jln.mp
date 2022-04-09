#pragma once

#include <jln/mp/algorithm/pairwise.hpp>
#include <jln/mp/number/operators.hpp>
#include <jln/mp/utility/always.hpp>

namespace jln::mp
{
  /// \ingroup algorithm

  /// Checks wheteher a \sequence is sorted.
  /// \treturn \number
  template<class Cmp = less<>, class C = identity>
  struct is_sorted
  : pairwise_with<Cmp, and_<>>
  {
    #ifdef JLN_MP_DOXYGENATING
    template<class... xs>
    using f;
    #endif
  };

  namespace emp
  {
    template<class L, class Cmp = mp::less<>, class C = mp::identity>
    using is_sorted = unpack<L, mp::is_sorted<Cmp, C>>;
  }
}
