// SPDX-FileCopyrightText: 2025 Jonathan Poelen <jonathan.poelen@gmail.com>
// SPDX-License-Identifier: MIT
#pragma once

#include <jln/mp/detail/expr_to_bool.hpp>
#include <jln/mp/functional/identity.hpp>
#include <jln/mp/utility/unpack.hpp>
#include <jln/mp/detail/compiler.hpp>
#include <jln/mp/list/list.hpp>

namespace jln::mp
{
  /// \ingroup algorithm

/// Fast implementation of std::is_same_v.
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

  /// Checks whether all \values are identical.
  /// \treturn \bool
  template<class C = identity>
  struct same
  {
    template<class... xs>
    using f = JLN_MP_CALL_TRACE(C, number<emp::same_xs_v<xs...>>);
  };

  template<class C = identity>
  struct same_v
  {
    template<class... xs>
    using f = typename C::template f<emp::same_xs_v<xs...>>;
  };

  namespace emp
  {
    template<class L, class C = mp::identity>
    using same = typename detail::_unpack<mp::same<C>, L>::type;

    template<class L, class C = mp::identity>
    inline constexpr bool same_v = detail::_unpack<mp::same<C>, L>::type::value;
  }
}


/// \cond
namespace jln::mp
{
  template<>
  struct same<identity>
  {
    template<class... xs>
    using f = number<emp::same_xs_v<xs...>>;
  };
}
/// \endcond
