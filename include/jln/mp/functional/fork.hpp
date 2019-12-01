#pragma once

#include "../algorithm/rotate.hpp"
#include "../number/number.hpp"
#include "bind.hpp"
#include "call.hpp"

namespace jln::mp
{
  namespace detail
  {
    template <class C, class... Fs>
    struct _fork;
  }

  // TODO DOXY template<class... F, class C>
  template <class... Fs>
  struct fork
  : rotate<number<sizeof...(Fs)-1>, cfe<detail::_fork>>
  ::template f<Fs...>
  {};

  template <class F, class C>
  struct fork<F, C>
  {
    template<class... xs>
    using f = unary_compose_call<C, F, xs...>;
  };

  template <class F0, class F1, class C>
  struct fork<F0, F1, C>
  {
    template<class... xs>
    using f = binary_compose_call<C, F0, F1, xs...>;
  };

  template <class F0, class F1, class F2, class C>
  struct fork<F0, F1, F2, C>
  {
    template<class... xs>
    using f = typename C::template f<
      call<F0, xs...>,
      call<F1, xs...>,
      call<F2, xs...>
    >;
  };

  // TODO emp
}

namespace jln::mp::detail
{
  template <class C, class... Fs>
  struct _fork
  {
    template <class... xs>
    using f = typename C::template f<call<Fs, xs...>...>;
  };
} // namespace jln::mp
