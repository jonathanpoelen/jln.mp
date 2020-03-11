#pragma once

#include "../algorithm/rotate.hpp"
#include "../number/number.hpp"
#include "function.hpp"
#include "call.hpp"

namespace jln::mp
{
  namespace detail
  {
    template <class, class, class...>
    struct _partial_eager;
  }

  template <class... Fs>
  struct partial_eager
  : rotate<number<-2>, cfe<detail::_partial_eager>>
  ::template f<Fs...>::type
  {};

  template <class C>
  struct partial_eager<C>
  {
    template <class... xs>
    using f = call<C, xs...>;
  };

  template <class F, class C>
  struct partial_eager<F, C>
  {
    template <class... xs>
    using f = unary_compose_call<C, F, xs...>;
  };

  template <class F0, class F1, class C>
  struct partial_eager<F0, F1, C>
  {
    template <class x0, class... xs>
    using f = typename detail::dcall<(sizeof...(xs) < 1000000)>
      ::template f<C, call<F0, x0>, call<F1, xs...>>;
  };

  template <class F0, class F1, class F2, class C>
  struct partial_eager<F0, F1, F2, C>
  {
    template <class x0, class x1, class... xs>
    using f = typename detail::dcall<(sizeof...(xs) < 1000000)>
      ::template f<C, call<F0, x0>, call<F1, x1>, call<F2, xs...>>;
  };
}

#include "each.hpp"
#include "fork.hpp"
#include "../list/join.hpp"
#include "../list/take.hpp"
#include "../list/drop.hpp"

namespace jln::mp::detail
{
  template <class Flast, class C, class... Fs>
  struct _partial_eager
  {
    using type = fork<
      take_c<sizeof...(Fs), _each<listify, Fs...>>, 
      drop_c<sizeof...(Fs), fork<Flast, listify>>,
      join<C>
    >;
  };
} // namespace jln::mp
