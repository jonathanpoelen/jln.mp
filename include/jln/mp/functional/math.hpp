#pragma once

#include "operators.hpp"
#include "../algorithm/fold_left.hpp"

namespace jln::mp
{
  template<class C = identity>
  // TODO fold_left<fork_front<less<cfe<conditional>>>, C> ?
  using min = fold_left<if_<less<>, mp::at0<>, mp::at1<>>, C>;

  template<class C = identity>
  using max = fold_left<if_<greater<>, mp::at0<>, mp::at1<>>, C>;

  template<class C = identity>
  using abs = mp::demux<
    mp::identity,
    mp::neg<>,
    if_<greater<>, mp::at0<C>, mp::at1<C>>
  >;

  // TODO pow
}
