#pragma once

#include "../functional/function.hpp"

namespace jln::mp
{
  template<class... xs>
  class list {};

  /// \return \link list
  using listify = cfe<list>;

  /// \cond
  template<>
  struct cfe<list, identity>
  {
    template<class... xs>
    using f = list<xs...>;
  };
  /// \endcond
} // namespace jln::mp
