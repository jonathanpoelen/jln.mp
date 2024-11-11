// SPDX-FileCopyrightText: 2023 Jonathan Poelen <jonathan.poelen@gmail.com>
// SPDX-License-Identifier: MIT
#pragma once

#include <jln/mp/detail/config.hpp>
#include <jln/mp/number/number.hpp>  // JLN_MP_ENABLE_TPL_AUTO

#if !JLN_MP_ENABLE_TPL_AUTO || (JLN_MP_ENABLE_DEBUG && !JLN_MP_CLANG_LIKE)
#  include <type_traits>
#endif

namespace jln::mp
{
  /// \ingroup value

#if JLN_MP_ENABLE_TPL_AUTO
# if !JLN_MP_ENABLE_DEBUG || JLN_MP_CLANG_LIKE
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
  using val = typed_value<std::remove_const_t<decltype(v)>, v>;

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
  using value_from = typed_value<std::remove_const_t<decltype(T::value)>, T::value>;
#endif
}
