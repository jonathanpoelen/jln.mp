#pragma once

#include "../algorithm/any_of.hpp"

namespace jln::mp
{
  /// \ingroup algorithm

  /// Checks whether a predicate does not hold for any element of a \sequence.
  /// \return \boolean
  template<class Pred, class C = identity>
  using none_of = any_of<Pred, not_<C>>;

  namespace emp
  {
    template<class L, class Pred, class C = mp::identity>
    using none_of = unpack<L, mp::none_of<Pred, C>>;
  }
} // namespace jln::mp
