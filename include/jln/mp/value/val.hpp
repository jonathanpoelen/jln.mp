// SPDX-FileCopyrightText: 2023 Jonathan Poelen <jonathan.poelen@gmail.com>
// SPDX-License-Identifier: MIT
#pragma once

#include <jln/mp/detail/config.hpp>
#include <jln/mp/number/number.hpp>  // JLN_MP_ENABLE_TPL_AUTO

#ifndef JLN_MP_VAL_AS_ALIAS
# define JLN_MP_VAL_AS_ALIAS (JLN_MP_ENABLE_DEBUG_ORIGINAL && !JLN_MP_CLANG_LIKE)
#endif

#if !JLN_MP_ENABLE_TPL_AUTO || JLN_MP_VAL_AS_ALIAS

# if JLN_MP_HAS_BUILTIN(__remove_const)
#   define JLN_MP_REMOVE_CONST_T __remove_const
# else
#   define JLN_MP_REMOVE_CONST_T(x) std::remove_const_t<x>
#   include <type_traits>
# endif

#endif

namespace jln::mp
{
  /// \ingroup value

#if JLN_MP_ENABLE_TPL_AUTO
# if !JLN_MP_VAL_AS_ALIAS
  // note: integer types are not displayed with some compilers
  // clang: val<0ll>
  // gcc: val<0> with 0 as long long
  template<auto v>
  struct val
  {
    static constexpr decltype(v) value = v;
  };

  template<class T, T v>
  using typed_value = val<v>;

  template<class T>
  using value_from = val<T::value>;
# else
  template<class T, T v>
  struct typed_value
  {
    static constexpr T const value = v;
  };

  template<auto v>
  using val = typed_value<JLN_MP_REMOVE_CONST_T(decltype(v)), v>;

  template<class T>
  using value_from = val<T::value>;
# endif
#else
  template<class T, T v>
  struct typed_value
  {
    static constexpr T const value = v;
  };

  template<int_t v>
  using val = typed_value<int_t, v>;

  template<class T>
  using value_from = typed_value<JLN_MP_REMOVE_CONST_T(decltype(T::value)), T::value>;
#endif
}

#ifdef JLN_MP_REMOVE_CONST_T
#  undef JLN_MP_REMOVE_CONST_T
#endif

#undef JLN_MP_VAL_AS_ALIAS
