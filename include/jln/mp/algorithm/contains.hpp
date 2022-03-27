#pragma once

#include <jln/mp/algorithm/drop_until.hpp>
#include <jln/mp/algorithm/any_of.hpp>
#include <jln/mp/utility/is.hpp>

namespace jln::mp
{
  /// \ingroup algorithm

  /// Checks whether a \value is contained in a \list.
  /// \treturn \bool
  template<class x, class C = identity>
  using contains = drop_until<is<x>, always<true_, C>, always<false_, C>>;

  namespace emp
  {
    template<class L, class x, class C = mp::identity>
    using contains = unpack<L, mp::contains<x, C>>;
  }
}
