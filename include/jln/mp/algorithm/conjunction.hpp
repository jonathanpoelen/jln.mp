#pragma once

#include <jln/mp/algorithm/all_of.hpp>
#include <jln/mp/number/to_bool.hpp>

namespace jln::mp
{
  /// \ingroup algorithm

  /// Perform a logical AND on the sequence of value.
  /// Conjunction is short-circuiting: if there is a template type
  /// argument `xs[i]` with `bool(Xi::value) == false`, then instantiating
  /// `conjunction<C>::f<xs[0], ..., xs[n-1]>` does not require the
  /// instantiation of `xs[j]::value` for `j > i`
  /// \treturn \bool
  /// \see disjunction, drop_while, take_while
  template<class C = identity>
  using conjunction = all_of<to_bool<>, C>;

  namespace emp
  {
    template<class L, class C = mp::identity>
    using conjunction = unpack<L, mp::conjunction<C>>;
  }
}
