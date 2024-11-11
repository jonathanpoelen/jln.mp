// SPDX-FileCopyrightText: 2023 Jonathan Poelen <jonathan.poelen@gmail.com>
// SPDX-License-Identifier: MIT
#pragma once

#include <cstdint>

namespace jln::mp
{
  /// \ingroup number

  using int_t = std::intmax_t;
  using uint_t = std::uintmax_t;
  // old version of int_t, but keep for compatibility reasons
  // and because msvc gives errors which make no sense when renaming the type
  using int_ = std::intmax_t;
  // old version of uint_t, but keep for compatibility reasons
  // and because msvc gives errors which make no sense when renaming the type
  using uint_ = std::uintmax_t;

  template<int_ v>
  struct number { static const int_ value = v; };

  using true_ = number<1>;
  using false_ = number<0>;

#ifndef JLN_MP_ENABLE_TPL_AUTO
# if defined(__cpp_nontype_template_parameter_auto)
#   if __cpp_nontype_template_parameter_auto >= 201606L
#     define JLN_MP_ENABLE_TPL_AUTO 1
#   endif
# endif
#endif

#ifndef JLN_MP_ENABLE_TPL_AUTO
# define JLN_MP_ENABLE_TPL_AUTO 0
#endif

#if JLN_MP_ENABLE_TPL_AUTO
# define JLN_MP_TPL_AUTO_OR_INT auto
# define JLN_MP_TPL_AUTO_OR(T) auto
#else
# define JLN_MP_TPL_AUTO_OR_INT ::jln::mp::int_
# define JLN_MP_TPL_AUTO_OR(T) T
#endif
}
