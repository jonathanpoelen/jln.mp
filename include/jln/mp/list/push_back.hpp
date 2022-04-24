#pragma once

#include <jln/mp/list/list.hpp>
#include <jln/mp/functional/call.hpp>
#include <jln/mp/utility/unpack.hpp>

namespace jln::mp
{
  /// \ingroup list

  /// Appends \c x to the end of the sequence.
  /// \treturn \sequence
  template<class x, class C = listify>
  struct push_back
  {
    template<class... xs>
    using f = JLN_MP_DCALL_TRACE_XS(xs, C, xs..., x);
  };

  namespace emp
  {
    template<class L, class T, class C = mp::listify>
    using push_back = unpack<L, mp::push_back<T, C>>;
  }

  /// \cond
  template<class x>
  struct push_back<x, listify>
  {
    template<class... xs>
    using f = list<xs..., x>;
  };
  /// \endcond
}
