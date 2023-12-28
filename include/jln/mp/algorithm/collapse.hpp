// SPDX-FileCopyrightText: 2023 Jonathan Poelen <jonathan.poelen@gmail.com>
// SPDX-License-Identifier: MIT
#pragma once

#include <jln/mp/algorithm/group.hpp>
#include <jln/mp/list/take_front.hpp>

namespace jln::mp
{
  /// \ingroup group

  /// Groups adjacent elements by adjacent keys.
  /// \pre `emp::is_list<Keys>` == `true`
  /// \pre `emp::size<Keys>` == `sizeof...(xs)`
  /// \semantics
  ///   \code
  ///   collapse<emp::numbers<1, 1, 0, 0, 0, 1, 2, 2>>
  ///   ::f<_0, _1, 2, _3, _4, _5, _6, _7>
  ///   ==
  ///   list<
  ///     list<_0, _1>,
  ///     list<_2, _3, _4>,
  ///     list<_5>,
  ///     list<_6, _7>
  ///   >
  ///   \endcode
  /// \note \c collapse<list<xs...>>::f<xs...> == \c group<>::f<xs...>
  /// \treturn \sequence
  template<class Keys, class C = listify>
  struct collapse
  {};

#ifdef JLN_MP_DOXYGENATING
  template<class... keys, class C>
  struct collapse<list<keys...>, C>
  {
    template<class... xs>
    using f;
  };
#endif

  template<class... keys>
  using collapse_for = collapse<list<keys...>>;

  template<bool... keys>
  using collapse_for_c = collapse<list<number<keys>...>>;

  namespace emp
  {
    template<class L, class Keys, class C = mp::listify>
    using collapse = unpack<L, mp::collapse<Keys, C>>;

    template<class L, class... keys>
    using collapse_for = unpack<L, mp::collapse<mp::list<keys...>>>;

    template<class L, bool... keys>
    using collapse_for_c = unpack<L, mp::collapse<mp::list<number<keys>...>>>;
  }


  /// \cond
  namespace detail
  {
    template<class...>
    struct make_collapse;
  }

  template<class C>
  struct collapse<list<>, C>
  {
    template<class... xs>
    using f = typename detail::_group<sizeof...(xs) != 0>
      ::template f<C, list<>>;
  };

  template<class key, class... keys, class C>
  struct collapse<list<key, keys...>, C>
  : detail::make_collapse<
      typename take_front_c<sizeof...(keys)>::template f<key, keys...>,
      keys...
    >::template f<C>
  {};
  /// \endcond
}


namespace jln::mp::detail
{
  template<class C, class... ns>
  struct _collapse
  {
    template<class x, class... xs>
    using f = typename fold_right<JLN_MP_LIFT_WRAP(split_state), unpack<_group_insert_x<x, C>>>
      ::template f<list<list<>>, list<ns, xs>...>;
  };

  template<class... xs, class... ys>
  struct make_collapse<list<ys...>, xs...>
  {
    template<class C>
    using f = _collapse<
      C, number<std::is_same<ys, xs>::value ? split_keep : split_before>...
    >;
  };
}
