#pragma once

#include "split_if.hpp"

namespace jln::mp
{
  namespace detail
  {
    template <class x, class state>
    struct split_before_push;

    template<class F>
    using split_before_if_pred = if_<
      at0<F>,
      cfl<split_before_push>,
      cfl<push_front_sublist>>;
  }

  template<class Pred, class C = listify>
  struct split_before_if
  {
    template <class... xs>
    using f = typename conditional_c<!sizeof...(xs)>
      ::template f<
        always<list<>>,
        fold_right<
          detail::split_before_if_pred<Pred>,
          push_front<unpack<C>, cfe<call>>
        >
      >::template f<list<list<>>, xs...>;
  };

  namespace emp
  {
    template<class L, class Pred, class C = mp::listify>
    using split_before_if = eager<L, mp::split_before_if<Pred, C>>;
  }
}

namespace jln::mp::detail
{
  template<class x, class... Ls, class... xs>
  struct split_before_push<x, list<list<xs...>, Ls...>>
  {
    using type = list<list<>, list<x, xs...>, Ls...>;
  };
}
