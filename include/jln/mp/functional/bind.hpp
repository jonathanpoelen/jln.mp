#pragma once

#include "partial.hpp"

namespace jln::mp
{
  /// \ingroup functional

  /// Partially apply a function to some arguments.
  /// \treturn \sequence
  template<class F, class... xs>
  struct bind
  {
    template<class... ys>
    using f = call<F, xs..., ys...>;
  };

  /// Partially apply a function to some arguments.
  /// \treturn \sequence
  template<class F, class... xs>
  struct reverse_bind
  {
    template<class... ys>
    using f = call<F, ys..., xs...>;
  };

  template<class F, class C>
  using bind1st = partial<F, C>;

  template<class F, class C>
  using bind2nd = partial<identity, F, C>;
} // namespace jln::mp
