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

  /// Fast implementation of \c std::enable_if_t.
  template<bool cond, class T = void>
  #if JLN_MP_FEATURE_CONCEPTS && !JLN_MP_FAST_TYPE_PACK_ELEMENT
    requires (cond)
  using enable_if_t = T;
  #elif JLN_MP_ENABLE_TYPE_PACK_ELEMENT
  using enable_if_t = __type_pack_element<!cond, T>;
  #else
  using enable_if_t = typename enable_if<cond, T>::type;
  #endif
}
