// SPDX-FileCopyrightText: 2023 Jonathan Poelen <jonathan.poelen@gmail.com>
// SPDX-License-Identifier: MIT
#pragma once

#include <jln/mp/list/front.hpp>
#include <jln/mp/list/push_back.hpp>
#include <jln/mp/algorithm/transform.hpp>
#include <jln/mp/functional/if.hpp>
#include <jln/mp/functional/partial_tee.hpp>
#include <jln/mp/map/map_contains.hpp>
#include <jln/mp/utility/wrapper.hpp>

namespace jln::mp
{
  /// \ingroup map

  /// If the \map contain the key \c Key, replaces the existing element `L<k, v...>` with `F<k, v...>`.
  /// \pre \c is_map<>
  /// \treturn \sequence
  template<class Key, class F, class C = listify>
  using map_update = transform<map_find<Key, F, front<>>, C>;

  /// Update an element `L<k, v...>` with `L<k, F<k, v...>>`.
  /// \pre `unpack<size<>>::f<x> >= 1`
  template<class F>
  struct map_element_value_update
  {
    template<class x>
    using f = typename detail::_unpack<tee<front<>, F, emp::wrapper<x>>, x>::type;
  };

  /// Update an element `L<k, v...>` with `L<F<k, v...>, v...>`.
  /// \pre `unpack<size<>>::f<x> >= 1`
  template<class F>
  struct map_element_key_update
  {
    template<class x>
    using f = typename detail::_unpack<partial_tee<F, emp::wrapper<x>>, x>::type;
  };

  /// If the \map contain the key \c Key, replaces the existing element `L<k, v...>` with `L<F<k, v...>, v...>`.
  /// \pre \c is_map<>
  /// \treturn \sequence
  template<class Key, class F, class C = listify>
  using map_key_update = map_update<Key, map_element_key_update<F>, C>;

  /// If the \map contain the key \c Key, replaces the existing element `L<k, v...>` with `L<k, F<k, v...>>`.
  /// \pre \c is_map<>
  /// \treturn \map
  template<class Key, class F, class C = listify>
  using map_value_update = map_update<Key, map_element_value_update<F>, C>;

  /// If the \map contain a key \c emp::front<KV>, replaces the existing element `L<k, v...>` with `F<k, v...>`; otherwise, inserts it using \c push_back<KV>.
  /// \pre \c is_map<>
  /// \treturn \sequence
  template<class KV, class F, class C = listify>
  using map_update_or_insert = if_<
    map_contains<unpack<front<>>::f<KV>>,
    map_update<unpack<front<>>::f<KV>, F, C>,
    push_back<KV, C>
  >;

  /// If the \map contain a key \c emp::front<KV>, replaces the existing element `L<k, v...>` with `L<k, F<k, v...>>`; otherwise, inserts it using \c push_back<KV>.
  /// \pre \c is_map<>
  /// \treturn \map
  template<class KV, class F, class C = listify>
  using map_value_update_or_insert = map_update_or_insert<KV, map_element_value_update<F>, C>;


  namespace emp
  {
    template<class L, class Key, class F, class C = mp::listify>
    using map_update = typename detail::_unpack<mp::map_update<Key, F, C>, L>::type;

    template<class KV, class F>
    using map_element_key_update = typename mp::map_element_key_update<F>
      ::template f<KV>;

    template<class KV, class F>
    using map_element_value_update = typename mp::map_element_value_update<F>
      ::template f<KV>;

    template<class L, class Key, class F, class C = mp::listify>
    using map_key_update =
      typename detail::_unpack<mp::map_key_update<Key, F, C>, L>::type;

    template<class L, class Key, class F, class C = mp::listify>
    using map_value_update =
      typename detail::_unpack<mp::map_value_update<Key, F, C>, L>::type;

    template<class L, class KV, class F, class C = mp::listify>
    using map_update_or_insert =
      typename detail::_unpack<mp::map_update_or_insert<KV, F, C>, L>::type;

    template<class L, class KV, class F, class C = mp::listify>
    using map_value_update_or_insert =
      typename detail::_unpack<mp::map_value_update_or_insert<KV, F, C>, L>::type;
  }
}
