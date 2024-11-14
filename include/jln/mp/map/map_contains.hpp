// SPDX-FileCopyrightText: 2023 Jonathan Poelen <jonathan.poelen@gmail.com>
// SPDX-License-Identifier: MIT
#pragma once

#include <jln/mp/map/map_find.hpp>

namespace jln::mp
{
  /// \ingroup map

  /// Checks if a key exists in a \map.
  /// \treturn \bool
  /// \pre \c is_map<>
  template<class key, class C = identity>
  using map_contains = map_find<key, always<true_, C>, always<false_, C>>;

  /// Checks if a key does not exists in a \map.
  /// \treturn \bool
  /// \pre \c is_map<>
  template<class key, class C = identity>
  using map_not_contains = map_find<key, always<false_, C>, always<true_, C>>;

  namespace emp
  {
    template<class L, class key, class C = mp::identity>
    using map_contains = typename detail::_unpack<mp::map_contains<key, C>, L>::type;

    template<class L, class key, class C = mp::identity>
    using map_not_contains = typename detail::_unpack<mp::map_not_contains<key, C>, L>::type;

    template<class key, class... kvs>
    using map_contains_xs = typename mp::map_contains<key>::template f<kvs...>;

    template<class key, class... kvs>
    using map_not_contains_xs = typename mp::map_not_contains<key>::template f<kvs...>;

    template<class L, class key, class C = mp::identity>
    inline constexpr bool map_contains_v = detail::_unpack<mp::map_contains<key, C>, L>::type::value;

    template<class L, class key, class C = mp::identity>
    inline constexpr bool map_not_contains_v = detail::_unpack<mp::map_not_contains<key, C>, L>::type::value;

    template<class key, class... kvs>
    inline constexpr bool map_contains_xs_v = mp::map_contains<key>::template f<kvs...>::value;

    template<class key, class... kvs>
    inline constexpr bool map_not_contains_xs_v = !mp::map_contains<key>::template f<kvs...>::value;
  }
}
