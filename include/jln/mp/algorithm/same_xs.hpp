// SPDX-FileCopyrightText: 2023 Jonathan Poelen <jonathan.poelen@gmail.com>
// SPDX-License-Identifier: MIT
#pragma once

#include <jln/mp/detail/compiler.hpp>
#include <jln/mp/list/list.hpp>

namespace jln::mp
{
  /// \ingroup algorithm

#if JLN_MP_HAS_BUILTIN(__is_same)
#  define JLN_MP_IS_SAME(...) __is_same(__VA_ARGS__)
#else
#  define JLN_MP_IS_SAME(...) ::jln::mp::emp::same_xs_v<__VA_ARGS__>
#endif

  namespace emp
  {
    template<class... xs>
    inline constexpr bool same_xs_v = true;

    template<class x>
    inline constexpr bool same_xs_v<x, x> = true;

    template<class x, class y>
    inline constexpr bool same_xs_v<x, y> = false;

    template<class x, class y, class z, class... xs>
    inline constexpr bool same_xs_v<x, y, z, xs...> =
#if JLN_MP_HAS_BUILTIN(__is_same)
      __is_same(list<x, y, z, xs...>, list<y, z, xs..., x>)
#else
      same_xs_v<list<x, y, z, xs...>, list<y, z, xs..., x>>
#endif
    ;
  }
}
