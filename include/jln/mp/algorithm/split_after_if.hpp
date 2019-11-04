#pragma once

#include "split_if.hpp"

namespace jln::mp
{
  namespace detail
  {
    template <class x, class state>
    struct split_after_push;

    template<class F>
    using split_after_if_pred = if_<
      at0<F>,
      cfl<split_after_push>,
      cfl<push_front_sublist>>;
  }

  template<class Pred, class C = listify>
  struct split_after_if
  {
    template <class... xs>
    using f = typename conditional_c<!sizeof...(xs)>
      ::template f<
        always<list<>>,
        fold_right<
          detail::split_after_if_pred<Pred>,
          push_front<unpack<C>, cfe<call>>
        >
      >::template f<list<list<>>, xs...>;
  };

  namespace emp
  {
    template<class L, class Pred, class C = mp::listify>
    using split_after_if = eager<L, mp::split_after_if<Pred, C>>;
  }
}

namespace jln::mp::detail
{
  template<class x, class... Ls, class... xs>
  struct split_after_push<x, list<list<xs...>, Ls...>>
  {
    using type = list<list<x>, list<xs...>, Ls...>;
  };
}
