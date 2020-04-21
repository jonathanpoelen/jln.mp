#pragma once

#include "pop_front.hpp"
#include "../algorithm/rotate.hpp"

namespace jln::mp
{
  /// \ingroup list

  /// Remove the last element of sequence
  /// \pre sizeof...(xs) \> 0
  /// \return \sequence
  template<class C = listify>
  using pop_back = rotate<number<-1>, pop_front<C>>;

  namespace emp
  {
    template<class L, class C = mp::listify>
    using pop_back = unpack<L, mp::pop_back<C>>;
  }
}
