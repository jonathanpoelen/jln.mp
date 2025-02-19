// SPDX-FileCopyrightText: 2023 Jonathan Poelen <jonathan.poelen@gmail.com>
// SPDX-License-Identifier: MIT
#pragma once

#include <jln/mp/number/number.hpp>
#include <jln/mp/utility/unpack.hpp>
#include <jln/mp/utility/is.hpp>
#include <cstddef>

namespace jln::mp
{
  /// \ingroup list

  /// Returns the number of elements in a \c xs.
  /// \treturn \number
  template<class C = identity>
  struct size
  {
    template<class... xs>
    using f = JLN_MP_CALL_TRACE(C, number<sizeof...(xs)>);
  };

  namespace emp
  {
    template<class L, class C = mp::identity>
    using size = typename detail::_unpack<mp::size<C>, L>::type;

    template<class L, class C = mp::identity>
    inline constexpr std::size_t size_v = detail::_unpack<mp::size<C>, L>::type::value;
  }

  /// \cond
  template<>
  struct size<identity>
  {
    template<class... xs>
    using f = number<sizeof...(xs)>;
  };

  template<int_t i>
  struct size<is<number<i>>>
  {
    template<class... xs>
    using f = number<sizeof...(xs) == i>;
  };

  template<int_t i, class C>
  struct size<is<number<i>, C>>
  {
    template<class... xs>
    using f = JLN_MP_CALL_TRACE(C, number<sizeof...(xs) == i>);
  };
  /// \endcond
}
