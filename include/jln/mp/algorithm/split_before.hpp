#pragma once

#include "split.hpp"

namespace jln::mp
{
  namespace detail
  {
    template <class x, class state>
    struct split_before_push;
  }

  template<class Pred, class C = listify>
  struct split_before_if
  {
    template <class... xs>
    using f = typename conditional_c<!sizeof...(xs)>
      ::template f<
        always<list<>>,
        fold_right<
          if_<
            at0<Pred>,
            cfl<detail::split_before_push>,
            cfl<detail::push_front_sublist>>,
          push_front<unpack<C>, cfe<call>>
        >
      >::template f<list<list<>>, xs...>;
  };

  template<class x, class C = listify>
  using split_before = split_before_if<same_as<x>, C>;

  namespace emp
  {
    template<class L, class Pred, class C = mp::listify>
    using split_before_if = eager<L, mp::split_before_if<Pred, C>>;

    template<class L, class x, class C = mp::listify>
    using split_before = eager<L, mp::split_before<x, C>>;
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
