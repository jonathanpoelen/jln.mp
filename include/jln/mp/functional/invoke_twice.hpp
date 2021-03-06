#pragma once

#include <jln/mp/functional/call.hpp>

namespace jln::mp
{
  /// \ingroup functional

  /// Invokes twice.
  /// \treturn \value
  template<class F>
  struct invoke_twice
  {
    template<class... xs>
    using f = typename call<F, xs...>::template f<xs...>;
  };
}
