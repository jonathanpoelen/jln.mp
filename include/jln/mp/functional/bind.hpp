#pragma once

#include <jln/mp/functional/partial.hpp>

namespace jln::mp
{
  /// \ingroup functional

  /// Partially apply a function to some arguments.
  /// \treturn \sequence
  template<class F, class... xs>
  struct bind
  {
    template<class... ys>
    using f = JLN_MP_DCALL_TRACE_XS(ys, F, xs..., ys...);
  };

  /// Partially apply a function to some arguments.
  /// \treturn \sequence
  template<class F, class... xs>
  struct reverse_bind
  {
    template<class... ys>
    using f = JLN_MP_DCALL_TRACE_XS(ys, F, ys..., xs...);
  };

  template<class F, class C>
  using bind1st = partial<F, C>;

  template<class F, class C>
  using bind2nd = partial<identity, F, C>;
} // namespace jln::mp
