// SPDX-FileCopyrightText: 2023 Jonathan Poelen <jonathan.poelen@gmail.com>
// SPDX-License-Identifier: MIT
#pragma once

#include <jln/mp/number/number.hpp>
#include <jln/mp/functional/identity.hpp>
#include <jln/mp/utility/unpack.hpp>

namespace jln::mp
{
  /// \ingroup list

  /// Difference between the number of parameter \c xs and \c I::value.
  /// \semantics
  ///   Equivalent to
  ///   \code
  ///   size<push_front<I, sub<C>>>
  ///   \endcode
  /// \treturn \number
  template<int_t I, class C = identity>
  struct offset_c
  {
    template<class... xs>
    using f = JLN_MP_CALL_TRACE(C, number<I - int_t(sizeof...(xs))>);
  };

  /// \cond
  template<int_t I>
  struct offset_c<I, identity>
  {
    template<class... xs>
    using f = number<I - int_t(sizeof...(xs))>;
  };
  /// \endcond

  template<class I, class C = identity>
  using offset = offset_c<I::value, C>;

  namespace emp
  {
    template<class L, class I, class C = mp::identity>
    using offset = typename detail::_unpack<mp::offset<I, C>, L>::type;

    template<class L, int_t i, class C = mp::identity>
    using offset_c = typename detail::_unpack<mp::offset_c<i, C>, L>::type;

    template<class L, class I, class C = mp::identity>
    inline constexpr int_t offset_v = detail::_unpack<mp::offset<I, C>, L>::type::value;

    template<class L, int_t i, class C = mp::identity>
    inline constexpr int_t offset_c_v = detail::_unpack<mp::offset_c<i, C>, L>::type::value;
  }
}
