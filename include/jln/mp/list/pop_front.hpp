#pragma once

#include <jln/mp/list/drop_front.hpp>

namespace jln::mp
{
  /// \ingroup list

  /// Remove the first element of sequence
  /// \pre `sizeof...(xs) > 0`
  /// \treturn \sequence
  template<class C = listify>
  using pop_front = drop_front_c<1, C>;

  namespace emp
  {
    template<class L, class C = mp::listify>
    using pop_front = drop_front_c<L, 1, C>;
  }
}
