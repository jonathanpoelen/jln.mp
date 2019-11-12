#pragma once

#include "split.hpp"


namespace jln::mp
{
  namespace detail
  {
    template <class x, class state>
    struct split_after_push;
  }

  template<class Pred, class C = listify>
  struct split_after_if
  {
    template <class... xs>
    using f = typename conditional_c<!sizeof...(xs)>
      ::template f<
        always<list<>>,
        fold_right<
          if_<
            at0<Pred>,
            cfl<detail::split_after_push>,
            cfl<detail::push_front_sublist>>,
          push_front<unpack<C>, cfe<call>>
        >
      >::template f<list<list<>>, xs...>;
  };

  template<class x, class C = listify>
  using split_after = split_after_if<same_as<x>, C>;

  namespace emp
  {
    template<class L, class Pred, class C = mp::listify>
    using split_after_if = eager<L, mp::split_after_if<Pred, C>>;

    template<class L, class x, class C = mp::listify>
    using split_after = eager<L, mp::split_after<x, C>>;
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
