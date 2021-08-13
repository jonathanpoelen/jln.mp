#pragma once

#include <jln/mp/algorithm/drop_while.hpp>
#include <jln/mp/functional/if.hpp>
#include <jln/mp/utility/always.hpp>
#include <jln/mp/number/as_bool.hpp>
#include <jln/mp/number/to_bool.hpp>
#include <jln/mp/number/operators.hpp>
#include <jln/mp/list/size.hpp>


namespace jln::mp
{
  /// \ingroup algorithm

  /// Perform a logical OR on the sequence of value.
  /// Disjunction is short-circuiting: if there is a template type argument Xi
  /// with `Xi::value != false`, then instantiating
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
  using disjunction = if_<size<>, drop_while<as_bool<not_<>>, size<to_bool<C>>>, always<false_, C>>;
#endif

  namespace emp
  {
    template<class L, class C = mp::identity>
    using disjunction = unpack<L, mp::disjunction<C>>;
  }
}
