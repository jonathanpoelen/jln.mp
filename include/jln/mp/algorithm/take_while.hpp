#pragma once

#include "index.hpp"
#include "../list/take.hpp"
#include "../utility/always.hpp"
#include "../functional/function.hpp"
#include "../functional/fork.hpp"
#include "../functional/fork_front.hpp"

namespace jln::mp
{
  namespace detail
  {
    template<class>
    struct _take_while;
  }

  template<class Pred, class C = listify, class NC = C>
  using take_while = fork_front<index_if<
    Pred, fork<identity, always<C>, cfe<take>>, always<NC>>>;

  namespace emp
  {
    template<class L, class Pred, class C = mp::listify, class NC = C>
    using take_while = unpack<L, mp::take_while<Pred, C, NC>>;
  }
}

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
