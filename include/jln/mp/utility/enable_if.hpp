// SPDX-FileCopyrightText: 2026 Jonathan Poelen <jonathan.poelen@gmail.com>
// SPDX-License-Identifier: MIT
#pragma once

#include <jln/mp/detail/compiler.hpp>

namespace jln::mp
{
  /// \ingroup trait

  /// If \c cond B is true, has a public member typedef type, equal to \c T;
  /// otherwise, there is no member typedef.
  /// It is preferable to use \c enable_if_t.
  template<bool cond, class T = void>
  struct enable_if
  {};

  template<class T>
  struct enable_if<true, T>
  {
    using type = T;
  };

  /// Implementation of \c std::enable_if_t.
  template<bool cond, class T = void>
  #if ! JLN_MP_HAS_MEMOIZED_TYPE_PACK_ELEMENT
  using enable_if_t = typename enable_if<cond, T>::type;
  #else
  using enable_if_t = __type_pack_element<!cond, T>;
  #endif
}
