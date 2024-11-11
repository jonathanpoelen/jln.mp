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
    using is_size_of = unpack<L, mp::is_size_of<N, C>>;

    template<class L, int_t n, class C = mp::identity>
    using is_size_of_c = unpack<L, mp::is_size_of_c<n, C>>;

    template<class L, class N, class C = mp::identity>
    inline constexpr bool is_size_of_v = unpack<L, mp::is_size_of<N, C>>::value;

    template<class L, int_t n, class C = mp::identity>
    inline constexpr bool is_size_of_c_v = unpack<L, mp::is_size_of_c<n, C>>::value;
  }
}
