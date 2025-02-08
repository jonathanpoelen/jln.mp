// SPDX-FileCopyrightText: 2023 Jonathan Poelen <jonathan.poelen@gmail.com>
// SPDX-License-Identifier: MIT
#pragma once

#include <jln/mp/list/front.hpp>
#include <jln/mp/list/push_back.hpp>
#include <jln/mp/algorithm/transform.hpp>
#include <jln/mp/functional/if.hpp>
#include <jln/mp/map/map_contains.hpp>

namespace jln::mp
{
  namespace detail
  {
    template<class F, class kv>
    struct map_element_key_update_impl
    {};

    template<class F, class kv>
    struct map_element_value_update_impl
    {};
  }

  /// \ingroup map

  /// If the \map contain the key \c Key, replaces the existing element `L<k, v...>` with `F<k, v...>`.
  /// \pre \c is_map<>
  /// \treturn \sequence
  template<class Key, class F, class C = listify>
  using map_update = transform<map_find<Key, F, front<>>, C>;

  /// Update an element `L<k, v...>` with `L<F<k, v...>, v...>`.
  /// \pre `unpack<size<>>::f<x> >= 1`
  template<class F>
  struct map_element_key_update
  {
    template<class kv>
    using f = typename detail::map_element_key_update_impl<F, kv>::type;
  };

  /// Update an element `L<k, v...>` with `L<k, F<k, v...>>`.
  /// \pre `unpack<size<>>::f<kv> >= 1`
  template<class F>
  struct map_element_value_update
  {
    template<class kv>
    using f = typename detail::map_element_value_update_impl<F, kv>::type;
  };

  /// If the \map contain the key \c key, replaces the existing element `L<k, v...>` with `L<F<k, v...>, v...>`.
  /// \pre \c is_map<>
  /// \treturn \sequence
  template<class key, class F, class C = listify>
  using map_key_update = map_update<key, map_element_key_update<F>, C>;

  /// If the \map contain the key \c key, replaces the existing element `L<k, v...>` with `L<k, F<k, v...>>`.
  /// \pre \c is_map<>
  /// \treturn \map
  template<class key, class F, class C = listify>
  using map_value_update = map_update<key, map_element_value_update<F>, C>;

  /// If the \map contain a key \c emp::front<kv>, replaces the existing element `L<k, v...>` with `F<k, v...>`; otherwise, inserts it using \c push_back<kv>.
  /// \pre \c is_map<>
  /// \treturn \sequence
  /// \see map_update_s_or_insert
  template<class kv, class F, class C = listify>
  using map_update_or_insert = if_<
    map_contains<unpack<front<>>::f<kv>>,
    map_update<unpack<front<>>::f<kv>, F, C>,
    push_back<kv, C>
  >;

  /// If the \map contain a key \c k, replaces the existing element `L<k, v...>` with `F<k, v...>`; otherwise, inserts it using \c push_back<list<k,v>>.
  /// \pre \c is_map<>
  /// \treturn \sequence
  /// \see map_update_or_insert
  template<class k, class v, class F, class C = listify>
  using map_update_s_or_insert = if_<
    map_contains<k>,
    map_update<k, F, C>,
    push_back<list<k, v>, C>
  >;

  /// If the \map contain a key \c emp::front<kv>, replaces the existing element `L<k, v...>` with `L<k, F<k, v...>>`; otherwise, inserts it using \c push_back<kv>.
  /// \pre \c is_map<>
  /// \treturn \map
  /// \see map_value_update_s_or_insert
  template<class kv, class F, class C = listify>
  using map_value_update_or_insert = map_update_or_insert<kv, map_element_value_update<F>, C>;

  /// If the \map contain a key \c k, replaces the existing element `L<k, v...>` with `L<k, F<k, v...>>`; otherwise, inserts it using \c push_back<list<k,v>>.
  /// \pre \c is_map<>
  /// \treturn \map
  /// \see map_value_update_or_insert
  template<class k, class v, class F, class C = listify>
  using map_value_update_s_or_insert = map_update_s_or_insert<k, v, map_element_value_update<F>, C>;


  namespace emp
  {
    template<class L, class key, class F, class C = listify>
    using map_update = typename detail::_unpack<mp::map_update<key, F, C>, L>::type;

    template<class kv, class F>
    using map_element_key_update = typename detail::map_element_key_update_impl<F, kv>::type;

    template<class kv, class F>
    using map_element_value_update = typename detail::map_element_value_update_impl<F, kv>::type;

    template<class L, class key, class F, class C = listify>
    using map_key_update =
      typename detail::_unpack<mp::map_key_update<key, F, C>, L>::type;

    template<class L, class key, class F, class C = listify>
    using map_value_update =
      typename detail::_unpack<mp::map_value_update<key, F, C>, L>::type;

    template<class L, class kv, class F, class C = listify>
    using map_update_or_insert =
      typename detail::_unpack<mp::map_update_or_insert<kv, F, C>, L>::type;

    template<class L, class k, class v, class F, class C = listify>
    using map_update_s_or_insert =
      typename detail::_unpack<mp::map_update_s_or_insert<k, v, F, C>, L>::type;

    template<class L, class kv, class F, class C = listify>
    using map_value_update_or_insert =
      typename detail::_unpack<mp::map_value_update_or_insert<kv, F, C>, L>::type;

    template<class L, class k, class v, class F, class C = listify>
    using map_value_update_s_or_insert =
      typename detail::_unpack<mp::map_value_update_s_or_insert<k, v, F, C>, L>::type;
  }
}

#include <jln/mp/list/front.hpp>
#include <jln/mp/list/pop_front.hpp>

/// \cond
namespace jln::mp::detail
{
  template<class F, template<class...> class S, class k, class... v>
  struct map_element_key_update_impl<F, S<k, v...>>
  {
    using type = S<JLN_MP_CALL_TRACE(F, k, v...), v...>;
  };

  template<class F, template<class...> class S, class k, class... v>
  struct map_element_value_update_impl<F, S<k, v...>>
  {
    using type = S<k, JLN_MP_CALL_TRACE(F, k, v...)>;
  };

  template<class F, template<class...> class S, class k, class... v>
  struct map_element_key_update_impl<front<F>, S<k, v...>>
  {
    using type = S<JLN_MP_CALL_TRACE(F, k), v...>;
  };

  template<class F, template<class...> class S, class k, class... v>
  struct map_element_value_update_impl<front<F>, S<k, v...>>
  {
    using type = S<k, JLN_MP_CALL_TRACE(F, k)>;
  };

  template<class F, template<class...> class S, class k, class... v>
  struct map_element_key_update_impl<pop_front<F>, S<k, v...>>
  {
    using type = S<JLN_MP_CALL_TRACE(F, v...), v...>;
  };

  template<class F, template<class...> class S, class k, class... v>
  struct map_element_value_update_impl<pop_front<F>, S<k, v...>>
  {
    using type = S<k, JLN_MP_CALL_TRACE(F, v...)>;
  };
}
/// \endcond
