#pragma once

#include "../functional/lift.hpp"

namespace jln::mp
{
  /// \ingroup list

  template<class... xs>
  class list {};

  /// \treturn \link list
  using listify = lift<list>;

  /// \cond
  template<>
  struct lift<list, identity>
  {
    template<class... xs>
    using f = list<xs...>;
  };
  /// \endcond
} // namespace jln::mp
