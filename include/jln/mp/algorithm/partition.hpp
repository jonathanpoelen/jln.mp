#pragma once

#include <jln/mp/algorithm/remove.hpp>
#include <jln/mp/algorithm/copy.hpp>
#include <jln/mp/functional/tee.hpp>

namespace jln::mp
{
  /// \ingroup group

  // TODO remove <-> copy
  // Pred::f<xs>::value... -> mk_list<b>::f<xs> | mk_list<!b>::f<xs>

  /// Splits a \list in two according to a predicate.
  /// The first value contains all elements for which the predicate returns true,
  /// the second value contains all elements for which predicate returns false
  /// \treturn \sequence of two \values
  template<class Pred, class F = listify, class C = listify>
  using partition_with = tee<copy_if<Pred, F>, remove_if<Pred, F>, C>;

  /// Splits a \list in two according to a predicate.
  /// The first value contains all elements for which the predicate returns true,
  /// the second value contains all elements for which predicate returns false
  /// \treturn \sequence of two \lists
  /// \see partition_with
  template<class Pred, class C = listify>
  using partition = tee<copy_if<Pred>, remove_if<Pred>, C>;

  namespace emp
  {
    template<class L, class Pred, class F = mp::listify, class C = mp::listify>
    using partition_with = unpack<L, mp::partition_with<Pred, F, C>>;

    template<class L, class Pred, class C = mp::listify>
    using partition = unpack<L, mp::partition<Pred, C>>;
  }
}
