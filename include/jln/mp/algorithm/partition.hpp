#pragma once

#include <jln/mp/algorithm/transform.hpp>
#include <jln/mp/utility/unpack.hpp>

namespace jln::mp
{
  /// \cond
  namespace detail
  {
    template<bool... bs>
    struct partition_impl;

    template<class... xs>
    using partition_caller = partition_impl<xs::value...>;
  }
  /// \endcond

  /// \ingroup group

  /// Splits a \list in two according to a predicate.
  /// The first value contains all elements for which the predicate returns true,
  /// the second value contains all elements for which predicate returns false
  /// \treturn \sequence of two \values
  template<class Pred, class F = listify, class C = listify>
  struct partition_with
  {
    template<class... xs>
    using f = typename transform<Pred, lift<detail::partition_caller>>
      ::template f<xs...>
      ::template f<JLN_MP_TRACE_F(C)::template f, F, xs...>;
  };

  /// Splits a \list in two according to a predicate.
  /// The first value contains all elements for which the predicate returns true,
  /// the second value contains all elements for which predicate returns false
  /// \treturn \sequence of two \lists
  /// \see partition_with
  template<class Pred, class C = listify>
  using partition = partition_with<Pred, listify, C>;

  namespace emp
  {
    template<class L, class Pred, class F = mp::listify, class C = mp::listify>
    using partition_with = unpack<L, mp::partition_with<Pred, F, C>>;

    template<class L, class Pred, class C = mp::listify>
    using partition = unpack<L, mp::partition<Pred, C>>;
  }

/// \cond
#if ! JLN_MP_ENABLE_DEBUG
  template<class Pred, class F, template<class...> class C>
  struct partition_with<Pred, F, lift<C>>
  {
    template<class... xs>
    using f = typename transform<Pred, lift<detail::partition_caller>>
      ::template f<xs...>
      ::template f<C, F, xs...>;
  };
#endif
/// \endcond
}


#include <jln/mp/list/wrap_in_list.hpp>
#include <jln/mp/list/join.hpp>

/// \cond
namespace jln::mp::detail
{
  template<bool... bs>
  struct partition_impl
  {
    template<template<class...> class C, class F, class... xs>
    using f = C<
      typename mp::join<F>::template f<typename mp::wrap_in_list_c<bs>::template f<xs>...>,
      typename mp::join<F>::template f<typename mp::wrap_in_list_c<!bs>::template f<xs>...>
    >;
  };
}
/// \endcond
