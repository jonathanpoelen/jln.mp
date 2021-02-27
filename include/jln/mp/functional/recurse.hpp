#pragma once

#include <jln/mp/functional/identity.hpp>
#include <jln/mp/utility/unpack.hpp>


namespace jln::mp
{
  /// \cond
  namespace detail
  {
    template<class, class>
    struct _recurse;

    template<class, class>
    struct _recurse_fix;

    template<class F>
    struct _recurse_fix_next;

    template<class, class>
    struct _infinite_recurse_next;

    template<class, class>
    struct _infinite_recurse;

    template<class F, class x, class y>
    struct _infinite_recurse_fix;
  }
  /// \endcond

  template<class>
  struct stop_iteration
  {};

  /// \ingroup functional

  /// Recursively invokes \c F until \c stop_iteration.
  /// The first invocation uses \c F::f<xs...>, the following invocations \c F::f<result>
  /// \treturn \value
  /// \see fix, recurse_fix, infinite_recurse
  template<class F, class C = identity>
  struct recurse
  {
    template<class... xs>
    using f = typename detail::_recurse<F, call<F, xs...>>
      ::template f<C>;
  };

  /// Version of \c fix that stops if there is \c stop_iteration
  /// The first invocation uses `F::f<F, xs...>`, the following
  /// invocations `F::f<F, result>`
  /// \treturn \value
  /// \see fix, recurse, infinite_recurse
  template<class F, class C = identity>
  struct recurse_fix
  {
    template<class... xs>
    using f = typename detail::_recurse_fix<
      F, typename detail::_recurse_fix_next<F>::template f<xs...>
    >::template f<C>;
  };

  /// Recursively invokes \c F until the result no longer changes
  /// \semantics
  ///   \code
  ///   call<infinite_recurse<lift_t<std::remove_pointer>>, int****> == int
  ///   \endcode
  /// \treturn \value
  /// \see fix, recurse, infinite_recurse_fix
  template<class F, class C = identity>
  struct infinite_recurse
  {
    template<class x>
    using f = typename detail::_infinite_recurse<F,
      typename detail::_infinite_recurse_next<call<F, x>, x>
      ::template f<F>
      ::template f<F>
      ::template f<F>
      ::template f<F>
      ::template f<F>
      ::template f<F>
      ::template f<F>
      ::template f<F>
    >::template f<C>;
  };

  /// Mix of \c fix and \c infinite_recurse.
  /// \treturn \value
  /// \see fix, recurse, infinite_recurse
  template<class F, class C = identity>
  struct infinite_recurse_fix
  {
    template<class... xs>
    using f = typename detail::_infinite_recurse_fix<
      F, list<xs...>, typename detail::_recurse_fix_next<F>::template f<xs...>
    >::template f<C>;
  };

  namespace emp
  {
    template<class L, class F, class C = mp::identity>
    using recurse = unpack<L, mp::recurse<F, C>>;

    template<class L, class F, class C = mp::identity>
    using recurse_fix = unpack<L, mp::recurse_fix<F, C>>;

    template<class L, class F, class C = mp::identity>
    using infinite_recurse = unpack<L, mp::infinite_recurse<F, C>>;

    template<class L, class F, class C = mp::identity>
    using infinite_recurse_fix = unpack<L, mp::infinite_recurse_fix<F, C>>;
  }
}


#include <jln/mp/functional/call.hpp>

/// \cond
namespace jln::mp::detail
{
  template<class F, class x>
  struct _recurse<F, stop_iteration<x>>
  {
    template<class C>
    using f = typename C::template f<x>;
  };

  template<class x>
  struct _recurse_next
  {
    template<class F>
    using f = typename F::template f<x>;
  };

  template<class x>
  struct _recurse_next<stop_iteration<x>>
  {
    template<class F>
    using f = stop_iteration<x>;
  };

  template<class F, class x>
  struct _recurse
  : _recurse<F,
    typename _recurse_next<
      typename _recurse_next<
        typename _recurse_next<
          typename _recurse_next<
            typename _recurse_next<
              typename _recurse_next<
                typename _recurse_next<
                  typename _recurse_next<
                    typename _recurse_next<
                      typename F::template f<x>
                    >::template f<F>
                  >::template f<F>
                >::template f<F>
              >::template f<F>
            >::template f<F>
          >::template f<F>
        >::template f<F>
      >::template f<F>
    >::template f<F>
  >
  {};


  struct _recurse_capture
  {
    template<class... xs>
    struct f;
  };

  template<class F>
  struct _recurse_fix_next
  {
    struct f0 { template<class... xs> using f = call<F, _recurse_capture, xs...>; };
    struct f1 { template<class... xs> using f = call<F, f0, xs...>; };
    struct f2 { template<class... xs> using f = call<F, f1, xs...>; };
    struct f3 { template<class... xs> using f = call<F, f2, xs...>; };
    struct f4 { template<class... xs> using f = call<F, f3, xs...>; };
    struct f5 { template<class... xs> using f = call<F, f4, xs...>; };
    struct f6 { template<class... xs> using f = call<F, f5, xs...>; };
    struct f7 { template<class... xs> using f = call<F, f6, xs...>; };
    struct f8 { template<class... xs> using f = call<F, f7, xs...>; };

    template<class... xs>
    using f = call<F, f8, xs...>;
  };

  template<class F, class... xs>
  struct _recurse_fix<F, _recurse_capture::f<xs...>>
  : _recurse_fix<F, typename _recurse_fix_next<F>::template f<xs...>>
  {};

  template<class F, class x>
  struct _recurse_fix<F, stop_iteration<x>>
  {
    template<class C>
    using f = typename C::template f<x>;
  };

  template<class, class x>
  struct _recurse_fix
  {
    template<class C>
    using f = typename C::template f<x>;
  };


  template<class x, class old>
  struct _infinite_recurse_next
  {
    template<class F>
    using f = _infinite_recurse_next<typename F::template f<x>, x>;
  };

  template<class F, class x>
  struct _infinite_recurse<F, _infinite_recurse_next<x, x>>
  {
    template<class C>
    using f = typename C::template f<x>;
  };

  template<class F, class x, class old>
  struct _infinite_recurse<F, _infinite_recurse_next<x, old>>
  : _infinite_recurse<F,
    typename _infinite_recurse_next<typename F::template f<x>, x>
    ::template f<F>
    ::template f<F>
    ::template f<F>
    ::template f<F>
    ::template f<F>
    ::template f<F>
    ::template f<F>
    ::template f<F>
  >
  {};

  template<class F, class x, class y>
  struct _infinite_recurse_fix
  {
      template<class C>
      using f = typename C::template f<y>;
  };

  template<class F, class... xs>
  struct _infinite_recurse_fix<F, list<xs...>, _recurse_capture::f<xs...>>
  {
      template<class C>
      using f = typename C::template f<xs...>;
  };

  template<class F, class... xs, class... ys>
  struct _infinite_recurse_fix<F, list<xs...>, _recurse_capture::f<ys...>>
  : _infinite_recurse_fix<F, list<ys...>,
      typename _recurse_fix_next<F>::template f<ys...>>
  {};
}
/// \endcond
