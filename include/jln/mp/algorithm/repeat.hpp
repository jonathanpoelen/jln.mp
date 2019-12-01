#pragma once

#include "make_int_sequence.hpp"

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

  template<int_ n, class C = listify>
  using repeat_c = repeat<number<n>, C>;

  namespace emp
  {
    template<class L, class n, class C = mp::listify>
    using repeat = eager<L, mp::repeat<n, C>>;

    template<class L, int_ n, class C = mp::listify>
    using repeat_c = eager<L, mp::repeat<number<n>, C>>;
  }
}


#include "transform.hpp"
#include "../list/join.hpp"
#include "../functional/call.hpp"
#include "../utility/always.hpp"

namespace jln::mp::detail
{
  template<int_ n>
  struct _repeat
  {
    template<class C, class... xs>
    // TODO join<C>::template f<list<conditional_c<true>::f<list<xs...>, x>...> ?
    using f = transform<always<list<xs...>>, join<C>>;
  };

  template<>
  struct _repeat<0>
  {
    template<class C>
    using f = always<C, cfe<call>>;
  };

  template<>
  struct _repeat<1>
  {
    template<class C, class x>
    using f = transform<always<x>, C>;
  };
}
