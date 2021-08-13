#pragma once

#include <jln/mp/algorithm/drop_while.hpp>
#include <jln/mp/list/is_empty.hpp>


namespace jln::mp
{
  /// \ingroup algorithm

  /// Perform a logical AND on the sequence of value.
  /// Conjunction is short-circuiting: if there is a template type argument Xi
  /// with `Xi::value == false`, then instantiating
  /// `disjunction<X1, ..., XN>::value` does not require the instantiation of
  /// `Xj::value` for j > i
  /// \treturn \bool
#ifdef JLN_MP_DOXYGENATING
  template<class C = identity>
  struct disjunction
  {
    template<class... X>
    using f;
  };
#else
  template<class C = identity>
  using conjunction = drop_while<identity, is_empty<C>>;
#endif

  namespace emp
  {
    template<class L, class C = mp::identity>
    using conjunction = unpack<L, mp::conjunction<C>>;
  }
}
