// SPDX-FileCopyrightText: 2023 Jonathan Poelen <jonathan.poelen@gmail.com>
// SPDX-License-Identifier: MIT
#pragma once

#include <jln/mp/detail/expr_conversion.hpp>
#include <jln/mp/functional/identity.hpp>
#include <jln/mp/functional/call.hpp>
#include <jln/mp/number/number.hpp>
#include <jln/mp/utility/enable_if.hpp>

#if JLN_MP_CUDA
#  include <type_traits>
#endif

namespace jln::mp
{
  /// \ingroup number

#if JLN_MP_CUDA
#  define JLN_MP_AS_BOOL(v) enable_if_t<std::size_t{v} <= 1, bool>{v}
#else
#  define JLN_MP_AS_BOOL(v) JLN_MP_INTEGRAL_AS(bool, v)
#endif

  /// Convertion without narrowing from \value to \bool.
  /// \treturn \bool
  template<class C = identity>
  struct as_bool
  {
    template<class x>
    using f = JLN_MP_CALL_TRACE(C, number<JLN_MP_AS_BOOL(x::value)>);
  };

  namespace emp
  {
    template<class x>
    using as_bool = number<JLN_MP_AS_BOOL(x::value)>;
  }

  /// \cond
  template<>
  struct as_bool<identity>
  {
    template<class x>
    using f = number<JLN_MP_AS_BOOL(x::value)>;
  };
  /// \endcond

#undef JLN_MP_AS_BOOL
}
