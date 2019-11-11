#pragma once

#include "../list/list.hpp"
#include "../list/join.hpp"
#include "../functional/call.hpp"
#include "transform.hpp"
#include "make_int_sequence.hpp"
#include "../utility/always.hpp"

namespace jln::mp
{
  namespace detail
  {
    template<int_ n>
    struct _repeat;
  }

  template<class N, class C = listify>
  struct repeat
  {
    template<class... xs>
    using f = emp::make_int_sequence<N,
      // TODO sizeof...(xs) > 2 ? 2 : sizeof...(xs) ; better ?
      typename detail::_repeat<sizeof...(xs)>
        ::template f<C, xs...>>;
  };
}

namespace jln::mp::detail
{
  template<int_ n>
  struct _repeat
  {
    template<class C, class... xs>
    using f = transform<always<list<xs...>>, join<C>>;
  };

  template<>
  struct _repeat<0>
  {
    template<class C>
    using f = typename C::template f<>;
  };

  template<>
  struct _repeat<1>
  {
    template<class C, class x>
    using f = transform<always<x>, C>;
  };
}
