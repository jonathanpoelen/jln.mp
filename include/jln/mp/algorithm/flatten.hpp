#pragma once

#include <jln/mp/list/join.hpp>
#include <jln/mp/functional/lift.hpp>
#include <jln/mp/utility/unpack.hpp>
#include <jln/mp/utility/wrapper.hpp>

namespace jln::mp
{
  /// \cond
  namespace detail
  {
    template<template<class...> class, class>
    struct _flatten_once;

    template<template<class...> class, class>
    struct _flatten;
  }
  /// \endcond

  /// \ingroup algorithm

  /// Remove 1 dimension level from a sequence.
  /// \semantic
  ///   \code
  ///   call<flatten_once<>, list<a, b>, c, list<list<d, e>, f>
  ///   ==
  ///   list<a, b, c, list<d, e>, f>
  ///   \endcode
  /// \treturn \sequence
  /// \see flatten
  template<class S = lift<list>, class C = listify>
  struct flatten_once
  {};

  template<template<class...> class S, class C>
  struct flatten_once<lift<S, identity>, C>
  {
    template<class... xs>
    using f = typename detail::_join_select<sizeof...(xs)>
      ::template f<JLN_MP_TRACE_F(C)::template f, typename detail::_flatten_once<S, xs>::type...>
      ::type;
  };

  /// Recursive version of \c flatten_once.
  ///   \code
  ///   call<flatten<>, list<a, b>, c, list<list<d, e>, f>
  ///   ==
  ///   list<a, b, c, d, e, f>
  ///   \endcode
  /// \treturn \sequence
  /// \see flatten_once
  template<class S = lift<list>, class C = listify>
  struct flatten
  {};

  template<template<class...> class S, class C>
  struct flatten<lift<S, identity>, C>
  {
    template<class... xs>
    using f = typename detail::_join_select<sizeof...(xs)>
      ::template f<JLN_MP_TRACE_F(C)::template f, typename detail::_flatten<S, xs>::type...>
      ::type;
  };

  namespace emp
  {
    template<class L, class S = wrapper<L>, class C = mp::listify>
    using flatten_once = unpack<L, mp::flatten_once<S, C>>;

    template<class L, class S = wrapper<L>, class C = mp::listify>
    using flatten = unpack<L, mp::flatten<S, C>>;
  }

/// \cond
#if ! JLN_MP_ENABLE_DEBUG
  template<template<class...> class S, template<class...> class C>
  struct flatten_once<lift<S, identity>, lift<C>>
  {
    template<class... xs>
    using f = typename detail::_join_select<sizeof...(xs)>
      ::template f<C, typename detail::_flatten_once<S, xs>::type...>
      ::type;
  };

  template<template<class...> class S, template<class...> class C>
  struct flatten<lift<S, identity>, lift<C>>
  {
    template<class... xs>
    using f = typename detail::_join_select<sizeof...(xs)>
      ::template f<C, typename detail::_flatten<S, xs>::type...>
      ::type;
  };
#endif
/// \endcond
}

/// \cond
namespace jln::mp::detail
{
  template<template<class...> class, class T>
  struct _flatten_once
  {
    using type = list<T>;
  };

  template<template<class...> class S, class... xs>
  struct _flatten_once<S, S<xs...>>
  {
    using type = list<xs...>;
  };

  template<template<class...> class, class T>
  struct _flatten
  {
    using type = list<T>;
  };

  template<template<class...> class S, class... xs>
  struct _flatten<S, S<xs...>>
  : _join_select<sizeof...(xs)>
    ::template f<list, typename _flatten<S, xs>::type...>
  {};
}
/// \endcond
