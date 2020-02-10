#pragma once

#include "unique.hpp"

namespace jln::mp
{
  namespace detail
  {
    template<class Cmp, class C>
    struct mk_is_unique;
  }

  template<class C = identity>
  using is_unique = typename detail::mk_is_unique<cfe<std::is_same>, C>::type;

  template<class Cmp = cfe<std::is_same>, class C = identity>
  using is_unique_if = typename detail::mk_is_unique<Cmp, C>::type;

  namespace emp
  {
    template<class L, class C = mp::identity>
    using is_unique = eager<L, is_unique<C>>;

    template<class L, class Cmp = cfe<std::is_same>, class C = mp::identity>
    using is_unique_if = eager<L, is_unique_if<Cmp, C>>;
  }
}


#include "../functional/fork.hpp"
#include "../number/to_bool.hpp"

namespace jln::mp::detail
{
  template<class C>
  struct _is_unique
  {
    template<class... xs>
    using f = typename dcall<(sizeof...(xs) < 100000)>::template f<
      C, mp::number<sizeof(inherit<std::make_index_sequence<sizeof...(xs)>, xs...>) == 1>>;
  };

  template<class Cmp, class C>
  struct _is_unique2
  {
    template<class... xs>
    using f = typename dcall<(sizeof...(xs) < 100000)>::template f<C, mp::number<std::is_same<
      typename unique_if<Cmp, C>::template f<xs...>,
      list<xs...>
    >::value>>;
  };

  template<class Cmp, class C>
  struct mk_is_unique
  {
    using type = fork<unique_if<Cmp>, listify, cfl<std::is_same, to_bool<C>>>;
  };

  template<class C>
  struct mk_is_unique<cfe<std::is_same>, C>
  {
    using type = _is_unique<C>;
  };

  template<class C>
  struct mk_is_unique<cfl<std::is_same>, C>
  : mk_is_unique<cfe<std::is_same>, C>
  {};

  template<class C>
  struct mk_is_unique<same<>, C>
  : mk_is_unique<cfe<std::is_same>, C>
  {};
}
