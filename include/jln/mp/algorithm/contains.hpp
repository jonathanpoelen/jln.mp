#pragma once

#include "any_of.hpp"
#include "../utility/same_as.hpp"

namespace jln::mp
{
  // TODO impl() -> decltype((static_cast<x*>(inherit<xs...>*), true_)) ? see unique
  // TODO find<x, always<true_, C>, always<false_, C>> ?
  template<class T, class C = identity>
  using contains = any_of<same_as<T>, C>;

  namespace emp
  {
    template<class L, class T, class C = mp::identity>
    using contains = eager<L, mp::contains<T, C>>;
  }
}
