// SPDX-FileCopyrightText: 2023 Jonathan Poelen <jonathan.poelen@gmail.com>
// SPDX-License-Identifier: MIT
#pragma once

#include <jln/mp/functional/identity.hpp>
#include <jln/mp/functional/call.hpp>
#include <jln/mp/value/val.hpp>
#include <jln/mp/detail/compiler.hpp>

namespace jln::mp
{
  /// \ingroup value

  /// Converts \c x to \val.
  /// \pre \c emp::has_value<x> == \c true
  /// \treturn \bool
  template<class C = identity>
  struct as_val
  {
#if JLN_MP_ENABLE_TPL_AUTO
    template<class x>
    using f = JLN_MP_CALL_TRACE(C, val<x::value>);
#else
    template<class x>
    using f = JLN_MP_CALL_TRACE(C, value_from<x>);
#endif
  };

  /// \cond
  template<>
  struct as_val<identity>
  {
#if JLN_MP_ENABLE_TPL_AUTO
    template<class x>
    using f = val<x::value>;
#else
    template<class x>
    using f = value_from<x>;
#endif
  };
  /// \endcond

  namespace emp
  {
    template<class x, class C = mp::identity>
    using as_val = typename mp::as_val<C>::template f<x>;
  }
}
