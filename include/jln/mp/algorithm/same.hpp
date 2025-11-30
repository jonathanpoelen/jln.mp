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

/// Fast implementation of \c std::is_same_v.
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
      JLN_MP_IS_SAME(list<x, y, z, xs...>, list<y, z, xs..., x>)
    ;
  }

#if JLN_MP_FEATURE_CONCEPTS
  template<class x, class y>
  concept same_as = JLN_MP_IS_SAME(x, y);

  template<class x, class y>
  concept not_same_as = !JLN_MP_IS_SAME(x, y);

  /// Equivalent to `std::enable_if_t<(same_as<T, Ts> && ... && true)>`.
  template<class T, same_as<T>...>
  using enable_if_all_same_as = void;

  /// Equivalent to `std::enable_if_t<(!same_as<T, Ts> && ... && true)>`.
  template<class T, not_same_as<T>...>
  using enable_if_none_same_as = void;
#endif


/// Fast implementation of `(std::is_same_v<T, xs> && ... && true)`.
#if !JLN_MP_HAS_BUILTIN(__is_same) || JLN_MP_GCC
# define JLN_MP_ALL_SAME_AS(T, xs) \
  JLN_MP_IS_SAME(::jln::mp::list<T, xs...>, ::jln::mp::list<xs..., T>)
#else
# define JLN_MP_ALL_SAME_AS(T, xs) (JLN_MP_IS_SAME(T, xs) && ... && true)
#endif

/// Fast implementation of `(!std::is_same_v<T, xs> && ... && true)`.
#if JLN_MP_REQUIRES_AS_FAST_SFINAE
# define JLN_MP_NONE_SAME_AS(T, xs) \
  requires { ::jln::mp::enable_if_none_same_as<T, xs...>(); }
#else
# define JLN_MP_NONE_SAME_AS(T, xs) !(JLN_MP_IS_SAME(T, xs) || ...)
#endif

/// Fast implementation of `(std::is_same_v<T, xs> || ...)`.
#if JLN_MP_REQUIRES_AS_FAST_SFINAE
# define JLN_MP_ANY_SAME_AS(T, xs) \
  !requires { ::jln::mp::enable_if_none_same_as<T, xs...>(); }
#else
# define JLN_MP_ANY_SAME_AS(T, xs) (JLN_MP_IS_SAME(T, xs) || ...)
#endif


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
