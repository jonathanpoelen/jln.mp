// SPDX-FileCopyrightText: 2023 Jonathan Poelen <jonathan.poelen@gmail.com>
// SPDX-License-Identifier: MIT
#pragma once

#include <jln/mp/list/join.hpp>
#include <jln/mp/functional/continuation.hpp>
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
  /// \semantics
  ///   \code
  ///   call<flatten_once<>, list<a, b>, c, list<list<d, e>, f>
  ///   ==
  ///   list<a, b, c, list<d, e>, f>
  ///   \endcode
  /// \treturn \sequence
  /// \see flatten
  template<class S = cfe<list>, class C = listify>
  struct flatten_once
  {};

  template<template<class...> class S, class C>
  struct flatten_once<cfe<S, identity>, C>
  {
    template<class... xs>
    using f = typename detail::_join_select<sizeof...(xs)>
      ::template f<JLN_MP_TRACE_F(C)::template f, typename detail::_flatten_once<S, xs>::type...>
      ::type;
  };

  template<template<class...> class S, class C = listify>
  using flatten_once_f = flatten_once<cfe<S>, C>;

  template<template<class...> class S, class C = identity>
  using flatten_once_for_f = flatten_once<cfe<S>, cfe<S, C>>;

  /// Recursive version of \c flatten_once.
  /// \semantics
  ///   \code
  ///   call<flatten<>, list<a, b>, c, list<list<d, e>, f>
  ///   ==
  ///   list<a, b, c, d, e, f>
  ///   \endcode
  /// \treturn \sequence
  /// \see flatten_once
  template<class S = cfe<list>, class C = listify>
  struct flatten
  {};

  template<template<class...> class S, class C>
  struct flatten<cfe<S, identity>, C>
  {
    template<class... xs>
    using f = typename detail::_join_select<sizeof...(xs)>
      ::template f<JLN_MP_TRACE_F(C)::template f, typename detail::_flatten<S, xs>::type...>
      ::type;
  };

  template<template<class...> class S, class C = listify>
  using flatten_f = flatten<cfe<S>, C>;

  template<template<class...> class S, class C = identity>
  using flatten_for_f = flatten<cfe<S>, cfe<S, C>>;

  namespace emp
  {
    template<class L, class S = wrapper<L>, class C = mp::listify>
    using flatten_once = typename detail::_unpack<mp::flatten_once<S, C>, L>::type;

    template<class L, class S = wrapper<L>, class C = mp::listify>
    using flatten = typename detail::_unpack<mp::flatten<S, C>, L>::type;

    template<class L, template<class...> class S, class C = mp::listify>
    using flatten_once_f = typename detail::_unpack<mp::flatten_once_f<S, C>, L>::type;

    template<class L, template<class...> class S, class C = mp::listify>
    using flatten_f = typename detail::_unpack<mp::flatten_f<S, C>, L>::type;

    template<class L, template<class...> class S, class C = mp::identity>
    using flatten_once_for_f = typename detail::_unpack<mp::flatten_once_for_f<S, C>, L>::type;

    template<class L, template<class...> class S, class C = mp::identity>
    using flatten_for_f = typename detail::_unpack<mp::flatten_for_f<S, C>, L>::type;
  }

/// \cond
#if ! JLN_MP_OPTIMIZED_ALIAS && ! JLN_MP_DEBUG
  template<template<class...> class S, template<class...> class C>
  struct flatten_once<cfe<S, identity>, cfe<C>>
  {
    template<class... xs>
    using f = typename detail::_join_select<sizeof...(xs)>
      ::template f<C, typename detail::_flatten_once<S, xs>::type...>
      ::type;
  };

  template<template<class...> class S, template<class...> class C>
  struct flatten<cfe<S, identity>, cfe<C>>
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
