#pragma once

#include "index.hpp"
#include "../list/take.hpp"
#include "../utility/always.hpp"
#include "../functional/lift.hpp"
#include "../functional/tee.hpp"
#include "../functional/invoke_twice.hpp"

namespace jln::mp
{
  /// \cond
  namespace detail
  {
    template<class>
    struct _take_while;
  }
  /// \endcond

  /// \ingroup algorithm

  /// Take elements from a \sequence while the predicate is satisfied.
  /// \treturn \sequence
  template<class Pred, class C = listify, class NC = C>
  using take_while = invoke_twice<index_if<
    Pred, tee<identity, always<C>, lift<take>>, always<NC>>>;

  namespace emp
  {
    template<class L, class Pred, class C = mp::listify, class NC = C>
    using take_while = unpack<L, mp::take_while<Pred, C, NC>>;
  }
}

/// \cond
namespace jln::mp::detail
{
  template<class n>
  struct _take_while
  {
    template<class C, class NC>
    using f = take<n, C>;
  };

  template<>
  struct _take_while<number<-1>>
  {
    template<class C, class NC>
    using f = NC;
  };
}
/// \endcond
