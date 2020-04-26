#pragma once

#include "fold_left.hpp"
#include "../list/join.hpp"
#include "../list/push_front.hpp"
#include "../functional/call.hpp"


namespace jln::mp
{
  /// \ingroup algorithm

  /// Unpack each \c seqs then use \c fold_left.
  /// \pre emp::is_list\<seqs\> && ...
  /// \semantics
  ///   Equivalent to
  ///   \code
  ///   fold_left\<F, C\>::f\<state, ...seqs[:]\>
  ///   \endcode
  /// \treturn \value
  template<class F, class C = identity>
  struct accumulate
  {
    template<class state, class... seqs>
    using f = call<join<push_front<state, fold_left<F, C>>>, seqs...>;
  };

  namespace emp
  {
    template<class L, class state, class F, class C = mp::identity>
    using accumulate = unpack<L,
      mp::push_front<state, mp::accumulate<F, C>>>;
  }
}
