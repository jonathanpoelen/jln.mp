#pragma once

#include "fold_right.hpp"
#include "../functional/bind.hpp"
#include "../functional/call.hpp"
#include "../utility/unpack.hpp"
#include "../utility/conditional.hpp"
#include "../list/push_front.hpp"
#include "../list/size.hpp"
#include "../list/at.hpp"

namespace jln::mp
{
  namespace detail
  {
    template <class x, class state>
    struct push_front_sublist;

    template<class F>
    using split_if_pred = if_<
      at0<F>,
      at1<unpack<push_front<list<>>>>,
      cfl<push_front_sublist>>;
  }

  template<class F = identity, class C = listify>
  struct split_if
  {
    template <class... xs>
    using f = typename conditional_c<!sizeof...(xs)>
      ::template f<
        always<list<>>,
        fold_right<
          detail::split_if_pred<F>,
          push_front<unpack<C>, cfe<call>>
        >
      >::template f<list<list<>>, xs...>;
  };

  namespace emp
  {
    template<class L, class F = mp::identity, class C = mp::listify>
    using split_if = eager<L, mp::split_if<F, C>>;
  }
}

namespace jln::mp::detail
{
  template<class x, class... Ls, class... xs>
  struct push_front_sublist<x, list<list<xs...>, Ls...>>
  {
    using type = list<list<x, xs...>, Ls...>;
  };
}
