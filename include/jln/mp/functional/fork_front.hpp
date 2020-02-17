#pragma once

#include "call.hpp"

namespace jln::mp
{
  // TODO compose ?
  template<class F>
  struct fork_front
  {
    template<class... xs>
    using f = typename call<F, xs...>::template f<xs...>;
  };
}
