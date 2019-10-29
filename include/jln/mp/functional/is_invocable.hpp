#pragma once

#include "try_invoke.hpp"

namespace jln::mp
{
  template<class F, class C = identity>
  using is_invocable = try_invoke<F, always<true_, C>, always<false_, C>>;

  namespace emp
  {
    template<class F, class... xs>
    using is_invocable = mp::call<mp::is_invocable<F>, xs...>;

    template<class L, class F, class C = mp::identity>
    inline constexpr bool is_invocable_v
      = eager<L, mp::is_invocable<C>>::value;
  }
}
