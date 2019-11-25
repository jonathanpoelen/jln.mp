#pragma once

#include "fold_right.hpp"
#include "../functional/bind.hpp"
#include "../functional/call.hpp"
#include "../utility/same_as.hpp"
#include "../utility/unpack.hpp"


namespace jln::mp
{
  namespace detail
  {
    template <bool>
    struct _split;

    // TODO enum ?
    inline constexpr int_ split_keep = 0;
    inline constexpr int_ split_after = 1;
    inline constexpr int_ split_before = 2;
    inline constexpr int_ split_skip = 3;
    // TODO
    inline constexpr int_ split_na = 4;
  }

  template<class Pred = identity, class C = listify>
  struct split_if
  {
    template <class... xs>
    using f = typename detail::_split<sizeof...(xs) != 0>
      ::template f<detail::split_skip, C, Pred, xs...>;
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
  template <class x, class state>
  struct split_state;

  template<class x, class... Ls, class... xs>
  struct split_state<list<number<split_keep>, x>, list<list<xs...>, Ls...>>
  {
    using type = list<list<x, xs...>, Ls...>;
  };

  template<class x, class... Ls, class... xs>
  struct split_state<list<number<split_after>, x>, list<list<xs...>, Ls...>>
  {
    using type = list<list<x>, list<xs...>, Ls...>;
  };

  template<class x, class... Ls, class... xs>
  struct split_state<list<number<split_before>, x>, list<list<xs...>, Ls...>>
  {
    using type = list<list<>, list<x, xs...>, Ls...>;
  };

  template<class x, class... Ls, class... xs>
  struct split_state<list<number<split_skip>, x>, list<list<xs...>, Ls...>>
  {
    using type = list<list<>, list<xs...>, Ls...>;
  };

  template<>
  struct _split<true>
  {
    template<int_ policy, class C, class Pred, class... xs>
    using f = call<
      // TODO unpack<listify> -> identity
      fold_right<cfl<split_state>, unpack<C>>,
      list<list<>>,
      list<number<Pred::template f<xs>::value
        ? policy : split_keep>, xs>...
    >;
  };

  template<>
  struct _split<false>
  {
    template<int_, class C, class>
    using f = typename C::template f<>;
  };
}
