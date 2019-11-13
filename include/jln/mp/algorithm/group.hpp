#pragma once

#include "same.hpp"
#include "rotate.hpp"


namespace jln::mp
{
  namespace detail
  {
    template<bool>
    struct _group;
  }

  template<class Cmp, class C = listify>
  struct group_if
  {
    template<class... xs>
    using f = typename detail::_group<sizeof...(xs) != 0>
      ::template f<C, Cmp, xs...>;
  };

  template<class C = listify>
  using group = group_if<same<>, C>;

  namespace emp
  {
    template<class L, class Cmp, class C = mp::listify>
    using group_if = eager<L, mp::group_if<Cmp, C>>;

    template<class L, class C = mp::listify>
    using group = eager<L, mp::group<C>>;
  }
}


#include "split.hpp"
#include "../list/take.hpp"
#include "../functional/fork_front.hpp"

namespace jln::mp::detail
{
  // TODO bind_front<unpack<push_front<x>>, C>
  template<class C, class x>
  struct _group_impl_x
  {
    template<class seq, class... seqs>
    using f = call<C, eager<seq, push_front<x>>, seqs...>;
  };

  template<class C, class Cmp, class x, class, class>
  struct _group_impl;

  template<class C, class Cmp, class x, class... xs, class... ys>
  struct _group_impl<C, Cmp, x, list<xs...>, list<ys...>>
  {
    using type = call<
      fold_right<cfl<split_state>, unpack<_group_impl_x<C, x>>>,
      list<list<>>,
      list<number<Cmp::template f<ys, xs>::value
        ? split_keep : split_before>, xs>...
    >;
  };

  template<>
  struct _group<true>
  {
    template<class C, class Cmp, class x, class... xs>
    using f = typename _group_impl<
      C, Cmp, x,
      list<xs...>,
      call<take_c<sizeof...(xs)>, x, xs...>
    >::type;
  };

  template<>
  struct _group<false>
  {
    template<class C, class>
    using f = typename C::template f<>;
  };
}
