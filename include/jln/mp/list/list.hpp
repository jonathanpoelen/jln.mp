#pragma once

#include "../functional/function.hpp"

namespace jln::mp
{
  /// \ingroup list

  template<class... xs>
  class list {};

  /// \treturn \link list
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
