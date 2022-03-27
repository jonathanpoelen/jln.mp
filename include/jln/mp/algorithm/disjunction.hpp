#pragma once

#include <jln/mp/algorithm/drop_until.hpp>
#include <jln/mp/utility/always.hpp>
#include <jln/mp/number/to_bool.hpp>


namespace jln::mp
{
  /// \ingroup algorithm

  /// Perform a logical OR on the sequence of value.
  /// Disjunction is short-circuiting: if there is a template type
  /// argument `xs[i]` with `bool(xs[i]::value) != false`, then instantiating
  /// `disjunction<C>::f<xs[0], ..., xs[n-1]>` does not require the
  /// instantiation of `xs[j]::value` for j > i
  /// \treturn \bool
  /// \see conjunction, drop_while, take_while
#ifdef JLN_MP_DOXYGENATING
  template<class C = identity>
  struct disjunction
  {
    template<class... xs>
    using f;
  };
#else
  template<class C = identity>
  using disjunction = drop_until<to_bool<>, always<true_, C>, always<false_, C>>;
#endif

  namespace emp
  {
    template<class L, class C = mp::identity>
    using disjunction = unpack<L, mp::disjunction<C>>;
  }
}
