// SPDX-FileCopyrightText: 2023 Jonathan Poelen <jonathan.poelen@gmail.com>
// SPDX-License-Identifier: MIT
#pragma once

#include <jln/mp/algorithm/group.hpp>
#include <jln/mp/list/take_front.hpp>

namespace jln::mp
{
  namespace jln::mp::detail
  {
    template<class C, class F, class Dispatcher>
    struct collapse_impl;
  }

  /// \ingroup group

  /// Groups adjacent elements by adjacent keys.
  /// \pre `sizeof...(keys)` == `sizeof...(xs)`
  /// \semantics
  ///   \code
  ///   collapse_for< 1,  1,  0,  0,  0,  1,  2,  2>
  ///            ::f<_0, _1, _2, _3, _4, _5, _6, _7>
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
  template<class C, class F, class... keys>
  struct collapse2_with
  {
#ifdef JLN_MP_DOXYGENATING
    template<class... xs>
    using f;
#endif
  };

  template<class C, class F, int_t... keys>
  using collapse2_with_c = collapse2_with<C, F, number<keys>...>;

  template<class C, int_t... keys>
  using collapse2_c = collapse2_with<C, listify, number<keys>...>;

  template<class C, class... keys>
  using collapse2 = collapse2_with<C, listify, keys...>;


  template<class keys, class F = listify, class C = listify>
  using collapse_with = typename detail::_unpack<cfe<collapse2_with>, keys, C, F>::type;

  template<class keys, class C = listify>
  using collapse = typename detail::_unpack<cfe<collapse2_with>, keys, C, listify>::type;


  template<class... keys>
  using collapse_for = collapse2_with<listify, listify, keys...>;

  template<int_t... keys>
  using collapse_for_c = collapse2_with<listify, listify, number<keys>...>;


  namespace emp
  {
    template<class L, class keys, class F = listify, class C = listify>
    using collapse_with = typename detail::_unpack<mp::collapse_with<keys, F, C>, L>::type;

    template<class L, class keys, class C = listify>
    using collapse = typename detail::_unpack<mp::collapse_with<keys, listify, C>, L>::type;

    template<class L, class... keys>
    using collapse_for = typename detail::_unpack<
      mp::collapse2_with<listify, listify, keys...>, L>::type;

    template<class L, int_t... keys>
    using collapse_for_c = typename detail::_unpack<
      mp::collapse2_with<listify, listify, number<keys>...>, L>::type;
  }
}


#include <jln/mp/functional/memoize.hpp> // uncallable_function

/// \cond
namespace jln::mp::detail
{
  template<class C, class F, std::size_t n, class Dispatcher>
  struct collapse_impl
  {
    template<class... xs>
    using f = typename Dispatcher::template f<
      std::enable_if_t<sizeof...(xs) == n, C>,
      F,
      build_indexed_v<xs...>
    >;
  };
}

namespace jln::mp
{
  template<class C, class F>
  struct collapse2_with<C, F>
  {
    template<class... xs>
    using f = typename conditional_c<!sizeof...(xs)>
      ::template f<JLN_MP_TRACE_F(C), detail::uncallable_function>
      ::template f<>;
  };

  template<class C, class F, class key, class... keys>
  struct collapse2_with<C, F, key, keys...> : detail::collapse_impl<
    C, F, sizeof...(keys) + 1,
    detail::mk_pairs_indices<
      same<>,
      key,
      typename detail::take_front_impl<sizeof...(keys)>
        ::template f<sizeof...(keys), list, key, keys...>,
      keys...
    >
  >
  {};
}
/// \endcond
