#pragma once

#include <jln/mp/algorithm/any_of.hpp>
#include <jln/mp/number/to_bool.hpp>

namespace jln::mp
{
  /// \ingroup algorithm

  /// Perform a logical OR on the sequence of value.
  /// Disjunction is short-circuiting: if there is a template type
  /// argument `xs[i]` with `bool(xs[i]::value) != false`, then instantiating
  /// `disjunction<C>::f<xs[0], ..., xs[n-1]>` does not require the
  /// instantiation of `xs[j]::value` for `j > i`
  /// \treturn \bool
  /// \see conjunction, drop_while, take_while
  template<class C = identity>
  using disjunction = any_of<to_bool<>, C>;

  namespace emp
  {
    template<class L, class C = mp::identity>
    using disjunction = unpack<L, mp::disjunction<C>>;
  }
}
