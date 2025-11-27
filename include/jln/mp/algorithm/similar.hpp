// SPDX-FileCopyrightText: 2023 Jonathan Poelen <jonathan.poelen@gmail.com>
// SPDX-License-Identifier: MIT
#pragma once

#include <jln/mp/algorithm/same.hpp>
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
  struct tpl_tps
  {
      using type = tpl_tps;
  };

  template<template<class T, JLN_MP_TPL_AUTO_OR(T)...> class Tpl>
  struct tpl_tp_vals
  {
      using type = tpl_tp_vals;
  };

  template<template<JLN_MP_TPL_AUTO_OR(std::size_t), class...> class Tpl>
  struct tpl_val_tps
  {
      using type = tpl_val_tps;
  };


#if !JLN_MP_ENABLE_TPL_AUTO
  template<template<class, std::size_t...> class Tpl>
  struct tpl_tp_szs
  {
      using type = tpl_tp_szs;
  };

  template<class T>
  struct normalize_similar3
  {
    using type = T;
  };

  template<template<class, std::size_t...> class Tpl, class T, std::size_t... v>
  struct normalize_similar3<Tpl<T, v...>> : tpl_tp_szs<Tpl>
  {};

  template<class T>
  struct normalize_similar2 : normalize_similar3<T>
  {};

#else // if JLN_MP_ENABLE_TPL_AUTO

// fix not matching of `template<class T, T...>` with `Tpl<class, auto...>`
# if JLN_MP_CLANG_LIKE >= 2000
  template<template<class T, T...> class Tpl>
  struct tpl_tp_tvals
  {
      using type = tpl_tp_tvals;
  };

  template<class T>
  struct normalize_similar3
  {
    using type = T;
  };

  template<template<class T, T...> class Tpl, class T, T... v>
  struct normalize_similar3<Tpl<T, v...>> : tpl_tp_tvals<Tpl>
  {};

  template<class T>
  struct normalize_similar2 : normalize_similar3<T>
  {};
# else
  template<class T>
  struct normalize_similar2
  {
    using type = T;
  };
# endif

  template<template<auto...> class Tpl>
  struct tpl_vals
  {
      using type = tpl_vals;
  };

  template<template<auto...> class Tpl, auto... v>
  struct normalize_similar2<Tpl<v...>> : tpl_vals<Tpl>
  {};
#endif

  template<template<class T, JLN_MP_TPL_AUTO_OR(T)...> class Tpl,
           class T, JLN_MP_TPL_AUTO_OR(T)... v>
  struct normalize_similar2<Tpl<T, v...>> : tpl_tp_vals<Tpl>
  {};

  template<class T>
  struct normalize_similar : normalize_similar2<T>
  {};

  template<template<class...> class Tpl, class... T>
  struct normalize_similar<Tpl<T...>> : tpl_tps<Tpl>
  {};

  template<template<JLN_MP_TPL_AUTO_OR(std::size_t), class...> class Tpl,
           JLN_MP_TPL_AUTO_OR(std::size_t) v, class... T>
  struct normalize_similar<Tpl<v, T...>> : tpl_val_tps<Tpl>
  {};
}
/// \endcond
