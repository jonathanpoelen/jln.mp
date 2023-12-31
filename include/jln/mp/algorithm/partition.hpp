// SPDX-FileCopyrightText: 2023 Jonathan Poelen <jonathan.poelen@gmail.com>
// SPDX-License-Identifier: MIT
#pragma once

#include <jln/mp/algorithm/transform.hpp>
#include <jln/mp/algorithm/compress.hpp>
#include <jln/mp/utility/unpack.hpp>

namespace jln::mp
{
  /// \cond
  namespace detail
  {
    template<class Left, class Right>
    struct partition_dispatch;

    template<class F, bool... bs>
    using make_partition = partition_dispatch<
      compress_c_with<F, bs...>,
      compress_c_with<F, !bs...>
    >;

    template<class F>
    struct partition_caller
    {
      template<class... xs>
      struct f : make_partition<F, xs::value...>
      {};
    };
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
    using f = typename transform<Pred, detail::partition_caller<F>>
      ::template f<xs...>
      ::template g<JLN_MP_TRACE_F(C)::template f, identity::f, xs...>;
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
}


/// \cond
#if ! JLN_MP_OPTIMIZED_ALIAS && ! JLN_MP_ENABLE_DEBUG
namespace jln::mp
{
  template<class Pred, class F, template<class...> class C>
  struct partition_with<Pred, F, lift<C>>
  {
    template<class... xs>
    using f = typename transform<Pred, detail::partition_caller<F>>
      ::template f<xs...>
      ::template g<C, identity::f, xs...>;
  };
}
#endif

namespace jln::mp::detail
{
  template<class Left, class Right>
  struct partition_dispatch
  {
    template<template<class...> class C, template<class> class G, class... xs>
    using g = C<
      typename G<Left>::template f<xs...>,
      typename G<Right>::template f<xs...>
    >;
  };
}
/// \endcond
