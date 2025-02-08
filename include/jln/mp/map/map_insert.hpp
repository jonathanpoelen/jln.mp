// SPDX-FileCopyrightText: 2023 Jonathan Poelen <jonathan.poelen@gmail.com>
// SPDX-License-Identifier: MIT
#pragma once

#include <jln/mp/list/front.hpp>
#include <jln/mp/list/push_back.hpp>
#include <jln/mp/functional/if.hpp>
#include <jln/mp/map/map_contains.hpp>

namespace jln::mp
{
  /// \ingroup map

  /// Inserts the element \c kv into the map, if the key \c emp::front<kv> does not exist.
  /// \pre \c is_map<>
  /// \treturn \map
  template<class kv, class C = listify>
  using map_insert = if_<map_contains<unpack<front<>>::f<kv>>, C, push_back<kv, C>>;

  /// Inserts the element \c list<k,v> into the map, if the key \c k does not exist.
  /// \pre \c is_map<>
  /// \treturn \map
  template<class k, class v, class C = listify>
  using map_insert_s = if_<map_contains<k>, C, push_back<list<k, v>, C>>;

  namespace emp
  {
    template<class L, class kv, class C = mp::listify>
    using map_insert = typename detail::_unpack<mp::map_insert<kv, C>, L>::type;

    template<class L, class k, class v, class C = mp::listify>
    using map_insert_s = typename detail::_unpack<mp::map_insert_s<k, v, C>, L>::type;
  }
}
