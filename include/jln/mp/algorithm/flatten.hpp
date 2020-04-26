#pragma once

#include "../list/join.hpp"
#include "../functional/call.hpp"
#include "../functional/function.hpp"
#include "../utility/unpack.hpp"

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

  /// converts a tree or list of lists into one list containing the contents of all children.
  /// \treturn \sequence
  template<class S = cfe<list>, class C = listify>
  struct flatten;

  template<template<class...> class S, class C>
  struct flatten<cfe<S, identity>, C>
  {
    template<class... seqs>
    using f = typename detail::_join_select<sizeof...(seqs)>
      ::template f<C, typename detail::_flatten<S, seqs>::type...>
      ::type;
  };

  template<class S>
  using wrapper = typename detail::wrapper<S>::type;

  namespace emp
  {
    template<class L, class S = wrapper<L>, class C = mp::listify>
    using flatten = unpack<L, mp::flatten<S, C>>;
  }
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
    ::template f<listify, typename _flatten<S, xs>::type...>
  {};

  template<template<class...> class S, class... xs>
  struct wrapper<S<xs...>>
  {
    using type = cfe<S>;
  };
}
/// \endcond
