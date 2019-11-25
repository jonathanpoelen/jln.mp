#pragma once

#include "same.hpp"
#include "rotate.hpp"
#include "../functional/try_invoke.hpp"


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
#include "../utility/conditional.hpp"
#include "../functional/fork_front.hpp"
#include "../functional/bind.hpp"

namespace jln::mp::detail
{
  // TODO bind_front<unpack<push_front<x>>, C>
  template<class x, class C>
  struct _group_insert_x
  {
    template<class seq, class... seqs>
    using f = call<C, eager<seq, push_front<x>>, seqs...>;
  };

  template<class...>
  struct _group_impl;

  template<class C, class Cmp, class x, class... xs, class... ys>
  struct _group_impl<C, Cmp, x, list<ys...>, xs...>
  {
    using type = call<
      fold_right<cfl<split_state>, unpack<_group_insert_x<x, C>>>,
      list<list<>>,
      list<number<Cmp::template f<ys, xs>::value
        ? split_keep : split_before>, xs>...
    >;
  };

  template<class... bools>
  struct _smp_group_impl
  {
    template<class C, class x, class... xs>
    using f = call<
      fold_right<cfl<split_state>, unpack<_group_insert_x<x, C>>>,
      list<list<>>,
      list<number<bools::value ? split_keep : split_before>, xs>...
    >;
  };

  template<class C, class Cmp, class TC, class FC, class x, class... xs, class... ys>
  struct _group_impl<C, try_invoke<Cmp, TC, FC>, x, list<ys...>, xs...>
  {
    template<class... bool_or_na>
    using impl = typename conditional_c<(
      ... || std::is_same<bool_or_na, na>::value
    )>::template f<always<violation>, cfe<_smp_group_impl>>
      ::template f<bool_or_na...>;

    using type = typename impl<
      typename try_invoke<Cmp, TC, FC>::template f<ys, xs>...
    >::template f<C, x, xs...>;
  };

  template<>
  struct _group<true>
  {
    template<class C, class Cmp, class x, class... xs>
    using f = typename _group_impl<
      C, Cmp, x,
      call<take_c<sizeof...(xs)>, x, xs...>,
      xs...
    >::type;
  };

  template<>
  struct _group<false>
  {
    template<class C, class>
    using f = typename C::template f<>;
  };
}
