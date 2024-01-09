// SPDX-FileCopyrightText: 2023 Jonathan Poelen <jonathan.poelen@gmail.com>
// SPDX-License-Identifier: MIT
#pragma once

#include <jln/mp/functional/identity.hpp>
#include <jln/mp/functional/call.hpp>
#include <jln/mp/number/number.hpp>

#if JLN_MP_CUDA
# include <cstddef>
#endif

namespace jln::mp
{
  /// \ingroup number

#if JLN_MP_CUDA
#  define JLN_MP_AS_NUMBER(v) std::enable_if_t<v < 0 || std::size_t{v} <= (~0ull >> 1), int_>{v}
#else
#  define JLN_MP_AS_NUMBER(v) int_{v}
#endif

  /// Narrowing convertion from \value to \number.
  /// \treturn \number
  template<class C = identity>
  struct as_number
  {
    template<class x>
    using f = JLN_MP_CALL_TRACE(C, number<JLN_MP_AS_NUMBER(x::value)>);
  };

  namespace emp
  {
    template<class x>
    using as_number = number<JLN_MP_AS_NUMBER(x::value)>;
  }

  /// \cond
  template<>
  struct as_number<identity>
  {
    template<class x>
    using f = number<JLN_MP_AS_NUMBER(x::value)>;
  };
  /// \endcond
}
