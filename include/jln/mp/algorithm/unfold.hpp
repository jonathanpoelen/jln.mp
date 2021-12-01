#pragma once

#include <jln/mp/functional/recursively.hpp>
#include <jln/mp/functional/if.hpp>
#include <jln/mp/list/size.hpp>
#include <jln/mp/list/push_front.hpp>
#include <jln/mp/list/pop_front.hpp>

namespace jln::mp
{
  /// \cond
  namespace detail
  {
    template<class F>
    struct unfold_impl;
  }
  /// \endcond

  /// \ingroup algorithm

  template<class value, class next = value>
  using Some = mp::list<value, next>;

  using None = mp::stop_recursion;

  /// Unfold \c F until returning \c None.
  /// When \c F returns `Some<value,next>`, \c value is added to the
  /// results list and \c next is used for the next iteration.
  /// \semantics
  ///   Equivalent to
  ///   \code
  ///   unfold<
  ///     if_<
  ///       less_than_c<5>,
  ///       inc<lift<Some>>,
  ///       None
  ///     >
  ///   >::f<
  ///     number<0>
  ///   >
  ///   == list<number<1>, number<2>, number<3>, number<4>, number<5>>
  ///   \endcode
  /// \treturn \list
  /// \see fold_left, fold_right, recursively
  template<class F, class C = listify>
  using unfold = mp::recursively<detail::unfold_impl<F>, mp::pop_front<C>>;

  namespace emp
  {
    template<class state, class F, class C = mp::listify>
    using unfold = JLN_MP_CALL_TRACE((mp::unfold<F, C>), state);
  }
}

/// \cond
namespace jln::mp::detail
{
  template<class>
  struct unfold_next
  {};

  template<>
  struct unfold_next<None>
  {
    template<class... xs>
    using f = stop_recursion;
  };

  template<class x, class next>
  struct unfold_next<list<x, next>>
  {
    template<class... xs>
    using f = _next_recursion<next, xs..., x>;
  };

  template<class F>
  struct unfold_impl
  {
    template<class state, class... xs>
    using f = typename unfold_next<JLN_MP_CALL_TRACE((F), state)>::template f<xs...>;
  };
}
/// \endcond
