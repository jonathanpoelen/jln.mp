#pragma once

#include "../functional/identity.hpp"
#include "../functional/call.hpp"
#include "../number/operators.hpp"
#include "../config/enumerate.hpp"

namespace jln::mp
{
  namespace detail
  {
    template<unsigned>
    struct _is_sorted;
  }

  template<class Cmp = less<>, class C = identity>
  struct is_sorted
  {
    template<class... xs>
    using f = typename detail::dcall<(sizeof...(xs) < 1000000)>
      ::template f<C, typename detail::_is_sorted<detail::min(sizeof...(xs), 3)>
        ::template f<Cmp, xs...>>;
  };

  template<class Cmp>
  struct is_sorted<Cmp, identity>
  {
    template<class... xs>
    using f = typename detail::_is_sorted<detail::min(sizeof...(xs), 3)>
      ::template f<Cmp, xs...>;
  };

  namespace emp
  {
    template<class L, class Cmp = mp::less<>, class C = mp::identity>
    using is_sorted = eager<L, mp::is_sorted<Cmp, C>>;
  }
}


#include "../number/operators.hpp"
#include "../list/pop_front.hpp"
#include "../list/push_front.hpp"
#include "zip.hpp"
#include "rotate.hpp"

namespace jln::mp::detail
{
  template<>
  struct _is_sorted<0>
  {
    template<class Cmp>
    using f = number<1>;
  };

  template<>
  struct _is_sorted<1>
  {
    template<class Cmp, class x>
    using f = number<1>;
  };

  template<>
  struct _is_sorted<2>
  {
    template<class Cmp, class x, class y>
    using f = number<!Cmp::template f<y, x>::value>;
  };

  template<>
  struct _is_sorted<3>
  {
    template<class Cmp, class x, class y, class... xs>
    using f = typename zip_with<Cmp, or_<not_<>>>::template f<
      list<y, xs...>,
      rotate_c<-1, pop_front<>>::f<x, y, xs...>
    >;
  };
}
