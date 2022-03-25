#pragma once

#include <jln/mp/algorithm/transform.hpp>
#include <jln/mp/algorithm/group.hpp>
#include <jln/mp/list/front.hpp>

namespace jln::mp
{
  /// List unique elements, preserving order.
  /// Remember only the element just seen.
  /// \semantics
  ///   \code
  ///   unique_justseen_by<same<>>::f<void, void, int, void>
  ///   == list<void, int, void>
  ///   \endcode
  /// \treturn \sequence
  template<class Cmp, class C = listify>
  using unique_justseen_by = group_by<Cmp, transform<unpack<front<>>, C>>;

  template<class C = listify>
  using unique_justseen = unique_justseen_by<same<>, C>;

  namespace emp
  {
    template<class L, class Cmp, class C = mp::listify>
    using unique_justseen_by = unpack<L, mp::unique_justseen_by<Cmp, C>>;

    template<class L, class C = mp::listify>
    using unique_justseen = unpack<L, mp::unique_justseen<C>>;
  }
}
