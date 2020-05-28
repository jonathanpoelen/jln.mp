#pragma once

#include "../functional/identity.hpp"
#include "../utility/unpack.hpp"


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
  }
  /// \endcond

  template<class>
  struct stop_iteration
  {};

  /// \ingroup functional

  /// Recursively calls `F` until `stop_iteration`.
  /// The first call uses \c F::f<xs...>, the following calls \c F::f<result>
  /// \treturn \value
  /// \see fix, recurse_fix
  template<class F, class C = identity>
  struct recurse
  {
    template<class... xs>
    using f = typename detail::_recurse<F, call<F, xs...>>
      ::template f<C>;
  };

  /// Recursively calls `F` until `stop_iteration`.
  /// The first call uses `F::f<F, xs...>, the following calls `F::f<F, result>`
  /// \treturn \value
  /// \see fix, recurse
  template<class F, class C = identity>
  struct recurse_fix
  {
    template<class... xs>
    using f = typename detail::_recurse_fix<
      F, typename detail::_recurse_fix_next<F>::template f<xs...>
    >::template f<C>;
  };

  namespace emp
  {
    template<class L, class F, class C = mp::identity>
    using recurse = unpack<L, mp::recurse<F, C>>;

    template<class L, class F, class C = mp::identity>
    using recurse_fix = unpack<L, mp::recurse_fix<F, C>>;
  }
}


#include "../functional/call.hpp"

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
    struct f0
    {
      template<class... xs>
      using f = call<F, _recurse_capture, xs...>;
    };

    struct f1
    {
      template<class... xs>
      using f = call<F, f0, xs...>;
    };

    struct f2
    {
      template<class... xs>
      using f = call<F, f1, xs...>;
    };

    struct f3
    {
      template<class... xs>
      using f = call<F, f2, xs...>;
    };

    struct f4
    {
      template<class... xs>
      using f = call<F, f3, xs...>;
    };

    struct f5
    {
      template<class... xs>
      using f = call<F, f4, xs...>;
    };

    struct f6
    {
      template<class... xs>
      using f = call<F, f5, xs...>;
    };

    struct f7
    {
      template<class... xs>
      using f = call<F, f6, xs...>;
    };

    struct f8
    {
      template<class... xs>
      using f = call<F, f7, xs...>;
    };

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
}
/// \endcond
