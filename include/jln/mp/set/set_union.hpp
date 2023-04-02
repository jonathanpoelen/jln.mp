#pragma once

#include <jln/mp/list/join.hpp>
#include <jln/mp/set/set_push_back_elements.hpp>


namespace jln::mp
{
  /// \ingroup set

  /// Appends to the end of the \set \c Set the elements of \c Ls which are not already in \c Set.
  /// \treturn \set
  /// \pre \c emp::is_unique<Set>
  /// \post \c emp::is_unique<result>
  template<class C = listify>
  struct set_union
  {
    template<class Set, class... Ls>
    using f = typename unpack<set_push_back_elements<C>>::template f<emp::join<Ls...>, Set>;
  };

  namespace emp
  {
    template<class Set, class... Ls>
    using set_union = mp::set_union<>::f<Set, Ls...>;
  }
}
