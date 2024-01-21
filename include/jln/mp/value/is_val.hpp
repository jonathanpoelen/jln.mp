// SPDX-FileCopyrightText: 2023 Jonathan Poelen <jonathan.poelen@gmail.com>
// SPDX-License-Identifier: MIT
#pragma once

#include <jln/mp/value/val.hpp>
#include <jln/mp/functional/call.hpp>
#include <jln/mp/functional/identity.hpp>

namespace jln::mp
{
  /// \cond
  namespace detail
  {
    template<class x>
    struct _is_val;
  }
  /// \endcond

  /// \ingroup value

  /// Checks whether \c x is a \val.
  /// \treturn \bool
  template<class C = identity>
  struct is_val
  {
    template<class x>
    using f = JLN_MP_CALL_TRACE(C, typename detail::_is_val<x>::type);
  };

  namespace emp
  {
    template<class x>
    using is_val = typename detail::_is_val<x>::type;
  }

  /// \cond
  template<>
  struct is_val<identity>
  {
    template<class x>
    using f = typename detail::_is_val<x>::type;
  };
  /// \endcond
}


#include <jln/mp/number/number.hpp>

/// \cond
namespace jln::mp::detail
{
  template<class x>
  struct _is_val
  {
    using type = false_;
  };

#if JLN_MP_ENABLE_TPL_AUTO && (!JLN_MP_ENABLE_DEBUG || JLN_MP_CLANG_LIKE)
  template<auto x>
  struct _is_val<val<x>>
#else
  template<class T, T x>
  struct _is_val<typed_value<T, x>>
#endif
  {
    using type = true_;
  };
}
/// \endcond
