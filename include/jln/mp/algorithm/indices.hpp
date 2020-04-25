#pragma once

#include "../algorithm/make_int_sequence.hpp"
#include "../list/size.hpp"

namespace jln::mp
{
  /// \ingroup number

  /// Replaces each element of a \sequence by its corresponding index.
  /// \return \sequence
  template<class C = listify>
  using indices = size<make_int_sequence<C>>;

  namespace emp
  {
    template<class L, class C = mp::listify>
    using indices = unpack<L, mp::indices<C>>;
  }
} // namespace jln::mp
