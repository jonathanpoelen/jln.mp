// SPDX-FileCopyrightText: 2023 Jonathan Poelen <jonathan.poelen@gmail.com>
// SPDX-License-Identifier: MIT
#pragma once

#include <jln/mp/map/map_update.hpp>

namespace jln::mp
{
  /// \ingroup map

  /// If the \map contain the key \c emp::front<KV>, replaces the existing element with \c KV.
  /// \pre \c is_map<>
  /// \treturn \map
  template<class KV, class C = listify>
  using map_replace = map_update<unpack<front<>>::f<KV>, always<KV>, C>;

  /// If the \map contain the key \c emp::front<KV>, replaces the existing element with \c KV; otherwise, inserts it using \c push_back<KV>.
  /// \pre \c is_map<>
  /// \treturn \map
  template<class KV, class C = listify>
  using map_replace_or_insert = map_update_or_insert<KV, always<KV>, C>;

  namespace emp
  {
    template<class L, class KV, class C = mp::listify>
    using map_replace = typename detail::_unpack<mp::map_replace<KV, C>, L>::type;

    template<class L, class KV, class C = mp::listify>
    using map_replace_or_insert = typename detail::_unpack<mp::map_replace_or_insert<KV, C>, L>::type;
  }
}
