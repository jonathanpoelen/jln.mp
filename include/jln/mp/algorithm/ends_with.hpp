// SPDX-FileCopyrightText: 2023 Jonathan Poelen <jonathan.poelen@gmail.com>
// SPDX-License-Identifier: MIT
#pragma once

#include <jln/mp/algorithm/starts_with.hpp>

namespace jln::mp
{
  /// \cond
  namespace detail
  {
    template<bool>
    struct ends_with_impl;
  }
  /// \endcond

  /// \ingroup algorithm

  /// Checks if the \sequence ends with the given prefix.
  /// \treturn \bool
  /// \see ends_with
  template<class Seq, class C = identity>
  struct ends_with
  {};

  template<class... Ts, class C>
  struct ends_with<list<Ts...>, C>
  {
    template<class... xs>
    using f = JLN_MP_CALL_TRACE(C,
      typename detail::ends_with_impl<sizeof...(Ts) <= sizeof...(xs)>
      ::template f<sizeof...(Ts), list<Ts...>, xs...>
    );
  };

  namespace emp
  {
    template<class L, class Seq, class C = mp::identity>
    using ends_with = unpack<ends_with<Seq, C>, L>;
  }

  /// \cond
  template<class... Ts>
  struct ends_with<list<Ts...>, identity>
  {
    template<class... xs>
    using f = typename detail::ends_with_impl<sizeof...(Ts) <= sizeof...(xs)>
      ::template f<sizeof...(Ts), list<Ts...>, xs...>;
  };

  template<class C>
  struct ends_with<list<>, C>
  {
    template<class... xs>
    using f = JLN_MP_DCALL_TRACE_XS(xs, C, true_);
  };

  template<>
  struct ends_with<list<>, identity> : always<true_>
  {};
  /// \endcond
}

/// \cond
#include <jln/mp/list/drop_front.hpp>

namespace jln::mp::detail
{
  template<>
  struct ends_with_impl<true>
  {
    template<unsigned n, class L, class... xs>
    using f = number<JLN_MP_IS_SAME(
      typename drop_front_c<sizeof...(xs) - n>::template f<xs...>,
      L
    )>;
  };

  template<>
  struct ends_with_impl<false> : starts_with_impl<false>
  {};
}
/// \endcond
