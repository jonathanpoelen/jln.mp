#pragma once

#include "../algorithm/rotate.hpp"
#include "../number/number.hpp"
#include "function.hpp"
#include "call.hpp"

namespace jln::mp
{
  /// \cond
  namespace detail
  {
    template <class, class, class...>
    struct _partial_eager;
  }
  /// \endcond

  /// \ingroup functional

  /// Invoke multiple functions each taking the parameter corresponding to its position
  /// (the last function takes the remaining parameters or 0)
  /// then calls `C` with the results
  /// \pre sizeof...(Fs) >= 1
  /// \pre sizeof...(xs) + 1 >= sizeof...(Fs) - 1
  /// \semantics
  ///   \code
  ///   partial_eager\<F,G,C\>::f\<a,b,c,d\> == C\<F\<a\>, G\<b, c, d\>\>
  ///   partial_eager\<F,G,C\>::f\<a\> == C\<F\<a\>, G\<\>\>
  ///   \endcode
  /// \return \value
  /// \see each
  /// \see fork
  /// \see partial
  template <class... Fs>
  struct partial_eager
  : rotate<number<-2>, cfe<detail::_partial_eager>>
  ::template f<Fs...>::type
  {};

  /// \cond
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
    using f = JLN_MP_DCALL(sizeof...(xs) < 100000,
      C, call<F0, x0>, call<F1, xs...>);
  };

  template <class F0, class F1, class F2, class C>
  struct partial_eager<F0, F1, F2, C>
  {
    template <class x0, class x1, class... xs>
    using f = JLN_MP_DCALL(sizeof...(xs) < 100000,
      C, call<F0, x0>, call<F1, x1>, call<F2, xs...>);
  };
  /// \endcond
}

#include "each.hpp"
#include "fork.hpp"
#include "../list/join.hpp"
#include "../list/take.hpp"
#include "../list/drop.hpp"

/// \cond
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
/// \endcond
