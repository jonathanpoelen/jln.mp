#pragma once

#include <jln/mp/algorithm/index.hpp>
#include <jln/mp/utility/always.hpp>
#include <jln/mp/number/to_bool.hpp>
#include <jln/mp/number/operators.hpp>


namespace jln::mp
{
  /// \ingroup algorithm

  /// Perform a logical AND on the sequence of value.
  /// Conjunction is short-circuiting: if there is a template type
  /// argument `xs[i]` with `bool(Xi::value) == false`, then instantiating
  /// `conjunction<C>::f<xs[0], ..., xs[n-1]>` does not require the
  /// instantiation of `xs[j]::value` for j > i
  /// \treturn \bool
  /// \see disjunction, drop_while, take_while
#ifdef JLN_MP_DOXYGENATING
  template<class C = identity>
  struct conjunction
  {
    template<class... xs>
    using f;
  };
#else
  template<class C = identity>
  using conjunction = index_if<not_<>, always<false_, C>, always<true_, C>>;
#endif

  namespace emp
  {
    template<class L, class C = mp::identity>
    using conjunction = unpack<L, mp::conjunction<C>>;
  }
}
