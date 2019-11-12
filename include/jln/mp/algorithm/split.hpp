#pragma once

#include "fold_right.hpp"
#include "../functional/if.hpp"
#include "../functional/bind.hpp"
#include "../functional/call.hpp"
#include "../utility/same_as.hpp"
#include "../utility/unpack.hpp"
#include "../utility/conditional.hpp"
#include "../list/push_front.hpp"
#include "../list/join.hpp"
#include "../list/size.hpp"
#include "../list/at.hpp"


namespace jln::mp
{
  namespace detail
  {
    template <class x, class state>
    struct push_front_sublist;
  }

  template<class Pred = identity, class C = listify>
  struct split_if
  {
    template <class... xs>
    // TODO zip_with<list<Pred<xs>...>, conditional_value>::f<xs...>;
    // conditional_value<x, bool>
    // if_<identity, ...>
    // split_if<> = split_???<bool_list, value_list>
    // same of split_before and after
    using f = typename conditional_c<!sizeof...(xs)>
      ::template f<
        always<list<>>,
        fold_right<
          if_<
            at0<Pred>,
            at1<unpack<push_front<list<>>>>,
            cfl<detail::push_front_sublist>>,
          push_front<unpack<C>, cfe<call>>
        >
      >::template f<list<list<>>, xs...>;
  };

  template<class x, class C = listify>
  using split = split_if<same_as<x>, C>;

  namespace emp
  {
    template<class L, class Pred = mp::identity, class C = mp::listify>
    using split_if = eager<L, mp::split_if<Pred, C>>;

    template<class L, class x, class C = mp::listify>
    using split = eager<L, mp::split<x, C>>;
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
