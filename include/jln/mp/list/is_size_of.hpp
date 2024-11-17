// SPDX-FileCopyrightText: 2023 Jonathan Poelen <jonathan.poelen@gmail.com>
// SPDX-License-Identifier: MIT
#pragma once

#include <jln/mp/list/size.hpp>
#include <jln/mp/utility/is.hpp>

namespace jln::mp
{
  /// \ingroup list

  template<class N, class C = identity>
  using is_size_of = size<is<N, C>>;

  template<int_t n, class C = identity>
  using is_size_of_c = size<is<number<n>, C>>;

  namespace emp
  {
    template<class L, class N, class C = mp::identity>
    using is_size_of = typename detail::_unpack<mp::is_size_of<N, C>, L>::type;

    template<class L, int_t n, class C = mp::identity>
    using is_size_of_c = typename detail::_unpack<mp::is_size_of_c<n, C>, L>::type;

    template<class L, class N, class C = mp::identity>
    inline constexpr bool is_size_of_v = detail::_unpack<mp::is_size_of<N, C>, L>::type::value;

    template<class L, int_t n, class C = mp::identity>
    inline constexpr bool is_size_of_c_v = detail::_unpack<mp::is_size_of_c<n, C>, L>::type::value;
  }
}
