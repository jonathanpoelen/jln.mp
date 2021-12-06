#pragma once

#include <jln/mp/functional/try.hpp>

namespace jln::mp
{
  /// \ingroup functional

  /// Checks whether \c F::f<xs...> is invocable.
  /// \pre \c F::f<xs...> must be a SFINAE compatible expression
  /// \treturn \bool
  template<class F, class C = identity>
  using is_invocable = try_<F, always<true_, C>, always<false_, C>>;

  namespace emp
  {
    template<class F, class... xs>
    using is_invocable = typename mp::is_invocable<F>::template f<xs...>;
  }
}
