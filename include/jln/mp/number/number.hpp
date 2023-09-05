// SPDX-FileCopyrightText: 2023 Jonathan Poelen <jonathan.poelen@gmail.com>
// SPDX-License-Identifier: MIT
#pragma once

#include <cstdint>

namespace jln::mp
{
  /// \ingroup number

  using int_ = std::intmax_t;
  using uint_ = std::intmax_t;

  template<int_ v>
  struct number { static const int_ value = v; };

  using true_ = number<1>;
  using false_ = number<0>;

#if defined( __cpp_nontype_template_parameter_auto)
# if  __cpp_nontype_template_parameter_auto >= 201606L
#  define JLN_MP_ENABLE_TPL_AUTO 1
#  define JLN_MP_TPL_AUTO_OR_INT auto
#  define JLN_MP_TPL_AUTO_OR(T) auto
# endif
#endif

#ifndef JLN_MP_TPL_AUTO_OR_INT
# define JLN_MP_TPL_AUTO_OR_INT ::jln::mp::int_
# define JLN_MP_ENABLE_TPL_AUTO 0
# define JLN_MP_TPL_AUTO_OR(T) T
#endif
}
