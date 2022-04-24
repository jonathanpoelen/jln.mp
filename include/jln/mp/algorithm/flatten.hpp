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
    struct _flatten;

    template<class S>
    struct wrapper;
  }
  /// \endcond

  /// \ingroup algorithm

  /// Converts a tree or list of lists into one list containing the contents of all children.
  /// \treturn \sequence
  template<class S = lift<list>, class C = listify>
  struct flatten
  {};

  template<template<class...> class S, class C>
  struct flatten<lift<S, identity>, C>
  {
    template<class... seqs>
    using f = typename detail::_join_select<sizeof...(seqs)>
      ::template f<JLN_MP_TRACE_F(C)::template f, typename detail::_flatten<S, seqs>::type...>
      ::type;
  };

  namespace emp
  {
    template<class L, class S = wrapper<L>, class C = mp::listify>
    using flatten = unpack<L, mp::flatten<S, C>>;
  }

  /// \cond
  template<template<class...> class S, template<class...> class C>
  struct flatten<lift<S, identity>, lift<C>>
  {
    template<class... seqs>
    using f = typename detail::_join_select<sizeof...(seqs)>
      ::template f<C, typename detail::_flatten<S, seqs>::type...>
      ::type;
  };
  /// \endcond
}

/// \cond
namespace jln::mp::detail
{
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
