#pragma once

#include "fold_left.hpp"
#include "zip.hpp"
#include "../list/push_front.hpp"
#include "../functional/flip.hpp"
#include "../functional/call.hpp"


namespace jln::mp
{
  /// \ingroup algorithm

  /// Computes the recursive invocation of \c F with the result of the previous
  /// invocation and each element of one or more \lists traversed in parallel
  /// from the beginning to the end.
  /// \pre all \c seqs must be the same size
  /// \semantics
  ///   Equivalent to
  ///   \code
  ///   C::f<fold_left<F>::f<
  ///     ...
  ///     fold_left<F>::f<fold_left<F>::f<state, ...seqs[:][0]>, ...seqs[:][1]>
  ///     ...,
  ///     ...seqs[:][n-1]>
  ///   >>
  ///   \endcode
  /// \treturn \value
  template<class F, class C = identity>
  struct accumulate
  {
    template<class state, class... seqs>
    using f = call<zip<push_front<state, fold_left<flip<unpack<F>>, C>>>, seqs...>;
  };

  namespace emp
  {
    template<class L, class state, class F, class C = mp::identity>
    using accumulate = unpack<L,
      mp::zip<mp::push_front<state, mp::fold_left<mp::flip<mp::unpack<F>>, C>>>>;
  }
}
