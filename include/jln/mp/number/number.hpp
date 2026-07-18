// SPDX-FileCopyrightText: 2023 Jonathan Poelen <jonathan.poelen@gmail.com>
// SPDX-License-Identifier: MIT
#pragma once

#include <cstdint>

namespace jln::mp
{
  /// \ingroup number

  using int_t = std::intmax_t;
  using uint_t = std::uintmax_t;

  /// Equivalent to `std::numeric_limits<int_t>::max()`.
  inline constexpr int_t int_max_v
      = (((int_t{1} << (sizeof(int_t) * 8 - 1 - 1)) - 1) << 1) + 1;
  /// Equivalent to `std::numeric_limits<int_t>::min()`.
  inline constexpr int_t int_min_v = -int_max_v - 1;

  /// Equivalent to `std::numeric_limits<uint_t>::max()`.
  inline constexpr uint_t uint_max_v = ~uint_t{};
  /// Equivalent to `std::numeric_limits<uint_t>::min()`.
  inline constexpr uint_t uint_min_v = 0;

  template<int_t v>
  struct number { static const int_t value = v; };

  using true_ = number<1>;
  using false_ = number<0>;

#ifndef JLN_MP_ENABLE_TPL_PARAM_AUTO
# if defined(__cpp_nontype_template_parameter_auto)
#   if __cpp_nontype_template_parameter_auto >= 201606L
#     define JLN_MP_ENABLE_TPL_PARAM_AUTO 1
#   endif
# endif
#endif

#ifndef JLN_MP_ENABLE_TPL_PARAM_AUTO
# define JLN_MP_ENABLE_TPL_PARAM_AUTO 0
#endif

#if JLN_MP_ENABLE_TPL_PARAM_AUTO
# define JLN_MP_TPL_PARAM_AUTO_OR_INT auto
# define JLN_MP_TPL_PARAM_AUTO_OR(T) auto
#else
# define JLN_MP_TPL_PARAM_AUTO_OR_INT ::jln::mp::int_t
# define JLN_MP_TPL_PARAM_AUTO_OR(T) T
#endif
}
