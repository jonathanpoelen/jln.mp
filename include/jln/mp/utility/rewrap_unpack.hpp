// SPDX-FileCopyrightText: 2023 Jonathan Poelen <jonathan.poelen@gmail.com>
// SPDX-License-Identifier: MIT
#pragma once

#include <jln/mp/utility/unpack.hpp>
#include <jln/mp/utility/wrapper.hpp>

namespace jln::mp
{
  /// \ingroup utility

  /// Rewrap result of \c unpack<C> in the same type as \c L.
  /// \semantics
  ///   \code
  ///   rewrap_unpack<C>::f<L, xs...>
  ///   ==
  ///   unpack<emp::wraper<L>>::f<unpack<C>::f<L, xs...>>
  ///
  ///   rewrap_unpack<remove<b>>::f<std::tuple<a, b, c>, d, e>
  ///   ==
  ///   std::tuple<d, e, a, c>
  ///   \endcode
  /// \treturn \sequence
  template<class C>
  struct rewrap_unpack
  {
    template<class L, class... xs>
    using f = typename detail::_unpack<
      typename detail::wrapper<L>::type,
      typename detail::_unpack<C, L, xs...>::type
    >::type;
  };

  /// Rewrap result of \c unpack_append<C> in the same type as \c L.
  /// \semantics
  ///   \code
  ///   rewrap_unpack_append<C>::f<L, xs...>
  ///   ==
  ///   unpack<emp::wraper<L>>::f<unpack_append<C>::f<L, xs...>>
  ///
  ///   rewrap_unpack<remove<b>>::f<std::tuple<a, b, c>, d, e>
  ///   ==
  ///   std::tuple<a, c, d, e>
  ///   \endcode
  /// \treturn \sequence
  template<class C>
  struct rewrap_unpack_append
  {
    template<class L, class... xs>
    using f = typename detail::_unpack<
      typename detail::wrapper<L>::type,
      typename detail::_unpack_append<C, L, xs...>::type
    >::type;
  };

  namespace emp
  {
    template<class L, class C, class... xs>
    using rewrap_unpack = typename detail::_unpack<
      wrapper<L>,
      typename detail::_unpack<C, L, xs...>::type
    >::type;

    template<class L, class C, class... xs>
    using rewrap_unpack_append = typename detail::_unpack<
      wrapper<L>,
      typename detail::_unpack_append<C, L, xs...>::type
    >::type;
  }
} // namespace jln::mp
