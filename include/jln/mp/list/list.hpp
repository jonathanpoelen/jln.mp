#pragma once

#include "../functional/function.hpp"

namespace jln::mp
{
  template<class... xs>
  class list {};

  using listify = cfe<list>;

  template<>
  struct cfe<list, identity>
  {
    template<class... xs>
    using f = list<xs...>;
  };
} // namespace jln::mp
