// SPDX-FileCopyrightText: 2023 Jonathan Poelen <jonathan.poelen@gmail.com>
// SPDX-License-Identifier: MIT
#pragma once

#include <jln/mp/algorithm/same_xs.hpp>
#include <jln/mp/number/number.hpp>
#include <jln/mp/utility/unpack.hpp>
#include <jln/mp/functional/call.hpp>
#include <jln/mp/functional/identity.hpp>
#include <cstddef>

namespace jln::mp
{
  /// \cond
  namespace detail
  {
    template<class T>
    struct normalize_similar;
  }
  /// \endcond

  /// \ingroup algorithm

  namespace emp
  {
    template<class... xs>
    inline constexpr bool similar_xs_v
      = same_xs_v<typename detail::normalize_similar<xs>::type...>;
  }

  /// Checks whether all types are the same or instantiations of the same class template.
  /// The list of supported class templates are:
  ///   - `template<class...>`
  ///   - `template<class T, T...>`
  ///   - `template<class, std::size_t>`
  ///   - `template<std::size_t, class...>`
  ///   - `template<class, auto...>` (when supported)
  ///   - `template<auto, class...>` (when supported)
  ///   - `template<auto...>` (when supported)
  /// \treturn \bool
  template<class C = identity>
  struct similar
  {
    template<class... xs>
    using f = JLN_MP_CALL_TRACE(C, number<emp::similar_xs_v<xs...>>);
  };

  template<class C = identity>
  struct similar_v
  {
    template<class... xs>
    using f = typename C::template f<emp::similar_xs_v<xs...>>;
  };

  namespace emp
  {
    template<class L, class C = mp::identity>
    using similar = typename detail::_unpack<mp::similar<C>, L>::type;

    template<class L, class C = mp::identity>
    inline constexpr bool similar_v = detail::_unpack<mp::similar<C>, L>::type::value;
  }
}


#include <jln/mp/number/not.hpp>

/// \cond
namespace jln::mp
{
  template<>
  struct similar<identity>
  {
    template<class... xs>
    using f = number<emp::same_xs_v<typename detail::normalize_similar<xs>::type...>>;
  };

  template<class C>
  struct similar<not_<C>>
  {
    template<class... xs>
    using f = JLN_MP_CALL_TRACE(C, number<JLN_MP_RAW_EXPR_TO_BOOL_NOT(
      emp::same_xs_v<typename detail::normalize_similar<xs>::type...>
    )>);
  };

  template<>
  struct similar<not_<>>
  {
    template<class... xs>
    using f = number<JLN_MP_RAW_EXPR_TO_BOOL_NOT(
      emp::same_xs_v<typename detail::normalize_similar<xs>::type...>
    )>;
  };
}

namespace jln::mp::detail
{
  template<template<class...> class Tpl>
  struct tpl_type1
  {
      using type = tpl_type1;
  };

  template<template<class T, JLN_MP_TPL_AUTO_OR(T)...> class Tpl>
  struct tpl_type2
  {
      using type = tpl_type2;
  };

#if JLN_MP_ENABLE_TPL_AUTO
  template<template<auto...> class Tpl>
#else
  template<template<class, std::size_t...> class Tpl>
#endif
  struct tpl_type3
  {
      using type = tpl_type3;
  };

  template<template<JLN_MP_TPL_AUTO_OR(std::size_t), class...> class Tpl>
  struct tpl_type4
  {
      using type = tpl_type4;
  };


#if !JLN_MP_ENABLE_TPL_AUTO
  template<class T>
  struct normalize_similar3
  {
    using type = T;
  };

  template<template<class, std::size_t...> class Tpl, class T, std::size_t... v>
  struct normalize_similar3<Tpl<T, v...>> : tpl_type3<Tpl>
  {};

  template<class T>
  struct normalize_similar2 : normalize_similar3<T>
  {};
#else // if JLN_MP_ENABLE_TPL_AUTO
  template<class T>
  struct normalize_similar2
  {
    using type = T;
  };

  template<template<auto...> class Tpl, auto... v>
  struct normalize_similar2<Tpl<v...>> : tpl_type3<Tpl>
  {};
#endif

  template<template<class T, JLN_MP_TPL_AUTO_OR(T)...> class Tpl,
           class T, JLN_MP_TPL_AUTO_OR(T)... v>
  struct normalize_similar2<Tpl<T, v...>> : tpl_type2<Tpl>
  {};

  template<class T>
  struct normalize_similar : normalize_similar2<T>
  {};

  template<template<class...> class Tpl, class... T>
  struct normalize_similar<Tpl<T...>> : tpl_type1<Tpl>
  {};

  template<template<JLN_MP_TPL_AUTO_OR(std::size_t), class...> class Tpl,
           JLN_MP_TPL_AUTO_OR(std::size_t) v, class... T>
  struct normalize_similar<Tpl<v, T...>> : tpl_type4<Tpl>
  {};
}
/// \endcond
